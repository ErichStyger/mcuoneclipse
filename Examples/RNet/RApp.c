/*
 * RApp.c
 *
 *  Created on: Oct 11, 2013
 *      Author: tastyger
 */


#include "Platform.h"
#if PL_HAS_RADIO
#include "Radio.h"
#include "RApp.h"
#include "RNWK.h"
#include "RStdIO.h"

static const RAPP_MsgHandler *RAPP_MsgHandlerTable;

uint8_t RAPP_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RAPP_MSG_Type type, RNWK_ShortAddrType dstAddr) {
  RAPP_BUF_TYPE(buf) = (uint8_t)type;
  RAPP_BUF_SIZE(buf) = payloadSize;
  return RNWK_PutPayload(buf, bufSize, payloadSize+RAPP_HEADER_SIZE, dstAddr);
}

uint8_t IterateTable(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, const RAPP_MsgHandler *table) {
  uint8_t res = ERR_OK;

  if (table==NULL) { /* no table??? */
    return ERR_FAILED;
  }
  /* iterate through all parser functions in table */
  while(*table!=NULL) {
    if ((*table)(type, size, data, srcAddr, handled)!=ERR_OK) {
      res = ERR_FAILED;
    }
    table++;
  }
  return res;
}

static uint8_t ParseMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr) {
  bool handled = FALSE;
  uint8_t res;
  
  res = IterateTable(type, size, data, srcAddr, &handled, RAPP_MsgHandlerTable); /* iterate through all parser functions in table */
  if (!handled || res!=ERR_OK) { /* no handler has handled the command? */
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t RAPP_OnPacketRx(RPHY_PacketDesc *packet) {
  uint8_t size;
  uint8_t *data;
  RAPP_MSG_Type type;
  RNWK_ShortAddrType srcAddr;
  
  type = RAPP_BUF_TYPE(packet->data);
  size = RAPP_BUF_SIZE(packet->data);
  data = RAPP_BUF_PAYLOAD_START(packet->data);
  srcAddr = RNWK_BUF_GET_SRC_ADDR(packet->data);
  return ParseMessage(type, size, data, srcAddr);
}

uint8_t RAPP_SetMessageHandlerTable(const RAPP_MsgHandler *table) {
  RAPP_MsgHandlerTable = table;
  return ERR_OK;
}

RNWK_ShortAddrType RAPP_GetOwnShortAddr(void) {
  return RNWK_GetOwnShortAddr();
}

uint8_t RAPP_SetOwnShortAddr(RNWK_ShortAddrType addr) {
  return RNWK_SetOwnShortAddr(addr);
}


void RAPP_Deinit(void) {
  /* nothing needed */
}

void RAPP_Init(void) {
  (void)RNWK_SetAppOnPacketRxCallback(RAPP_OnPacketRx);
  RAPP_MsgHandlerTable = NULL;
}

#endif /* PL_HAS_RADIO */
