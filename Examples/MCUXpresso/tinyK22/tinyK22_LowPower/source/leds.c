/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds.h"
#include "McuLED.h"

#if 1 /* tinyK22 */
  #define PINS_LEDBLUE_GPIO       GPIOC
  #define PINS_LEDBLUE_PORT       PORTC
  #define PINS_LEDBLUE_PIN        2U
#elif 1 /* FRDM-K22F */
  #define PINS_LEDBLUE_GPIO       GPIOD
  #define PINS_LEDBLUE_PORT       PORTD
  #define PINS_LEDBLUE_PIN        5U
#endif

McuLED_Handle_t tinyLED;

void LEDS_Deinit(void) {
  tinyLED = McuLED_DeinitLed(tinyLED);
  McuLED_Deinit(); /* de-initialize LED module */
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  tinyLED = McuLED_InitLed(&config);
}
