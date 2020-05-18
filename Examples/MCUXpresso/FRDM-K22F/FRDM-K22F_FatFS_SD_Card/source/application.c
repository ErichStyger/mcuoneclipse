/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "leds.h"
#include "McuTimeout.h"

static TimerHandle_t timerHndl;

static void vTimerTimoutAddTick(TimerHandle_t pxTimer) {
  McuTimeout_AddTick();
}

static void AppTask(void *pv) {
  for(;;) {
    McuLED_Toggle(LEDS_LedRed);
    vTaskDelay(pdMS_TO_TICKS(100));
    McuLED_Toggle(LEDS_LedGreen);
    vTaskDelay(pdMS_TO_TICKS(100));
    McuLED_Toggle(LEDS_LedBlue);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}


void APP_Run(void) {
  BaseType_t result;

  PL_Init();
  result =xTaskCreate(AppTask, "AppTask", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL);
  if (result!=pdPASS) {
    /* error! */
  }
  timerHndl = xTimerCreate(  /* timer to handle periodic things */
        "timeout", /* name */
        pdMS_TO_TICKS(McuTimeout_TICK_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerTimoutAddTick); /* callback */
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) { /* start the timer */
    for(;;); /* failure!?! */
  }

  vTaskStartScheduler();
  for(;;) {}
}
