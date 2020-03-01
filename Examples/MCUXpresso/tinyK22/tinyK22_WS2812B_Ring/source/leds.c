/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "leds.h"
#include "McuLED.h"

#define PINS_LEDBLUE_GPIO       GPIOC
#define PINS_LEDBLUE_PORT       PORTC
#define PINS_LEDBLUE_PIN        2U

McuLED_Handle_t tinyLED;

void LEDS_Deinit(void) {
  tinyLED = McuLED_DeinitLed(tinyLED);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;
  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  tinyLED = McuLED_InitLed(&config);
}
