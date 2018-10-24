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

#define WIDTH_PIXELS (3*8)

static void SetPixel(int x, int y, uint32_t color) {
  /* 0, 0 is left upper corner */
  /* single lane, 3x64 modules from left to right */
  int pos;

  pos = ((x/8)*64) /* position in tile */
       + (x%8) /* position in row */
       + (y)*8; /* add y offset */
  NEO_SetPixelColor(0, pos, color);
}

static void Layer(int layer, uint32_t color) {
  int y, x;

  y = layer;
  for(x=0;x<WIDTH_PIXELS;x++) {
    SetPixel(x, y, color);
  }
}

static int32_t Rainbow(int32_t numOfSteps, int32_t step) {
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;
    float h = (double)step / numOfSteps;
    int i = (int32_t)(h * 6);
    float f = h * 6.0 - i;
    float q = 1 - f;

    switch (i % 6)
    {
        case 0:
            r = 1;
            g = f;
            b = 0;
            break;
        case 1:
            r = q;
            g = 1;
            b = 0;
            break;
        case 2:
            r = 0;
            g = 1;
            b = f;
            break;
        case 3:
            r = 0;
            g = q;
            b = 1;
            break;
        case 4:
            r = f;
            g = 0;
            b = 1;
            break;
        case 5:
            r = 1;
            g = 0;
            b = q;
            break;
    }
    r *= 255;
    g *= 255;
    b *= 255;
    return (((int)r)<<16)|(((int)g)<<8)+(int)b;
   // return "#" + ((Int32)(r * 255)).ToString("X2") + ((Int32)(g * 255)).ToString("X2") + ((Int32)(b * 255)).ToString("X2");
}



static void NeoTask(void* pvParameters) {
  int i, cntr, val = 0;
  int inc = 1;
  int red, green, blue;
  NEO_Color color;

  (void)pvParameters; /* parameter not used */
  cntr = 0;

   for(;;) {
      int row;
      int32_t color;

      for(int colorStep=0; colorStep<512; colorStep++) {
        for(row=0; row<8; row++) {
          color = Rainbow(512,colorStep);
          color = NEO_SetColorPercent(color, 5); /* reduce brightness */
          Layer(row, color);
        }
        NEO_TransferPixels();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
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

