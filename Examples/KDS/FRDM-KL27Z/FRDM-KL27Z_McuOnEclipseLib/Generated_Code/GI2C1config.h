/**
 * \file
 * \brief Configuration header file for GenericI2C
 *
 * This header file is used to configure settings of the Generic I2C module.
 */

#ifndef __GI2C1_CONFIG_H
#define __GI2C1_CONFIG_H

#if !defined(GI2C1_CONFIG_USE_ON_REQUEST_BUS_EVENT)
  #define GI2C1_CONFIG_USE_ON_REQUEST_BUS_EVENT    (1)
    /*!< 1: generate user events for requesting bus; 0: no user events */
  #define GI2C1_CONFIG_ON_REQUEST_BUS_EVENT   GI2C1_OnRequestBus
  void GI2C1_CONFIG_ON_REQUEST_BUS_EVENT(void); /* prototype */
#endif

#if !defined(GI2C1_CONFIG_USE_ON_RELEASE_BUS_EVENT)
  #define GI2C1_CONFIG_USE_ON_RELEASE_BUS_EVENT    (1)
    /*!< 1: generate user events for releasing bus; 0: no user events */
  #define GI2C1_CONFIG_ON_RELEASE_BUS_EVENT   GI2C1_OnReleaseBus
  void GI2C1_CONFIG_ON_RELEASE_BUS_EVENT(void); /* prototype */
#endif

#if !defined(GI2C1_CONFIG_USE_ON_ERROR_EVENT)
  #define GI2C1_CONFIG_USE_ON_ERROR_EVENT    (0)
    /*!< 1: generate user events for errors; 0: no error events */
  #define GI2C1_CONFIG_ON_ERROR_EVENT   McuGenericI2C_OnRequestBus
  void GI2C1_CONFIG_ON_ERROR_EVENT(void); /* prototype */
#endif

#if !defined(GI2C1_CONFIG_USE_MUTEX)
  #define GI2C1_CONFIG_USE_MUTEX             (1)
    /*!< 1: Use a mutex to protect access to the bus; 0: no mutex used */
#endif

#if !defined(GI2C1_CONFIG_WRITE_BUFFER_SIZE)
  #define GI2C1_CONFIG_WRITE_BUFFER_SIZE             (16)
    /*!< Size of the write buffer size which defines the maximum block size which can be sent */
#endif

#if !defined(GI2C1_CONFIG_SUPPORT_STOP_NO_START)
  #define GI2C1_CONFIG_SUPPORT_STOP_NO_START      (0)
    /*!< 1: send a STOP condition without sending a new START condition. Currently only supported for the GenericSWI2C component. 0: send a STOP for every START */
#endif

/* configuration of function names used for low level I2C functions */
#ifndef GI2C1_CONFIG_INTERFACE_HEADER_FILE
  #define GI2C1_CONFIG_INTERFACE_HEADER_FILE "I2C1.h"
#endif
#include GI2C1_CONFIG_INTERFACE_HEADER_FILE /* interface of low level I2C driver */

#ifndef GI2C1_CONFIG_RECV_BLOCK
  #define GI2C1_CONFIG_RECV_BLOCK                        I2C1_RecvBlock
#endif

#ifndef GI2C1_CONFIG_SEND_BLOCK
  #define GI2C1_CONFIG_SEND_BLOCK                        I2C1_SendBlock
#endif

#if GI2C1_CONFIG_SUPPORT_STOP_NO_START
  #ifndef GI2C1_CONFIG_SEND_BLOCK_CONTINUE
    #define GI2C1_CONFIG_SEND_BLOCK_CONTINUE             I2C1_SendBlockContinue
  #endif
#endif

#ifndef GI2C1_CONFIG_SEND_STOP
  #define GI2C1_CONFIG_SEND_STOP                         I2C1_SendStop
#endif

#ifndef GI2C1_CONFIG_SELECT_SLAVE
  #define GI2C1_CONFIG_SELECT_SLAVE                      I2C1_SelectSlave
#endif

#ifndef GI2C1_CONFIG_RECV_BLOCK_CUSTOM
  #define GI2C1_CONFIG_RECV_BLOCK_CUSTOM                 I2C1_RecvBlockCustom
#endif

#ifndef GI2C1_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE
  #define GI2C1_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE       (defined(I2C1_RECVBLOCKCUSTOM_AVAILABLE) && (I2C1_RECVBLOCKCUSTOM_AVAILABLE))
#endif


#endif /* __GI2C1_CONFIG_H */
