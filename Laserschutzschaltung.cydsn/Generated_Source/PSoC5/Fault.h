/*******************************************************************************
* File Name: Fault.h  
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

#if !defined(CY_PINS_Fault_H) /* Pins Fault_H */
#define CY_PINS_Fault_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Fault_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Fault__PORT == 15 && ((Fault__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Fault_Write(uint8 value);
void    Fault_SetDriveMode(uint8 mode);
uint8   Fault_ReadDataReg(void);
uint8   Fault_Read(void);
void    Fault_SetInterruptMode(uint16 position, uint16 mode);
uint8   Fault_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Fault_SetDriveMode() function.
     *  @{
     */
        #define Fault_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Fault_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Fault_DM_RES_UP          PIN_DM_RES_UP
        #define Fault_DM_RES_DWN         PIN_DM_RES_DWN
        #define Fault_DM_OD_LO           PIN_DM_OD_LO
        #define Fault_DM_OD_HI           PIN_DM_OD_HI
        #define Fault_DM_STRONG          PIN_DM_STRONG
        #define Fault_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Fault_MASK               Fault__MASK
#define Fault_SHIFT              Fault__SHIFT
#define Fault_WIDTH              1u

/* Interrupt constants */
#if defined(Fault__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Fault_SetInterruptMode() function.
     *  @{
     */
        #define Fault_INTR_NONE      (uint16)(0x0000u)
        #define Fault_INTR_RISING    (uint16)(0x0001u)
        #define Fault_INTR_FALLING   (uint16)(0x0002u)
        #define Fault_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Fault_INTR_MASK      (0x01u) 
#endif /* (Fault__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Fault_PS                     (* (reg8 *) Fault__PS)
/* Data Register */
#define Fault_DR                     (* (reg8 *) Fault__DR)
/* Port Number */
#define Fault_PRT_NUM                (* (reg8 *) Fault__PRT) 
/* Connect to Analog Globals */                                                  
#define Fault_AG                     (* (reg8 *) Fault__AG)                       
/* Analog MUX bux enable */
#define Fault_AMUX                   (* (reg8 *) Fault__AMUX) 
/* Bidirectional Enable */                                                        
#define Fault_BIE                    (* (reg8 *) Fault__BIE)
/* Bit-mask for Aliased Register Access */
#define Fault_BIT_MASK               (* (reg8 *) Fault__BIT_MASK)
/* Bypass Enable */
#define Fault_BYP                    (* (reg8 *) Fault__BYP)
/* Port wide control signals */                                                   
#define Fault_CTL                    (* (reg8 *) Fault__CTL)
/* Drive Modes */
#define Fault_DM0                    (* (reg8 *) Fault__DM0) 
#define Fault_DM1                    (* (reg8 *) Fault__DM1)
#define Fault_DM2                    (* (reg8 *) Fault__DM2) 
/* Input Buffer Disable Override */
#define Fault_INP_DIS                (* (reg8 *) Fault__INP_DIS)
/* LCD Common or Segment Drive */
#define Fault_LCD_COM_SEG            (* (reg8 *) Fault__LCD_COM_SEG)
/* Enable Segment LCD */
#define Fault_LCD_EN                 (* (reg8 *) Fault__LCD_EN)
/* Slew Rate Control */
#define Fault_SLW                    (* (reg8 *) Fault__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Fault_PRTDSI__CAPS_SEL       (* (reg8 *) Fault__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Fault_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Fault__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Fault_PRTDSI__OE_SEL0        (* (reg8 *) Fault__PRTDSI__OE_SEL0) 
#define Fault_PRTDSI__OE_SEL1        (* (reg8 *) Fault__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Fault_PRTDSI__OUT_SEL0       (* (reg8 *) Fault__PRTDSI__OUT_SEL0) 
#define Fault_PRTDSI__OUT_SEL1       (* (reg8 *) Fault__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Fault_PRTDSI__SYNC_OUT       (* (reg8 *) Fault__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Fault__SIO_CFG)
    #define Fault_SIO_HYST_EN        (* (reg8 *) Fault__SIO_HYST_EN)
    #define Fault_SIO_REG_HIFREQ     (* (reg8 *) Fault__SIO_REG_HIFREQ)
    #define Fault_SIO_CFG            (* (reg8 *) Fault__SIO_CFG)
    #define Fault_SIO_DIFF           (* (reg8 *) Fault__SIO_DIFF)
#endif /* (Fault__SIO_CFG) */

/* Interrupt Registers */
#if defined(Fault__INTSTAT)
    #define Fault_INTSTAT            (* (reg8 *) Fault__INTSTAT)
    #define Fault_SNAP               (* (reg8 *) Fault__SNAP)
    
	#define Fault_0_INTTYPE_REG 		(* (reg8 *) Fault__0__INTTYPE)
#endif /* (Fault__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Fault_H */


/* [] END OF FILE */
