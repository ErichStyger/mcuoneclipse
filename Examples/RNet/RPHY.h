/*
 * RPHY.h
 *
 *  Created on: Oct 12, 2013
 *      Author: tastyger
 */

#ifndef RPHY_H_
#define RPHY_H_

#include "RNet_Config.h"
/* message format is:
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
 * \param[out] buf Buffer where to store the data, must be of size PHY_BUFFER_SIZE.
 * \param[out] bufSize Buffer size.
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small, ERR_.
 */
uint8_t RPHY_GetPayload(uint8_t *buf, uint8_t bufSize);

uint8_t RPHY_PutPayload(uint8_t *buf, size_t bufSize, uint8_t payloadSize);

uint8_t RPHY_ProcessRx(RPHY_PacketDesc *packet);

/*! \brief Initializes the module */
void RPHY_Init(void);

/*! \brief Deinitializes the module */
void RPHY_Deinit(void);

#endif /* RPHY_H_ */
