/*
 * Neo.c
 *
 *  Created on: 10.10.2018
 *      Author: Erich Styger
 */


#include "Platform.h"
#if PL_CONFIG_HAS_NEO_PIXEL
#include "NeoApp.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "PixelDMA.h"

static void NeoTask(void* pvParameters) {
  int i, cntr, val = 0;
  int inc = 1;
  int red, green, blue;

  red = 0xff;
  green = 0;
  blue = 0;

  (void)pvParameters; /* parameter not used */
  NEO_ClearAllPixel();
  cntr = 0;
  for(;;) {
//    NEO_SetPixelColor(0, 0, NEO_MAKE_COLOR_RGBW(0xff,0x00,0x00,0x00));
//    NEO_SetPixelColor(0, 1, NEO_MAKE_COLOR_RGBW(0x00,0xff,0x00,0x00));
//    NEO_SetPixelColor(0, 2, NEO_MAKE_COLOR_RGBW(0x00,0x00,0xff,0x00));
//    NEO_SetPixelColor(0, 3, NEO_MAKE_COLOR_RGBW(0x00,0x00,0x00,0xff));
//    NEO_SetPixelColor(0, 4, NEO_MAKE_COLOR_RGBW(0xff,0xff,0xff,0xff));
//    NEO_SetPixelColor(0, 5, NEO_MAKE_COLOR_RGBW(0xff,0x00,0x00,0x00));
//    NEO_SetPixelColor(0, 6, NEO_MAKE_COLOR_RGBW(0x00,0xff,0x00,0x00));
//    NEO_SetPixelColor(0, 7, NEO_MAKE_COLOR_RGBW(0x00,0x00,0xff,0x00));
#if 1
    NEOL_PixelTrail(NEO_MAKE_COLOR_RGB(0x10, 0x00, 0x00), 0, NEOC_NOF_PIXEL-1, 2, 50, 100);
    NEOL_PixelTrail(NEO_MAKE_COLOR_RGB(0x00, 0x10, 0x00), 0, NEOC_NOF_PIXEL-1, 2, 50, 100);
    NEOL_PixelTrail(NEO_MAKE_COLOR_RGB(0x00, 0x00, 0x10), 0, NEOC_NOF_PIXEL-1, 2, 50, 100);
    NEOL_PixelTrail(NEO_MAKE_COLOR_RGBW(0x00, 0x00, 0x00, 0x10), 0, NEOC_NOF_PIXEL-1, 2, 50, 100);
#elif 0
     if (val==0xff) {
       inc = -1;
      } else if (val==0) {
       inc = 1;
     }
     val += inc;
     for(i=0;i<NEO_NOF_PIXEL;i++) {
       if (cntr<2*0xff) {
         NEO_SetPixelRGB(0, i, val, 0x00, 0x00);
       } else if (cntr<=4*0xff) {
         NEO_SetPixelRGB(0, i, 0x00, val, 0x00);
       } else {
         NEO_SetPixelRGB(0, i, 0x00, 0x00, val);
       }
     }
     cntr++;
     if (cntr>6*0xff) {
       cntr = 0;
     }
#elif 0
     NEO_SetPixelRGB(0, 0, val, 0x00, 0x00);
     NEO_SetPixelRGB(0, 1, 0x00, val, 0x00);
     NEO_SetPixelRGB(0, 2, 0x00, 0x00, val);
     NEO_SetPixelRGB(0, 3, 0x00, 0x00, val);
     NEO_SetPixelRGB(0, 4, 0x00, 0x00, val);
     NEO_SetPixelRGB(0, 5, 0x00, 0x00, val);
     NEO_SetPixelRGB(0, 6, 0x00, 0x00, val);
     NEO_SetPixelRGB(0, 7, 0x00, 0x00, val);
//    NEO_SetPixelRGB(0, 0, 0xff, 0x00, 0x00);
//    NEO_SetPixelRGB(0, 1, 0x00, 0xFF, 0x00);
//    NEO_SetPixelRGB(0, 2, 0x00, 0x00, 0xff);
//    NEO_SetPixelRGB(0, 3, 0x40, 0x50, 0x80);
//    NEO_SetPixelRGB(0, 4, 0x60, 0x00, 0xA0);
//    NEO_SetPixelRGB(0, 5, 0x40, 0x20, 0x80);
//    NEO_SetPixelRGB(0, 6, 0x20, 0x40, 0xFF);
//    NEO_SetPixelRGB(0, 7, 0xff, 0x60, 0x30);
#endif
    vTaskDelay(5/portTICK_RATE_MS);
    NEO_TransferPixels();
    LED1_Neg();
  }
}


void NEOA_Init(void) {
  NEO_Init();
  PIXDMA_Init();
  if (xTaskCreate(
        NeoTask,  /* pointer to the task */
        "Neo", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY+1,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
}

#endif /* PL_CONFIG_HAS_NEO_PIXEL */

