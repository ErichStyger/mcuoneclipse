/*
 * LiDoReader.c
 *
 *  Created on: 03.03.2026
 *      Author: Erich Styger
 */

#include "platform.h"
#if PL_CONFIG_USE_LIDO_READER
#include "LiDoReader.h"
#include "McuShell.h"
#include "McuUtility.h"

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[32];

  McuShell_SendStatusStr((unsigned char*)"lido", (unsigned char*)"lido reader status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"lido", (unsigned char*)"Group of lido reader commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}


uint8_t LiDoReader_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "lido help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "lido status")==0)
            )
  {
    *handled = true;
    return PrintStatus(io);
  }
  return ERR_OK;
}

void LiDoReader_Init(void) {
}

#endif /* PL_CONFIG_USE_LIDO_READER */
