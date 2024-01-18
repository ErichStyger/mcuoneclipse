/**
 * \file
 * \brief Configuration header file for a RingBuffer.
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the ring buffer module.
 */

#ifndef MCURBCONFIG_H_
#define MCURBCONFIG_H_

#include "McuLibconfig.h"

#ifndef MCURB_CONFIG_USE_FREERTOS_HEAP
  #define MCURB_CONFIG_USE_FREERTOS_HEAP   (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS Heap (default), 0: use stdlib malloc() and free() */
#endif

#endif /* MCURBCONFIG_H_ */
