/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INI_H_
#define INI_H_

#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

uint8_t INI_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

#endif /* INI_H_ */
