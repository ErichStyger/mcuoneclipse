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

/*! Default McuShell buffer */
extern uint8_t McuShellUart_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

/*! Standard I/O for input/output */
extern McuShell_ConstStdIOType McuShellUart_stdio;

/*!
 * \brief Module de-initialization
 */
void McuShellUart_Deinit(void);

/*!
 * \brief Module initialization
 */
void McuShellUart_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUSHELLUART_H_ */
