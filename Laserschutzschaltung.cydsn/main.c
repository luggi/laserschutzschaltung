/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <device.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <VDAC8.h>
#include <math.h>
#include "pid.h"
#include "cli.h"
#include "eeprom.h"

#define REQUEST_PER_BURST        (1u)
#define BYTES_PER_BURST          (1u)
#define UPPER_SRC_ADDRESS        CYDEV_PERIPH_BASE
#define UPPER_DEST_ADDRESS       CYDEV_PERIPH_BASE

void DMA_Config(void);
float calc_temperature(int32_t adc_input);
float calc_temperature_ntc10k(int32_t input);
float calc_voltage(int32_t adc_input);
float calc_diode_power(int16_t adc_input, float power_coeff, int bits);
void pid1_write(int32_t output);
void USB_init(void);
void peripheral_init(void);

uint8_t debug = 0;
int deltaTms = 1000;
int temp_limit=5000;
uint32_t eventcounter = 0;
uint8_t filterStatus = 0;
uint8_t cliMode = 0;
uint8_t faultStatus = 0;
uint8_t pidStatus = 0;
uint16_t filter_read = 0;
uint8_t dac_offset = 0;
uint16_t pd_input = 0;
uint16_t current_offset = 4095;
float photodiode_power_coefficients[3] = {1.0f, 1.0f, 1.0f};
pid pid1;
int pidoutput;
int setpoint = 3800;
float Temperature;
float current_output_coeff = 10000.0f / 45.0f;
float set_current_psu = 0.0f;
uint8_t auto_current=1;
float slope = 0.5f; // ampere per second to increase/decrease the power supply
uint8_t faultreason = 0;

enum { 
    PSU_DECREASING,
    PSU_INCREASING,
    PSU_OFF,
    PSU_SET_CURRENT
};

enum {
    ERR_PERSIST = 1,
    OR_ERR = 2,
    SEED_ERR1 = 4,
    SEED_ERR2 = 8,
    OSC_ERR = 16
};

enum {
    RESET_ERR = 2,
    TEMP_ERR = 1
};

enum {
    OSCILLATION_PD = 0, 
    PUMP_PD = 1, 
    SEED_PD = 2
};

/*******************************************************************************
* Interrupt
********************************************************************************
* Interrupt generated on Filter sample-ready. Interrupt handle:filterVDAC
*
* Summary:
*  The interrupt performs following functions:
*   1: Reads the left-justified register for Filter Channel A
*   2: Converts it into an unsigned value
*   3: Writes this value to VDAC
*
*******************************************************************************/
//CY_ISR_PROTO(filterVDAC) __attribute__ ((section(".data")));
CY_ISR(filterVDAC) 
{
    int filter_read1;
    int filter_read2;
    
    
	filter_read = Filter_HOLDAM_REG;
    
    
    
	filter_read1 = filter_read + dac_offset;
    if(filter_read > dac_offset)
        filter_read2 = filter_read - dac_offset;
    else 
        filter_read2 = 0;
    
    
	VDAC8_Data = filter_read1 & 0xff;
    VDAC8_1_Data = filter_read2 & 0xff;
    
	filterStatus = 1;
}

/*******************************************************************************
* Interrupt
********************************************************************************
* Interrupt generated on Filter sample-ready. Interrupt handle:filterVDAC
*
* Summary:
*  The interrupt performs following functions:
*   1: Sets Status flag 1 when Fault is triggered
*
*******************************************************************************/
CY_ISR(faultISR)
{
	faultStatus=1;
    faultreason = Fault_Reg_Read();
	eventcounter++; //unkommentieren für sehr schnelles erkennen von fehlern
}

/*******************************************************************************
* Interrupt
********************************************************************************
* Interrupt generated on timer overflow(specified for pid sample time). Interrupt handle:pidISR
*
* Summary:
*  The interrupt performs following functions:
*   1: Sets Status flag 1 when Timerinterrupt is triggered
*
*******************************************************************************/
CY_ISR(pidISR)
{
	Counter_1_ReadStatusRegister();
	pidStatus=1;
}
void value_to_string00_00(char* buffer, float value){ // prints format 00.00
            
    if(value < 0)
        value = 0;
			buffer[0] = ((int)value / 10) % 10 + '0';
			buffer[1] = ((int)value  % 10) + '0';
			buffer[2] = '.';
			buffer[3] = (int)(value * 10) % 10 + '0';
			buffer[4] = (int)(value * 100) % 10 + '0';
			buffer[5] = '\0';
}

void value_to_string1(char* buffer, float value){ // prints format 000.00
            
    if(value < 0)
        value = 0;
            buffer[0] = ((int)value / 100) % 10 + '0';
			buffer[1] = ((int)value / 10) % 10 + '0';
			buffer[2] = ((int)value  % 10) + '0';
			buffer[3] = '.';
			buffer[4] = (int)(value * 10) % 10 + '0';
			buffer[5] = (int)(value * 100) % 10 + '0';
			buffer[6] = '\0';
}

void value_to_string2(char* buffer, float value){ // prints format 0.00
            
    if(value<0)
        value = 0;
			buffer[0] = ((int)value  % 10) + '0';
			buffer[1] = '.';
			buffer[2] = (int)(value * 10) % 10 + '0';
			buffer[3] = (int)(value * 100) % 10 + '0';
			buffer[4] = '\0';
}

void value_to_string3(char* buffer, float value){ // prints format 0000.00
            
    if(value < 0)
        value = 0;
            buffer[0] = ((int)value / 1000) % 10 + '0';
            buffer[1] = ((int)value / 100) % 10 + '0';
			buffer[2] = ((int)value / 10) % 10 + '0';
			buffer[3] = ((int)value  % 10) + '0';
			buffer[4] = '.';
			buffer[5] = (int)(value * 10) % 10 + '0';
			buffer[6] = (int)(value * 100) % 10 + '0';
			buffer[7] = '\0';
}

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1: Enables global interrupts
*   2: Start all components on the schematic
*   3: Calls a function to configure DMA

* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main(void)
{
	char buffer[40];
	uint8_t filterRead;
    uint8_t temp;
    uint8_t status;
	int counter = 0;
	int32_t ADCtemp_read;
	uint8_t testoutput=0;
    float power_diode[3];
    static uint8_t psu_state;
    static float set_current_psu_actual = 0.0f;
	
	/* Enable all components used in the Schematic */
	peripheral_init();
    
    /* Enable Global Interrupts */
    CYGlobalIntEnable;
	

    for(;;)
    {
        status = Fault_Reg_Read();
		/*if(filterStatus)
		{
			LCD_Position(1u, 0u);
			
			//filterRead = Filter_Read8(Filter_CHANNEL_A);
			filterRead = filter_read;
			
			if(filterRead < 10) {
			LCD_PrintString("  ");			
			} else if(filterRead < 100) {
			LCD_PrintString(" ");			
			} else {}
			
			sprintf(buffer, "%i", filterRead);
			LCD_PrintString(buffer);
			filterStatus=0;
		}*/
		
		if(faultStatus) {
            set_current_psu_actual = 0.0f;
            psu_state = PSU_OFF;
			LCD_Position(0u, 0u);
			LCD_PrintString("ERROR");
            PWM_1_Start();

            
			faultStatus=0;
			
		} else if(!(status & (ERR_PERSIST|OR_ERR))) {
            PWM_1_Stop();
			LCD_Position(0u, 0u);
			LCD_PrintString("OK   ");
		}
		
		if(pidStatus) { // executes every x milliseconds(deltaTms), driven by a timer interrupt
			
            uint8_t fault = (status & 0x01);
            power_diode[OSCILLATION_PD] = calc_diode_power(ADC_SAR_Seq_2_GetResult16(OSCILLATION_PD) ,photodiode_power_coefficients[0],0x0fff); // oscillation pd
            power_diode[PUMP_PD] = calc_diode_power(ADC_SAR_Seq_2_GetResult16(PUMP_PD) ,photodiode_power_coefficients[1],0x0fff); // pump pd
            power_diode[SEED_PD] = calc_diode_power(ADC_SAR_Seq_2_GetResult16(SEED_PD) ,photodiode_power_coefficients[2],0x0fff); // seed pd
            
            set_current_psu = calc_diode_power(ADC_SAR_Seq_2_GetResult16(3) ,9.0f,0x0fff); // current
            
            LCD_Position(1u, 0u);
            value_to_string2(buffer,power_diode[OSCILLATION_PD]);
			LCD_PrintString(buffer);
            
            value_to_string00_00(buffer,set_current_psu);
            LCD_Position(0u, 11u);
            LCD_PrintString(buffer);
            
            value_to_string00_00(buffer,power_diode[SEED_PD]);
            LCD_Position(1u, 11u);
            LCD_PrintString(buffer);
            
            
            if(auto_current) {
                switch(psu_state)
                {
                    case PSU_OFF:
                        set_current_psu_actual = 0.0f;

                        if(!fault && (set_current_psu > 0.0f)) {
                            psu_state = PSU_INCREASING;
                        }
                    break;
                        
                    case PSU_INCREASING:
                        if(set_current_psu_actual < set_current_psu)
                            set_current_psu_actual += slope * (float)deltaTms/1000.0f;
                        else {
                            psu_state = PSU_SET_CURRENT;
                            set_current_psu_actual = set_current_psu;
                        }
                    break;
                        
                    case PSU_DECREASING:
                        if(set_current_psu_actual > set_current_psu)
                            set_current_psu_actual -= slope * (float)deltaTms/1000.0f;
                        else {
                            psu_state = PSU_SET_CURRENT;
                            set_current_psu_actual = set_current_psu;
                        }
                    break;
                            
                    case PSU_SET_CURRENT:
                            if(set_current_psu > set_current_psu_actual)
                                psu_state = PSU_INCREASING;
                            else if (set_current_psu_actual > set_current_psu)
                                psu_state = PSU_DECREASING;
                            if(set_current_psu == 0.0f)
                                psu_state = PSU_OFF;
                    break;
                            
                    default: 
                        set_current_psu_actual = 0.0f;
                }
            }
            
            uint32_t temp = set_current_psu_actual*current_output_coeff;
            uint32_t output_current = (temp > 10000) ? 10000 : temp;
            PWM_2_WriteCompare(output_current);            
            
            if(!SW2_Read())
                eventcounter = 0;
            
            
                
			Temperature = calc_temperature_ntc10k(ADCtemp_read / 64); //only for 10k-10k ntc voltage divider input
			
            if((Temperature*100.0f) > temp_limit)
                Control_RS_Write(TEMP_ERR); // set error state at too high temperature
            else
                Control_RS_Write(0x00);
			
			// PID Routine aufrufen
			pid_calc(&pid1, setpoint,(int32_t)(Temperature*100),100);
			
			LCD_Position(0u,5u); // manuell Integer to String konvertieren
            value_to_string00_00(buffer, Temperature);
			LCD_PrintString(buffer);
            
            if(debug)
            {
                if(USBUART_1_CDCIsReady()){
                    char buffer_large[200];
                    USBUART_1_SetComPort(1);
                    sprintf(buffer_large, "%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i\n\r", setpoint, (int)(Temperature*100), (int)(power_diode[0]*100), (int)(power_diode[1]*100), status, eventcounter, filterRead, pid1.Iterm, pidoutput, (int)(set_current_psu*100), (int)(set_current_psu_actual*100));
                    USBUART_1_PutString(buffer_large);
                    USBUART_1_SetComPort(0);
                }
			}
            
            LCD_Position(1u,5u);
            value_to_string00_00(buffer, (float)setpoint/100);
			LCD_PrintString(buffer);
            

                
			pidStatus=0;
			if(eventcounter == 0) {
                if(!(status & OR_ERR)) {
    				faultStatus = 0;
    				Control_RS_Write(RESET_ERR);
    				CyDelayUs(10);
    				Control_RS_Write(0x00);
                }
			}
		}
		
		// USB-CDC Communication
        temp = VUSB_Read();
        if(temp) {
            //temp = '0' + temp;
            //LCD_Position(1u,3u);
            //LCD_PutChar(temp);
            
            if(USBUART_1_initVar == 0u)
                USB_init();
            cliProcess();
        }  
        else {
            if(USBUART_1_initVar)
                USBUART_1_Stop();
                
            //LCD_Position(1u,3u);
            //temp = '0' + temp;
            //LCD_PutChar(temp);
		}
		
		//pd_input = ADC_SAR_2_GetResult8(); // Offset vom potentiometer auf dem Eval board lesen
        
		//Temperatur ADC einlesen und filtern durch Mittelwertbildung
        ADCtemp_read -= ADCtemp_read/64;
        ADCtemp_read += ADC_DelSig_1_GetResult32();
        
        
		
    }
    return 0;
} /* End of main */

void USB_init(void) 
{
    /* Start USBFS Operation with 5V operation */
	USBUART_1_Start(0u, USBUART_1_5V_OPERATION);
    //USBUART_1_Start(1u, USBUART_1_5V_OPERATION);
	while(!USBUART_1_GetConfiguration()){};
    
	USBUART_1_CDC_Init();
    USBUART_1_SetPowerStatus(USBUART_1_DEVICE_STATUS_SELF_POWERED);
    
    
}


/*******************************************************************************
* Function Name: DMA_Config
********************************************************************************
*
* Summary:
*  Initializes and sets up DMA for use (generated by DMA Wizard)
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DMA_Config(void)
{
    /* Declare variable to hold the handle for DMA channel */
    uint8 channelHandle;

    /* Declare DMA Transaction Descriptor for memory transfer into
     * Filter Channel.
     */
    uint8 tdChanA;

    /* Configure the DMA to Transfer the data in 1 burst with individual trigger
     * for each burst.
     */
    channelHandle = DMA_DmaInitialize(BYTES_PER_BURST, REQUEST_PER_BURST,
                                        HI16(UPPER_SRC_ADDRESS), HI16(UPPER_DEST_ADDRESS));

    /* This function allocates a TD for use with an initialized DMA channel */
    tdChanA = CyDmaTdAllocate();

    /* Configure the tdChanA to transfer 1 byte with no next TD */
    CyDmaTdSetConfiguration(tdChanA, 1u, DMA_INVALID_TD, 0u);

    /* Set the source address as ADC_DelSig and the destination as
     * Filter Channel A.
     */
    CyDmaTdSetAddress(tdChanA, LO16((uint32)ADC_SAR_1_SAR_WRK0_PTR), LO16((uint32)Filter_STAGEAM_PTR));

    /* Set tdChanA to be the initial TD associated with channelHandle */
    CyDmaChSetInitialTd(channelHandle, tdChanA);

    /* Enable the DMA channel represented by channelHandle and preserve the TD */
    CyDmaChEnable(channelHandle, 1u);
}

/*******************************************************************************
* Function Name: pid1_write
********************************************************************************
*
* Summary:
*  writes pid output to a peripheral needs to be passed to pid struct
*
* Parameters:
*  int32_t output given by the pid library
*
* Return:
*  None.
*
*******************************************************************************/
void pid1_write(int32_t output) //incomplete
{
	uint8_t temp1, temp2;
	
    pidoutput = output;
    
    output += current_offset;
    
	if(output > 8191)
		output = 8191;
	else if(output < 0)
		output = 0;
	
	temp1 = output >> 5;
	temp2 = (output & 0x001F) << 1;
	
	IDAC8_1_SetValue(temp1);
	IDAC8_2_SetValue(temp2);
}

/*******************************************************************************
* Function Name: calc_temperature_ntc10k
********************************************************************************
*
* Summary:
*  calculates the temperature from adc for a 10k ntc
*
* Parameters:
*  int32_t adc input from ntc
*
* Return:
*  None.
*
*******************************************************************************/

#define PULLUP_RESISTANCE 11960

float calc_temperature_ntc10k(int32_t adc_input)
{
    
    if(adc_input > 60000 || adc_input < 5000) // sanity check return high temperature in case of failure
        return 500.0f;
    
	float A1,B1,C1,D1;
	float Temp,Res;

	A1 = 3.354016e-3f;
	B1 = 2.569850e-4f;
	C1 = 2.62013e-6f;
	D1 = 6.38309e-8f;
	
	Res = (float) PULLUP_RESISTANCE / (float)(((float)0xffff / (float)adc_input) - 1); 
	
	Temp = 1.0f / (A1 + B1 * logf(Res/10000.0f) + C1 * logf(Res/10000.0f) * logf(Res/10000.0f) + D1 * logf(Res/10000.0f) * logf(Res/10000.0f) * logf(Res/10000.0f));  
	Temp -= 273.15f;
	return Temp;
}

/*******************************************************************************
* Function Name: calc_temperature_ntc10k
********************************************************************************
*
* Summary:
*  calculates the temperature from adc input
*
* Parameters:
*  int32_t adc input from diode via opamp circuit
*
* Return:
*  None.
*
*******************************************************************************/


float calc_voltage(int32_t adc_input)
{
	float Voltage;

	Voltage = ((float)adc_input * 5.0f) / (float)0xffff; // 5V voltage range
		
	return Voltage;
}

float calc_diode_power(int16_t adc_input, float power_coeff, int bits)
{
    float voltage = ((float)adc_input / (float)bits) * 5.0f; // assuming bits-bit ADC and 5V reference
    
    return voltage * power_coeff;
}


void peripheral_init(void)
{
	/* Start all components used on schematic */
    //ADC_DelSig_IRQ_Start();
    isr_StartEx(filterVDAC);
    //ADC_DelSig_Start();
    //ADC_DelSig_StartConvert();
	ADC_SAR_1_Start();
	ADC_SAR_Seq_2_Start();
	ADC_DelSig_1_Start();
    
	ADC_SAR_1_StartConvert();
	ADC_DelSig_1_StartConvert();
    ADC_SAR_Seq_2_StartConvert();
	Fault_isr_StartEx(faultISR);
	Fault_isr_SetPriority(0u);
	PID_isr_StartEx(pidISR);
	PID_isr_SetPriority(7u);
	Comp_1_Start();
	Comp_2_Start();
	Comp_3_Start();
    VDAC8_Start();
	IDAC8_1_Start();
	IDAC8_2_Start();
	PGA_1_Start();
	PGA_2_Start();
    PGA_1_SetGain(PGA_1_GAIN_02);
    Filter_Start();
	Filter_SetCoherency(Filter_CHANNEL_A,Filter_KEY_MID);
	LCD_Start();
	Counter_1_Start();
    PWM_1_Start();
    PWM_2_Start();
	
    /* User-implemented function to set-up DMA */
    DMA_Config();
    
	/* initialize pid controller */
    EEPROM_1_Start();
    read_settings();
    pid_init(&pid1,pid1_write);
    if(deltaTms < 100)		// sanity check
        deltaTms = 100;
    else if (deltaTms > 10000)
        deltaTms = 10000;
    Counter_1_WritePeriod(48*deltaTms);
    
    
}


/* [] END OF FILE */
