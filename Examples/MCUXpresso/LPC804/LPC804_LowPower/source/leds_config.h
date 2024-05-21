/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

   /* Green: PIO0_13
    * Red:   PIO0_12 */
  #define LEDS_ENABLE_CLOCK()     GPIO_PortInit(GPIO, 0) /* ungate the clocks for GPIO0: used for LEDs */

  #define LEDS_LED_RED_GPIO       GPIO
  #define LEDS_LED_RED_PORT       0
  #define LEDS_LED_RED_PIN        12
  #define LEDS_LED_RED_IOCON      IOCON_INDEX_PIO0_12

  #define LEDS_LED_GREEN_GPIO     GPIO
  #define LEDS_LED_GREEN_PORT     0
  #define LEDS_LED_GREEN_PIN      13
  #define LEDS_LED_GREEN_IOCON    IOCON_INDEX_PIO0_13

#endif /* LEDS_CONFIG_H_ */
