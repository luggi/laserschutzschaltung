/*******************************************************************************
* File Name: vref.h  
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

#if !defined(CY_PINS_vref_H) /* Pins vref_H */
#define CY_PINS_vref_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "vref_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 vref__PORT == 15 && ((vref__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    vref_Write(uint8 value);
void    vref_SetDriveMode(uint8 mode);
uint8   vref_ReadDataReg(void);
uint8   vref_Read(void);
void    vref_SetInterruptMode(uint16 position, uint16 mode);
uint8   vref_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the vref_SetDriveMode() function.
     *  @{
     */
        #define vref_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define vref_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define vref_DM_RES_UP          PIN_DM_RES_UP
        #define vref_DM_RES_DWN         PIN_DM_RES_DWN
        #define vref_DM_OD_LO           PIN_DM_OD_LO
        #define vref_DM_OD_HI           PIN_DM_OD_HI
        #define vref_DM_STRONG          PIN_DM_STRONG
        #define vref_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define vref_MASK               vref__MASK
#define vref_SHIFT              vref__SHIFT
#define vref_WIDTH              1u

/* Interrupt constants */
#if defined(vref__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in vref_SetInterruptMode() function.
     *  @{
     */
        #define vref_INTR_NONE      (uint16)(0x0000u)
        #define vref_INTR_RISING    (uint16)(0x0001u)
        #define vref_INTR_FALLING   (uint16)(0x0002u)
        #define vref_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define vref_INTR_MASK      (0x01u) 
#endif /* (vref__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define vref_PS                     (* (reg8 *) vref__PS)
/* Data Register */
#define vref_DR                     (* (reg8 *) vref__DR)
/* Port Number */
#define vref_PRT_NUM                (* (reg8 *) vref__PRT) 
/* Connect to Analog Globals */                                                  
#define vref_AG                     (* (reg8 *) vref__AG)                       
/* Analog MUX bux enable */
#define vref_AMUX                   (* (reg8 *) vref__AMUX) 
/* Bidirectional Enable */                                                        
#define vref_BIE                    (* (reg8 *) vref__BIE)
/* Bit-mask for Aliased Register Access */
#define vref_BIT_MASK               (* (reg8 *) vref__BIT_MASK)
/* Bypass Enable */
#define vref_BYP                    (* (reg8 *) vref__BYP)
/* Port wide control signals */                                                   
#define vref_CTL                    (* (reg8 *) vref__CTL)
/* Drive Modes */
#define vref_DM0                    (* (reg8 *) vref__DM0) 
#define vref_DM1                    (* (reg8 *) vref__DM1)
#define vref_DM2                    (* (reg8 *) vref__DM2) 
/* Input Buffer Disable Override */
#define vref_INP_DIS                (* (reg8 *) vref__INP_DIS)
/* LCD Common or Segment Drive */
#define vref_LCD_COM_SEG            (* (reg8 *) vref__LCD_COM_SEG)
/* Enable Segment LCD */
#define vref_LCD_EN                 (* (reg8 *) vref__LCD_EN)
/* Slew Rate Control */
#define vref_SLW                    (* (reg8 *) vref__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define vref_PRTDSI__CAPS_SEL       (* (reg8 *) vref__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define vref_PRTDSI__DBL_SYNC_IN    (* (reg8 *) vref__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define vref_PRTDSI__OE_SEL0        (* (reg8 *) vref__PRTDSI__OE_SEL0) 
#define vref_PRTDSI__OE_SEL1        (* (reg8 *) vref__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define vref_PRTDSI__OUT_SEL0       (* (reg8 *) vref__PRTDSI__OUT_SEL0) 
#define vref_PRTDSI__OUT_SEL1       (* (reg8 *) vref__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define vref_PRTDSI__SYNC_OUT       (* (reg8 *) vref__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(vref__SIO_CFG)
    #define vref_SIO_HYST_EN        (* (reg8 *) vref__SIO_HYST_EN)
    #define vref_SIO_REG_HIFREQ     (* (reg8 *) vref__SIO_REG_HIFREQ)
    #define vref_SIO_CFG            (* (reg8 *) vref__SIO_CFG)
    #define vref_SIO_DIFF           (* (reg8 *) vref__SIO_DIFF)
#endif /* (vref__SIO_CFG) */

/* Interrupt Registers */
#if defined(vref__INTSTAT)
    #define vref_INTSTAT            (* (reg8 *) vref__INTSTAT)
    #define vref_SNAP               (* (reg8 *) vref__SNAP)
    
	#define vref_0_INTTYPE_REG 		(* (reg8 *) vref__0__INTTYPE)
#endif /* (vref__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_vref_H */


/* [] END OF FILE */
