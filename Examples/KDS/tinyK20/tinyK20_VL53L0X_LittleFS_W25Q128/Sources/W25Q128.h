/*
 * W25Q128.h
 *
 *  Created on: 05.01.2019
 *      Author: Erich Styger
 */

#ifndef SOURCES_W25Q128_H_
#define SOURCES_W25Q128_H_

#include <stdint.h>
#include <stddef.h>

#include "CLS1.h"

uint8_t W25_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);

#define W25_SERIAL_BUF_SIZE  (8)
uint8_t W25_ReadSerialNumber(uint8_t *buf, size_t bufSize);

#define W25_ID_BUF_SIZE  (3)
uint8_t W25_ReadID(uint8_t *buf, size_t bufSize);

uint8_t W25_Init(void);


#endif /* SOURCES_W25Q128_H_ */
