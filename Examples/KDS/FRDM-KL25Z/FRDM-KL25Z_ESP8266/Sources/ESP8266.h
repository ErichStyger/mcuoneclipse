/*
 * ESP8266.h
 *
 *      Author: Erich Styger
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "CLS1.h"

uint8_t ESP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);

uint8_t ESP_SendStr(const uint8_t *str, CLS1_ConstStdIOType *io);

/*!
 * \brief Sends an AT command to test the connection
 * \return Error code, ERR_OK for no failure
 */
uint8_t ESP_TestAT(void);

uint8_t ESP_Restart(const CLS1_StdIOType *io, uint16_t timeoutMs);

uint8_t ESP_SelectMode(uint8_t mode);

uint8_t ESP_GetFirmwareString(uint8_t *fwBuf, size_t fwBufSize);

uint8_t ESP_ListAccessPoint(void);

uint8_t ESP_JoinAP(const uint8_t *ssid, const uint8_t *pwd, int nofRetries, CLS1_ConstStdIOType *io);

void ESP_Process(void);

void ESP_Init(void);

#endif /* ESP8266_H_ */
