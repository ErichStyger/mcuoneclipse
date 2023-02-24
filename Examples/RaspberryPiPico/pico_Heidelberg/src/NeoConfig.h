/*
 * Copyright (c) 2001-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOCONFIG_H_
#define NEOCONFIG_H_

#include "app_platform.h"

#if PL_CONFIG_USE_NEO_PIXEL_HW

#define NEOC_LANE_START        (2)  /* this is the first GPIO pin used: GPIO2 */
#define NEOC_LANE_END          (2)  /* this is the last GPIO pin used: GPIO2 */
#define NEOC_NOF_COLORS        (4)  /* 3 for RGB, 4 for RGBW */

#if PL_CONFIG_IS_APP_NAME_PLATE
  #define NEOC_NOF_LEDS_IN_LANE   (2)
#elif PL_CONFIG_IS_APP_LED_COUNTER /* full LED counter app */
  #define NEOC_NOF_LEDS_IN_LANE   (2+16+8) /* number of LEDs in a lane for counter app */
#else
  #define NEOC_NOF_LEDS_IN_LANE   (4) /* number of LEDs in a lane */
#endif

#ifndef NEOC_NOF_COLORS
  #define NEOC_NOF_COLORS (3)  /* 3 for RGB, 4 for RGBW */
#endif

#if (NEOC_NOF_LANES>8)
  #error "can only handle up to 8 lanes (8bit port)"
#endif

#define NEOC_NOF_PIXEL   ((NEOC_LANE_END+1-NEOC_LANE_START)*(NEOC_NOF_LEDS_IN_LANE)) /* number of pixels */

#define NEOC_USE_DMA     (0) /* if using DMA. Not supported for RP2040 as using PLU */

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */

#endif /* NEOCONFIG_H_ */
