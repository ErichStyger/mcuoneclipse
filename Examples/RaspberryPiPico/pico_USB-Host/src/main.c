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

#if !PL_CONFIG_USE_USB_HOST_MODE /* normal test mode */
int main(void) {
   PL_Init();
  vTaskStartScheduler();
#if PL_CONFIG_USE_GCOV
  McuCoverage_WriteFiles(); /* write coverage data files */
#endif /* PL_CONFIG_USE_GCOV */

  for(;;) {
    /* do not return from main() */
  }
  return 0;
}
#endif /* PL_CONFIG_USE_USB_HOST_MODE */
