/**
 * \file
 * \brief This is the implementation for the Radio Application service part.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module provides application services of the network stack.
 */

#include "RNetConf.h"
#include "RApp.h"
#include "RNWK.h"
%if defined(Shell)
#include "%@Utility@'ModuleName'.h"
%endif

static const RAPP_MsgHandler *RAPP_MsgHandlerTable;

uint8_t RAPP_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RAPP_MSG_Type type, RNWK_ShortAddrType dstAddr, RPHY_FlagsType flags) {
  RAPP_BUF_TYPE(buf) = (uint8_t)type;
  RAPP_BUF_SIZE(buf) = payloadSize;
  return RNWK_PutPayload(buf, bufSize, payloadSize+RAPP_HEADER_SIZE, dstAddr, flags);
}

uint8_t RAPP_SendPayloadDataBlock(uint8_t *appPayload, uint8_t appPayloadSize, uint8_t msgType, RNWK_ShortAddrType dstAddr, RPHY_FlagsType flags) {
  uint8_t buf[RAPP_BUFFER_SIZE]; /* payload data buffer */
  int i;
  
  if (appPayloadSize>RAPP_PAYLOAD_SIZE) {
    return ERR_OVERFLOW; /* block too large for payload */
  }
  i = 0;
  while(i<appPayloadSize) {
    RAPP_BUF_PAYLOAD_START(buf)[i] = *appPayload;
    appPayload++; i++;
  }
  return RAPP_PutPayload(buf, sizeof(buf), appPayloadSize, msgType, dstAddr, flags);
}

uint8_t IterateTable(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet, const RAPP_MsgHandler *table) {
  uint8_t res = ERR_OK;

  if (table==NULL) { /* no table??? */
    return ERR_FAILED;
  }
  /* iterate through all parser functions in table */
  while(*table!=NULL) {
    if ((*table)(type, size, data, srcAddr, handled, packet)!=ERR_OK) {
      res = ERR_FAILED;
    }
    table++;
  }
  return res;
}

static uint8_t ParseMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, RPHY_PacketDesc *packet) {
  bool handled = FALSE;
  uint8_t res;
  
  res = IterateTable(type, size, data, srcAddr, &handled, packet, RAPP_MsgHandlerTable); /* iterate through all parser functions in table */
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
  
  type = RAPP_BUF_TYPE(packet->phyData);
  size = RAPP_BUF_SIZE(packet->phyData);
  data = RAPP_BUF_PAYLOAD_START(packet->phyData);
  srcAddr = RNWK_BUF_GET_SRC_ADDR(packet->phyData);
  return ParseMessage(type, size, data, srcAddr, packet);
}

uint8_t RAPP_SetMessageHandlerTable(const RAPP_MsgHandler *table) {
  RAPP_MsgHandlerTable = table;
  return ERR_OK;
}

RNWK_ShortAddrType RAPP_GetThisNodeAddr(void) {
  return RNWK_GetThisNodeAddr();
}

uint8_t RAPP_SetThisNodeAddr(RNWK_ShortAddrType addr) {
  return RNWK_SetThisNodeAddr(addr);
}

void RAPP_SniffPacket(RPHY_PacketDesc *packet, bool isTx) {
%if defined(Shell)
  uint8_t buf[32];
  const %@Shell@'ModuleName'%.StdIOType *io;
  int i;
  uint8_t dataSize;
  RNWK_ShortAddrType addr;
  
  io = %@Shell@'ModuleName'%.GetStdio();
  if (isTx) {
    %@Shell@'ModuleName'%.SendStr((unsigned char*)"Packet Tx ", io->stdOut);
  } else {
    %@Shell@'ModuleName'%.SendStr((unsigned char*)"Packet Rx ", io->stdOut);
  }
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)"flags: ");
  %@Utility@'ModuleName'%.strcatNum16s(buf, sizeof(buf), packet->flags);
  %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  if (packet->flags!=RPHY_PACKET_FLAGS_NONE) {
    %@Shell@'ModuleName'%.SendStr((unsigned char*)"(", io->stdOut);
    if (packet->flags&RPHY_PACKET_FLAGS_IS_ACK) {
      %@Shell@'ModuleName'%.SendStr((unsigned char*)"IS_ACK,", io->stdOut);
    }
    if (packet->flags&RPHY_PACKET_FLAGS_REQ_ACK) {
      %@Shell@'ModuleName'%.SendStr((unsigned char*)"REQ_ACK", io->stdOut);
    }
    %@Shell@'ModuleName'%.SendStr((unsigned char*)")", io->stdOut);
  }
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)" size: ");
  %@Utility@'ModuleName'%.strcatNum16s(buf, sizeof(buf), packet->phySize);
  %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  /* PHY */
  %@Shell@'ModuleName'%.SendStr((unsigned char*)" PHY data: ", io->stdOut);
  dataSize = RPHY_BUF_SIZE(packet->phyData);
  for(i=0; i<dataSize+RPHY_HEADER_SIZE;i++) {
    buf[0] = '\0';
    %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), packet->phyData[i]);
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" ");
    %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  }
  /* MAC */
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)" MAC size:");
  %@Utility@'ModuleName'%.strcatNum8u(buf, sizeof(buf), dataSize);
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" type:");
  %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), RMAC_BUF_TYPE(packet->phyData));
  %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  RMAC_DecodeType(buf, sizeof(buf), packet);
  %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)" s#:");
  %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), RMAC_BUF_SEQN(packet->phyData));
  %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  /* NWK */
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)" NWK src:");
  addr = RNWK_BUF_GET_SRC_ADDR(packet->phyData);
#if RNWK_SHORT_ADDR_SIZE==1
  %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), addr);
#else
  %@Utility@'ModuleName'%.strcatNum16Hex(buf, sizeof(buf), addr);
#endif
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" dst:");
  addr = RNWK_BUF_GET_DST_ADDR(packet->phyData);
#if RNWK_SHORT_ADDR_SIZE==1
  %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), addr);
#else
  %@Utility@'ModuleName'%.strcatNum16Hex(buf, sizeof(buf), addr);
#endif
  %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  /* APP */
  if (dataSize>RMAC_HEADER_SIZE+RNWK_HEADER_SIZE) { /* there is application data */
    %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)" APP type:");
    %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), RAPP_BUF_TYPE(packet->phyData));
    %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)" size:");
    %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), RAPP_BUF_SIZE(packet->phyData));
    %@Shell@'ModuleName'%.SendStr(buf, io->stdOut);
  }
  %@Shell@'ModuleName'%.SendStr((unsigned char*)"\r\n", io->stdOut);
%else
  (void)packet;
  (void)isTx;
%endif
}
void RAPP_Deinit(void) {
  /* nothing needed */
}

void RAPP_Init(void) {
  (void)RNWK_SetAppOnPacketRxCallback(RAPP_OnPacketRx);
  RAPP_MsgHandlerTable = NULL;
}
