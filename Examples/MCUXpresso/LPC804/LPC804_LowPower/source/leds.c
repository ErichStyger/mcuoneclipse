/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds_config.h"
#include "leds.h"
#include "McuLED.h"

static McuLED_Handle_t ledRed, ledGreen;

void LEDS_On(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_RED:        McuLED_On(ledRed); break;
    case LEDS_GREEN:      McuLED_On(ledGreen); break;
    default:
      break; /* error */
  }
}

void LEDS_Off(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_RED:        McuLED_Off(ledRed); break;
    case LEDS_GREEN:      McuLED_Off(ledGreen); break;
    default:
      break; /* error */
  }
}

void LEDS_Neg(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_RED:        McuLED_Toggle(ledRed); break;
    case LEDS_GREEN:      McuLED_Toggle(ledGreen); break;
    default:
      break; /* error */
  }
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  LEDS_ENABLE_CLOCK();
  McuLED_GetDefaultConfig(&config);
  config.isOnInit = false;
  config.isLowActive = false;
  config.hw.gpio = LEDS_LED_RED_GPIO;
  config.hw.port = LEDS_LED_RED_PORT;
  config.hw.pin = LEDS_LED_RED_PIN;
  config.hw.iocon = LEDS_LED_RED_IOCON;
  ledRed = McuLED_InitLed(&config);
  if (ledRed==NULL) {
    for(;;) {}
  }

  config.isLowActive = false;
  config.hw.gpio = LEDS_LED_GREEN_GPIO;
  config.hw.port = LEDS_LED_GREEN_PORT;
  config.hw.pin = LEDS_LED_GREEN_PIN;
  config.hw.iocon = LEDS_LED_GREEN_IOCON;
  ledGreen = McuLED_InitLed(&config);
  if (ledGreen==NULL) {
    for(;;) {}
  }
}

void LED_Deinit(void) {
  ledRed = McuLED_DeinitLed(ledRed);
  ledGreen = McuLED_DeinitLed(ledGreen);
}
