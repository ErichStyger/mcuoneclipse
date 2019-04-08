/**
 *  @filename   :   epdpaint.h
 *  @brief      :   Header file for epdpaint.cpp
 *  @author     :   Yehui from Waveshare
 *  
 *  Copyright (C) Waveshare     July 28 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef EPDPAINT_H
#define EPDPAINT_H

// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3

#include "Display_Config.h"
// Color inverse. 1 or 0 = set or reset a bit if set a colored pixel
#if DISPLAY_IS_2_COLOR
	#define IF_INVERT_COLOR     1
#else
	#define IF_INVERT_COLOR     0
#endif
#include "fonts.h"

typedef struct Paint_t {
    unsigned char* image;
    int width;
    int height;
    int rotate;
} Paint;

void Paint_Init(Paint* paint, unsigned char* image, int width, int height);
void Paint_Clear(Paint* paint, int colored);
int  Paint_GetWidth(Paint* paint);
void Paint_SetWidth(Paint* paint, int width);
int  Paint_GetHeight(Paint* paint);
void Paint_SetHeight(Paint* paint, int height);
int  Paint_GetRotate(Paint* paint);
void Paint_SetRotate(Paint* paint, int rotate);
unsigned char* Paint_GetImage(Paint* paint);
void Paint_DrawAbsolutePixel(Paint* paint, int x, int y, int colored);
void Paint_DrawPixel(Paint* paint, int x, int y, int colored);
void Paint_DrawCharAt(Paint* paint, int x, int y, char ascii_char, sFONT* font, int colored);
void Paint_DrawStringAt(Paint* paint, int x, int y, const char* text, sFONT* font, int colored);
void Paint_DrawLine(Paint* paint, int x0, int y0, int x1, int y1, int colored);
void Paint_DrawHorizontalLine(Paint* paint, int x, int y, int width, int colored);
void Paint_DrawVerticalLine(Paint* paint, int x, int y, int height, int colored);
void Paint_DrawRectangle(Paint* paint, int x0, int y0, int x1, int y1, int colored);
void Paint_DrawFilledRectangle(Paint* paint, int x0, int y0, int x1, int y1, int colored);
void Paint_DrawCircle(Paint* paint, int x, int y, int radius, int colored);
void Paint_DrawFilledCircle(Paint* paint, int x, int y, int radius, int colored);

#endif

/* END OF FILE */

