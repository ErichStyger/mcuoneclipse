/**
 * \file
 * \brief This is the interface for the Radio Application part.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module acts as the application part of the network stack.
 */

#ifndef RAPP_H_
#define RAPP_H_

#include "RNetConf.h"
#include "RNWK.h"
#include "RPHY.h"

/* payload format is:
 * <type><size><data>
 */
#define RAPP_HEADER_SIZE   (2) /* <type><size> */
#define RAPP_PAYLOAD_SIZE  (RNWK_PAYLOAD_SIZE-RAPP_HEADER_SIZE)
#define RAPP_BUFFER_SIZE   (RNWK_BUFFER_SIZE)

/* PHY buffer access macros */
#define RAPP_BUF_IDX_TYPE                 (RNWK_BUF_IDX_PAYLOAD+0) /* <type> index */
#define RAPP_BUF_IDX_SIZE                 (RNWK_BUF_IDX_PAYLOAD+1) /* <size> index */
#define RAPP_BUF_IDX_PAYLOAD              (RNWK_BUF_IDX_PAYLOAD+2) /* <app payload> index */

#define RAPP_BUF_TYPE(phy)                ((phy)[RAPP_BUF_IDX_TYPE])
#define RAPP_BUF_SIZE(phy)                ((phy)[RAPP_BUF_IDX_SIZE])

#define RAPP_BUF_PAYLOAD_START(phy)       (RNWK_BUF_PAYLOAD_START(phy)+RAPP_HEADER_SIZE)

typedef uint8_t (*RAPP_MsgHandler) (RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet);

uint8_t RAPP_SetMessageHandlerTable(const RAPP_MsgHandler *table);

uint8_t RAPP_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RAPP_MSG_Type type, RNWK_ShortAddrType dstAddr);

RNWK_ShortAddrType RAPP_GetThisNodeAddr(void);

uint8_t RAPP_SetThisNodeAddr(RNWK_ShortAddrType addr);

/*!
 * \brief Send an application payload data block
 * \param appPayload Size of application payload
 * \param appPayloadSize Application payload size
 * \param msgType Payload message type
 * \param dstAddr destination address
 * \return Error code, ERR_OK for no failure
 */
uint8_t RAPP_SendPayloadDataBlock(uint8_t *appPayload, uint8_t appPayloadSize, uint8_t msgType, RNWK_ShortAddrType dstAddr);

/*!
 * \brief Sniffs and dumps a packet.
 * \param packet Data packet
 * \param isTx If either Tx or Rx packet
 */
void RAPP_SniffPacket(RPHY_PacketDesc *packet, bool isTx);

/*! \brief Initializes the module */
void RAPP_Init(void);

/*! \brief Deinitializes the module */
void RAPP_Deinit(void);

#endif /* RAPP_H_ */
