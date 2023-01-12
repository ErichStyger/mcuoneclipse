/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LIGHTS_H_
#define LIGHTS_H_

#include "McuShell.h"
#include <stdbool.h>
#include <stdint.h>

void Lights_SetColor(uint32_t color);
uint32_t Lights_GetColor(void);

void Lights_SetBrightnessPercent(uint8_t percent);
uint8_t Lights_GetBrightnessPercent(void);

bool Lights_GetLightIsOn(void);
void Lights_SetLightIsOn(bool on);

uint8_t Lights_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void Lights_Init(void);

#endif /* LIGHTS_H_ */
