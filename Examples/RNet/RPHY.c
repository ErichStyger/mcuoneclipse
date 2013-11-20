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

uint8_t RPHY_GetPayload(uint8_t *buf, uint8_t bufSize) {
  return RMSG_GetRxMsg(buf, bufSize); /* ERR_OK, ERR_OVERFLOW or ERR_RXEMPTY */
}

uint8_t RPHY_OnPacketRx(RPHY_PacketDesc *packet) {
  return RMAC_OnPacketRx(packet); /* pass message up the stack */
}

uint8_t RPHY_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize) {
  return RMSG_QueueTxMsg(buf, bufSize, payloadSize);
}

uint8_t RPHY_ProcessRx(RPHY_PacketDesc *packet, uint8_t flags) {
  uint8_t res;
  
  res = RPHY_GetPayload(packet->data, packet->dataSize); /* get message */
  if (res!=ERR_OK) { /* failed or no message available? */
    return res; /* return error code */
  }
  packet->flags = flags; /* initialize packet flags */
  return RMAC_OnPacketRx(packet); /* pass packet up the stack */
}

void RPHY_Deinit(void) {
  /* nothing needed */
}

void RPHY_Init(void) {
  /* nothing needed */
}

#endif /* PL_HAS_RADIO */
