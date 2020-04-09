/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "leds.h"
#include "McuLED.h"
#include "pin_mux.h"

/* LED on the board */
#define LED_GREEN_GPIO       BOARD_INITPINS_LED_GREEN_GPIO
#define LED_GREEN_PIN        BOARD_INITPINS_LED_GREEN_GPIO_PIN

McuLED_Handle_t LEDS_Led;

void LEDS_Deinit(void) {
  LEDS_Led = McuLED_DeinitLed(LEDS_Led);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;
  config.hw.gpio = LED_GREEN_GPIO;
  config.hw.pin = LED_GREEN_PIN;
  LEDS_Led = McuLED_InitLed(&config);
}
