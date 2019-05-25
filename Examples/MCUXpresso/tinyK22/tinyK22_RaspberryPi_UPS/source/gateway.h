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
#include "McuShell.h"

extern uint8_t GATEWAY_LinuxToShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType GATEWAY_stdioLinuxToShell; /* default standard I/O */

extern uint8_t GATEWAY_HostToShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType GATEWAY_stdioHostToShell; /* default standard I/O */

uint32_t GATEWAY_GetNofRx(void);
uint32_t GATEWAY_GetNofTx(void);

bool GATEWAY_LinuxToHostIsEnabled(void);
void GATEWAY_SetLinuxToHostEnabled(bool isEnabled);

bool GATEWAY_HostToLinuxIsEnabled(void);
void GATEWAY_SetHostToLinuxEnabled(bool isEnabled);

void GW_WriteToHost(const unsigned char *str);

void GATEWAY_Process(void);

void GATEWAY_Init(void);
void GATEWAY_Deinit(void);

#endif /* UARTGATEWAY_H_ */
