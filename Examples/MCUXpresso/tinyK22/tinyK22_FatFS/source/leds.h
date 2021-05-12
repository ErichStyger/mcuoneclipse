/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MY_LEDS_H_
#define MY_LEDS_H_

#include "McuLED.h"

/* led handles */
extern McuLED_Handle_t tinyLED;

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* MY_LEDS_H_ */
