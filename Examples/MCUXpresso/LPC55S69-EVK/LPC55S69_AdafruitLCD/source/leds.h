/*
 * leds.h
 *
 *  Created on: 28.03.2019
 *      Author: Erich Styger
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "McuLED.h"

/* led handles */
extern McuLED_Handle_t LED_Red, LED_Blue, LED_Green;

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* LEDS_H_ */
