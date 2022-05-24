/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef LITTLEFS_MCULITTLEFSBLOCKDEVICECONFIG_H_
#define LITTLEFS_MCULITTLEFSBLOCKDEVICECONFIG_H_

#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_GENERIC          0
#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128  1

#ifndef McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE
  #define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE     McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_GENERIC
#endif


#endif /* LITTLEFS_MCULITTLEFSBLOCKDEVICECONFIG_H_ */
