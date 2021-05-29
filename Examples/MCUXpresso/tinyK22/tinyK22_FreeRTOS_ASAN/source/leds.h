/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "McuLED.h"

/* led handle */
extern McuLED_Handle_t tinyLED;

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* LEDS_H_ */
