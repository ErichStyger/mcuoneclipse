/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_BLEUART_CMDMODE_H_
#define SOURCES_BLEUART_CMDMODE_H_

#include "McuShell.h"

extern McuShell_ConstStdIOType BLEUART_stdio;
extern uint8_t BLEUART_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

uint8_t BLEUART_CMDMODE_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void BLEUART_CMDMODE_Init(void);

#endif /* SOURCES_BLEUART_CMDMODE_H_ */
