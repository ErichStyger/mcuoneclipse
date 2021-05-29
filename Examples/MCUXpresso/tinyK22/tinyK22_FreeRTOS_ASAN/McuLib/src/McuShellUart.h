/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSHELLUART_H_
#define MCUSHELLUART_H_

#include "McuShellUartconfig.h"
#include "McuShell.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t McuShellUart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType McuShellUart_stdio;

void McuShellUart_Deinit(void);
void McuShellUart_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUSHELLUART_H_ */
