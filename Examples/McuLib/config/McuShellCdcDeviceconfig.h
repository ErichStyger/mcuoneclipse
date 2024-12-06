/*!
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief \brief Configuration items for the McuShellCdcDevice module.
 */

#ifndef MCUSHELLCDCDEVICECONFIG_H_
#define MCUSHELLCDCDEVICECONFIG_H_

#include "McuLib.h"

#ifndef McuShellCdcDevice_CONFIG_IS_ENABLED
  #define McuShellCdcDevice_CONFIG_IS_ENABLED    (0)
    /*!< if module is enabled or not */
#endif

#ifndef McuShellCdcDevice_CONFIG_RX_BUFFER_SIZE
  #define McuShellCdcDevice_CONFIG_RX_BUFFER_SIZE    (McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE)
    /*!< default receiving buffer size */
#endif

#ifndef McuShellCdcDevice_CONFIG_USE_FREERTOS
  #define McuShellCdcDevice_CONFIG_USE_FREERTOS  (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< If FreeRTOS (Queues) shall be used or not */
#endif

#ifndef McuShellCdcDevice_CONFIG_PROCESS_WAIT_TIME_MS
  #define McuShellCdcDevice_CONFIG_PROCESS_WAIT_TIME_MS    (5)
    /*!< Processing wait time for the USB CDC device task, in milli-seconds */
#endif

#ifndef McuShellCdcDevice_CONFIG_PROCESS_PRIORITY
  #define McuShellCdcDevice_CONFIG_PROCESS_PRIORITY    (configMAX_PRIORITIES-1)
    /*!< FreeRTOS task priority for processing task */
#endif

#endif