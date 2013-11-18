/**
 * \file
 * \brief This is the implementation of the Radio MAC part.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module encapsulates the Media Access of network stack.
 */

#include "Platform.h"
#if PL_HAS_RADIO
#include "RMAC.h"
#include "RPHY.h"
#include "RNWK.h"

static uint8_t RMAC_SeqNr = 0;
static uint8_t RMAC_ExpectedAckSeqNr;

uint8_t RMAC_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize) {
  RMAC_BUF_TYPE(buf) = RMAC_MSG_TYPE_DATA;
  RMAC_ExpectedAckSeqNr = RMAC_SeqNr;
  RMAC_BUF_SEQN(buf) = RMAC_SeqNr++;
  return RPHY_PutPayload(buf, bufSize, payloadSize+RMAC_HEADER_SIZE);
}

uint8_t RMAC_OnPacketRx(RPHY_PacketDesc *packet) {
  return RNWK_OnPacketRx(packet); /* pass data packet up the stack */
}

uint8_t RMAC_SendACK(RPHY_PacketDesc *packet) {
  /* send an ack message back: this is is of type ack with src and dst address */
  RMAC_BUF_TYPE(packet->data) = RMAC_MSG_TYPE_ACK; /* set type to ack */
  /* use same sequence number as in the received package, so no change */
  return RPHY_PutPayload(packet->data, packet->dataSize, RMAC_HEADER_SIZE+RNWK_HEADER_SIZE);
}

RMAC_MsgType RMAC_GetType(uint8_t *buf, size_t bufSize) {
  (void)bufSize; /* not used */
  return RMAC_BUF_TYPE(buf);
}

bool RMAC_IsExpectedACK(uint8_t *buf, size_t bufSize) {
  (void)bufSize; /* not used */
  return RMAC_BUF_SEQN(buf)==RMAC_ExpectedAckSeqNr;
}

void RMAC_Deinit(void) {
  /* nothing needed */
}

void RMAC_Init(void) {
  RMAC_SeqNr = 0;
  RMAC_ExpectedAckSeqNr = 0;
}
#endif /* PL_HAS_RADIO */
