/**
 * \file
 * \brief Radio PHY (Physical Interface)
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html), see 'RNet_License.txt'
 *
 * This interface is for the PHY (Physical) part of the stack.
  */

#ifndef RPHY_H_
#define RPHY_H_

#include "RNetConf.h"
/* payload format is:
 * PHY: <size><phy payload>
 * MAC:       <type><seq#><mac payload> 
 * NWK:                   <saddr><dstaddr><nwk payload>
 * APP:                                   <type><size><data>
 */
#define RPHY_HEADER_SIZE    (1) /* <size> */
#define RPHY_PAYLOAD_SIZE   (RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE) /* total number of payload bytes */
#define RPHY_BUFFER_SIZE    (RPHY_HEADER_SIZE+RPHY_PAYLOAD_SIZE) /* <size><phy payload> */

/* PHY buffer access macros */
#define RPHY_BUF_IDX_SIZE                 (0) /* <size> index */
#define RPHY_BUF_IDX_PAYLOAD              (1) /* <phy payload> index */
/* access macros */
#define RPHY_BUF_SIZE(phy)                ((phy)[RPHY_BUF_IDX_SIZE])
#define RPHY_BUF_PAYLOAD_START(phy)       ((phy)+RPHY_HEADER_SIZE)

/* flag bits inside PacketDesc below */
#define RPHY_PACKET_FLAGS_NONE  (0)
  /*!< initialization value */
#define RPHY_PACKET_FLAGS_ACK   (1<<0)
  /*!< valid ACK received */

typedef struct {
  uint8_t flags;    /*!< flags, see RPHY_PACKET_FLAGS_XXXX above */
  uint8_t *data;    /*!< pointer to the data packet */
  uint8_t dataSize; /*!< size of data buffer */
} RPHY_PacketDesc;

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
 * \return Error code, ERR_OK for everything fine.
 */
uint8_t RPHY_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize);

/*! \brief Initializes the module */
void RPHY_Init(void);

/*! \brief Deinitializes the module */
void RPHY_Deinit(void);

#endif /* RPHY_H_ */
