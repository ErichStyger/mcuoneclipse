/*
 * Copyright (c) 2020-2026 Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCU_WIFI_H_
#define MCU_WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "McuWiFi_config.h"

#if MCU_WIFI_CONFIG_USE_SHELL
  #include "McuShell.h"

  /*!
   * \brief Command line and shell handler
   * \param cmd The command to be parsed
   * \param handled If command has been recognized and handled
   * \param io I/O handler to be used
   * \return error code, otherwise ERR_OK
   */
  uint8_t McuWiFi_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*!
 * \brief Decides if we are connected or not
 * \return true if we are connected to WiFi, false otherwise
 */
bool McuWiFi_isConnected(void);

/*!
 * \brief Decides if reconnect data is available
 * \return true if WiFi can reconnect with already configured credentials
 */
bool McuWiFi_canReconnect(void);

/*!
 * \brief return the host name
 */
const char *McuWifi_GetHostName(void);

/*!
 * \brief Module de-initialization
 */
void McuWiFi_Deinit(void);

/*!
 * \brief Module initialization
 */
void McuWiFi_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MCU_WIFI_H_ */
