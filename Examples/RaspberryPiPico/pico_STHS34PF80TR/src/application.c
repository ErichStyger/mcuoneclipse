/*
 * Copyright (c) 2023-2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"

#include "application.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#include "McuLED.h"
#include "McuLog.h"
#include "McuWait.h"
#include "McuUtility.h"

static void AppTask(void *pv) {
  McuLED_Config_t config;
  McuLED_Handle_t led_red, led_green;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = false;
  config.hw.pin = 0; /* red led on GPIO0*/
  led_red = McuLED_InitLed(&config);
  if (led_red==NULL) {
    McuLog_fatal("failed initializing red LED");
    for(;;){}
  }
  config.hw.pin = 1; /* green LED on GPIO1*/
  led_green = McuLED_InitLed(&config);
  if (led_green==NULL) {
    McuLog_fatal("failed initializing green LED");
    for(;;){}
  }
  for(;;) {
    McuLED_Toggle(led_red);
    vTaskDelay(pdMS_TO_TICKS(500));
    McuLED_Toggle(led_green);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void App_Run(void) {
  PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      1500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("failed creating task");
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) {
    /* shall not get here */
  }
  PL_Deinit();
}
