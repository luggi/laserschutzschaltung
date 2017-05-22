/*******************************************************************************
* File Name: Diode_Pumpseite.h  
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

#if !defined(CY_PINS_Diode_Pumpseite_H) /* Pins Diode_Pumpseite_H */
#define CY_PINS_Diode_Pumpseite_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Diode_Pumpseite_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Diode_Pumpseite__PORT == 15 && ((Diode_Pumpseite__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Diode_Pumpseite_Write(uint8 value);
void    Diode_Pumpseite_SetDriveMode(uint8 mode);
uint8   Diode_Pumpseite_ReadDataReg(void);
uint8   Diode_Pumpseite_Read(void);
void    Diode_Pumpseite_SetInterruptMode(uint16 position, uint16 mode);
uint8   Diode_Pumpseite_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Diode_Pumpseite_SetDriveMode() function.
     *  @{
     */
        #define Diode_Pumpseite_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Diode_Pumpseite_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Diode_Pumpseite_DM_RES_UP          PIN_DM_RES_UP
        #define Diode_Pumpseite_DM_RES_DWN         PIN_DM_RES_DWN
        #define Diode_Pumpseite_DM_OD_LO           PIN_DM_OD_LO
        #define Diode_Pumpseite_DM_OD_HI           PIN_DM_OD_HI
        #define Diode_Pumpseite_DM_STRONG          PIN_DM_STRONG
        #define Diode_Pumpseite_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Diode_Pumpseite_MASK               Diode_Pumpseite__MASK
#define Diode_Pumpseite_SHIFT              Diode_Pumpseite__SHIFT
#define Diode_Pumpseite_WIDTH              1u

/* Interrupt constants */
#if defined(Diode_Pumpseite__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Diode_Pumpseite_SetInterruptMode() function.
     *  @{
     */
        #define Diode_Pumpseite_INTR_NONE      (uint16)(0x0000u)
        #define Diode_Pumpseite_INTR_RISING    (uint16)(0x0001u)
        #define Diode_Pumpseite_INTR_FALLING   (uint16)(0x0002u)
        #define Diode_Pumpseite_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Diode_Pumpseite_INTR_MASK      (0x01u) 
#endif /* (Diode_Pumpseite__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Diode_Pumpseite_PS                     (* (reg8 *) Diode_Pumpseite__PS)
/* Data Register */
#define Diode_Pumpseite_DR                     (* (reg8 *) Diode_Pumpseite__DR)
/* Port Number */
#define Diode_Pumpseite_PRT_NUM                (* (reg8 *) Diode_Pumpseite__PRT) 
/* Connect to Analog Globals */                                                  
#define Diode_Pumpseite_AG                     (* (reg8 *) Diode_Pumpseite__AG)                       
/* Analog MUX bux enable */
#define Diode_Pumpseite_AMUX                   (* (reg8 *) Diode_Pumpseite__AMUX) 
/* Bidirectional Enable */                                                        
#define Diode_Pumpseite_BIE                    (* (reg8 *) Diode_Pumpseite__BIE)
/* Bit-mask for Aliased Register Access */
#define Diode_Pumpseite_BIT_MASK               (* (reg8 *) Diode_Pumpseite__BIT_MASK)
/* Bypass Enable */
#define Diode_Pumpseite_BYP                    (* (reg8 *) Diode_Pumpseite__BYP)
/* Port wide control signals */                                                   
#define Diode_Pumpseite_CTL                    (* (reg8 *) Diode_Pumpseite__CTL)
/* Drive Modes */
#define Diode_Pumpseite_DM0                    (* (reg8 *) Diode_Pumpseite__DM0) 
#define Diode_Pumpseite_DM1                    (* (reg8 *) Diode_Pumpseite__DM1)
#define Diode_Pumpseite_DM2                    (* (reg8 *) Diode_Pumpseite__DM2) 
/* Input Buffer Disable Override */
#define Diode_Pumpseite_INP_DIS                (* (reg8 *) Diode_Pumpseite__INP_DIS)
/* LCD Common or Segment Drive */
#define Diode_Pumpseite_LCD_COM_SEG            (* (reg8 *) Diode_Pumpseite__LCD_COM_SEG)
/* Enable Segment LCD */
#define Diode_Pumpseite_LCD_EN                 (* (reg8 *) Diode_Pumpseite__LCD_EN)
/* Slew Rate Control */
#define Diode_Pumpseite_SLW                    (* (reg8 *) Diode_Pumpseite__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Diode_Pumpseite_PRTDSI__CAPS_SEL       (* (reg8 *) Diode_Pumpseite__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Diode_Pumpseite_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Diode_Pumpseite__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Diode_Pumpseite_PRTDSI__OE_SEL0        (* (reg8 *) Diode_Pumpseite__PRTDSI__OE_SEL0) 
#define Diode_Pumpseite_PRTDSI__OE_SEL1        (* (reg8 *) Diode_Pumpseite__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Diode_Pumpseite_PRTDSI__OUT_SEL0       (* (reg8 *) Diode_Pumpseite__PRTDSI__OUT_SEL0) 
#define Diode_Pumpseite_PRTDSI__OUT_SEL1       (* (reg8 *) Diode_Pumpseite__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Diode_Pumpseite_PRTDSI__SYNC_OUT       (* (reg8 *) Diode_Pumpseite__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Diode_Pumpseite__SIO_CFG)
    #define Diode_Pumpseite_SIO_HYST_EN        (* (reg8 *) Diode_Pumpseite__SIO_HYST_EN)
    #define Diode_Pumpseite_SIO_REG_HIFREQ     (* (reg8 *) Diode_Pumpseite__SIO_REG_HIFREQ)
    #define Diode_Pumpseite_SIO_CFG            (* (reg8 *) Diode_Pumpseite__SIO_CFG)
    #define Diode_Pumpseite_SIO_DIFF           (* (reg8 *) Diode_Pumpseite__SIO_DIFF)
#endif /* (Diode_Pumpseite__SIO_CFG) */

/* Interrupt Registers */
#if defined(Diode_Pumpseite__INTSTAT)
    #define Diode_Pumpseite_INTSTAT            (* (reg8 *) Diode_Pumpseite__INTSTAT)
    #define Diode_Pumpseite_SNAP               (* (reg8 *) Diode_Pumpseite__SNAP)
    
	#define Diode_Pumpseite_0_INTTYPE_REG 		(* (reg8 *) Diode_Pumpseite__0__INTTYPE)
#endif /* (Diode_Pumpseite__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Diode_Pumpseite_H */


/* [] END OF FILE */
