/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "board.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "McuShellUart.h"
#include "McuShell.h"
#include "McuRTT.h"
#include "McuSystemView.h"
#include "McuLog.h"
#include "McuTimeDate.h"
#include "McuDebounce.h"
#include "McuSWO.h"
#include "leds.h"
#include "buttons.h"
#include "Shell.h"
#include "disk.h"
#include "cr_section_macros.h"
#if PL_CONFIG_HAS_LITTLE_FS
  #include "littleFS/McuLittleFS.h"
#endif

void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

static SemaphoreHandle_t mutex;

static void AppOnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      McuLog_info("Dbnc pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_PRESSED_REPEAT:
      McuLog_info("Dbnc repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED:
      McuLog_info("Dbnc long pressed: %d", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
      McuLog_info("Dbnc pressed repeat: %d", buttons);
      break;

    case MCUDBNC_EVENT_RELEASED:
      McuLog_info("Dbnc released: %d", buttons);
      break;

    default:
    case MCUDBNC_EVENT_END:
      McuLog_info("Dbnc end: %d", buttons);
      break;
  }
}

static void AppTask(void *pv) {
#if PL_CONFIG_USE_SD_CARD
  bool sdDiskPresent = false;
  bool present;
#endif

  McuLog_info("App Task started.");
#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  McuTimeDate_Init(); /* if using external RTC it uses I2C, need to do this from clock task */
#endif
  BTN_RegisterAppCallback(AppOnDebounceEvent);
#if PL_CONFIG_HAS_LITTLE_FS
  McuLog_info("Mounting litteFS volume.");
  (void)McuLFS_Mount(McuShell_GetStdio());
#endif
  for(;;) {
#if PL_CONFIG_USE_SD_CARD
    present = DISK_IsInserted((unsigned char*)DISK_DRIVE_SD_CARD);
    if (!sdDiskPresent && present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_INSERTED);
      sdDiskPresent = true;
    } else if (sdDiskPresent && !present) {
      DISK_SendEvent(DISK_EVENT_SD_CARD_REMOVED);
      sdDiskPresent = false;
    }
#endif
    if (BTN_IsPressed(BTN_UP)) {
      McuLog_info("User Up pressed.");
      LEDS_Neg(LEDS_BLUE);
    }
#if 1
    BTN_PollDebounce(); /* check and debounce */
#else /* simply button polling */
    if (BTN_IsPressed(BTN_USER)) {
      McuLog_info("User Button pressed.");
      LEDS_Neg(LEDS_BLUE);
    }
    if (BTN_IsPressed(BTN_WAKEUP)) {
      McuLog_info("Wakeup Button pressed.");
      LEDS_Neg(LEDS_GREEN);
    }
#endif
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS    McuTimeDate_CONFIG_TICK_TIME_MS

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
  McuTimeDate_AddTick();
}

void APP_Run(void) {
  PL_Init(); /* init modules */
#if 0 /* simple blinky */
  for(int i=0;i<2;i++) {
    for(;;) {
  #if PL_CONFIG_USE_SWO
      McuSWO_SendStr((unsigned char*)"Hello World using ITM console.\n");
  #endif
      LEDS_On(LEDS_RED);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_RED);
      McuWait_Waitms(100);
      LEDS_On(LEDS_GREEN);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_GREEN);
      McuWait_Waitms(100);
      LEDS_On(LEDS_BLUE);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_BLUE);
      McuWait_Waitms(100);
  #if PL_CONFIG_HAS_USER_BUTTON
      if (BTN_IsPressed(BTN_USER)) {
        LEDS_On(LEDS_RED);
        McuWait_Waitms(100);
        LEDS_Off(LEDS_RED);
      }
  #endif
    }
  } /* for */
#endif
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
  timerHndl = xTimerCreate("timer0", pdMS_TO_TICKS(TIMER_PERIOD_MS), pdTRUE, (void *)0, vTimerCallback);
  if (timerHndl==NULL) {
    for(;;); /* failure! */
  }
  if (xTimerStart(timerHndl, 0)!=pdPASS) {
    for(;;); /* failure! */
  }
  mutex = xSemaphoreCreateMutex();
  if (mutex!=NULL) {
    vQueueAddToRegistry(mutex, "Mutex");
  }
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
