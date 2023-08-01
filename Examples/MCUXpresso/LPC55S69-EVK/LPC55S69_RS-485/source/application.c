/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "application.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "leds.h"

static void AppTask(void *pv) {
  for(;;) {
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  PL_Init(); /* init modules */

  LEDS_Neg(LEDS_RED);
  McuWait_Waitms(100);
  LEDS_Neg(LEDS_RED);
  McuWait_Waitms(100);
  LEDS_Neg(LEDS_GREEN);
  McuWait_Waitms(100);
  LEDS_Neg(LEDS_GREEN);
  McuWait_Waitms(100);
  LEDS_Neg(LEDS_BLUE);
  McuWait_Waitms(100);
  LEDS_Neg(LEDS_BLUE);
  McuWait_Waitms(100);
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
  for(;;) { /* should not get here */ }
}
