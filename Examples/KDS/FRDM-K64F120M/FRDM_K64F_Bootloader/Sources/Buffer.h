/*
 * Buffer.h
 *
 *  Created on: 16.06.2016
 *      Author: Erich Styger
 */

#ifndef SOURCES_BUFFER_H_
#define SOURCES_BUFFER_H_

#include <stdint.h>

uint8_t BUF_Flush(void);

uint8_t BUF_Write(uint32_t address, uint8_t *data, uint32_t dataSize);

void BUF_Init(void);


#endif /* SOURCES_BUFFER_H_ */
