/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuRTOS.h"

uint8_t APP_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  return ERR_OK;
}

void APP_Run(void) {
  PL_Init();
  vTaskStartScheduler();
  for(;;) { /* should not get here */ }
}
