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
#if PL_CONFIG_USE_SWO
  #include "McuSWO.h"
#endif
#include "leds.h"
#if PL_CONFIG_USE_BUTTON
  #include "buttons.h"
#endif
#if PL_CONFIG_USE_SHELL
  #include "Shell.h"
#endif
#if PL_CONFIG_USE_SD_CARD
  #include "disk.h"
#endif
#include "cr_section_macros.h"

void __assertion_failed(char *_Expr) {
  for(;;) {
    __asm("nop");
  }
}

static SemaphoreHandle_t mutex;

#if PL_CONFIG_USE_BUTTON
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
#endif

static void AppTask(void *pv) {
#if PL_CONFIG_USE_SD_CARD
  bool sdDiskPresent = false;
  bool present;
#endif

  McuLog_info("App Task started.");
#if PL_CONFIG_USE_BUTTON
  BTN_RegisterAppCallback(AppOnDebounceEvent);
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
#if PL_CONFIG_USE_BUTTON
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
#endif
    LEDS_Neg(LEDS_1);
    vTaskDelay(pdMS_TO_TICKS(1000));
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
#if PL_CONFIG_INIT_SWO
  McuSWO_Init(SystemCoreClock, McuSWO_CONFIG_SPEED_BAUD); /* if initialization is not done by the debugger, need to do it manually here */
  McuSWO_ChangeSpeed(McuSWO_CONFIG_SPEED_BAUD); /* execute again if J-Link has changed speed */
#endif

  for(int i=0;i<2;i++) {
//  for(;;) {
#if PL_CONFIG_USE_SWO
    McuSWO_SendStr((unsigned char*)"Hello World using ITM console.\n");
#endif
    LEDS_On(LEDS_1);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_1);
    McuWait_Waitms(100);
    LEDS_On(LEDS_2);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_2);
    McuWait_Waitms(100);
    LEDS_On(LEDS_3);
    McuWait_Waitms(100);
    LEDS_Off(LEDS_3);
    McuWait_Waitms(100);
#if PL_CONFIG_USE_BUTTON
    if (BTN_IsPressed(BTN_USER)) {
      LEDS_On(LEDS_RED);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_RED);
    }
#endif
  } /* for */
  if (xTaskCreate(
      AppTask,  /* pointer to the task */
      "App", /* task name for kernel awareness debugging */
      700/sizeof(StackType_t), /* task stack size */
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
