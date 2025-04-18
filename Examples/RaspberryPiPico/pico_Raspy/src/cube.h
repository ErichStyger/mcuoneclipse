/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "McuShell.h"
#include <stdint.h>
#include "NeoPixel.h"

/* coordinate dimension of cube */
#define CUBE_DIM_X  (NEOC_NOF_LANES) /* number of horizontal lanes */
#define CUBE_DIM_Y  (8) /* number of 'rods' in lane */
#define CUBE_DIM_Z  (4) /* height of each LED rod. Note there are two LEDs for each point */

uint8_t Cube_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void Cube_SetPixelColorDual(int x, int y, int z, uint32_t color0, uint32_t color1);

bool Cube_RequestUpdateLEDsFromISR(void);
void Cube_RequestUpdateLEDs(void);

void Cube_Init(void);

#endif /* CUBE_H_ */
