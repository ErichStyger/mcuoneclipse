/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_platform.h"
#if PL_CONFIG_USE_PICO_W
  #include "pico/cyw43_arch.h"
#endif
#include "application.h"
#include "McuRTOS.h"
#if PL_CONFIG_USE_RTT
  #include "McuRTT.h"
#endif
#include "hardware/gpio.h"
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
#if PL_CONFIG_USE_GUI_KEY_NAV
  #include "lv.h"
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
#if PL_CONFIG_USE_ROAD && !PL_CONFIG_USE_GUI
  if (kind==MCUDBNC_EVENT_RELEASED) {
    Road_DemoToggle();
  }
#endif
#if PL_CONFIG_USE_LED_COUNTER_APP
  NeoCounter_OnButtonEvent(button, kind);
#endif
#if PL_CONFIG_USE_GUI_KEY_NAV
  uint8_t btn;
  uint16_t eventMask;

  switch(button) {
    case BTN_NAV_UP:      btn = LV_BTN_MASK_UP;  break;
    case BTN_NAV_LEFT:    btn = LV_BTN_MASK_LEFT; break;
    case BTN_NAV_RIGHT:   btn = LV_BTN_MASK_RIGHT; break;
    case BTN_NAV_DOWN:    btn = LV_BTN_MASK_DOWN; break;
    case BTN_NAV_CENTER:  btn = LV_BTN_MASK_CENTER; break;
    case BTN_NAV_SET:     btn = LV_BTN_MASK_PREV; break;
    case BTN_NAV_RESET:   btn = LV_BTN_MASK_NEXT; break;
    default:              btn = 0; break;
  }
  switch (kind) {
    case MCUDBNC_EVENT_PRESSED:             eventMask = LV_MASK_PRESSED; break;
    case MCUDBNC_EVENT_PRESSED_REPEAT:      eventMask = LV_MASK_PRESSED;  break;
    case MCUDBNC_EVENT_LONG_PRESSED:        eventMask = LV_MASK_PRESSED;  break;
    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT: eventMask = LV_MASK_PRESSED;  break;
    case MCUDBNC_EVENT_RELEASED:            eventMask = LV_MASK_RELEASED;  break;
    case MCUDBNC_EVENT_LONG_RELEASED:       eventMask = LV_MASK_RELEASED_LONG;  break;
    default:                                eventMask = 0; break;
  }
  LV_ButtonEvent(btn, eventMask);
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
  #if !PL_CONFIG_USE_PICO_W
    McuLED_Toggle(led);
  #endif
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

static uint8_t PrintStatus(McuShell_ConstStdIOType *io) {
  unsigned char buf[48];

  McuShell_SendStatusStr((unsigned char*)"app", (const unsigned char*)"Status of application\r\n", io->stdOut);
  McuUtility_Num32uToStr(buf, sizeof(buf), PL_CONFIG_HW_ACTIVE_HW_VERSION);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((uint8_t*)"  HW", (unsigned char*)buf, io->stdOut);
  return ERR_OK;
}

uint8_t App_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint32_t value;
  const unsigned char *p;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "app help")==0) {
    McuShell_SendHelpStr((unsigned char*)"app", (const unsigned char*)"Group of application commands\r\n", io->stdOut);
    McuShell_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = true;
    return ERR_OK;
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "app status")==0)) {
    *handled = true;
    return PrintStatus(io);
  }
  return ERR_OK;
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
  for(;;) {
    /* shall not get here */
  }
}
