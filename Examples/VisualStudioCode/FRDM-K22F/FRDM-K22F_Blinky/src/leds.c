/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "leds.h"
#include "McuLED.h"

/* LEDs on the FRDM-K22 board */
#define LED_RED_GPIO        GPIOA
#define LED_RED_PORT        PORTA
#define LED_RED_PIN         1U

#define LED_GREEN_GPIO      GPIOA
#define LED_GREEN_PORT      PORTA
#define LED_GREEN_PIN       2U

#define LED_BLUE_GPIO       GPIOD
#define LED_BLUE_PORT       PORTD
#define LED_BLUE_PIN        5U

McuLED_Handle_t LEDS_LedRed, LEDS_LedGreen, LEDS_LedBlue;

void LEDS_Deinit(void) {
  LEDS_LedRed = McuLED_DeinitLed(LEDS_LedRed);
  LEDS_LedGreen = McuLED_DeinitLed(LEDS_LedGreen);
  LEDS_LedBlue = McuLED_DeinitLed(LEDS_LedBlue);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;

  config.hw.gpio = LED_RED_GPIO;
  config.hw.port = LED_RED_PORT;
  config.hw.pin = LED_RED_PIN;
  LEDS_LedRed = McuLED_InitLed(&config);

  config.hw.gpio = LED_GREEN_GPIO;
  config.hw.port = LED_GREEN_PORT;
  config.hw.pin = LED_GREEN_PIN;
  LEDS_LedGreen = McuLED_InitLed(&config);

  config.hw.gpio = LED_BLUE_GPIO;
  config.hw.port = LED_BLUE_PORT;
  config.hw.pin = LED_BLUE_PIN;
  LEDS_LedBlue = McuLED_InitLed(&config);
}
