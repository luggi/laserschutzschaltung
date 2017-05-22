/*******************************************************************************
* File Name: DAC_Current_Control_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "DAC_Current_Control.h"

static DAC_Current_Control_backupStruct DAC_Current_Control_backup;


/*******************************************************************************
* Function Name: DAC_Current_Control_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void DAC_Current_Control_SaveConfig(void) 
{
    if (!((DAC_Current_Control_CR1 & DAC_Current_Control_SRC_MASK) == DAC_Current_Control_SRC_UDB))
    {
        DAC_Current_Control_backup.data_value = DAC_Current_Control_Data;
    }
}


/*******************************************************************************
* Function Name: DAC_Current_Control_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void DAC_Current_Control_RestoreConfig(void) 
{
    if (!((DAC_Current_Control_CR1 & DAC_Current_Control_SRC_MASK) == DAC_Current_Control_SRC_UDB))
    {
        if((DAC_Current_Control_Strobe & DAC_Current_Control_STRB_MASK) == DAC_Current_Control_STRB_EN)
        {
            DAC_Current_Control_Strobe &= (uint8)(~DAC_Current_Control_STRB_MASK);
            DAC_Current_Control_Data = DAC_Current_Control_backup.data_value;
            DAC_Current_Control_Strobe |= DAC_Current_Control_STRB_EN;
        }
        else
        {
            DAC_Current_Control_Data = DAC_Current_Control_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: DAC_Current_Control_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  DAC_Current_Control_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void DAC_Current_Control_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(DAC_Current_Control_ACT_PWR_EN == (DAC_Current_Control_PWRMGR & DAC_Current_Control_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        DAC_Current_Control_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        DAC_Current_Control_backup.enableState = 0u;
    }
    
    DAC_Current_Control_Stop();
    DAC_Current_Control_SaveConfig();
}


/*******************************************************************************
* Function Name: DAC_Current_Control_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  DAC_Current_Control_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DAC_Current_Control_Wakeup(void) 
{
    DAC_Current_Control_RestoreConfig();
    
    if(DAC_Current_Control_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        DAC_Current_Control_Enable();

        /* Restore the data register */
        DAC_Current_Control_SetValue(DAC_Current_Control_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
