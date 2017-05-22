/*******************************************************************************
* File Name: Seed_ref.h  
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

#if !defined(CY_PINS_Seed_ref_H) /* Pins Seed_ref_H */
#define CY_PINS_Seed_ref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Seed_ref_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Seed_ref__PORT == 15 && ((Seed_ref__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Seed_ref_Write(uint8 value);
void    Seed_ref_SetDriveMode(uint8 mode);
uint8   Seed_ref_ReadDataReg(void);
uint8   Seed_ref_Read(void);
void    Seed_ref_SetInterruptMode(uint16 position, uint16 mode);
uint8   Seed_ref_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Seed_ref_SetDriveMode() function.
     *  @{
     */
        #define Seed_ref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Seed_ref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Seed_ref_DM_RES_UP          PIN_DM_RES_UP
        #define Seed_ref_DM_RES_DWN         PIN_DM_RES_DWN
        #define Seed_ref_DM_OD_LO           PIN_DM_OD_LO
        #define Seed_ref_DM_OD_HI           PIN_DM_OD_HI
        #define Seed_ref_DM_STRONG          PIN_DM_STRONG
        #define Seed_ref_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Seed_ref_MASK               Seed_ref__MASK
#define Seed_ref_SHIFT              Seed_ref__SHIFT
#define Seed_ref_WIDTH              1u

/* Interrupt constants */
#if defined(Seed_ref__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Seed_ref_SetInterruptMode() function.
     *  @{
     */
        #define Seed_ref_INTR_NONE      (uint16)(0x0000u)
        #define Seed_ref_INTR_RISING    (uint16)(0x0001u)
        #define Seed_ref_INTR_FALLING   (uint16)(0x0002u)
        #define Seed_ref_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Seed_ref_INTR_MASK      (0x01u) 
#endif /* (Seed_ref__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Seed_ref_PS                     (* (reg8 *) Seed_ref__PS)
/* Data Register */
#define Seed_ref_DR                     (* (reg8 *) Seed_ref__DR)
/* Port Number */
#define Seed_ref_PRT_NUM                (* (reg8 *) Seed_ref__PRT) 
/* Connect to Analog Globals */                                                  
#define Seed_ref_AG                     (* (reg8 *) Seed_ref__AG)                       
/* Analog MUX bux enable */
#define Seed_ref_AMUX                   (* (reg8 *) Seed_ref__AMUX) 
/* Bidirectional Enable */                                                        
#define Seed_ref_BIE                    (* (reg8 *) Seed_ref__BIE)
/* Bit-mask for Aliased Register Access */
#define Seed_ref_BIT_MASK               (* (reg8 *) Seed_ref__BIT_MASK)
/* Bypass Enable */
#define Seed_ref_BYP                    (* (reg8 *) Seed_ref__BYP)
/* Port wide control signals */                                                   
#define Seed_ref_CTL                    (* (reg8 *) Seed_ref__CTL)
/* Drive Modes */
#define Seed_ref_DM0                    (* (reg8 *) Seed_ref__DM0) 
#define Seed_ref_DM1                    (* (reg8 *) Seed_ref__DM1)
#define Seed_ref_DM2                    (* (reg8 *) Seed_ref__DM2) 
/* Input Buffer Disable Override */
#define Seed_ref_INP_DIS                (* (reg8 *) Seed_ref__INP_DIS)
/* LCD Common or Segment Drive */
#define Seed_ref_LCD_COM_SEG            (* (reg8 *) Seed_ref__LCD_COM_SEG)
/* Enable Segment LCD */
#define Seed_ref_LCD_EN                 (* (reg8 *) Seed_ref__LCD_EN)
/* Slew Rate Control */
#define Seed_ref_SLW                    (* (reg8 *) Seed_ref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Seed_ref_PRTDSI__CAPS_SEL       (* (reg8 *) Seed_ref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Seed_ref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Seed_ref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Seed_ref_PRTDSI__OE_SEL0        (* (reg8 *) Seed_ref__PRTDSI__OE_SEL0) 
#define Seed_ref_PRTDSI__OE_SEL1        (* (reg8 *) Seed_ref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Seed_ref_PRTDSI__OUT_SEL0       (* (reg8 *) Seed_ref__PRTDSI__OUT_SEL0) 
#define Seed_ref_PRTDSI__OUT_SEL1       (* (reg8 *) Seed_ref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Seed_ref_PRTDSI__SYNC_OUT       (* (reg8 *) Seed_ref__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Seed_ref__SIO_CFG)
    #define Seed_ref_SIO_HYST_EN        (* (reg8 *) Seed_ref__SIO_HYST_EN)
    #define Seed_ref_SIO_REG_HIFREQ     (* (reg8 *) Seed_ref__SIO_REG_HIFREQ)
    #define Seed_ref_SIO_CFG            (* (reg8 *) Seed_ref__SIO_CFG)
    #define Seed_ref_SIO_DIFF           (* (reg8 *) Seed_ref__SIO_DIFF)
#endif /* (Seed_ref__SIO_CFG) */

/* Interrupt Registers */
#if defined(Seed_ref__INTSTAT)
    #define Seed_ref_INTSTAT            (* (reg8 *) Seed_ref__INTSTAT)
    #define Seed_ref_SNAP               (* (reg8 *) Seed_ref__SNAP)
    
	#define Seed_ref_0_INTTYPE_REG 		(* (reg8 *) Seed_ref__0__INTTYPE)
#endif /* (Seed_ref__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Seed_ref_H */


/* [] END OF FILE */
