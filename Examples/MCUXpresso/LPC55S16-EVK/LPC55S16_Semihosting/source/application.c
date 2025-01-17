/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "McuSemihost.h"
#include "McuShell.h"
#include "McuArmTools.h"

#if PL_CONFIG_USE_SHELL
static const McuShell_ParseCommandCallback CmdParserTable[] =
{
  McuShell_ParseCommand,
  McuArmTools_ParseCommand,
  NULL /* Sentinel */
};
#endif

void APP_Run(void) {
  PL_Init(); /* init modules */
#if PL_CONFIG_USE_SHELL
  McuSemihost_DefaultShellBuffer[0] = '\0';
  McuSemihost_WriteString0((unsigned char*)McuShell_CONFIG_PROMPT_STRING);
  for(;;) {
    int i = McuSemihost_ReadLine(McuSemihost_DefaultShellBuffer, sizeof(McuSemihost_DefaultShellBuffer), true);
    if (i>1 && (McuSemihost_DefaultShellBuffer[i-1]=='\r' || McuSemihost_DefaultShellBuffer[i-1]=='\n')) {
      McuSemihost_DefaultShellBuffer[i-1] = '\0'; /* remove line end character */
      (void)McuShell_ParseWithCommandTableExt(McuSemihost_DefaultShellBuffer, &McuSemihost_stdio, CmdParserTable, true);
      McuSemihost_WriteString0((unsigned char*)McuShell_CONFIG_PROMPT_STRING);
    }
  }
#else
  McuSemihost_WriteString((unsigned char*)"hello world with semihosting!\n");
  for(;;) {
	  unsigned char buf[16];
	  int i;

	  McuSemihost_WriteString((unsigned char*)"Please type some text and press <ENTER>:\n");
	  i = McuSemihost_ReadLine(buf, sizeof(buf));
	  McuSemihost_printf("You entered %d characters: %s\n", i, buf);
  }
#endif
}
