/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h"
  #include "PicoWiFi.h"
#endif
#include "application.h"
#include "McuRTOS.h"
#include "McuUtility.h"
#include "McuLED.h"
#include "McuLog.h"
#include "McuST7735.h"

#if !PL_CONFIG_USE_PICO_W
  #define LED_PIN   (25) /* GPIO 25 */
#endif

static void TestDisplay(void) {
  uint16_t w, h;

  w = McuST7735_GetWidth();
  h = McuST7735_GetHeight();
  McuST7735_FillRectangle(0, 0, w, h, McuST7735_COLOR_BLACK);
 // McuST7735_DrawPixel(10, 10, McuST7735_COLOR_RED);
 // McuST7735_DrawPixel(10, 15, McuST7735_COLOR_BLUE);
  McuST7735_FillRectangle(20, 20, 15, 20, McuST7735_COLOR_RED);
  McuST7735_FillRectangle(40, 40, 15, 20, McuST7735_COLOR_GREEN);
  McuST7735_FillRectangle(60, 60, 15, 20, McuST7735_COLOR_BLUE);
  McuST7735_FillRectangle(0, 0, McuST7735_GetWidth(), McuST7735_GetHeight(), McuST7735_COLOR_RED);
  McuST7735_FillRectangle(0, 0, McuST7735_GetWidth(), McuST7735_GetHeight(), McuST7735_COLOR_GREEN);
  McuST7735_FillRectangle(0, 0, McuST7735_GetWidth(), McuST7735_GetHeight(), McuST7735_COLOR_BLUE);

  uint16_t x, y, color;
  for(int i=0; i<100; i++) {
    x = McuUtility_random(0, w-20);
    y = McuUtility_random(0, h-20);
    color = McuUtility_random(0x10, 0xffff);
    McuST7735_FillRectangle(x, y, 20, 20, color);
  }
}

static void AppTask(void *pv) {
  #define APP_HAS_ONBOARD_GREEN_LED   (!PL_CONFIG_USE_PICO_W)
#if !PL_CONFIG_USE_WIFI && PL_CONFIG_USE_PICO_W
  if (cyw43_arch_init()==0)  { /* need to init for accessing LEDs and other pins */
    PicoWiFi_SetArchIsInitialized(true);
  } else {
    McuLog_fatal("failed initializing CYW43");
    for(;;){}
  }
#endif

#if APP_HAS_ONBOARD_GREEN_LED
  /* only for pico boards which have an on-board green LED */
  McuLED_Config_t config;
  McuLED_Handle_t led;

  McuLED_GetDefaultConfig(&config);
  config.hw.pin = LED_PIN;
  config.isLowActive = false;
  led = McuLED_InitLed(&config);
  if (led==NULL) {
    for(;;){}
  }
#elif PL_CONFIG_USE_PICO_W && !PL_CONFIG_USE_WIFI
  bool ledIsOn = false;
#endif
  for(;;) {
  #if APP_HAS_ONBOARD_GREEN_LED
    McuLED_Toggle(led);
  #elif PL_CONFIG_USE_PICO_W && !PL_CONFIG_USE_WIFI
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, ledIsOn);
    ledIsOn = !ledIsOn;
  #endif
    TestDisplay();
    vTaskDelay(pdMS_TO_TICKS(10*100));
  }
}

void APP_Run(void) {
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
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
  for(;;) {
    /* shall not get here */
  }
}
