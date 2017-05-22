/*******************************************************************************
* File Name: PID_isr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_PID_isr_H)
#define CY_ISR_PID_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void PID_isr_Start(void);
void PID_isr_StartEx(cyisraddress address);
void PID_isr_Stop(void);

CY_ISR_PROTO(PID_isr_Interrupt);

void PID_isr_SetVector(cyisraddress address);
cyisraddress PID_isr_GetVector(void);

void PID_isr_SetPriority(uint8 priority);
uint8 PID_isr_GetPriority(void);

void PID_isr_Enable(void);
uint8 PID_isr_GetState(void);
void PID_isr_Disable(void);

void PID_isr_SetPending(void);
void PID_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the PID_isr ISR. */
#define PID_isr_INTC_VECTOR            ((reg32 *) PID_isr__INTC_VECT)

/* Address of the PID_isr ISR priority. */
#define PID_isr_INTC_PRIOR             ((reg8 *) PID_isr__INTC_PRIOR_REG)

/* Priority of the PID_isr interrupt. */
#define PID_isr_INTC_PRIOR_NUMBER      PID_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable PID_isr interrupt. */
#define PID_isr_INTC_SET_EN            ((reg32 *) PID_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the PID_isr interrupt. */
#define PID_isr_INTC_CLR_EN            ((reg32 *) PID_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the PID_isr interrupt state to pending. */
#define PID_isr_INTC_SET_PD            ((reg32 *) PID_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the PID_isr interrupt. */
#define PID_isr_INTC_CLR_PD            ((reg32 *) PID_isr__INTC_CLR_PD_REG)


#endif /* CY_ISR_PID_isr_H */


/* [] END OF FILE */
