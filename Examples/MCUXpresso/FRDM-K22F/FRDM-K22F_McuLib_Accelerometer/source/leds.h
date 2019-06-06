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
extern McuLED_Handle_t LED_red, LED_green, LED_blue;

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* LEDS_H_ */
