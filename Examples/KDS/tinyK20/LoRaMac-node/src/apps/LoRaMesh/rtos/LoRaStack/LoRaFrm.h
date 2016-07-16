/**
 * \file LoRaNet.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 03.12.2015
 * \version 1.0
 *
 * \brief LoRa stack network layer implementation
 */

#ifndef __LORAFRM_H_
#define __LORAFRM_H_

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "LoRaMesh-config.h"
#include "LoRaMac.h"
#include "LoRaPhy.h"

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
#define LORAFRM_LOWEST_FPORT                    (1)
#define LORAFRM_HIGHEST_FPORT                   (224)

#define LORAFRM_HEADER_SIZE_MAX                 (22)
#define LORAFRM_HEADER_SIZE_MIN                 (7)
#define LORAFRM_OPTSLEN_MAX                     (15)
#define LORAFRM_PORT_SIZE                       (1)
#define LORAFRM_PAYLOAD_SIZE                    (LORAMAC_PAYLOAD_SIZE-LORAFRM_HEADER_SIZE_MIN)
#define LORAFRM_BUFFER_SIZE                     (LORAMAC_BUFFER_SIZE)

/* PHY buffer access macros */
#define LORAFRM_BUF_IDX_DEVADDR                 (LORAMAC_BUF_IDX_PAYLOAD+0) /* <DevAddr> index */
#define LORAFRM_BUF_IDX_CTRL                    (LORAMAC_BUF_IDX_PAYLOAD+4) /* <fCtrl> index */
#define LORAFRM_BUF_IDX_CNTR                    (LORAMAC_BUF_IDX_PAYLOAD+5) /* <fCnt> index */
#define LORAFRM_BUF_IDX_OPTS                    (LORAMAC_BUF_IDX_PAYLOAD+7) /* <fOpts> index */
/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/
#define LORAFRM_BUF_DEVADDR(phy)                ((phy)[LORAFRM_BUF_IDX_DEVADDR])
#define LORAFRM_BUF_CTRL(phy)                   ((phy)[LORAFRM_BUF_IDX_CTRL])
#define LORAFRM_BUF_CNTR(phy)                   ((phy)[LORAFRM_BUF_IDX_CNTR])
#define LORAFRM_BUF_OPTS(phy)                   ((phy)[LORAFRM_BUF_IDX_OPTS])

#define LORAFRM_BUF_IDX_PORT(optsLen)           (LORAFRM_BUF_IDX_OPTS + optsLen)
#define LORAFRM_BUF_PAYLOAD_START(phy)          (LORAMAC_BUF_PAYLOAD_START(phy) + LORAFRM_HEADER_SIZE_MIN)
#define LORAFRM_BUF_PAYLOAD_START_WPORT(phy)    (LORAMAC_BUF_PAYLOAD_START(phy) + LORAFRM_HEADER_SIZE_MIN + LORAFRM_PORT_SIZE)

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
/*! LoRa network frame header field definition */
typedef union {
    uint8_t Value;
    struct {
        uint8_t FOptsLen :4;
        uint8_t FPending :1;
        uint8_t Ack :1;
        uint8_t AdrAckReq :1;
        uint8_t Adr :1;
    } Bits;
} LoRaFrm_Ctrl_t;

/*! Frame direction definition */
typedef enum LoRaFrm_Dir_e {
    UP_LINK = 0, DOWN_LINK
} LoRaFrm_Dir_t;

/*******************************************************************************
 * API FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 * LoRa network layer initialization
 */
void LoRaFrm_Init( void );

/*!
 * \brief
 *
 * \param packet Pointer to the packet descriptor
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small.
 */
uint8_t LoRaFrm_OnPacketRx( LoRaPhy_PacketDesc *packet, uint32_t devAddr,
        LoRaFrm_Dir_t fDir, uint32_t fCnt );

/*!
 * \brief Puts a payload into the buffer queue to be sent asynchronously.
 *
 * \param fBuffer Message buffer with payload.
 * \param fBufferSize Size of message buffer, must be of LORAFRM_BUFFER_SIZE.
 * \param payloadSize Size of the payload in bytes.
 * \param fPort Destination port.
 * \param fOpts Options buffer.
 * \param fOptsLen Size of options buffer in bytes.
 * \param type LoRa messsage type.
 *
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small.
 */
uint8_t LoRaFrm_PutPayload( uint8_t* buf, uint16_t bufSize, uint8_t payloadSize,
        uint32_t devAddr, uint8_t fPort, bool isConfirmed );

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

#endif /* __LORAFRM_H_ */
