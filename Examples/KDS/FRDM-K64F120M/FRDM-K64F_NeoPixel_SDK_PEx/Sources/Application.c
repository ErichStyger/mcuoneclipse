/*
 * Application.c
 *
 *  Created on: 26.07.2015
 *      Author: tastyger
 */

#include "Application.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "gpio1.h"
#include "osa1.h"

static bool start = true;

void APP_Run(void) {
  int i;
  uint8_t red, green, blue;
  uint8_t dimmPercent = 50;

  NEO_Init();
  for(;;) {
    GPIO_DRV_TogglePinOutput(LEDRGB_BLUE);
    if (start) {
      NEO_ClearAllPixel();
      NEO_TransferPixels();
      for(i=0;i<NEO_NOF_PIXEL;i++) {
        red = 0x10+(i*0x10); if (red==0) { red = 0x10; }
        green = 0x20+(i*0x20); if (green==0) { green = 0x10; }
        blue = 0x30+(i*0x30); if (blue==0) { blue = 0x10; }
        NEO_SetPixelRGB(i, red, green, blue);
        NEO_TransferPixels();
        OSA_TimeDelay(50);
      }
      NEO_ClearAllPixel();
      NEO_TransferPixels();

      for(i=0;i<=7;i++) {
        NEO_SetPixelRGB(i, 0x00, 0x00, (i+1)*10);
        NEO_DimmPercentPixel(i, i*10);
      }
      for(i=8;i<=15;i++) {
        NEO_SetPixelRGB(i, 0x00, i-7*10, 0x00);
        NEO_DimmPercentPixel(i, (i-8)*10);
      }
      for(i=16;i<=23;i++) {
        NEO_SetPixelRGB(i, i-15*10, 0x00, 0x00);
        NEO_DimmPercentPixel(i, (i-16)*10);
      }
      for(i=24;i<=31;i++) {
        NEO_SetPixelRGB(i, 0x00, 0x00, (i-23)*10);
        NEO_DimmPercentPixel(i, (i-23)*10);
      }
      for(i=32;i<=39;i++) {
        NEO_SetPixelRGB(i, 0x00, i-31*10, 0x00);
        NEO_DimmPercentPixel(i, (i-31)*10);
      }
      for(i=40;i<=47;i++) {
        NEO_SetPixelRGB(i, i-40*10, 0, 0x00);
        NEO_DimmPercentPixel(i, (i-39)*10);
      }
      for(i=48;i<=55;i++) {
        NEO_SetPixelRGB(i, 0, 0, i-47*10);
        NEO_DimmPercentPixel(i, (i-47)*10);
      }
      for(i=56;i<=63;i++) {
        NEO_SetPixelRGB(i, 0, 0, i-55*10);
        NEO_DimmPercentPixel(i, (i-55)*10);
      }
      NEO_TransferPixels();


      for(i=0;i<NEO_NOF_PIXEL;i++) {
        green = 0x5+(i*0x10); if (red==0) { red = 0x5; }
        blue = 0x5+(i*0x15); if (green==0) { green = 0x5; }
        red = 0x5+(i*0x20); if (blue==0) { blue = 0x5; }
        NEO_SetPixelRGB(i, red, green, blue);
        NEO_DimmPercentPixel(i, dimmPercent);
      }
      NEO_TransferPixels();

      NEOL_PixelTrail(0xff, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*2);
      NEOL_PixelTrail(0xff, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*2);
      NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*2);
      NEOL_PixelTrail(0x00, 0xff, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*2);
      NEO_ClearAllPixel();
      NEOL_PixelTrail(0x00, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*2);
      NEO_ClearAllPixel();
      NEOL_PixelTrail(0xff, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*2);
    }
  }
}
