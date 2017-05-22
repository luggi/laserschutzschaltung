/*******************************************************************************
* File Name: temp_sens.h  
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

#if !defined(CY_PINS_temp_sens_H) /* Pins temp_sens_H */
#define CY_PINS_temp_sens_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "temp_sens_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 temp_sens__PORT == 15 && ((temp_sens__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    temp_sens_Write(uint8 value);
void    temp_sens_SetDriveMode(uint8 mode);
uint8   temp_sens_ReadDataReg(void);
uint8   temp_sens_Read(void);
void    temp_sens_SetInterruptMode(uint16 position, uint16 mode);
uint8   temp_sens_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the temp_sens_SetDriveMode() function.
     *  @{
     */
        #define temp_sens_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define temp_sens_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define temp_sens_DM_RES_UP          PIN_DM_RES_UP
        #define temp_sens_DM_RES_DWN         PIN_DM_RES_DWN
        #define temp_sens_DM_OD_LO           PIN_DM_OD_LO
        #define temp_sens_DM_OD_HI           PIN_DM_OD_HI
        #define temp_sens_DM_STRONG          PIN_DM_STRONG
        #define temp_sens_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define temp_sens_MASK               temp_sens__MASK
#define temp_sens_SHIFT              temp_sens__SHIFT
#define temp_sens_WIDTH              1u

/* Interrupt constants */
#if defined(temp_sens__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in temp_sens_SetInterruptMode() function.
     *  @{
     */
        #define temp_sens_INTR_NONE      (uint16)(0x0000u)
        #define temp_sens_INTR_RISING    (uint16)(0x0001u)
        #define temp_sens_INTR_FALLING   (uint16)(0x0002u)
        #define temp_sens_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define temp_sens_INTR_MASK      (0x01u) 
#endif /* (temp_sens__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define temp_sens_PS                     (* (reg8 *) temp_sens__PS)
/* Data Register */
#define temp_sens_DR                     (* (reg8 *) temp_sens__DR)
/* Port Number */
#define temp_sens_PRT_NUM                (* (reg8 *) temp_sens__PRT) 
/* Connect to Analog Globals */                                                  
#define temp_sens_AG                     (* (reg8 *) temp_sens__AG)                       
/* Analog MUX bux enable */
#define temp_sens_AMUX                   (* (reg8 *) temp_sens__AMUX) 
/* Bidirectional Enable */                                                        
#define temp_sens_BIE                    (* (reg8 *) temp_sens__BIE)
/* Bit-mask for Aliased Register Access */
#define temp_sens_BIT_MASK               (* (reg8 *) temp_sens__BIT_MASK)
/* Bypass Enable */
#define temp_sens_BYP                    (* (reg8 *) temp_sens__BYP)
/* Port wide control signals */                                                   
#define temp_sens_CTL                    (* (reg8 *) temp_sens__CTL)
/* Drive Modes */
#define temp_sens_DM0                    (* (reg8 *) temp_sens__DM0) 
#define temp_sens_DM1                    (* (reg8 *) temp_sens__DM1)
#define temp_sens_DM2                    (* (reg8 *) temp_sens__DM2) 
/* Input Buffer Disable Override */
#define temp_sens_INP_DIS                (* (reg8 *) temp_sens__INP_DIS)
/* LCD Common or Segment Drive */
#define temp_sens_LCD_COM_SEG            (* (reg8 *) temp_sens__LCD_COM_SEG)
/* Enable Segment LCD */
#define temp_sens_LCD_EN                 (* (reg8 *) temp_sens__LCD_EN)
/* Slew Rate Control */
#define temp_sens_SLW                    (* (reg8 *) temp_sens__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define temp_sens_PRTDSI__CAPS_SEL       (* (reg8 *) temp_sens__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define temp_sens_PRTDSI__DBL_SYNC_IN    (* (reg8 *) temp_sens__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define temp_sens_PRTDSI__OE_SEL0        (* (reg8 *) temp_sens__PRTDSI__OE_SEL0) 
#define temp_sens_PRTDSI__OE_SEL1        (* (reg8 *) temp_sens__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define temp_sens_PRTDSI__OUT_SEL0       (* (reg8 *) temp_sens__PRTDSI__OUT_SEL0) 
#define temp_sens_PRTDSI__OUT_SEL1       (* (reg8 *) temp_sens__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define temp_sens_PRTDSI__SYNC_OUT       (* (reg8 *) temp_sens__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(temp_sens__SIO_CFG)
    #define temp_sens_SIO_HYST_EN        (* (reg8 *) temp_sens__SIO_HYST_EN)
    #define temp_sens_SIO_REG_HIFREQ     (* (reg8 *) temp_sens__SIO_REG_HIFREQ)
    #define temp_sens_SIO_CFG            (* (reg8 *) temp_sens__SIO_CFG)
    #define temp_sens_SIO_DIFF           (* (reg8 *) temp_sens__SIO_DIFF)
#endif /* (temp_sens__SIO_CFG) */

/* Interrupt Registers */
#if defined(temp_sens__INTSTAT)
    #define temp_sens_INTSTAT            (* (reg8 *) temp_sens__INTSTAT)
    #define temp_sens_SNAP               (* (reg8 *) temp_sens__SNAP)
    
	#define temp_sens_0_INTTYPE_REG 		(* (reg8 *) temp_sens__0__INTTYPE)
#endif /* (temp_sens__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_temp_sens_H */


/* [] END OF FILE */
