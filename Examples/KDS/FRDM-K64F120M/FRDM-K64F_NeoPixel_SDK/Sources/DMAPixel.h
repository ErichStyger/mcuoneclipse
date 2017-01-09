/**
 * \file
 * \brief WS2812B Driver using DMA.
 * \author Erich Styger
 *
 * This module deals with the low level timer and eDMA to
 * generate the bitstream for multiple WS2812B lanes.
 * \license
 *  This is a free software and is opened for education,  research and commercial developments under license policy of following terms:
 *  This is a free software and there is NO WARRANTY.
 *  No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
 *  Redistributions of source code must retain the above copyright notice.
 */

#ifndef SOURCES_DMAPIXEL_H_
#define SOURCES_DMAPIXEL_H_

#include <stdint.h>
#include "Color.h"
#define NEO_NOF_PIXEL       16
#define NEO_NOF_BITS_PIXEL 24
static uint8_t transmitBuf[NEO_NOF_PIXEL*NEO_NOF_BITS_PIXEL] ={};

/*!
 * \brief Transmits a buffer of WS2812 pixel data
 * \param transmitBuf Pointer to the buffer
 * \param nofBytes Size of buffer in bytes
 */
void DMA_Transfer(uint8_t *transmitBuf, uint32_t nofBytes);

/*! \brief Initialize the timer and DMA */
void DMA_Init(void);
/* Initialize the Random Number Generator Hardware*/
void RNG_Init(void);
/*!
 * \brief Generates a random number between 0 and limit, including limit
 * \param limit maximum number to generate
 */
uint32_t getRandom(uint8_t limit);

void initBuffer(void);
void randomColors(uint8_t count);
void Twinkle(Color c, uint32_t Count, uint32_t SpeedDelay, uint8_t OnlyOne, uint8_t reset); 
void colorWipe(Color c, uint32_t SpeedDelay);
void FadeInOut(Color c);
void theaterChase(Color c, uint32_t SpeedDelay);
void setAll(Color c);
void setPixel(uint8_t Pixel, Color c);
void delay(uint32_t ms);

#endif /* SOURCES_DMAPIXEL_H_ */
