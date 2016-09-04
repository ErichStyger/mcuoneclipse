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

/* Pixel Orientation, view from the front
 * 1: one module
 *    ..**....
 *    .*.*....
 *    *..*....
 *    ...*....
 *    ...*....
 *  x ...*....
 *  ^ ...*....
 *  | ...*....
 *  (0/0)-->y
 *   DIN
 *   x==0
 *   y==0..63
 *
 * 2: two modules on one data lane (NEOC_NOF_X==1, NEOC_NOF_Y==2*64)
 *    ..**....   ..**....
 *    .*.*....   .*.*....
 *    *..*....   *..*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *    ...*....   ...*....
 *  (0/0)-->y   (1/0)-->y
 *   DIN        DIN
 *   x==0       x==1
 *   y==0..63   y==0..63
 */
static const uint32_t Numbers8x4[10] = { /* digits 0-9, data byte with two nibbles (rows) */
    /* from MSB to LSB: 4bits for each row, e.g. for '1':
     *  0010
     *  0110
     *  1010
     *  0010
     *  0010
     *  0010
     *  0010
     *  0010
     */
  /* 0 */ 0b01101001100110011001100110010110,
  /* 1 */ 0b00100110101000100010001000100010,
  /* 2 */ 0b01101001000100100100100010001111,
  /* 3 */ 0b01101001000101100010000110010110,
  /* 4 */ 0b00011001100111110001000100010001,
  /* 5 */ 0b11111000100001100001000110010110,
  /* 6 */ 0b01101001100010001111100110010110,
  /* 7 */ 0b11110001000100100010010001001000,
  /* 8 */ 0b01101001100101101001100110010110,
  /* 9 */ 0b01101001100101110001000110010110
};

static void LEDFRAME_SetChar8x4Pixels(char ch, NEO_PixelIdxT x0, NEO_PixelIdxT y0, uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t data;
  int i;
  GDisp1_PixelColor color = (red<<16)|(green<<8)|blue;

  /* x/y (0/0) is top left corner, with x increasing to the right and y increasing to the bottom */
  if (ch>='0' && ch<='9') { /* check if valid digit */
    data = Numbers8x4[(unsigned int)(ch-'0')];
    for(i=0;i<32;i++) { /* 32bits for each digit */
      if (data&(1<<31)) { /* MSB set? */
        GDisp1_PutPixel(x0+(i%4), y0+(i/4), color);
      } else {
        GDisp1_ClrPixel(x0+(i%4), y0+(i/4));
      }
      data <<= 1; /* next bit */
    } /* for */
  } /* if number */
}

void LEDFRAME_ShowClockTime(uint8_t hour, uint8_t min, uint8_t sec) {
  const uint8_t level = 8;

  (void)hour;
  if (GDisp1_GetWidth()>=16) { /* at least two modules */
    /* write min:sec */
    LEDFRAME_SetChar8x4Pixels('0'+(min/10), 0, 0, 0x00, 0x00, level);
    LEDFRAME_SetChar8x4Pixels('0'+(min%10), 4, 0, level, 0x00, 0x00);
    /* write first two digits */
    LEDFRAME_SetChar8x4Pixels('0'+(sec/10), 8, 0, 0x00, 0x00, level);
    LEDFRAME_SetChar8x4Pixels('0'+(sec%10), 12, 0, level, 0x00, 0x00);
    NEO_TransferPixels();
  } else if (GDisp1_GetWidth()>=8) { /* at least one module */
    /* write sec */
    LEDFRAME_SetChar8x4Pixels('0'+(sec/10), 0, 0, 0x00, 0x00, level);
    LEDFRAME_SetChar8x4Pixels('0'+(sec%10), 4, 0, level, 0x00, 0x00);
    NEO_TransferPixels();
  }
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
