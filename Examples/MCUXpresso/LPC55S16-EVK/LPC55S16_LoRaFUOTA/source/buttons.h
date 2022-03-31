/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <stdbool.h>
#include "buttons_config.h"

/* Gadfly sync with button */
bool BTN_IsPressed(BTN_Buttons_e btn);

/* Gadfly sync with debouncing */
void BTN_PollDebounce(void);

#include "McuDebounce.h"
void BTN_RegisterAppCallback(void (*)(McuDbnc_EventKinds, uint32_t));

void BTN_Deinit(void);

void BTN_Init(void);

#endif /* BUTTONS_H_ */
