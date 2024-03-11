/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef CUBEFONT_H_
#define CUBEFONT_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  CubeFont_Font_5x7,
  CubeFont_Font_16x16,
} CubeFont_Font_e;

void CubeFont_paintLetter16(CubeFont_Font_e font, char ch, uint32_t color, uint32_t bgColor, int y, bool mirrorX);

void CubeFont_PaintLetter(CubeFont_Font_e font, char ch, int x, int y, int z, uint32_t color, uint32_t bgColor, bool mirrorX);

#endif /* CUBEFONT_H_ */
