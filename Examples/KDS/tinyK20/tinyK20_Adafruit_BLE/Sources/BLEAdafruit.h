/*
 * AdaBLE.h
 *
 *  Created on: 30.12.2015
 *      Author: Erich Styger
 */

#ifndef SOURCES_ADABLE_H_
#define SOURCES_ADABLE_H_

#include "Platform.h"
#include "sdep.h"
#include "CLS1.h"

uint8_t BLE_SendATCommandExpectedResponse(const uint8_t *cmd, uint8_t *rxBuf, size_t rxBufSize, const uint8_t *expectedTailStr);

bool BLE_sendPacket(uint16_t command, const uint8_t *buf, uint8_t count, uint8_t more_data);

bool BLE_getResponse(void);

uint8_t BLE_Echo(bool on);

bool BLE_IsConnected(void);

uint8_t BLE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

void BLE_Init(void);

#endif /* SOURCES_ADABLE_H_ */
