/*
 * lcd.h
 *
 *  Created on: 08.08.2018
 *      Author: Erich Styger
 */

#ifndef LCD_H_
#define LCD_H_

#include "McuSSD1306.h"

/* configuration settings for lv_conf.h: */
#define LCD_LV_DISPLAY_HEIGHT 		(McuSSD1306_HW_SHORTER_SIDE)
#define LCD_LV_DISPLAY_WIDTH 		(McuSSD1306_HW_LONGER_SIDE)
#define LCD_LV_COLOR_DEPTH          (1)
#define LCD_LV_DPI                  (25)

void LCD_WritePixel(int x, int y, int color);

void LCD_SetPixel(int idx, int x, int y, int color);

void LCD_SwitchDisplayBuffer(int idx);

void LCD_Init(void);

#endif /* LCD_H_ */
