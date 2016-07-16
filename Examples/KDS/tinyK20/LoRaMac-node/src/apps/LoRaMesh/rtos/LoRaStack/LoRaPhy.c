/**
 * \file LoRaPhy.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 03.12.2015
 * \version 1.0
 *
 * \brief LoRa stack physical layer implementation
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "LoRaMesh.h"
#include "LoRaPhy.h"

#define LOG_LEVEL_ERROR
#include "debug.h"
/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
/*! Class A&B receive delay in us  */
#define RECEIVE_DELAY1                      (LORAMESH_CONFIG_RECEIVE_DELAY1)
#define RECEIVE_DELAY2                      (LORAMESH_CONFIG_RECEIVE_DELAY2)

/*! Join accept receive delay in us */
#define JOIN_ACCEPT_DELAY1                  (LORAMESH_CONFIG_JOIN_ACCEPT_DELAY1)
#define JOIN_ACCEPT_DELAY2                  (LORAMESH_CONFIG_JOIN_ACCEPT_DELAY2)

/*! Class A&B maximum receive window delay in us */
#define MAX_RX_WINDOW                       (LORAMESH_CONFIG_MAX_RX_WINDOW)

/*! Tx timeout */
#define TX_TIMEOUT                          (LORAMESH_CONFIG_TX_TIMEOUT)

/* Advertising constants */
#define ADV_CHANNEL_FREQUENCY               (LORAMESH_CONFIG_ADV_CHANNEL_FREQUENCY)
#define ADV_DATARATE                        (LORAMESH_CONFIG_ADV_DATARATE)
#define ADV_TX_POWER                        (LORAMESH_CONFIG_ADV_TX_POWER)
#define ADV_INTERVAL                        (LORAMESH_CONFIG_ADV_INTERVAL)
#define ADV_SLOT_DURATION                   (LORAMESH_CONFIG_ADV_SLOT_DURATION)
#define ADV_EXPLICIT_HDR_OFF                (LORAMESH_CONFIG_ADV_EXPLICIT_HDR_OFF)
#define ADV_PACKET_LEN                      (LORAMESH_CONFIG_ADV_PACKET_LEN)
#define ADV_CRC_ON                          (LORAMESH_CONFIG_ADV_CRC_ON)

/* Configuration for tx and rx queues */
#define MSG_QUEUE_RX_NOF_ITEMS              (LORAMESH_CONFIG_MSG_QUEUE_RX_LENGTH) /* number of items in the queue */
#define MSG_QUEUE_TX_NOF_ITEMS              (LORAMESH_CONFIG_MSG_QUEUE_TX_LENGTH) /* number of items in the queue */
#define MSG_QUEUE_PUT_WAIT                  (LORAMESH_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS) /* blocking time for putting messages into queue */

#define LORAPHY_TXTYPE_ADVERTISING          (0)
#define LORAPHY_TXTYPE_REGULAR              (1)
#define LORAPHY_TXTYPE_MULTICAST            (2)

#define LORAPHY_RXSLOT_ADVERTISING          (0)
#define LORAPHY_RXSLOT_RX1WINDOW            (1)
#define LORAPHY_RXSLOT_RX2WINDOW            (2)
#define LORAPHY_RXSLOT_TIME_SYNCHRONIZED    (3)

/*******************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ******************************************************************************/
typedef union {
    uint8_t Value;
    struct {
        uint8_t TxDone :1; /* 1: Tx done */
        uint8_t TxType :2; /* Transmission type
         *   0: Advertising
         *   1: Regular (Open Rx1 & Rx2 windows)
         *   2: Multicast (No Rx windows)
         */
        uint8_t RxDone :1; /* 1: Rx done */
        uint8_t RxSlot :2; /* Reception window open
         *   0: Advertising
         *   1: Rx1
         *   2: Rx2
         *   3: Synch Rx
         */
        uint8_t reserved :2;
    } Bits;
} LoRaPhy_Flags_t;

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
/*! Radio events function pointer */
static RadioEvents_t radioEvents;

/*! LoRaPhy Rx message queue handler */
static xQueueHandle msgRxQueue;

/*! LoRaPhy Tx message queue handler */
static xQueueHandle msgTxQueue;

/*! LoRaPhy application status */
static LoRaPhy_AppStatus_t phyStatus = PHY_INITIAL_STATE;

/*! LoRaPhy flags structure */
static LoRaPhy_Flags_t phyFlags;

/* Incoming packet descriptor */
static LoRaPhy_PacketDesc rxPacket;

/* Incoming packet buffer */
static uint8_t rxPacketBuffer[LORAPHY_BUFFER_SIZE];

/*! LoRaPhy reception windows delay from end of Tx */
static uint32_t ReceiveDelay1;
static uint32_t ReceiveDelay2;
static uint32_t JoinAcceptDelay1;
static uint32_t JoinAcceptDelay2;

/* Reception windows parameters */
static uint8_t Rx1DrOffset;
static uint8_t Rx2Dr;
static uint32_t Rx2ChannelFrequency;

/*! LoRa maximum time a reception window stays open */
static uint32_t MaxRxWindow;

/*! Agregated duty cycle management */
static uint16_t MaxDCycle = 0;
static uint16_t AggregatedDCycle = 0;
static TimerTime_t AggregatedLastTxDoneTime = 0;
static TimerTime_t AggregatedTimeOff = 0;

/*! LoRaPhy bands */
static LoRaPhy_Band_t Bands[LORA_MAX_NB_BANDS] = { BAND0, BAND1, BAND2, BAND3, BAND4, };

/*! LoRaPhy channels */
static LoRaPhy_ChannelParams_t Channels[LORA_MAX_NB_CHANNELS] = { LC1, LC2, LC3, LC4, LC5, LC6, LC7,
        LC8, LC9, };

/*! Last transmission time on air */
static TimerTime_t TxTimeOnAir = 0;

/*! LoRaPhy reception window timers */
static TimerEvent_t RxWindow1Timer;
static TimerEvent_t RxWindow2Timer;

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
/*! \brief Handles the transmission process */
static void HandleStateMachine( void );

/*! \brief Retrieves outgoing message from tx queue */
static uint8_t GetTxMsg( uint8_t *buf, size_t bufSize );

/*! \brief Retrieves incoming message from rx queue */
static uint8_t GetRxMsg( uint8_t *buf, size_t bufSize );

/*! \brief Adds an element to rx or tx queue */
static uint8_t QueuePut( uint8_t *buf, size_t bufSize, size_t payloadSize, bool fromISR, bool isTx,
        bool toBack, uint8_t flags );

/*! \brief Check if tx queue contains any messages and send them if so */
static uint8_t CheckTx( void );

/*! \brief Sets up and opens a reception window with the specified settings */
static void OpenReceptionWindow( uint32_t freq, int8_t datarate, uint32_t bandwidth,
        uint16_t timeout, bool rxContinuous );

/*! \brief Sets next transmission channel */
static uint8_t SetNextChannel( void );

/*! \brief Function to be executed on Radio Tx Done event */
static void OnRadioTxDone( void );

/*! \brief Function to be executed on Radio Rx Done event */
static void OnRadioRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );

/*! \brief Function to be executed on Radio Cad Done event */
static void OnCadDone( bool channelActivityDetected );

/*! \brief Function executed on Radio Tx Timeout event */
static void OnRadioTxTimeout( void );

/*! \brief Function executed on Radio Rx error event */
static void OnRadioRxError( void );

/*! \brief Function executed on Radio Rx Timeout event */
static void OnRadioRxTimeout( void );

/*! Function executed on first Rx window timer event */
static void OnRxWindow1TimerEvent( TimerHandle_t xTimer );

/*! Function executed on second Rx window timer event */
static void OnRxWindow2TimerEvent( TimerHandle_t xTimer );

/*******************************************************************************
 * API FUNCTIONS (PUBLIC)
 ******************************************************************************/
void LoRaPhy_Init( void )
{
    /* Initialize structures */
    msgRxQueue = xQueueCreate(MSG_QUEUE_RX_NOF_ITEMS, LORAPHY_BUFFER_SIZE);
    if ( msgRxQueue == NULL ) { /* queue creation failed! */
        LOG_ERROR("Could not create Rx queue at %s line %d", __FILE__,
        __LINE__);
        for ( ;; ) {
        } /* not enough memory? */
    }
    vQueueAddToRegistry(msgRxQueue, "RadioRxMsg");

    msgTxQueue = xQueueCreate(MSG_QUEUE_TX_NOF_ITEMS, LORAPHY_BUFFER_SIZE);
    if ( msgTxQueue == NULL ) { /* queue creation failed! */
        LOG_ERROR("Could not create Rx queue at %s line %d", __FILE__,
        __LINE__);
        for ( ;; ) {
        } /* not enough memory? */
    }
    vQueueAddToRegistry(msgTxQueue, "RadioTxMsg");

    /* Initialize phy flags structure */
    phyFlags.Value = 0U;

    /* Initialize rx window delays*/
    MaxRxWindow = MAX_RX_WINDOW;
    ReceiveDelay1 = RECEIVE_DELAY1;
    ReceiveDelay2 = RECEIVE_DELAY2;
    JoinAcceptDelay1 = JOIN_ACCEPT_DELAY1;
    JoinAcceptDelay2 = JOIN_ACCEPT_DELAY2;

    pLoRaDevice->rxWindow1Delay = RECEIVE_DELAY1 - RADIO_WAKEUP_TIME;
    pLoRaDevice->rxWindow2Delay = RECEIVE_DELAY2 - RADIO_WAKEUP_TIME;

    /* Initialize advertising guard time */
    pLoRaDevice->advertisingSlot.Duration = ADV_SLOT_DURATION;
    pLoRaDevice->advertisingSlot.Interval = ADV_INTERVAL;
    pLoRaDevice->advertisingSlot.Time = 100;

    /* Initialize duty cycle variables */
    MaxDCycle = 0;
    AggregatedDCycle = 1;
    AggregatedLastTxDoneTime = 0;
    AggregatedTimeOff = 0;

    /* Reception window parameters */
    Rx1DrOffset = 0;
    Rx2Dr = DR_5;
    Rx2ChannelFrequency = 868100000;

    /* Default channels mask */
    pLoRaDevice->channelsMask[0] = LC(1) + LC(2) + LC(3);

    /* init Rx descriptor */
    rxPacket.phyData = &rxPacketBuffer[0];
    rxPacket.phySize = sizeof(rxPacketBuffer);
    rxPacket.rxtx = LORAPHY_BUF_PAYLOAD_START(rxPacket.phyData); /* we transmit the size too */

    /*
     * Initialize Timers
     */
    /* RX1 delay timer & config */
    TimerInit(&RxWindow1Timer, "RxWindow1Timer", (void*) NULL, OnRxWindow1TimerEvent, false);
    /* RX2 delay timer & config */
    TimerInit(&RxWindow2Timer, "RxWindow2Timer", (void*) NULL, OnRxWindow2TimerEvent, false);

    /* Initialize Radio driver */
    radioEvents.CadDone = OnCadDone;
    radioEvents.TxDone = OnRadioTxDone;
    radioEvents.RxDone = OnRadioRxDone;
    radioEvents.RxError = OnRadioRxError;
    radioEvents.TxTimeout = OnRadioTxTimeout;
    radioEvents.RxTimeout = OnRadioRxTimeout;
    Radio.Init(&radioEvents);
}

uint8_t LoRaPhy_Process( void )
{
    uint8_t result;

    HandleStateMachine(); /* process state machine */
    /* process rx message */
    result = GetRxMsg(rxPacket.phyData, rxPacket.phySize);
    if ( result == ERR_OK ) {
        /* Handle incoming packet */
        if ( LoRaPhy_OnPacketRx(&rxPacket) == ERR_OK ) {
            /* Packet handled */
        }
    }
    return ERR_OK;
}

uint8_t LoRaPhy_PutPayload( uint8_t *buf, size_t bufSize, size_t payloadSize, uint8_t flags )
{
    return QueuePut(buf, bufSize, payloadSize, false, true, true, flags);
}

uint8_t LoRaPhy_OnPacketRx( LoRaPhy_PacketDesc *packet )
{
#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
    LOG_TRACE("%s - Size %d", __FUNCTION__, LORAPHY_BUF_SIZE(packet->phyData));
    LOG_TRACE_BARE("\t");
    for ( uint8_t i = 0; i < (LORAPHY_BUF_SIZE(packet->phyData) + 2); i++ )
    LOG_TRACE_BARE("0x%02x ", packet->phyData[i]);
    LOG_TRACE_BARE("\r\n");
#endif

    return LoRaMac_OnPacketRx(packet); /* Pass message up the stack */
}

uint32_t LoRaPhy_GenerateNonce( void )
{
    return Radio.Random();
}

/*******************************************************************************
 * SETUP FUNCTIONS (PUBLIC)
 ******************************************************************************/
void LoRaPhy_GetChannels( LoRaPhy_ChannelParams_t* channels )
{
    for ( uint8_t i = 0; i < LORA_MAX_NB_CHANNELS; i++ ) {
        channels[i] = Channels[i];
    }
}
void LoRaPhy_SetChannel( uint8_t id, LoRaPhy_ChannelParams_t params )
{
    params.Band = 0;
    Channels[id] = params;
    // Activate the newly created channel
    if ( id < 16 ) {
        pLoRaDevice->channelsMask[0] |= 1 << id;
    } else if ( id < 32 ) {
        pLoRaDevice->channelsMask[1] |= 1 << (id - 16);
    } else if ( id < 48 ) {
        pLoRaDevice->channelsMask[2] |= 1 << (id - 32);
    } else if ( id < 64 ) {
        pLoRaDevice->channelsMask[3] |= 1 << (id - 48);
    } else if ( id < 72 ) {
        pLoRaDevice->channelsMask[4] |= 1 << (id - 64);
    } else {
        // Don't activate the channel
    }

    if ( (Channels[id].Frequency >= 865000000) && (Channels[id].Frequency <= 868000000) ) {
        if ( Channels[id].Band != BAND_G1_0 ) {
            Channels[id].Band = BAND_G1_0;
        }
    } else if ( (Channels[id].Frequency > 868000000) && (Channels[id].Frequency <= 868600000) ) {
        if ( Channels[id].Band != BAND_G1_1 ) {
            Channels[id].Band = BAND_G1_1;
        }
    } else if ( (Channels[id].Frequency >= 868700000) && (Channels[id].Frequency <= 869200000) ) {
        if ( Channels[id].Band != BAND_G1_2 ) {
            Channels[id].Band = BAND_G1_2;
        }
    } else if ( (Channels[id].Frequency >= 869400000) && (Channels[id].Frequency <= 869650000) ) {
        if ( Channels[id].Band != BAND_G1_3 ) {
            Channels[id].Band = BAND_G1_3;
        }
    } else if ( (Channels[id].Frequency >= 869700000) && (Channels[id].Frequency <= 870000000) ) {
        if ( Channels[id].Band != BAND_G1_4 ) {
            Channels[id].Band = BAND_G1_4;
        }
    } else {
        Channels[id].Frequency = 0;
        Channels[id].DrRange.Value = 0;
    }

    // Check if it is a valid channel
    if ( Channels[id].Frequency == 0 ) {
        LoRaPhy_ChannelRemove(id);
    }
}

void LoRaPhy_ChannelRemove( uint8_t id )
{
    if ( phyStatus != PHY_IDLE ) {
        return;
    }
    if ( id < 3 ) {
        return;
    }

    uint8_t index = 0;
    index = id / 16;

    if ( (index > 4) || (id >= LORA_MAX_NB_CHANNELS) ) {
        return;
    }

    // Deactivate channel
    pLoRaDevice->channelsMask[index] &= ~(1 << (id % 16));

    return;
}

void LoRaPhy_SetMaxRxWindow( uint32_t delay )
{
    MaxRxWindow = delay;
}

void LoRaPhy_SetReceiveDelay1( uint32_t delay )
{
    ReceiveDelay1 = delay;
}

void LoRaPhy_SetReceiveDelay2( uint32_t delay )
{
    ReceiveDelay2 = delay;
}

void LoRaPhy_SetJoinAcceptDelay1( uint32_t delay )
{
    JoinAcceptDelay1 = delay;
}

void LoRaPhy_SetJoinAcceptDelay2( uint32_t delay )
{
    JoinAcceptDelay2 = delay;
}

void LoRaPhy_SetMaxDutyCycle( uint8_t maxDCycle )
{
    if ( maxDCycle >= 0 && maxDCycle < 16 ) {
        MaxDCycle = maxDCycle;
        AggregatedDCycle = 1 << maxDCycle;
    }
}

void LoRaPhy_SetDownLinkSettings( uint8_t rx1DrOffset, uint8_t rx2Dr )
{

    Rx1DrOffset = rx1DrOffset;
    Rx2Dr = rx2Dr;
}

void LoRaPhy_SetRxParameters( uint8_t rx1DrOffset, uint8_t rx2Dr, uint32_t rx2Freq )
{
    LoRaPhy_SetDownLinkSettings(rx1DrOffset, rx2Dr);
    Rx2ChannelFrequency = rx2Freq;
}

uint32_t LoRaPhy_GetChannelFrequency( uint8_t channel )
{
    if ( channel < 0 || channel > (sizeof(Channels) / sizeof(LoRaPhy_ChannelParams_t)) ) return 0;

    return Channels[channel].Frequency;
}

uint8_t LoRaPhy_GetChannelIndex( uint32_t frequency )
{
    if ( frequency < 863000000 || frequency > 870000000 ) return 0;

    for ( uint8_t i = 0; i < LORA_MAX_NB_CHANNELS; i++ ) {
        if ( frequency == Channels[i].Frequency ) return i;
    }
    return 0xFF;
}

/*******************************************************************************
 * TEST FUNCTION PROTOTYPES (PUBLIC) (FOR DEBUG PURPOSES ONLY)
 ******************************************************************************/
uint8_t LoRaPhy_TestSetContinuousTx( void )
{
    Radio.SetTxConfig(MODEM_LORA, 14, 0, 0, 7, 1, 8, false, true, 0, 0, false, 3000000);
    // Sets the radio in Tx mode
    Radio.Send(NULL, 0);
    return ERR_OK;
}

uint8_t LoRaPhy_TestSetContinuousRx( uint32_t freq, uint8_t dr )
{
    uint32_t bandwidth = 0;     // 0: 125 kHz
    uint16_t symbTimeout = 5;     // DR_2, DR_1, DR_0

    if ( dr >= DR_3 ) {   // DR_6, DR_5, DR_4, DR_3
        symbTimeout = 8;
    }
    if ( dr == DR_6 ) {   // LoRa 250 kHz
        bandwidth = 1;
    }

    OpenReceptionWindow(freq, dr, bandwidth, symbTimeout, true);
    return ERR_OK;
}

uint8_t LoRaPhy_QueueRxMessage( uint8_t *payload, size_t payloadSize, bool toBack, uint8_t flags )
{
    return QueuePut(payload, LORAPHY_BUFFER_SIZE, payloadSize, false, false, toBack, flags);
}

uint8_t LoRaPhy_TestSendFrame( uint8_t *buf, size_t bufSize )
{
    Radio.SetChannel(Channels[pLoRaDevice->currChannelIndex].Frequency);
    Radio.SetMaxPayloadLength(MODEM_LORA, bufSize);

    if ( pLoRaDevice->currDataRateIndex == DR_7 ) {   // High Speed FSK channel
        Radio.SetTxConfig(MODEM_FSK, TxPowers[pLoRaDevice->currTxPowerIndex], 25e3, 0,
                Datarates[pLoRaDevice->currDataRateIndex] * 1e3, 0, 5, false, true, 0, 0, false,
                3e6);
    } else if ( pLoRaDevice->currDataRateIndex == DR_6 ) {   // High speed LoRa channel
        Radio.SetTxConfig(MODEM_LORA, TxPowers[pLoRaDevice->currTxPowerIndex], 0, 1,
                Datarates[pLoRaDevice->currDataRateIndex], 1, 8, false, true, 0, 0, false, 3e6);
    } else {   // Normal LoRa channel
        Radio.SetTxConfig(MODEM_LORA, TxPowers[pLoRaDevice->currTxPowerIndex], 0, 0,
                Datarates[pLoRaDevice->currDataRateIndex], 1, 8, false, true, 0, 0, false, 3e6);
    }

    // Send now
    Radio.Send(buf, bufSize);
    return ERR_OK;
}

uint8_t LoRaPhy_TestOpenRxWindow( uint8_t ch, uint8_t datarate )
{
    uint32_t bandwidth = 0;     // 0: 125 kHz
    uint16_t symbTimeout = 5;   // DR_2, DR_1, DR_0

    if ( datarate >= DR_3 ) {   // DR_6, DR_5, DR_4, DR_3
        symbTimeout = 16;
    }
    if ( datarate == DR_6 ) {   // LoRa 250 kHz
        bandwidth = 1;
    }

    OpenReceptionWindow(Channels[ch].Frequency, datarate, bandwidth, symbTimeout, false);
    return ERR_OK;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
/*!
 * Physical layer state machine implementation
 */
static void HandleStateMachine()
{
    uint8_t result;

    for ( ;; ) {
        switch ( phyStatus ) {
            case PHY_INITIAL_STATE:
                LOG_TRACE("Radio reset.");
                Radio.Reset();
                /* Random seed initialization */
                srand1(Radio.Random());
                if ( pLoRaDevice->devClass != CLASS_C ) {
                    LOG_TRACE("Radio idle.");
                    phyStatus = PHY_IDLE;
                } else {
                    LOG_TRACE("Radio receiving.");
                    phyStatus = PHY_RECEIVING;
                }
                break;
            case PHY_POWER_DOWN:
                Radio.Sleep();
                LOG_TRACE("Radio idle.");
                phyStatus = PHY_IDLE;
                return;
            case PHY_IDLE:
            {
                result = CheckTx();
                if ( result == ERR_OK ) { /* there was data and it has been sent */
                    phyStatus = PHY_WAIT_FOR_TXDONE;
                    LOG_TRACE("Radio wait tx done.");
                    break; /* process switch again */
                }
                return;
            }
            case PHY_WAIT_FOR_TXDONE:
                if ( phyFlags.Bits.TxDone == 1 ) {
                    phyFlags.Bits.TxDone = 0;
                    if ( pLoRaDevice->devClass != CLASS_C ) {
                        LOG_TRACE("Tx done. Radio power down.");
                        phyStatus = PHY_POWER_DOWN;
                    } else {
                        LOG_TRACE("Radio receiving.");
                        phyStatus = PHY_RECEIVING;
                    }
                    break;
                }
                return;
            case PHY_RECEIVING:
                if ( phyFlags.Bits.RxDone == 1 ) {
                    phyFlags.Bits.RxDone = 0;
                    LOG_TRACE("Rx done. Radio power down.");
                    phyStatus = PHY_POWER_DOWN;
                    break;
                }
                /* Reception window open */
                return;
            case PHY_ADVERTISING:
                return;
            case PHY_TIMEOUT:
                phyStatus = PHY_POWER_DOWN;
                LOG_TRACE("Radio timeout. Radio power down.");
                break;
            case PHY_ERROR:
                phyStatus = PHY_POWER_DOWN;
                LOG_TRACE("Radio error. Radio power down.");
                break;
            default:
                return;
        }
    }
}

/*!
 * \brief Retrieve outgoing message from tx queue.
 *
 * \param buf Pointer to the buffer to which the message will be copied.
 * \param bufSize Size of the target buffer.
 */
static uint8_t GetTxMsg( uint8_t *buf, size_t bufSize )
{
    if ( bufSize < LORAPHY_BUFFER_SIZE ) {
        return ERR_OVERFLOW; /* not enough space in buffer */
    }
    if ( xQueueReceive(msgTxQueue, buf, 0) == pdPASS ) {
        /* received message from queue */
#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
        LOG_TRACE("LoRaPhy %s - Size %d", __FUNCTION__, LORAPHY_BUF_SIZE(buf));
        LOG_TRACE_BARE("\t");
        for ( uint8_t i = 0; i < (LORAPHY_BUF_SIZE(buf) + 2); i++ )
        LOG_TRACE_BARE("0x%02x ", buf[i]);
        LOG_TRACE_BARE("\r\n");
#endif
        return ERR_OK;
    }
    return ERR_RXEMPTY;
}

/*!
 * \brief Retrieve incoming message from rx queue.
 *
 * \param buf Pointer to the buffer to which the message will be copied.
 * \param bufSize Size of the target buffer.
 */
static uint8_t GetRxMsg( uint8_t *buf, size_t bufSize )
{
    /* first byte in the queue is the size of the item */
    if ( bufSize < LORAPHY_BUFFER_SIZE ) {
        return ERR_OVERFLOW; /* not enough space in buffer */
    }
    if ( xQueueReceive(msgRxQueue, buf, 0) == pdPASS ) { /* immediately returns if queue is empty */
        /* received message from queue */
        return ERR_OK;
    }
    return ERR_RXEMPTY;
}

/*!
 * \brief Queues a message to be sent to the radio transceiver.
 *
 * \param buf Pointer to the message data to be sent.
 * \param bufSize Size of buffer.
 * \param payloadSize Size of payload data.
 * \param fromISR If called from an ISR routine.
 * \param isTx If message is TX or RX.
 * \param flags Packet flags.
 *
 * \return Error code, ERR_OK if message has been queued.
 */
static uint8_t QueuePut( uint8_t *buf, size_t bufSize, size_t payloadSize, bool fromISR, bool isTx,
        bool toBack, uint8_t flags )
{
    /* data format is: dataSize(8bit) data */
    uint8_t res = ERR_OK;
    xQueueHandle queue;
    BaseType_t qRes;

    if ( bufSize != LORAPHY_BUFFER_SIZE ) {
        return ERR_OVERFLOW; /* must be exactly this buffer size!!! */
    }

    if ( isTx ) {
        queue = msgTxQueue;
    } else {
        queue = msgRxQueue;
    }

    LORAPHY_BUF_FLAGS(buf) = flags;
    LORAPHY_BUF_SIZE(buf) = (uint8_t) payloadSize;

#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
    LOG_TRACE("LoRaPhy %s - Size %d", __FUNCTION__, payloadSize);
    LOG_TRACE_BARE("\t");
    for ( uint8_t i = 0; i < (payloadSize + 2); i++ )
    LOG_TRACE_BARE("0x%02x ", buf[i]);
    LOG_TRACE_BARE("\r\n");
#endif

    if ( fromISR ) {
        signed portBASE_TYPE
        pxHigherPriorityTaskWoken;

        if ( toBack ) {
            qRes = xQueueSendToBackFromISR(queue, buf, &pxHigherPriorityTaskWoken);
        } else {
            qRes = xQueueSendToFrontFromISR(queue, buf, &pxHigherPriorityTaskWoken);
        }
        if ( qRes != pdTRUE ) {
            /* was not able to send to the queue. Well, not much we can do here... */
            res = ERR_BUSY;
        }
    } else {
        if ( toBack ) {
            qRes = xQueueSendToBack(queue, buf, MSG_QUEUE_PUT_WAIT);
        } else {
            qRes = xQueueSendToFront(queue, buf, MSG_QUEUE_PUT_WAIT);
        }
        if ( qRes != pdTRUE ) {
            res = ERR_BUSY;
        }
    }
    return res;
}

/*!
 * Check tx message queue to see if any messages are pending.
 *
 * \retvalue    ERR_OK          Transmission started successfully.
 *              ERR_NOTAVAIL    No channel available.
 *              ERR_VALUE       Invalid tx type selected.
 *              ERR_DISABLED    Device was remotely disable (MaxDCycle setting).
 *              ERR_RXEMPTY     Message queue is empty.
 */
static uint8_t CheckTx( void )
{
    LoRaPhy_ChannelParams_t channel;
    uint8_t flags;
    uint8_t TxDataBuffer[LORAPHY_BUFFER_SIZE];

    if ( GetTxMsg(TxDataBuffer, sizeof(TxDataBuffer)) == ERR_OK ) {
#if 0
        if ( SetNextChannel() != ERR_OK ) {
            return ERR_NOTAVAIL;
        }
#endif
        flags = LORAPHY_BUF_FLAGS(TxDataBuffer);
        channel = Channels[pLoRaDevice->currChannelIndex];

        if ( flags & LORAPHY_PACKET_FLAGS_JOIN_REQ ) {
            pLoRaDevice->rxWindow1Delay = JoinAcceptDelay1 - RADIO_WAKEUP_TIME;
            pLoRaDevice->rxWindow2Delay = JoinAcceptDelay2 - RADIO_WAKEUP_TIME;
        } else {
            pLoRaDevice->rxWindow1Delay = ReceiveDelay1 - RADIO_WAKEUP_TIME;
            pLoRaDevice->rxWindow2Delay = ReceiveDelay2 - RADIO_WAKEUP_TIME;
        }

        Radio.SetChannel(channel.Frequency);
        Radio.SetMaxPayloadLength(MODEM_LORA, LORAPHY_BUF_SIZE(TxDataBuffer));

        if ( pLoRaDevice->currDataRateIndex == DR_7 ) {   // High Speed FSK channel
            Radio.SetTxConfig(MODEM_FSK, TxPowers[pLoRaDevice->currTxPowerIndex], 25e3, 0,
                    Datarates[pLoRaDevice->currDataRateIndex] * 1e3, 0, 5, false, true, 0, 0, false,
                    TX_TIMEOUT);
            TxTimeOnAir = Radio.TimeOnAir(MODEM_FSK, LORAPHY_BUF_SIZE(TxDataBuffer));
        } else if ( pLoRaDevice->currDataRateIndex == DR_6 ) {   // High speed LoRa channel
            Radio.SetTxConfig(MODEM_LORA, TxPowers[pLoRaDevice->currTxPowerIndex], 0, 1,
                    Datarates[pLoRaDevice->currDataRateIndex], 1, 8, false, true, 0, 0, false,
                    TX_TIMEOUT);
            TxTimeOnAir = Radio.TimeOnAir(MODEM_LORA, LORAPHY_BUF_SIZE(TxDataBuffer));
        } else {   // Normal LoRa channel
            Radio.SetTxConfig(MODEM_LORA, TxPowers[pLoRaDevice->currTxPowerIndex], 0, 0,
                    Datarates[pLoRaDevice->currDataRateIndex], 1, 8, false, true, 0, 0, false,
                    TX_TIMEOUT);
            TxTimeOnAir = Radio.TimeOnAir(MODEM_LORA, LORAPHY_BUF_SIZE(TxDataBuffer));
        }

        if ( MaxDCycle == 255 ) {
            return ERR_DISABLED;
        }
        if ( MaxDCycle == 0 ) {
            AggregatedTimeOff = 0;
        }

        if ( MAX(Bands[channel.Band].TimeOff, AggregatedTimeOff) > (TimerGetCurrentTime()) ) {
            // Schedule transmission
            LOG_TRACE("Send in %d ticks on channel %d (DR: %u).",
                    MAX(Bands[channel.Band].TimeOff, AggregatedTimeOff), channel.Frequency,
                    pLoRaDevice->currDataRateIndex);
            vTaskDelay(
                    MAX(Bands[channel.Band].TimeOff, AggregatedTimeOff)
                            / MAX(Bands[channel.Band].TimeOff, AggregatedTimeOff));
        } else {
            // Send now
            LOG_TRACE("Sending at %u ms on channel %d (DR: %u).",
                    (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS), channel.Frequency,
                    pLoRaDevice->currDataRateIndex);
            Radio.Send(LORAPHY_BUF_PAYLOAD_START(TxDataBuffer), LORAPHY_BUF_SIZE(TxDataBuffer));
//            LOG_DEBUG("Send data on channel with frequency %u Hz", channel.Frequency);
        }

        if ( (flags & LORAPHY_PACKET_FLAGS_FRM_MASK) == LORAPHY_PACKET_FLAGS_FRM_ADVERTISING ) {
            phyFlags.Bits.TxType = LORAPHY_TXTYPE_ADVERTISING;
        } else if ( (flags & LORAPHY_PACKET_FLAGS_FRM_MASK) == LORAPHY_PACKET_FLAGS_FRM_REGULAR ) {
            phyFlags.Bits.TxType = LORAPHY_TXTYPE_REGULAR;
        } else if ( (flags & LORAPHY_PACKET_FLAGS_FRM_MASK)
                == LORAPHY_PACKET_FLAGS_FRM_MULTICAST ) {
            phyFlags.Bits.TxType = LORAPHY_TXTYPE_MULTICAST;
        } else {
            return ERR_VALUE;
        }

        return ERR_OK;
    }
    return ERR_NOTAVAIL; /* no data to send? */
}

/*!
 * Open up a reception window with specified settings.
 *
 * \param [IN] freq window channel frequency
 * \param [IN] datarate window channel datarate
 * \param [IN] bandwidth window channel bandwidth
 * \param [IN] timeout window channel timeout
 * \param [IN] windowType Type of reception window (Advertising or Regular)
 */
static void OpenReceptionWindow( uint32_t freq, int8_t datarate, uint32_t bandwidth,
        uint16_t timeout, bool rxContinuous )
{

    uint8_t downlinkDatarate = Datarates[datarate];
    RadioModems_t modem;

    if ( Radio.GetStatus() == RF_IDLE ) {
        Radio.SetChannel(freq);
        if ( datarate == DR_7 ) {
            modem = MODEM_FSK;
            Radio.SetRxConfig(MODEM_FSK, 50e3, downlinkDatarate * 1e3, 0, 83.333e3, 5, 0, false, 0,
                    true, 0, 0, false, rxContinuous);
        } else {
            modem = MODEM_LORA;
            Radio.SetRxConfig(MODEM_LORA, bandwidth, downlinkDatarate, 1, 0, 8, timeout, false, 0,
                    true, 0, 0, false, rxContinuous);
        }

        Radio.SetMaxPayloadLength(modem, MaxPayloadByDatarate[datarate]);

        if ( rxContinuous == false ) {
            Radio.Rx(MaxRxWindow);
        } else {
            Radio.Rx(0);   // Continuous mode
        }
        phyStatus = PHY_RECEIVING;
//        LOG_DEBUG("Open reception window on frequency %u Hz", freq);
    }
}

/*
 * Set next transmission channel according to duty cycle boundries
 * unless it is a scheduled transmission on a specific channel (Class D)
 *
 * \return ERR_OK if a channel was set successfully
 */
static uint8_t SetNextChannel( void )
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    uint8_t nbEnabledChannels = 0;
    uint8_t enabledChannels[LORA_MAX_NB_CHANNELS];
    TimerTime_t curTime = TimerGetCurrentTime();

    memset1(enabledChannels, 0, LORA_MAX_NB_CHANNELS);

// Update Aggregated duty cycle
    if ( AggregatedTimeOff < (curTime - AggregatedLastTxDoneTime) ) {
        AggregatedTimeOff = 0;
    }

// Update bands Time OFF
    TimerTime_t minTime = (TimerTime_t)(-1);
    for ( i = 0; i < LORA_MAX_NB_BANDS; i++ ) {
        if ( pLoRaDevice->dbgFlags.Bits.dutyCycleCtrlOff == 0 ) {
            if ( Bands[i].TimeOff < (curTime - Bands[i].LastTxDoneTime) ) {
                Bands[i].TimeOff = 0;
            }
            if ( Bands[i].TimeOff != 0 ) {
                minTime = MIN(Bands[i].TimeOff, minTime);
            }
        } else {
            minTime = 0;
            Bands[i].TimeOff = 0;
        }
    }

// Search how many channels are enabled
    for ( i = 0, k = 0; i < LORA_MAX_NB_CHANNELS; i += 16, k++ ) {
        for ( j = 0; j < 16; j++ ) {
            if ( (pLoRaDevice->channelsMask[k] & (1 << j)) != 0 ) {
                if ( Channels[i + j].Frequency == 0 ) {   // Check if the channel is enabled
                    continue;
                }
                if ( ((Channels[i + j].DrRange.Fields.Min <= pLoRaDevice->currChannelIndex)
                        && (pLoRaDevice->currDataRateIndex <= Channels[i + j].DrRange.Fields.Max))
                        == false ) {   // Check if the current channel selection supports the given datarate
                    continue;
                }
                if ( Bands[Channels[i + j].Band].TimeOff > 0 ) {   // Check if the band is available for transmission
                    continue;
                }
                if ( AggregatedTimeOff > 0 ) {   // Check if there is time available for transmission
                    continue;
                }
                enabledChannels[nbEnabledChannels++] = i + j;
            }
        }
    }
    if ( nbEnabledChannels > 0 ) {
        pLoRaDevice->currChannelIndex = enabledChannels[randr(0, nbEnabledChannels - 1)];
        return 0;
    }

    return ERR_OK;
}

static void OnRadioTxDone( void )
{
    TimerTime_t curTime = TimerGetCurrentTime();

    LOG_TRACE("Transmitted successfully (%u ms).", (uint32_t)(curTime * portTICK_PERIOD_MS));

// Update Band Time OFF
    Bands[Channels[pLoRaDevice->currChannelIndex].Band].LastTxDoneTime = curTime;
    if ( pLoRaDevice->dbgFlags.Bits.dutyCycleCtrlOff == 0 ) {
        Bands[Channels[pLoRaDevice->currChannelIndex].Band].TimeOff = TxTimeOnAir
                * Bands[Channels[pLoRaDevice->currChannelIndex].Band].DCycle - TxTimeOnAir;
    } else {
        Bands[Channels[pLoRaDevice->currChannelIndex].Band].TimeOff = 0;
    }
// Update Agregated Time OFF
    AggregatedLastTxDoneTime = curTime;
    AggregatedTimeOff = AggregatedTimeOff + (TxTimeOnAir * AggregatedDCycle - TxTimeOnAir);

    if ( phyFlags.Bits.TxType == LORAPHY_TXTYPE_ADVERTISING ) {
        /* Open advertising beacon reception window */

    } else if ( phyFlags.Bits.TxType == LORAPHY_TXTYPE_REGULAR
            && pLoRaDevice->dbgFlags.Bits.rxWindowsDisabled != 1 ) {
        TimerSetValue(&RxWindow1Timer, pLoRaDevice->rxWindow1Delay);
        TimerStart(&RxWindow1Timer);
        TimerSetValue(&RxWindow2Timer, pLoRaDevice->rxWindow2Delay);
        TimerStart(&RxWindow2Timer);
    } else {
        phyFlags.Bits.TxDone = 1;
    }

    /* Uplink message repetition is only valid for unconfirmed messages */
    if ( pLoRaDevice->ctrlFlags.Bits.ackPending == 0 ) {
        pLoRaDevice->nbRepCounter++;
    }
}

static void OnRadioRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    LoRaPhy_PacketDesc packet;

    LOG_DEBUG("Received %u bytes.", size);

    packet.flags = LORAPHY_PACKET_FLAGS_NONE;
    packet.phyData = payload;
    packet.rxtx = LORAPHY_BUF_PAYLOAD_START(packet.phyData);
    packet.phySize = LORAPHY_BUFFER_SIZE;

    if ( QueuePut(packet.phyData, packet.phySize, size, true, false, true, packet.flags)
            == ERR_OK ) {
        phyFlags.Bits.RxDone = 1;
    } else {
        LOG_ERROR("Failed to put received frame to queue.");
    }
}

static void OnCadDone( bool channelActivityDetected )
{
#if defined(LOG_LEVEL_TRACE)
    uint64_t curTime = TimerGetCurrentTime();
#endif
    Radio.Sleep();
    if ( !channelActivityDetected ) {
        LOG_TRACE("Channel clear. Send packet now (%d%d)", *(((int*) (&curTime)) + 1), curTime);
//        Radio.Send(LoRaMacBuffer, LoRaMacBufferPktLen);
    }
}

static void OnRadioTxTimeout( void )
{
    LOG_ERROR("Tx timeout occurred.");

    phyStatus = PHY_TIMEOUT;
    phyFlags.Bits.TxDone = 0;
}

static void OnRadioRxTimeout( void )
{
#if defined(LOG_LEVEL_TRACE)
    if ( phyFlags.Bits.RxSlot == 1 ) {
        LOG_TRACE("Receive window 1 timeout occurred at %u ms.",
                (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS));
    } else if ( phyFlags.Bits.RxSlot == 2 ) {
        LOG_TRACE("Receive window 2 timeout occurred at %u ms.",
                (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS));
    } else if ( phyFlags.Bits.RxSlot == 3 ) {
        LOG_TRACE("Time synchronized reception window timeout occurred.");
    }
#endif

    phyStatus = PHY_TIMEOUT;
    phyFlags.Bits.RxDone = 0;
}

static void OnRadioRxError( void )
{
    LOG_ERROR("Rx error occurred (Slot %d).", phyFlags.Bits.RxSlot);

    if ( pLoRaDevice->devClass != CLASS_C ) {
        Radio.Sleep();
    } else {
        OnRxWindow2TimerEvent (NULL);
    }
    if ( phyFlags.Bits.RxSlot == 2 ) {
        phyFlags.Bits.TxDone = 1;
    }

    phyStatus = PHY_ERROR;
}

static void OnRxWindow1TimerEvent( TimerHandle_t xTimer )
{
    uint16_t symbTimeout = 5;   // DR_2, DR_1, DR_0
    int8_t datarate = 0;
    uint32_t bandwidth = 0;   // LoRa 125 kHz

    TimerStop(&RxWindow1Timer);
    phyFlags.Bits.RxSlot = 1;

    datarate = pLoRaDevice->currDataRateIndex - Rx1DrOffset;
    if ( datarate < 0 ) {
        datarate = DR_0;
    }

// For higher datarates, we increase the number of symbols generating a Rx Timeout
    if ( datarate >= DR_3 ) {   // DR_6, DR_5, DR_4, DR_3
        symbTimeout = 8;
    }
    if ( datarate == DR_6 ) {   // LoRa 250 kHz
        bandwidth = 1;
    }
    LOG_TRACE("Open single Rx window 1 at %u ms (Channel : %u / DR: %u).",
            (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS),
            Channels[pLoRaDevice->currChannelIndex].Frequency, datarate);
    OpenReceptionWindow(Channels[pLoRaDevice->currChannelIndex].Frequency, datarate, bandwidth,
            symbTimeout, false);
}

static void OnRxWindow2TimerEvent( TimerHandle_t xTimer )
{
    uint16_t symbTimeout = 5;   // DR_2, DR_1, DR_0
    uint32_t bandwidth = 0;   // LoRa 125 kHz

    TimerStop(&RxWindow2Timer);
    phyFlags.Bits.RxSlot = 2;

    if ( pLoRaDevice->ctrlFlags.Bits.ackRequested == 1 ) {
//        TimerSetValue(&AckTimeoutTimer,
//                ACK_TIMEOUT + randr(-ACK_TIMEOUT_RND, ACK_TIMEOUT_RND));
//        TimerStart (&AckTimeoutTimer);
    }

// For higher datarates, we increase the number of symbols generating a Rx Timeout
    if ( Rx2Dr >= DR_3 ) {   // DR_6, DR_5, DR_4, DR_3
        symbTimeout = 8;
    }
    if ( Rx2Dr == DR_6 ) {   // LoRa 250 kHz
        bandwidth = 1;
    }

    if ( pLoRaDevice->devClass != CLASS_C ) {
        LOG_TRACE("Open single Rx window 2 at %u ms (Channel : %u / DR: %u).",
                (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS), Rx2ChannelFrequency, Rx2Dr);
        OpenReceptionWindow(Rx2ChannelFrequency, Rx2Dr, bandwidth, symbTimeout, false);
    } else {
        LOG_TRACE("Open continuous Rx window 2 at %u ms (Channel : %u / DR: %u).",
                (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS), Rx2ChannelFrequency, Rx2Dr);
        OpenReceptionWindow(Rx2ChannelFrequency, Rx2Dr, bandwidth, symbTimeout, true);
    }
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
