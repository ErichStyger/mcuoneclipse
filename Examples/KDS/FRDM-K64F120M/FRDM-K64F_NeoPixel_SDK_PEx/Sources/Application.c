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

  NEO_Init();
  for(;;) {
    GPIO_DRV_TogglePinOutput(LEDRGB_BLUE);
    //OSA_TimeDelay(10);
    if (start) {
      NEO_ClearAllPixel();
      NEO_TransferPixels();
      for(i=0;i<NEO_NOF_PIXEL;i++) {
        NEO_SetPixelRGB(i, 0x10+(i*0x10), 0x20+(i*0x20), 0x30+(i*0x30));
        NEO_TransferPixels();
        OSA_TimeDelay(50);
      }
      NEO_ClearAllPixel();
      NEO_TransferPixels();
      NEOL_PixelTrail(0xff, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*5);
     // DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, true, false, false);
      NEOL_PixelTrail(0xff, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*5);
     // DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, false, true, false);
      NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*5);
     // DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, false, false, true);
      NEOL_PixelTrail(0x00, 0xff, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*5);
     // DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, false, true, true);
      NEO_ClearAllPixel();
      NEOL_PixelTrail(0x00, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*5);
     // DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, true, false, true);
      NEO_ClearAllPixel();
      NEOL_PixelTrail(0xff, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10*5);
     // DimmColor(NEO_PIXEL_FIRST, NEO_PIXEL_LAST, true, true, true);
    }
  }
}
