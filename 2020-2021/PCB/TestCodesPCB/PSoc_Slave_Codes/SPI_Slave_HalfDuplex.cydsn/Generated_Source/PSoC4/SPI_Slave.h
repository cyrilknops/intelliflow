/*******************************************************************************
* File Name: SPI_Slave.h
* Version 2.70
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Slave Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIS_SPI_Slave_H)
#define CY_SPIS_SPI_Slave_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define SPI_Slave_DATA_WIDTH                  (8u)
#define SPI_Slave_INTERNAL_TX_INT_ENABLED     (0u)
#define SPI_Slave_INTERNAL_RX_INT_ENABLED     (1u)
#define SPI_Slave_MODE_USE_ZERO               (1u)
#define SPI_Slave_BIDIRECTIONAL_MODE          (1u)
#define SPI_Slave_MODE                        (0u)

#define SPI_Slave_FIFO_SIZE                  (4u)
/* Internal interrupt handling */
#define SPI_Slave_TX_BUFFER_SIZE             (4u)
#define SPI_Slave_RX_BUFFER_SIZE             (4u)
#define SPI_Slave_INTERNAL_TX_INT_ENABLED    (0u)
#define SPI_Slave_INTERNAL_RX_INT_ENABLED    (1u)

#define SPI_Slave_TX_SOFTWARE_BUF_ENABLED    ((0u != SPI_Slave_INTERNAL_TX_INT_ENABLED) && \
                                                     (SPI_Slave_TX_BUFFER_SIZE > SPI_Slave_FIFO_SIZE))

#define SPI_Slave_RX_SOFTWARE_BUF_ENABLED    ((0u != SPI_Slave_INTERNAL_RX_INT_ENABLED) && \
                                                     (SPI_Slave_RX_BUFFER_SIZE > SPI_Slave_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
} SPI_Slave_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  SPI_Slave_Init(void) ;
void  SPI_Slave_Enable(void) ;
void  SPI_Slave_Start(void) ;
void  SPI_Slave_Stop(void) ;
void  SPI_Slave_EnableTxInt(void) ;
void  SPI_Slave_EnableRxInt(void) ;
void  SPI_Slave_DisableTxInt(void) ;
void  SPI_Slave_DisableRxInt(void) ;
void  SPI_Slave_SetTxInterruptMode(uint8 intSrc) ;
void  SPI_Slave_SetRxInterruptMode(uint8 intSrc) ;
uint8 SPI_Slave_ReadTxStatus(void) ;
uint8 SPI_Slave_ReadRxStatus(void) ;
void  SPI_Slave_WriteTxData(uint8 txData);

#if(SPI_Slave_MODE_USE_ZERO != 0u)
    void  SPI_Slave_WriteTxDataZero(uint8 txDataByte) \
                                              ;
#endif /* (SPI_Slave_MODE_USE_ZERO != 0u) */

uint8 SPI_Slave_ReadRxData(void) ;
uint8 SPI_Slave_GetRxBufferSize(void) ;
uint8 SPI_Slave_GetTxBufferSize(void) ;
void  SPI_Slave_ClearRxBuffer(void) ;
void  SPI_Slave_ClearTxBuffer(void) ;

#if (SPI_Slave_BIDIRECTIONAL_MODE != 0u)
    void  SPI_Slave_TxEnable(void) ;
    void  SPI_Slave_TxDisable(void) ;
#endif /* SPI_Slave_BIDIRECTIONAL_MODE != 0u */

void  SPI_Slave_PutArray(const uint8 buffer[], uint8 byteCount) ;
void  SPI_Slave_ClearFIFO(void) ;
void  SPI_Slave_Sleep(void) ;
void  SPI_Slave_Wakeup(void) ;
void  SPI_Slave_SaveConfig(void) ;
void  SPI_Slave_RestoreConfig(void) ;

/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_Slave) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    SPI_Slave_CyBtldrCommStart(void) CYSMALL ;
    void    SPI_Slave_CyBtldrCommStop(void) CYSMALL ;
    void    SPI_Slave_CyBtldrCommReset(void) CYSMALL ;
    cystatus SPI_Slave_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus SPI_Slave_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_Slave)
        #define CyBtldrCommStart    SPI_Slave_CyBtldrCommStart
        #define CyBtldrCommStop     SPI_Slave_CyBtldrCommStop
        #define CyBtldrCommReset    SPI_Slave_CyBtldrCommReset
        #define CyBtldrCommWrite    SPI_Slave_CyBtldrCommWrite
        #define CyBtldrCommRead     SPI_Slave_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_Slave) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define SPI_Slave_BYTE2BYTE_TIME_OUT (1u)

#endif /* (CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_Slave) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


CY_ISR_PROTO(SPI_Slave_TX_ISR);
CY_ISR_PROTO(SPI_Slave_RX_ISR);

/* Macros for getting software status of SPIS Statusi Register */
#define SPI_Slave_GET_STATUS_TX(swTxSts) ( (uint8)(SPI_Slave_TX_STATUS_REG | \
                                                       ((swTxSts) & SPI_Slave_STS_CLR_ON_RD_BYTES_MASK)) )
#define SPI_Slave_GET_STATUS_RX(swRxSts) ( (uint8)(SPI_Slave_RX_STATUS_REG | \
                                                       ((swRxSts) & SPI_Slave_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 SPI_Slave_initVar;


/***************************************
*           API Constants
***************************************/

#define SPI_Slave_TX_ISR_NUMBER     ((uint8)SPI_Slave_TxInternalInterrupt__INTC_NUMBER)
#define SPI_Slave_RX_ISR_NUMBER     ((uint8)SPI_Slave_RxInternalInterrupt__INTC_NUMBER)
#define SPI_Slave_TX_ISR_PRIORITY   ((uint8)SPI_Slave_TxInternalInterrupt__INTC_PRIOR_NUM)
#define SPI_Slave_RX_ISR_PRIORITY   ((uint8)SPI_Slave_RxInternalInterrupt__INTC_PRIOR_NUM)


/***************************************
*    Initial Parameter Constants
***************************************/

#define SPI_Slave_INT_ON_SPI_DONE    (uint8)(0u << SPI_Slave_STS_SPI_DONE_SHIFT)
#define SPI_Slave_INT_ON_TX_EMPTY    (uint8)(0u << SPI_Slave_STS_TX_FIFO_EMPTY_SHIFT)
#define SPI_Slave_INT_ON_TX_NOT_FULL (uint8)(0u << SPI_Slave_STS_TX_FIFO_NOT_FULL_SHIFT)
#define SPI_Slave_INT_ON_BYTE_COMP   (uint8)(0u << SPI_Slave_STS_BYTE_COMPLETE_SHIFT)

#define SPI_Slave_TX_INIT_INTERRUPTS_MASK  (SPI_Slave_INT_ON_SPI_DONE | \
                                            SPI_Slave_INT_ON_TX_EMPTY | SPI_Slave_INT_ON_TX_NOT_FULL | \
                                            SPI_Slave_INT_ON_BYTE_COMP)

#define SPI_Slave_INT_ON_RX_EMPTY     (uint8)(0u << SPI_Slave_STS_RX_FIFO_EMPTY_SHIFT)
#define SPI_Slave_INT_ON_RX_NOT_EMPTY (uint8)(0u << SPI_Slave_STS_RX_FIFO_NOT_EMPTY_SHIFT)
#define SPI_Slave_INT_ON_RX_OVER      (uint8)(0u << SPI_Slave_STS_RX_FIFO_OVERRUN_SHIFT)
#define SPI_Slave_INT_ON_RX_FULL      (uint8)(0u << SPI_Slave_STS_RX_FIFO_FULL_SHIFT)

#define SPI_Slave_RX_INIT_INTERRUPTS_MASK (SPI_Slave_INT_ON_RX_EMPTY | \
                                            SPI_Slave_INT_ON_RX_NOT_EMPTY | SPI_Slave_INT_ON_RX_OVER | \
                                            SPI_Slave_INT_ON_RX_FULL)

#define SPI_Slave_BITCTR_INIT           (SPI_Slave_DATA_WIDTH - 1u)

#define SPI_Slave__MODE_00 0
#define SPI_Slave__MODE_01 1
#define SPI_Slave__MODE_10 2
#define SPI_Slave__MODE_11 3


#define SPI_Slave_TX_BUFFER_SIZE         (4u)
#define SPI_Slave_RX_BUFFER_SIZE         (4u)

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define SPI_Slave_INIT_INTERRUPTS_MASK  (SPI_Slave_INT_ON_SPI_DONE | SPI_Slave_INT_ON_TX_EMPTY | \
                                            SPI_Slave_INT_ON_TX_NOT_FULL | SPI_Slave_INT_ON_RX_EMPTY | \
                                            SPI_Slave_INT_ON_RX_NOT_EMPTY | SPI_Slave_INT_ON_RX_OVER | \
                                            SPI_Slave_INT_ON_BYTE_COMP)


/***************************************
*             Registers
***************************************/
#if(CY_PSOC3 || CY_PSOC5)
    #define SPI_Slave_TXDATA_ZERO_REG          (* (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_Slave_TXDATA_ZERO_PTR           (  (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_Slave_RXDATA_ZERO_REG           (* (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_Slave_RXDATA_ZERO_PTR           (  (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_Slave_TXDATA_REG                (* (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__F0_REG)

    #define SPI_Slave_TXDATA_PTR                (  (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__F0_REG)

    #define SPI_Slave_RXDATA_REG                (* (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__F1_REG)

    #define SPI_Slave_RXDATA_PTR                (  (reg8  *) \
            SPI_Slave_BSPIS_sR8_Dp_u0__F1_REG)
#else
    #if(SPI_Slave_DATA_WIDTH <= 8u) /* 8bit - SPIS */
        #define SPI_Slave_TXDATA_ZERO_REG           (* (reg8 *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_Slave_TXDATA_ZERO_PTR           (  (reg8  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_Slave_RXDATA_ZERO_REG           (* (reg8  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_Slave_RXDATA_ZERO_PTR           (  (reg8 *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_Slave_TXDATA_REG                (* (reg8  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__F0_REG)

        #define SPI_Slave_TXDATA_PTR                (  (reg8  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__F0_REG)

        #define SPI_Slave_RXDATA_REG                (* (reg8  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__F1_REG)

        #define SPI_Slave_RXDATA_PTR                (  (reg8  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__F1_REG)
    #else /* 16bit - SPIS */
        #define SPI_Slave_TXDATA_ZERO_REG           (* (reg16  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_Slave_TXDATA_ZERO_PTR           (  (reg16  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_Slave_RXDATA_ZERO_REG           (* (reg16  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_Slave_RXDATA_ZERO_PTR           (  (reg16  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_Slave_TXDATA_REG                (* (reg16  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define SPI_Slave_TXDATA_PTR                (  (reg16  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define SPI_Slave_RXDATA_REG                (* (reg16  *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_F1_REG)

        #define SPI_Slave_RXDATA_PTR                (  (reg16 *) \
                SPI_Slave_BSPIS_sR8_Dp_u0__16BIT_F1_REG)
    #endif /* (SPI_Slave_DATA_WIDTH <= 8u) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define SPI_Slave_TX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        SPI_Slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPI_Slave_TX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        SPI_Slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#define SPI_Slave_RX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        SPI_Slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPI_Slave_RX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        SPI_Slave_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(SPI_Slave_DATA_WIDTH > 8u)

    #define SPI_Slave_TX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            SPI_Slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPI_Slave_TX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            SPI_Slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

    #define SPI_Slave_RX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            SPI_Slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPI_Slave_RX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            SPI_Slave_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

#endif /* SPI_Slave_DATA_WIDTH > 8u */


#define SPI_Slave_COUNTER_PERIOD_REG    (* (reg8 *) \
        SPI_Slave_BSPIS_BitCounter__PERIOD_REG)
#define SPI_Slave_COUNTER_PERIOD_PTR    (  (reg8 *) \
        SPI_Slave_BSPIS_BitCounter__PERIOD_REG)

#define SPI_Slave_TX_STATUS_MASK_REG    (* (reg8 *) \
        SPI_Slave_BSPIS_TxStsReg__MASK_REG)
#define SPI_Slave_TX_STATUS_MASK_PTR    (  (reg8 *) \
        SPI_Slave_BSPIS_TxStsReg__MASK_REG)

#define SPI_Slave_RX_STATUS_MASK_REG    (* (reg8 *) \
        SPI_Slave_BSPIS_RxStsReg__MASK_REG)
#define SPI_Slave_RX_STATUS_MASK_PTR    (  (reg8 *) \
        SPI_Slave_BSPIS_RxStsReg__MASK_REG)

#define SPI_Slave_ONE_REG               (* (reg8 *) \
        SPI_Slave_BSPIS_SPISlave_dpCounter_u0__D1_REG)
#define SPI_Slave_ONE_PTR               (  (reg8 *) \
        SPI_Slave_BSPIS_dpCounter_u0__D1_REG)

#define SPI_Slave_TX_STATUS_REG         (* (reg8 *) \
        SPI_Slave_BSPIS_TxStsReg__STATUS_REG)
#define SPI_Slave_TX_STATUS_PTR         (  (reg8 *) \
        SPI_Slave_BSPIS__TxStsReg__STATUS_REG)

#define SPI_Slave_RX_STATUS_REG         (* (reg8 *) \
        SPI_Slave_BSPIS_RxStsReg__STATUS_REG)
#define SPI_Slave_RX_STATUS_PTR         (  (reg8 *) \
        SPI_Slave_BSPIS_RxStsReg__STATUS_REG)

#define SPI_Slave_COUNTER_CONTROL_REG   (* (reg8 *) \
        SPI_Slave_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)
#define SPI_Slave_COUNTER_CONTROL_PTR   (  (reg8 *) \
        SPI_Slave_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)

#define SPI_Slave_TX_STATUS_ACTL_REG    (* (reg8 *) \
        SPI_Slave_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)
#define SPI_Slave_TX_STATUS_ACTL_PTR    (  (reg8 *) \
        SPI_Slave_TX_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)

#define SPI_Slave_RX_STATUS_ACTL_REG    (* (reg8 *) \
        SPI_Slave_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)
#define SPI_Slave_RX_STATUS_ACTL_PTR    (  (reg8 *) \
        SPI_Slave_RX_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)

#if(SPI_Slave_BIDIRECTIONAL_MODE)

    #define SPI_Slave_CONTROL_REG       (* (reg8 *) \
   SPI_Slave_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)
    #define SPI_Slave_CONTROL_PTR       (  (reg8 *) \
   SPI_Slave_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)

#endif /* SPI_Slave_BIDIRECTIONAL_MODE */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define SPI_Slave_STS_SPI_DONE_SHIFT             (0x00u)
#define SPI_Slave_STS_TX_FIFO_NOT_FULL_SHIFT     (0x01u)
#define SPI_Slave_STS_TX_FIFO_EMPTY_SHIFT        (0x02u)
#define SPI_Slave_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x03u)
#define SPI_Slave_STS_RX_FIFO_EMPTY_SHIFT        (0x04u)
#define SPI_Slave_STS_RX_FIFO_OVERRUN_SHIFT      (0x05u)
#define SPI_Slave_STS_RX_FIFO_FULL_SHIFT         (0x06u)
#define SPI_Slave_STS_BYTE_COMPLETE_SHIFT        (0x06u)

#define SPI_Slave_STS_SPI_DONE                   ((uint8)(0x01u << SPI_Slave_STS_SPI_DONE_SHIFT))
#define SPI_Slave_STS_TX_FIFO_EMPTY              ((uint8)(0x01u << SPI_Slave_STS_TX_FIFO_EMPTY_SHIFT))
#define SPI_Slave_STS_TX_FIFO_NOT_FULL           ((uint8)(0x01u << SPI_Slave_STS_TX_FIFO_NOT_FULL_SHIFT))
#define SPI_Slave_STS_RX_FIFO_EMPTY              ((uint8)(0x01u << SPI_Slave_STS_RX_FIFO_EMPTY_SHIFT))
#define SPI_Slave_STS_RX_FIFO_NOT_EMPTY          ((uint8)(0x01u << SPI_Slave_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define SPI_Slave_STS_RX_FIFO_OVERRUN            ((uint8)(0x01u << SPI_Slave_STS_RX_FIFO_OVERRUN_SHIFT))
#define SPI_Slave_STS_RX_FIFO_FULL               ((uint8)(0x01u << SPI_Slave_STS_RX_FIFO_FULL_SHIFT))
#define SPI_Slave_STS_BYTE_COMPLETE              ((uint8)(0x01u << SPI_Slave_STS_BYTE_COMPLETE_SHIFT))

#define SPI_Slave_STS_CLR_ON_RD_BYTES_MASK       (0x61u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define SPI_Slave_INT_ENABLE                     (0x10u)
#define SPI_Slave_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define SPI_Slave_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define SPI_Slave_FIFO_CLR       (SPI_Slave_TX_FIFO_CLR | SPI_Slave_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define SPI_Slave_CNTR_ENABLE                    (0x20u)

/* Bi-Directional mode control bit */
#define SPI_Slave_CTRL_TX_SIGNAL_EN              (0x01u)

/* Datapath Auxillary Control Register definitions */
#define SPI_Slave_AUX_CTRL_FIFO0_CLR             (0x00u)
#define SPI_Slave_AUX_CTRL_FIFO1_CLR             (0x00u)
#define SPI_Slave_AUX_CTRL_FIFO0_LVL             (0x00u)
#define SPI_Slave_AUX_CTRL_FIFO1_LVL             (0x00u)
#define SPI_Slave_STATUS_ACTL_INT_EN_MASK        (0x10u)

/* Component disabled */
#define SPI_Slave_DISABLED   (0u)

/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define SPI_Slave_TXDATA_ZERO               (SPI_Slave_TXDATA_ZERO_REG)
#define SPI_Slave_TXDATA                    (SPI_Slave_TXDATA_REG)
#define SPI_Slave_RXDATA                    (SPI_Slave_RXDATA_REG)
#define SPI_Slave_MISO_AUX_CONTROLDP0       (SPI_Slave_MISO_AUX_CTRL_DP0_REG)
#define SPI_Slave_MOSI_AUX_CONTROLDP0       (SPI_Slave_MOSI_AUX_CTRL_DP0_REG)
#define SPI_Slave_TXBUFFERREAD              (SPI_Slave_txBufferRead)
#define SPI_Slave_TXBUFFERWRITE             (SPI_Slave_txBufferWrite)
#define SPI_Slave_RXBUFFERREAD              (SPI_Slave_rxBufferRead)
#define SPI_Slave_RXBUFFERWRITE             (SPI_Slave_rxBufferWrite)

#if(SPI_Slave_DATA_WIDTH > 8u)

    #define SPI_Slave_MISO_AUX_CONTROLDP1   (SPI_Slave_MISO_AUX_CTRL_DP1_REG)
    #define SPI_Slave_MOSI_AUX_CONTROLDP1   (SPI_Slave_MOSI_AUX_CTRL_DP0_REG)

#endif /* SPI_Slave_DATA_WIDTH > 8u */

#define SPI_Slave_COUNTER_PERIOD            (SPI_Slave_COUNTER_PERIOD_REG)
#define SPI_Slave_COUNTER_CONTROL           (SPI_Slave_COUNTER_CONTROL_REG)
#define SPI_Slave_ONE                       (SPI_Slave_ONE_REG)
#define SPI_Slave_STATUS                    (SPI_Slave_TX_STATUS_REG)
#define SPI_Slave_STATUS_MASK               (SPI_Slave_TX_STATUS_MASK_REG)
#define SPI_Slave_STATUS_ACTL               (SPI_Slave_TX_STATUS_ACTL_REG)

#define SPI_Slave_WriteByte      (SPI_Slave_WriteTxData)
#define SPI_Slave_ReadByte       (SPI_Slave_ReadRxData)
#define SPI_Slave_WriteByteZero  (SPI_Slave_WriteTxDataZero)
void  SPI_Slave_SetInterruptMode(uint8 intSrc) ;
uint8 SPI_Slave_ReadStatus(void) ;
void  SPI_Slave_EnableInt(void) ;
void  SPI_Slave_DisableInt(void) ;

#define SPI_Slave_STS_TX_BUF_NOT_FULL_SHIFT      (0x01u)
#define SPI_Slave_STS_TX_BUF_FULL_SHIFT          (0x02u)
#define SPI_Slave_STS_RX_BUF_NOT_EMPTY_SHIFT     (0x03u)
#define SPI_Slave_STS_RX_BUF_EMPTY_SHIFT         (0x04u)
#define SPI_Slave_STS_RX_BUF_OVERRUN_SHIFT       (0x05u)

#define SPI_Slave_STS_TX_BUF_NOT_FULL            ((uint8)(0x01u << SPI_Slave_STS_TX_BUF_NOT_FULL_SHIFT))
#define SPI_Slave_STS_TX_BUF_FULL                ((uint8)(0x01u << SPI_Slave_STS_TX_BUF_FULL_SHIFT))
#define SPI_Slave_STS_RX_BUF_NOT_EMPTY           ((uint8)(0x01u << SPI_Slave_STS_RX_BUF_NOT_EMPTY_SHIFT))
#define SPI_Slave_STS_RX_BUF_EMPTY               ((uint8)(0x01u << SPI_Slave_STS_RX_BUF_EMPTY_SHIFT))
#define SPI_Slave_STS_RX_BUF_OVERRUN             ((uint8)(0x01u << SPI_Slave_STS_RX_BUF_OVERRUN_SHIFT))

#define SPI_Slave_DataWidth                  (SPI_Slave_DATA_WIDTH)
#define SPI_Slave_InternalClockUsed          (SPI_Slave_INTERNAL_CLOCK)
#define SPI_Slave_InternalTxInterruptEnabled (SPI_Slave_INTERNAL_TX_INT_ENABLED)
#define SPI_Slave_InternalRxInterruptEnabled (SPI_Slave_INTERNAL_RX_INT_ENABLED)
#define SPI_Slave_ModeUseZero                (SPI_Slave_MODE_USE_ZERO)
#define SPI_Slave_BidirectionalMode          (SPI_Slave_BIDIRECTIONAL_MODE)
#define SPI_Slave_Mode                       (SPI_Slave_MODE)
#define SPI_Slave_DATAWIDHT                  (SPI_Slave_DATA_WIDTH)
#define SPI_Slave_InternalInterruptEnabled   (0u)

#define SPI_Slave_TXBUFFERSIZE   (SPI_Slave_TX_BUFFER_SIZE)
#define SPI_Slave_RXBUFFERSIZE   (SPI_Slave_RX_BUFFER_SIZE)

#define SPI_Slave_TXBUFFER       SPI_Slave_txBuffer
#define SPI_Slave_RXBUFFER       SPI_Slave_rxBuffer

#endif  /* CY_SPIS_SPI_Slave_H */

/* [] END OF FILE */
