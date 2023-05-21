/**
 * \file
 * \brief Configuration header file for GenericI2C
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the Generic I2C module.
 */

#ifndef __McuGenericI2C_CONFIG_H
#define __McuGenericI2C_CONFIG_H

#include "McuLibconfig.h"

#if !defined(McuGenericI2C_CONFIG_USE_ON_REQUEST_BUS_EVENT)
  #define McuGenericI2C_CONFIG_USE_ON_REQUEST_BUS_EVENT    (1)
    /*!< 1: generate user events for requesting bus; 0: no user events */
  #define McuGenericI2C_CONFIG_ON_REQUEST_BUS_EVENT   McuGenericI2C_OnRequestBus
  void McuGenericI2C_CONFIG_ON_REQUEST_BUS_EVENT(void); /* prototype */
#endif

#if !defined(McuGenericI2C_CONFIG_USE_ON_RELEASE_BUS_EVENT)
  #define McuGenericI2C_CONFIG_USE_ON_RELEASE_BUS_EVENT    (1)
    /*!< 1: generate user events for releasing bus; 0: no user events */
  #define McuGenericI2C_CONFIG_ON_RELEASE_BUS_EVENT   McuGenericI2C_OnReleaseBus
  void McuGenericI2C_CONFIG_ON_RELEASE_BUS_EVENT(void); /* prototype */
#endif

#if !defined(McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT)
  #define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT    (0)
    /*!< 1: generate user events for errors; 0: no error events */
  #define McuGenericI2C_CONFIG_ON_ERROR_EVENT   McuGenericI2C_OnError
  void McuGenericI2C_CONFIG_ON_ERROR_EVENT(void); /* prototype */
#endif

#if !defined(McuGenericI2C_CONFIG_USE_MUTEX)
  #define McuGenericI2C_CONFIG_USE_MUTEX             (0 && McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< 1: Use a mutex to protect access to the bus; 0: no mutex used */
#endif

#if !defined(McuGenericI2C_CONFIG_USE_TIMEOUT)
  #define McuGenericI2C_CONFIG_USE_TIMEOUT             (0)
    /*!< 1: Use a timeout in case problems; 0: do not use a timeout */
#endif

#if !defined(McuGenericI2C_CONFIG_TIMEOUT_US)
  #define McuGenericI2C_CONFIG_TIMEOUT_US  ((uint32_t)500)  /* number of microseconds as specified in properties used for timeout */
#endif

#if !defined(McuGenericI2C_CONFIG_WRITE_BUFFER_SIZE)
  #define McuGenericI2C_CONFIG_WRITE_BUFFER_SIZE             (32)
    /*!< Size of the write buffer size which defines the maximum block size which can be sent */
#endif

#if !defined(McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START)
  #define McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START      (0)
    /*!< 1: send a STOP condition without sending a new START condition. Currently only supported for the GenericSWI2C component. 0: send a STOP for every START */
#endif

/* configuration of function names used for low level I2C functions */
#ifndef McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE "McuGenericSWI2C.h"
#endif
#include McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE /* interface of low level I2C driver */

#ifndef McuGenericI2C_CONFIG_RECV_BLOCK
  #define McuGenericI2C_CONFIG_RECV_BLOCK                        McuGenericSWI2C_RecvBlock
#endif

#ifndef McuGenericI2C_CONFIG_SEND_BLOCK
  #define McuGenericI2C_CONFIG_SEND_BLOCK                        McuGenericSWI2C_SendBlock
#endif

#if McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START
  #ifndef McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE
    #define McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE             McuGenericSWI2C_SendBlockContinue
  #endif
#endif

#ifndef McuGenericI2C_CONFIG_SEND_STOP
  #define McuGenericI2C_CONFIG_SEND_STOP                         McuGenericSWI2C_SendStop
#endif

#ifndef McuGenericI2C_CONFIG_SELECT_SLAVE
  #define McuGenericI2C_CONFIG_SELECT_SLAVE                      McuGenericSWI2C_SelectSlave
#endif

#ifndef McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM                 McuGenericSWI2C_RecvBlockCustom
#endif

#ifndef McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE       (defined(McuGenericSWI2C_RECVBLOCKCUSTOM_AVAILABLE) && (McuGenericSWI2C_RECVBLOCKCUSTOM_AVAILABLE))
#endif


#endif /* __McuGenericI2C_CONFIG_H */
