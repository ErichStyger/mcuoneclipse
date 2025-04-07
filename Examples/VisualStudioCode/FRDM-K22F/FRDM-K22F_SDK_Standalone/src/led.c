/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "led.h"
#include "McuLed.h"

/* tinyK22     : blue LED (PTC2)
   FRDM-K22F   : blue LED (PTD5)
   LPC55S69_EVK: blue LED (PIO1_4)
   MCU-Link Pro: green LED1 (PIO1_12)
 */
static McuLED_Handle_t led1;

#if LED_CONFIG_HAS_2_LED
  /* tinyK22     : n/a
    FRDM-K22F   : green LED (PTA2)
    LPC55S69_EVK: green LED (PIO1_7)
    MCU-Link Pro: green LED3 (PIO0_5)
  */
  static McuLED_Handle_t led2;
#endif

void Led1_On(void) {
  McuLED_On(led1);
}

void Led1_Off(void) {
  McuLED_Off(led1);
}

void Led1_Toggle(void) {
  McuLED_Toggle(led1);
}

#if LED_CONFIG_HAS_2_LED
  void Led2_On(void) {
    McuLED_On(led2);
  }

  void Led2_Off(void) {
    McuLED_Off(led2);
  }

  void Led2_Toggle(void) {
    McuLED_Toggle(led2);
  }
#endif

void Led_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;
#if McuLib_CONFIG_CPU_IS_LPC55xx
  #if PL_CONFIG_IS_LPC55S69_EVK
    /* blue: P1_4 */
    config.hw.gpio = GPIO;
    config.hw.port = 1;
    config.hw.pin = 4;
    config.isLowActive = true;
  #else
    /* green: P1_12 */
    config.hw.gpio = GPIO;
    config.hw.port = 1;
    config.hw.pin = 12;
    config.isLowActive = true;
  #endif
#elif McuLib_CONFIG_CPU_IS_KINETIS
  #if PL_CONFIG_IS_FRDM_K22F
    CLOCK_EnableClock(kCLOCK_PortD); /* port for LED */
    config.hw.gpio = GPIOD;
    config.hw.port = PORTD;
    config.hw.pin = 5U;
  #else
    CLOCK_EnableClock(kCLOCK_PortC); /* port for LED */
    config.hw.gpio = GPIOC;
    config.hw.port = PORTC;
    config.hw.pin = 2U;
  #endif
#endif
  led1 = McuLED_InitLed(&config);

#if LED_CONFIG_HAS_2_LED
  #if McuLib_CONFIG_CPU_IS_LPC55xx
    #if PL_CONFIG_IS_LPC55S69_EVK
      /* blue: P1_7 */
      config.hw.gpio = GPIO;
      config.hw.port = 1;
      config.hw.pin = 7;
      config.isLowActive = true;
    #else
      /* green: P0_5 */
      config.hw.gpio = GPIO;
      config.hw.port = 0;
      config.hw.pin = 5;
      config.isLowActive = true;
    #endif
  #elif McuLib_CONFIG_CPU_IS_KINETIS
    #if PL_CONFIG_IS_FRDM_K22F
      CLOCK_EnableClock(kCLOCK_PortA);
      config.hw.gpio = GPIOA;
      config.hw.port = PORTA;
      config.hw.pin = 2U;
    #else
      #error "no 2nd LED"
    #endif
  #endif
  led2 = McuLED_InitLed(&config);
#endif
}
