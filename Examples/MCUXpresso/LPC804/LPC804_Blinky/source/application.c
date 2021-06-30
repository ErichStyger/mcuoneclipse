/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuLED.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "leds.h"

static void blinky(void *pv) {
  for(;;) {
    LEDS_Neg(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void APP_Run(void) {
  PL_Init();
  for(int i=0; i<3; i++) {
    LEDS_On(LEDS_GREEN);
    McuWait_Waitms(50);
    LEDS_Off(LEDS_GREEN);
    LEDS_On(LEDS_RED);
    McuWait_Waitms(50);
    LEDS_Off(LEDS_RED);
    McuWait_Waitms(500);
  }
  if (xTaskCreate(blinky, "blinky", 400/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {
    for(;;) {}
  }
  vTaskStartScheduler();
}
