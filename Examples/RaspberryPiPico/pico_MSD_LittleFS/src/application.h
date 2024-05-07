/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "platform.h"
#include "McuShell.h"

#define APP_VERSION_STR  "v1.0b"

uint8_t App_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void APP_Run(void);

#endif /* __APPLICATION_H__ */
