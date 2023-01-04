/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SWO_H_
#define SWO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuSWOconfig.h"
#include "McuShell.h"

extern uint8_t McuSWO_DefaultShellBuffer[McuShell_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */
extern McuShell_ConstStdIOType McuSWO_stdio; /* default standard I/O */

uint8_t McuSWO_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io);

/* send a string through SWO ITM Port 0 (0x1) */
void McuSWO_SendStr(const unsigned char *str);

/* The TraceClock is used to configure the SWO speed. Use this method if the clock has been changed */
void McuSWO_ChangeTraceClock(uint32_t traceClock);

/* used to change speed to the desired value */
void McuSWO_ChangeSpeed(uint32_t baud);

/* call this to initialize the module. Possible usage:  McuSWO_Init(SystemCoreClock, McuSWO_CONFIG_SPEED_BAUD); */
void McuSWO_Init(uint32_t traceClock, uint32_t baud);

#ifdef __cplusplus
}
#endif

#endif /* SWO_H_ */
