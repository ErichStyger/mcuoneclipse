/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

#define LEDS_CONFIG_HAS_RED_LED            (0) /* 1: has red LED */
#define LEDS_CONFIG_HAS_GREEN_LED          (0) /* 1: has green LED */
#define LEDS_CONFIG_HAS_BLUE_LED           (0) /* 1: has blue LED */
#define LEDS_CONFIG_HAS_ORANGE_LED         (0) /* 1: has orange LED */
#define LEDS_CONFIG_HAS_GREEN_PICO_LED     (1) /* 1: has green onboard LED */
#define LEDS_CONFIG_HAS_BLUE_TINY_LED      (0) /* 1: has blue onboard LED */

#define LEDS_CONFIG_ENABLE_CLOCK()     /* nothing */

#if LEDS_CONFIG_HAS_RED_LED
  #define LEDS_CONFIG_RED_PIN           20u
  #define LEDS_CONFIG_RED_LOW_ACTIVE    false
#endif

#if LEDS_CONFIG_HAS_GREEN_LED
  #define LEDS_CONFIG_GREEN_PIN         19u
  #define LEDS_CONFIG_GREEN_LOW_ACTIVE  false
#endif

#if LEDS_CONFIG_HAS_BLUE_LED
  #define LEDS_CONFIG_BLUE_PIN          18u
  #define LEDS_CONFIG_BLUE_LOW_ACTIVE   false
#endif

#if LEDS_CONFIG_HAS_GREEN_PICO_LED
  #define LEDS_CONFIG_PICO_GREEN_PIN          25u
  #define LEDS_CONFIG_PICO_GREEN_LOW_ACTIVE   false
#endif

#endif /* LEDS_CONFIG_H_ */
