/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SWO_H_
#define SWO_H_

void SWO_SendStr(const char *str);

/* used to set speed back to desired value */
void SWO_SetSpeed(void);

void SWO_Init(void);

#endif /* SWO_H_ */
