/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef WS2812_H_
#define WS2812_H_

#include <stdint.h>

/*!
 * \brief Wait until the buffer for the pixel data is available and ready for writing.
 */
void WS2812_WaitForBufferReady(void);

/*!
 * \brief Decides if a DMA transfer is still going on.
 * \return true if a DMA transfer is going on, false otherwise.
 */
bool WS2812_DMATransferIsOngoing(void);

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
