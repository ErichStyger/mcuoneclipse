/*
 * lcd.h
 *
 *  Created on: 08.08.2018
 *      Author: Erich Styger
 */

#ifndef LCD_H_
#define LCD_H_

#define LCD_DISPLAY_HEIGHT 		(272)
#define LCD_DISPLAY_WIDTH 		(480)

void LCD_SetPixel(int idx, int x, int y, int color);

void LCD_SwitchDisplayBuffer(int idx);

void LCD_Init(void);

#endif /* LCD_H_ */
