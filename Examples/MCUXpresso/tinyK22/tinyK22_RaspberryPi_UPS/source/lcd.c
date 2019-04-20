/*
 * lcd.c
 *
 *  Created on: 08.08.2018
 *      Author: Erich Styger
 */

#include <platform.h>
#if PL_CONFIG_USE_LVGL
#include "lcd.h"
#include "McuGDisplaySSD1306.h"
#include <string.h> /* for memset() */
#include "FreeRTOS.h"
#include "task.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
void LCD_SwitchDisplayBuffer(int idx) {
}

void LCD_SetPixel(int idx, int x, int y, int color) {
//  s_frameBuffer[0][y][x] = color;
}

void LCD_WritePixel(int x, int y, int color) {
//	s_frameBuffer[0][y][x] = color;
}

void LCD_Init(void) {
}
#endif /* PL_CONFIG_USE_LCD */
