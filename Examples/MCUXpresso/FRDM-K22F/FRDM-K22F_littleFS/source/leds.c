/*
 * Copyright (c) 2020-2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "leds.h"
#include "McuLED.h"

/* LED on the board */
#if McuLib_CONFIG_CPU_IS_KINETIS /* tinyK22 & FRDM-K22F */
  #if PL_CONFIG_IS_TINY_K22
    #define LED_BLUE_GPIO       GPIOC
    #define LED_BLUE_PORT       PORTC
    #define LED_BLUE_PIN        2U
    #define LED_INIT_CLOCKS()      CLOCK_EnableClock(kCLOCK_PortC);
  #else /* FRDM-K22F */
    #define LED_BLUE_GPIO       GPIOD
    #define LED_BLUE_PORT       PORTD
    #define LED_BLUE_PIN        5U
    #define LED_INIT_CLOCKS()      CLOCK_EnableClock(kCLOCK_PortD);
  #endif
#endif

McuLED_Handle_t LEDS_Led;

void LEDS_Deinit(void) {
  LEDS_Led = McuLED_DeinitLed(LEDS_Led);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  LED_INIT_CLOCKS();
  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;
  config.hw.gpio = LED_BLUE_GPIO;
  config.hw.port = LED_BLUE_PORT;
  config.hw.pin = LED_BLUE_PIN;
  LEDS_Led = McuLED_InitLed(&config);
}
