/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "McuShell.h"
uint8_t CLOCK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void CLOCK_Init(void);

#endif /* CLOCK_H_ */
