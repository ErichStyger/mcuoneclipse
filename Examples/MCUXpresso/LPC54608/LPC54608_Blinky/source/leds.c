/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds_config.h"
#include "leds.h"
#include "McuLED.h"

static McuLED_Handle_t led1, led2, led3;

void LEDS_On(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_1:      McuLED_On(led1); break;
    case LEDS_2:      McuLED_On(led2); break;
    case LEDS_3:      McuLED_On(led3); break;
    default:
      break; /* error */
  }
}

void LEDS_Off(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_1:      McuLED_Off(led1); break;
    case LEDS_2:      McuLED_Off(led2); break;
    case LEDS_3:      McuLED_Off(led3); break;
    default:
      break; /* error */
  }
}

void LEDS_Neg(LEDS_Leds_e led) {
  switch(led) {
    case LEDS_1:      McuLED_Toggle(led1); break;
    case LEDS_2:      McuLED_Toggle(led2); break;
    case LEDS_3:      McuLED_Toggle(led3); break;
    default:
      break; /* error */
  }
}

#include "fsl_iocon.h"
#include "pin_mux.h"

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isOnInit = false;
  config.isLowActive = true;
  config.hw.gpio = LEDS_LED_1_GPIO;
  config.hw.port = LEDS_LED_1_PORT;
  config.hw.pin = LEDS_LED_1_PIN;
  led1 = McuLED_InitLed(&config);
  if (led1==NULL) {
    for(;;) {}
  }

  config.isOnInit = false;
  config.isLowActive = true;
  config.hw.gpio = LEDS_LED_2_GPIO;
  config.hw.port = LEDS_LED_2_PORT;
  config.hw.pin = LEDS_LED_2_PIN;
  led2 = McuLED_InitLed(&config);
  if (led2==NULL) {
    for(;;) {}
  }

  config.isOnInit = false;
  config.isLowActive = true;
  config.hw.gpio = LEDS_LED_3_GPIO;
  config.hw.port = LEDS_LED_3_PORT;
  config.hw.pin = LEDS_LED_3_PIN;
  led3 = McuLED_InitLed(&config);
  if (led3==NULL) {
    for(;;) {}
  }
}

void LED_Deinit(void) {
  led1 = McuLED_DeinitLed(led1);
  led2 = McuLED_DeinitLed(led2);
  led3 = McuLED_DeinitLed(led3);
}
