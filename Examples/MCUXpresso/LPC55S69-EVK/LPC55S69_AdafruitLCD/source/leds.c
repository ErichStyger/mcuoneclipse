/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "leds.h"
#include "McuLED.h"
#include "board.h" /* defines the BOARD_LED_ macros */

/* Blue: P1_4 */
#ifdef BOARD_LED_BLUE_GPIO
  #define LED_BLUE_GPIO    BOARD_LED_BLUE_GPIO
#else
  #define LED_BLUE_GPIO    GPIO
#endif
#ifdef BOARD_LED_BLUE_GPIO_PORT
  #define LED_BLUE_PORT    BOARD_LED_BLUE_GPIO_PORT
#else
  #define LED_BLUE_PORT    1U
#endif
#ifdef BOARD_LED_BLUE_GPIO_PIN
  #define LED_BLUE_PIN     BOARD_LED_BLUE_GPIO_PIN
#else
  #define LED_BLUE_PIN     4U
#endif

/* Red: P1_6 */
#ifdef BOARD_LED_BLUE_GPIO
  #define LED_RED_GPIO    BOARD_LED_RED_GPIO
#else
  #define LED_RED_GPIO    GPIO
#endif
#ifdef BOARD_LED_RED_GPIO_PORT
  #define LED_RED_PORT    BOARD_LED_RED_GPIO_PORT
#else
  #define LED_RED_PORT    1U
#endif
#ifdef BOARD_LED_RED_GPIO_PIN
  #define LED_RED_PIN     BOARD_LED_RED_GPIO_PIN
#else
  #define LED_RED_PIN    6U
#endif

/* Green: P1_7 */
#ifdef BOARD_LED_GREEN_GPIO
  #define LED_GREEN_GPIO    BOARD_LED_GREEN_GPIO
#else
  #define LED_GREEN_GPIO    GPIO
#endif
#ifdef BOARD_LED_GREEN_GPIO_PORT
  #define LED_GREEN_PORT    BOARD_LED_GREEN_GPIO_PORT
#else
  #define LED_GREEN_PORT    1U
#endif
#ifdef BOARD_LED_GREEN_GPIO_PIN
  #define LED_GREEN_PIN     BOARD_LED_GREEN_GPIO_PIN
#else
  #define LED_GREEN_PIN    7U
#endif

McuLED_Handle_t LED_Red, LED_Blue, LED_Green;

void LEDS_Deinit(void) {
  LED_Red = McuLED_DeinitLed(LED_Red);
  LED_Green = McuLED_DeinitLed(LED_Green);
  LED_Blue = McuLED_DeinitLed(LED_Blue);
}

void LEDS_Init(void) {
  McuLED_Config_t config;

  /* initialize LEDs */
  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;

  config.hw.pin = LED_RED_PIN;
  config.hw.port = LED_RED_PORT;
  config.hw.gpio = LED_RED_GPIO;
  LED_Red = McuLED_InitLed(&config);

  config.hw.pin = LED_GREEN_PIN;
  config.hw.port = LED_GREEN_PORT;
  config.hw.gpio = LED_GREEN_GPIO;
  LED_Green = McuLED_InitLed(&config);

  config.hw.pin = LED_BLUE_PIN;
  config.hw.port = LED_BLUE_PORT;
  config.hw.gpio = LED_BLUE_GPIO;
  LED_Blue = McuLED_InitLed(&config);
}
