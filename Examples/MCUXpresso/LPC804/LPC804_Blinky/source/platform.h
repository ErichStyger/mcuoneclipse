/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_WS2812B  (1)
#define PL_CONFIG_USE_PLU      (1)
#define PL_PLU_FAST            (0 && PL_CONFIG_USE_PLU)
#define PL_NO_PLU_SPI_ONLY     (1 && !PL_CONFIG_USE_PLU)

void PL_Init(void);

#endif /* PLATFORM_H_ */
