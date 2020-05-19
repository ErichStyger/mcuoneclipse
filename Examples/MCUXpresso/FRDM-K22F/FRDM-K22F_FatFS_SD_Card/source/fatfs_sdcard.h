/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FATFS_SDCARD_H_
#define FATFS_SDCARD_H_

#include <stdint.h>
#include <stdbool.h>

bool FatFS_SdCardIsDiskPresent(uint8_t drv);

bool FatFS_SdCardIsWriteProtected(uint8_t drv);

void FatFS_SdCardInit(void);

#endif /* FATFS_SDCARD_H_ */
