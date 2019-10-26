/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RASPYGPIO_H_
#define RASPYGPIO_H_

#include "platform.h"
#include <stdbool.h>
#include "McuShell.h"

uint8_t RGPIO_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

void RGPIO_EnableI2CtoRaspy(bool enable);
void RGPIO_SignalPowerdown(void);
void RGPIO_PowerOn(void);

void RGPIO_Deinit(void);
void RGPIO_Init(void);

#endif /* RASPYGPIO_H_ */
