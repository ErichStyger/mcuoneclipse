/*
 * touch.h
 *
 *  Created on: 03.08.2018
 *      Author: Erich Styger
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include <stdbool.h>

int TOUCH_Poll(bool *pressed, int *x, int *y);
void TOUCH_Deinit(void);
void TOUCH_Init(void);

#endif /* TOUCH_H_ */
