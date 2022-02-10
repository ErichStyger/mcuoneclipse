/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "McuShell.h"

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void APP_Init(void);

#endif /* APPLICATION_H_ */
