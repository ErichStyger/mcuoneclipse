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
  McuShell_SendHelpStr((unsigned char*)"  write <f> <s> <k> <v>", (const unsigned char*)"Write a key with value to a section in a file\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  delkey <f> <s> <k>", (const unsigned char*)"Delete a key in a section of file\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  delsec <f> <s>", (const unsigned char*)"Delete a section in a file\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[16];

  McuShell_SendStatusStr((unsigned char*)"ini", (unsigned char*)"MinINI status\r\n", io->stdOut);
  McuUtility_Num32uToStr(buf, sizeof(buf), INI_BUFFERSIZE);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" bytes\r\n");
  McuShell_SendStatusStr((unsigned char*)"  buffer", buf, io->stdOut);

#if defined(INI_REAL)
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"supported\r\n");
#else
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"not supported\r\n");
#endif
  McuShell_SendStatusStr((unsigned char*)"  real", buf, io->stdOut);

#if defined(INI_READONLY)
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"read-only\r\n");
#else
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"read-write\r\n");
#endif
  McuShell_SendStatusStr((unsigned char*)"  mode", buf, io->stdOut);

  switch(McuMinINI_CONFIG_FS) {
    case McuMinINI_CONFIG_FS_TYPE_GENERIC:
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"Generic\r\n"); break;
    case McuMinINI_CONFIG_FS_TYPE_TINY_FS:
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"TinyFS\r\n"); break;
    case McuMinINI_CONFIG_FS_TYPE_FAT_FS:
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FatFS\r\n"); break;
    default:
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"ERROR\r\n"); break;
    }
  McuShell_SendStatusStr((unsigned char*)"  FS", buf, io->stdOut);
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
    if (*p != '\0') { /* still some arguments? */
      return ERR_FAILED;
    }
    if (ini_gets((const TCHAR *)section, (const TCHAR *)key, (const TCHAR *)"", (TCHAR *)value, sizeof(value), (const TCHAR *)fileName) == 0) {
      return ERR_FAILED;
    }
    McuShell_SendStr(key, io->stdOut);
    McuShell_SendStr((unsigned char*)"=", io->stdOut);
    McuShell_SendStr(value, io->stdOut);
    McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
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
    if (McuUtility_ReadEscapedName(p, value, sizeof(value), &lenRead, NULL, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    p += lenRead;
    if (*p != '\0') { /* still some arguments? */
      return ERR_FAILED;
    }
    if (ini_puts((const TCHAR *)section, (const TCHAR *)key, (const TCHAR *)value, (const TCHAR *)fileName) == 0) {
      return ERR_FAILED;
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "ini delkey ", sizeof("ini delkey ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("ini delkey ")-1;
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
    if (McuUtility_ReadEscapedName(p, key, sizeof(key), &lenRead, NULL, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    p += lenRead;
    if (*p != '\0') { /* still some arguments? */
      return ERR_FAILED;
    }
    if (ini_puts((const TCHAR *)section, (const TCHAR *)key, NULL, (const TCHAR *)fileName) == 0) {
      return ERR_FAILED;
    }
    return ERR_OK;
  } else if (McuUtility_strncmp((char*)cmd, "ini delsec ", sizeof("ini delsec ")-1)==0) {
    *handled = TRUE;
    p = cmd + sizeof("ini delsec ")-1;
    if (McuUtility_ReadEscapedName(p, fileName, sizeof(fileName), &lenRead, NULL, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    p += lenRead;
    McuUtility_SkipSpaces(&p);
    if (McuUtility_ReadEscapedName(p, section, sizeof(section), &lenRead, NULL, NULL)!=ERR_OK || lenRead==0) {
      return ERR_FAILED;
    }
    p += lenRead;
    if (*p != '\0') { /* still some arguments? */
      return ERR_FAILED;
    }
    if (ini_puts((const TCHAR *)section, NULL, NULL, (const TCHAR *)fileName) == 0) {
      return ERR_FAILED;
    }
    return ERR_OK;
  }
  return ERR_OK;
}

