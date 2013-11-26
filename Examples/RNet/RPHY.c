/**
 * \file
 * \brief This implements the PHY layer of the network stack.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module is used to process the raw payload packets.
 */

#include "RNetConf.h"
#if PL_HAS_RADIO
#include "RPHY.h"
#include "RMAC.h"
#include "RMSG.h"
#if PL_HAS_SHELL
  #include "CLS1.h"
#endif

uint8_t RPHY_GetPayload(RPHY_PacketDesc *packet) {
  packet->flags = RPHY_PACKET_FLAGS_NONE;
  return RMSG_GetRxMsg(packet->data, packet->dataSize); /* ERR_OK, ERR_OVERFLOW or ERR_RXEMPTY */
}

uint8_t RPHY_OnPacketRx(RPHY_PacketDesc *packet) {
  return RMAC_OnPacketRx(packet); /* pass message up the stack */
}

uint8_t RPHY_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize) {
  return RMSG_QueueTxMsg(buf, bufSize, payloadSize);
}

void RPHY_SniffPacket(RPHY_PacketDesc *packet, bool isTx) {
#if PL_HAS_SHELL
  uint8_t buf[32];
  const CLS1_StdIOType *io;
  int i;
  uint8_t dataSize;
  
  io = CLS1_GetStdio();
  if (isTx) {
    CLS1_SendStr((unsigned char*)"Tx, ", io->stdOut);
  } else {
    CLS1_SendStr((unsigned char*)"Rx, ", io->stdOut);
  }
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"flags: ");
  UTIL1_strcatNum16s(buf, sizeof(buf), packet->flags);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" size: ");
  UTIL1_strcatNum16s(buf, sizeof(buf), packet->dataSize);
  CLS1_SendStr(buf, io->stdOut);
  /* write as hex */
  CLS1_SendStr((unsigned char*)" hex: ", io->stdOut);
  dataSize = packet->data[0]; /* first byte in data buffer is number of bytes */
  for(i=0; i<=dataSize;i++) {
    buf[0] = '\0';
    UTIL1_strcatNum8Hex(buf, sizeof(buf), packet->data[i]);
    UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" ");
    CLS1_SendStr(buf, io->stdOut);
  }
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStr(buf, io->stdOut);
#else
  (void)packet;
  (void)isTx;
#endif
}

void RPHY_Deinit(void) {
  /* nothing needed */
}

void RPHY_Init(void) {
  /* nothing needed */
}

#endif /* PL_HAS_RADIO */
