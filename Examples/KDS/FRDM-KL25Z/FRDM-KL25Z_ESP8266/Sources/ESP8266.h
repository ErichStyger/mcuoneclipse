/*
 * ESP8266.h
 *
 *  Created on: 16.11.2014
 *      Author: tastyger
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "CLS1.h"

uint8_t ESP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

uint8_t ESP_SendStr(const uint8_t *str, CLS1_ConstStdIOType *io);

uint8_t ESP_Test(void);

uint8_t ESP_Restart(const CLS1_StdIOType *io, uint16_t timeoutMs);

uint8_t ESP_SelectWiFiMode(uint8_t mode);

uint8_t ESP_GetFirmwareString(uint8_t *fwBuf, size_t fwBufSize);

uint8_t ESP_ListAccessPoint(void);

uint8_t ESP_JoinAccessPoint(uint8_t *ssid, uint8_t *pwd, CLS1_ConstStdIOType *io);

uint8_t ESP_ConnectWiFi(uint8_t *ssid, uint8_t *pwd, int nofRetries, CLS1_ConstStdIOType *io);

void ESP_Process(void);

void ESP_Init(void);

#endif /* ESP8266_H_ */
