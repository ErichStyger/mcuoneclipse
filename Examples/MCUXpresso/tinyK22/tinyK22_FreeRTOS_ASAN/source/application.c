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
#include "McuASAN.h"
#include "McuLog.h"
#include "asan_test.h"

static void AppTask(void *pv) {
  uint8_t *pa[10];
  size_t idx = 0;

  for(int i=0; i<sizeof(pa)/sizeof(pa[0]); i++) {
    pa[i] = NULL; /* initialize pointers */
  }
  for(;;) {
    if (pa[idx]!=NULL) {
      vPortFree(pa[idx]);
    }
    if (pa[idx]!=NULL) {
      pa[idx][5]++;
    }
    pa[idx] = pvPortMalloc(20);
    idx++;
    if (idx==sizeof(pa)/sizeof(pa[0])) {
      idx = 0;
    }
    McuLED_Toggle(tinyLED);
    vTaskDelay(pdMS_TO_TICKS(500));
  } /* for */
}

void APP_Run(void) {
  PL_Init();
  McuLog_info("Running application instrumented with ASAN");
  ASAN_Test();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
}
