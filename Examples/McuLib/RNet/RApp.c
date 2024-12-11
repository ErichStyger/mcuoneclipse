/**
 * \file
 * \brief This is the implementation for the Radio Application service part.
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module provides application services of the network stack.
 */

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED
#include "RApp.h"
#include "RNWK.h"
#include "McuUtility.h"
#include "McuLog.h"

static const RAPP_MsgHandler *RAPP_MsgHandlerTable;

uint8_t RAPP_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RAPP_MSG_Type type, RAPP_ShortAddrType dstAddr, RAPP_FlagsType flags) {
  RAPP_BUF_TYPE(buf) = (uint8_t)type;
  RAPP_BUF_SIZE(buf) = payloadSize;
  return RNWK_PutPayload(buf, bufSize, payloadSize+RAPP_HEADER_SIZE, dstAddr, flags);
}

uint8_t RAPP_SendPayloadDataBlock(uint8_t *appPayload, uint8_t appPayloadSize, uint8_t msgType, RAPP_ShortAddrType dstAddr, RAPP_FlagsType flags) {
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
  return RAPP_PutPayload(buf, sizeof(buf), appPayloadSize, (RAPP_MSG_Type)msgType, dstAddr, flags);
}

static uint8_t IterateTable(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RAPP_ShortAddrType srcAddr, bool *handled, RAPP_PacketDesc *packet, const RAPP_MsgHandler *table) {
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

static uint8_t ParseMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RAPP_ShortAddrType srcAddr, RAPP_PacketDesc *packet) {
  bool handled = FALSE;
  uint8_t res;
  
  res = IterateTable(type, size, data, srcAddr, &handled, packet, RAPP_MsgHandlerTable); /* iterate through all parser functions in table */
  if (!handled || res!=ERR_OK) { /* no handler has handled the command? */
    res = ERR_FAILED;
  }
  return res;
}

static uint8_t RAPP_OnPacketRx(RAPP_PacketDesc *packet) {
  uint8_t size;
  uint8_t *data;
  RAPP_MSG_Type type;
  RAPP_ShortAddrType srcAddr;
  
  type = (RAPP_MSG_Type)RAPP_BUF_TYPE(packet->phyData);
  size = RAPP_BUF_SIZE(packet->phyData);
  data = RAPP_BUF_PAYLOAD_START(packet->phyData);
  srcAddr = RNWK_BUF_GET_SRC_ADDR(packet->phyData);
  return ParseMessage(type, size, data, srcAddr, packet);
}

uint8_t RAPP_SetMessageHandlerTable(const RAPP_MsgHandler *table) {
  RAPP_MsgHandlerTable = table;
  return ERR_OK;
}

RAPP_ShortAddrType RAPP_GetThisNodeAddr(void) {
  return RNWK_GetThisNodeAddr();
}

uint8_t RAPP_SetThisNodeAddr(RAPP_ShortAddrType addr) {
  return RNWK_SetThisNodeAddr(addr);
}

void RAPP_SniffPacket(RAPP_PacketDesc *packet, bool isTx) {
  int i;
  uint8_t dataSize;
  unsigned char flagsBuf[32];
  unsigned char phyBuf[96];
  unsigned char macBuf[32];

  if (packet->flags!=RPHY_PACKET_FLAGS_NONE) {
    flagsBuf[0] = '\0';
    if (packet->flags&RPHY_PACKET_FLAGS_IS_ACK) {
      McuUtility_strcat(flagsBuf, sizeof(flagsBuf), (unsigned char*)" IS_ACK");
    }
    if (packet->flags&RPHY_PACKET_FLAGS_REQ_ACK) {
      McuUtility_strcat(flagsBuf, sizeof(flagsBuf), (unsigned char*)" REQ_ACK");
    }
    if (packet->flags&RPHY_PACKET_FLAGS_NO_ACK) {
      McuUtility_strcat(flagsBuf, sizeof(flagsBuf), (unsigned char*)" NO_ACK");
    }
    if (packet->flags&RPHY_PACKET_FLAGS_POWER_DOWN) {
      McuUtility_strcat(flagsBuf, sizeof(flagsBuf), (unsigned char*)" POWER_DOWN");
    }
  } else {
    McuUtility_strcpy(flagsBuf, sizeof(flagsBuf), (unsigned char*)" ");
  }

  /* PHY */
  phyBuf[0] = '\0';
  dataSize = RPHY_BUF_SIZE(packet->phyData);
  for(i=0; i<dataSize+RPHY_HEADER_SIZE;i++) {
    McuUtility_strcatNum8Hex(phyBuf, sizeof(phyBuf), packet->phyData[i]);
    McuUtility_chcat(phyBuf, sizeof(phyBuf), ' ');
  }

  /* MAC */
  RMAC_DecodeType(macBuf, sizeof(macBuf), packet);

  McuLog_trace("%s:flags:%02x%s size:%02x PHY: %sMAC: type:%02x%s, s#:%02x NWK: src:%02x dst:%02x",
    isTx?"Tx":"Rx",
    packet->flags,
    flagsBuf,
    packet->phySize,
    /* PHY */
    phyBuf,
    /* MAC */
    RMAC_BUF_TYPE(packet->phyData),
    macBuf,
    RMAC_BUF_SEQN(packet->phyData),
    /* NWK */
    RNWK_BUF_GET_SRC_ADDR(packet->phyData),
    RNWK_BUF_GET_DST_ADDR(packet->phyData)
  );

  /* APP */
  if (dataSize>RMAC_HEADER_SIZE+RNWK_HEADER_SIZE) { /* there is application data */
    unsigned char appBuf[32];

    dataSize = RAPP_BUF_SIZE(packet->phyData);
    uint8_t *app_data = RAPP_BUF_PAYLOAD_START(packet->phyData);
    appBuf[0] = '\0';
    for(i=0; i<dataSize;i++) {
      McuUtility_strcatNum8Hex(appBuf, sizeof(appBuf), app_data[i]);
      McuUtility_strcat(appBuf, sizeof(appBuf), (unsigned char*)" ");
    }
    McuLog_trace("APP: type:%02x size:%02x data:%s",
      /* APP */
      RAPP_BUF_TYPE(packet->phyData),
      RAPP_BUF_SIZE(packet->phyData),
      appBuf
    );
  }
}

void RAPP_Deinit(void) {
  /* nothing needed */
}

void RAPP_Init(void) {
  (void)RNWK_SetAppOnPacketRxCallback(RAPP_OnPacketRx);
  RAPP_MsgHandlerTable = NULL;
}

#endif /* McuRNET_CONFIG_IS_ENABLED */
