/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>

#define BTN_SW2     (1<<0)

bool BTN_SW2ButtonIsPressed(void);

void BTN_Deinit(void);

void BTN_Init(void);

#endif /* BUTTONS_H_ */
