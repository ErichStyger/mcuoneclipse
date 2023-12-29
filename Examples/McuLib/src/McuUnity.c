/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#include "McuRTT.h"
#include "McuLog.h"
#if McuLib_CONFIG_CPU_IS_RPxxxx
  #include "pico/platform.h"
#endif

/* The variable below is not initialized during statup, and set by JRun using a test JLinkScript,
 * writing the variable during HandleAfterFlashProg().
 */
#if McuLib_CONFIG_CPU_IS_RPxxxx
  static uint32_t __uninitialized_ram(program_arg);
#else /* put variable into a no-init section */
  uint32_t program_arg __attribute__((section (".uninit_RESERVED")));
#endif

uint32_t McuUnity_GetArgument(void) {
  McuLog_info("program_arg: value 0x%x @0x%x", program_arg, &program_arg);
  return program_arg;
}

void setUp(void) {
  /* run before each test*/
}

void tearDown(void) { 
  /* run after each test */
}

void McuUnity_putc(int c) {
  McuRTT_StdIOSendChar(c); /* using JRun with RTT */
}

void McuUnity_flush(void) {
  /* used to flush the communication channel */
}

void McuUnity_start(void) {
  /* used to open/start the communicatino channel */
}

void McuUnity_complete(void) {
  /* used to close/stop the communication channel */
}
