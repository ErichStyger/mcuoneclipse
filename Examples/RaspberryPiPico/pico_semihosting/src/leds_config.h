/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

#include "platform.h"

#if    (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V0_1) \
    || (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V0_2) \
    || (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V1_0)
  #define LEDS_CONFIG_HAS_ONBOARD_LED        (0)
  #define LEDS_CONFIG_HAS_RED_LED            (1)
  #define LEDS_CONFIG_HAS_GREEN_LED          (1)
  #define LEDS_CONFIG_HAS_BLUE_LED           (1)
  #define LEDS_CONFIG_HAS_ORANGE_LED         (0)
#elif PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP_ROBO_SHIELD
  #define LEDS_CONFIG_HAS_ONBOARD_LED        (0)
  #define LEDS_CONFIG_HAS_RED_LED            (1)
  #define LEDS_CONFIG_HAS_GREEN_LED          (0)
  #define LEDS_CONFIG_HAS_BLUE_LED           (0)
  #define LEDS_CONFIG_HAS_ORANGE_LED         (0)
#elif (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_1) || (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_2)
  #define LEDS_CONFIG_HAS_ONBOARD_LED        (1)
  #define LEDS_CONFIG_HAS_RED_LED            (1)
  #define LEDS_CONFIG_HAS_GREEN_LED          (1)
  #define LEDS_CONFIG_HAS_BLUE_LED           (1)
  #define LEDS_CONFIG_HAS_ORANGE_LED         (0)
#endif

#if    (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V0_1) \
    || (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V0_2) \
    || (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP32_CONSOLE_V1_0)
  #define LEDS_CONFIG_ENABLE_CLOCK()    /* nothing */

  #if LEDS_CONFIG_HAS_RED_LED
    /* red led on IO27, HIGH active */
    #define LEDS_CONFIG_RED_PIN           (GPIO_NUM_27)
    #define LEDS_CONFIG_RED_LOW_ACTIVE    (0)
  #endif

  #if LEDS_CONFIG_HAS_GREEN_LED
    /* green led on IO26, HIGH active */
    #define LEDS_CONFIG_GREEN_PIN         (GPIO_NUM_26)
    #define LEDS_CONFIG_GREEN_LOW_ACTIVE  (0)
  #endif

  #if LEDS_CONFIG_HAS_BLUE_LED
    /* blue led on IO16, HIGH active */
    #define LEDS_CONFIG_BLUE_PIN          (GPIO_NUM_16)
    #define LEDS_CONFIG_BLUE_LOW_ACTIVE   (0)
  #endif
#elif PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_ESP_ROBO_SHIELD
  #define LEDS_CONFIG_ENABLE_CLOCK()    /* nothing */

  #if LEDS_CONFIG_HAS_RED_LED
    /* red led on the shield is on IO10, LOW active */
    #define LEDS_CONFIG_RED_PIN          (GPIO_NUM_10) /* IO10 */
    #define LEDS_CONFIG_RED_LOW_ACTIVE    (1)
  #endif
#elif (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_1) || (PL_CONFIG_HW_VERSION==PL_CONFIG_HW_ADIS_PICO_W_CONSOLE_V0_2)
  /* Green: GPIO18
   * Blue:  GPIO19
   * Red:   GPIO20 */
  #define LEDS_CONFIG_ENABLE_CLOCK()    /* nothing */

  #if LEDS_CONFIG_HAS_RED_LED
    #define LEDS_CONFIG_RED_PIN           20
    #define LEDS_CONFIG_RED_LOW_ACTIVE    false
  #endif

  #if LEDS_CONFIG_HAS_GREEN_LED
    #define LEDS_CONFIG_GREEN_PIN         19
    #define LEDS_CONFIG_GREEN_LOW_ACTIVE  false
  #endif

  #if LEDS_CONFIG_HAS_BLUE_LED
    #define LEDS_CONFIG_BLUE_PIN          18
    #define LEDS_CONFIG_BLUE_LOW_ACTIVE   false
  #endif

  #if LEDS_CONFIG_HAS_ONBOARD_LED
    #if !PL_CONFIG_USE_PICO_W
      #define LEDS_CONFIG_ONBOARD_PIN          25 /* only for non-W! */
      #define LEDS_CONFIG_ONBOARD_LOW_ACTIVE   false
    #endif
  #endif
#endif

#endif /* LEDS_CONFIG_H_ */
