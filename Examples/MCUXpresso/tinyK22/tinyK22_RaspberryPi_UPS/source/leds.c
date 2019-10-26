/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds.h"
#include "McuLED.h"

McuLED_Handle_t tinyLED, hatRedLED, hatBlueLED, hatGreenLED, hatYellowLED;

void LEDS_Deinit(void) {
  tinyLED = McuLED_DeinitLed(tinyLED);
  hatBlueLED = McuLED_DeinitLed(hatBlueLED);
  hatRedLED = McuLED_DeinitLed(hatRedLED);
  hatGreenLED = McuLED_DeinitLed(hatGreenLED);
  hatYellowLED = McuLED_DeinitLed(hatYellowLED);

  McuLED_Deinit(); /* de-initialize LED module */
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_Init(); /* initialize LED module */

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  tinyLED = McuLED_InitLed(&config);

  /* hat LEDs are high active */
  config.isLowActive = false;

  config.hw.pin = PINS_HATLEDBLUE_PIN;
  config.hw.port = PINS_HATLEDBLUE_PORT;
  config.hw.gpio = PINS_HATLEDBLUE_GPIO;
  hatBlueLED = McuLED_InitLed(&config);

  config.hw.pin = PINS_HATLEDGREEN_PIN;
  config.hw.port = PINS_HATLEDGREEN_PORT;
  config.hw.gpio = PINS_HATLEDGREEN_GPIO;
  hatGreenLED = McuLED_InitLed(&config);

  config.hw.pin = PINS_HATLEDRED_PIN;
  config.hw.port = PINS_HATLEDRED_PORT;
  config.hw.gpio = PINS_HATLEDRED_GPIO;
  hatRedLED = McuLED_InitLed(&config);

  config.hw.pin = PINS_HATLEDYELLOW_PIN;
  config.hw.port = PINS_HATLEDYELLOW_PORT;
  config.hw.gpio = PINS_HATLEDYELLOW_GPIO;
  hatYellowLED = McuLED_InitLed(&config);
}
