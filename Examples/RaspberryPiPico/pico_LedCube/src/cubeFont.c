/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#include "cubeFont.h"
#include "cube.h"


typedef uint8_t  CubeFont_5x7_t[7];

static const CubeFont_5x7_t digit_5x7_0 = {
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
};

static const CubeFont_5x7_t digit_5x7_1[7] = {
    0b00011,
    0b00101,
    0b01001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
};

static const CubeFont_5x7_t digit_5x7_2[7] = {
    0b01110,
    0b10001,
    0b10001,
    0b00010,
    0b00100,
    0b01000,
    0b11111,
};


static const uint16_t letter_H[16] = {
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1111111111111111,
    0b1111111111111111,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
};

static const uint16_t letter_S[16] = {
    0b0111111111111111,
    0b1111111111111111,
    0b1110000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1110000000000000,
    0b1111111111111110,
    0b0111111111111111,
    0b0000000000000111,
    0b0000000000000011,
    0b0000000000000011,
    0b0000000000000011,
    0b0000000000000111,
    0b1111111111111111,
    0b1111111111111110,
};

static const uint16_t letter_L[16] = {
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1100000000000000,
    0b1111111111111111,
    0b1111111111111111,
};

static const uint16_t letter_U[16] = {
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1100000000000011,
    0b1111111111111111,
    0b1111111111111111,
};

static void CubeFont_paintLetter5x7(CubeFont_Font_e font, char ch, int x0, int y0, int z0, uint32_t color, uint32_t bgColor, bool mirrorX) {
  uint8_t val;
  const uint8_t *letter;
  int y = y0;
  const int nofX = 5;
  const int nofY = 7;

  switch(ch) {
    case '0': letter = (uint8_t*)digit_5x7_0; break;
    case '1': letter = (uint8_t*)digit_5x7_1; break;
    case '2': letter = (uint8_t*)digit_5x7_2; break;
    default:
      for(;;){}; break;
  }

  for(int z=z0+nofY-1; z>=z0; z--) {
    val = *letter;
    if (mirrorX) {
      for(int x=x0;x<x0+nofX-1;x++) {
        if (val&1) { /* pixel set */
          Cube_SetPixelColor(x, y, z, color, color);
        } else if (bgColor!=-1) {
          Cube_SetPixelColor(x, y, z, bgColor, bgColor);
        }
        val >>= 1;
      }
    } else {
      for(int x=x0+nofX-1;x>=x0;x--) {
        if (val&1) { /* pixel set */
          Cube_SetPixelColor(x, y, z, color, color);
        } else if (bgColor!=-1) {
          Cube_SetPixelColor(x, y, z, bgColor, bgColor);
        }
        val >>= 1;
      }
    }
    letter++;
  }
}

void CubeFont_paintLetter16(CubeFont_Font_e font, char ch, uint32_t color, uint32_t bgColor, int y, bool mirrorX) {
  uint16_t val;
  const uint16_t *letter;

  switch(ch) {
    case 'H': letter = letter_H; break;
    case 'S': letter = letter_S; break;
    case 'L': letter = letter_L; break;
    case 'U': letter = letter_U; break;
    default:
      for(;;){}; break;
  }

  for(int z=15; z>=0; z--) {
    val = *letter;
    if (mirrorX) {
      for(int x=0;x<16;x++) {
        if (val&1) { /* pixel set */
          Cube_SetPixelColor(x, y, z, color, color);
        } else if (bgColor!=-1) {
          Cube_SetPixelColor(x, y, z, bgColor, bgColor);
        }
        val >>= 1;
      }
    } else {
      for(int x=15;x>=0;x--) {
        if (val&1) { /* pixel set */
          Cube_SetPixelColor(x, y, z, color, color);
        } else if (bgColor!=-1) {
          Cube_SetPixelColor(x, y, z, bgColor, bgColor);
        }
        val >>= 1;
      }
    }
    letter++;
  }
}

void CubeFont_PaintLetter(CubeFont_Font_e font, char ch, int x, int y, int z, uint32_t color, uint32_t bgColor, bool mirrorX) {
  switch(font) {
    case CubeFont_Font_5x7:
      CubeFont_paintLetter5x7(font, ch, x, y, z, color, bgColor, mirrorX);
      break;
    case CubeFont_Font_16x16:
      CubeFont_paintLetter16(font, ch, color, bgColor, y, mirrorX);
      break;
  } /* switch */
}
