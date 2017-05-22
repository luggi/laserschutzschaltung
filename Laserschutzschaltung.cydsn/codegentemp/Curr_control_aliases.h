/*******************************************************************************
* File Name: Curr_control.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Curr_control_ALIASES_H) /* Pins Curr_control_ALIASES_H */
#define CY_PINS_Curr_control_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Curr_control_0			(Curr_control__0__PC)
#define Curr_control_0_INTR	((uint16)((uint16)0x0001u << Curr_control__0__SHIFT))

#define Curr_control_INTR_ALL	 ((uint16)(Curr_control_0_INTR))

#endif /* End Pins Curr_control_ALIASES_H */


/* [] END OF FILE */
