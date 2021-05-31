/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "application.h"
#include "platform.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "leds.h"

#if PL_CONFIG_USE_SHELL
uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  return ERR_OK;
}
#endif


static void blinkyTask(void *pv) {
  for(;;) {
    McuLED_Toggle(LEDS_Led);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Run(void) {
  PL_Init();
  if (xTaskCreate(
      blinkyTask,  /* pointer to the task */
      "blinky", /* task name for kernel awareness debugging */
      600/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+1,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) {}
}
