/*******************************************************************************
* File Name: seed_diode.h  
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

#if !defined(CY_PINS_seed_diode_H) /* Pins seed_diode_H */
#define CY_PINS_seed_diode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "seed_diode_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 seed_diode__PORT == 15 && ((seed_diode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    seed_diode_Write(uint8 value);
void    seed_diode_SetDriveMode(uint8 mode);
uint8   seed_diode_ReadDataReg(void);
uint8   seed_diode_Read(void);
void    seed_diode_SetInterruptMode(uint16 position, uint16 mode);
uint8   seed_diode_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the seed_diode_SetDriveMode() function.
     *  @{
     */
        #define seed_diode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define seed_diode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define seed_diode_DM_RES_UP          PIN_DM_RES_UP
        #define seed_diode_DM_RES_DWN         PIN_DM_RES_DWN
        #define seed_diode_DM_OD_LO           PIN_DM_OD_LO
        #define seed_diode_DM_OD_HI           PIN_DM_OD_HI
        #define seed_diode_DM_STRONG          PIN_DM_STRONG
        #define seed_diode_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define seed_diode_MASK               seed_diode__MASK
#define seed_diode_SHIFT              seed_diode__SHIFT
#define seed_diode_WIDTH              1u

/* Interrupt constants */
#if defined(seed_diode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in seed_diode_SetInterruptMode() function.
     *  @{
     */
        #define seed_diode_INTR_NONE      (uint16)(0x0000u)
        #define seed_diode_INTR_RISING    (uint16)(0x0001u)
        #define seed_diode_INTR_FALLING   (uint16)(0x0002u)
        #define seed_diode_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define seed_diode_INTR_MASK      (0x01u) 
#endif /* (seed_diode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define seed_diode_PS                     (* (reg8 *) seed_diode__PS)
/* Data Register */
#define seed_diode_DR                     (* (reg8 *) seed_diode__DR)
/* Port Number */
#define seed_diode_PRT_NUM                (* (reg8 *) seed_diode__PRT) 
/* Connect to Analog Globals */                                                  
#define seed_diode_AG                     (* (reg8 *) seed_diode__AG)                       
/* Analog MUX bux enable */
#define seed_diode_AMUX                   (* (reg8 *) seed_diode__AMUX) 
/* Bidirectional Enable */                                                        
#define seed_diode_BIE                    (* (reg8 *) seed_diode__BIE)
/* Bit-mask for Aliased Register Access */
#define seed_diode_BIT_MASK               (* (reg8 *) seed_diode__BIT_MASK)
/* Bypass Enable */
#define seed_diode_BYP                    (* (reg8 *) seed_diode__BYP)
/* Port wide control signals */                                                   
#define seed_diode_CTL                    (* (reg8 *) seed_diode__CTL)
/* Drive Modes */
#define seed_diode_DM0                    (* (reg8 *) seed_diode__DM0) 
#define seed_diode_DM1                    (* (reg8 *) seed_diode__DM1)
#define seed_diode_DM2                    (* (reg8 *) seed_diode__DM2) 
/* Input Buffer Disable Override */
#define seed_diode_INP_DIS                (* (reg8 *) seed_diode__INP_DIS)
/* LCD Common or Segment Drive */
#define seed_diode_LCD_COM_SEG            (* (reg8 *) seed_diode__LCD_COM_SEG)
/* Enable Segment LCD */
#define seed_diode_LCD_EN                 (* (reg8 *) seed_diode__LCD_EN)
/* Slew Rate Control */
#define seed_diode_SLW                    (* (reg8 *) seed_diode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define seed_diode_PRTDSI__CAPS_SEL       (* (reg8 *) seed_diode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define seed_diode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) seed_diode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define seed_diode_PRTDSI__OE_SEL0        (* (reg8 *) seed_diode__PRTDSI__OE_SEL0) 
#define seed_diode_PRTDSI__OE_SEL1        (* (reg8 *) seed_diode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define seed_diode_PRTDSI__OUT_SEL0       (* (reg8 *) seed_diode__PRTDSI__OUT_SEL0) 
#define seed_diode_PRTDSI__OUT_SEL1       (* (reg8 *) seed_diode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define seed_diode_PRTDSI__SYNC_OUT       (* (reg8 *) seed_diode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(seed_diode__SIO_CFG)
    #define seed_diode_SIO_HYST_EN        (* (reg8 *) seed_diode__SIO_HYST_EN)
    #define seed_diode_SIO_REG_HIFREQ     (* (reg8 *) seed_diode__SIO_REG_HIFREQ)
    #define seed_diode_SIO_CFG            (* (reg8 *) seed_diode__SIO_CFG)
    #define seed_diode_SIO_DIFF           (* (reg8 *) seed_diode__SIO_DIFF)
#endif /* (seed_diode__SIO_CFG) */

/* Interrupt Registers */
#if defined(seed_diode__INTSTAT)
    #define seed_diode_INTSTAT            (* (reg8 *) seed_diode__INTSTAT)
    #define seed_diode_SNAP               (* (reg8 *) seed_diode__SNAP)
    
	#define seed_diode_0_INTTYPE_REG 		(* (reg8 *) seed_diode__0__INTTYPE)
#endif /* (seed_diode__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_seed_diode_H */


/* [] END OF FILE */
