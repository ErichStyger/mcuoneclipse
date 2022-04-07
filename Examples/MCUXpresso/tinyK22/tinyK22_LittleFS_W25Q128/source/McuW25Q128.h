/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_W25Q128_H_
#define MCU_W25Q128_H_

#include "McuW28Q128config.h"
#include <stdint.h>
#include <stddef.h>
#include "McuShell.h"

uint8_t W25_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

#define W25_SERIAL_BUF_SIZE  (8)
uint8_t W25_ReadSerialNumber(uint8_t *buf, size_t bufSize);

#define W25_ID_BUF_SIZE  (3)
uint8_t W25_ReadID(uint8_t *buf, size_t bufSize);

uint8_t W25_ReadStatus1(uint8_t *status);

bool W25_isBusy(void);

void W25_WaitIfBusy(void);

uint8_t W25_Read(uint32_t address, uint8_t *buf, size_t bufSize);

uint8_t W25_EraseAll(void);

uint8_t W25_EraseSector4K(uint32_t address);

uint8_t W25_EraseBlock32K(uint32_t address);

uint8_t W25_EraseBlock64K(uint32_t address);

/*!
 * Program a page with data
 * \param address, should be aligned on page (256 bytes) if programming 256 bytes
 * \param data pointer to data
 * \param dataSize size of data in bytes, max 256
 * \return error code, ERR_OK for no error
 */
uint8_t W25_ProgramPage(uint32_t address, const uint8_t *data, size_t dataSize);

uint8_t W25_GetCapacity(const uint8_t *id, uint32_t *capacity);

uint8_t W25_Init(void);

//uint16_t W25_SpiInOut( Spi_t *obj, uint16_t outData );

#endif /* MCU_W25Q128_H_ */
