/*
 * Application.c
 *
 *  Created on: Nov 15, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#include "WAIT1.h"
#include "RStack.h"
#include "RApp.h"
#if PL_HAS_RSTDIO
#include "RStdIO.h"
#endif

static RNWK_ShortAddrType APP_srcAddr = RNWK_ADDR_BROADCAST; /* own node address */
static RNWK_ShortAddrType APP_dstAddr = RNWK_ADDR_BROADCAST; /* destination node address */

/* type ID's for application messages */
#define RAPP_MSG_TYPE_DATA    0x00
#define RAPP_MSG_TYPE_STDIN   0x01
#define RAPP_MSG_TYPE_STDOUT  0x02
#define RAPP_MSG_TYPE_STDERR  0x03

#if PL_HAS_RSTDIO
static uint8_t HandleStdioMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled) {
  (void)srcAddr;
  switch(type) {
    case RAPP_MSG_TYPE_STDIN: /* <type><size><data */
      *handled = TRUE;
      return RSTDIO_AddToQueue(RSTDIO_QUEUE_RX_IN, data, size);
    case RAPP_MSG_TYPE_STDOUT: /* <type><size><data */
      *handled = TRUE;
      return RSTDIO_AddToQueue(RSTDIO_QUEUE_RX_OUT, data, size);
    case RAPP_MSG_TYPE_STDERR: /* <type><size><data */
      *handled = TRUE;
      return RSTDIO_AddToQueue(RSTDIO_QUEUE_RX_ERR, data, size);
    default:
      break;
  } /* switch */
  return ERR_OK;
}
#endif

static const RAPP_MsgHandler handlerTable[] = 
{
#if PL_HAS_RSTDIO
  HandleStdioMessage,
#endif
  NULL /* sentinel */
};

void APP_Run(void) {
  uint8_t buf[RPHY_PAYLOAD_SIZE];
#if PL_HAS_RSTDIO
  CLS1_ConstStdIOTypePtr io = CLS1_GetStdio();
#endif
  
  RSTACK_Init(); /* initialize stack */
  RAPP_SetMessageHandlerTable(handlerTable); /* assign application message handler */
  (void)RAPP_SetOwnShortAddr(APP_srcAddr);
  for(;;) {
#if PL_HAS_RSTDIO
    RSTDIO_Print(io); /* handle stdout/stderr messages coming in */
#endif
    RAPP_BUF_PAYLOAD_START(buf)[0] = 32; /* sample 1 byte data */
    RAPP_PutPayload(buf, sizeof(buf), 1, RAPP_MSG_TYPE_DATA, APP_dstAddr); /* send one byte of data */
    WAIT1_Waitms(1000);
  }
}

#if PL_HAS_SHELL
static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  
  CLS1_SendStatusStr((unsigned char*)"app", (unsigned char*)"\r\n", io->stdOut);
  
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), APP_srcAddr);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  source addr", buf, io->stdOut);

  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), APP_dstAddr);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  dest addr", buf, io->stdOut);
  
  return ERR_OK;
}

static void PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"app", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help", (unsigned char*)"Shows radio help or status\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  saddr 0x<addr>", (unsigned char*)"Set node source address\r\n", io->stdOut);
#if PL_HAS_RSTDIO
  CLS1_SendHelpStr((unsigned char*)"  send (in/out/err)", (unsigned char*)"Send a string to stdio using the wireless transceiver\r\n", io->stdOut);
#endif
}

uint8_t RAPP_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  const uint8_t *p;
  uint16_t val16;

  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"app help")==0) {
    PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"app status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, (char*)"app saddr", sizeof("app saddr")-1)==0) {
    p = cmd + sizeof("app saddr")-1;
    *handled = TRUE;
    if (UTIL1_ScanHex16uNumber(&p, &val16)==ERR_OK) {
      APP_srcAddr = val16;
      RNWK_SetOwnShortAddr((RNWK_ShortAddrType)val16);
    } else {
      CLS1_SendStr((unsigned char*)"ERR: wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    }
#if PL_HAS_RSTDIO
    } else if (UTIL1_strncmp((char*)cmd, (char*)"app send", sizeof("app send")-1)==0) {
    unsigned char buf[32];
    RSTDIO_QueueType queue;
    
    if (UTIL1_strncmp((char*)cmd, (char*)"app send in", sizeof("app send in")-1)==0) {
      queue = RSTDIO_QUEUE_TX_IN;
      cmd += sizeof("app send in");
    } else if (UTIL1_strncmp((char*)cmd, (char*)"app send out", sizeof("app send out")-1)==0) {
      queue = RSTDIO_QUEUE_TX_OUT;      
      cmd += sizeof("app send out");
    } else if (UTIL1_strncmp((char*)cmd, (char*)"app send err", sizeof("app send err")-1)==0) {
      queue = RSTDIO_QUEUE_TX_ERR;      
      cmd += sizeof("app send err");
    } else {
      return ERR_OK; /* not handled */
    }
    UTIL1_strcpy(buf, sizeof(buf), cmd);
    UTIL1_chcat(buf, sizeof(buf), '\n');
    buf[sizeof(buf)-2] = '\n'; /* have a '\n' in any case */
    if (RSTDIO_SendToTxStdio(queue, buf, UTIL1_strlen((char*)buf))!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
    }
    *handled = TRUE;
#endif
  }
  return res;
}
#endif /* PL_HAS_SHELL */

