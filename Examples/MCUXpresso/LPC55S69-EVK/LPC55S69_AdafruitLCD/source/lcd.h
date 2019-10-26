/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stddef.h>

void LCD_WritePixelData(uint16_t *pixels, size_t nofPixels);

void LCD_SetPixel(int x, int y, int color);

void LCD_UpdateRegion(int x, int y, int w, int h);

void LCD_Init(void);
void LCD_Deinit(void);

#endif /* LCD_H_ */
