/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef WS2812_H_
#define WS2812_H_

#include <stdint.h>

int WS2812_Transfer(uint32_t address, size_t nofBytes);

void WS2812_Init(void);

#endif /* WS2812_H_ */
