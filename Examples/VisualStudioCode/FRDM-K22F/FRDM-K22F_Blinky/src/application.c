/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "application.h"
#include "platform.h"
#include "McuRTOS.h"
#include "leds.h"
#include "McuRTT.h"
#include "McuLog.h"

static void BlinkyTask(void *p) {
  McuLog_info("blinky task started");
  for(;;) {
    McuLED_Toggle(LEDS_LedBlue);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Run(void) {
    PL_Init();
    McuShell_SendStr((unsigned char*)"hello world!\n", McuRTT_GetStdio()->stdOut);
    if (xTaskCreate(BlinkyTask, "Blinky", 500/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+1, NULL)!= pdPASS) {
      McuLog_fatal("failed creating blinky task");
      for(;;) {}
    }
    vTaskStartScheduler();    
    for(;;);
}
