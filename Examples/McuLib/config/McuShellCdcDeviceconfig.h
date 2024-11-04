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
#endif

#ifndef McuShellCdcDevice_CONFIG_UART_RX_BUFFER_SIZE
  #define McuShellCdcDevice_CONFIG_UART_RX_BUFFER_SIZE    (McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE)
#endif

#ifndef McuShellCdcDevice_CONFIG_USE_FREERTOS
  #define McuShellCdcDevice_CONFIG_USE_FREERTOS  (McuLib_CONFIG_SDK_USE_FREERTOS)
    /*!< If FreeRTOS (Queues) shall be used or not */
#endif

#endif