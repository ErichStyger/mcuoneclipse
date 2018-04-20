/*
 * Feeder.c
 *
 *  Created on: 19.04.2018
 *      Author: Erich Styger
 */

#include "CLS1.h"
#include "UTIL1.h"
#include "Feeder.h"
#include "AS2.h" /* UART to feeder */

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"feeder", (unsigned char*)"Group of feeder commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"feeder", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  send <cmd>", (unsigned char*)"send command to the feeder with <addr>, supported commands:\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"", (unsigned char*)"CMD <addr> FWD        : one step forward\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"", (unsigned char*)"CMD <addr> REV        : one step backward\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"", (unsigned char*)"CMD <addr> STEP <n>mm : set feeder step (4 or 12mm)\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"", (unsigned char*)"STS <addr> OK         : ??????\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t FEED_SendCommand(const unsigned char *cmd, const CLS1_StdIOType *io) {
  uint8_t res;
  uint16_t snt;
  size_t len;

  len = UTIL1_strlen(cmd);
  res = AS2_SendBlock((char*)cmd, len, &snt);
  if (res!=ERR_OK || len!=snt) {
    CLS1_SendStr("Failed to send command to feeder: '", io->stdErr);
    CLS1_SendStr(cmd, io->stdErr);
    CLS1_SendStr("'\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* check response from Feeder. Possible responses are (with the address as the feeder number:
   * ERR -6 Invalid number format
   * ERR -6 Unknown command
   * ERR -6 Invalid Stepsize (n*2mm)
   */
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
  } else if (UTIL1_strncmp((char*)cmd, "feeder send ", sizeof("feeder send ")-1)==0) {
    *handled = TRUE;
    return FEED_SendCommand(cmd+sizeof("feeder send ")-1, io);
  }
  return res;
}

void FEED_Init(void) {
  /* nothing needed */
}
