/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>

#define BTN_UP      (1<<0)
#define BTN_DOWN    (1<<1)
#define BTN_LEFT    (1<<2)
#define BTN_RIGHT   (1<<3)
#define BTN_CENTER  (1<<4)

bool BTN_DownButtonIsPressed(void);
bool BTN_CenterButtonIsPressed(void);

void BTN_Deinit(void);

void BTN_Init(void);

#endif /* BUTTONS_H_ */
