/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef WS2812_H_
#define WS2812_H_

#include <stdint.h>

/*!
 * \brief Transfer the LED data buffer to the hardware
 * \param address Address of data
 * \param nofBytes Number of byes
 * \return 0 for success, non-zero otherwise
 */
int WS2812_Transfer(uint32_t address, size_t nofBytes);

/*!
 * \brief Module initialization
 */
void WS2812_Init(void);

#endif /* WS2812_H_ */
