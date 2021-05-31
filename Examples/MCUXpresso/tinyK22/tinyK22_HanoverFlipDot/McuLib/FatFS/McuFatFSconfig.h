/**
 * \file
 * \brief Configuration header file for FAT_FileSystem
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the FAT File System module.
 */

#ifndef __McuFatFS_CONFIG_H
#define __McuFatFS_CONFIG_H

#ifndef McuFatFS_CONFIG_CARD_INSERT_DELAY_TIME_MS
  #define McuFatFS_CONFIG_CARD_INSERT_DELAY_TIME_MS    (100)
    /*!< Delay time in milliseconds after insertion of the card detected */
#endif

#ifndef McuFatFS_CONFIG_SHELL_ENABLED
  #define McuFatFS_CONFIG_SHELL_ENABLED    (1)
    /*!< 1: Shell support is enabled; 0: no shell support enabled */
#endif

#ifndef McuFatFS_CONFIG_IS_DISK_PRESENT_CALLBACK
  #define McuFatFS_CONFIG_IS_DISK_PRESENT_CALLBACK    McuFatFS_CardPinDiskPresent
    /*!< 1: callback name to be used to decide if a device is present or not */
#endif

#ifndef McuFatFS_CONFIG_IS_WRITE_PROTECTED_CALLBACK
  #define McuFatFS_CONFIG_IS_WRITE_PROTECTED_CALLBACK    McuFatFS_CardPinWriteProtected
    /*!< 1: callback name to be used to decide if a device is present or not */
#endif

#ifndef McuFatFS_CONFIG_DEFAULT_DRIVE_STRING
  #define McuFatFS_CONFIG_DEFAULT_DRIVE_STRING    "0:/"
    /*!< default drive used for commands. The first letter defines the drive */
#endif

#endif /* __McuFatFS_CONFIG_H */

