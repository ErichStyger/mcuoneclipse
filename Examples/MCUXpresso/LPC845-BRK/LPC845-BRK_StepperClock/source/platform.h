/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_KBI     (0)
#define PL_CONFIG_USE_GUI     (0)
#define PL_CONFIG_USE_SHELL   (1)
#define PL_CONFIG_USE_I2C     (0)
#define PL_CONFIG_USE_USB_CDC (0)


#define PL_HAS_LINE_SENSOR    (1)


void PL_Init(void);

#endif /* PLATFORM_H_ */
