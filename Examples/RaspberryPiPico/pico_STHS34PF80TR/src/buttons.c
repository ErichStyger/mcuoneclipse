/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "buttons.h"
#include "buttons_config.h"
#include <assert.h>
#include "McuButton.h"
#include "McuRTOS.h"
#include "McuLED.h"
#include "leds.h"
#include "debounce.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

typedef struct BTN_Desc_t {
  McuBtn_Handle_t handle; /* handle of button pin */
} BTN_Desc_t;

static BTN_Desc_t BTN_Infos[BTN_NOF_BUTTONS];

BTN_Buttons_e BTN_RotateButton(BTN_Buttons_e button) {
#if BTN_CONFIG_ROTATION==0
  return button;
#elif BTN_CONFIG_ROTATION==180
  if (button == BTN_NAV_LEFT) {
    return BTN_NAV_RIGHT;
  } else if (button == BTN_NAV_RIGHT) {
    return BTN_NAV_LEFT;
  } else if (button == BTN_NAV_UP) {
    return BTN_NAV_DOWN;
  } else if (button == BTN_NAV_DOWN) {
    return BTN_NAV_UP;
  }
  return button;
#endif
}

bool BTN_IsPressed(BTN_Buttons_e btn) {
  assert(btn<BTN_NOF_BUTTONS);
  return McuBtn_IsOn(BTN_Infos[btn].handle);
}

uint32_t BTN_GetButtons(void) {
  uint32_t val = 0;

#if BUTTON_HAS_NAV_UP
  if (BTN_IsPressed(BTN_NAV_UP)) {
    val |= BTN_BIT_NAV_UP;
  }
#endif
#if BUTTON_HAS_NAV_DOWN
  if (BTN_IsPressed(BTN_NAV_DOWN)) {
    val |= BTN_BIT_NAV_DOWN;
  }
#endif
#if BUTTON_HAS_NAV_LEFT
  if (BTN_IsPressed(BTN_NAV_LEFT)) {
    val |= BTN_BIT_NAV_LEFT;
  }
#endif
#if BUTTON_HAS_NAV_RIGHT
  if (BTN_IsPressed(BTN_NAV_RIGHT)) {
    val |= BTN_BIT_NAV_RIGHT;
  }
#endif
#if BUTTON_HAS_NAV_CENTER
  if (BTN_IsPressed(BTN_NAV_CENTER)) {
    val |= BTN_BIT_NAV_CENTER;
  }
#endif
  return val;
}

static void gpio_IsrCallback(uint gpio, uint32_t events) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_RecordEnterISR();
#endif
  uint32_t button = 0; /* init */
  BaseType_t xHigherPriorityTaskWoken = false;
  switch(gpio) {
#if BUTTON_HAS_NAV_CENTER
    case BUTTONS_PINS_NAVCENTER_PIN:
      button = BTN_BIT_NAV_CENTER;
      break;
#endif
#if BUTTON_HAS_NAV_UP
    case BUTTONS_PINS_NAVUP_PIN:
      button = BTN_BIT_NAV_UP;
      break;
#endif
#if BUTTON_HAS_NAV_DOWN
    case BUTTONS_PINS_NAVDOWN_PIN:
      button = BTN_BIT_NAV_DOWN;
      break;
#endif
#if BUTTON_HAS_NAV_LEFT
    case BUTTONS_PINS_NAVLEFT_PIN:
      button = BTN_BIT_NAV_LEFT;
      break;
#endif
#if BUTTON_HAS_NAV_RIGHT
    case BUTTONS_PINS_NAVRIGHT_PIN:
      button = BTN_BIT_NAV_RIGHT;
      break;
#endif
    default:
      button = 0;
      break;
  }
  if (button!=0) {
    Debounce_StartDebounceFromISR(button, &xHigherPriorityTaskWoken);
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

#if BUTTON_HAS_NAV_CENTER
  btnConfig.hw.pin = BUTTONS_PINS_NAVCENTER_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_CENTER].handle = McuBtn_InitButton(&btnConfig);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAVCENTER_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
#endif

#if BUTTON_HAS_NAV_LEFT
  btnConfig.hw.pin = BUTTONS_PINS_NAVLEFT_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_LEFT].handle = McuBtn_InitButton(&btnConfig);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAVLEFT_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
#endif

#if BUTTON_HAS_NAV_RIGHT
  btnConfig.hw.pin = BUTTONS_PINS_NAVRIGHT_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_RIGHT].handle = McuBtn_InitButton(&btnConfig);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAVRIGHT_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
#endif

#if BUTTON_HAS_NAV_UP
  btnConfig.hw.pin = BUTTONS_PINS_NAVUP_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_UP].handle = McuBtn_InitButton(&btnConfig);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAVUP_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
#endif

#if BUTTON_HAS_NAV_DOWN
  btnConfig.hw.pin = BUTTONS_PINS_NAVDOWN_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_DOWN].handle = McuBtn_InitButton(&btnConfig);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAVDOWN_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
#endif
}