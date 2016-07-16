/**
 * \file LoRaMac.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 03.12.2015
 * \version 1.0
 *
 * \brief LoRa stack medium access layer implementation
 */

#ifndef __LORAMAC_H_
#define __LORAMAC_H_

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "LoRaMesh-config.h"
#include "LoRaPhy.h"

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
#define LORAMAC_HEADER_SIZE                 (1)
#define LORAMAC_MIC_SIZE                    (4)
#define LORAMAC_PAYLOAD_SIZE                (LORAPHY_PAYLOAD_SIZE-LORAMAC_HEADER_SIZE)
#define LORAMAC_BUFFER_SIZE                 (LORAPHY_BUFFER_SIZE)

/* PHY buffer access macros */
#define LORAMAC_BUF_IDX_HDR                 (LORAPHY_BUF_IDX_PAYLOAD+0) /* <Hdr> index */
#define LORAMAC_BUF_IDX_PAYLOAD             (LORAMAC_BUF_IDX_HDR+LORAMAC_HEADER_SIZE) /* <nwk payload> index */

#define LORAMAC_JOIN_MESH_MSG_LENGTH        (0x1B)
#define LORAMAC_REBIND_MESH_MSG_LENGTH      (0x1F)
/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/
#define LORAMAC_BUF_HDR(phy)                        ((phy)[LORAMAC_BUF_IDX_HDR])

#define LORAMAC_BUF_MIC_START(phy, payloadSize)     (LORAPHY_BUF_PAYLOAD_START(phy) + payloadSize)
#define LORAMAC_BUF_PAYLOAD_START(phy)              (LORAPHY_BUF_PAYLOAD_START(phy) + LORAMAC_HEADER_SIZE)
/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
/*! LoRaMAC message types */
typedef enum {
    MSG_TYPE_JOIN_REQ = 0x00,
    MSG_TYPE_JOIN_ACCEPT = 0x01,
    MSG_TYPE_DATA_UNCONFIRMED_UP = 0x02,
    MSG_TYPE_DATA_UNCONFIRMED_DOWN = 0x03,
    MSG_TYPE_DATA_CONFIRMED_UP = 0x04,
    MSG_TYPE_DATA_CONFIRMED_DOWN = 0x05,
    MSG_TYPE_RFU = 0x06,
    MSG_TYPE_PROPRIETARY = 0x07,
} LoRaMac_MsgType_t;

typedef enum {
    MAC_COMMAND_LINK_CHECK = 0x02,
    MAC_COMMAND_LINK_ADR,
    MAC_COMMAND_DUTY_CYCLE,
    MAC_COMMAND_RX_PARAM_SETUP,
    MAC_COMMAND_DEV_STATUS,
    MAC_COMMAND_NEW_CHANNEL,
    MAC_COMMAND_RX_TIMING_SETUP,
    /* 0x09 to 0x7F reserved for RFU */
    MAC_COMMAND_UP_LINK_SLOT_INFO = 0x80,
    MAC_COMMAND_MULTICAST_GROUP_INFO,
    MAC_COMMAND_ROUTE_DISCOVER,
    MAC_COMMAND_ADDR_CONF_RES,
} LoRaMac_Command_t;

/*! LoRaMAC Battery level indicator */
typedef enum {
    BAT_LEVEL_EXT_SRC = 0x00,
    BAT_LEVEL_EMPTY = 0x01,
    BAT_LEVEL_FULL = 0xFE,
    BAT_LEVEL_NO_MEASURE = 0xFF,
} LoRaMacBatteryLevel_t;

typedef struct {
    uint8_t Margin;
    uint8_t GwCnt;
} LoRaMac_LinkCheck_t;

/*! LoRaMAC header field definition */
typedef union {
    uint8_t Value;
    struct {
        uint8_t Major :2;
        uint8_t RFU :3;
        uint8_t MType :3;
    } Bits;
} LoRaMac_Header_t;

/*!
 * Function callback to get the current battery level needed for status
 * request command
 *
 * \retval batteryLevel Current battery level
 */
typedef uint8_t (*LoRaMac_BatteryLevelCallback_t)( void );

/*******************************************************************************
 * API FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 * LoRa medium access layer initialization.
 */
void LoRaMac_Init( LoRaMac_BatteryLevelCallback_t callback );

/*!
 * \brief
 *
 * \param packet Pointer to the packet descriptor
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small.
 */
uint8_t LoRaMac_OnPacketRx( LoRaPhy_PacketDesc *packet );

/*!
 * \brief Puts a payload into the buffer queue to be sent asynchronously.
 *
 * \param fBuffer Message buffer with payload.
 * \param fBufferSize Size of message buffer, must be of LORAMAC_BUFFER_SIZE.
 * \param payloadSize Size of the payload in bytes.
 * \param type LoRa messsage type.
 *
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small.
 */
uint8_t LoRaMac_PutPayload( uint8_t* buf, size_t bufSize, size_t payloadSize,
        LoRaMac_MsgType_t type, uint32_t addr, uint32_t seqCntr, uint8_t *key,
        bool isMulticast );

/*!
 * \brief
 *
 * \param [IN] cmd
 * \param [IN] args
 * \param [IN] argsSize
 */
uint8_t LoRaMac_AddCommand( uint8_t cmd, uint8_t *args, size_t argsSize );

/*!
 * Processes received MAC commands.
 *
 * \Remark MAC layer internal function
 *
 * \param [in] payload Pointer to the rx packet payload.
 * \param [in] macIndex Index of the MAC command to be processed.
 * \param [in] commandsSize Size of MAC commands to be processed.
 */
void LoRaMac_ProcessCommands( uint8_t *payload, uint8_t macIndex, uint8_t commandsSize );

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

#endif /* __LORAMAC_H_ */
