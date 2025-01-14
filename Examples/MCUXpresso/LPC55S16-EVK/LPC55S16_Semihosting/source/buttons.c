/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "buttons.h"
#include "buttons_config.h"
#include <assert.h>
#include "McuButton.h"
#include "McuDebounce.h"
#include "McuRTT.h"
#include "fsl_pint.h"
#include "McuLED.h"
#include "leds.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

typedef struct BTN_Desc_t {
  McuBtn_Handle_t handle; /* handle of button pin */
} BTN_Desc_t;

static BTN_Desc_t BTN_Infos[BTN_NOF_BUTTONS];

bool BTN_IsPressed(BTN_Buttons_e btn) {
  assert(btn<BTN_NOF_BUTTONS);
  return McuBtn_IsOn(BTN_Infos[btn].handle);
}

static uint32_t GetButtons(void) {
  uint32_t val = 0;

#if PL_CONFIG_HAS_USER_BUTTON
  if (BTN_IsPressed(BTN_USER)) {
    val |= BTN_BIT_USER;
  }
#endif
  if (BTN_IsPressed(BTN_WAKEUP)) {
    val |= BTN_BIT_WAKEUP;
  }
  if (BTN_IsPressed(BTN_UP)) {
    val |= BTN_BIT_UP;
  }
  return val;
}

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons);

#define TIMER_PERIOD_MS  20 /* frequency of debouncing timer */
static McuDbnc_Desc_t data =
{
  .state = MCUDBMC_STATE_IDLE,  /* state of state machine */
  .timerPeriodMs = TIMER_PERIOD_MS, /* timer period for debouncing */
  .timer = NULL, /* FreeRTOS timer handle */
  .debounceTimeMs = 100, /* debouncing time */
  .repeatTimeMs   = 300, /* time for repeated button events */
  .longKeyTimeMs  = 1000, /* time for a long key press */
  .getButtons = GetButtons, /* callback to get bitset of buttons */
  .onDebounceEvent = OnDebounceEvent, /* debounce event handler */
};

void BTN_RegisterAppCallback(void (*cb)(McuDbnc_EventKinds, uint32_t)) {
  data.onDebounceEvent = cb;
}

static void OnDebounceEvent(McuDbnc_EventKinds event, uint32_t buttons) {
  switch(event) {
    case MCUDBNC_EVENT_PRESSED:
      SEGGER_printf("pressed: %d\r\n", buttons);
      break;

    case MCUDBNC_EVENT_PRESSED_REPEAT:
      SEGGER_printf("repeat: %d\r\n", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED:
      SEGGER_printf("long pressed: %d\r\n", buttons);
      break;

    case MCUDBNC_EVENT_LONG_PRESSED_REPEAT:
      SEGGER_printf("long repeat: %d\r\n", buttons);
      break;

    case MCUDBNC_EVENT_RELEASED:
      SEGGER_printf("released: %d\r\n", buttons);
      break;

    default:
    case MCUDBNC_EVENT_END:
      (void)xTimerStop(data.timer, pdMS_TO_TICKS(100)); /* stop timer */
      SEGGER_printf("end: %d\r\n", buttons);
      break;
  }
}

static void vTimerCallbackDebounce(TimerHandle_t pxTimer) {
  /* called with TIMER_PERIOD_MS during debouncing */
  McuDbnc_Process(&data);
}

static void StartDebounce(uint32_t buttons, bool fromISR) {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  if (data.state==MCUDBMC_STATE_IDLE) {
    data.scanValue = buttons;
    data.state = MCUDBMC_STATE_START;
    McuDbnc_Process(&data);
    if (fromISR) {
      (void)xTimerStartFromISR(data.timer, &xHigherPriorityTaskWoken);
    } else {
      (void)xTimerStart(data.timer, pdMS_TO_TICKS(100));
    }
    if (fromISR) {
      portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
  }
}

void BTN_PollDebounce(void) {
#if PL_CONFIG_HAS_USER_BUTTON
  if (BTN_IsPressed(BTN_USER)) {
    StartDebounce(BTN_BIT_USER, false);
  }
#endif
  if (BTN_IsPressed(BTN_WAKEUP)) {
    StartDebounce(BTN_BIT_WAKEUP, false);
  }
  if (BTN_IsPressed(BTN_UP)) {
    StartDebounce(BTN_BIT_UP, false);
  }
}

#if 0
static void SysViewLogStart(void) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #define MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT (0)
  McuSystemView_RecordEnterISR();
  McuSystemView_Print((const char*)"Pressed button\r\n");
  McuSystemView_OnUserStart(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
#endif
}

static void SysViewLogEnd(void) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_OnUserStop(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
  McuSystemView_RecordExitISR();
#endif
}
#endif

#if 0 && McuLib_CONFIG_CPU_IS_LPC
static void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status) {
  SysViewLogStart();
  /* ... */
  SysViewLogEnd();
}
#endif

void BTN_Deinit(void) {
  for(int i=0; i<BTN_NOF_BUTTONS; i++) {
    BTN_Infos[i].handle = McuBtn_DeinitButton(BTN_Infos[i].handle);
  }
}

void BTN_Init(void) {
  McuBtn_Config_t btnConfig;

  McuBtn_GetDefaultConfig(&btnConfig);

#if PL_CONFIG_HAS_USER_BUTTON
  btnConfig.isLowActive = true;
  btnConfig.hw.gpio = BUTTONS_USER_GPIO;
  btnConfig.hw.port = BUTTONS_USER_PORT;
  btnConfig.hw.pin = BUTTONS_USER_PIN;
  BTN_Infos[BTN_USER].handle = McuBtn_InitButton(&btnConfig);
#endif

  btnConfig.isLowActive = true;
  btnConfig.hw.gpio = BUTTONS_WAKEUP_GPIO;
  btnConfig.hw.port = BUTTONS_WAKEUP_PORT;
  btnConfig.hw.pin = BUTTONS_WAKEUP_PIN;
  BTN_Infos[BTN_WAKEUP].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.isLowActive = true;
  btnConfig.hw.gpio = BUTTONS_UP_GPIO;
  btnConfig.hw.port = BUTTONS_UP_PORT;
  btnConfig.hw.pin = BUTTONS_UP_PIN;
  BTN_Infos[BTN_UP].handle = McuBtn_InitButton(&btnConfig);
  McuBtn_EnablePullResistor(BTN_Infos[BTN_UP].handle);

#if 0
  SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, kSYSCON_GpioPort0Pin4ToPintsel);

  PINT_Init(PINT); /* Initialize PINT */
  /* Setup Pin Interrupt 0 for rising edge */
  PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  /* Enable callbacks for PINT0 by Index */
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);
#endif

  data.timer = xTimerCreate(
        "tmrDbnc", /* name */
        pdMS_TO_TICKS(TIMER_PERIOD_MS), /* period/time */
        pdTRUE, /* auto reload */
        (void*)0, /* timer ID */
        vTimerCallbackDebounce); /* callback */
  if (data.timer==NULL) {
    for(;;); /* failure! */
  }

}
