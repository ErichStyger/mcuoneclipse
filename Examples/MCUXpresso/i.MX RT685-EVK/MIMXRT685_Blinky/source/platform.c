/*
 * platform.c
 * Copyright (c) 2024, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"

void PL_Init(void) {
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();
}
