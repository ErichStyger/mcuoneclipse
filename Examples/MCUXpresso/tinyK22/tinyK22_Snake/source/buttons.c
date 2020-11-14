/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "buttons.h"
#include "buttons_config.h"
#include <assert.h>
#include "McuButton.h"
#if McuLib_CONFIG_CPU_IS_KINETIS
  #include "fsl_port.h"
#elif McuLib_CONFIG_CPU_IS_LPC
  #include "fsl_pint.h"
  #include "fsl_syscon.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif
#include "Snake.h"

#if McuLib_CONFIG_CPU_IS_KINETIS
static McuBtn_Handle_t btnUp, btnDown, btnLeft, btnRight, btnCenter;
#endif
typedef struct BTN_Desc_t {
  McuBtn_Handle_t handle; /* handle of pin */
  volatile bool isPressed; /* flag set by ISR if button was pressed */
} BTN_Desc_t;

static BTN_Desc_t BTN_Infos[BTN_NAV_NOF_BUTTONS];

bool BTN_IsPressed(BTN_Buttons_e btn) {
  assert(btn<BTN_NAV_NOF_BUTTONS);
  return McuBtn_IsOn(BTN_Infos[btn].handle);
}

bool BTN_WasPressed(BTN_Buttons_e btn) {
  assert(btn<BTN_NAV_NOF_BUTTONS);
  if (BTN_Infos[btn].isPressed) { /* pressed? */
    BTN_Infos[btn].isPressed = false; /* reset flag */
    return true; /* pressed */
  }
  return false; /* not pressed */
}

#if McuLib_CONFIG_CPU_IS_KINETIS
#if TINYK22_HAT_VERSION>3
  /* all buttons are on PTB */
void PORTA_IRQHandler(void) {
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  flags = GPIO_PortGetInterruptFlags(GPIOA);
  if (flags&(1U<<BUTTONS_PINS_HATNAVLEFT_PIN)) {
    GPIO_PortClearInterruptFlags(BUTTONS_PINS_HATNAVLEFT_GPIO, 1U<<BUTTONS_PINS_HATNAVLEFT_PIN);
    BTN_Infos[BTN_NAV_LEFT].isPressed = true;
    SNAKE_SendButtonEventFromISR(SNAKE_LEFT_EVENT, &xHigherPriorityTaskWoken);
  }
  if (flags&(1U<<BUTTONS_PINS_HATNAVRIGHT_PIN)) {
    GPIO_PortClearInterruptFlags(BUTTONS_PINS_HATNAVRIGHT_GPIO, 1U<<BUTTONS_PINS_HATNAVRIGHT_PIN);
    BTN_Infos[BTN_NAV_RIGHT].isPressed = true;
    SNAKE_SendButtonEventFromISR(SNAKE_RIGHT_EVENT, &xHigherPriorityTaskWoken);
  }
  if (xHigherPriorityTaskWoken) {
    taskYIELD();
  }
  __DSB();
}
#endif
#endif

#if McuLib_CONFIG_CPU_IS_KINETIS
void PORTB_IRQHandler(void) {
  uint32_t flags;
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  flags = GPIO_PortGetInterruptFlags(GPIOB);
  if (flags&(1U<<BUTTONS_PINS_HATNAVCENTER_PIN)) {
    GPIO_PortClearInterruptFlags(BUTTONS_PINS_HATNAVCENTER_GPIO, 1U<<BUTTONS_PINS_HATNAVCENTER_PIN);
    BTN_Infos[BTN_NAV_CENTER].isPressed = true;
    SNAKE_SendButtonEventFromISR(SNAKE_ENTER_EVENT, &xHigherPriorityTaskWoken);
  }
  if (flags&(1U<<BUTTONS_PINS_HATNAVDOWN_PIN)) {
    GPIO_PortClearInterruptFlags(BUTTONS_PINS_HATNAVDOWN_GPIO, 1U<<BUTTONS_PINS_HATNAVDOWN_PIN);
    BTN_Infos[BTN_NAV_DOWN].isPressed = true;
    SNAKE_SendButtonEventFromISR(SNAKE_DOWN_EVENT, &xHigherPriorityTaskWoken);
  }
  if (flags&(1U<<BUTTONS_PINS_HATNAVUP_PIN)) {
    GPIO_PortClearInterruptFlags(BUTTONS_PINS_HATNAVUP_GPIO, 1U<<BUTTONS_PINS_HATNAVUP_PIN);
    BTN_Infos[BTN_NAV_UP].isPressed = true;
    SNAKE_SendButtonEventFromISR(SNAKE_UP_EVENT, &xHigherPriorityTaskWoken);
  }
#if TINYK22_HAT_VERSION==3 /* all buttons are on PTB */
  if (flags&(1U<<BUTTONS_PINS_HATNAVLEFT_PIN)) {
    GPIO_PortClearInterruptFlags(BUTTONS_PINS_HATNAVLEFT_GPIO, 1U<<BUTTONS_PINS_HATNAVLEFT_PIN);
    BTN_Infos[BTN_NAV_LEFT].isPressed = true;
    SNAKE_SendButtonEventFromISR(SNAKE_LEFT_EVENT, &xHigherPriorityTaskWoken);
  }
  if (flags&(1U<<BUTTONS_PINS_HATNAVRIGHT_PIN)) {
    GPIO_PortClearInterruptFlags(BUTTONS_PINS_HATNAVRIGHT_GPIO, 1U<<BUTTONS_PINS_HATNAVRIGHT_PIN);
    BTN_Infos[BTN_NAV_RIGHT].isPressed = true;
    SNAKE_SendButtonEventFromISR(SNAKE_RIGHT_EVENT, &xHigherPriorityTaskWoken);
  }
#endif
  if (xHigherPriorityTaskWoken) {
    taskYIELD();
  }
  __DSB();
}
#endif

#if McuLib_CONFIG_CPU_IS_LPC
static void pint_intr_callback(pint_pin_int_t pintr, uint32_t pmatch_status) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #define MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT (0)
  McuSystemView_RecordEnterISR();
  McuSystemView_Print((const char*)"Pressed button\r\n");
  McuSystemView_OnUserStart(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
#endif
  BTN_Infos[BTN_USER].isPressed = true;
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  McuSystemView_OnUserStop(MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT);
  McuSystemView_RecordExitISR();
#endif
}
#endif

void BTN_Deinit(void) {
#if McuLib_CONFIG_CPU_IS_KINETIS
#if TINYK22_HAT_VERSION==3
  /* all buttons are on PTB */
  DisableIRQ(PORTB_IRQn);
#else
  DisableIRQ(PORTA_IRQn);
  DisableIRQ(PORTB_IRQn);
#endif
  btnCenter = McuBtn_DeinitButton(btnCenter);
  btnUp = McuBtn_DeinitButton(btnUp);
  btnDown = McuBtn_DeinitButton(btnDown);
  btnLeft = McuBtn_DeinitButton(btnLeft);
  btnRight = McuBtn_DeinitButton(btnRight);
#endif
}

void BTN_Init(void) {
#if McuLib_CONFIG_CPU_IS_KINETIS
  McuBtn_Config_t btnConfig;

  BUTTONS_ENABLE_CLOCK();
  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.gpio = BUTTONS_PINS_HATNAVCENTER_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_HATNAVCENTER_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_HATNAVCENTER_PIN;
  btnCenter = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_HATNAVLEFT_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_HATNAVLEFT_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_HATNAVLEFT_PIN;
  btnLeft = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_HATNAVRIGHT_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_HATNAVRIGHT_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_HATNAVRIGHT_PIN;
  btnRight = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_HATNAVUP_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_HATNAVUP_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_HATNAVUP_PIN;
  btnUp = McuBtn_InitButton(&btnConfig);

  btnConfig.hw.gpio = BUTTONS_PINS_HATNAVDOWN_GPIO;
  btnConfig.hw.port = BUTTONS_PINS_HATNAVDOWN_PORT;
  btnConfig.hw.pin = BUTTONS_PINS_HATNAVDOWN_PIN;
  btnDown = McuBtn_InitButton(&btnConfig);

#if TINYK22_HAT_VERSION==3
  /* all buttons are on PTB */
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVLEFT_PORT,  BUTTONS_PINS_HATNAVLEFT_PIN,  kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVRIGHT_PORT, BUTTONS_PINS_HATNAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVDOWN_PORT, BUTTONS_PINS_HATNAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVUP_PORT,   BUTTONS_PINS_HATNAVUP_PIN,   kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVCENTER_PORT, BUTTONS_PINS_HATNAVCENTER_PIN, kPORT_InterruptFallingEdge);
  NVIC_SetPriority(PORTB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTB_IRQn);
#else
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVLEFT_PORT,  BUTTONS_PINS_HATNAVLEFT_PIN,  kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVRIGHT_PORT, BUTTONS_PINS_HATNAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  NVIC_SetPriority(PORTA_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTA_IRQn);

  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVDOWN_PORT, BUTTONS_PINS_HATNAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVUP_PORT,   BUTTONS_PINS_HATNAVUP_PIN,   kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(BUTTONS_PINS_HATNAVCENTER_PORT, BUTTONS_PINS_HATNAVCENTER_PIN, kPORT_InterruptFallingEdge);
  NVIC_SetPriority(PORTB_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
  EnableIRQ(PORTB_IRQn);
#endif
#elif McuLib_CONFIG_CPU_IS_LPC
  /* user button on LPC845-BRK board: PIO0_4 */

  McuBtn_Config_t btnConfig;

  BUTTONS_ENABLE_CLOCK();
  McuBtn_GetDefaultConfig(&btnConfig);
  btnConfig.isLowActive = true;

  btnConfig.hw.gpio = BUTTONS_USER_GPIO;
  btnConfig.hw.port = BUTTONS_USER_PORT;
  btnConfig.hw.pin = BUTTONS_USER_PIN;
  btnConfig.hw.iocon = BUTTONS_USER_IOCON;
  BTN_Infos[BTN_USER].handle = McuBtn_InitButton(&btnConfig);

  SYSCON_AttachSignal(SYSCON, kPINT_PinInt0, kSYSCON_GpioPort0Pin4ToPintsel);

  PINT_Init(PINT); /* Initialize PINT */
  /* Setup Pin Interrupt 0 for rising edge */
  PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableFallEdge, pint_intr_callback);
  /* Enable callbacks for PINT0 by Index */
  PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);
#endif
}
