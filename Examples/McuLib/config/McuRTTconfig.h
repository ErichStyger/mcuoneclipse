/**
 * \file
 * \brief Configuration header file for Segger RTT
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the Segger RTT Module.
 */

#ifndef __McuRTT_CONFIG_H
#define __McuRTT_CONFIG_H

#include "McuLib.h" /* SDK and API used */

#ifndef RTT_USE_ASM
  #define RTT_USE_ASM      (0)
    /*!< 1: use assembly version of low level buffer routines; 0: use C version */
#endif

#ifndef McuRTT_CONFIG_PROVIDE_SYSCALLS
  #define McuRTT_CONFIG_PROVIDE_SYSCALLS         (0)
    /*!< 1: RTT library implements SysCalls; 0: no Syscalls implemented */
#endif

#ifndef McuRTT_CONFIG_BLOCKING_SEND
  #define McuRTT_CONFIG_BLOCKING_SEND            (0)
    /*!< 1: using blocking call for stdio calls; 0: do not using blocking calls */
#endif

#ifndef McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS
  #define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS (0)
    /*!< Timeout value for blocking calls for sending. Use zero for no timeout */
#endif

#ifndef McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS
  #define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS    (0)
    /*!< Waiting time during blocking send. Use zero for no waiting time */
#endif

#ifndef McuRTT_CONFIG_RTT_BUFFER_SIZE_UP
  #define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP       (512)
    /*!< Size of the up (Tx on the target side) buffer in bytes */
#endif

#ifndef McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN
  #define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN     (64)
    /*!< Size of the down (Rx on the target side) buffer in bytes */
#endif

#ifndef McuRTT_CONFIG_RTT_BUFFER_SIZE_PRINTF
  #define McuRTT_CONFIG_RTT_BUFFER_SIZE_PRINTF   (64)
    /*!< Size of the buffer for RTT printf() in bytes */
#endif

#ifndef McuRTT_CONFIG_RTT_UP_BUFFER_MODE
  #define McuRTT_CONFIG_RTT_UP_BUFFER_MODE       (SEGGER_RTT_MODE_NO_BLOCK_SKIP)
    /*!< Up buffer mode: SEGGER_RTT_MODE_NO_BLOCK_SKIP, SEGGER_RTT_MODE_NO_BLOCK_TRIM or SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL */
#endif

#ifndef McuRTT_CONFIG_RTT_DOWN_BUFFER_MODE
  #define McuRTT_CONFIG_RTT_DOWN_BUFFER_MODE     (SEGGER_RTT_MODE_NO_BLOCK_SKIP)
    /*!< Up buffer mode: SEGGER_RTT_MODE_NO_BLOCK_SKIP, SEGGER_RTT_MODE_NO_BLOCK_TRIM or SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL  */
#endif

#ifndef McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS
  #define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS   (3)
  /*!< Max. number of up-buffers (T->H) available on this target    (Default: 3) */
#endif

#ifndef McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS
  #define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS (3)
  /*!< Max. number of down-buffers (H->T) available on this target  (Default: 3) */
#endif

#if McuLib_CONFIG_SDK_USE_FREERTOS
  #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY       configMAX_SYSCALL_INTERRUPT_PRIORITY /* Interrupts at this level and below will be blocked (valid values 1-15) */
#else
  #define SEGGER_RTT_LOCK_INTERRUPT_LEVEL         (3) /* Interrupts at this level and below will be blocked (valid values 1-15 for Kinetis) */
  #define SEGGER_RTT_PRIO_BITS                    4 /* NXP Kinetis M4(F) has 4 interrupt priority bits */
  #define SEGGER_RTT_MAX_INTERRUPT_PRIORITY       (SEGGER_RTT_LOCK_INTERRUPT_LEVEL<<(8-SEGGER_RTT_PRIO_BITS))
#endif

/* channel0 settings */
#define SEGGER_RTT_CHANNEL_0_ENABLED              (1) /* 1: initialize channel; 0: do not initialize channel */
#define SEGGER_RTT_CHANNEL_0_NAME                 "Terminal"
#define SEGGER_RTT_CHANNEL_0_BUFFER_SIZE_UP       (McuRTT_CONFIG_RTT_BUFFER_SIZE_UP)
#define SEGGER_RTT_CHANNEL_0_BUFFER_SIZE_DOWN     (McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN)
#define SEGGER_RTT_CHANNEL_0_MODE_UP              SEGGER_RTT_MODE_NO_BLOCK_SKIP
#define SEGGER_RTT_CHANNEL_0_MODE_DOWN            SEGGER_RTT_MODE_NO_BLOCK_SKIP

#endif /* __McuRTT_CONFIG_H */
