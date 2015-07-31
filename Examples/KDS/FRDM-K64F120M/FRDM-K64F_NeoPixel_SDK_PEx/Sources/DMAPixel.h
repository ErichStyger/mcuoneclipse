/*
 * DMAPixel.h
 *
 *  Created on: 31.07.2015
 *      Author: tastyger
 */

#ifndef SOURCES_DMAPIXEL_H_
#define SOURCES_DMAPIXEL_H_

#include <stdint.h>

void DMA_Transfer(uint8_t *transmitBuf, uint32_t nofBytes);

void DMA_Init(void);

#endif /* SOURCES_DMAPIXEL_H_ */
