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
extern McuLED_Handle_t tinyLED; /* blue LED on tinyK22 */
extern McuLED_Handle_t hatRedLED; /* red LED on HAT */
#if TINYK22_HAT_VERSION < 7  /* no blue LED on HAT v7 */
extern McuLED_Handle_t hatBlueLED; /* blue LED on HAT */
#endif
extern McuLED_Handle_t hatGreenLED; /* green LED on HAT */
extern McuLED_Handle_t hatYellowLED; /* yellow/orange LED on HAT */

void LEDS_Deinit(void);
void LEDS_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* LEDS_H_ */
