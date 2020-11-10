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

int main()
{
   
    UART_Putty_Start();
    SPI_Slave_Start();
 
    
    UART_Putty_UartPutString("Slave read\n\r");
   
    for(;;)
    {
        if(SPI_Slave_ReadRxData() != 0)
        {
           
                UART_Putty_UartPutChar(SPI_Slave_ReadByte());
        }
    }
    
}
       