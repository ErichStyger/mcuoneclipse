/**
 * \file
 * \brief Configuration header file for Segger RTT
 *
 * This header file is used to configure settings of the Segger RTT Module.
 */

#ifndef __McuRTT_CONFIG_H
#define __McuRTT_CONFIG_H

#ifndef McuRTT_CONFIG_PROVIDE_SYSCALLS
  #define  McuRTT_CONFIG_PROVIDE_SYSCALLS  (0)
    /*!< 1: RTT library implements SysCalls; 0: no Syscalls implemented */
#endif

#endif /* __McuRTT_CONFIG_H */
