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

uint8_t McuSWO_ParseCommand(const uint8_t *cmd, bool *handled, McuShell_ConstStdIOType *io);

/* send a string through SWO ITM Port 0 (0x1) */
void McuSWO_SendStr(const unsigned char *str);

/* used to set speed back to desired value */
void McuSWO_SetSpeed(void);

void McuSWO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* SWO_H_ */
