/*******************************************************************************
* File Name: seed_diode.h  
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

#if !defined(CY_PINS_seed_diode_ALIASES_H) /* Pins seed_diode_ALIASES_H */
#define CY_PINS_seed_diode_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define seed_diode_0			(seed_diode__0__PC)
#define seed_diode_0_INTR	((uint16)((uint16)0x0001u << seed_diode__0__SHIFT))

#define seed_diode_INTR_ALL	 ((uint16)(seed_diode_0_INTR))

#endif /* End Pins seed_diode_ALIASES_H */


/* [] END OF FILE */
