/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "leds.h"
#include "McuLED.h"
#include "board.h" /* defines the BOARD_LED_ macros */

#ifdef BOARD_LED_BLUE_GPIO
  #define LED_BLUE_GPIO    BOARD_LED_BLUE_GPIO
#else
  #define LED_BLUE_GPIO    GPIOC
#endif
#ifdef BOARD_LED_BLUE_GPIO_PORT
  #define LED_BLUE_PORT    BOARD_LED_BLUE_PORT
#else
  #define LED_BLUE_PORT    PORTC
#endif
#ifdef BOARD_LED_BLUE_GPIO_PIN
  #define LED_BLUE_PIN     BOARD_LED_BLUE_GPIO_PIN
#else
  #define LED_BLUE_PIN     2U
#endif

McuLED_Handle_t LED_Blue;

void LEDS_Deinit(void) {
  LED_Blue = McuLED_DeinitLed(LED_Blue);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;

  config.hw.pin = LED_BLUE_PIN;
  config.hw.port = LED_BLUE_PORT;
  config.hw.gpio = LED_BLUE_GPIO;
  LED_Blue = McuLED_InitLed(&config);
}
