/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SHELL_H_
#define SHELL_H_

#include "McuShell.h"
#include <stdbool.h>

void SHELL_SendString(unsigned char *str);
void SHELL_SendChar(unsigned char ch);

uint8_t SHELL_ParseCommand(const unsigned char *command, McuShell_ConstStdIOType *io, bool silent);

void SHELL_Init(void);
void SHELL_Deinit(void);

#endif /* SHELL_H_ */
