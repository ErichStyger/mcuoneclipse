/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCULITTLEFS_CONFIG_H_
#define MCULITTLEFS_CONFIG_H_

#ifndef MCULITTLEFS_CONFIG_BLOCK_SIZE
  #define MCULITTLEFS_CONFIG_BLOCK_SIZE    (4096)
    /*!< standard block size. Needs to match flash device block size*/
#endif

#ifndef MCULITTLEFS_CONFIG_BLOCK_COUNT
  #define MCULITTLEFS_CONFIG_BLOCK_COUNT    (16384) /* 16384 * 4K = 64 MByte */
    /*!< number of blocks used for the file system */
#endif

#endif /* MCULITTLEFS_CONFIG_H_ */
