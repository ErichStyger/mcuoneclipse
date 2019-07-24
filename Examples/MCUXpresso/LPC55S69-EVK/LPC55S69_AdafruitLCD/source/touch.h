/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include <stdbool.h>

int TOUCH_Poll(bool *pressed, int *x, int *y);
void TOUCH_Deinit(void);
void TOUCH_Init(void);

#endif /* TOUCH_H_ */
