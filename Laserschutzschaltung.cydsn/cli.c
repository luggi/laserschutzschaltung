#include "cli.h"
#include "pid.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "device.h"
#include "eeprom.h"
#include <math.h>

// we unset this on 'exit'
extern uint8_t cliMode;
static void cliDefaults(char *cmdline);
static void cliExit(char *cmdline);
static void cliHelp(char *cmdline);
static void cliSave(char *cmdline);
static void cliSet(char *cmdline);
static void cliStatus(char *cmdline);
static void cliSetPeltier(char *cmdline);

// from main.c
extern pid pid1;
extern int setpoint;
extern float Temperature;
extern uint32_t eventcounter;
extern uint8_t debug;
extern int deltaTms;
extern uint8_t dac_offset;
extern uint16_t current_offset;
extern float photodiode_power_coefficients[3];
extern int temp_limit;
extern float current_output_coeff;
extern float set_current_psu;
extern uint8_t auto_current;
extern float slope;

// buffer
static char cliBuffer[48];
static uint32_t bufferIndex = 0;

static float _atof(const char *p);
static char *ftoa(float x, char *floatString);


typedef struct {
    const char *name;
    const char *param;
    void (*func)(char *cmdline);
} clicmd_t;

// should be sorted a..z for bsearch()
const clicmd_t cmdTable[] = {
    { "defaults", "reset to defaults and reboot", cliDefaults },
    { "exit", "", cliExit },
    { "help", "", cliHelp },
    { "save", "save variables", cliSave },
    { "set", "name=value or blank or * for list", cliSet },
    { "setpeltier", "value for adc", cliSetPeltier },
    { "status", "show system status", cliStatus },
};
#define CMD_COUNT (sizeof(cmdTable) / sizeof(clicmd_t))

typedef enum {
    VAR_UINT8 = 0,
    VAR_INT8 = 1,
    VAR_UINT16 = 2,
    VAR_INT16 = 3,
    VAR_UINT32 = 4,
    VAR_FLOAT = 5,
    VAR_INT1DECIMALS = 11,
    VAR_INT2DECIMALS = 12,
    VAR_INT3DECIMALS = 13,
    VAR_INT4DECIMALS = 14,
} vartype_e;

typedef union {
    float fInput;
    int   iInput;
} inputValue_u;

typedef struct {
    uint8_t type;
    inputValue_u value;
} inputValue_t;


typedef struct {
    const char *name;
    const uint8_t type; // vartype_e
    void *ptr;
    const int32_t min;
    const int32_t max;
} clivalue_t;


const clivalue_t valueTable[] = { // { "name", VAR_TYPE, &varpointer, min, max } neue variablen zur Konfiguration hier hinzufügen
    { "P-term", VAR_INT1DECIMALS, &pid1.P, 0, 100},
	{ "I-term", VAR_INT2DECIMALS, &pid1.I, 0, 100},
	{ "D-term", VAR_INT2DECIMALS, &pid1.D, 0, 100},
	{ "setpoint", VAR_INT2DECIMALS, &setpoint, 0, 50},
    { "temperature_limit", VAR_INT2DECIMALS, &temp_limit, 0, 60},
    { "Regelzeit", VAR_INT3DECIMALS, &deltaTms, 0, 10},
    { "windup", VAR_UINT32, &pid1.windup, 0, 10000000},
    { "debug_output", VAR_UINT8, &debug, 0, 1},
    { "dac_offset", VAR_UINT8, &dac_offset, 0, 255},
    { "current_offset", VAR_INT16, &current_offset, 0, 8192},
    { "pd_seed_coeff", VAR_FLOAT, &photodiode_power_coefficients[0], 0, 100000},
    { "pd_pump_coeff", VAR_FLOAT, &photodiode_power_coefficients[1], 0, 100000},
    { "pd_osc_coeff", VAR_FLOAT, &photodiode_power_coefficients[2], 0, 100000},
    { "current_output_coeff", VAR_FLOAT, &current_output_coeff, 0, 100},
    { "set_current_psu", VAR_FLOAT, &set_current_psu, 0, 45},
    { "current_slope", VAR_FLOAT, &slope, 0, 10},
    { "automatic_current_control", VAR_UINT8, &auto_current, 0, 1},
};

#define VALUE_COUNT (sizeof(valueTable) / sizeof(clivalue_t))

typedef union {
    int32_t int_value;
    float float_value;
} int_float_value_t;

static void cliSetVar(const clivalue_t *var, const int_float_value_t value);
static void cliPrintVar(const clivalue_t *var, uint32_t full);
static void cliPrint(const char *str);
static void cliWrite(uint8_t ch);

#ifndef HAVE_ITOA_FUNCTION

/*
** The following two functions together make up an itoa()
** implementation. Function i2a() is a 'private' function
** called by the public itoa() function.
**
** itoa() takes three arguments:
**        1) the integer to be converted,
**        2) a pointer to a character conversion buffer,
**        3) the radix for the conversion
**           which can range between 2 and 36 inclusive
**           range errors on the radix default it to base10
** Code from http://groups.google.com/group/comp.lang.c/msg/66552ef8b04fe1ab?pli=1
*/

static char *i2a(unsigned i, char *a, unsigned r)
{
    if (i / r > 0)
        a = i2a(i / r, a, r);
    *a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i % r];
    return a + 1;
}

char *itoa(int i, char *a, int r)
{
    if ((r < 2) || (r > 36))
        r = 10;
    if (i < 0) {
        *a = '-';
        *i2a(-(unsigned)i, a + 1, r) = 0;
    } else
        *i2a(i, a, r) = 0;
    return a;
}

#endif

////////////////////////////////////////////////////////////////////////////////
// String to Float Conversion
///////////////////////////////////////////////////////////////////////////////
// Simple and fast atof (ascii to float) function.
//
// - Executes about 5x faster than standard MSCRT library atof().
// - An attractive alternative if the number of calls is in the millions.
// - Assumes input is a proper integer, fraction, or scientific format.
// - Matches library atof() to 15 digits (except at extreme exponents).
// - Follows atof() precedent of essentially no error checking.
//
// 09-May-2009 Tom Van Baak (tvb) www.LeapSecond.com
//
#define white_space(c) ((c) == ' ' || (c) == '\t')
#define valid_digit(c) ((c) >= '0' && (c) <= '9')
static float _atof(const char *p)
{
    int frac = 0;
    float sign, value, scale;

    // Skip leading white space, if any.
    while (white_space(*p) ) {
        p += 1;
    }

    // Get sign, if any.
    sign = 1.0f;
    if (*p == '-') {
        sign = -1.0f;
        p += 1;

    } else if (*p == '+') {
        p += 1;
    }

    // Get digits before decimal point or exponent, if any.
    value = 0.0f;
    while (valid_digit(*p)) {
        value = value * 10.0f + (*p - '0');
        p += 1;
    }

    // Get digits after decimal point, if any.
    if (*p == '.') {
        float pow10 = 10.0f;
        p += 1;

        while (valid_digit(*p)) {
            value += (*p - '0') / pow10;
            pow10 *= 10.0f;
            p += 1;
        }
    }

    // Handle exponent, if any.
    scale = 1.0f;
    if ((*p == 'e') || (*p == 'E')) {
        unsigned int expon;
        p += 1;

        // Get sign of exponent, if any.
        frac = 0;
        if (*p == '-') {
            frac = 1;
            p += 1;

        } else if (*p == '+') {
            p += 1;
        }

        // Get digits of exponent, if any.
        expon = 0;
        while (valid_digit(*p)) {
            expon = expon * 10 + (*p - '0');
            p += 1;
        }
        if (expon > 308) 
            expon = 308;

        // Calculate scaling factor.
        // while (expon >= 50) { scale *= 1E50f; expon -= 50; }
        while (expon >=  8) { scale *= 1E8f;  expon -=  8; }
        while (expon >   0) { scale *= 10.0f; expon -=  1; }
    }

    // Return signed and scaled floating point result.
    return sign * (frac ? (value / scale) : (value * scale));
}

///////////////////////////////////////////////////////////////////////////////
// FTOA
///////////////////////////////////////////////////////////////////////////////
static char *ftoa(float x, char *floatString)
{
    int32_t value;
    char intString1[12];
    char intString2[12] = { 0, };
    char *decimalPoint = ".";
    uint8_t dpLocation;

    if (x > 0)                  // Rounding for x.xxx display format
        x += 0.0005f;
    else
        x -= 0.0005f;

    value = (int32_t) (x * 1000.0f);    // Convert float * 1000 to an integer

    itoa(ABS(value), intString1, 10);   // Create string from abs of integer value

    if (value >= 0)
        intString2[0] = ' ';    // Positive number, add a pad space
    else
        intString2[0] = '-';    // Negative number, add a negative sign

    if (strlen(intString1) == 1) {
        intString2[1] = '0';
        intString2[2] = '0';
        intString2[3] = '0';
        strcat(intString2, intString1);
    } else if (strlen(intString1) == 2) {
        intString2[1] = '0';
        intString2[2] = '0';
        strcat(intString2, intString1);
    } else if (strlen(intString1) == 3) {
        intString2[1] = '0';
        strcat(intString2, intString1);
    } else {
        strcat(intString2, intString1);
    }

    dpLocation = strlen(intString2) - 3;

    strncpy(floatString, intString2, dpLocation);
    floatString[dpLocation] = '\0';
    strcat(floatString, decimalPoint);
    strcat(floatString, intString2 + dpLocation);

    return floatString;
}

int n_pow(int a, int e)
{
    while(e > 1)
    {
        a *= a;
        e--;
    }
    return a;
}

static void cliPrompt(void)
{
    cliPrint("\r\n# ");
}

static int cliCompare(const void *a, const void *b)
{
    const clicmd_t *ca = a, *cb = b;
    return strncasecmp(ca->name, cb->name, strlen(cb->name));
}

static void cliDefaults(char *cmdline)
{
    cliPrint("Resetting to defaults...\r\n");

}

static void cliExit(char *cmdline)
{
    cliPrint("\r\nLeaving CLI mode...\r\n");
    *cliBuffer = '\0';
    bufferIndex = 0;
    cliMode = 0;
}

static void cliHelp(char *cmdline)
{
    uint32_t i = 0;
	char buffer_temp[64];

    cliPrint("Available commands:\r\n");
    for (i = 0; i < CMD_COUNT; i++) {
        sprintf(buffer_temp, "%s\t%s\r\n", cmdTable[i].name, cmdTable[i].param);
		cliPrint(buffer_temp);
    }
}

static void cliSave(char *cmdline)
{
 // todo save parameters
    if(save_settings()) cliPrint("settings saved");
    else cliPrint("failed");
}

static void cliPrint(const char *str)
{
	while(!USBUART_1_CDCIsReady());
	USBUART_1_PutString(str);   
}

static void cliWrite(uint8_t ch)
{
	if(USBUART_1_CDCIsReady())
        USBUART_1_PutChar(ch);
}

static void cliPrintVar(const clivalue_t *var, uint32_t full)
{
    int32_t value = 0;
    float fvalue = 0;
	char buffer_temp[64];
    char buf[16];

    switch (var->type) {
        case VAR_UINT8:
            value = *(uint8_t *)var->ptr;
            break;

        case VAR_INT8:
            value = *(int8_t *)var->ptr;
            break;

        case VAR_UINT16:
            value = *(uint16_t *)var->ptr;
            break;

        case VAR_INT16:
            value = *(int16_t *)var->ptr;
            break;

        case VAR_UINT32:
            value = *(uint32_t *)var->ptr;
            break;

        case VAR_FLOAT:
            sprintf(buffer_temp, "%s", ftoa(*(float *)var->ptr, buf));
			cliPrint(buffer_temp);
            if (full) {
                sprintf(buffer_temp, " %s", ftoa((float)var->min, buf));
				cliPrint(buffer_temp);
                sprintf(buffer_temp, " %s", ftoa((float)var->max, buf));
				cliPrint(buffer_temp);
            }
            return; // return from case for float only
            
        case VAR_INT1DECIMALS:
        case VAR_INT2DECIMALS:
        case VAR_INT3DECIMALS:
        case VAR_INT4DECIMALS:
            fvalue = (float)(*(int *)var->ptr) / (float)n_pow(10,var->type - 10);
            sprintf(buffer_temp, "%s", ftoa(fvalue, buf));
			cliPrint(buffer_temp);
            if (full) {
                sprintf(buffer_temp, " %s", ftoa((float)var->min, buf));
				cliPrint(buffer_temp);
                sprintf(buffer_temp, " %s", ftoa((float)var->max, buf));
				cliPrint(buffer_temp);
            }
            return; // return from case for float only
        
    }
    sprintf(buffer_temp, "%d", (int)value);
	cliPrint(buffer_temp);
    if (full) {
        sprintf(buffer_temp, " %d %d", (int)var->min, (int)var->max);
		cliPrint(buffer_temp);
    }
}

static void cliSetVar(const clivalue_t *var, const int_float_value_t value)
{
    switch (var->type) {
        case VAR_UINT8:
        case VAR_INT8:
            *(char *)var->ptr = (char)value.int_value;
            break;

        case VAR_UINT16:
        case VAR_INT16:
            *(short *)var->ptr = (short)value.int_value;
            break;

        case VAR_UINT32:
            *(int *)var->ptr = (int)value.int_value;
            break;

        case VAR_FLOAT:
            *(float *)var->ptr = (float)value.float_value;
            break;
        
        case VAR_INT1DECIMALS:
        case VAR_INT2DECIMALS:
        case VAR_INT3DECIMALS:
        case VAR_INT4DECIMALS:
            *(int *)var->ptr = lrintf((float)value.float_value * n_pow(10,var->type - 10));
            break;
    }
}



static void cliSet(char *cmdline)
{
    uint32_t i;
    uint32_t len;
    const clivalue_t *val;
    float temp;
    char *eqptr = NULL;
    int32_t value = 0;
    float valuef = 0;
	char buffer_temp[64];

    len = strlen(cmdline);

    if (len == 0 || (len == 1 && cmdline[0] == '*')) {
        cliPrint("Current settings: \r\n");
        for (i = 0; i < VALUE_COUNT; i++) {
            val = &valueTable[i];
            sprintf(buffer_temp, "%s = ", valueTable[i].name);
			cliPrint(buffer_temp);
            cliPrintVar(val, len); // when len is 1 (when * is passed as argument), it will print min/max values as well, for gui
            cliPrint("\r\n");
        }
    } else if ((eqptr = strstr(cmdline, "=")) != NULL) {
        // has equal, set var
        eqptr++;
        len--;
        value = atoi(eqptr);
        valuef = _atof(eqptr);
        for (i = 0; i < VALUE_COUNT; i++) {
            val = &valueTable[i];
            if (strncasecmp(cmdline, valueTable[i].name, strlen(valueTable[i].name)) == 0) {
                if (valuef >= (float)valueTable[i].min && valuef <= (float)valueTable[i].max) { // here we compare the float value since... it should work, RIGHT?
                    int_float_value_t tmp;
                    if (valueTable[i].type == VAR_FLOAT || ((valueTable[i].type >= VAR_INT1DECIMALS) && (valueTable[i].type <= VAR_INT4DECIMALS)))
                        tmp.float_value = valuef;
                    else
                        tmp.int_value = value;
                    cliSetVar(val, tmp);
                    temp = *(int *)val->ptr;
                    temp++;
                    sprintf(buffer_temp, "%s set to ", valueTable[i].name);
					cliPrint(buffer_temp);
                    cliPrintVar(val, 0);
                } else {
                    cliPrint("ERR: Value assignment out of range\r\n");
                }
                return;
            }
        }
        cliPrint("ERR: Unknown variable name\r\n");
    } else {
        // no equals, check for matching variables.
        for (i = 0; i < VALUE_COUNT; i++) {
            if (strstr(valueTable[i].name, cmdline)) {
                val = &valueTable[i];
                sprintf(buffer_temp, "%s = ", valueTable[i].name);
				cliPrint(buffer_temp);
                cliPrintVar(val, 0);
                cliPrint("\r\n");
            }
        }
    }
}

static void cliSetPeltier(char *cmdline)
{
    uint32_t len;
    char buffer_temp[64];
    int32_t value = 0;
    float valuef = 0;
    char *eqptr = NULL;
    
    len = strlen(cmdline);
    
    if(len == 0)
    {
	cliPrint("No value entered\r\n");  
    }
    else
    {
       value = atoi(cmdline);
       valuef = atof(cmdline);
       if(value < 5000 && value > -5000) {
        pid1.write(value);
        sprintf(buffer_temp, "Value written: %d\r\n", value);
        cliPrint(buffer_temp);
       }
    }
}

static void cliStatus(char *cmdline)
{
	char buf[8];
	char buffer_temp[64];
	cliPrint("Temperature: ");
	cliPrint(ftoa(Temperature, buf));
    cliPrint("\r\nSetpoint: ");
    cliPrint(ftoa((float)setpoint/100.0f,buf));
	cliPrint("\r\nFaults: ");
	sprintf(buffer_temp, "%d\r\n",(unsigned int)eventcounter);
	cliPrint(buffer_temp);
    sprintf(buffer_temp, "I-term: %d\r\n",(int)pid1.Iterm);
    cliPrint(buffer_temp);
    sprintf(buffer_temp, "windup: %d\r\n",(int)pid1.windup);
    cliPrint(buffer_temp);
    sprintf(buffer_temp, "DAC Offset: %d",(int)dac_offset);
    cliPrint(buffer_temp);
}

void cliProcess(void)
{
	int count, i;
	uint8_t buffer[64];
	
    if (!cliMode) {
        cliMode = 1;
        cliPrint("\r\nEntering CLI Mode, type 'exit' to return, or 'help'\r\n");
        cliPrompt();
    }
	
	count = USBUART_1_GetCount();
	if(count)
	USBUART_1_GetAll(buffer);
	else return;
		
	for(i=0; i<count;i++)
	{	
        uint8_t c = buffer[i];
        if (c == '\t' || c == '?') {
            // do tab completion
            const clicmd_t *cmd, *pstart = NULL, *pend = NULL;
            int i = bufferIndex;
            for (cmd = cmdTable; cmd < cmdTable + CMD_COUNT; cmd++) {
                if (bufferIndex && (strncasecmp(cliBuffer, cmd->name, bufferIndex) != 0))
                    continue;
                if (!pstart)
                    pstart = cmd;
                pend = cmd;
            }
            if (pstart) {    /* Buffer matches one or more commands */
                for (; ; bufferIndex++) {
                    if (pstart->name[bufferIndex] != pend->name[bufferIndex])
                        break;
                    if (!pstart->name[bufferIndex] && bufferIndex < sizeof(cliBuffer) - 2) {
                        /* Unambiguous -- append a space */
                        cliBuffer[bufferIndex++] = ' ';
                        cliBuffer[bufferIndex] = '\0';
                        break;
                    }
                    cliBuffer[bufferIndex] = pstart->name[bufferIndex];
                }
            }
            if (!bufferIndex || pstart != pend) {
                /* Print list of ambiguous matches */
                cliPrint("\r\033[K");
                for (cmd = pstart; cmd <= pend; cmd++) {
                    cliPrint(cmd->name);
                    cliWrite('\t');
                }
                cliPrompt();
                i = 0;    /* Redraw prompt */
            }
            for (; i < bufferIndex; i++)
                cliWrite(cliBuffer[i]);
        } else if (!bufferIndex && c == 4) {
            cliExit(cliBuffer);
            return;
        } else if (c == 12) {
            // clear screen
            cliPrint("\033[2J\033[1;1H");
            cliPrompt();
        } else if (bufferIndex && (c == '\n' || c == '\r')) {
            // enter pressed
            clicmd_t *cmd = NULL;
            clicmd_t target;
            cliPrint("\r\n");
            cliBuffer[bufferIndex] = 0; // null terminate

            target.name = cliBuffer;
            target.param = NULL;

            cmd = bsearch(&target, cmdTable, CMD_COUNT, sizeof cmdTable[0], cliCompare);
            if (cmd)
                cmd->func(cliBuffer + strlen(cmd->name) + 1);
            else
                cliPrint("ERR: Unknown command, try 'help'");

            memset(cliBuffer, 0, sizeof(cliBuffer));
            bufferIndex = 0;

            // 'exit' will reset this flag, so we don't need to print prompt again
            if (!cliMode)
                return;
            cliPrompt();
        } else if (c == 127) {
            // backspace
            if (bufferIndex) {
                cliBuffer[--bufferIndex] = 0;
                cliPrint("\010 \010");
            }
        } else if (bufferIndex < sizeof(cliBuffer) && c >= 32 && c <= 126) {
            if (!bufferIndex && c == 32)
				continue;
            cliBuffer[bufferIndex++] = c;
            cliWrite(c);
        }
	}
}
