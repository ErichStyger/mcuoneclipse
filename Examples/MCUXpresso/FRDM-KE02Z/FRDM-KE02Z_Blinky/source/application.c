/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "platform.h"
#include "application.h"
#include "McuLED.h"
#include "McuWait.h"

static McuLED_Handle_t ledRed, ledGreen, ledBlue;

static void InitLed(void) {
  McuLED_Config_t config;

  McuLED_GetDefaultConfig(&config);
  config.isLowActive = true;
  config.isOnInit = false;
  config.hw.port = PORT;
  /* red: PTH1 */
  config.hw.portType = kPORT_PTH;
  config.hw.portNum = kGPIO_PORTH;
  config.hw.pin = 1;
  ledRed = McuLED_InitLed(&config);
  /* green: PTH2 */
  config.hw.portType = kPORT_PTH;
  config.hw.portNum = kGPIO_PORTH;
  config.hw.pin = 2;
  ledGreen = McuLED_InitLed(&config);
  /* blue: PTE7 */
  config.hw.portType = kPORT_PTE;
  config.hw.portNum = kGPIO_PORTE;
  config.hw.pin = 7;
  ledBlue = McuLED_InitLed(&config);
}

void APP_Run(void) {
  PL_Init();
  InitLed();
  for(;;) {
    McuLED_On(ledRed);
    McuWait_Waitms(100);
    McuLED_Off(ledRed);

    McuLED_On(ledGreen);
    McuWait_Waitms(100);
    McuLED_Off(ledGreen);

    McuLED_On(ledBlue);
    McuWait_Waitms(100);
    McuLED_Off(ledBlue);
  }
}
