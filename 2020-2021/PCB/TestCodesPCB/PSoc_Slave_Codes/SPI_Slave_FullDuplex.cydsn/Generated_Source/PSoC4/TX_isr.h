/*******************************************************************************
* File Name: TX_isr.h
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
#if !defined(CY_ISR_TX_isr_H)
#define CY_ISR_TX_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void TX_isr_Start(void);
void TX_isr_StartEx(cyisraddress address);
void TX_isr_Stop(void);

CY_ISR_PROTO(TX_isr_Interrupt);

void TX_isr_SetVector(cyisraddress address);
cyisraddress TX_isr_GetVector(void);

void TX_isr_SetPriority(uint8 priority);
uint8 TX_isr_GetPriority(void);

void TX_isr_Enable(void);
uint8 TX_isr_GetState(void);
void TX_isr_Disable(void);

void TX_isr_SetPending(void);
void TX_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the TX_isr ISR. */
#define TX_isr_INTC_VECTOR            ((reg32 *) TX_isr__INTC_VECT)

/* Address of the TX_isr ISR priority. */
#define TX_isr_INTC_PRIOR             ((reg32 *) TX_isr__INTC_PRIOR_REG)

/* Priority of the TX_isr interrupt. */
#define TX_isr_INTC_PRIOR_NUMBER      TX_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable TX_isr interrupt. */
#define TX_isr_INTC_SET_EN            ((reg32 *) TX_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the TX_isr interrupt. */
#define TX_isr_INTC_CLR_EN            ((reg32 *) TX_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the TX_isr interrupt state to pending. */
#define TX_isr_INTC_SET_PD            ((reg32 *) TX_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the TX_isr interrupt. */
#define TX_isr_INTC_CLR_PD            ((reg32 *) TX_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_TX_isr_H */


/* [] END OF FILE */
