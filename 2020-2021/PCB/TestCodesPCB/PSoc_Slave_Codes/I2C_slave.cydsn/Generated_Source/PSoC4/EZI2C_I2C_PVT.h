/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
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

#if !defined(CY_SCB_I2C_PVT_EZI2C_H)
#define CY_SCB_I2C_PVT_EZI2C_H

#include "EZI2C_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 EZI2C_state; /* Current state of I2C FSM */

#if(EZI2C_I2C_SLAVE_CONST)
    extern volatile uint8 EZI2C_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * EZI2C_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  EZI2C_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  EZI2C_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * EZI2C_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  EZI2C_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  EZI2C_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  EZI2C_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   EZI2C_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (EZI2C_I2C_SLAVE_CONST) */

#if(EZI2C_I2C_MASTER_CONST)
    extern volatile uint16 EZI2C_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  EZI2C_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * EZI2C_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  EZI2C_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  EZI2C_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * EZI2C_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  EZI2C_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  EZI2C_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  EZI2C_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (EZI2C_I2C_MASTER_CONST) */

#if (EZI2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*EZI2C_customAddressHandler) (void);
#endif /* (EZI2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(EZI2C_SCB_MODE_I2C_CONST_CFG)
    void EZI2C_I2CInit(void);
#endif /* (EZI2C_SCB_MODE_I2C_CONST_CFG) */

void EZI2C_I2CStop(void);
void EZI2C_I2CFwBlockReset(void);

void EZI2C_I2CSaveConfig(void);
void EZI2C_I2CRestoreConfig(void);

#if(EZI2C_I2C_MASTER_CONST)
    void EZI2C_I2CReStartGeneration(void);
#endif /* (EZI2C_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_EZI2C_H) */


/* [] END OF FILE */
