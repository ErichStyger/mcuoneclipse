/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_WIFI
  #include "pico/cyw43_arch.h"
#endif
#include "application.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#include "hardware/gpio.h"
#if PL_CONFIG_USE_NEO_PIXEL_HW
  #include "ws2812.h"
#endif
#include "McuLED.h"
#include "McuLog.h"
#include "McuWait.h"
#include "McuUtility.h"
#if PL_CONFIG_USE_BUTTONS
  #include "buttons.h"
  #include "debounce.h"
#endif
#if PL_CONFIG_HAS_LITTLE_FS
  #include "McuLittleFS.h"
#endif
#if PL_CONFIG_USE_USB_CDC
  /* needed for USB CDC: */
  #include <stdio.h>
  #include "pico/stdlib.h"
#endif
#if PL_CONFIG_USE_LED_COUNTER_APP
  #include "neoCounter.h"
#endif
#if PL_CONFIG_USE_ROAD
  #include "road.h"
#endif

#if !PL_CONFIG_USE_PICO_W
  #define LED_PIN   (25) /* GPIO 25 */
#endif

#if PL_CONFIG_USE_BUTTONS
void APP_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind) {
  unsigned char buf[32];

  buf[0] = '\0';
  switch(button) {
    case BTN_NAV_UP:      McuUtility_strcat(buf, sizeof(buf), "up"); break;
    case BTN_NAV_LEFT:    McuUtility_strcat(buf, sizeof(buf), "left"); break;
    case BTN_NAV_RIGHT:   McuUtility_strcat(buf, sizeof(buf), "right"); break;
    case BTN_NAV_DOWN:    McuUtility_strcat(buf, sizeof(buf), "down"); break;
    case BTN_NAV_CENTER:  McuUtility_strcat(buf, sizeof(buf), "center"); break;
    case BTN_NAV_SET:     McuUtility_strcat(buf, sizeof(buf), "set"); break;
    case BTN_NAV_RESET:   McuUtility_strcat(buf, sizeof(buf), "reset"); break;
    default:              McuUtility_strcat(buf, sizeof(buf), "???"); break;
  }
  switch (kind) {
    case MCUDBNC_EVENT_PRESSED:             McuUtility_strcat(buf, sizeof(buf), " pressed"); break;
    case MCUDBNC_EVENT_PRESSED_REPEAT:      McuUtility_strcat(buf, sizeof(buf), " pressed-repeat"); break;
    case MCUDBNC_EVENT_LONG_PRESSED:        McuUtility_strcat(buf, sizeof(buf), " pressed-long"); break;
    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT: McuUtility_strcat(buf, sizeof(buf), " pressed-long-repeat"); break;
    case MCUDBNC_EVENT_RELEASED:            McuUtility_strcat(buf, sizeof(buf), " released"); break;
    case MCUDBNC_EVENT_LONG_RELEASED:       McuUtility_strcat(buf, sizeof(buf), " long released"); break;
    default:                                McuUtility_strcat(buf, sizeof(buf), "???"); break;
  }
  McuUtility_strcat(buf, sizeof(buf), "\n");
#if 0 && PL_CONFIG_USE_RTT
  McuRTT_printf(0, buf);
#endif
#if PL_CONFIG_USE_ROAD
  if (kind==MCUDBNC_EVENT_RELEASED) {
    Road_DemoToggle();
  }
#endif
#if PL_CONFIG_USE_LED_COUNTER_APP
  NeoCounter_OnButtonEvent(button, kind);
#endif
}
#endif

static void AppTask(void *pv) {
#if !PL_CONFIG_USE_PICO_W
  McuLED_Config_t config;
  McuLED_Handle_t led;

  McuLED_GetDefaultConfig(&config);
  config.hw.pin = LED_PIN;
  config.isLowActive = false;
  led = McuLED_InitLed(&config);
  if (led==NULL) {
    for(;;){}
  }
#endif
#if PL_CONFIG_HAS_LITTLE_FS
  McuLog_info("Mounting litteFS volume.");
  if(McuLFS_Mount(McuShell_GetStdio())==ERR_FAILED){
    McuLog_info("Mounting failed please format device first");
  }
#endif

  for(;;) {
#if 0 && PL_CONFIG_USE_BUTTONS
    uint32_t buttons = BTN_GetButtons();
    if (buttons!=0) {
      Debounce_StartDebounce(buttons);
  #if 0 && PL_CONFIG_USE_RTT
      if (buttons&BTN_BIT_NAV_CENTER) {
        McuRTT_printf(0, "center\n");
      }
      if (buttons&BTN_BIT_NAV_LEFT) {
        McuRTT_printf(0, "left\n");
      }
      if (buttons&BTN_BIT_NAV_RIGHT) {
        McuRTT_printf(0, "right\n");
      }
      if (buttons&BTN_BIT_NAV_UP) {
        McuRTT_printf(0, "up\n");
      }
      if (buttons&BTN_BIT_NAV_DOWN) {
        McuRTT_printf(0, "down\n");
      }
  #endif
    }
#endif
  #if !PL_CONFIG_USE_PICO_W
    McuLED_Toggle(led);
  #endif
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void APP_Run(void) {
  PL_Init();
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      1000/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    for(;;){} /* error! probably out of memory */
  }
  vTaskStartScheduler();
}
