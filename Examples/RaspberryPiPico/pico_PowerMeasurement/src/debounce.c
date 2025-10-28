/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "debounce.h"
#include "McuDebounce.h"
#include "McuRTOS.h"
#include "buttons.h"
#include "application.h"
#include "McuSystemView.h"

#if McuLib_CONFIG_SDK_USE_FREERTOS

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons);

#define TIMER_PERIOD_MS  20 /* frequency of debouncing timer */

static McuDbnc_Desc_t data =
{
  .state = MCUDBMC_STATE_IDLE,  /* state of state machine */
  .timerPeriodMs = TIMER_PERIOD_MS, /* timer period for debouncing */
  #if McuLib_CONFIG_SDK_USE_FREERTOS && configUSE_TIMERS
  .timer = NULL, /* FreeRTOS timer handle */
  #endif
  .debounceTimeMs = 100, /* debouncing time */
  .repeatTimeMs   = 200, /* time for repeated button events */
  .longKeyTimeMs  = 1000, /* time for a long key press */
  .getButtons = Buttons_GetButtons, /* callback to get bitset of buttons */
  .onDebounceEvent = OnDebounceEvent, /* debounce event handler */
};

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  Buttons_e button = BUTTONS_NOF_BUTTONS;

  if (buttons&BUTTONS_BIT_NAV_LEFT) {
    button = BUTTONS_NAV_LEFT;
  } else if (buttons&BUTTONS_BIT_NAV_RIGHT) {
    button = BUTTONS_NAV_RIGHT;
  } else if (buttons&BUTTONS_BIT_NAV_UP) {
    button = BUTTONS_NAV_UP;
  } else if (buttons&BUTTONS_BIT_NAV_DOWN) {
    button = BUTTONS_NAV_DOWN;
  } else if (buttons&BUTTONS_BIT_NAV_CENTER) {
    button = BUTTONS_NAV_CENTER;
  }

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SEGGER_SYSVIEW_PrintfTarget("event: %d, buttons %d pressed:\n", buttons, event);
#endif
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
    case MCUDBNC_EVENT_PRESSED_REPEAT:
    case MCUDBNC_EVENT_LONG_PRESSED:
    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
    case MCUDBNC_EVENT_RELEASED:
    case MCUDBNC_EVENT_LONG_RELEASED:
      button = Buttons_RotateButton(button);
      /* \TODO handle button, e.g. call application event, ... */
      break;

    case MCUDBNC_EVENT_END:
    #if configUSE_TIMERS
      (void)xTimerStop(data.timer, pdMS_TO_TICKS(100)); /* stop timer */
    #endif
      break;

    default:
      break;
  }
}

static void vTimerCallbackDebounce(TimerHandle_t pxTimer) {
  /* called with TIMER_PERIOD_MS during debouncing */
  McuDbnc_Process(&data);
}

void Debounce_StartDebounce(uint32_t buttons) {
  if (data.state==MCUDBMC_STATE_IDLE) {
    data.scanValue = buttons;
    data.state = MCUDBMC_STATE_START;
    McuDbnc_Process(&data);
    #if McuLib_CONFIG_SDK_USE_FREERTOS && configUSE_TIMERS
    (void)xTimerStart(data.timer, pdMS_TO_TICKS(100));
    #endif
  }
}

void Debounce_StartDebounceFromISR(uint32_t buttons, BaseType_t *pxHigherPriorityTaskWoken) {
  if (data.state==MCUDBMC_STATE_IDLE) {
    data.scanValue = buttons;
    data.state = MCUDBMC_STATE_START;
    McuDbnc_Process(&data);
    #if McuLib_CONFIG_SDK_USE_FREERTOS && configUSE_TIMERS
    (void)xTimerStartFromISR(data.timer, pxHigherPriorityTaskWoken);
    #endif
  }
}
#endif /* McuLib_CONFIG_SDK_USE_FREERTOS */

void Debounce_Deinit(void) {
  /* nothing needed */
}

void Debounce_Init(void) {
#if McuLib_CONFIG_SDK_USE_FREERTOS && configUSE_TIMERS
  data.timer = xTimerCreate(
        "tmrDbnc", /* name */
        pdMS_TO_TICKS(TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackDebounce); /* callback */
  if (data.timer==NULL) {
    for(;;); /* failure! */
  }
#endif
}
