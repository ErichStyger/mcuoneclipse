/**
 * \file
 * \brief Radio PHY (Physical Interface)
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This interface is for the PHY (Physical) part of the stack.
 */

#ifndef RPHY_H_
#define RPHY_H_

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED

/* payload format is:
 * PHY: <flags><size><phy payload>
 * MAC:              <type><seq#><mac payload> 
 * NWK:                          <saddr><dstaddr><nwk payload>
 * APP:                                          <type><size><data>
 */
#define RPHY_HEADER_SIZE    (2) /* <flags><size> */
#define RPHY_PAYLOAD_SIZE   (RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE) /* total number of payload bytes */
#define RPHY_BUFFER_SIZE    (RPHY_HEADER_SIZE+RPHY_PAYLOAD_SIZE) /* <size><phy payload> */

/* PHY buffer access macros */
#define RPHY_BUF_IDX_FLAGS                (0) /* <flags> index */
#define RPHY_BUF_IDX_SIZE                 (1) /* <size> index */
#define RPHY_BUF_IDX_PAYLOAD              (2) /* <phy payload> index */
/* access macros */
#define RPHY_BUF_FLAGS(phy)               ((phy)[RPHY_BUF_IDX_FLAGS])
#define RPHY_BUF_SIZE(phy)                ((phy)[RPHY_BUF_IDX_SIZE])
#define RPHY_BUF_PAYLOAD_START(phy)       ((phy)+RPHY_HEADER_SIZE)

typedef uint8_t RPHY_FlagsType;
/* flag bits inside PacketDesc below */
#define RPHY_PACKET_FLAGS_NONE        (0)
  /*!< initialization value */
#define RPHY_PACKET_FLAGS_IS_ACK      (1<<0)
  /*!< valid ACK received */
#define RPHY_PACKET_FLAGS_REQ_ACK     (1<<1)
  /*!< request acknowledge */
#define RPHY_PACKET_FLAGS_POWER_DOWN  (1<<2)
  /*!< power down transceiver */

typedef struct {
  RPHY_FlagsType flags;/*!< flags, see RPHY_PACKET_FLAGS_XXXX above */
  uint8_t phySize;     /*!< size of PHY data buffer */
  uint8_t *phyData;    /*!< pointer to the PHY data buffer */
  uint8_t *rxtx;       /*!< pointer into phyData, start of TX/RX data */
} RPHY_PacketDesc;

/*!
 * \brief Flushes the Rx queue.
 * \return Error code, ERR_OK for everything fine.
 */
uint8_t RPHY_FlushRxQueue(void);

/*!
 * \brief Flushes the Tx queue.
 * \return Error code, ERR_OK for everything fine.
 */
uint8_t RPHY_FlushTxQueue(void);

/*!
 * \brief Function called on Rx of a packet.
 * \param packet Pointer to packet
 * \return ERR_OK, if everything is fine, error code otherwise.
 */
uint8_t RPHY_OnPacketRx(RPHY_PacketDesc *packet);

/*!
 * \brief Returns the PHY payload data.
 * \param[out] packet Pointer to packet descriptor.
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small, ERR_.
 */
uint8_t RPHY_GetPayload(RPHY_PacketDesc *packet);

/*!
 * \brief Puts a packet into the queue to be sent.
 * \param buf Pointer to the packet buffer.
 * \param bufSize Size of the payload buffer.
 * \param payloadSize Size of payload data.
 * \param flags Packet flags.
 * \return Error code, ERR_OK for everything fine.
 */
uint8_t RPHY_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize, RPHY_FlagsType flags);

/*!
 * \brief Sniffs and dumps a packet.
 * \param packet Data packet.
 * \param isTx If either Tx or Rx packet.
 */
void RPHY_SniffPacket(RPHY_PacketDesc *packet, bool isTx);

/*! \brief Initializes the module */
void RPHY_Init(void);

/*! \brief Deinitializes the module */
void RPHY_Deinit(void);

#endif /* McuRNET_CONFIG_IS_ENABLED */

#endif /* RPHY_H_ */

