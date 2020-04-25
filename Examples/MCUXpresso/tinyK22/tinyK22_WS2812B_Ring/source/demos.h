/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DEMOS_H_
#define DEMOS_H_

#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

uint8_t DEMO_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void DEMO_Init(void);

#endif /* DEMOS_H_ */
