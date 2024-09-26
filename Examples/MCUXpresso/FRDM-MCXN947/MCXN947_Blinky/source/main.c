/*
 * Copyright (c) 2024, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include "fsl_clock.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuWait.h"

static void blink(void) {
  CLOCK_EnableClock(kCLOCK_Gpio0); /* red */
  CLOCK_EnableClock(kCLOCK_Port0);
  CLOCK_EnableClock(kCLOCK_Gpio1); /* blue */
  CLOCK_EnableClock(kCLOCK_Port1);

  McuLED_Config_t config;
  McuLED_Handle_t red, blue, green;

  /* red LED */
  config.hw.gpio = GPIO0;
  config.hw.port = PORT0;
  config.hw.pin = 10U;
  config.isLowActive = true;
  config.isOnInit = false;
  red = McuLED_InitLed(&config);
  if (red==NULL) {
    for(;;){}
  }

  /* green LED */
  config.hw.gpio = GPIO0;
  config.hw.port = PORT0;
  config.hw.pin = 27U;
  config.isLowActive = true;
  config.isOnInit = false;
  green = McuLED_InitLed(&config);
  if (green==NULL) {
    for(;;){}
  }

  /* blue LED */
  config.hw.gpio = GPIO1;
  config.hw.port = PORT1;
  config.hw.pin = 2U;
  config.isLowActive = true;
  config.isOnInit = false;
  blue = McuLED_InitLed(&config);
  if (blue==NULL) {
    for(;;){}
  }

  for(;;) {
    McuLED_On(red);
    McuWait_Waitms(500);
    McuLED_Off(red);
    McuWait_Waitms(500);
    McuLED_Toggle(red);
    McuWait_Waitms(500);
    McuLED_Toggle(red);
    McuWait_Waitms(500);

    McuLED_On(green);
    McuWait_Waitms(500);
    McuLED_Off(green);
    McuWait_Waitms(500);
    McuLED_Toggle(green);
    McuWait_Waitms(500);
    McuLED_Toggle(green);
    McuWait_Waitms(500);

    McuLED_On(blue);
    McuWait_Waitms(500);
    McuLED_Off(blue);
    McuWait_Waitms(500);
    McuLED_Toggle(blue);
    McuWait_Waitms(500);
    McuLED_Toggle(blue);
    McuWait_Waitms(500);
  }
}

int main(void) {
  /* Init board hardware. */
  BOARD_InitBootPins();
  BOARD_InitBootClocks();
  BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
  /* Init FSL debug console. */
  BOARD_InitDebugConsole();
#endif

  McuGPIO_Init();
  McuLED_Init();
  McuWait_Init();
  blink();

  for(;;) {}
  return 0 ;
}
