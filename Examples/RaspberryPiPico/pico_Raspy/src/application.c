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
#include "McuLED.h"
#include "leds.h"

#if !PL_CONFIG_USE_PICO_W
  #define LED_PIN   (25) /* GPIO 25 */
#endif

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
    vTaskDelay(pdMS_TO_TICKS(5*100));
  }
}

#if PL_CONFIG_USE_LEDS
static void ledTask(void *pv) {
  Leds_Init();
  for(int i=0; i<2; i++) {
    Leds_Off(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(500));
    Leds_Off(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(500));
    Leds_Off(LEDS_BLUE);
    vTaskDelay(pdMS_TO_TICKS(500));
    Leds_On(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(500));
    Leds_On(LEDS_GREEN);
    vTaskDelay(pdMS_TO_TICKS(500));
    Leds_On(LEDS_BLUE);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  Leds_Deinit();
  vTaskDelete(NULL); /* kill and exit task */
}
#endif

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
#if PL_CONFIG_USE_LEDS
  if (xTaskCreate(
      ledTask,  /* pointer to the task */
      "Led", /* task name for kernel awareness debugging */
      500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
#endif
  vTaskStartScheduler();
  for(;;) {
    /* shall not get here */
  }
}
