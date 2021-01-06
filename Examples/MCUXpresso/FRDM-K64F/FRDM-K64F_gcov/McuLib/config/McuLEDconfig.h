/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Configuration header file for McuLED
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCULED_CONFIG_H_
#define MCULED_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuLibconfig.h"

#ifndef MCULED_CONFIG_USE_FREERTOS_HEAP
  #define MCULED_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCULEDCONFIG_H_ */
