/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef WS2812B_H_
#define WS2812B_H_

#include <stdint.h>
#include <stddef.h>

void WS2812B_SendPixels(uint8_t *data, size_t cnt);

void WS2812B_Init(void);

#endif /* WS2812B_H_ */
