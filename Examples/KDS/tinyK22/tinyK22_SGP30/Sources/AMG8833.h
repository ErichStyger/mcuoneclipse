/*
 * AMG8833.h
 *
 *  Created on: 09.11.2018
 *      Author: Erich Styger
 */

#ifndef SOURCES_AMG8833_AMG8833_H_
#define SOURCES_AMG8833_AMG8833_H_

#include <stdint.h>

#define AMG88xx_PIXEL_ARRAY_SIZE          64

uint8_t AMG88xx_readPixels(float *buf, uint8_t size);

uint8_t AMG_Init(void);


#endif /* SOURCES_AMG8833_AMG8833_H_ */
