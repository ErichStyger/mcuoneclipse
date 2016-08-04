/*
 * LEDFrame.c
 *
 *  Created on: 03.08.2016
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#include "LEDFrame.h"
#include "GDisp1.h"
#include "NeoPixel.h"
#include "FreeRTOS.h"

#define LEDFRAME_NOF_MODULES    (1)

static const uint8_t Numbers8x4[10][4] = { /* 0-9, byte with two nibbles (rows) */
  /* 0 */ {0b01101001, 0b10011001, 0b10011001, 0b10010110},
  /* 1 */ {0b00100110, 0b10100010, 0b00100010, 0b00100010},
  /* 2 */ {0b01101001, 0b00010010, 0b01001000, 0b10001111},
  /* 3 */ {0b01101001, 0b00010110, 0b00100001, 0b10010110},
  /* 4 */ {0b00011001, 0b10011111, 0b00010001, 0b00010001},
  /* 5 */ {0b11111000, 0b10000110, 0b00010001, 0b10010110},
  /* 6 */ {0b01101001, 0b10001000, 0b11111001, 0b10010110},
  /* 7 */ {0b11110001, 0b00010010, 0b00100100, 0b01001000},
  /* 8 */ {0b01101001, 0b10010110, 0b10011001, 0b10010110},
  /* 9 */ {0b01101001, 0b10010111, 0b00010001, 0b10010110}
};

void LEDFRAME_SetChar8x4Pixels(char ch, NEO_PixelIdxT x0, NEO_PixelIdxT y0, uint8_t red, uint8_t green, uint8_t blue) {
  int i, n;
  const uint8_t *dataP;
  uint8_t data;
  uint8_t nibble;
  NEO_PixelIdxT x, y;
  GDisp1_PixelColor color = (red<<16)|(green<<8)|blue;

  x = x0;
  y = y0;
  if (ch>='0' && ch<='9') {
    dataP = &Numbers8x4[(unsigned int)(ch-'0')][0];
    for(i=3;i>=0;i--) { /* 4 bytes of data */
      data = dataP[i];
      for(n=3;n>=0;n--) { /* 4 pixels in row */
        if (data&1) {
          GDisp1_PutPixel(x, y+n, color);
        } else {
          GDisp1_ClrPixel(x, y+n);
        }
        data >>= 1; /* next bit */
      } /* for */
      x++; /* next row up in display */
      for(n=3;n>=0;n--) { /* 4 pixels in row */
        if (data&1) {
          GDisp1_PutPixel(x, y+n, color);
        } else {
          GDisp1_ClrPixel(x, y+n);
        }
        data >>= 1; /* next bit */
      } /* for */
      x++; /* next row up in display */
    } /* for */
  } /* if number */
}

void LEDFRAME_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec) {
#if LEDFRAME_NOF_MODULES == 1
  LEDFRAME_SetChar8x4Pixels('0'+(sec/10), 0, 0, 0x00, 0x00, 0xff);
  LEDFRAME_SetChar8x4Pixels('0'+(sec%10), 0, 4, 0xff, 0x00, 0x00);
  NEO_TransferPixels();
#endif
}

void LEDFRAME_Demo(void) {
  LEDFRAME_SetChar8x4Pixels('0', 0, 0, 0x10, 0, 0x0);
  NEO_TransferPixels();
  vTaskDelay(500/portTICK_RATE_MS);
  LEDFRAME_SetChar8x4Pixels('1', 0, 4, 0x00, 0x10, 0x0);
  NEO_TransferPixels();
  vTaskDelay(500/portTICK_RATE_MS);
  LEDFRAME_SetChar8x4Pixels('2', 0, 0, 0x0, 0x0, 0x10);
  NEO_TransferPixels();
  vTaskDelay(500/portTICK_RATE_MS);
  {
    int i;

    for(i=0;i<10;i++) {
      LEDFRAME_SetChar8x4Pixels(i+'0', 0, 0, 0xff, 0x00, 0x00);
      NEO_TransferPixels();
      vTaskDelay(500/portTICK_RATE_MS);
    }
  }
}
