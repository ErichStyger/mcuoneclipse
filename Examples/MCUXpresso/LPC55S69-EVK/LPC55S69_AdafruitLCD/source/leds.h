/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "McuLED.h"

/* led handles */
extern McuLED_Handle_t LED_Red, LED_Blue, LED_Green;

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* LEDS_H_ */
