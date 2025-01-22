/**
 * \file
 * \brief This is main application file
 * \author (c) 2016 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * This module implements the application part of the program.
 */

#include "RNet/McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED
#include "platform.h"
#if PL_HAS_RADIO
#include "RNet_App.h"
#include "application.h"
#include "RNet/Radio.h"
#include "RNet/RStack.h"
#include "RNet/RApp.h"
#include "McuRTOS.h"
#include "McuLog.h"
#include "RNet/RPHY.h"
#if RNET_CONFIG_REMOTE_STDIO
  #include "RNet/RStdIO.h"
#endif
#if PL_HAS_REMOTE
  #include "Remote.h"
#endif
#if PL_HAS_MINT
  #include "MintRobot.h"
#endif
#if PL_CONFIG_HAS_LCD
  #include "LCD.h"
#endif
#include "shell.h"
#if PL_HAS_MINT_REMOTE
  #include "MintRemote.h"
#endif
#if PL_CONFIG_USE_LEDS
  #include "leds.h"
  #include "McuLED.h"
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "McuSystemView.h"
#endif

static RNWK_ShortAddrType APP_dstAddr = RNWK_ADDR_BROADCAST; /* destination node address */

RNWK_ShortAddrType RNETA_GetDestAddr(void) {
  return APP_dstAddr;
}

uint8_t RNETA_SendIdValuePairMessage(uint8_t msgType, uint16_t id, uint32_t value, RAPP_ShortAddrType addr, RAPP_FlagsType flags) {
  uint8_t dataBuf[6]; /* 2 byte ID followed by 4 byte data */

  if (msgType==RAPP_MSG_TYPE_QUERY_VALUE) { /* only sending query with the ID, no value needed */
    McuUtility_SetValue16LE(id, &dataBuf[0]);
    return RAPP_SendPayloadDataBlock(dataBuf, sizeof(id), msgType, addr, flags);
  } else {
    McuUtility_SetValue16LE(id, &dataBuf[0]);
    McuUtility_SetValue32LE(value, &dataBuf[2]);
    return RAPP_SendPayloadDataBlock(dataBuf, sizeof(dataBuf), msgType, addr, flags);
  }
}

static uint8_t HandleDataRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
  uint8_t val;
  
  (void)size;
  (void)packet;
  switch(type) {
    case RAPP_MSG_TYPE_DATA: /* generic data message */
      *handled = TRUE;
      val = *data; /* get data value */
      McuLog_info("Data %d from addr 0x%x", val, srcAddr);
      return ERR_OK;
    default:
      break;
  } /* switch */
  return ERR_OK;
}

static const RAPP_MsgHandler handlerTable[] = 
{
#if RNET_CONFIG_REMOTE_STDIO
  RSTDIO_HandleStdioRxMessage,
#endif
#if PL_HAS_REMOTE
  REMOTE_HandleRemoteRxMessage,
#endif
#if PL_HAS_MINT
  MINT_HandleRemoteRxMessage,
#endif
#if PL_CONFIG_HAS_LCD
  LCD_HandleRemoteRxMessage,
#endif
  HandleDataRxMessage,
#if PL_HAS_MINT_REMOTE
  MINTREMOTE_HandleRemoteRxMessage,
#endif
  NULL /* sentinel */
};

static void Init(void) {
  if (RAPP_SetThisNodeAddr(RNWK_ADDR_BROADCAST)!=ERR_OK) { /* set a default address */
    McuLog_fatal("Failed setting node address");
  }
}

void RNETA_Deinit(void) {
  McuRNet_Deinit();
}

void RNETA_Init(void) {
  Init();
  McuRNet_Init(); /* initialize stack */
  if (RAPP_SetMessageHandlerTable(handlerTable)!=ERR_OK) { /* assign application message handler */
    McuLog_fatal("failed setting message handler!");
  }
}

#if PL_CONFIG_USE_SHELL
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];
  
  McuShell_SendStatusStr((unsigned char*)"rapp", (unsigned char*)"Remote App RF status\r\n", io->stdOut);
  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
#if RNWK_SHORT_ADDR_SIZE==1
  McuUtility_strcatNum8Hex(buf, sizeof(buf), APP_dstAddr);
#else
  McuUtility_strcatNum16Hex(buf, sizeof(buf), APP_dstAddr);
#endif
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  dest addr", buf, io->stdOut);
  
  return ERR_OK;
}

static void PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"rapp", (unsigned char*)"Group of application commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows rapp help or status\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  saddr 0x<addr>", (unsigned char*)"Set source node address\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  daddr 0x<addr>", (unsigned char*)"Set destination node address\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  send val <val>", (unsigned char*)"Send a value to the destination node\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  nsend val <val>", (unsigned char*)"Send a value to the destination node, with no_ack\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set <id> <val>", (unsigned char*)"Send request to set value for an ID\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  notify <id> <val>", (unsigned char*)"Send notification value for an ID\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  query <id>", (unsigned char*)"Send a query for an ID\r\n", io->stdOut);
#if RNET_CONFIG_REMOTE_STDIO
  McuShell_SendHelpStr((unsigned char*)"  send (in/out/err)", (unsigned char*)"Send a string to stdio using the wireless transceiver\r\n", io->stdOut);
#endif
}

uint8_t RNETA_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;
  const uint8_t *p;
  uint16_t val16;
  uint8_t val8;

  if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, (char*)"rapp help")==0) {
    *handled = TRUE;
    PrintHelp(io);
  } else if (McuUtility_strcmp((char*)cmd, (char*)McuShell_CMD_STATUS)==0 || McuUtility_strcmp((char*)cmd, (char*)"rapp status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp saddr", sizeof("rapp saddr")-1)==0) {
    p = cmd + sizeof("rapp saddr")-1;
    *handled = TRUE;
    if (McuUtility_ScanHex16uNumber(&p, &val16)==ERR_OK) {
      (void)RNWK_SetThisNodeAddr((RNWK_ShortAddrType)val16);
    } else {
      McuShell_SendStr((unsigned char*)"ERR: wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp send val", sizeof("rapp send val")-1)==0) {
    p = cmd + sizeof("rapp send val")-1;
    *handled = TRUE;
    if (McuUtility_ScanDecimal8uNumber(&p, &val8)==ERR_OK) {
      (void)RAPP_SendPayloadDataBlock(&val8, sizeof(val8), (uint8_t)RAPP_MSG_TYPE_DATA, APP_dstAddr, RPHY_PACKET_FLAGS_NONE); /* only send low byte */
    } else {
      McuShell_SendStr((unsigned char*)"ERR: wrong number format\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp nsend val", sizeof("rapp nsend val")-1)==0) {
    p = cmd + sizeof("rapp nsend val")-1;
    *handled = TRUE;
    if (McuUtility_ScanDecimal8uNumber(&p, &val8)==ERR_OK) {
      (void)RAPP_SendPayloadDataBlock(&val8, sizeof(val8), (uint8_t)RAPP_MSG_TYPE_DATA, APP_dstAddr, RPHY_PACKET_FLAGS_NO_ACK); /* only send low byte */
    } else {
      McuShell_SendStr((unsigned char*)"ERR: wrong number format\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp notify ", sizeof("rapp notify ")-1)==0) {
    uint32_t val32u;

    p = cmd + sizeof("rapp notify ")-1;
    *handled = TRUE;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16)==ERR_OK && McuUtility_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_NOTIFY_VALUE, val16, val32u, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
    } else {
      McuShell_SendStr((unsigned char*)"ERR: wrong id format\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp set ", sizeof("rapp set ")-1)==0) {
    uint32_t val32u;

    p = cmd + sizeof("rapp set ")-1;
    *handled = TRUE;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16)==ERR_OK && McuUtility_ScanDecimal32uNumber(&p, &val32u)==ERR_OK) {
      RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_REQUEST_SET_VALUE, val16, val32u, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
    } else {
      McuShell_SendStr((unsigned char*)"ERR: wrong id format\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp query ", sizeof("rapp query ")-1)==0) {
    p = cmd + sizeof("rapp query ")-1;
    *handled = TRUE;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16)==ERR_OK) {
      RNETA_SendIdValuePairMessage(RAPP_MSG_TYPE_QUERY_VALUE, val16, 0, RNETA_GetDestAddr(), RPHY_PACKET_FLAGS_NONE);
    } else {
      McuShell_SendStr((unsigned char*)"ERR: wrong id format\r\n", io->stdErr);
      return ERR_FAILED;
    }
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp daddr", sizeof("rapp daddr")-1)==0) {
    p = cmd + sizeof("rapp daddr")-1;
    *handled = TRUE;
    if (McuUtility_ScanHex16uNumber(&p, &val16)==ERR_OK) {
      APP_dstAddr = val16;
    } else {
      McuShell_SendStr((unsigned char*)"ERR: wrong address\r\n", io->stdErr);
      return ERR_FAILED;
    }
#if RNET_CONFIG_REMOTE_STDIO
  } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp send", sizeof("rapp send")-1)==0) {
    unsigned char buf[32];
    RSTDIO_QueueType queue;
    
    if (McuUtility_strncmp((char*)cmd, (char*)"rapp send in", sizeof("rapp send in")-1)==0) {
      queue = RSTDIO_QUEUE_TX_IN;
      cmd += sizeof("rapp send in");
    } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp send out", sizeof("rapp send out")-1)==0) {
      queue = RSTDIO_QUEUE_TX_OUT;      
      cmd += sizeof("rapp send out");
    } else if (McuUtility_strncmp((char*)cmd, (char*)"rapp send err", sizeof("rapp send err")-1)==0) {
      queue = RSTDIO_QUEUE_TX_ERR;      
      cmd += sizeof("rapp send err");
    } else {
      return ERR_OK; /* not handled */
    }
    McuUtility_strcpy(buf, sizeof(buf), cmd);
    McuUtility_chcat(buf, sizeof(buf), '\n');
    buf[sizeof(buf)-2] = '\n'; /* have a '\n' in any case */
    if (RSTDIO_SendToTxStdio(queue, buf, McuUtility_strlen((char*)buf))!=ERR_OK) {
      McuShell_SendStr((unsigned char*)"failed!\r\n", io->stdErr);
    }
    *handled = TRUE;
#endif
  }
  return res;
}
#endif /* PL_CONFIG_USE_SHELL */

#endif /* McuRNET_CONFIG_IS_ENABLED */

#endif /* PL_HAS_RADIO */
