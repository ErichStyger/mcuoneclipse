/**
 * \file
 * \brief Radio Network NWK Layer Implementation
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module implements the NWK (Network) of the radio network stack.
 */

#include "RNetConf.h"
#include "RPHY.h"
#include "RMAC.h"
#include "RNWK.h"
#include "RAPP.h"
#include "%@Utility@'ModuleName'.h"

static RNWK_ShortAddrType RNWK_ThisNodeAddr = RNWK_ADDR_BROADCAST; /* address of this network node */
static RNWK_AppOnRxCallbackType RNWK_AppOnRxCallback = NULL; /* notification callback installed by upper layer */

RNWK_ShortAddrType RNWK_GetThisNodeAddr(void) {
  return RNWK_ThisNodeAddr;
}

uint8_t RNWK_SetThisNodeAddr(RNWK_ShortAddrType addr) {
  RNWK_ThisNodeAddr = addr;
  return ERR_OK;
}

uint8_t RNWK_SetAppOnPacketRxCallback(RNWK_AppOnRxCallbackType callback) {
  RNWK_AppOnRxCallback = callback;
  return ERR_OK;
}

uint8_t RNWK_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RNWK_ShortAddrType dstAddr, RPHY_FlagsType flags) {
  RNWK_ShortAddrType srcAddr;
  
  srcAddr = RNWK_GetThisNodeAddr();
  RNWK_BUF_SET_SRC_ADDR(buf, srcAddr);
  RNWK_BUF_SET_DST_ADDR(buf, dstAddr);
  return RMAC_PutPayload(buf, bufSize, payloadSize+RNWK_HEADER_SIZE, flags);
}

uint8_t RNWK_SendACK(RPHY_PacketDesc *rxPacket, RNWK_ShortAddrType saddr) {
  RNWK_ShortAddrType addr;
  uint8_t buf[RMAC_BUFFER_SIZE];
  RPHY_PacketDesc ackPacket;
  
  ackPacket.flags = RPHY_PACKET_FLAGS_NONE;
  ackPacket.phyData = buf;
  ackPacket.phySize = sizeof(buf);
  
  /* send an ack message back: this is is of type ack with src and dst address */
  addr = RNWK_BUF_GET_SRC_ADDR(rxPacket->phyData); /* who should receive the ack? */
  RNWK_BUF_SET_SRC_ADDR(ackPacket.phyData, saddr); /* set source address */
  RNWK_BUF_SET_DST_ADDR(ackPacket.phyData, addr); /* destination address is from where we got the data */
  return RMAC_SendACK(rxPacket, &ackPacket);
}

uint8_t RNWK_OnPacketRx(RPHY_PacketDesc *packet) {
  RNWK_ShortAddrType addr;
  RMAC_MsgType type;

  addr = RNWK_BUF_GET_DST_ADDR(packet->phyData);
  if (addr==RNWK_ADDR_BROADCAST || addr==RNWK_GetThisNodeAddr()) { /* it is for me :-) */
    type = RMAC_GetType(packet->phyData, packet->phySize); /* get the type of the message */
    if (RMAC_MSG_TYPE_IS_ACK(type) && RMAC_IsExpectedACK(packet->phyData, packet->phySize)) {
      /* it is an ACK, and the sequence number matches. Mark it with a flag and return, as no need for further processing */
      packet->flags |= RPHY_PACKET_FLAGS_IS_ACK;
      return ERR_OK; /* no need to process the packet further */
    } else if (RMAC_MSG_TYPE_IS_DATA(type)) { /* data packet received */
      if (RNWK_AppOnRxCallback!=NULL) { /* do we have a callback? */
#if RNET_CONFIG_USE_ACK
        if (RMAC_MSG_TYPE_REQ_ACK(type)) {
          (void)RNWK_SendACK(packet, RNWK_GetThisNodeAddr()); /* send ack message back */
        }
#endif
        return RNWK_AppOnRxCallback(packet); /* call upper layer */
      }
    } else {
      return ERR_FAULT; /* wrong message type? */
    }
  }
  return ERR_FAILED;
}

void RNWK_SniffPacket(RPHY_PacketDesc *packet, bool isTx) {
  RAPP_SniffPacket(packet, isTx);
}

%if defined(Shell)
static uint8_t PrintHelp(const %@Shell@'ModuleName'%.StdIOType *io) {
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"rnwk", (unsigned char*)"Group of rnwk commands\r\n", io->stdOut);
  %@Shell@'ModuleName'%.SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows help or status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const %@Shell@'ModuleName'%.StdIOType *io) {
  uint8_t buf[32];
  
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"rnwk", (unsigned char*)"\r\n", io->stdOut);
  
  %@Utility@'ModuleName'%.strcpy(buf, sizeof(buf), (unsigned char*)"0x");
#if RNWK_SHORT_ADDR_SIZE==1
  %@Utility@'ModuleName'%.strcatNum8Hex(buf, sizeof(buf), RNWK_GetThisNodeAddr());
#else
  %@Utility@'ModuleName'%.strcatNum16Hex(buf, sizeof(buf), RNWK_GetThisNodeAddr());
#endif
  %@Utility@'ModuleName'%.strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  %@Shell@'ModuleName'%.SendStatusStr((unsigned char*)"  addr", buf, io->stdOut);

  return ERR_OK;
}

uint8_t RNWK_ParseCommand(const unsigned char *cmd, bool *handled, const %@Shell@'ModuleName'%.StdIOType *io) {
  if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)%@Shell@'ModuleName'%.CMD_HELP)==0 || %@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"rnwk help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (%@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)%@Shell@'ModuleName'%.CMD_STATUS)==0 || %@Utility@'ModuleName'%.strcmp((char*)cmd, (char*)"rnwk status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK;
}
%endif

void RNWK_Deinit(void) {
  /* nothing needed */
}

void RNWK_Init(void) {
  RNWK_ThisNodeAddr = RNWK_ADDR_BROADCAST;
  RNWK_AppOnRxCallback = NULL;
}
