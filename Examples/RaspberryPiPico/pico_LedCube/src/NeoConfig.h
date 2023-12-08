/*
 * Copyright (c) 2001-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOCONFIG_H_
#define NEOCONFIG_H_

#include "app_platform.h"

#if PL_CONFIG_USE_NEO_PIXEL_HW

#define NEOC_NOF_COLORS        (3)  /* number of colors: 3 for RGB, 4 for RGBW */

#define NEOC_PIN_START         (21) /* start of physical GPIO pin number: GPIO2 */
#define NEOC_NOF_LANES         (8) /* number of lanes (and pins) to be used */

#define NEOC_LANE_START        (0)  /* start bit number in lane (logical) data: for Kinetis DMA, this has to match physical NEOC_PIN_START! */
#define NEOC_LANE_END          (NEOC_LANE_START+NEOC_NOF_LANES-1)  /* this is the last GPIO pin used: GPIOx */

#define NEOC_EXTENDED_LANE      (1) /* if lane is extended. Needed for 8 NEOC_NOF_LANES building a 16x16 cube  */

#if NEOC_EXTENDED_LANE
  #define NEOC_NOF_LEDS_IN_LANE   (2*16*16*2) /* number of LEDs in each lane, 16 rods with 16x2 LEDs. 8 Lanes to build a 16x16x16 cube */
#else
  #define NEOC_NOF_LEDS_IN_LANE   (16*16*2) /* number of LEDs in each lane, 16 rods with 16x2 LEDs */
#endif

#ifndef NEOC_NOF_COLORS
  #define NEOC_NOF_COLORS (3)  /* default number of colors: 3 for RGB, 4 for RGBW */
#endif

#if (NEOC_NOF_LANES>8)
  #error "can only handle up to 8 lanes (8bit port)"
#endif

#define NEOC_NOF_PIXEL            ((NEOC_NOF_LANES)*(NEOC_NOF_LEDS_IN_LANE)) /* total number of pixels in the system */

#define NEOC_USE_DMA              (1) /* if using DMA. Otherwise the bits are sent in a loop */

#define NEOC_PIO_32BIT_PIXELS     (1) /* pixels are organized as 32bit values, optimized for the RP2040 PIO, supporting 1 and up to 8 lanes */

#endif /* PL_CONFIG_USE_NEO_PIXEL_HW */

#endif /* NEOCONFIG_H_ */
