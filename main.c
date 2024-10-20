/*
*	@File        MAIN.C	 		
*	@Author		JOSIMAR PEREIRA LEITE
*	@country	Brazil
*	@Date		20/10/2024
*
*	Copyright (C) 2024  JOSIMAR PEREIRA LEITE
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*/

#include "LM3S3xx.h"

void UART_init(void);
void UART_tx(unsigned char data);

/*************************************** UART ********************************************/

void UART_init(void)
{	
	RCGC1 |= (1UL << 1UL); /* ENABLE UART1 */
	
	RCGC2 |= (1UL << 3UL); /* ENABLE GPIOD */
	
	GPIODFSEL |= ((1UL << 2)|(1UL << 3UL)); /* RX , TX */
		
	UARTCTL &=~(1UL << 0UL); /* DISABLE UART1 */
	
	UARTIBRD = 52; /* 8.000000 / (16 * 9.600) = 0.0520833	*/
	UARTFBRD = 53; /* 0.833 * 64 + 0.5 = 53.812 */
		
	UARTLCRH &=~((1UL << 5UL)|(1UL << 6UL)); /* CLEAR WLEN */
	UARTLCRH |= ((1UL << 5UL)|(1UL << 6UL)); /* SET 8 BITS DATA LENGTH */
		
	UARTLCRH |= (1UL << 4UL); /* ENABLE FIFO */
	
	UARTCTL |=(1UL << 0UL); /* ENABLE UART1 */
}

void UART_tx(unsigned char data)
{
	UARTDR = data;
	while((UARTFR & (1UL << 3UL)) == 1);
}

/*************************************** MAIN ********************************************/

int main (void)
{				
	/* CLEAR CRYSTAL BITS AND SET 8MHZ CRYSTAL OSCILATION */
	RCC &=~((1UL << 6)|(1 << 7UL)|(1UL << 8UL)|(1UL << 9UL));	
	RCC |= ((1UL << 7UL)|(1UL << 8UL)|(1UL << 9UL)); 
	
	/* CLEAR OSCILATION SOURCE AND SET MAIN OSCILATION */
	RCC &=~((1UL << 4UL)|(1UL << 5UL));	
	
	UART_init();
	
	UART_tx('H');
	UART_tx('E');
	UART_tx('L');
	UART_tx('L');
	UART_tx('0');
	UART_tx(' ');
	UART_tx('W');
	UART_tx('O');
	UART_tx('R');
	UART_tx('L');
	UART_tx('D');
	
	while (1)
	{		
		
	}
}
