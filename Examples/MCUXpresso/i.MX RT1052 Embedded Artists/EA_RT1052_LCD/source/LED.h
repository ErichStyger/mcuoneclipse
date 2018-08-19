/*
 * LED.h
 *
 *  Created on: 06.08.2018
 *      Author: Erich Styger
 */

#ifndef LED_H_
#define LED_H_

#include <stdbool.h>

void LED_On(void);

void LED_Off(void);

void LED_Toggle(void);

bool LED_IsOn(void);

void LED_Init(void);

#endif /* LED_H_ */
