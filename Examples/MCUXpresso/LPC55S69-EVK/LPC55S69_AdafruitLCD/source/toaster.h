/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TOASTER_H_
#define TOASTER_H_

#include <stdbool.h>

bool TOASTER_IsRunning(void);
void TOASTER_StopScreenSaver(void);
void TOASTER_Show(void);
void TOASTER_Init(void);
void TOASTER_Deinit(void);

#endif /* TOASTER_H_ */
