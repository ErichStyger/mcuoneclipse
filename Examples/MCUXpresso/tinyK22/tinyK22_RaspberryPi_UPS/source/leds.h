/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "McuLED.h"
#ifdef __cplusplus
extern "C" {
#endif

/* led handles */
extern McuLED_Handle_t tinyLED, hatRedLED, hatBlueLED, hatGreenLED, hatYellowLED;

void LEDS_Deinit(void);
void LEDS_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* LEDS_H_ */
