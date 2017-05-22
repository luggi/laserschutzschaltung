/*******************************************************************************
* File Name: Diode_Seedseite.h  
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

#if !defined(CY_PINS_Diode_Seedseite_H) /* Pins Diode_Seedseite_H */
#define CY_PINS_Diode_Seedseite_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Diode_Seedseite_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Diode_Seedseite__PORT == 15 && ((Diode_Seedseite__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Diode_Seedseite_Write(uint8 value);
void    Diode_Seedseite_SetDriveMode(uint8 mode);
uint8   Diode_Seedseite_ReadDataReg(void);
uint8   Diode_Seedseite_Read(void);
void    Diode_Seedseite_SetInterruptMode(uint16 position, uint16 mode);
uint8   Diode_Seedseite_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Diode_Seedseite_SetDriveMode() function.
     *  @{
     */
        #define Diode_Seedseite_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Diode_Seedseite_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Diode_Seedseite_DM_RES_UP          PIN_DM_RES_UP
        #define Diode_Seedseite_DM_RES_DWN         PIN_DM_RES_DWN
        #define Diode_Seedseite_DM_OD_LO           PIN_DM_OD_LO
        #define Diode_Seedseite_DM_OD_HI           PIN_DM_OD_HI
        #define Diode_Seedseite_DM_STRONG          PIN_DM_STRONG
        #define Diode_Seedseite_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Diode_Seedseite_MASK               Diode_Seedseite__MASK
#define Diode_Seedseite_SHIFT              Diode_Seedseite__SHIFT
#define Diode_Seedseite_WIDTH              1u

/* Interrupt constants */
#if defined(Diode_Seedseite__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Diode_Seedseite_SetInterruptMode() function.
     *  @{
     */
        #define Diode_Seedseite_INTR_NONE      (uint16)(0x0000u)
        #define Diode_Seedseite_INTR_RISING    (uint16)(0x0001u)
        #define Diode_Seedseite_INTR_FALLING   (uint16)(0x0002u)
        #define Diode_Seedseite_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Diode_Seedseite_INTR_MASK      (0x01u) 
#endif /* (Diode_Seedseite__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Diode_Seedseite_PS                     (* (reg8 *) Diode_Seedseite__PS)
/* Data Register */
#define Diode_Seedseite_DR                     (* (reg8 *) Diode_Seedseite__DR)
/* Port Number */
#define Diode_Seedseite_PRT_NUM                (* (reg8 *) Diode_Seedseite__PRT) 
/* Connect to Analog Globals */                                                  
#define Diode_Seedseite_AG                     (* (reg8 *) Diode_Seedseite__AG)                       
/* Analog MUX bux enable */
#define Diode_Seedseite_AMUX                   (* (reg8 *) Diode_Seedseite__AMUX) 
/* Bidirectional Enable */                                                        
#define Diode_Seedseite_BIE                    (* (reg8 *) Diode_Seedseite__BIE)
/* Bit-mask for Aliased Register Access */
#define Diode_Seedseite_BIT_MASK               (* (reg8 *) Diode_Seedseite__BIT_MASK)
/* Bypass Enable */
#define Diode_Seedseite_BYP                    (* (reg8 *) Diode_Seedseite__BYP)
/* Port wide control signals */                                                   
#define Diode_Seedseite_CTL                    (* (reg8 *) Diode_Seedseite__CTL)
/* Drive Modes */
#define Diode_Seedseite_DM0                    (* (reg8 *) Diode_Seedseite__DM0) 
#define Diode_Seedseite_DM1                    (* (reg8 *) Diode_Seedseite__DM1)
#define Diode_Seedseite_DM2                    (* (reg8 *) Diode_Seedseite__DM2) 
/* Input Buffer Disable Override */
#define Diode_Seedseite_INP_DIS                (* (reg8 *) Diode_Seedseite__INP_DIS)
/* LCD Common or Segment Drive */
#define Diode_Seedseite_LCD_COM_SEG            (* (reg8 *) Diode_Seedseite__LCD_COM_SEG)
/* Enable Segment LCD */
#define Diode_Seedseite_LCD_EN                 (* (reg8 *) Diode_Seedseite__LCD_EN)
/* Slew Rate Control */
#define Diode_Seedseite_SLW                    (* (reg8 *) Diode_Seedseite__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Diode_Seedseite_PRTDSI__CAPS_SEL       (* (reg8 *) Diode_Seedseite__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Diode_Seedseite_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Diode_Seedseite__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Diode_Seedseite_PRTDSI__OE_SEL0        (* (reg8 *) Diode_Seedseite__PRTDSI__OE_SEL0) 
#define Diode_Seedseite_PRTDSI__OE_SEL1        (* (reg8 *) Diode_Seedseite__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Diode_Seedseite_PRTDSI__OUT_SEL0       (* (reg8 *) Diode_Seedseite__PRTDSI__OUT_SEL0) 
#define Diode_Seedseite_PRTDSI__OUT_SEL1       (* (reg8 *) Diode_Seedseite__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Diode_Seedseite_PRTDSI__SYNC_OUT       (* (reg8 *) Diode_Seedseite__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Diode_Seedseite__SIO_CFG)
    #define Diode_Seedseite_SIO_HYST_EN        (* (reg8 *) Diode_Seedseite__SIO_HYST_EN)
    #define Diode_Seedseite_SIO_REG_HIFREQ     (* (reg8 *) Diode_Seedseite__SIO_REG_HIFREQ)
    #define Diode_Seedseite_SIO_CFG            (* (reg8 *) Diode_Seedseite__SIO_CFG)
    #define Diode_Seedseite_SIO_DIFF           (* (reg8 *) Diode_Seedseite__SIO_DIFF)
#endif /* (Diode_Seedseite__SIO_CFG) */

/* Interrupt Registers */
#if defined(Diode_Seedseite__INTSTAT)
    #define Diode_Seedseite_INTSTAT            (* (reg8 *) Diode_Seedseite__INTSTAT)
    #define Diode_Seedseite_SNAP               (* (reg8 *) Diode_Seedseite__SNAP)
    
	#define Diode_Seedseite_0_INTTYPE_REG 		(* (reg8 *) Diode_Seedseite__0__INTTYPE)
#endif /* (Diode_Seedseite__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Diode_Seedseite_H */


/* [] END OF FILE */
