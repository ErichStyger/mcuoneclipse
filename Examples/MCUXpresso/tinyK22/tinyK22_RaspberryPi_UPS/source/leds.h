/*
 * leds.h
 *
 *  Created on: 28.03.2019
 *      Author: Erich Styger
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "SuperDuperLedDriverOfTheWorld.h"

/* led handles */
extern SDLED_Handle_t tinyLED, hatRedLED, hatBlueLED, hatGreenLED, hatYellowLED;;

void LEDS_Deinit(void);
void LEDS_Init(void);

#endif /* LEDS_H_ */
