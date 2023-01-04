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
 * \brief Module de-initialization
 */
void PicoWiFi_Deinit(void);

/*!
 * \brief Module initialization
 */
void PicoWiFi_Init(void);

#endif /* PICO_WIFI_H_ */
