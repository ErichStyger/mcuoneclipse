/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds.h"
#include "McuLED.h"
#include "board.h" /* defines the BOARD_LED_ macros */

/* LEDs on the board */
#define LED_BLUE_GPIO       GPIO
#define LED_BLUE_PORT       0U
#define LED_BLUE_PIN        19U

McuLED_Handle_t LEDS_Blue;

void LEDS_Deinit(void) {
  LEDS_Blue = McuLED_DeinitLed(LEDS_Blue);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;

  config.hw.gpio = LED_BLUE_GPIO;
  config.hw.port = LED_BLUE_PORT;
  config.hw.pin = LED_BLUE_PIN;
  LEDS_Blue = McuLED_InitLed(&config);
}
