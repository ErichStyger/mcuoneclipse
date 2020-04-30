/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "platform.h"
#include "matrixconfig.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"
#include "stepper.h"

#if PL_CONFIG_USE_STEPPER_EMUL
  bool MATRIX_GetUpdateRotorLed(void);
  void MATRIX_SetUpdateRotorLed(bool enable);

  void MATRIX_SetRotorColor(int32_t x, int32_t y, int32_t z, uint8_t red, uint8_t green, uint8_t blue);
  void MATRIX_SetRingPixelColor(int32_t x, int32_t y, uint8_t pos, uint8_t red, uint8_t green, uint8_t blue);
  void MATRIX_SetRingColor(int32_t x, int32_t y, uint8_t red, uint8_t green, uint8_t blue);
#endif

uint8_t MATRIX_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

uint8_t MATRIX_MoveAllto12(int32_t timeoutMs, const McuShell_StdIOType *io);
uint8_t MATRIX_DrawAllMoveMode(STEPPER_MoveMode_e mode0, STEPPER_MoveMode_e mode1);
uint8_t MATRIX_DrawAllClockDelays(uint8_t delay0, uint8_t delay1);
uint8_t MATRIX_ShowTime(uint8_t hour, uint8_t minute);

void MATRIX_SetRotorLEDs(void);

void MATRIX_TimerCallback(void);

uint8_t MATRIX_Intermezzo(uint8_t *nr);

void MATRIX_Init(void);

#endif /* MATRIX_H_ */
