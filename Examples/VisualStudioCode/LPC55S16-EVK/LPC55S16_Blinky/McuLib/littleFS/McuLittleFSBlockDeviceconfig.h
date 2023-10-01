/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef LITTLEFS_MCULITTLEFSBLOCKDEVICECONFIG_H_
#define LITTLEFS_MCULITTLEFSBLOCKDEVICECONFIG_H_

/* supported block device types */
#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_GENERIC          0 /* dummy, generic implementation */
#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128  1 /* using WinBond W25Q128 external SPI FLASH */
#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH        2 /* using McuFlash blocks */

#ifndef McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE
  #define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE     McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_GENERIC
    /*<! sets used block device */
#endif

#endif /* LITTLEFS_MCULITTLEFSBLOCKDEVICECONFIG_H_ */
