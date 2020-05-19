/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#include "ini.h"
#include "MinINI.h"
#include "McuUtility.h"

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"ini", (unsigned char*)"Group of MinINI commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  read <f> <s> <k>", (const unsigned char*)"Read a key from a section in a file\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  write <f> <s> <k> <v>", (const unsigned char*)"Write a key with value to a section in a file \r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  //uint8_t buf[16];

  //McuShell_SendStatusStr((unsigned char*)"ini", (unsigned char*)"MinINI status\r\n", io->stdOut);
  //McuShell_SendStatusStr((unsigned char*)"  Version", (const unsigned char*)tskKERNEL_VERSION_NUMBER, io->stdOut);
  return ERR_OK;
}

uint8_t INI_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  unsigned char section[48], key[48], value[96], fileName[64];
  size_t lenRead;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "ini help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "ini status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, "ini read ", sizeof("ini read ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("ini read ")-1;
    if (McuUtility_ReadEscapedName(p, fileName, sizeof(fileName), NULL, NULL, NULL)!=ERR_OK) {
      return ERR_FAILED;
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "ini write ", sizeof("ini write ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("ini write ")-1;
    if (McuUtility_ReadEscapedName(p, fileName, sizeof(fileName), &lenRead, NULL, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    p += lenRead;
    McuUtility_SkipSpaces(&p);
    if (McuUtility_ReadEscapedName(p, section, sizeof(section), &lenRead, NULL, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    p += lenRead;
    McuUtility_SkipSpaces(&p);
    if (McuUtility_ReadEscapedName(p, key, sizeof(key), NULL, &lenRead, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    p += lenRead;
    McuUtility_SkipSpaces(&p);
    if (McuUtility_ReadEscapedName(p, value, sizeof(value), NULL, NULL, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    if (ini_puts((const TCHAR *)section, (const TCHAR *)key, (const TCHAR *)value, (const TCHAR *)fileName) == 0) {
      return ERR_FAILED;
    }
    return ERR_OK;
  }
  return ERR_OK;
}

