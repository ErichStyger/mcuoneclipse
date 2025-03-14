/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CUBE_H_
#define CUBE_H_

#include "platform.h"
#if PL_CONFIG_USE_NEO_PIXEL_HW

#include "McuShell.h"
#include <stdint.h>
#include "NeoPixel.h"

/* coordinate dimension of cube */
#define CUBE_DIM_X  (NEOC_NOF_LANES) /* number of horizontal lanes */
#define CUBE_DIM_Y  (8) /* number of 'rods' in lane */
#define CUBE_DIM_Z  (4) /* height of each LED rod. Note there are two LEDs for each point */

#define CUBE_EXTENDED_LANE  (NEOC_EXTENDED_LANE) /* if lane is extended into another one */

uint8_t Cube_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Sets a dual-pixel in the LED cube which has two LEDS per pixel position.
 * \param x X position
 * \param y Y position
 * \param z Z position
 * \param color0 color (rgb) of one led
 * \param color1 color (rgb) of other led
 */
void Cube_SetPixelColor(int x, int y, int z, uint32_t color0, uint32_t color1);

bool Cube_RequestUpdateLEDsFromISR(void);
void Cube_RequestUpdateLEDs(void);

void Cube_Init(void);

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */

#endif /* CUBE_H_ */
