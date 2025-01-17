/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuSemihost.h"
#include "McuShell.h"

void PL_Init(void) {
  McuLib_Init();
  McuWait_Init();
  McuSemiHost_Init();
#if PL_CONFIG_USE_SHELL
  McuShell_Init();
#endif
}
