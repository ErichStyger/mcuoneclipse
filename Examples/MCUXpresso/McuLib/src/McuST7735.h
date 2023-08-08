/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUST7735_H_
#define MCUST7735_H_

#include "McuST7735_config.h"
#include <stdint.h>

/* some predefined colors: */
#define McuST7735_COLOR_BLACK   0x0000
#define McuST7735_COLOR_RED     0x001F
#define McuST7735_COLOR_GREEN   0x07E0
#define McuST7735_COLOR_BLUE    0xF800
#define McuST7735_COLOR_WHITE   0xFFFF
#define McuST7735_COLOR_color565(r, g, b) ((((b)&0xF8)<<8) | (((g)&0xFC)<<3) | (((r)&0xF8)>>3))

/* width and height based on orientation of display: */
uint16_t McuST7735_GetWidth(void);
uint16_t McuST7735_GetHeight(void);

/* width and height based on hardware pixels */
#if McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_128X128
  #define McuST7735_GetHwWidth()      128
  #define McuST7735_GetHwHeight()     128
#elif McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X80
  #define McuST7735_GetHwWidth()      160
  #define McuST7735_GetHwHeight()     80
#elif McuST7735_CONFIG_DISPLAY_TYPE==MCUST7735_TYPE_160X128
  #define McuST7735_GetHwWidth()      160
  #define McuST7735_GetHwHeight()     128
#endif

void McuST7735_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

void McuST7735_FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void McuST7735_Init(void);

#endif /* MCUST7735_H_ */
