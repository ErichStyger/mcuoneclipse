/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include "buttons_config.h"

bool BTN_IsPressed(BTN_Buttons_e btn);

void BTN_Deinit(void);

void BTN_Init(void);

#endif /* BUTTONS_H_ */
