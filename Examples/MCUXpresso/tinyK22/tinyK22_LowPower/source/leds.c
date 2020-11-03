/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds.h"
#include "McuLED.h"

#if 0 /* tinyK22 */
  #define PINS_LEDBLUE_GPIO       GPIOC
  #define PINS_LEDBLUE_PORT       PORTC
  #define PINS_LEDBLUE_PIN        2U
#elif 1 /* FRDM-K22F */
/* blue: PTD5 */
  #define PINS_LEDBLUE_GPIO       GPIOD
  #define PINS_LEDBLUE_PORT       PORTD
  #define PINS_LEDBLUE_PIN        5U

  /* red: PTA1 */
  #define PINS_LEDRED_PIN     1
  #define PINS_LEDRED_PORT    PORTA
  #define PINS_LEDRED_GPIO    GPIOA

  /* green: PTA2 */
  #define PINS_LEDGREEN_PIN   2
  #define PINS_LEDGREEN_PORT  PORTA
  #define PINS_LEDGREEN_GPIO  GPIOA
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
