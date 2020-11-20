/*******************************************************************************
* File Name: SPI_Slave_PM.c
* Version 2.70
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_Slave_PVT.h"

static SPI_Slave_BACKUP_STRUCT SPI_Slave_backup = 
{
    SPI_Slave_DISABLED,
    SPI_Slave_BITCTR_INIT,
};


/*******************************************************************************
* Function Name: SPI_Slave_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPI_Slave_SaveConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPI_Slave_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SPI_Slave_RestoreConfig(void) 
{

}


/*******************************************************************************
* Function Name: SPI_Slave_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPI Slave Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI_Slave_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_Slave_Sleep(void) 
{
    /* Save components enable state */
    if ((SPI_Slave_TX_STATUS_ACTL_REG & SPI_Slave_INT_ENABLE) != 0u)
    {
        SPI_Slave_backup.enableState = 1u;
    }
    else /* Components block is disabled */
    {
        SPI_Slave_backup.enableState = 0u;
    }

    SPI_Slave_Stop();

}


/*******************************************************************************
* Function Name: SPI_Slave_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI_Slave_backup - used when non-retention registers are restored.
*  SPI_Slave_txBufferWrite - modified every function call - resets to
*  zero.
*  SPI_Slave_txBufferRead - modified every function call - resets to
*  zero.
*  SPI_Slave_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPI_Slave_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI_Slave_Wakeup(void) 
{
    #if (SPI_Slave_TX_SOFTWARE_BUF_ENABLED)
        SPI_Slave_txBufferFull = 0u;
        SPI_Slave_txBufferRead = 0u;
        SPI_Slave_txBufferWrite = 0u;
    #endif /* SPI_Slave_TX_SOFTWARE_BUF_ENABLED */

    #if (SPI_Slave_RX_SOFTWARE_BUF_ENABLED)
        SPI_Slave_rxBufferFull = 0u;
        SPI_Slave_rxBufferRead = 0u;
        SPI_Slave_rxBufferWrite = 0u;
    #endif /* SPI_Slave_RX_SOFTWARE_BUF_ENABLED */

    SPI_Slave_ClearFIFO();

    /* Restore components block enable state */
    if (SPI_Slave_backup.enableState != 0u)
    {
         /* Components block was enabled */
         SPI_Slave_Enable();
    } /* Do nothing if components block was disabled */
}


/* [] END OF FILE */
