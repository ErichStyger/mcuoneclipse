/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOAPP_H_
#define NEOAPP_H_

#include "platform.h"
#if PL_CONFIG_USE_NEO_APP

#include "McuShell.h"
#include <stdint.h>
#include "NeoPixel.h"

uint8_t NeoApp_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

bool NeoApp_RequestUpdateLEDsFromISR(void);
void NeoApp_RequestUpdateLEDs(void);

void NeoApp_Init(void);

#endif /* PL_CONFIG_USE_NEO_APP */

#endif /* NEOAPP_H_ */
