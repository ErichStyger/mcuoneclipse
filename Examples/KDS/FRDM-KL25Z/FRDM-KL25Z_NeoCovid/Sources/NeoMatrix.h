/*--------------------------------------------------------------------
  This file is part of the Adafruit NeoMatrix library.

  NeoMatrix is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  NeoMatrix is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with NeoMatrix.  If not, see
  <http://www.gnu.org/licenses/>.
  --------------------------------------------------------------------*/

#ifndef __NEO_MATRIX__
#define __NEO_MATRIX__

/* the values below are used in MATRIX_Init() to configure the matrix.
 * See https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library
 *  */
// These define the layout for a single 'unified' matrix (e.g. one made
// from NeoPixel strips, or a single NeoPixel shield), or for the pixels
// within each matrix of a tiled display (e.g. multiple NeoPixel shields).
#define NEO_MATRIX_TOP         0x00 // Pixel 0 is at top of matrix
#define NEO_MATRIX_BOTTOM      0x01 // Pixel 0 is at bottom of matrix
#define NEO_MATRIX_LEFT        0x00 // Pixel 0 is at left of matrix
#define NEO_MATRIX_RIGHT       0x02 // Pixel 0 is at right of matrix
#define NEO_MATRIX_CORNER      0x03 // Bitmask for pixel 0 matrix corner
#define NEO_MATRIX_ROWS        0x00 // Matrix is row major (horizontal): pixels are increasing in rows
#define NEO_MATRIX_COLUMNS     0x04 // Matrix is column major (vertical): pixels are increasing in columns
#define NEO_MATRIX_AXIS        0x04 // Bitmask for row/column layout
#define NEO_MATRIX_PROGRESSIVE 0x00 // Same pixel order across each line (otherwise ZIGZAG)
#define NEO_MATRIX_ZIGZAG      0x08 // Pixel order reverses between lines (otherwise Progressive)
#define NEO_MATRIX_SEQUENCE    0x08 // Bitmask for pixel line order

// These apply only to tiled displays (multiple matrices):
#define NEO_TILE_TOP           0x00 // First tile is at top of matrix
#define NEO_TILE_BOTTOM        0x10 // First tile is at bottom of matrix
#define NEO_TILE_LEFT          0x00 // First tile is at left of matrix
#define NEO_TILE_RIGHT         0x20 // First tile is at right of matrix
#define NEO_TILE_CORNER        0x30 // Bitmask for first tile corner
#define NEO_TILE_ROWS          0x00 // Tiles ordered in rows
#define NEO_TILE_COLUMNS       0x40 // Tiles ordered in columns
#define NEO_TILE_AXIS          0x40 // Bitmask for tile H/V orientation
#define NEO_TILE_PROGRESSIVE   0x00 // Same tile order across each line
#define NEO_TILE_ZIGZAG        0x80 // Tile order reverses between lines
#define NEO_TILE_SEQUENCE      0x80 // Bitmask for tile line order

#include "NeoPixel.h"

void Adafruit_NeoMatrix_drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue);

void MATRIX_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec);

void MATRIX_Init(void);

void MATRIX_Test(void);

#endif /* __NEO_MATRIX__ */

