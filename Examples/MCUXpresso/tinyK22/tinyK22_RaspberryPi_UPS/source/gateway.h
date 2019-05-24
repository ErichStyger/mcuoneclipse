/*
 * doGateWay.h
 *
 *  Created on: 18.03.2019
 *      Author: Erich Styger
 */

#ifndef UARTGATEWAY_H_
#define UARTGATEWAY_H_

#include <stdint.h>
#include <stdbool.h>

uint32_t GATEWAY_GetNofRx(void);
uint32_t GATEWAY_GetNofTx(void);

bool GATEWAY_IsEnabled(void);
void GATEWAY_SetEnabled(bool isEnabled);

void GW_WriteToHost(const unsigned char *str);

void GATEWAY_Process(void);

void GATEWAY_Init(void);
void GATEWAY_Deinit(void);

#endif /* UARTGATEWAY_H_ */
