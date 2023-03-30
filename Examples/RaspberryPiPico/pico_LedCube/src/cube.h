/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "McuShell.h"

uint8_t Cube_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

bool Cube_RequestUpdateLEDsFromISR(void);
void Cube_RequestUpdateLEDs(void);

void Cube_Init(void);

#endif /* CUBE_H_ */
