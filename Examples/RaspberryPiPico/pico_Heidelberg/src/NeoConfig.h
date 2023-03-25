/*
 * Copyright (c) 2001-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOCONFIG_H_
#define NEOCONFIG_H_

#include "app_platform.h"

#if PL_CONFIG_USE_NEO_PIXEL_HW

#define NEOC_NOF_COLORS        (4)  /* number of colors: 3 for RGB, 4 for RGBW */

#define NEOC_PIN_START         (2) /* start of physical GPIO pin number: GPIO2 */
#define NEOC_NOF_LANES         (1) /* number of lanes (and pins) to be used */

#define NEOC_LANE_START        (0)  /* start bit number in lane (logical) data: for Kinetis DMA, this has to match physical NEOC_PIN_START! */
#define NEOC_LANE_END          (NEOC_LANE_START+NEOC_NOF_LANES)  /* this is the last GPIO pin used: GPIOx */

#if PL_CONFIG_IS_APP_NAME_PLATE
  #define NEOC_NOF_LEDS_IN_LANE   (2)
#elif PL_CONFIG_IS_APP_LED_COUNTER /* full LED counter app */
  #define NEOC_NOF_LEDS_IN_LANE   (2+16+8) /* number of LEDs in a lane for counter app */
#else
  #define NEOC_NOF_LEDS_IN_LANE   (1) /* number of LEDs in a lane */
#endif

#ifndef NEOC_NOF_COLORS
  #define NEOC_NOF_COLORS (3)  /* default number of colors: 3 for RGB, 4 for RGBW */
#endif

#if (NEOC_NOF_LANES>8)
  #error "can only handle up to 8 lanes (8bit port)"
#endif

#define NEOC_NOF_PIXEL   ((NEOC_NOF_LANES)*(NEOC_NOF_LEDS_IN_LANE)) /* number of pixels */

#define NEOC_USE_DMA     (0) /* if using DMA. Not supported for RP2040 as using PLU */

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */

#endif /* NEOCONFIG_H_ */
