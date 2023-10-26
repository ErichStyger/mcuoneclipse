/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_USE_BUTTONS
#include "buttons.h"
#include "buttons_config.h"
#include <assert.h>
#include "McuButton.h"
#include "McuUtility.h"
#include "McuRTOS.h"
#include "debounce.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_LPC
  #include "fsl_pint.h"
  #include "fsl_syscon.h"
#endif
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

  if (BTN_IsPressed(BTN_NAV_UP)) {
    val |= BTN_BIT_NAV_UP;
  }
  if (BTN_IsPressed(BTN_NAV_DOWN)) {
    val |= BTN_BIT_NAV_DOWN;
  }
  if (BTN_IsPressed(BTN_NAV_LEFT)) {
    val |= BTN_BIT_NAV_LEFT;
  }
  if (BTN_IsPressed(BTN_NAV_RIGHT)) {
    val |= BTN_BIT_NAV_RIGHT;
  }
  if (BTN_IsPressed(BTN_NAV_CENTER)) {
    val |= BTN_BIT_NAV_CENTER;
  }
#if PL_CONFIG_USE_BUTTON_NEXT_PREV
  if (BTN_IsPressed(BTN_NAV_NEXT)) {
    val |= BTN_BIT_NAV_NEXT;
  }
  if (BTN_IsPressed(BTN_NAV_PREV)) {
    val |= BTN_BIT_NAV_PREV;
  }
#endif
  return val;
}

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

static void gpio_IsrCallback(uint gpio, uint32_t events) {
  uint32_t button = 0; /* init */
  BaseType_t xHigherPriorityTaskWoken = false;

  switch(gpio) {
    case BUTTONS_PINS_NAV_CENTER_PIN:
      button = BTN_BIT_NAV_CENTER;
      break;
    case BUTTONS_PINS_NAV_UP_PIN:
      button = BTN_BIT_NAV_UP;
      break;
    case BUTTONS_PINS_NAV_DOWN_PIN:
      button = BTN_BIT_NAV_DOWN;
      break;
    case BUTTONS_PINS_NAV_LEFT_PIN:
      button = BTN_BIT_NAV_LEFT;
      break;
    case BUTTONS_PINS_NAV_RIGHT_PIN:
      button = BTN_BIT_NAV_RIGHT;
      break;
#if PL_CONFIG_USE_BUTTON_NEXT_PREV
    case BUTTONS_PINS_NAV_NEXT_PIN:
      button = BTN_BIT_NAV_NEXT;
      break;
    case BUTTONS_PINS_NAV_PREV_PIN:
      button = BTN_BIT_NAV_PREV;
      break;
#endif
    default:
      button = 0;
      break;
  }
  if (button!=0) {
    Debounce_StartDebounceFromISR(button, &xHigherPriorityTaskWoken);
  }
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

  btnConfig.hw.pin = BUTTONS_PINS_NAV_CENTER_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_CENTER].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.pin = BUTTONS_PINS_NAV_LEFT_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_LEFT].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.pin = BUTTONS_PINS_NAV_RIGHT_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_RIGHT].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.pin = BUTTONS_PINS_NAV_UP_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_UP].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.pin = BUTTONS_PINS_NAV_DOWN_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_DOWN].handle = McuBtn_InitButton(&btnConfig);

#if PL_CONFIG_USE_BUTTON_NEXT_PREV
  btnConfig.hw.pin = BUTTONS_PINS_NAV_NEXT_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_NEXT].handle = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.pin = BUTTONS_PINS_NAV_PREV_PIN;
  btnConfig.hw.pull = McuGPIO_PULL_UP;
  BTN_Infos[BTN_NAV_PREV].handle = McuBtn_InitButton(&btnConfig);
#endif

  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAV_CENTER_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAV_UP_PIN,     GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAV_DOWN_PIN,   GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAV_LEFT_PIN,   GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAV_RIGHT_PIN,  GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
#if PL_CONFIG_USE_BUTTON_NEXT_PREV
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAV_NEXT_PIN,   GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
  gpio_set_irq_enabled_with_callback(BUTTONS_PINS_NAV_PREV_PIN,   GPIO_IRQ_EDGE_FALL, true, &gpio_IsrCallback);
#endif
}

#endif /* #if PL_CONFIG_USE_BUTTONS */
