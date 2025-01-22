/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "McuLED.h"
#include "leds_config.h"
#include "leds.h"

#if LEDS_CONFIG_HAS_RED_LED
  static McuLED_Handle_t ledRed;
#endif
#if LEDS_CONFIG_HAS_GREEN_LED
  static McuLED_Handle_t ledGreen;
#endif
#if LEDS_CONFIG_HAS_BLUE_LED
  static McuLED_Handle_t ledBlue;
#endif

void Leds_On(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_On(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_On(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_On(ledBlue); break;
  #endif
    default:
      break; /* error */
  }
}

void Leds_Off(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_Off(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_Off(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_Off(ledBlue); break;
  #endif
    default:
      break; /* error */
  }
}

void Leds_Neg(LEDS_Leds_e led) {
  switch(led) {
  #if LEDS_CONFIG_HAS_RED_LED
    case LEDS_RED:        McuLED_Toggle(ledRed); break;
  #endif
  #if LEDS_CONFIG_HAS_GREEN_LED
    case LEDS_GREEN:      McuLED_Toggle(ledGreen); break;
  #endif
  #if LEDS_CONFIG_HAS_BLUE_LED
    case LEDS_BLUE:       McuLED_Toggle(ledBlue); break;
  #endif
    default:
      break; /* error */
  }
}

void Leds_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isOnInit = false;

#if LEDS_CONFIG_HAS_RED_LED
  config.hw.pin = LEDS_CONFIG_RED_PIN;
  config.isOnInit = false;
  config.isLowActive = LEDS_CONFIG_RED_LOW_ACTIVE;
  ledRed = McuLED_InitLed(&config);
  if (ledRed==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  config.hw.pin = LEDS_CONFIG_GREEN_PIN;
  config.isOnInit = false;
  config.isLowActive = LEDS_CONFIG_GREEN_LOW_ACTIVE;
  ledGreen = McuLED_InitLed(&config);
  if (ledGreen==NULL) {
    for(;;) {}
  }
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  config.hw.pin = LEDS_CONFIG_BLUE_PIN;
  config.isOnInit = false;
  config.isLowActive = LEDS_CONFIG_BLUE_LOW_ACTIVE;
  ledBlue = McuLED_InitLed(&config);
  if (ledBlue==NULL) {
    for(;;) {}
  }
#endif
}

void Leds_Deinit(void) {
#if LEDS_CONFIG_HAS_RED_LED
  ledRed = McuLED_DeinitLed(ledRed);
#endif
#if LEDS_CONFIG_HAS_RED_GREEN
  ledGreen = McuLED_DeinitLed(ledGreen);
#endif
#if LEDS_CONFIG_HAS_RED_BLUE
  ledBlue = McuLED_DeinitLed(ledBlue);
#endif
}
