/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOSTEPPERRING_H_
#define NEOSTEPPERRING_H_

#include <stdint.h>
#include <stdbool.h>
#include "NeoStepperRingConfig.h"

typedef void *NEOSR_Handle_t;

typedef struct NEOSR_Config_t {
  bool ledCw;      /* if LEDs are organized cw (clockwise) or ccw (counter-clockwise) */
  int ledLane;     /* LED lane */
  int ledStartPos; /* LED starting position in lane */
  bool ledOn;      /* if hand LED is on or not */
  uint8_t ledRed, ledGreen, ledBlue; /* colors for hand LED */
} NEOSR_Config_t;

void NEOSR_GetDefaultConfig(NEOSR_Config_t *config);

NEOSR_Handle_t NEOSR_InitDevice(NEOSR_Config_t *config);

void NEOSR_SetRingPixelColor(NEOSR_Handle_t device, uint8_t pos, uint8_t red, uint8_t green, uint8_t blue);
void NEOSR_SetRingColor(NEOSR_Handle_t device, uint8_t red, uint8_t green, uint8_t blue);
void NEOSR_SetRotorColor(NEOSR_Handle_t device, uint8_t red, uint8_t green, uint8_t blue);
void NEOSR_SetRotorPixel(NEOSR_Handle_t device, int32_t stepperPos);

void NEOSR_SetHandLedOn(NEOSR_Handle_t device, bool on);
bool NEOSR_GetHandLedOn(NEOSR_Handle_t device);

void NEOSR_IlluminatePos(int stepperPos, int ledStartPos, int ledLane, bool cw, int ledRed, int ledGreen, int ledBlue);

void NEOSR_Deinit(void);
void NEOSR_Init(void);

#endif /* NEOSTEPPERRING_H_ */
