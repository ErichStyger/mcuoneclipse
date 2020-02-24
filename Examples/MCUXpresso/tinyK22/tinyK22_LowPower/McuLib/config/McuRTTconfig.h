/**
 * \file
 * \brief Configuration header file for Segger RTT
 *
 * This header file is used to configure settings of the Segger RTT Module.
 */

#ifndef __McuRTT_CONFIG_H
#define __McuRTT_CONFIG_H

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

#endif /* __McuRTT_CONFIG_H */
