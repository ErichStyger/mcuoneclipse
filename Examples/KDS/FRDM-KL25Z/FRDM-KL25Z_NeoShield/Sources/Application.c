/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "RNet_App.h"

static portTASK_FUNCTION(Task1, pvParameters) {
  int i;

#define DIMM 0x50
  (void)pvParameters; /* parameter not used */
  NEO_SetPixelRGB(0, 0xff, 0x00, 0x00);
  NEO_SetPixelRGB(1, 0x00, 0xFF, 0x00);
  NEO_SetPixelRGB(2, 0x00, 0x00, 0xff);
  NEO_SetPixelRGB(3, 0x40, 0x50, 0x80);
  NEO_SetPixelRGB(4, 0x60, 0x00, 0xA0);
  NEO_SetPixelRGB(5, 0x40, 0x20, 0x80);
  NEO_SetPixelRGB(6, 0x20, 0x40, 0xFF);
  NEO_SetPixelRGB(7, 0xff, 0x60, 0x30);
  NEO_TransferPixels();
  for(i=0;i<7;i++) {
    NEO_DimmPercentPixel(i,50);
  }
  NEO_TransferPixels();

  for(;;) {
    for(i=0;i<=NEO_PIXEL_LAST;i++) {
      NEO_SetPixelRGB(i, 0xff, 0x00, 0x00);
      if (i>0) {
        NEO_SetPixelRGB(i-1, 0x00, 0x00, 0x00);
      } else if (i==0) {
        NEO_SetPixelRGB(NEO_PIXEL_LAST, 0x00, 0x00, 0x00);
      }
      NEO_TransferPixels();
      FRTOS1_vTaskDelay(200/portTICK_RATE_MS);
    }
#if 0
    NEOL_PixelTrail(0xff, 0x00, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0xff, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0x00, 0xff, 0x00, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0x00, 0xff, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0x00, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
    NEOL_PixelTrail(0xff, 0x00, 0xff, NEO_PIXEL_FIRST, NEO_PIXEL_LAST, 12, 50, 10);
#endif
    LED1_Neg();
    FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
    //NEO_TransferPixels();
  }
}

void APP_Run(void) {
  NEO_Init();
  SHELL_Init();
  RNETA_Init();
  if (FRTOS1_xTaskCreate(
        Task1,  /* pointer to the task */
        "Task1", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  FRTOS1_vTaskStartScheduler();
}

