/*
 * RNWK.c
 *
 *  Created on: Oct 10, 2013
 *      Author: tastyger
 */


#include "Platform.h"
#if PL_HAS_RADIO
#include "RPHY.h"
#include "RNWK.h"
#include "RMAC.h"

static RNWK_ShortAddrType RNWK_OwnShortAddr = RNWK_ADDR_BROADCAST;

static RNWK_AppOnRxCallbackType RNWK_AppOnRxCallback;

RNWK_ShortAddrType RNWK_GetOwnShortAddr(void) {
  return RNWK_OwnShortAddr;
}

void RNWK_SetOwnShortAddr(RNWK_ShortAddrType addr) {
  RNWK_OwnShortAddr = addr;
}

uint8_t RNWK_SetAppOnPacketRxCallback(RNWK_AppOnRxCallbackType callback) {
  RNWK_AppOnRxCallback = callback;
  return ERR_OK;
}

uint8_t RNWK_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RNWK_ShortAddrType dstAddr) {
  RNWK_ShortAddrType srcAddr;
  
  srcAddr = RNWK_GetOwnShortAddr();
  RNWK_BUF_SET_SRC_ADDR(buf, srcAddr);
  RNWK_BUF_SET_DST_ADDR(buf, dstAddr);
  return RMAC_PutPayload(buf, bufSize, payloadSize+RNWK_HEADER_SIZE);
}

uint8_t RNWK_OnPacketRx(RPHY_PacketDesc *packet) {
  RNWK_ShortAddrType addr;
  RMAC_MsgType type;
  uint8_t res;

  addr = RNWK_BUF_GET_DST_ADDR(packet->data);
  if (addr==RNWK_ADDR_BROADCAST || addr==RNWK_GetOwnShortAddr()) { /* it is for me :-) */
    type = RMAC_GetType(packet->data, packet->dataSize);
    if (type==RMAC_MSG_TYPE_ACK && RMAC_IsExpectedACK(packet->data, packet->dataSize)) {
      packet->flags |= RPHY_PACKET_FLAGS_ACK;
      return ERR_OK; /* no need to process the packet further */
    } else if (type==RMAC_MSG_TYPE_DATA) {
      if (RNWK_AppOnRxCallback!=NULL) {
        res = RNWK_AppOnRxCallback(packet);
        if (res==ERR_OK) { /* send acknowledge back */
          addr = RNWK_BUF_GET_SRC_ADDR(packet->data);
          RNWK_BUF_SET_DST_ADDR(packet->data, addr); /* destination address is from where we got the data */
          return RMAC_SendACK(packet);
        }
      }
    } else {
      return ERR_FAULT; /* wrong message type? */
    }
  }
  return ERR_FAILED;
}

#if PL_HAS_SHELL
static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"rnwk", (unsigned char*)"Group of rnwk commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows help or status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  
  CLS1_SendStatusStr((unsigned char*)"rnwk", (unsigned char*)"\r\n", io->stdOut);
  
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum16Hex(buf, sizeof(buf), RNWK_OwnShortAddr);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  addr", buf, io->stdOut);

  return ERR_OK;
}

uint8_t RNWK_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"rnwk help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"rnwk status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}
#endif /* PL_HAS_SHELL */

void RNWK_Deinit(void) {
  /* nothing needed */
}

void RNWK_Init(void) {
  RNWK_OwnShortAddr = RNWK_ADDR_BROADCAST;
  RNWK_AppOnRxCallback = NULL;
}

#endif /* PL_HAS_RADIO */
