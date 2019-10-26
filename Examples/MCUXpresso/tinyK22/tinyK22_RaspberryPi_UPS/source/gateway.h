/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef UARTGATEWAY_H_
#define UARTGATEWAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

uint8_t GATEWAY_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

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

void GATEWAY_UartWriteToHostCh(unsigned char ch);
void GATEWAY_UartWriteToHostStr(const unsigned char *str);

void GATEWAY_UartWriteToLinuxCh(unsigned char ch);
void GATEWAY_UartWriteToLinuxStr(const unsigned char *str);

void GATEWAY_Process(void);

void GATEWAY_Init(void);
void GATEWAY_Deinit(void);

#endif /* UARTGATEWAY_H_ */
