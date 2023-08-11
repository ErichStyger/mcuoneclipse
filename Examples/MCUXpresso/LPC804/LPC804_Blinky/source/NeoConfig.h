/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOCONFIG_H_
#define NEOCONFIG_H_

#define NEOC_NOF_LEDS          (16) /* number of LEDs  */
#define NEOC_NOF_COLORS        (4)  /* 3 for RGB, 4 for RGBW */

#if (NEOC_NOF_LANES>8)
  #error "can only handle up to 8 lanes (8bit port)"
#endif

#define NEOC_NOF_PIXEL   (NEOC_NOF_LEDS) /* number of pixels */


#endif /* NEOCONFIG_H_ */
