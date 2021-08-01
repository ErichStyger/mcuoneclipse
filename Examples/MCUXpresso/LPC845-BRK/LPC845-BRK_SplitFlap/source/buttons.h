/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>

#define BTN_K1      (1<<0)
#define BTN_K3      (1<<1)

bool BTN_K1ButtonIsPressed(void);
bool BTN_K3ButtonIsPressed(void);

void BTN_Deinit(void);

void BTN_Init(void);

#endif /* BUTTONS_H_ */
