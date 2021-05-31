/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RS458UART_H_
#define RS458UART_H_

#include "rs485Uartconfig.h"
#include "McuShell.h"

extern uint8_t RS485Uart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType RS485Uart_stdio;

void RS485Uart_SendString(unsigned char *data);
void RS485Uart_SendBlock(unsigned char *data, size_t dataSize);

void RS458Uart_ClearResponseQueue(void);
uint8_t RS458Uart_GetResponseQueueChar(void);

uint8_t RS485Uart_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void RS485Uart_Deinit(void);
void RS485Uart_Init(void);

#endif /* SHELLUART_H_ */
