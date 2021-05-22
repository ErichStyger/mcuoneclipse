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

/* send a string through SWO ITM Port 0 (0x1) */
void McuSWO_SendStr(const char *str);

/* used to set speed back to desired value */
void McuSWO_SetSpeed(void);

void McuSWO_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* SWO_H_ */
