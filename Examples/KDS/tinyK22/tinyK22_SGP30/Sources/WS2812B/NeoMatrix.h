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

#include "NeoPixel.h"

void Adafruit_NeoMatrix_drawPixel(int16_t x, int16_t y, uint8_t red, uint8_t green, uint8_t blue);

void MATRIX_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec);

void MATRIX_Init(void);

void MATRIX_Test(void);

#endif /* __NEO_MATRIX__ */

