/*******************************************************************************
* File Name: Control_RS_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Control_RS.h"

/* Check for removal by optimization */
#if !defined(Control_RS_Sync_ctrl_reg__REMOVED)

static Control_RS_BACKUP_STRUCT  Control_RS_backup = {0u};

    
/*******************************************************************************
* Function Name: Control_RS_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_RS_SaveConfig(void) 
{
    Control_RS_backup.controlState = Control_RS_Control;
}


/*******************************************************************************
* Function Name: Control_RS_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Control_RS_RestoreConfig(void) 
{
     Control_RS_Control = Control_RS_backup.controlState;
}


/*******************************************************************************
* Function Name: Control_RS_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_RS_Sleep(void) 
{
    Control_RS_SaveConfig();
}


/*******************************************************************************
* Function Name: Control_RS_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_RS_Wakeup(void)  
{
    Control_RS_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
