/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef POWER_H_
#define POWER_H_

#include "power_config.h"

#include "McuShell.h"
uint8_t Power_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void Power_Init(void);

#endif /* POWER_H_ */
