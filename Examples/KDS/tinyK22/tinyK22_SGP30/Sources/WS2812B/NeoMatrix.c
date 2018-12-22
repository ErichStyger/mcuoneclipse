/*-------------------------------------------------------------------------
  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  -------------------------------------------------------------------------
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
  -------------------------------------------------------------------------*/

#include "Platform.h"
#include "NeoMatrix.h"
#include "NeoPixel.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "FDisp1.h"

void MATRIX_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec) {
  GDisp1_PixelDim x, y;
  uint8_t buf[16];

  (void)hour;
  NEO_ClearAllPixel();

  buf[0] = '\0';
  UTIL1_strcatNum16uFormatted(buf, sizeof(buf), min, '0', 2);
  UTIL1_chcat(buf, sizeof(buf), ':');
  x = 0; y = 0;
  FDisp1_WriteString(buf, 0x001100, &x, &y, GFONT1_GetFont());

  buf[0] = '\0';
  UTIL1_strcatNum16uFormatted(buf, sizeof(buf), sec, '0', 2);
  x = 3; y = 8;
  FDisp1_WriteString(buf, 0x001100, &x, &y, GFONT1_GetFont());

  NEO_TransferPixels();
}

#if 0
static void FontTest(void) {
  GDisp1_PixelDim x, y;
  uint16_t i;
  uint8_t buf1[8], buf2[8];

  for(i=0;i<15;i++) {
    x = y = 0;
    UTIL1_Num16uToStr(buf1, sizeof(buf1), 150+i*10);
    FDisp1_WriteString(buf1, 0x002200, &x, &y, GFONT1_GetFont());
    x = 0; y = 8;
    UTIL1_Num16uToStr(buf2, sizeof(buf2), 20+i*5);
    FDisp1_WriteString(buf2, 0x112211, &x, &y, GFONT1_GetFont());
    NEO_TransferPixels();
    WAIT1_Waitms(1000);
    /* clear */
    x = y = 0;
    FDisp1_WriteString(buf1, 0x000000, &x, &y, GFONT1_GetFont());
    x = 0; y = 8;
    FDisp1_WriteString(buf2, 0x000000, &x, &y, GFONT1_GetFont());
  }
}

void MATRIX_Test(void) {
  int x, y;

  //GDisp1_PutPixel(0,0,0xFF0000);
  //GDisp1_PutPixel(8,0,0xFFFF00);
  //GDisp1_PutPixel(0,8,0xFF00FF);
  //GDisp1_PutPixel(8,8,0x00FF00);
  FontTest();
#if 0
  for (x=0; x<GDisp1_GetWidth(); x++) {
    for(y=0; y<GDisp1_GetHeight(); y++) {
      //Adafruit_NeoMatrix_drawPixel(x, y, 0xff/4, 0x0, 0x0);
      GDisp1_PutPixel(x, y, 0xff0000);
      NEO_TransferPixels();
      WAIT1_Waitms(10);
      //Adafruit_NeoMatrix_drawPixel(x, y, 0x0, 0x0, 0x0);
      GDisp1_PutPixel(x, y, 0);
    }
  }
#endif
}
#endif

void MATRIX_Init(void) {
}
