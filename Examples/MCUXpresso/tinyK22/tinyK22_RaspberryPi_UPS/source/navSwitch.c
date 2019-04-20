/*
 * navSwitch.c
 *
 *  Created on: 12.04.2019
 *      Author: Erich Styger
 */
#include "platform.h"
#include "navSwitch.h"
#include "McuWait.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "leds.h"
#include "lv.h"

#if 0
static bool isBtnPressed(void) {
  if (GPIO_PinRead(PINS_HATNAVDOWN_GPIO, PINS_HATNAVDOWN_PIN)==0) {
    return true;
  }
  if (GPIO_PinRead(PINS_HATNAVUP_GPIO, PINS_HATNAVUP_PIN)==0) {
    return true;
  }
  if (GPIO_PinRead(PINS_HATNAVLEFT_GPIO, PINS_HATNAVLEFT_PIN)==0) {
    return true;
  }
  if (GPIO_PinRead(PINS_HATNAVRIGHT_GPIO, PINS_HATNAVRIGHT_PIN)==0) {
    return true;
  }
#if 1 /* pulled down by raspy? */
  if (GPIO_PinRead(PINS_HATNAVPUSH_GPIO, PINS_HATNAVPUSH_PIN)==0) {
    return true;
  }
#endif
  return false;
}
#endif

void PORTB_IRQHandler(void) {
  /* Clear external interrupt flag. */
  uint32_t flags;

  flags = GPIO_PortGetInterruptFlags(GPIOB);
  if (flags&(1U<<PINS_HATNAVLEFT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVLEFT_GPIO, 1U<<PINS_HATNAVLEFT_PIN);
    McuLED_Neg(hatBlueLED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_HW_BTN_LEFT, LV_MASK_PRESSED);
    LV_ButtonEvent(LV_HW_BTN_LEFT, LV_MASK_RELEASED);
#endif
  }
  if (flags&(1U<<PINS_HATNAVRIGHT_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVRIGHT_GPIO, 1U<<PINS_HATNAVRIGHT_PIN);
    McuLED_Neg(hatRedLED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_HW_BTN_RIGHT, LV_MASK_PRESSED);
    LV_ButtonEvent(LV_HW_BTN_RIGHT, LV_MASK_RELEASED);
#endif
  }
  if (flags&(1U<<PINS_HATNAVUP_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVUP_GPIO, 1U<<PINS_HATNAVUP_PIN);
    McuLED_Neg(hatGreenLED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_HW_BTN_UP, LV_MASK_PRESSED);
    LV_ButtonEvent(LV_HW_BTN_UP, LV_MASK_RELEASED);
#endif
  }
  if (flags&(1U<<PINS_HATNAVDOWN_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVDOWN_GPIO, 1U<<PINS_HATNAVDOWN_PIN);
    McuLED_Neg(hatYellowLED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_PRESSED);
    LV_ButtonEvent(LV_HW_BTN_DOWN, LV_MASK_RELEASED);
#endif
  }
  if (flags&(1U<<PINS_HATNAVPUSH_PIN)) {
    GPIO_PortClearInterruptFlags(PINS_HATNAVPUSH_GPIO, 1U<<PINS_HATNAVPUSH_PIN);
    McuLED_Neg(hatBlueLED);
#if PL_CONFIG_HAS_GUI_KEY_NAV
    LV_ButtonEvent(LV_HW_BTN_CENTER, LV_MASK_PRESSED);
    LV_ButtonEvent(LV_HW_BTN_CENTER, LV_MASK_RELEASED);
#endif
  }
  __DSB();
}

void NAV_ScanKeys(void) {
  /* using interrupts */
}

void NAV_Init(void) {
  PORT_SetPinInterruptConfig(PINS_HATNAVUP_PORT, PINS_HATNAVUP_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVDOWN_PORT, PINS_HATNAVDOWN_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVLEFT_PORT, PINS_HATNAVLEFT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVRIGHT_PORT, PINS_HATNAVRIGHT_PIN, kPORT_InterruptFallingEdge);
  PORT_SetPinInterruptConfig(PINS_HATNAVPUSH_PORT, PINS_HATNAVPUSH_PIN, kPORT_InterruptFallingEdge);
  EnableIRQ(PORTB_IRQn);
}

void NAV_Deinit(void) {
  DisableIRQ(PORTB_IRQn);
}
