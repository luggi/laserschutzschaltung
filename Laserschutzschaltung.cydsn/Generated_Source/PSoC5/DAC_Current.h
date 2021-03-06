/*******************************************************************************
* File Name: DAC_Current.h  
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

#if !defined(CY_PINS_DAC_Current_H) /* Pins DAC_Current_H */
#define CY_PINS_DAC_Current_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DAC_Current_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DAC_Current__PORT == 15 && ((DAC_Current__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DAC_Current_Write(uint8 value);
void    DAC_Current_SetDriveMode(uint8 mode);
uint8   DAC_Current_ReadDataReg(void);
uint8   DAC_Current_Read(void);
void    DAC_Current_SetInterruptMode(uint16 position, uint16 mode);
uint8   DAC_Current_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DAC_Current_SetDriveMode() function.
     *  @{
     */
        #define DAC_Current_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DAC_Current_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DAC_Current_DM_RES_UP          PIN_DM_RES_UP
        #define DAC_Current_DM_RES_DWN         PIN_DM_RES_DWN
        #define DAC_Current_DM_OD_LO           PIN_DM_OD_LO
        #define DAC_Current_DM_OD_HI           PIN_DM_OD_HI
        #define DAC_Current_DM_STRONG          PIN_DM_STRONG
        #define DAC_Current_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DAC_Current_MASK               DAC_Current__MASK
#define DAC_Current_SHIFT              DAC_Current__SHIFT
#define DAC_Current_WIDTH              1u

/* Interrupt constants */
#if defined(DAC_Current__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DAC_Current_SetInterruptMode() function.
     *  @{
     */
        #define DAC_Current_INTR_NONE      (uint16)(0x0000u)
        #define DAC_Current_INTR_RISING    (uint16)(0x0001u)
        #define DAC_Current_INTR_FALLING   (uint16)(0x0002u)
        #define DAC_Current_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DAC_Current_INTR_MASK      (0x01u) 
#endif /* (DAC_Current__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DAC_Current_PS                     (* (reg8 *) DAC_Current__PS)
/* Data Register */
#define DAC_Current_DR                     (* (reg8 *) DAC_Current__DR)
/* Port Number */
#define DAC_Current_PRT_NUM                (* (reg8 *) DAC_Current__PRT) 
/* Connect to Analog Globals */                                                  
#define DAC_Current_AG                     (* (reg8 *) DAC_Current__AG)                       
/* Analog MUX bux enable */
#define DAC_Current_AMUX                   (* (reg8 *) DAC_Current__AMUX) 
/* Bidirectional Enable */                                                        
#define DAC_Current_BIE                    (* (reg8 *) DAC_Current__BIE)
/* Bit-mask for Aliased Register Access */
#define DAC_Current_BIT_MASK               (* (reg8 *) DAC_Current__BIT_MASK)
/* Bypass Enable */
#define DAC_Current_BYP                    (* (reg8 *) DAC_Current__BYP)
/* Port wide control signals */                                                   
#define DAC_Current_CTL                    (* (reg8 *) DAC_Current__CTL)
/* Drive Modes */
#define DAC_Current_DM0                    (* (reg8 *) DAC_Current__DM0) 
#define DAC_Current_DM1                    (* (reg8 *) DAC_Current__DM1)
#define DAC_Current_DM2                    (* (reg8 *) DAC_Current__DM2) 
/* Input Buffer Disable Override */
#define DAC_Current_INP_DIS                (* (reg8 *) DAC_Current__INP_DIS)
/* LCD Common or Segment Drive */
#define DAC_Current_LCD_COM_SEG            (* (reg8 *) DAC_Current__LCD_COM_SEG)
/* Enable Segment LCD */
#define DAC_Current_LCD_EN                 (* (reg8 *) DAC_Current__LCD_EN)
/* Slew Rate Control */
#define DAC_Current_SLW                    (* (reg8 *) DAC_Current__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DAC_Current_PRTDSI__CAPS_SEL       (* (reg8 *) DAC_Current__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DAC_Current_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DAC_Current__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DAC_Current_PRTDSI__OE_SEL0        (* (reg8 *) DAC_Current__PRTDSI__OE_SEL0) 
#define DAC_Current_PRTDSI__OE_SEL1        (* (reg8 *) DAC_Current__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DAC_Current_PRTDSI__OUT_SEL0       (* (reg8 *) DAC_Current__PRTDSI__OUT_SEL0) 
#define DAC_Current_PRTDSI__OUT_SEL1       (* (reg8 *) DAC_Current__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DAC_Current_PRTDSI__SYNC_OUT       (* (reg8 *) DAC_Current__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DAC_Current__SIO_CFG)
    #define DAC_Current_SIO_HYST_EN        (* (reg8 *) DAC_Current__SIO_HYST_EN)
    #define DAC_Current_SIO_REG_HIFREQ     (* (reg8 *) DAC_Current__SIO_REG_HIFREQ)
    #define DAC_Current_SIO_CFG            (* (reg8 *) DAC_Current__SIO_CFG)
    #define DAC_Current_SIO_DIFF           (* (reg8 *) DAC_Current__SIO_DIFF)
#endif /* (DAC_Current__SIO_CFG) */

/* Interrupt Registers */
#if defined(DAC_Current__INTSTAT)
    #define DAC_Current_INTSTAT            (* (reg8 *) DAC_Current__INTSTAT)
    #define DAC_Current_SNAP               (* (reg8 *) DAC_Current__SNAP)
    
	#define DAC_Current_0_INTTYPE_REG 		(* (reg8 *) DAC_Current__0__INTTYPE)
#endif /* (DAC_Current__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DAC_Current_H */


/* [] END OF FILE */
