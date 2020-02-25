/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOURCES_PIXELDMA_H_
#define SOURCES_PIXELDMA_H_

#include <stdint.h>

uint8_t PIXDMA_Transfer(uint32_t dataAddress, size_t nofBytes);

void PIXDMA_Init(void);

#endif /* SOURCES_PIXELDMA_H_ */
