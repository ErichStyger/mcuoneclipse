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
  CLS1_SendHelpStr((unsigned char*)"  send <cmd>", (unsigned char*)"send command to the feeder with <addr>, supported commands:\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"CMD <addr> FWD          : one step forward\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"CMD <addr> REV          : one step backward\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"CMD <addr> CNT          : used to count the number of feeders\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"CMD <addr> SET STEP <n> : set feeder step (mm) (4 or 12)\r\n", io->stdOut);
//  CLS1_SendHelpStr((unsigned char*)"", (unsigned char*)"CMD <addr> STS          : get status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  CLS1_SendStatusStr((unsigned char*)"feeder", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  tbd", (unsigned char*)"tbd\r\n", io->stdOut);
  return ERR_OK;
}

typedef struct {
  unsigned char cmd[sizeof("CMD")];
  int32_t id; /* device ID/address */
  unsigned char op[sizeof("SET STEP 12")];
  unsigned char reply[64]; /* response string */
} FEED_CmdDesc;

static uint8_t ParseCommand(const unsigned char *cmd, FEED_CmdDesc *command) {
  uint8_t res;
  const unsigned char *p;

  /* init descriptor */
  command->cmd[0] = '\0';
  command->id = 0;
  command->op[0] = '\0';
  command->reply[0] = '\0';
  if (UTIL1_strncmp(cmd, "CMD ", sizeof("CMD ")-1)!=0) {
    /* no match, store it as error string */
    UTIL1_strcpy(command->reply, sizeof(command->reply), cmd);
    return ERR_OK;
  } else {
    UTIL1_strcpy(command->cmd, sizeof(command->cmd), "CMD");
   }
  p = cmd+sizeof("CMD ")-1;
  res = UTIL1_xatoi(&p, &command->id);
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  if (UTIL1_strncmp(p, " FWD", sizeof(" FWD")-1)==0) {
    UTIL1_strcpy(command->op, sizeof(command->op), "FWD");
    p += sizeof(" FWD")-1;
  } else if (UTIL1_strncmp(p, " REV", sizeof(" REV")-1)==0) {
    UTIL1_strcpy(command->op, sizeof(command->op), "REV");
    p += sizeof(" REV")-1;
  } else if (UTIL1_strncmp(p, " CNT", sizeof(" CNT")-1)==0) {
    UTIL1_strcpy(command->op, sizeof(command->op), "CNT");
    p += sizeof(" CNT")-1;
  } else if (UTIL1_strncmp(p, " SET STEP ", sizeof(" SET STEP ")-1)==0) {
    int32_t num;

    UTIL1_strcpy(command->op, sizeof(command->op), "SET STEP ");
    p += sizeof(" SET STEP ")-1;
    res = UTIL1_xatoi(&p, &num); /* parse number... */
    if (res!=ERR_OK) {
      return ERR_FAILED;
    }
    UTIL1_strcatNum32s(command->op, sizeof(command->op), num); /* ... and add it again */
  }
  if (*p==' ') {
    p++; /* skip space */
  }
  UTIL1_strcpy(command->reply, sizeof(command->reply), p); /* copy rest of message */
  return ERR_OK;
}

static uint8_t FEED_SendCommand(const unsigned char *cmd, const CLS1_StdIOType *io) {
  uint8_t res;
  uint16_t snt;
  size_t len;
  static unsigned char recvBuf[64];
  static FEED_CmdDesc txCommand, rxCommand;
  char ch;
  int timeoutMs = 1000;

  res = ParseCommand(cmd, &txCommand);
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed parsing TX command: '", io->stdErr);
    CLS1_SendStr(cmd, io->stdErr);
    CLS1_SendStr("'\r\n", io->stdErr);
    return ERR_FAILED;
  }
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
  recvBuf[0] = '\0';
  for(;;) { /* breaks */
    ch = '\0';
    res = AS2_RecvChar(&ch);
    if (res==ERR_RXEMPTY) {
      vTaskDelay(pdMS_TO_TICKS(10));
      timeoutMs -= 10;
      if (timeoutMs<=0) { /* timeout! */
        break;
      }
    } else { /* received character */
      UTIL1_chcat(recvBuf, sizeof(recvBuf), ch);
      if (ch=='\n') { /* end of transmission */
        break;
      }
    }
  }
#if 0 /* \todo disabled for now */
  if (timeoutMs<=0) {
    CLS1_SendStr("TIMEOUT, failed get response from feeder: '", io->stdErr);
    CLS1_SendStr(cmd, io->stdErr);
    CLS1_SendStr("', received: '", io->stdErr);
    CLS1_SendStr(recvBuf, io->stdErr);
    CLS1_SendStr("'\r\n", io->stdErr);
    return ERR_FAILED;
  }
#else
  /* dummy response for testing only */
  UTIL1_strcpy(recvBuf, sizeof(recvBuf), "CMD -3 FWD ok");
#endif
  res = ParseCommand(recvBuf, &rxCommand);
  if (res!=ERR_OK) {
    CLS1_SendStr("Failed parsing RX command: '", io->stdErr);
    CLS1_SendStr(recvBuf, io->stdErr);
    CLS1_SendStr("'\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* \todo handle 'ok' response or 'error' response' */
  /* Check if we received the same command back.
   * Errors would be appended in front of the response
   */
  if (   UTIL1_strcmp(txCommand.cmd, rxCommand.cmd)==0 /* same command */
      && UTIL1_strcmp(txCommand.op, rxCommand.op)==0 /* same op */
      && UTIL1_strcmp(rxCommand.reply, "ok")==0 /* reply was 'ok' */
     )
  {
    /* here everything was working fine. Print 'ok' message so it can be parsed by OpenPnP Regular Expression */
    CLS1_SendStr("ok\r\nok\r\nok\r\n", io->stdOut);
    return ERR_OK;
  }
  /* here we are in an error case: the response is not what we expected. So we throw an error */
  CLS1_SendStr("not expected response from feeder: '", io->stdErr);
  CLS1_SendStr(recvBuf, io->stdErr);
  CLS1_SendStr("'\r\n", io->stdErr);
  return ERR_FAILED;
}

uint8_t FEED_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io)
{
  uint8_t res = ERR_OK;

  /* from OpenPnP the following commands are sent:
   * 'Feed'      => M800
   * 'Post Pick' => M801
   */
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
