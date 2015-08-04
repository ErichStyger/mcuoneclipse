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

/*! \brief Initialize the timer and DMA */
void DMA_Init(void);

#endif /* SOURCES_DMAPIXEL_H_ */
