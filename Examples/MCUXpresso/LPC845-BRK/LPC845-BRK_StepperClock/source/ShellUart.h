/*
 * ShellUart.h
 *
 *  Created on: 31.07.2019
 *      Author: Erich Styger
 */

#ifndef SHELLUART_H_
#define SHELLUART_H_

#include "McuShell.h"

extern uint8_t ShellUart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType ShellUart_stdio;

void ShellUart_Deinit(void);

void ShellUart_Init(void);


#endif /* SHELLUART_H_ */
