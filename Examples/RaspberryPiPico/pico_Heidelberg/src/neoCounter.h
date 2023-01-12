/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef NEOCOUNTER_H_
#define NEOCOUNTER_H_

#include "McuShell.h"
#include "buttons.h"
#include "McuDebounce.h"

uint8_t NeoCounter_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void NeoCounter_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind);

void NeoCounter_Init(void);

#endif /* NEOAPP_H_ */
