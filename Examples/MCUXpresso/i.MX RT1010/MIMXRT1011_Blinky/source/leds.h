/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "McuLED.h"

/* led handles */
extern McuLED_Handle_t LEDS_Led;

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* LEDS_H_ */
