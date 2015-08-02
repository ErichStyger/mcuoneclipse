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
