/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCULITTLEFS_CONFIG_H_
#define MCULITTLEFS_CONFIG_H_

#ifndef McuLittleFS_CONFIG_BLOCK_SIZE
  #define McuLittleFS_CONFIG_BLOCK_SIZE    (4096)
    /*!< standard block size. Needs to match flash device block size*/
#endif

#ifndef McuLittleFS_CONFIG_BLOCK_COUNT
  #define McuLittleFS_CONFIG_BLOCK_COUNT    (16384) /* 16384 * 4K = 64 MByte */
    /*!< number of blocks used for the file system */
#endif

#ifndef McuLittleFS_CONFIG_BLOCK_OFFSET
  #define McuLittleFS_CONFIG_BLOCK_OFFSET    (0)
    /*!< block offset number for the block device */
#endif

#ifndef McuLittleFS_CONFIG_FILE_NAME_SIZE
  #define McuLittleFS_CONFIG_FILE_NAME_SIZE     (60)
    /*!< Length of file name, used in buffers */
#endif

#ifndef McuLittleFS_CONFIG_FILESYSTEM_READ_BUFFER_SIZE
  #define McuLittleFS_CONFIG_FILESYSTEM_READ_BUFFER_SIZE    (256)
#endif

#ifndef McuLittleFS_CONFIG_FILESYSTEM_PROG_BUFFER_SIZE
  #define McuLittleFS_CONFIG_FILESYSTEM_PROG_BUFFER_SIZE    (256)
#endif

#ifndef McuLittleFS_CONFIG_FILESYSTEM_LOOKAHEAD_SIZE
  #define McuLittleFS_CONFIG_FILESYSTEM_LOOKAHEAD_SIZE      (256)
#endif

#ifndef McuLittleFS_CONFIG_FILESYSTEM_CACHE_SIZE
  #define McuLittleFS_CONFIG_FILESYSTEM_CACHE_SIZE          (256)
#endif

#endif /* MCULITTLEFS_CONFIG_H_ */
