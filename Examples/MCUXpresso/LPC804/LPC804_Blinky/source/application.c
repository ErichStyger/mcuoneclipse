/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuLED.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuRTOS.h"
#include "leds.h"
#if PL_CONFIG_USE_WS2812B
  #include "ws2812b.h"
#endif

#if PL_CONFIG_USE_WS2812B
static McuGPIO_Handle_t WS_lane;

static void WS_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);
  /* PIO0_9 */
  config.hw.gpio = GPIO;
  config.hw.iocon = IOCON_INDEX_PIO0_9;
  config.hw.pin =  9;
  config.hw.port = 0;
  config.hw.pull = McuGPIO_PULL_DISABLE ;
  config.isHighOnInit = false;
  config.isInput = false;
  WS_lane = McuGPIO_InitGPIO(&config);
  if (WS_lane==NULL) {
    for(;;) {} /* error */
  }
  WS2812B_Init();
}

#endif

static void blinky(void *pv) {
  for(;;) {
    LEDS_Neg(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(500));
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(500));
#if PL_CONFIG_USE_WS2812B
    McuGPIO_SetHigh(WS_lane);
    vTaskDelay(pdMS_TO_TICKS(1));
    McuGPIO_SetLow(WS_lane);
#endif
  }
}

void APP_Run(void) {
  PL_Init();
#if PL_CONFIG_USE_WS2812B
  WS_Init();
#endif
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
