/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SHUTDOWN_H_
#define SHUTDOWN_H_

#include <stdbool.h>

bool SHUTDOWN_UserPowerOffRequested(void);

void SHUTDOWN_RequestPowerOff(void);
void SHUTDOWN_RequestPowerOn(void);

void SHUTDOWN_Init(void);
void SHUTDOWN_Deinit(void);

#endif /* SHUTDOWN_H_ */
