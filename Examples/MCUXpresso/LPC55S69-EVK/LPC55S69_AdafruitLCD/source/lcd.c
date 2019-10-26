/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_GUI
#include "lcd.h"
#include "McuILI9341.h"

void LCD_UpdateRegion(int x, int y, int w, int h) {
  /* nothing needed, as we write directly to the display RAM */
}

void LCD_SetWindow(int x, int y, int w, int h) {
  McuILI9341_SetWindow(x, y, w, h);
}

void LCD_WritePixelData(uint16_t *pixels, size_t nofPixels) {
  McuILI9341_WritePixelData(pixels, nofPixels);
}

void LCD_SetPixel(int x, int y, int color) {
  McuILI9341_DrawPixel(x, y, color);
}

void LCD_Init(void) {
}

void LCD_Deinit(void) {
}

#endif /* PL_CONFIG_USE_LCD */
