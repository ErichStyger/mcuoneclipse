/*
 * lcd.c
 *
 *  Created on: 08.08.2018
 *      Author: Erich Styger
 */

#include "platform.h"
#if PL_CONFIG_USE_LVGL
#include "lcd.h"
#include "McuGDisplaySSD1306.h"

void LCD_UpdateRegion(int x, int y, int w, int h) {
  McuGDisplaySSD1306_UpdateRegion(x, y, w, h);
  //McuGDisplaySSD1306_UpdateFull();
}
void LCD_SetPixel(int x, int y, int color) {
  McuGDisplaySSD1306_PutPixel(x, y, color);
}

void LCD_Init(void) {
}

void LCD_Deinit(void) {
}

#endif /* PL_CONFIG_USE_LCD */
