/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RS485_H_
#define RS485_H_

#include <stdbool.h>
#include <stdint.h>
#include "McuShell.h"

#define RS485_BROADCAST_ADDRESS (0x00) /* special broadcast address */

uint8_t RS485_SendCommand(uint8_t dstAddr, unsigned char *cmd, int32_t timeoutMs, bool intern, uint32_t nofRetry);

uint8_t RS485_GetAddress(void);

uint8_t RS485_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void RS485_Deinit(void);
void RS485_Init(void);

#endif /* RS485_H_ */
