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
  /* red LED: GPIO4 18 */
  /* green LED: GPIO4 19 */
  /* blue LED: GPIO4 17 */
  CLOCK_EnableClock(kCLOCK_Gpio4);
  CLOCK_EnableClock(kCLOCK_Port4);

  McuLED_Config_t config;
  McuLED_Handle_t red, blue, green;

  /* red LED */
  config.hw.gpio = GPIO4;
  config.hw.port = PORT4;
  config.hw.pin = 18U;
  config.isLowActive = true;
  config.isOnInit = false;
  red = McuLED_InitLed(&config);
  if (red==NULL) {
    for(;;){}
  }

  /* green LED */
  config.hw.gpio = GPIO4;
  config.hw.port = PORT4;
  config.hw.pin = 19U;
  config.isLowActive = true;
  config.isOnInit = false;
  green = McuLED_InitLed(&config);
  if (green==NULL) {
    for(;;){}
  }

  /* blue LED */
  config.hw.gpio = GPIO4;
  config.hw.port = PORT4;
  config.hw.pin = 17U;
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
