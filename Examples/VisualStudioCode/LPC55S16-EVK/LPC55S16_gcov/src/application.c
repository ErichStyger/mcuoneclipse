/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuRTOS.h"
#include "leds.h"
#if PL_CONFIG_USE_GCOV
  #include "gcov_support.h"     
#endif 

 void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

static void AppTask(void *pv) {
  uint32_t ms = 0;
  for(;;) {
    LEDS_Neg(LEDS_BLUE);
    vTaskDelay(pdMS_TO_TICKS(1000));
    ms += 1000;
  #if PL_CONFIG_USE_GCOV
    if (ms>5000) {
      vPortEndScheduler();
    }
  #endif
  }
}

void APP_Run(void) {
  PL_Init(); /* init modules */
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      1000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS) {
     for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  #if PL_CONFIG_USE_GCOV
    gcov_write_files();
  #endif
  for(;;) { /* should not get here */ }
}
