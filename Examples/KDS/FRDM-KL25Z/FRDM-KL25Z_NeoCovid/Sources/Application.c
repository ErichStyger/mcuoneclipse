/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Application.h"
#include "LED1.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "NeoPixel.h"
#include "NeoLine.h"
#include "NeoMatrix.h"
#include "GDisp1.h"

static void DimmColor(NEO_PixelIdxT start, NEO_PixelIdxT end, bool isRed, bool isGreen, bool isBlue) {
  int i;
  NEO_PixelIdxT j;
  uint8_t red, green, blue;

  for(i=0;i<0x50;i+=0x8){
    for(j=start;j<end;j++) {
      red = green = blue = 0;
      if (isRed) {
        red = i;
      }
      if (isGreen) {
        green = i;
      }
      if (isBlue) {
        blue = i;
      }
      NEO_SetPixelRGB(0, j, red, green, blue);
    }
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}


static void smile(uint8_t r, uint8_t g, uint8_t b) {
  NEO_ClearAllPixel();
  NEO_TransferPixels();

  for(int i=0; i<=6; i++) {
    NEO_SetPixelRGB(0, 6+i, r, g, b);
    NEO_SetPixelRGB(0, 6-i, r, g, b);
    NEO_TransferPixels();
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

#if PL_HAS_NEO_PIXEL && !PL_HAS_LED_FRAME
static void NeoTask(void* pvParameters) {
  #define DIMM 0x50
  (void)pvParameters; /* parameter not used */

  for(;;) {
    smile(0, 0, 0x50);
    NEOL_PixelTrail(0xff, 0x00, 0x00, NEO_PIXEL_FIRST, 12, 12, 30, 100);
    DimmColor(NEO_PIXEL_FIRST, 12, FALSE, TRUE, FALSE);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
#endif

void APP_Run(void) {
#if PL_HAS_NEO_PIXEL
  NEO_Init();
  MATRIX_Init();
#endif
#if PL_HAS_LED_CUBE
  LCUBE_Init();
#endif
  SHELL_Init();
#if PL_HAS_MAZE_RACE
  MR_Init();
#endif
#if PL_HAS_MUSIC || PL_HAS_SD_CARD
  SPIBus_Init();
#endif
#if PL_HAS_MUSIC
  MUSIC_Init();
#endif
#if PL_HAS_RNET
  RNETA_Init();
#endif
#if PL_HAS_PONG
  PONG_Init();
#elif PL_HAS_LED_FRAME
  LEDFRAME_Init();
#elif PL_HAS_NEO_PIXEL
  if (xTaskCreate(
        NeoTask,  /* pointer to the task */
        "Neo", /* task name for kernel awareness debugging */
        500/sizeof(StackType_t), /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (TaskHandle_t*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
#endif
  vTaskStartScheduler();
}

