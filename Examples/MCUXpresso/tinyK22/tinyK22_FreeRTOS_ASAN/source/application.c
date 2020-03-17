/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuArmTools.h"
#include "leds.h"
#include "fsl_pit.h"
#include "asan.h"

static void AppTask(void *pv) {
  uint8_t *pa[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
  size_t idx = 0;

  for(;;) {
    if (pa[idx]!=NULL) {
      vPortFree(pa[idx]);
    }
    pa[idx] = pvPortMalloc(20);
    idx++;
    if (idx==10) {
      idx = 0;
    }
    McuLED_Toggle(tinyLED);
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for */
}

void APP_Run(void) {
  __asan_init(); /* initialize ASAN */

  PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      300/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
}
