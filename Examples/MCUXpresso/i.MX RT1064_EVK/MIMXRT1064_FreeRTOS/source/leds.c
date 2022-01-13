/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "leds.h"
#include "McuLED.h"
#include "pin_mux.h"

McuLED_Handle_t LEDS_Led;

void LEDS_Deinit(void) {
  LEDS_Led = McuLED_DeinitLed(LEDS_Led);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;
  config.hw.gpio = GPIO1;
  config.hw.pin = 9;
  McuGPIO_SetMux(&config.hw, IOMUXC_GPIO_AD_B0_09_GPIO1_IO09); /* set special i.MX RT muxing fields */
  LEDS_Led = McuLED_InitLed(&config);
}
