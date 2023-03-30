/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#include "cube.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "NeoPixel.h"
#endif
#include "McuLog.h"
#include "McuUtility.h"

#if PL_CONFIG_USE_NEO_PIXEL_HW
  static SemaphoreHandle_t semNeoUpdate; /* semaphore use to trigger a display update */
#endif

#if PL_CONFIG_USE_SHELL
uint8_t Cube_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  return ERR_OK;
}
#endif

#if PL_CONFIG_USE_NEO_PIXEL_HW
#define TEST_MODE   (1)  /* test mode for rings */

#if TEST_MODE
static void TestRing(void) {
  uint8_t cR, cG, cB;
  int i;

  cR = 0x2;
  cG = 0;
  cB = 0;
  i = 0;
  NEO_ClearAllPixel();
  for(;;) {
    for(int lane=NEOC_LANE_START; lane<=NEOC_LANE_END; lane++) {
      NEO_SetPixelRGB(lane, i, cR, cG, cB);
    }
    NEO_TransferPixels();
    i++;
    if (i==NEOC_NOF_LEDS_IN_LANE) {
      i = 0;
      NEO_ClearAllPixel();
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
#endif

#if PL_CONFIG_USE_NEO_PIXEL_HW
bool APP_RequestUpdateLEDsFromISR(void) {
  BaseType_t xHigherPriorityTaskWoken;

  xSemaphoreGiveFromISR(semNeoUpdate, &xHigherPriorityTaskWoken);
  return xHigherPriorityTaskWoken==pdTRUE;
}

void APP_RequestUpdateLEDs(void) {
  xSemaphoreGive(semNeoUpdate);
}
#endif

static void cubeTask(void *pv) {
  BaseType_t res;

  vTaskDelay(pdMS_TO_TICKS(100));
  McuLog_trace("starting cube task");
  NEO_ClearAllPixel();
  NEO_TransferPixels();
#if TEST_MODE
  TestRing();
#endif
  for(;;) {
#if PL_CONFIG_USE_NEO_PIXEL_HW
    res = xSemaphoreTake(semNeoUpdate, portMAX_DELAY); /* block until we get a request to update */
    if (res==pdTRUE) { /* received the signal */
      NEO_ClearAllPixel();
      /* do matrix demo here */
      NEO_TransferPixels();
    }
#endif
    vTaskDelay(pdMS_TO_TICKS(20)); /* can wait 20 ms until a next update is needed */
  } /* for */
}
#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */

void Cube_Init(void) {
#if PL_CONFIG_USE_NEO_PIXEL_HW
  if (xTaskCreate(
      cubeTask,  /* pointer to the task */
      "cube", /* task name for kernel awareness debugging */
      900/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  semNeoUpdate = xSemaphoreCreateBinary();
  if (semNeoUpdate==NULL) {
    McuLog_fatal("Failed creating binary semaphore.");
    for(;;){}
  }
  vQueueAddToRegistry(semNeoUpdate, "semNeoUpdate");
  xSemaphoreGive(semNeoUpdate); /* trigger initial update */
#endif
}
