/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "EEPROM_1.h"
#include "pid.h"

// global data to save
extern pid pid1;
extern int setpoint;
extern uint32_t eventcounter;
extern int deltaTms;
extern uint8_t dac_offset;
extern uint16_t current_offset;
extern float photodiode_power_coefficients[3];
extern uint8_t debug;
extern int temp_limit;


typedef union saveDataUnion // union zum umwandeln der Variablen in ein byte array
{
    struct datastructure{
        pid pidx;
        int setPoint; 
        int deltaTms; 
        uint8_t offset; 
        uint16_t currentOffset;
        float photodiode_power_coefficients[3];
        uint8_t debug;
        int temp_limit;
    } structData;
    uint8_t Data[sizeof(struct datastructure)];
} saveDataUnion;

int erase_eeprom(void) // eeprom löschen
{
    unsigned int Index;
    cystatus eraseStatus;
    reg8 * RegPointer;
    
    for(Index = 0u; Index < CY_EEPROM_NUMBER_ARRAYS; Index++)
    {
        eraseStatus = EEPROM_1_EraseSector(Index);
    }
    if(eraseStatus != CYRET_SUCCESS)
        return 0;
    
    RegPointer = (reg8 *)CYDEV_EE_BASE;
    
    for(Index = 0; Index < EEPROM_1_EEPROM_SIZE; Index++)
    {
        if(RegPointer[Index] != 0u)
        {
            return 0;
        }
    }
    return 1;
}

int save_settings(void) // speichern der Variablen
{
    reg8 * RegPointer;
    saveDataUnion globalData;
    unsigned int byteswritten=0;
    unsigned int x,y;
    unsigned int Index;
    
	// Variablen in Zwischenspeicher schreiben
    memcpy(&globalData.structData.pidx,&pid1,sizeof(pid));
    globalData.structData.setPoint = setpoint;
    globalData.structData.deltaTms = deltaTms;
	globalData.structData.offset = dac_offset;
    globalData.structData.currentOffset = current_offset;
    globalData.structData.photodiode_power_coefficients[0] = photodiode_power_coefficients[0];
    globalData.structData.photodiode_power_coefficients[1] = photodiode_power_coefficients[1];
    globalData.structData.photodiode_power_coefficients[2] = photodiode_power_coefficients[2];
    globalData.structData.debug = debug;
    globalData.structData.temp_limit = temp_limit;
    
    // Variablen byteweise in den EEPROM schreiben
    for(x = 0; x <= (sizeof(globalData) / SIZEOF_EEPROM_ROW); x++) 
    {
        for(y=0; y < SIZEOF_EEPROM_ROW; y++)
        {
            EEPROM_1_ByteWrite(globalData.Data[byteswritten], x, y);
            byteswritten++;
            if(byteswritten >= sizeof(globalData))
                break;
        }
    }
    
	// die geschriebenen Daten überprüfen
    RegPointer = (reg8 *) CYDEV_EE_BASE;
    for(Index = 0; Index < sizeof(globalData); Index++)
    {
        if(globalData.Data[Index] != RegPointer[Index])
            return 0;
    }
    
    return 1;   
}

void read_settings(void)
{
    reg8 * RegPointer;
    saveDataUnion globalData;
    unsigned int Index;
    
	// EEPROM byteweise lesen
    RegPointer = (reg8 *) CYDEV_EE_BASE;
    for(Index = 0; Index < sizeof(globalData); Index++)
    {
        globalData.Data[Index] = RegPointer[Index];
    }
	
	// globale Variablen setzen 
    memcpy(&pid1, &globalData.structData.pidx, sizeof(pid));
    setpoint = globalData.structData.setPoint;  
    deltaTms = globalData.structData.deltaTms;
	dac_offset = globalData.structData.offset;
    photodiode_power_coefficients[0] = globalData.structData.photodiode_power_coefficients[0];
    photodiode_power_coefficients[1] = globalData.structData.photodiode_power_coefficients[1];
    photodiode_power_coefficients[2] = globalData.structData.photodiode_power_coefficients[2];
    debug = globalData.structData.debug;
    temp_limit = globalData.structData.temp_limit;
}

/* [] END OF FILE */