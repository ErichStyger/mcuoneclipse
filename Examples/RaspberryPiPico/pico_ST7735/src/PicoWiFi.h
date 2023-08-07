/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PICO_WIFI_H_
#define PICO_WIFI_H_

#include "McuShell.h"

uint8_t PicoWiFi_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Sets the initialized status of the CYW43 architecture
 * \param isInitialized If initialized or not
 */
void PicoWiFi_SetArchIsInitialized(bool isInitialized);

/*!
 * \brief Determine if the Cygwin WiFi chip has been initialized, because only afterwards calls to the lwIP or Cygwin device can be used.
 * \return true if cyw43_arch_init has been called, false otherwise
 */
bool PicoWiFi_ArchIsInit(void);

/*!
 * \brief Module de-initialization
 */
void PicoWiFi_Deinit(void);

/*!
 * \brief Module initialization
 */
void PicoWiFi_Init(void);

#endif /* PICO_WIFI_H_ */
