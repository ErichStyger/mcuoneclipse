/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_WS2812B  (1) /* if support for WS2812B LEDs is enabled */
#define PL_CONFIG_USE_MININI   (0) /* if support for storing data in FLASH with MinIni is enabled */
#define PL_CONFIG_USE_RTT      (0) /* if using SEGGER RTT */

void PL_Init(void);

#endif /* PLATFORM_H_ */
