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
#include "leds.h"
#include "buttons.h"

static SemaphoreHandle_t mutex;

static void Init(void) {
  McuLib_Init();
//  McuRTOS_Init();
  McuWait_Init();
  McuLED_Init();
  LEDS_Init();
  BTN_Init();
}

static void AppTask(void *pv) {
  for(;;) {
    LEDS_Neg(LEDS_RED);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static TimerHandle_t timerHndl;
#define TIMER_PERIOD_MS 100

static void vTimerCallback(TimerHandle_t pxTimer) {
  /* TIMER_PERIOD_MS ms timer */
}

bool doIt = false;

void APP_Run(void) {
  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  GPIO_PortInit(GPIO, 1); /* Initialize GPIO for LEDs and User Button */

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
      300/sizeof(StackType_t), /* task stack size */
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
  if (doIt) {
    vTaskStartScheduler();
  }
  for(;;) { /* should not get here */ }
}
