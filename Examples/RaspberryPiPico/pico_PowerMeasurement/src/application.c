/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuLog.h"
#include "McuSystemView.h"
#include "McuShellCdcDevice.h"

#if PL_CONFIG_USE_LEDS
  #include "leds.h"
#endif
#if PL_CONFIG_USE_BUTTONS
  #include "buttons.h"
#endif
#if PL_CONFIG_USE_SENSOR_TASK
  #include "sensor.h"
#endif
#if PL_CONFIG_USE_DEBOUNCE
  #include "debounce.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "shell.h"
#endif

#if PL_CONFIG_USE_BLINKY_TASK
static void blinkyTask(void *pv) {
  LEDS_Leds_e led = *(LEDS_Leds_e*)pv;
  for(;;) {
    Leds_Neg(led);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
#endif

#if PL_CONFIG_USE_BLINKY_TASK
static void appTask(void *pv) {
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}
#endif

void App_Run(void) {
  PL_Init(); /* initialize platform and drivers */
#if PL_CONFIG_USE_LEDS
  Leds_Init();
#endif
#if PL_CONFIG_USE_BUTTONS
  Buttons_Init();
#endif
#if PL_CONFIG_USE_SENSOR_TASK
  Sensor_Init();
#endif
#if PL_CONFIG_USE_DEBOUNCE
  Debounce_Init();
#endif
#if PL_CONFIG_USE_SHELL
  Shell_Init();
#endif
  BaseType_t res;

  res = xTaskCreate(appTask, "appTask", 600/sizeof(StackType_t), NULL, tskIDLE_PRIORITY+2, NULL);
  if (res!=pdPASS) {
    for(;;) {} /* error! */
  }
  #if PL_CONFIG_USE_BLINKY_TASK
  LEDS_Leds_e led = LEDS_PICO_GREEN;

  res = xTaskCreate(blinkyTask, "blinkyTask", 600/sizeof(StackType_t), &led, tskIDLE_PRIORITY+1, NULL);
  if (res!=pdPASS) {
    for(;;) {} /* error! */
  }
  #endif
  /* run application */
  vTaskStartScheduler(); /* start the scheduler */
  PL_Deinit(); /* deinitialize the platform */
}
