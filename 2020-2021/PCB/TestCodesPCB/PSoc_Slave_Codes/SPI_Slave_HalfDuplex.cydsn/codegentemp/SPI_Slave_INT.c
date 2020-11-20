/*******************************************************************************
* File Name: SPI_Slave_INT.c
* Version 2.70
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Slave
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_Slave_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START SPI_Slave_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SPI_Slave_TX_ISR
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_Slave_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPI_Slave_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SPI_Slave_txBuffer[SPI_Slave_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPI_Slave_TX_ISR)
{

    #if(SPI_Slave_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (SPI_Slave_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPI_Slave_TX_ISR_ENTRY_CALLBACK
        SPI_Slave_TX_ISR_EntryCallback();
    #endif /* SPI_Slave_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPI_Slave_ISR_TX_START` */

    /* `#END` */

    #if(SPI_Slave_TX_SOFTWARE_BUF_ENABLED)
        /* Component interrupt service code */

        /* See if TX data buffer is not empty and there is space in TX FIFO */
        while(SPI_Slave_txBufferRead != SPI_Slave_txBufferWrite)
        {
            tmpStatus = SPI_Slave_GET_STATUS_TX(SPI_Slave_swStatusTx);
            SPI_Slave_swStatusTx = tmpStatus;

            if ((SPI_Slave_swStatusTx & SPI_Slave_STS_TX_FIFO_NOT_FULL) != 0u)
            {
                if(SPI_Slave_txBufferFull == 0u)
                {
                   SPI_Slave_txBufferRead++;

                    if(SPI_Slave_txBufferRead >= SPI_Slave_TX_BUFFER_SIZE)
                    {
                        SPI_Slave_txBufferRead = 0u;
                    }
                }
                else
                {
                    SPI_Slave_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(SPI_Slave_TXDATA_PTR, 
                                             SPI_Slave_txBuffer[SPI_Slave_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        /* If Buffer is empty then disable TX FIFO status interrupt until there is data in the buffer */
        if(SPI_Slave_txBufferRead == SPI_Slave_txBufferWrite)
        {
            SPI_Slave_TX_STATUS_MASK_REG &= ((uint8)~SPI_Slave_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* SPI_Slave_TX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START SPI_Slave_ISR_TX_END` */

    /* `#END` */
    
    #ifdef SPI_Slave_TX_ISR_EXIT_CALLBACK
        SPI_Slave_TX_ISR_ExitCallback();
    #endif /* SPI_Slave_TX_ISR_EXIT_CALLBACK */
   }


/*******************************************************************************
* Function Name: SPI_Slave_RX_ISR
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_Slave_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SPI_Slave_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SPI_Slave_rxBuffer[SPI_Slave_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPI_Slave_RX_ISR)
{
    #if(SPI_Slave_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (SPI_Slave_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPI_Slave_RX_ISR_ENTRY_CALLBACK
        SPI_Slave_RX_ISR_EntryCallback();
    #endif /* SPI_Slave_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPI_Slave_RX_ISR_START` */

    /* `#END` */
    
    #if(SPI_Slave_RX_SOFTWARE_BUF_ENABLED)
        tmpStatus = SPI_Slave_GET_STATUS_RX(SPI_Slave_swStatusRx);
        SPI_Slave_swStatusRx = tmpStatus;
        /* See if RX data FIFO has some data and if it can be moved to the RX Buffer */
        while((SPI_Slave_swStatusRx & SPI_Slave_STS_RX_FIFO_NOT_EMPTY) != 0u)
        {
            rxData = CY_GET_REG8(SPI_Slave_RXDATA_PTR);

            /* Set next pointer. */
            SPI_Slave_rxBufferWrite++;
            if(SPI_Slave_rxBufferWrite >= SPI_Slave_RX_BUFFER_SIZE)
            {
                SPI_Slave_rxBufferWrite = 0u;
            }

            if(SPI_Slave_rxBufferWrite == SPI_Slave_rxBufferRead)
            {
                SPI_Slave_rxBufferRead++;
                if(SPI_Slave_rxBufferRead >= SPI_Slave_RX_BUFFER_SIZE)
                {
                    SPI_Slave_rxBufferRead = 0u;
                }
                SPI_Slave_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SPI_Slave_rxBuffer[SPI_Slave_rxBufferWrite] = rxData;

            tmpStatus = SPI_Slave_GET_STATUS_RX(SPI_Slave_swStatusRx);
            SPI_Slave_swStatusRx = tmpStatus;
        }
    #endif /* SPI_Slave_RX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START SPI_Slave_RX_ISR_END` */

    /* `#END` */

    #ifdef SPI_Slave_RX_ISR_EXIT_CALLBACK
        SPI_Slave_RX_ISR_ExitCallback();
    #endif /* SPI_Slave_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */
