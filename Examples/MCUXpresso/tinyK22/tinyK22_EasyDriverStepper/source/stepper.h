/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include "McuShell.h"

uint8_t STEPPER_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

void STEPPER_Deinit(void);
void STEPPER_Init(void);

#endif /* STEPPER_H_ */
