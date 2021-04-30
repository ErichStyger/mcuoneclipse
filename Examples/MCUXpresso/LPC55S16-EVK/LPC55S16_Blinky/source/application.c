/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

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
#include "leds.h"
#include "buttons.h"
#include "Shell.h"

static SemaphoreHandle_t mutex;

static void Init(void) {
  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  CLOCK_EnableClock(kCLOCK_Gpio0); /* for button on P0_7 */
  GPIO_PortInit(GPIO, 0); /* Initialize GPIO button */
  CLOCK_EnableClock(kCLOCK_Gpio1); /* LEDs and user buttons */
  GPIO_PortInit(GPIO, 1); /* Initialize GPIO for LEDs and User Button */

  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
  McuRTT_Init();
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_Init();
#endif
  McuLog_Init();
  //McuShellUart_Init();
  McuShell_Init();
  McuTimeDate_Init();
  McuDbnc_Init();

  /* user modules */
  LEDS_Init();
  BTN_Init();
  SHELL_Init();
}

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
  McuLog_info("App Task started.");
  BTN_RegisterAppCallback(AppOnDebounceEvent);
  for(;;) {
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
  Init(); /* init modules */

  for(int i=0;i<5;i++) {
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
    if (BTN_IsPressed(BTN_USER)) {
      LEDS_On(LEDS_RED);
      McuWait_Waitms(100);
      LEDS_Off(LEDS_RED);
    }
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
