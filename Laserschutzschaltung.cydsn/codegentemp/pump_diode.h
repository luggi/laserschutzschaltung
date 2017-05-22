/*******************************************************************************
* File Name: pump_diode.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pump_diode_H) /* Pins pump_diode_H */
#define CY_PINS_pump_diode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pump_diode_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pump_diode__PORT == 15 && ((pump_diode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pump_diode_Write(uint8 value);
void    pump_diode_SetDriveMode(uint8 mode);
uint8   pump_diode_ReadDataReg(void);
uint8   pump_diode_Read(void);
void    pump_diode_SetInterruptMode(uint16 position, uint16 mode);
uint8   pump_diode_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pump_diode_SetDriveMode() function.
     *  @{
     */
        #define pump_diode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pump_diode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pump_diode_DM_RES_UP          PIN_DM_RES_UP
        #define pump_diode_DM_RES_DWN         PIN_DM_RES_DWN
        #define pump_diode_DM_OD_LO           PIN_DM_OD_LO
        #define pump_diode_DM_OD_HI           PIN_DM_OD_HI
        #define pump_diode_DM_STRONG          PIN_DM_STRONG
        #define pump_diode_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pump_diode_MASK               pump_diode__MASK
#define pump_diode_SHIFT              pump_diode__SHIFT
#define pump_diode_WIDTH              1u

/* Interrupt constants */
#if defined(pump_diode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pump_diode_SetInterruptMode() function.
     *  @{
     */
        #define pump_diode_INTR_NONE      (uint16)(0x0000u)
        #define pump_diode_INTR_RISING    (uint16)(0x0001u)
        #define pump_diode_INTR_FALLING   (uint16)(0x0002u)
        #define pump_diode_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pump_diode_INTR_MASK      (0x01u) 
#endif /* (pump_diode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pump_diode_PS                     (* (reg8 *) pump_diode__PS)
/* Data Register */
#define pump_diode_DR                     (* (reg8 *) pump_diode__DR)
/* Port Number */
#define pump_diode_PRT_NUM                (* (reg8 *) pump_diode__PRT) 
/* Connect to Analog Globals */                                                  
#define pump_diode_AG                     (* (reg8 *) pump_diode__AG)                       
/* Analog MUX bux enable */
#define pump_diode_AMUX                   (* (reg8 *) pump_diode__AMUX) 
/* Bidirectional Enable */                                                        
#define pump_diode_BIE                    (* (reg8 *) pump_diode__BIE)
/* Bit-mask for Aliased Register Access */
#define pump_diode_BIT_MASK               (* (reg8 *) pump_diode__BIT_MASK)
/* Bypass Enable */
#define pump_diode_BYP                    (* (reg8 *) pump_diode__BYP)
/* Port wide control signals */                                                   
#define pump_diode_CTL                    (* (reg8 *) pump_diode__CTL)
/* Drive Modes */
#define pump_diode_DM0                    (* (reg8 *) pump_diode__DM0) 
#define pump_diode_DM1                    (* (reg8 *) pump_diode__DM1)
#define pump_diode_DM2                    (* (reg8 *) pump_diode__DM2) 
/* Input Buffer Disable Override */
#define pump_diode_INP_DIS                (* (reg8 *) pump_diode__INP_DIS)
/* LCD Common or Segment Drive */
#define pump_diode_LCD_COM_SEG            (* (reg8 *) pump_diode__LCD_COM_SEG)
/* Enable Segment LCD */
#define pump_diode_LCD_EN                 (* (reg8 *) pump_diode__LCD_EN)
/* Slew Rate Control */
#define pump_diode_SLW                    (* (reg8 *) pump_diode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pump_diode_PRTDSI__CAPS_SEL       (* (reg8 *) pump_diode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pump_diode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pump_diode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pump_diode_PRTDSI__OE_SEL0        (* (reg8 *) pump_diode__PRTDSI__OE_SEL0) 
#define pump_diode_PRTDSI__OE_SEL1        (* (reg8 *) pump_diode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pump_diode_PRTDSI__OUT_SEL0       (* (reg8 *) pump_diode__PRTDSI__OUT_SEL0) 
#define pump_diode_PRTDSI__OUT_SEL1       (* (reg8 *) pump_diode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pump_diode_PRTDSI__SYNC_OUT       (* (reg8 *) pump_diode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pump_diode__SIO_CFG)
    #define pump_diode_SIO_HYST_EN        (* (reg8 *) pump_diode__SIO_HYST_EN)
    #define pump_diode_SIO_REG_HIFREQ     (* (reg8 *) pump_diode__SIO_REG_HIFREQ)
    #define pump_diode_SIO_CFG            (* (reg8 *) pump_diode__SIO_CFG)
    #define pump_diode_SIO_DIFF           (* (reg8 *) pump_diode__SIO_DIFF)
#endif /* (pump_diode__SIO_CFG) */

/* Interrupt Registers */
#if defined(pump_diode__INTSTAT)
    #define pump_diode_INTSTAT            (* (reg8 *) pump_diode__INTSTAT)
    #define pump_diode_SNAP               (* (reg8 *) pump_diode__SNAP)
    
	#define pump_diode_0_INTTYPE_REG 		(* (reg8 *) pump_diode__0__INTTYPE)
#endif /* (pump_diode__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pump_diode_H */


/* [] END OF FILE */
