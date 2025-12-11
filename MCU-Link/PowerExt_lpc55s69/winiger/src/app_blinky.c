/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_BLINKY
#include "app_blinky.h"
#include "McuLog.h"
#include "McuRTOS.h"
#include "led.h"

static void AppBlinky(void *pv) {
  Led1_On();
  Led1_Off();
  #if LED_CONFIG_HAS_2_LED
    Led2_On();
    Led2_Off();
  #endif
  for(;;) {
    Led1_Toggle();
    #if LED_CONFIG_HAS_2_LED
    Led2_Toggle();
    #endif
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void App_BlinkyInit(void) {
  if (xTaskCreate(
    AppBlinky,  /* pointer to the task */
    "AppBlinky", /* task name for kernel awareness debugging */
    1*1024/sizeof(StackType_t), /* task stack size */
    (void*)NULL, /* optional task startup argument */
    tskIDLE_PRIORITY+1,  /* initial priority */
    NULL /* optional task handle to create */
    ) != pdPASS) 
  {
   for(;;){} /* error! probably out of memory */
  }
}

#endif /* PL_CONFIG_USE_BLINKY */
