/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "debounce.h"
#include "McuDebounce.h"
#include "McuRTOS.h"
#include "buttons.h"
#include "leds.h"

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons);

#define TIMER_PERIOD_MS  20 /* frequency of debouncing timer */

static McuDbnc_Desc_t data =
{
  .state = MCUDBMC_STATE_IDLE,  /* state of state machine */
  .timerPeriodMs = TIMER_PERIOD_MS, /* timer period for debouncing */
  .timer = NULL, /* FreeRTOS timer handle */
  .debounceTimeMs = 100, /* debouncing time */
  .repeatTimeMs   = 200, /* time for repeated button events */
  .longKeyTimeMs  = 1000, /* time for a long key press */
  .getButtons = BTN_GetButtons, /* callback to get bitset of buttons */
  .onDebounceEvent = OnDebounceEvent, /* debounce event handler */
};

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  BTN_Buttons_e button = BTN_NOF_BUTTONS;

#if BUTTON_HAS_NAV_LEFT
  if (buttons & BTN_BIT_NAV_LEFT) {
    button = BTN_NAV_LEFT;
  }
#endif
#if BUTTON_HAS_NAV_RIGHT
  if (buttons & BTN_BIT_NAV_RIGHT) {
    button = BTN_NAV_RIGHT;
  }
#endif
#if BUTTON_HAS_NAV_UP
  if (buttons & BTN_BIT_NAV_UP) {
    button = BTN_NAV_UP;
  }
#endif
#if BUTTON_HAS_NAV_DOWN
  if (buttons & BTN_BIT_NAV_DOWN) {
    button = BTN_NAV_DOWN;
  }
#endif
#if BUTTON_HAS_NAV_CENTER
  if (buttons & BTN_BIT_NAV_CENTER) {
    button = BTN_NAV_CENTER;
  }
#endif

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SEGGER_SYSVIEW_PrintfTarget("event: %d, buttons %d pressed:\n", buttons, event);
#endif

  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      Leds_Neg(LEDS_RED);
      break;
    case MCUDBNC_EVENT_PRESSED_REPEAT:
    case MCUDBNC_EVENT_LONG_PRESSED:
    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
    case MCUDBNC_EVENT_RELEASED:
    case MCUDBNC_EVENT_LONG_RELEASED:
      
      break;

    case MCUDBNC_EVENT_END:
      (void)xTimerStop(data.timer, pdMS_TO_TICKS(100)); /* stop timer */
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
  if (data.state == MCUDBMC_STATE_IDLE) {
    data.scanValue = buttons;
    data.state = MCUDBMC_STATE_START;
    McuDbnc_Process(&data);
    (void)xTimerStart(data.timer, pdMS_TO_TICKS(100));
  }
}

void Debounce_StartDebounceFromISR(uint32_t buttons, BaseType_t *pxHigherPriorityTaskWoken) {
  if (data.state == MCUDBMC_STATE_IDLE) {
    data.scanValue = buttons;
    data.state = MCUDBMC_STATE_START;
    McuDbnc_Process(&data);
    (void)xTimerStartFromISR(data.timer, pxHigherPriorityTaskWoken);
  }
}

void Debounce_Deinit(void) {
  /* nothing needed */
}

void Debounce_Init(void) {
  data.timer = xTimerCreate(
        "tmrDbnc", /* name */
        pdMS_TO_TICKS(TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackDebounce); /* callback */
  if (data.timer == NULL) {
    for(;;); /* failure! */
  }
}