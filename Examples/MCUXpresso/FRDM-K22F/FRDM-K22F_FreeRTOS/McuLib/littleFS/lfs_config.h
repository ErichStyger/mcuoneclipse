/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LITTLEFS_LFSCONFIG_H_
#define LITTLEFS_LFSCONFIG_H_

#include "McuLibconfig.h" /* to know if RTOS is used */
#include "McuRTOS.h" /* for RTOS malloc()/free() */

#ifndef LITTLEFS_CONFIG_ENABLED
  #define LITTLEFS_CONFIG_ENABLED    (0)
    /*!< 1: if LittleFS module is enabled; 0: no littleFS support */
#endif

#ifndef LITTLEFS_CONFIG_THREAD_SAFE
  #define LITTLEFS_CONFIG_THREAD_SAFE  (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: make littleFS thread safe; 0: littleFS is not thread safe */
#endif

#if LITTLEFS_CONFIG_THREAD_SAFE
  #define LFS_THREADSAFE
    /* define macro to tell FS to be thread safe */
#endif

#ifndef LITTLEFS_CONFIG_USE_FREERTOS_HEAP
  #define LITTLEFS_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#endif /* LITTLEFS_LFSCONFIG_H_ */
