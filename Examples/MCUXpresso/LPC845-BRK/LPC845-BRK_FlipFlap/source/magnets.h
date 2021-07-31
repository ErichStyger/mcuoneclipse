/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MAGNETS_H_
#define MAGNETS_H_

#include <stdbool.h>

#define MAG_CONFIG_NOF_MAGNETS   (1) /* number of magnets */

#include "McuShell.h"
uint8_t MAG_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

bool MAG_Triggered(uint8_t magnetIdx);

void MAG_Deinit(void);
void MAG_Init(void);

#endif /* MAGNETS_H_ */
