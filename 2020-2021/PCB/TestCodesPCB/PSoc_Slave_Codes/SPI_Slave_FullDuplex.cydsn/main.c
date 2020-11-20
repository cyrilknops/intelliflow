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

int8 recieve;
int8 print;
char string[1];

const char8 send[] = "PSOC4!";

int flagSPI = 0;

uint8 countTx = 0;
uint8 countRx = 0;

int main()
{
    CyGlobalIntEnable;
    UART_Putty_Start();
    SPI_Slave_Start();
    UART_Putty_UartPutString("Slave read\n\r");
   
    for(;;)
    {
       if(SS_Read() == 0)
       {
            SPI_Slave_WriteTxData(send[countTx]);
            countTx++;
                    
            if(countTx == 6)
            {            
                countTx = 0;
            }
           
            recieve = SPI_Slave_ReadRxData();
            
            if(recieve)
            {
            itoa(recieve,string, 10);
            UART_Putty_UartPutString(string);
            UART_Putty_UartPutCRLF(0);
            }  
            
            CyDelay(500);        
        }      
    }
    
}
       