/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FATFS_SDCARD_H_
#define FATFS_SDCARD_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool McuFatFS_CardPinDiskPresent(uint8_t *drvStr);

bool McuFatFS_CardPinWriteProtected(uint8_t *drvStr);

void McuFatFS_CardPinInit(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* FATFS_SDCARD_H_ */
