/*
 * Copyright (c) 2023, Erich Styger
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
#include "McuLog.h"
#include "McuUtility.h"
#include "McuLED.h"
#include "leds.h"
#if PL_CONFIG_USE_BUTTONS && !PL_CONFIG_USE_BUTTONS_IRQ
  #include "buttons.h"
  #include "debounce.h"
#endif
#if PL_CONFIG_USE_OLED
  #include "OLED.h"
#endif
#if PL_CONFIG_USE_GCOV
  #include "gcov_support.h"
#endif
#include <stdio.h>

#if PL_CONFIG_USE_BUTTONS
void App_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind) {
  const char *p = NULL;

  if (kind==MCUDBNC_EVENT_PRESSED) {
    switch(button) {
      case BTN_NAV_UP:
        p = "up";
        break;
      case BTN_NAV_DOWN:
         p = "down";
         break;
      case BTN_NAV_LEFT:
         p = "left";
         break;
      case BTN_NAV_RIGHT:
         p = "right";
         break;
      case BTN_NAV_CENTER:
         p = "center";
         break;
      default:
        p = NULL;
        break;
    }
    if (p!=NULL) {
      McuLog_info(p);
    #if PL_CONFIG_USE_OLED
      OLED_SendText(p);
    #endif
    }
  }
}
#endif

static void AppTask(void *pv) {
  uint32_t ms = 0;
  volatile bool dumpCoverage = false;

#if PL_CONFIG_USE_PICO_W && PL_CONFIG_USE_LEDS
  Leds_InitFromTask(); /* needed for the on-board Pico-W LED */
#endif
  for(;;) {
    //McuLog_info("app task");
  #if PL_CONFIG_USE_BUTTONS && !PL_CONFIG_USE_BUTTONS_IRQ
    /*! \TODO if enabled WiFi, it triggers GPIO button interrupts? Doing polling instead */
    uint32_t buttons;

    buttons = BTN_GetButtons();
    if (buttons!=0) { /* poll buttons */
      Debounce_StartDebounce(buttons);
    }
    vTaskDelay(pdMS_TO_TICKS(20));
    ms += 20;
  #else
    vTaskDelay(pdMS_TO_TICKS(1000));
    ms += 1000;
  #endif
  #if PL_CONFIG_USE_GCOV
    if (dumpCoverage && ms>5*1000) {
      //vTaskEndScheduler();
      taskENTER_CRITICAL();
      gcov_write_files();
      for(;;) {       // GCOVR_EXCL_LINE
        __asm("nop"); // GCOVR_EXCL_LINE
      }               // GCOVR_EXCL_LINE
      taskEXIT_CRITICAL();
    }
  #endif
  }
}

void App_Init(void) {
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      1500/sizeof(StackType_t), /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY+2,  /* initial priority */
      (TaskHandle_t*)NULL /* optional task handle to create */
    ) != pdPASS)
  {
    McuLog_fatal("Failed creating task");         // GCOVR_EXCL_LINE
    for(;;){} /* error! probably out of memory */ // GCOVR_EXCL_LINE
  }
}
