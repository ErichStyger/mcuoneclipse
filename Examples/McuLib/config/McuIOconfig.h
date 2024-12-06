/*!
 * Copyright (c) 2024, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration header file for the McuIO module.
 */

#ifndef __MCU_IO_CONFIG_H__
#define __MCU_IO_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MCUIO_CONFIG_USE_FREERTOS_HEAP
  #define MCUIO_CONFIG_USE_FREERTOS_HEAP  (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS heap for memory allocation (default); 0: using normal malloc() and free()  */
#endif

#ifndef MCUIO_CONFIG_USE_FREERTOS_QUEUE
  #define MCUIO_CONFIG_USE_FREERTOS_QUEUE  (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: use FreeRTOS queue for buffer management allocation (default); 0: using bare-metal ring buffer  */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* __MCU_IO_CONFIG_H__ */
