/**
 * \file
 * \brief This is the interface for the Radio MAC part.
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This module encapsulates the Media Access of network stack.
 */

#ifndef RMAC_H_
#define RMAC_H_

#include "RPHY.h"

typedef enum RMAC_MsgType {
  RMAC_MSG_TYPE_DATA, /* data message */
  RMAC_MSG_TYPE_ACK,  /* acknowledge message */
  RMAC_MSG_TYPE_CMD   /* command message */
} RMAC_MsgType;

/* message format is:
 * PHY: <size><phy payload>
 * MAC:       <type><seq#><mac payload> 
 * NWK:                   <saddr><dstaddr><nwk payload>
 * APP:                                   <type><size><data>
 */
#define RMAC_HEADER_SIZE   (2) /* <type><seq#> */
#define RMAC_PAYLOAD_SIZE  (RPHY_PAYLOAD_SIZE-RMAC_HEADER_SIZE)
#define RMAC_BUFFER_SIZE   (RPHY_BUFFER_SIZE)

/* PHY buffer access macros */
#define RMAC_BUF_IDX_TYPE                 (RPHY_BUF_IDX_PAYLOAD+0) /* <type> index */
#define RMAC_BUF_IDX_SEQNR                (RPHY_BUF_IDX_PAYLOAD+1) /* <seq#> index */
#define RMAC_BUF_IDX_PAYLOAD              (RPHY_BUF_IDX_PAYLOAD+2) /* <mac payload> index */

#define RMAC_BUF_TYPE(phy)                ((phy)[RMAC_BUF_IDX_TYPE])
#define RMAC_BUF_SEQN(phy)                ((phy)[RMAC_BUF_IDX_SEQNR])

#define RMAC_BUF_PAYLOAD_START(phy)       (RPHY_BUF_PAYLOAD_START(phy)+RMAC_HEADER_SIZE)

uint8_t RMAC_OnPacketRx(RPHY_PacketDesc *packet);

/*!
 * \brief Puts the MAC payload data into a buffer to be sent later.
 * \param[in] buf Buffer with the data, must be of RMAC_BUFFER_SIZE.
 * \param[in] bufSize Buffer size.
 * \param[in] payloadSize Size of MAC payload data.
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small.
 */
uint8_t RMAC_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize);

/*!
 * \brief Sends an acknowledge message for the received MAC payload data.
 * \param[in] packet Packet data for which we need to send the ack.
 * \return Error code, ERR_OK if everything is ok, error code otherwise.
 */
uint8_t RMAC_SendACK(RPHY_PacketDesc *packet);

/*!
 * \brief Check if the expected ACK message is expected. This is done with checking the sequence number.
 * \param[in] buf Pointer to the received packet.
 * \param[in] bufSize size of the received packet.
 * \return TRUE if it is an expected ACK packet, false otherwise (e.g. if sequence number does not match).
 */
bool RMAC_IsExpectedACK(uint8_t *buf, size_t bufSize);

/*!
 * \brief Returns the type of the message
 * \param buf Pointer to the message buffer
 * \param bufSize Size of the buffer
 * \return Type of message
 */
RMAC_MsgType RMAC_GetType(uint8_t *buf, size_t bufSize);

/*! \brief Initializes the module */
void RMAC_Init(void);

/*! \brief Deinitializes the module */
void RMAC_Deinit(void);

#endif /* RMAC_H_ */
