/*
 * Feeder.c
 *
 *  Created on: 19.04.2018
 *      Author: Erich Styger
 */

#include "CLS1.h"
#include "UTIL1.h"

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"feeder", (unsigned char*)"Group of feeder commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"  feeder", (unsigned char*)"tbd\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t FEED_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io)
{
  uint8_t res = ERR_OK;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0 || UTIL1_strcmp((char*)cmd, "feeder help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "feeder status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
//  } else if (UTIL1_strcmp((char*)cmd, "feed reset") == 0) {
//    *handled = TRUE;
    //KIN1_SoftwareReset(); /* will perform RESET and does NOT return here! */
  }
  return res;
}


void FEED_Init(void) {

}
