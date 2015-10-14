/*
 * lcd.h
 *
 *  Created on: Nov 2, 2012
 *      Author: Erich Styger
 */

#ifndef LCD_H_
#define LCD_H_

#include "TCHS1.h"

void LCD_Run(void);

void OnTouch(TCHS1_TouchScreenEvent event, TCHS1_PixelDim x, TCHS1_PixelDim y);


#endif /* LCD_H_ */
