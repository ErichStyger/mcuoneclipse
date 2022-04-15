/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "myTimer.h"
#include "McuRTOS.h"
#include "McuTimeDate.h"

#define LedTimer_TIMEOUT_MS (500) /* time or timeout for the blink */
static TimerHandle_t timer;

static void timerCallback(TimerHandle_t xTimer) {
  McuTimeDate_AddTick();
}

void MyTimer_Init(void) {
  timer = xTimerCreate("ledTimer", pdMS_TO_TICKS(McuTimeDate_CONFIG_TICK_TIME_MS), pdTRUE, NULL, timerCallback);
  if (timer==NULL) {
    for(;;) {} /* error */
  }
  if (xTimerStart(timer, 0)!=pdPASS) {
    for(;;) {} /* error */
  }
}
