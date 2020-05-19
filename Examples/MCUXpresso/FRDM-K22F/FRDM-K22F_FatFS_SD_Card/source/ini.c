/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "ini.h"
#include "McuUtility.h"

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"ini", (unsigned char*)"Group of MinINI commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  //uint8_t buf[16];

  //McuShell_SendStatusStr((unsigned char*)"ini", (unsigned char*)"MinINI status\r\n", io->stdOut);
  //McuShell_SendStatusStr((unsigned char*)"  Version", (const unsigned char*)tskKERNEL_VERSION_NUMBER, io->stdOut);
  return ERR_OK;
}

uint8_t INI_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "ini help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "ini status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
//  } else if (McuUtility_strcmp((char*)cmd, "ini ")==0) {
//    *handled = TRUE;
//    return PrintTaskList(io);
  }
  return ERR_OK;
}

