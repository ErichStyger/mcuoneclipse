/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * Configuration header file for McuGPIO
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUGPIO_CONFIG_H_
#define MCUGPIO_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuLibconfig.h"

#ifndef MCUGPIO_CONFIG_USE_FREERTOS_HEAP
  #define MCUGPIO_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUGPIOCONFIG_H_ */
