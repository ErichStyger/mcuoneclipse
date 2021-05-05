/**
 * \file
 * \brief Configuration header file for MinINI
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the MinINI module.
 */
#ifndef __McuMinINI_CONFIG_H
#define __McuMinINI_CONFIG_H

#define McuMinINI_CONFIG_FS_TYPE_GENERIC  (0) /* Generic File System */
#define McuMinINI_CONFIG_FS_TYPE_FAT_FS   (1) /* FatFS File System */
#define McuMinINI_CONFIG_FS_TYPE_TINY_FS  (2) /* TinyFS File System */

#ifndef McuMinINI_CONFIG_FS
  #define McuMinINI_CONFIG_FS      (McuMinINI_CONFIG_FS_TYPE_GENERIC)
    /*!< File System integration used, one of McuMinINI_CONFIG_FS_TYPE_GENERIC, McuMinINI_CONFIG_FS_TYPE_FAT_FS, McuMinINI_CONFIG_FS_TYPE_TINY_FS */
#endif

#define PORTABLE_STRNICMP

//#define INI_REAL double

//#define INI_READONLY

#ifndef NDEBUG
  #define NDEBUG
#endif

#define INI_USE_GLOBAL_BUFFER   0 /* 0: use stack for buffer; 1: use global memory for buffer */

#if !defined(McuMinINI_CONFIG_PARSE_COMMAND_ENABLED)
  #define McuMinINI_CONFIG_PARSE_COMMAND_ENABLED  (1)
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#endif /* __McuMinINI_CONFIG_H */
