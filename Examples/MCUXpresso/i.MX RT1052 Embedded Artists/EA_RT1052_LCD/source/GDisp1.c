/*
 * GDisp1.c
 *
 *  Created on: 19.07.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "GDisp1.h"
#include "lcd.h"

#if PL_CONFIG_USE_LCD_DOUBLE_BUFFER
static uint32_t frameBufferIndex = 0;
#endif

void GDisp1_PutPixel(unsigned int x, unsigned int y, uint16_t color) {
#if PL_CONFIG_USE_LCD_DOUBLE_BUFFER
	LCD_SetPixel(frameBufferIndex, x,y, color);
#else
	LCD_SetPixel(0, x,y, color);
#endif
}

void GDisp1_UpdateFull(void) {
#if PL_CONFIG_USE_LCD_DOUBLE_BUFFER
	LCD_SwitchDisplayBuffer(frameBufferIndex);
    frameBufferIndex ^= 1U;
#endif
}
