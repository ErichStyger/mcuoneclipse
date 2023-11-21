/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"
#include "McuRTOS.h"
#include "leds.h"
#if McuRdimon_CONFIG_IS_ENABLED
  #include "rdimon/McuRdimon.h"
#endif
#if McuSemihost_CONFIG_IS_ENABLED
  #include "McuSemihost.h"
#endif
#if PL_CONFIG_USE_GCOV
  #include "gcov_support.h"
  #include "gcov_test.h"
#endif
#include <stdio.h>

void PL_Init(void) {
#if McuRdimon_CONFIG_IS_ENABLED
  McuRdimon_Init();
#endif
#if McuSemihost_CONFIG_IS_ENABLED
  McuSemiHost_Init();
  printf("hello world!\n");
  McuSemiHost_Test();
#endif
#if PL_CONFIG_USE_GCOV
  gcov_init();  /* initialize library */
  gcov_check(); /* test for file I/O only  */
  gcov_test(3);
#endif
  CLOCK_EnableClock(kCLOCK_Iocon); /* ungate clock for IOCON */
  CLOCK_EnableClock(kCLOCK_Gpio0); /* for button on P0_7 */
  GPIO_PortInit(GPIO, 0); /* Initialize GPIO button */
  CLOCK_EnableClock(kCLOCK_Gpio1); /* LEDs and user buttons, plus I2C */
  GPIO_PortInit(GPIO, 1); /* Initialize GPIO for LEDs and User Button */

  McuLib_Init();
  McuRTOS_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();

  LEDS_Init();
}
