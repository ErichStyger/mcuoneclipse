/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "platform.h"
#include "McuLED.h"

/* led handles */
#if PL_BOARD_IS_TINYK22
  extern McuLED_Handle_t blueLED;
#else
  extern McuLED_Handle_t redLED, blueLED, greenLED;
#endif

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* LEDS_H_ */
