/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FLIPDOT_H_
#define FLIPDOT_H_

#include "McuShell.h"
#include <stdint.h>

uint8_t FlipDot_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void FlipDot_DrawTime3x5(int x0, int y0, uint8_t hour, uint8 minute);

void FlipDot_DrawDate3x5(int x0, int y0, uint8_t day, uint8 month, uint16_t year);

void FlipDot_ClearAllDots(void);
void FlipDot_SetAllDots(void);
void FlipDot_SendDots(void);

void FlipDot_Test(void);

void FlipDot_Init(void);

#endif /* FLIPDOT_H_ */
