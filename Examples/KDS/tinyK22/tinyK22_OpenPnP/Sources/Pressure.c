/*
 * Feeder.c
 *
 *  Created on: 19.04.2018
 *      Author: Erich Styger
 */

#include "CLS1.h"
#include "UTIL1.h"
#include "Pressure.h"

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"pressure", (unsigned char*)"Group of pressure sensor commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"pressure", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  tbd", (unsigned char*)"tbd\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t PRESSURE_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0 || UTIL1_strcmp((char*)cmd, "pressure help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "pressure status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  }
  return res;
}

void PRESSURE_Init(void) {
  /* nothing needed */
}
