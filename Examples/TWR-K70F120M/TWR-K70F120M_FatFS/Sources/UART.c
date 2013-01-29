/*
 * UART.c
 *
 *  Created on: Jan 29, 2016
 *      Author: User
 */

#include "UART.h"

/*-----------------------------------------------------------------*\
;  FUNCTION:      UART_print
;
;  PARAMETERS:    String to print 
;
;  DESCRIPTION:   Potential infinite loop...update later
;				  Prints over UART 2...update later (option to choose)
;
;  RETURNS:       Nothing
\*-----------------------------------------------------------------*/
void UART_print(char buffer[], int size)
{
	int i = 0;
	while(buffer[i] != '\0' && i<size){
		while(!(UART2_S1 & UART_S1_TDRE_MASK));	// spin while tx data register not empty
		UART2_D = buffer[i];
		i++;
	}
}

void UART_read(){
	char c;
	
	// just wait for a character in order to prevent running while reprogramming
	while(!(UART2_S1 & UART_S1_RDRF_MASK));	// spin
	c = UART2_D;	// read character
}