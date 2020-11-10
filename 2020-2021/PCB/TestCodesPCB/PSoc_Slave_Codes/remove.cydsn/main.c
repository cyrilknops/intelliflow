/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  This is source code for example project of the SCB in SPI
*  (Master, Slave) modes.
*  Parameters used:
*   Mode               (CPHA = 0, CPOL = 0)
*   Bit order           MSB First
*   TX/RX data bits     8 
*   TX/RX buffer size   16
*   Data rate           1Mbit/s
*
*  SCB in SPI mode communication test using software buffer. 
*  16 bytes are transmitted between SPI Master and SPI Slave.
*  Received data are displayed on LCD. 
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include "project.h"
#include <stdlib.h>

static int  data[12];

int main()
{
    uint8 i = 0u;
    uint8 b = 0u;
    
    int data2[8];
    int test;
    float test2;
    
    CyGlobalIntEnable;
    char string[30];
    char string2[30];
    UART_Start();
   
    SPI_Slave_Start();
   
    //SPIM_ClearMasterInterruptSource(SPIM_INTR_MASTER_SPI_DONE);
     
    /* Writing data into the SPIM software buffer */
    /*SPIM_SpiUartWriteTxData(0x99u);
    SPIM_SpiUartWriteTxData(0xAAu);
    SPIM_SpiUartWriteTxData(0xBBu);
    SPIM_SpiUartWriteTxData(0xCCu);
    SPIM_SpiUartWriteTxData(0xDDu);
    SPIM_SpiUartWriteTxData(0xEEu);
    SPIM_SpiUartWriteTxData(0xFFu);
    SPIM_SpiUartWriteTxData(0x12u);*/
    

    /* 
    * We need to know the moment when SPI communication is completed
    * to display received data. SPIM_INTR_MASTER_SPI_DONE status should be polled. 
    */
    
   UART_UartPutString("Slave read\n\r");
    int index = 0;
   /*while(0u == (SPIS_GetMasterInterruptSource() & SPIS_INTR_MASTER_SPI_DONE))
    {
        data[index] = SPIS_SpiUartReadRxData();  
        index++;
        if(index == 7)
        {
        break;
        }
    }
    index = 0;*/
    /* SPI communication is complete so we can display received data */
    
    for(;;)
        {
               
    /*SPIS_SpiUartWriteTxData(0x11u);
    SPIS_SpiUartWriteTxData(0x22u);
    SPIS_SpiUartWriteTxData(0x33u);
    SPIS_SpiUartWriteTxData(0x44u);
    SPIS_SpiUartWriteTxData(0x55u);
    SPIS_SpiUartWriteTxData(0x66u);
    SPIS_SpiUartWriteTxData(0x77u);
    SPIS_SpiUartWriteTxData(0x88u);*/
            
        if(SPI_Slave_SpiUartReadRxData() != 0)
        {
          UART_UartPutString("Recieved = \n\r");
          for(i=0u; i<=8u; i++)
            {           
                data[i] = SPI_Slave_SpiUartReadRxData();  
                itoa(data[i],string,10);
                UART_UartPutString(string);
                UART_UartPutString("\n\r");
            }
       /*  for(b=0u; b<=8u; b++)
            {          
                IDAC_SetValue(data[b]);
                test = ADC_GetResult16(0);
                test2 = ADC_CountsTo_mVolts(0,test);
                itoa(test2,string2,10);
                UART_UartPutString("Analoge waarde : ");
                UART_UartPutString(string2);
                UART_UartPutString("\n\r");
            }*/
         }
        CyDelay(1000);
        }
}