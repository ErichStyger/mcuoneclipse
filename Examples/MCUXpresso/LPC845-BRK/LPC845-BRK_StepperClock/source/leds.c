/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "leds.h"
#include "McuLED.h"
#include "board.h" /* defines the BOARD_LED_ macros */

/* LEDs on LPC845-BRK */
#define LED_GREEN_GPIO      GPIO
#define LED_GREEN_PORT      1U
#define LED_GREEN_PIN       0U

#define LED_BLUE_GPIO       GPIO
#define LED_BLUE_PORT       1U
#define LED_BLUE_PIN        1U

#define LED_RED_GPIO        GPIO
#define LED_RED_PORT        1U
#define LED_RED_PIN         2U

McuLED_Handle_t LEDS_Blue, LEDS_Green, LEDS_Red;

void LEDS_Deinit(void) {
  LEDS_Blue = McuLED_DeinitLed(LEDS_Blue);
  LEDS_Green = McuLED_DeinitLed(LEDS_Green);
  LEDS_Green = McuLED_DeinitLed(LEDS_Green);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;

  config.hw.pin = LED_BLUE_PIN;
  config.hw.port = LED_BLUE_PORT;
  config.hw.gpio = LED_BLUE_GPIO;
  LEDS_Blue = McuLED_InitLed(&config);

  config.hw.pin = LED_GREEN_PIN;
  config.hw.port = LED_GREEN_PORT;
  config.hw.gpio = LED_GREEN_GPIO;
  LEDS_Green = McuLED_InitLed(&config);

  config.hw.pin = LED_RED_PIN;
  config.hw.port = LED_RED_PORT;
  config.hw.gpio = LED_RED_GPIO;
  LEDS_Red = McuLED_InitLed(&config);
}
