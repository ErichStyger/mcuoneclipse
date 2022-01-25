/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"

void PL_Init(void) {
  McuLib_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
}

