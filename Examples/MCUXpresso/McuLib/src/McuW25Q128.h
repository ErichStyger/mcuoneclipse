/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_W25Q128_H_
#define MCU_W25Q128_H_

#include "McuW25Q128config.h"
#include <stdint.h>
#include <stddef.h>
#include "McuShell.h"

/* supported devices */
typedef enum {
  McuW25_DEVICE_UNKNOWN,
  McuW25_DEVICE_W25Q128JV_IQ_JQ,
  McuW25_DEVICE_W25Q128JV_IM_JM,
} McuW25_Device_e;

McuW25_Device_e McuW25_GetDeviceType(void);

uint8_t McuW25_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

#define McuW25_SERIAL_BUF_SIZE  (8)
uint8_t McuW25_ReadSerialNumber(uint8_t *buf, size_t bufSize);

#define McuW25_ID_BUF_SIZE  (3)
uint8_t McuW25_ReadID(uint8_t *buf, size_t bufSize);

uint8_t McuW25_ReadStatus1(uint8_t *status);

bool McuW25_isBusy(void);

void McuW25_WaitIfBusy(void);

uint8_t McuW25_Read(uint32_t address, uint8_t *buf, size_t bufSize);

uint8_t McuW25_EraseAll(void);

uint8_t McuW25_EraseSector4K(uint32_t address);

uint8_t McuW25_EraseBlock32K(uint32_t address);

uint8_t McuW25_EraseBlock64K(uint32_t address);

/*!
 * Program a page with data
 * \param address, should be aligned on page (256 bytes) if programming 256 bytes
 * \param data pointer to data
 * \param dataSize size of data in bytes, max 256
 * \return error code, ERR_OK for no error
 */
uint8_t McuW25_ProgramPage(uint32_t address, const uint8_t *data, size_t dataSize);

uint8_t McuW25_GetCapacity(uint32_t *capacity);

/*!* \brief Module de-initialization */
void McuW25_Deinit(void);

/*!* \brief Module initialization */
void McuW25_Init(void);

#endif /* MCU_W25Q128_H_ */
