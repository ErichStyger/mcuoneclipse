/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUA3967CONFIG_H_
#define MCUA3967CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MCUA3967_CONFIG_USE_FREERTOS_HEAP
  #define MCUA3967_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUA3967CONFIG_H_ */
