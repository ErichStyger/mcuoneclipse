/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#if McuSWO_CONFIG_HAS_SWO
  #include "McuSWO.h"
#endif

void PL_Init(void) {
  McuLib_Init();
  McuWait_Init();
#if McuSWO_CONFIG_HAS_SWO
  McuSWO_Init(); /* if initialization is not done by the debugger, need to do it manually here */
#endif
}
