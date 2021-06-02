/*
 * Copyright (c) 2020, Erich Styger
  *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BLE_H_
#define BLE_H_

#include "McuShell.h"

uint8_t BLE_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

bool BLE_sendPacket(uint16_t command, const uint8_t *buf, uint8_t count, uint8_t more_data);

bool BLE_getResponse(void);

uint8_t BLE_Echo(bool on);

bool BLE_IsConnected(void);

uint8_t BLE_SendATCommandExpectedResponse(const uint8_t *cmd, uint8_t *rxBuf, size_t rxBufSize, const uint8_t *expectedTailStr);

void BLE_Init(void);

#endif /* BLE_H_ */
