/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds.h"
#include "McuLED.h"

/* red */
#define PINS_LEDRED_GPIO       GPIOB
#define PINS_LEDRED_PORT       PORTB
#define PINS_LEDRED_PIN        18U

/* green */
#define PINS_LEDGREEN_GPIO     GPIOB
#define PINS_LEDGREEN_PORT     PORTB
#define PINS_LEDGREEN_PIN      19U

/* blue */
#define PINS_LEDBLUE_GPIO      GPIOD
#define PINS_LEDBLUE_PORT      PORTD
#define PINS_LEDBLUE_PIN       1U

McuLED_Handle_t LEDS_red, LEDS_green, LEDS_blue;

void LEDS_Deinit(void) {
  LEDS_red = McuLED_DeinitLed(LEDS_red);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDRED_PIN;
  config.hw.port = PINS_LEDRED_PORT;
  config.hw.gpio = PINS_LEDRED_GPIO;
  LEDS_red = McuLED_InitLed(&config);

  config.hw.pin = PINS_LEDGREEN_PIN;
  config.hw.port = PINS_LEDGREEN_PORT;
  config.hw.gpio = PINS_LEDGREEN_GPIO;
  LEDS_green = McuLED_InitLed(&config);

  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  LEDS_blue = McuLED_InitLed(&config);
}
