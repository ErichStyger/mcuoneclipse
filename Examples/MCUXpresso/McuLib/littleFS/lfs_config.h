/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LITTLEFS_LFSCONFIG_H_
#define LITTLEFS_LFSCONFIG_H_

#ifndef LITTLEFS_CONFIG_ENABLED
  #define LITTLEFS_CONFIG_ENABLED    (0)
    /*!< 1: if LittleFS module is enabled; 0: no littleFS support */
#endif

#ifndef LITTLEFS_CONFIG_THREAD_SAFE
  #define LITTLEFS_CONFIG_THREAD_SAFE  (1)
    /*!< 1: make littleFS thread safe; 0: littleFS is not thread safe */
#endif

#if LITTLEFS_CONFIG_THREAD_SAFE
  #define LFS_THREADSAFE
    /* define macro to tell FS to be thread safe */
#endif

#endif /* LITTLEFS_LFSCONFIG_H_ */
