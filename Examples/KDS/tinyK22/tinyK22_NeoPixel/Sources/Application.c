/*
 * Application.c
 *
 *  Created on: 14.07.2018
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"
#include "PixelDMA.h"
#include "NeoPixel.h"

static void NeoTask(void* pvParameters) {
  int i, cntr, val = 0;
  int inc = 1;
  (void)pvParameters; /* parameter not used */
  NEO_ClearAllPixel();
  cntr = 0;
  for(;;) {
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
#if 0
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

void APP_Run(void) {
#if PL_HAS_NEO_PIXEL
  NEO_Init();
#endif
  PIXDMA_Init();

  if (xTaskCreate(
        NeoTask,  /* pointer to the task */
        "Neo", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }

  vTaskStartScheduler();

  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(500);
  }
}



