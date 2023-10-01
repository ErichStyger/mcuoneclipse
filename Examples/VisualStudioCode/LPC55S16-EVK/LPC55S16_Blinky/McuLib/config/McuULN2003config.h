/*
 * Copyright (c) 2019, Erich Styger
 *
 * Configuration header file for ULN2003 stepper motor driver
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUULN2003_CONFIG_H_
#define MCUULN2003_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuLibconfig.h"

#ifndef MCUULN2003_CONFIG_USE_FREERTOS_HEAP
  #define MCUULN2003_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#ifndef McuULN2003_CONFIG_USE_ACCELERATION
  #define McuULN2003_CONFIG_USE_ACCELERATION            (0)
    /*!< 1: stepper motor uses acceleration table; 0: no acceleration table used */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCUULN2003_CONFIG_H_ */
