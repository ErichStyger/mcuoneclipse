/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

/* Red: P1_6 */
#define LEDS_LED_RED_GPIO       GPIO
#define LEDS_LED_RED_PORT       1
#define LEDS_LED_RED_PIN        6
//#define LEDS_LED_RED_IOCON      IOCON_INDEX_PIO1_6

/* Green: P1_7 */
#define LEDS_LED_GREEN_GPIO     GPIO
#define LEDS_LED_GREEN_PORT     1
#define LEDS_LED_GREEN_PIN      7
//#define LEDS_LED_GREEN_IOCON    IOCON_INDEX_PIO1_7

/* Blue: P1_4 */
#define LEDS_LED_BLUE_GPIO      GPIO
#define LEDS_LED_BLUE_PORT      1
#define LEDS_LED_BLUE_PIN       4
//#define LEDS_LED_BLUE_IOCON     IOCON_INDEX_PIO1_4

#endif /* LEDS_CONFIG_H_ */
