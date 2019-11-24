/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RS485_H_
#define RS485_H_

#include <stdbool.h>
#include "McuShell.h"

uint8_t RS485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void RS485_Deinit(void);
void RS485_Init(void);

#endif /* RS485_H_ */
