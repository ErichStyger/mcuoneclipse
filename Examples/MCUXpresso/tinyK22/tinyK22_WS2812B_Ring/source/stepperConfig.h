/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef STEPPERCONFIG_H_
#define STEPPERCONFIG_H_

#include "McuLibconfig.h"

#ifndef STEPPER_CONFIG_USE_FREERTOS_HEAP
  #define STEPPER_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#endif /* STEPPERCONFIG_H_ */
