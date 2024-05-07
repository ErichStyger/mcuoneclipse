/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "buttons.h"
#include "buttons_config.h"
#include <assert.h>
#include "McuButton.h"
#include "McuRTOS.h"
#include "debounce.h"
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

uint32_t BTN_GetButtons(void) {
  uint32_t val = 0;

  if (BTN_IsPressed(BTN_USER)) {
    val |= BTN_BIT_USER;
  }
  return val;
}

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
/* IDs for SystemView */
#define MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT  (0)

static void SysViewLogStart(void) {
  McuSystemView_RecordEnterISR();
  McuSystemView_Print((const char*)"Pressed button\r\n");
  McuSystemView_OnUserStart(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
}
#endif

#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
static void SysViewLogEnd(void) {
  McuSystemView_OnUserStop(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
  McuSystemView_RecordExitISR();
}
#endif

static void gpio_IsrCallback(uint gpio, uint32_t events) {
  uint32_t button = 0; /* init */
  BaseType_t xHigherPriorityTaskWoken = false;

  #if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_RecordEnterISR();
  #endif
  switch(gpio) {
    case BUTTONS_PINS_USER_PIN:
      button = BTN_BIT_USER;
      break;
    default:
      button = 0;
      break;
  }
  if (button!=0) {
    Debounce_StartDebounceFromISR(button, &xHigherPriorityTaskWoken);
#if PL_CONFIG_USE_DTN_LED
    dtnLed_NotifyFromISR(DTN_LED_GREEN|DTN_LED_RED);
#endif
  }
  #if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_RecordExitISR();
  #endif
}


void BTN_Deinit(void) {
  for(int i=0; i<BTN_NOF_BUTTONS; i++) {
    BTN_Infos[i].handle = McuBtn_DeinitButton(BTN_Infos[i].handle);
  }
}

void BTN_Init(void) {
  McuBtn_Config_t btnConfig;

  BUTTONS_ENABLE_CLOCK();
  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.pin = BUTTONS_PINS_USER_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_USER].handle = McuBtn_InitButton(&btnConfig);

  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_USER_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
}
