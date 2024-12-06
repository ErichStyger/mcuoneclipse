/*!
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief \brief Configuration items for the McuSDEP module.
 */

#ifndef MCUDEPCONFIG_H_
#define MCUDEPCONFIG_H_

#include "McuLib.h"

#ifndef McuSDEP_CONFIG_IS_ENABLED
  #define McuSDEP_CONFIG_IS_ENABLED   (0 && McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< If the SDEP module is enabled or not. */
#endif

#ifndef McuSDEP_CONFIG_USE_FRAMING
  #define McuSDEP_CONFIG_USE_FRAMING  (0)
    /* if using SDEP messages with a framing, useful for shared SDEP and SDEP communication */
#endif

#ifndef McuSDEP_CONFIG_MSG_FRAMING_START
  #define McuSDEP_CONFIG_MSG_FRAMING_START  '@'   /* marker to start an SDEP message */
    /*!< used if McuSDEP_CONFIG_USE_FRAMING is enabled, used as starting frame */
#endif

#ifndef McuSDEP_CONFIG_MSG_FRAMING_END
  #define McuSDEP_CONFIG_MSG_FRAMING_END    '\n'  /* marker to end a SDEP message */
    /*!< used if McuSDEP_CONFIG_USE_FRAMING is enabled, used as ending frame */
#endif

#ifndef McuSDEP_CONFIG_RX_BUFFER_SIZE
  #define McuSDEP_CONFIG_RX_BUFFER_SIZE  (64)
    /* size of the buffer for the incoming SDEP data */
#endif

#ifndef McuSDEP_CONFIG_SHELL_TO_SDEP_QUEUE_LENGTH
  #define McuSDEP_CONFIG_SHELL_TO_SDEP_QUEUE_LENGTH    (128)
  /*!< Size of buffer of data sent by shell to SDEP */
#endif

#ifndef McuSDEP_CONFIG_USE_FREERTOS
  #define McuSDEP_CONFIG_USE_FREERTOS  (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< If FreeRTOS (Queues) shall be used or not */
#endif

#endif /* MCUDEPCONFIG_H_ */