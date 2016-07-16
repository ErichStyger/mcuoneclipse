/**
 * \file LoRaPhy.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 12.11.2015
 * \version 1.0
 *
 * \brief LoRa stack physical layer implementation
 */

#ifndef __LORAPHY_H_
#define __LORAPHY_H_

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "LoRaMac-board.h"
#include "LoRaMesh-config.h"

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
/*!
 * Payload format is:
 *
 * PHY: <flags><size>|<phy payload>
 * MAC:               <mhdr><mac payload><mic>
 * FRM:                     <fhdr><fport><frm payload>
 * MSH:                                  <mesh payload>
 */
#define LORAPHY_HEADER_SIZE                     (2)
#define LORAPHY_PAYLOAD_SIZE                    (LORAMESH_CONFIG_TRANSCEIVER_PAYLOAD_SIZE)
#define LORAPHY_BUFFER_SIZE                     (LORAPHY_HEADER_SIZE+LORAPHY_PAYLOAD_SIZE)

/* PHY buffer access macros */
#define LORAPHY_BUF_IDX_FLAGS                   (0) /* <flags> index */
#define LORAPHY_BUF_IDX_SIZE                    (1) /* <size> index */
#define LORAPHY_BUF_IDX_PAYLOAD                 (2) /* <phy payload> index */

/* flag bits inside PacketDesc below */
#define LORAPHY_PACKET_FLAGS_NONE               (0)     /*!< initialization value */
#define LORAPHY_PACKET_FLAGS_FRM_REGULAR        (0<<0)  /*!< regular message received (down link) */
#define LORAPHY_PACKET_FLAGS_FRM_MULTICAST      (1<<0)  /*!< multicast received */
#define LORAPHY_PACKET_FLAGS_FRM_ADVERTISING    (2<<0)  /*!< advertising received */
#define LORAPHY_PACKET_FLAGS_JOIN_REQ           (1<<3)  /*!< join request message */
#define LORAPHY_PACKET_FLAGS_ACK_REQ            (1<<4)  /*!< acknowledge requested */

#define LORAPHY_PACKET_FLAGS_FRM_MASK           (0x3)

/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/
#define LORAPHY_BUF_FLAGS(phy)              ((phy)[LORAPHY_BUF_IDX_FLAGS])
#define LORAPHY_BUF_SIZE(phy)               ((phy)[LORAPHY_BUF_IDX_SIZE])
#define LORAPHY_BUF_PAYLOAD_START(phy)      ((phy) + LORAPHY_HEADER_SIZE)

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
typedef enum {
    PHY_INITIAL_STATE,
    PHY_POWER_DOWN,
    PHY_IDLE,
    PHY_WAIT_FOR_TXDONE,
    PHY_RECEIVING,
    PHY_ADVERTISING,
    PHY_TIMEOUT,
    PHY_ERROR
} LoRaPhy_AppStatus_t;

/*! */
typedef struct {
    int16_t Rssi;
    int8_t Snr;
} LoRaPhy_LastConnection_t;

/*! LoRaPhy channels parameters definition */
typedef union {
    int8_t Value;
    struct {
        int8_t Min :4;
        int8_t Max :4;
    } Fields;
} LoRaPhy_DrRange_t;

typedef struct {
    uint16_t DCycle;
    int8_t TxMaxPower;
    uint64_t LastTxDoneTime;
    uint64_t TimeOff;
} LoRaPhy_Band_t;

typedef struct {
    uint32_t Frequency;   // Hz
    LoRaPhy_DrRange_t DrRange;   // Max datarate [0: SF12, 1: SF11, 2: SF10, 3: SF9, 4: SF8, 5: SF7, 6: SF7, 7: FSK]
    // Min datarate [0: SF12, 1: SF11, 2: SF10, 3: SF9, 4: SF8, 5: SF7, 6: SF7, 7: FSK]
    uint8_t Band;        // Band index
} LoRaPhy_ChannelParams_t;

/*! Rx channel parameter structure */
typedef struct {
    uint32_t freq;      // Hz
    uint8_t datarate;   // [0: SF12, 1: SF11, 2: SF10, 3: SF9, 4: SF8, 5: SF7, 6: SF7, 7: FSK]
} LoRaPhy_RxChannelParams_t;

/*! Rx reception window type */
typedef enum {
    RX_TYPE_ADVERTISING, RX_TYPE_REGULAR
} LoRaPhy_RxWindowType_t;

/*! Tx config structure */
typedef struct {
    RadioModems_t modem;
    int8_t power;
    uint32_t fdev;
    uint32_t bandwidth;
    uint32_t datarate;
    uint8_t coderate;
    uint16_t preambleLen;
    bool fixLen;
    bool crcOn;
    bool FreqHopOn;
    uint8_t HopPeriod;
    bool iqInverted;
    uint32_t timeout;
} LoRaPhy_TxChannelParams_t;

typedef struct {
    uint8_t flags;/*!< flags, see LORAPHY_PACKET_FLAGS_XXXX above */
    uint8_t *phyData; /*!< pointer to the PHY data buffer */
    size_t phySize; /*!< size of PHY data buffer */
    uint8_t *rxtx; /*!< pointer into phyData, start of TX/RX data */
} LoRaPhy_PacketDesc;

/*******************************************************************************
 * API FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 * LoRa physical layer initialization.
 */
void LoRaPhy_Init( void );

/*!
 * LoRa physical layer process.
 */
uint8_t LoRaPhy_Process( void );

/*!
 * \brief
 *
 * \param packet Pointer to the packet descriptor
 * \return Error code, ERR_OK if everything is ok, ERR_OVERFLOW if buffer is too small.
 */
uint8_t LoRaPhy_OnPacketRx( LoRaPhy_PacketDesc *packet );

/*!
 * \brief Puts a packet into the queue to be sent.
 * \param buf Pointer to the packet buffer.
 * \param bufSize Size of the payload buffer.
 * \param payloadSize Size of payload data.
 * \return Error code, ERR_OK for everything fine.
 */
uint8_t LoRaPhy_PutPayload( uint8_t *buf, size_t bufSize, size_t payloadSize, uint8_t flags );

/*!
 *
 */
uint8_t LoRaPhy_ScheduleRxWindow();

/*!
 * Returns a radomly generated 16-bit value called nonce to generate session keys
 */
uint32_t LoRaPhy_GenerateNonce( void );

/*******************************************************************************
 * SETUP FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 *
 */
void LoRaPhy_GetChannels( LoRaPhy_ChannelParams_t* channels );

/*!
 * \brief
 *
 * \param id
 * \param params
 */
void LoRaPhy_SetChannel( uint8_t id, LoRaPhy_ChannelParams_t params );

/*!
 * \brief
 *
 * \param id
 */
void LoRaPhy_ChannelRemove( uint8_t id );

/*
 * \brief Maximal duration a reception window will be opened for
 *
 * \param duration Max. reception window duration in ms
 */
void LoRaPhy_SetMaxRxWindow( uint32_t duration );

/*
 * \brief Set the delay of the first reception window after Tx
 * of a regular message
 *
 * \param delay Delay in ms
 */
void LoRaPhy_SetReceiveDelay1( uint32_t delay );

/*!
 * \brief Set the delay of the second reception window after Tx
 * of a regular message
 *
 * \param delay Delay in ms
 */
void LoRaPhy_SetReceiveDelay2( uint32_t delay );

/*!
 * \brief Set the delay of the first reception window after Tx
 * of a join request message
 *
 * \param delay Delay in ms
 */
void LoRaPhy_SetJoinAcceptDelay1( uint32_t delay );

/*
 * \brief Sets the delay of the second reception window after Tx
 * of a join request message
 *
 * \param delay Delay in ms
 */
void LoRaPhy_SetJoinAcceptDelay2( uint32_t delay );

/*!
 * \brief Sets maximum aggregated transmit duty cycle of the end-device
 *
 * \param [IN] maxDCycle Maximum aggregated duty cycle
 */
void LoRaPhy_SetMaxDutyCycle( uint8_t maxDCycle );

/*!
 * \brief Set the delay of the second reception window after Tx
 *
 * \param rx1DrOffset Offset between up and down link
 * \param rx2Dr Data rate of second reception window
 */
void LoRaPhy_SetDownLinkSettings( uint8_t rx1DrOffset, uint8_t rx2Dr );

/*!
 * \brief Set the delay of the second reception window after Tx
 *
 * \param rx1DrOffset Offset between up and down link
 * \param rx2Dr Data rate of second reception window
 * \param rx2Freq
 */
void LoRaPhy_SetRxParameters( uint8_t rx1DrOffset, uint8_t rx2Dr, uint32_t rx2Freq );

uint32_t LoRaPhy_GetChannelFrequency( uint8_t channel );

uint8_t LoRaPhy_GetChannelIndex( uint32_t frequency );

/*******************************************************************************
 * TEST FUNCTION PROTOTYPES (PUBLIC) (FOR DEBUG PURPOSES ONLY)
 ******************************************************************************/
uint8_t LoRaPhy_TestSetContinuousTx( void );

uint8_t LoRaPhy_TestSetContinuousRx( uint32_t freq, uint8_t dr );

uint8_t LoRaPhy_TestSendFrame( uint8_t *buf, size_t bufSize );

uint8_t LoRaPhy_TestOpenRxWindow( uint8_t ch, uint8_t dr );

uint8_t LoRaPhy_QueueRxMessage( uint8_t *payload, size_t payloadSize, bool toBack, uint8_t flags );

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

#endif /* __LORAPHY_H_ */
