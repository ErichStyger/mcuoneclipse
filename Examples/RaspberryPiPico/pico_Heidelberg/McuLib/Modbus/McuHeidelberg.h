/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef MODBUS_MCUHEIDELBERG_H_
#define MODBUS_MCUHEIDELBERG_H_

#include "McuShell.h"

uint8_t McuHeidelberg_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void McuHeidelberg_Deinit(void);
void McuHeidelberg_Init(void);

#endif /* MODBUS_MCUHEIDELBERG_H_ */
