/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef MCULITTLEFSMEMORY_H_
#define MCULITTLEFSMEMORY_H_

#include <stdint.h>
#include "littleFS/lfs.h"

uint8_t McuLFSMem_Read(uint32_t address, uint8_t *buf, size_t bufSize);

/*!
 * Program a page with data
 * \param address, should be aligned on page (256 bytes) if programming 256 bytes
 * \param data pointer to data
 * \param dataSize size of data in bytes, max 256
 * \return error code, ERR_OK for no error
 */
uint8_t McuLFSMem_Program(uint32_t address, const uint8_t *data, size_t dataSize);

uint8_t McuLFSMem_EraseBlock(lfs_block_t block);

uint8_t McuLFSMem_Deinit(void);

uint8_t McuLFSMem_Init(void);

#endif /* MCULITTLEFSMEMORY_H_ */
