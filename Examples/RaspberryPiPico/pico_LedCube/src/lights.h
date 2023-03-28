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

/*!
 * \brief Setting lights directly, without storing value in NVMC
 * \param color (W)RGB color information
 */
void Lights_SetLed(uint32_t color);

void Lights_SetColor(uint32_t color);
uint32_t Lights_GetColor(void);

void Lights_SetBrightnessPercent(uint8_t percent);
uint8_t Lights_GetBrightnessPercent(void);
uint8_t Lights_GetBrightnessValue(void);

bool Lights_GetLightIsOn(void);
void Lights_SetLightIsOn(bool on);

/*!
 * \brief Suspends the light task
 */
void Lights_Suspend(void);

/*!
 * \brief Resumes the light task
 */
void Lights_Resume(void);

/*!
 * \brief Used to store the light values to flash, used for delayed and reduced storage.
 */
void Lights_StoreValues(void);

uint8_t Lights_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void Lights_Init(void);

#endif /* LIGHTS_H_ */
