/*******************************************************************************
* File Name: SPIS_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SPIS_IntClock_H)
#define CY_CLOCK_SPIS_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SPIS_IntClock_StartEx(uint32 alignClkDiv);
#define SPIS_IntClock_Start() \
    SPIS_IntClock_StartEx(SPIS_IntClock__PA_DIV_ID)

#else

void SPIS_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SPIS_IntClock_Stop(void);

void SPIS_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SPIS_IntClock_GetDividerRegister(void);
uint8  SPIS_IntClock_GetFractionalDividerRegister(void);

#define SPIS_IntClock_Enable()                         SPIS_IntClock_Start()
#define SPIS_IntClock_Disable()                        SPIS_IntClock_Stop()
#define SPIS_IntClock_SetDividerRegister(clkDivider, reset)  \
    SPIS_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define SPIS_IntClock_SetDivider(clkDivider)           SPIS_IntClock_SetDividerRegister((clkDivider), 1u)
#define SPIS_IntClock_SetDividerValue(clkDivider)      SPIS_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SPIS_IntClock_DIV_ID     SPIS_IntClock__DIV_ID

#define SPIS_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SPIS_IntClock_CTRL_REG   (*(reg32 *)SPIS_IntClock__CTRL_REGISTER)
#define SPIS_IntClock_DIV_REG    (*(reg32 *)SPIS_IntClock__DIV_REGISTER)

#define SPIS_IntClock_CMD_DIV_SHIFT          (0u)
#define SPIS_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define SPIS_IntClock_CMD_DISABLE_SHIFT      (30u)
#define SPIS_IntClock_CMD_ENABLE_SHIFT       (31u)

#define SPIS_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SPIS_IntClock_CMD_DISABLE_SHIFT))
#define SPIS_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SPIS_IntClock_CMD_ENABLE_SHIFT))

#define SPIS_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define SPIS_IntClock_DIV_FRAC_SHIFT (3u)
#define SPIS_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define SPIS_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define SPIS_IntClock_DIV_REG        (*(reg32 *)SPIS_IntClock__REGISTER)
#define SPIS_IntClock_ENABLE_REG     SPIS_IntClock_DIV_REG
#define SPIS_IntClock_DIV_FRAC_MASK  SPIS_IntClock__FRAC_MASK
#define SPIS_IntClock_DIV_FRAC_SHIFT (16u)
#define SPIS_IntClock_DIV_INT_MASK   SPIS_IntClock__DIVIDER_MASK
#define SPIS_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SPIS_IntClock_H) */

/* [] END OF FILE */
