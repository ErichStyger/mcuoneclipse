/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MIMXRT1064_gcov_cpp.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuCoverage.h"
#include "rdimon/McuRdimon.h"
#include "McuSemihost.h"

static void blink(void) {
  McuLED_Config_t config;
  McuLED_Handle_t led;

  McuLED_GetDefaultConfig(&config);
  config.hw.gpio = GPIO1;
  config.hw.pin = 9;
  McuGPIO_SetMux(&config.hw, IOMUXC_GPIO_AD_B0_09_GPIO1_IO09); /* set special i.MX RT muxing fields */
  led = McuLED_InitLed(&config);
  if (led==NULL) {
    for(;;){}
  }
  for(int i=0;i<10;i++) {
    McuLED_Toggle(led);
    McuWait_Waitms(500);
  }
}

static void init(void) {
  McuWait_Init(); /* busy waiting, used by blink() */
  McuGPIO_Init(); /* GPIO pins, used by blink() */
  McuLED_Init();  /* LED driver, used by blink() */
#if McuSemihost_CONFIG_IS_ENABLED
  McuSemiHost_Init(); /* using Semihosting to write the files to to host */
#endif
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init(); /* initialize standard file descriptors */
#endif
#if McuCoverage_CONFIG_IS_ENABLED
#ifndef __cplusplus /* only if not using C++ */
  McuCoverage_Init();  /* call global constructors to initialize gcov hooks: not needed for C++ */
#endif
  if (!McuCoverage_Check()) { /* optional semihosting check: checks if writing files is possible */
    for(;;) {} /* error, something not working with coverage and writing information */
  }
#endif
}


int main(void) {
  init();
  BOARD_ConfigMPU();
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
#endif

  blink();

  PRINTF("Hello World\r\n");

#if McuCoverage_CONFIG_IS_ENABLED
  McuCoverage_WriteFiles(); /* write coverage files, might take a while depending how many files are covered */
#endif

  /* Force the counter to be placed into memory. */
  volatile static int i = 0 ;
  /* Enter an infinite loop, just incrementing a counter. */
  while(1) {
      i++ ;
      /* 'Dummy' NOP to allow source level single stepping of
          tight while() loop */
      __asm volatile ("nop");
  }
  return 0 ;
}
