/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "McuRTOS.h"
#include "McuWait.h"
#include <stdio.h>
#if PL_CONFIG_USE_GCOV
  #include "McuCoverage.h"
#endif
#include "usbHost.h"

int main(void) {
   PL_Init();
   UsbHost_Init();
 #if 0
  McuWait_Waitms(1000);
  UsbHost_PowerEnable(true);
  McuWait_Waitms(5000);
  UsbHost_PowerEnable(false);
#endif
  vTaskStartScheduler();
#if PL_CONFIG_USE_GCOV
  McuCoverage_WriteFiles(); /* write coverage data files */
#endif /* PL_CONFIG_USE_GCOV */

  for(;;) {
    /* do not return from main() */
  }
  return 0;
}
