/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "leds.h"

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
  vTaskStartScheduler();
  for(;;) {}
}
