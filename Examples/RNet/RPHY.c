/*
 * RPHY.c
 *
 *  Created on: Oct 12, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#if PL_HAS_RADIO
#include "RPHY.h"
#include "RMAC.h"
#include "RMSG.h"

uint8_t RPHY_GetPayload(uint8_t *buf, uint8_t bufSize) {
  return RMSG_GetRxMsg(buf, bufSize); /* ERR_OK, ERR_OVERFLOW or ERR_RXEMPTY */
}

uint8_t RPHY_OnPacketRx(RPHY_PacketDesc *packet) {
  /* pass message up the stack */
  return RMAC_OnPacketRx(packet);
}

uint8_t RPHY_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize) {
  return RMSG_QueueTxMsg(buf, bufSize, payloadSize);
}

void RPHY_Deinit(void) {
  /* nothing needed */
}

void RPHY_Init(void) {
  /* nothing needed */
}

#endif /* PL_HAS_RADIO */
