/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds.h"
#include "McuLED.h"
#include "board.h" /* defines the BOARD_LED_ macros */

/* LEDs on Seeed Arch Mix i.MX RT1052 board */
#define LED_RED_GPIO        GPIO1
#define LED_RED_PIN         9U

#define LED_GREEN_GPIO      GPIO1
#define LED_GREEN_PIN       10U

#define LED_BLUE_GPIO       GPIO1
#define LED_BLUE_PIN        11U


McuLED_Handle_t LEDS_Blue, LEDS_Green, LEDS_Red;

void LEDS_Deinit(void) {
  LEDS_Blue = McuLED_DeinitLed(LEDS_Blue);
  LEDS_Red = McuLED_DeinitLed(LEDS_Red);
  LEDS_Green = McuLED_DeinitLed(LEDS_Green);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;

  config.hw.pin = LED_BLUE_PIN;
  config.hw.gpio = LED_BLUE_GPIO;
  LEDS_Blue = McuLED_InitLed(&config);

  config.hw.pin = LED_GREEN_PIN;
  config.hw.gpio = LED_GREEN_GPIO;
  LEDS_Green = McuLED_InitLed(&config);

  config.hw.pin = LED_RED_PIN;
  config.hw.gpio = LED_RED_GPIO;
  LEDS_Red = McuLED_InitLed(&config);
}
