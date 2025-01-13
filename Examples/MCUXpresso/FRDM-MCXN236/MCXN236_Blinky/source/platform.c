/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "platform.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuWait.h"
#include "McuRTT.h"

void PL_Init(void) {
  McuGPIO_Init();
  McuLED_Init();
  McuWait_Init();
#if PL_CONFIG_USE_RTT
  McuRTT_Init();
#endif
}
