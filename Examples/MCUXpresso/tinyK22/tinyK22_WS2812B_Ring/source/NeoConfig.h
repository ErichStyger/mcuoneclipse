/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOCONFIG_H_
#define NEOCONFIG_H_

#define NEOC_NOF_LANES         (1) /* number of data lanes. For a matrix it is assumed that the number of pixels are divided to the available lanes! */
#define NEOC_NOF_LEDS_IN_LANE  (2*40) /* number of LEDs in each lane */

#define NEOC_NOF_PIXEL   ((NEOC_NOF_LANES)*(NEOC_NOF_LEDS_IN_LANE)) /* number of pixels */

#endif /* NEOCONFIG_H_ */
