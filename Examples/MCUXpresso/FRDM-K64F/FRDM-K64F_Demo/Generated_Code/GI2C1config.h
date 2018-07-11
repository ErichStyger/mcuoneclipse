/**
 * \file
 * \brief Configuration header file for GenericI2C
 *
 * This header file is used to configure settings of the Generic I2C module.
 */

#ifndef __GI2C1_CONFIG_H
#define __GI2C1_CONFIG_H

#if !defined(GI2C1_CONFIG_USE_ON_REQUEST_BUS_EVENT)
  #define GI2C1_CONFIG_USE_ON_REQUEST_BUS_EVENT    (0)
    /*!< 1: generate user events for requesting bus; 0: no user events */
  #define GI2C1_CONFIG_ON_REQUEST_BUS_EVENT   McuGenericI2C_OnRequestBus
  void GI2C1_CONFIG_ON_REQUEST_BUS_EVENT(void); /* prototype */
#endif

#if !defined(GI2C1_CONFIG_USE_ON_RELEASE_BUS_EVENT)
  #define GI2C1_CONFIG_USE_ON_RELEASE_BUS_EVENT    (0)
    /*!< 1: generate user events for releasing bus; 0: no user events */
  #define GI2C1_CONFIG_ON_RELEASE_BUS_EVENT   McuGenericI2C_DriverAuthorBus
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
#include "I2C.h" /* interface of low level I2C driver */
#define GI2C1_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE  (0)

#endif /* __GI2C1_CONFIG_H */
