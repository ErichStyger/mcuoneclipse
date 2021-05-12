/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "leds.h"
#include "McuLED.h"

#if PL_BOARD_IS_TINYK22 /* tinyK22 */
  #define PINS_LEDBLUE_GPIO       GPIOC
  #define PINS_LEDBLUE_PORT       PORTC
  #define PINS_LEDBLUE_PIN        2U
#else /* FRDM-K22F */
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

#if PL_BOARD_IS_TINYK22
  McuLED_Handle_t blueLED;
#else
  McuLED_Handle_t redLED, blueLED, greenLED;
#endif

void LEDS_Deinit(void) {
#if PL_BOARD_IS_TINYK22
  blueLED = McuLED_DeinitLed(blueLED);
#else
  redLED = McuLED_DeinitLed(redLED);
  greenLED = McuLED_DeinitLed(greenLED);
  blueLED = McuLED_DeinitLed(blueLED);
#endif
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);

#if PL_BOARD_IS_TINYK22
  CLOCK_EnableClock(kCLOCK_PortC); /* tinyK22 has LED on port D */
  config.isLowActive = true;
  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  blueLED = McuLED_InitLed(&config);
#else
  CLOCK_EnableClock(kCLOCK_PortA); /* FRDM-K22 has LED on port A */
  CLOCK_EnableClock(kCLOCK_PortD); /* FRDM-K22 has LED on port D */
  config.isLowActive = true;
  config.hw.pin = PINS_LEDRED_PIN;
  config.hw.port = PINS_LEDRED_PORT;
  config.hw.gpio = PINS_LEDRED_GPIO;
  redLED = McuLED_InitLed(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDGREEN_PIN;
  config.hw.port = PINS_LEDGREEN_PORT;
  config.hw.gpio = PINS_LEDGREEN_GPIO;
  greenLED = McuLED_InitLed(&config);

  config.isLowActive = true;
  config.hw.pin = PINS_LEDBLUE_PIN;
  config.hw.port = PINS_LEDBLUE_PORT;
  config.hw.gpio = PINS_LEDBLUE_GPIO;
  blueLED = McuLED_InitLed(&config);
#endif
}
