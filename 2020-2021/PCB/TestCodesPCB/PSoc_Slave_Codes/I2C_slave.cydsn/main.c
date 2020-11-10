/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

/* 10 byte buffer is used with all bytes having Read/Write Access */

/* EZI2C buffer */
uint8   ezi2cBuffer_1[1];

uint8 count;

int main()
{
	/* Enable global interrupts. */
    CyGlobalIntEnable;
    uint8 check = 0;
	ezi2cBuffer_1[0] = 0;
	/* Start and initialize the EzI2C Buffer */
    EZI2C_Start(); // Even bridge control panel doesnt work
    UART_Putty_Start();
    EZI2C_EzI2CSetBuffer1(1,1, ezi2cBuffer_1);
    
    UART_Putty_UartPutString("I2C Slave started\n\r");
    	
    for(;;)
    {
        /* Place your application code here. */
		
		/* If Master write is complete */
		if(check != ezi2cBuffer_1[0])
        {
            check = ezi2cBuffer_1[0];
		    UART_Putty_UartPutString(" Master has written Data Successfully! \n");
			UART_Putty_UartPutString(" Data Written by Master: \n");
            UART_Putty_UartPutChar(ezi2cBuffer_1[0]);
        }
			
			/* Display the Slave contents */
		/*	for(count=0; count<2; count++)
            {
			UART_Putty_UartPutChar(ezi2cBuffer_1[count]);
            }*/
            
		
        
       // CyDelay(1000);
    }
}
