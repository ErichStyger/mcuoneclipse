/**
 * \file
 * \brief Radio Network NWK Layer
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module implements interface for the NWK (Network) of the radio network stack.
 */

#ifndef RNWK_H_
#define RNWK_H_

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED
#include "RMAC.h"
#include "RPHY.h"

/* payload format is:
 * PHY: <size><phy payload>
 * MAC:       <type><seq#><mac payload> 
 * NWK:                   <saddr><dstaddr><nwk payload>
 * APP:                                   <type><size><data>
 */
#define RNWK_SHORT_ADDR_SIZE   RNET_CONFIG_SHORT_ADDR_SIZE /* size of short address type */
#if RNWK_SHORT_ADDR_SIZE==1
  typedef uint8_t          RNWK_ShortAddrType; /* short address type */
#elif RNWK_SHORT_ADDR_SIZE==2
  typedef uint16_t          RNWK_ShortAddrType; /* short address type */
#else
  #error "ERROR: unsupported address size"
#endif

#define RNWK_HEADER_SIZE   (2*RNWK_SHORT_ADDR_SIZE) /* <saddr><daddr> */
#define RNWK_PAYLOAD_SIZE  (RMAC_PAYLOAD_SIZE-RNWK_HEADER_SIZE)
#define RNWK_BUFFER_SIZE   (RMAC_BUFFER_SIZE)

/* PHY buffer access macros */
#define RNWK_BUF_IDX_SRC_ADDR             (RMAC_BUF_IDX_PAYLOAD+0) /* <saddr> index */
#define RNWK_BUF_IDX_DST_ADDR             (RMAC_BUF_IDX_PAYLOAD +RNWK_SHORT_ADDR_SIZE) /* <daddr#> index */
#define RNWK_BUF_IDX_PAYLOAD              (RNWK_BUF_IDX_DST_ADDR+RNWK_SHORT_ADDR_SIZE) /* <nwk payload> index */

#if RNWK_SHORT_ADDR_SIZE==1
  #define RNWK_BUF_SET_SRC_ADDR(phy, addr)            ((phy)[RNWK_BUF_IDX_SRC_ADDR])=(addr);
  #define RNWK_BUF_SET_DST_ADDR(phy, addr)            ((phy)[RNWK_BUF_IDX_DST_ADDR])=(addr);
  #define RNWK_ADDR_BROADCAST                         0xFF
#elif RNWK_SHORT_ADDR_SIZE==2
  #define RNWK_BUF_SET_SRC_ADDR(phy, addr)            {((phy)[RNWK_BUF_IDX_SRC_ADDR])=(uint8_t)((addr)&0xFF); ((phy)[RNWK_BUF_IDX_SRC_ADDR+1])=(uint8_t)((addr>>8)&0xFF);}
  #define RNWK_BUF_SET_DST_ADDR(phy, addr)            {((phy)[RNWK_BUF_IDX_DST_ADDR])=(uint8_t)((addr)&0xFF); ((phy)[RNWK_BUF_IDX_DST_ADDR+1])=(uint8_t)((addr>>8)&0xFF);}
  #define RNWK_ADDR_BROADCAST                         0xFFFF
#else
  #error "NYI"
#endif

#if RNWK_SHORT_ADDR_SIZE==1
  #define RNWK_BUF_GET_SRC_ADDR(phy)            ((phy)[RNWK_BUF_IDX_SRC_ADDR])
  #define RNWK_BUF_GET_DST_ADDR(phy)            ((phy)[RNWK_BUF_IDX_DST_ADDR])
#elif RNWK_SHORT_ADDR_SIZE==2
  #define RNWK_BUF_GET_SRC_ADDR(phy)            (((phy)[RNWK_BUF_IDX_SRC_ADDR+1])<<8)|((phy)[RNWK_BUF_IDX_SRC_ADDR])
  #define RNWK_BUF_GET_DST_ADDR(phy)            (((phy)[RNWK_BUF_IDX_DST_ADDR+1])<<8)|((phy)[RNWK_BUF_IDX_DST_ADDR])
#else
  #error "NYI"
#endif

#define RNWK_BUF_PAYLOAD_START(phy)             (RMAC_BUF_PAYLOAD_START(phy)+RNWK_HEADER_SIZE)

typedef uint8_t (*RNWK_AppOnRxCallbackType)(RPHY_PacketDesc *packet);

uint8_t RNWK_SetAppOnPacketRxCallback(RNWK_AppOnRxCallbackType callback);

uint8_t RNWK_OnPacketRx(RPHY_PacketDesc *packet);

/*!
 * \brief Sents an ACK packet for a packet received.
 * \param rxPacket Packet which has been received and for which an ACK should be sent.
 * \param saddr Address to where to send the ACK back.
 * \return Error code, ERR_OK for no error.
 */
uint8_t RNWK_SendACK(RPHY_PacketDesc *rxPacket, RNWK_ShortAddrType saddr);

/*!
 * \brief Puts a payload into the buffer queue to be sent asynchronously.
 * \param buf Message buffer with payload.
 * \param bufSize Size of message buffer, must be of RNWK_BUFFER_SIZE.
 * \param payloadSize Size of the payload in bytes.
 * \param dstAddr Destination node address.
 * \param flags Packet flags.
 */
uint8_t RNWK_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RNWK_ShortAddrType dstAddr, RPHY_FlagsType flags);

#include "McuShell.h"
uint8_t RNWK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

/*!
 * \brief Returns the node network address.
 * \return Node short address.
 */
RNWK_ShortAddrType RNWK_GetThisNodeAddr(void);

/*!
 * \brief Sets this node own address
 * \param addr New address to use
 */
uint8_t RNWK_SetThisNodeAddr(RNWK_ShortAddrType addr);

/*!
 * \brief Sniffs and dumps a packet.
 * \param packet Data packet.
 * \param isTx If either Tx or Rx packet.
 */
void RNWK_SniffPacket(RPHY_PacketDesc *packet, bool isTx);

/*! \brief Initializes the module */
void RNWK_Init(void);

/*! \brief Deinitializes the module */
void RNWK_Deinit(void);

#endif /* McuRNET_CONFIG_IS_ENABLED */

#endif /* RNWK_H_ */

