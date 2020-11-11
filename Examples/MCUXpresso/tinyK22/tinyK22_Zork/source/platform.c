/*
 * platform.c
 *
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "platform.h"
#include "McuRTT.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include "McuTimeDate.h"
#include "McuShellUart.h"
#include "Shell.h"
#include "Zork.h"

void PL_Init(void) {
  McuWait_Init();
  McuRTT_Init();
  McuRTOS_Init();
  McuTimeDate_Init();
  McuShellUart_Init();
  SHELL_Init();
  ZORK_Init();
}
