/*
 * UART.h
 *
 *  Created on: Jan 29, 2016
 *      Author: User
 */

#ifndef UART_H_
#define UART_H_

#include "IO_Map.h"

#define U2_print(str)	UART_print(str, strlen(str))

void UART_print(char buffer[], int size);
void UART_read(void);


#endif /* UART_H_ */
