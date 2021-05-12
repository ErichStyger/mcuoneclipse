/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FATFS_SDCARD_H_
#define FATFS_SDCARD_H_

#include <stdint.h>
#include <stdbool.h>

bool McuFatFS_IsDiskPresent(uint8_t drv);

bool McuFatFS_IsWriteProtected(uint8_t drv);

void FatFS_SdCardInit(void);

#endif /* FATFS_SDCARD_H_ */
