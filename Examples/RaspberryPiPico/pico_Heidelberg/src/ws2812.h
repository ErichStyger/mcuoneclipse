/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef WS2812_H_
#define WS2812_H_

int WS2812_Transfer(uint8_t *data, size_t dataSize);

void WS2812_Init(void);

#endif /* WS2812_H_ */
