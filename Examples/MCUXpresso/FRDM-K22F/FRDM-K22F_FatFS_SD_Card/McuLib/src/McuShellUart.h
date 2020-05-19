/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SHELLUART_H_
#define SHELLUART_H_

#include "McuShellUartconfig.h"
#include "McuShell.h"

extern uint8_t McuShellUart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType McuShellUart_stdio;

void McuShellUart_Deinit(void);
void McuShellUart_Init(void);

#endif /* SHELLUART_H_ */
