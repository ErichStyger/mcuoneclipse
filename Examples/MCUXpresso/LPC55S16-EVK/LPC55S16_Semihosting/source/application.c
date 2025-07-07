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
#include <stdio.h>

#if PL_CONFIG_USE_FILES
static int testFile(void) {
  FILE *file = NULL;

  /*
   * Creating a file without absolute path.
   * With J-Link and MCUXpresso IDE 11.4.1, this file gets created in the IDE installation directory (C:\NXP\MCUXpressoIDE_11.4.1_6260\ide).
   * Where the file gets created (current directory of the semihosting process on the host) really depends on the probe firmware and is non-standard.
   * See as well:
   * https://developer.arm.com/documentation/dui0058/d/semihosting/semihosting-swis/sys-open--0x01-?lang=en
   */
  file = fopen ("testFile.txt", "w"); /* on RP2040, file is present in project root folder. If using external gdb server: in the current directory of the GDB server */
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    fclose(file);
  } else {
    return 0; /* failed */
  }

  file = fopen ("c:\\tmp\\test.txt", "w");
  if (file!=NULL) {
    fputs("hello world with file I/O\r\n", file);
    (void)fwrite("hello\r\n", sizeof("hello\r\n")-1, 1, file);
    fclose(file);
    return 1; /* ok */
  }
  return 0; /* failed */
}
#endif

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
#if PL_CONFIG_USE_FILES
  testFile();
#endif
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
