/*
 * Copyright (c) 2019, Erich Styger
 *
 * Configuration header file for X12.017 quad-stepper motor driver
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_X12_017_CONFIG_H_
#define MCU_X12_017_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuLibconfig.h"

#ifndef McuX12_017_CONFIG_USE_FREERTOS_HEAP
  #define McuX12_017_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCU_X12_017_CONFIG_H_ */
