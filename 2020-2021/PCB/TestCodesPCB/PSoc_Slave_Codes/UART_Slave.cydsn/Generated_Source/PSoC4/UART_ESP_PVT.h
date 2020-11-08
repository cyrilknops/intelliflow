/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_UART_ESP_H)
#define CY_SCB_PVT_UART_ESP_H

#include "UART_ESP.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UART_ESP_SetI2CExtClkInterruptMode(interruptMask) UART_ESP_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UART_ESP_ClearI2CExtClkInterruptSource(interruptMask) UART_ESP_CLEAR_INTR_I2C_EC(interruptMask)
#define UART_ESP_GetI2CExtClkInterruptSource()                (UART_ESP_INTR_I2C_EC_REG)
#define UART_ESP_GetI2CExtClkInterruptMode()                  (UART_ESP_INTR_I2C_EC_MASK_REG)
#define UART_ESP_GetI2CExtClkInterruptSourceMasked()          (UART_ESP_INTR_I2C_EC_MASKED_REG)

#if (!UART_ESP_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UART_ESP_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UART_ESP_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UART_ESP_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UART_ESP_CLEAR_INTR_SPI_EC(interruptMask)
    #define UART_ESP_GetExtSpiClkInterruptSource()                 (UART_ESP_INTR_SPI_EC_REG)
    #define UART_ESP_GetExtSpiClkInterruptMode()                   (UART_ESP_INTR_SPI_EC_MASK_REG)
    #define UART_ESP_GetExtSpiClkInterruptSourceMasked()           (UART_ESP_INTR_SPI_EC_MASKED_REG)
#endif /* (!UART_ESP_CY_SCBIP_V1) */

#if(UART_ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UART_ESP_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UART_ESP_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UART_ESP_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UART_ESP_CUSTOM_INTR_HANDLER)
    extern cyisraddress UART_ESP_customIntrHandler;
#endif /* !defined (CY_REMOVE_UART_ESP_CUSTOM_INTR_HANDLER) */
#endif /* (UART_ESP_SCB_IRQ_INTERNAL) */

extern UART_ESP_BACKUP_STRUCT UART_ESP_backup;

#if(UART_ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UART_ESP_scbMode;
    extern uint8 UART_ESP_scbEnableWake;
    extern uint8 UART_ESP_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UART_ESP_mode;
    extern uint8 UART_ESP_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UART_ESP_rxBuffer;
    extern uint8   UART_ESP_rxDataBits;
    extern uint32  UART_ESP_rxBufferSize;

    extern volatile uint8 * UART_ESP_txBuffer;
    extern uint8   UART_ESP_txDataBits;
    extern uint32  UART_ESP_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UART_ESP_numberOfAddr;
    extern uint8 UART_ESP_subAddrSize;
#endif /* (UART_ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UART_ESP_SCB_MODE_I2C_CONST_CFG || \
        UART_ESP_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UART_ESP_IntrTxMask;
#endif /* (! (UART_ESP_SCB_MODE_I2C_CONST_CFG || \
              UART_ESP_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UART_ESP_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UART_ESP_SCB_MODE_I2C_RUNTM_CFG     (UART_ESP_SCB_MODE_I2C      == UART_ESP_scbMode)
    #define UART_ESP_SCB_MODE_SPI_RUNTM_CFG     (UART_ESP_SCB_MODE_SPI      == UART_ESP_scbMode)
    #define UART_ESP_SCB_MODE_UART_RUNTM_CFG    (UART_ESP_SCB_MODE_UART     == UART_ESP_scbMode)
    #define UART_ESP_SCB_MODE_EZI2C_RUNTM_CFG   (UART_ESP_SCB_MODE_EZI2C    == UART_ESP_scbMode)
    #define UART_ESP_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UART_ESP_SCB_MODE_UNCONFIG == UART_ESP_scbMode)

    /* Defines wakeup enable */
    #define UART_ESP_SCB_WAKE_ENABLE_CHECK       (0u != UART_ESP_scbEnableWake)
#endif /* (UART_ESP_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UART_ESP_CY_SCBIP_V1)
    #define UART_ESP_SCB_PINS_NUMBER    (7u)
#else
    #define UART_ESP_SCB_PINS_NUMBER    (2u)
#endif /* (!UART_ESP_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UART_ESP_H) */


/* [] END OF FILE */
