/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOSTEPPERRING_H_
#define NEOSTEPPERRING_H_

#include <stdint.h>
#include <stdbool.h>

typedef void *NEOSR_Handle_t;

typedef struct NEOSR_Config_t {
  bool ledCw;      /* if leds are organized cw (clockwise) or ccw (counter-clockwise) */
  int ledLane;     /* LED lane */
  int ledStartPos; /* LED starting position in lane */
  uint8_t ledRed, ledGreen, ledBlue; /* colors */
} NEOSR_Config_t;

void NEOSR_GetDefaultConfig(NEOSR_Config_t *config);

NEOSR_Handle_t NEOSR_InitDevice(NEOSR_Config_t *config);

int32_t NEOSR_GetPos(NEOSR_Handle_t device);

void NEOSR_SetPos(NEOSR_Handle_t device, int32_t pos);
int32_t NEOSR_GetPos(NEOSR_Handle_t device);

void NEOSR_SetRotorColor(NEOSR_Handle_t device, uint8_t red, uint8_t green, uint8_t blue);
void NEOSR_SetRotorPixel(NEOSR_Handle_t device);

void NEOSR_SingleStep(NEOSR_Handle_t device, int step);

void NEOSR_IlluminatePos(int stepperPos, int ledStartPos, int ledLane, bool cw, int ledRed, int ledGreen, int ledBlue);

void NEOSR_Deinit(void);
void NEOSR_Init(void);

#endif /* NEOSTEPPERRING_H_ */
