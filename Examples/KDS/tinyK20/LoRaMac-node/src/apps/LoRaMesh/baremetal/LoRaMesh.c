/**
 * \file LoRaMac.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 11.11.2015
 * \brief Mesh LoRa network implementation
 *
 */

#include "board.h"
#include <inttypes.h>

#include "LoRaMacCrypto.h"
#include "LoRaMesh.h"

#define LOG_LEVEL_TRACE
#include "debug.h"

/*****************************************************************************
 *                                                                           *
 * Local definitions                                                         *
 *                                                                           *
 *****************************************************************************/
/*!
 * Maximum PHY layer payload size
 */
#define LORAMAC_PHY_MAXPAYLOAD                      255

/*!
 * LoRaMac internal states
 */
enum LoRaMacState_e {
    MAC_IDLE = 0x00000000,
    MAC_TX_RUNNING = 0x00000001,
    MAC_RX = 0x00000002,
    MAC_ACK_REQ = 0x00000004,
    MAC_ACK_RETRY = 0x00000008,
    MAC_CHANNEL_CHECK = 0x00000010,
};

/*****************************************************************************
 *                                                                           *
 * Local variables                                                           *
 *                                                                           *
 *****************************************************************************/
/************* Initial Devie/Application Specific Variables ******************/
/*!
 * Device IEEE EUI
 */
static uint8_t *LoRaMacDevEui;

/*!
 * Application IEEE EUI
 */
static uint8_t *LoRaMacAppEui;

/*!
 * AES encryption/decryption cipher application key
 */
static uint8_t *LoRaMacAppKey;

/*!
 * Device nonce is a random value extracted by issuing a sequence of RSSI
 * measurements
 */
static uint16_t LoRaMacDevNonce;

/********************* Device Configuration Variables ************************/
/*!
 * Network ID ( 3 bytes )
 */
static uint32_t LoRaMacNetID;

/*!
 * Mote Address
 */
static uint32_t LoRaMacDevAddr;

/*!
 * Actual device class
 */
static DeviceClass_t LoRaMacDeviceClass;

/*********************** Packet Handling Variables ***************************/
/*!
 * Buffer containing the data to be sent or received.
 */
static uint8_t LoRaMacBuffer[LORAMAC_PHY_MAXPAYLOAD];

/*!
 * Length of packet in LoRaMacBuffer
 */
static uint16_t LoRaMacBufferPktLen = 0;

/*!
 * Buffer containing the upper layer data.
 */
static uint8_t LoRaMacPayload[LORAMAC_PHY_MAXPAYLOAD];
static uint8_t LoRaMacRxPayload[LORAMAC_PHY_MAXPAYLOAD];

/******************* Parent Node Connection Variables ************************/
/*!
 * AES encryption/decryption cipher network session key
 */
static uint8_t LoRaMacNwkSKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/*!
 * AES encryption/decryption cipher application session key
 */
static uint8_t LoRaMacAppSKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/*!
 * LoRaMAC frame counter. Each time a packet is sent the counter is incremented.
 * Only the 16 LSB bits are sent
 */
static uint32_t UpLinkCounter = 1;

/*!
 * LoRaMAC frame counter. Each time a packet is received the counter is incremented.
 * Only the 16 LSB bits are received
 */
static uint32_t DownLinkCounter = 0;

/************************** MAC Option Variables *****************************/
/*!
 * Indicates if the node is connected to a private or public network
 */
static bool PublicNetwork;

/*!
 * Indicates if the node supports repeaters
 */
static bool RepeaterSupport;

/*!
 * IsPacketCounterFixed enables the MIC field tests by fixing the
 * UpLinkCounter value
 */
static bool IsUpLinkCounterFixed = false;

/*!
 * Used for test purposes. Disables the opening of the reception windows.
 */
static bool IsRxWindowsEnabled = true;

/*!
 * Indicates if the MAC layer has already joined a network.
 */
static bool IsLoRaMacNetworkJoined = false;

/*!
 * LoRaMac ADR control status
 */
static bool AdrCtrlOn = false;

/************************* MAC Commands Variables ****************************/
/*!
 * Indicates if the MAC layer wants to send MAC commands
 */
static bool MacCommandsInNextTx = false;

/*!
 * Contains the current MacCommandsBuffer index
 */
static uint8_t MacCommandsBufferIndex = 0;

/*!
 * Buffer containing the MAC layer commands
 */
static uint8_t MacCommandsBuffer[15];

/*********************** Default LoRaMac Variables ***************************/
/*!
 * Data rates table definition
 */
const uint8_t Datarates[] = { 12, 11, 10, 9, 8, 7, 7, 50 };

/*!
 * Maximum payload with respect to the datarate index. Cannot operate with repeater.
 */
const uint8_t MaxPayloadOfDatarate[] = { 51, 51, 51, 115, 242, 242, 242, 242 };

/*!
 * Maximum payload with respect to the datarate index. Can operate with repeater.
 */
const uint8_t MaxPayloadOfDatarateRepeater[] = { 51, 51, 51, 115, 222, 222, 222, 222 };

/*!
 * Tx output powers table definition
 */
const int8_t TxPowers[] = { 20, 14, 11, 8, 5, 2 };

/*!
 * LoRaMac bands
 */
static Band_t Bands[LORA_MAX_NB_BANDS] = { BAND0, BAND1, BAND2, BAND3, BAND4, };

/*!
 * LoRaMAC channels
 */
static ChannelParams_t Channels[LORA_MAX_NB_CHANNELS] = { LC1, LC2, LC3, LC4, LC5, LC6, LC7, LC8,
        LC9, };

/*********************** Reception Window Variables **************************/
/*!
 * LoRaMAC 2nd reception window settings
 */
static Rx2ChannelParams_t Rx2Channel = RX_WND_2_CHANNEL;

/*!
 * Datarate offset between uplink and downlink on first window
 */
static uint8_t Rx1DrOffset = 0;

/*!
 * LoRaMac maximum time a reception window stays open
 */
static uint32_t MaxRxWindow;

/*************************** Channel Variables *******************************/
/*!
 * Mask indicating which channels are enabled
 */
static uint16_t ChannelsMask[6];

/*!
 * Channels Tx output power
 */
static int8_t ChannelsTxPower = LORAMAC_DEFAULT_TX_POWER;

/*!
 * Channels datarate
 */
static int8_t ChannelsDatarate = LORAMAC_DEFAULT_DATARATE;

/*!
 * Channels default datarate
 */
static int8_t ChannelsDefaultDatarate = LORAMAC_DEFAULT_DATARATE;

/*!
 * Number of uplink messages repetitions [1:15] (unconfirmed messages only)
 */
static uint8_t ChannelsNbRep = 1;

/*!
 * Uplink messages repetitions counter
 */
static uint8_t ChannelsNbRepCounter = 0;

/*!
 * Current channel index
 */
static uint8_t Channel;

/************************ MAC internal Variables *****************************/
/*!
 * LoRaMac internal state
 */
static uint32_t LoRaMacState = MAC_IDLE;

/*!
 * LoRaMac upper layer event functions
 */
static LoRaMacCallbacks_t *LoRaMacCallbacks;

/*!
 * LoRaMac notification event flags
 */
LoRaMacEventFlags_t LoRaMacEventFlags;

/*!
 * LoRaMac notification event info
 */
LoRaMacEventInfo_t LoRaMacEventInfo;

/**************************** Timer Variables ********************************/
/*!
 * LoRaMac channel check timer
 */
static TimerEvent_t ChannelCheckTimer;

/*!
 * LoRaMac duty cycle delayed Tx timer
 */
static TimerEvent_t TxDelayedTimer;

/*!
 * LoRaMac reception windows timers
 */
static TimerEvent_t RxWindowTimer1;
static TimerEvent_t RxWindowTimer2;

/*!
 * LoRaMesh synchronized reception windows timer
 */
static TimerEvent_t SynchRxWindowTimer;

/*!
 * LoRaMesh advertising beacon timer
 */
static TimerEvent_t AdvBcnTimer;

/*!
 * LoRaMesh advertising beacon send delay timer
 */
static TimerEvent_t AdvBcnSendDelayTimer;

/*!
 * LoRaMesh advertising beacon send delay timer
 */
static TimerEvent_t AdvBcnRxWindowTimer;

/*!
 * Acknowledge timeout timer. Used for packet retransmissions.
 */
static TimerEvent_t AckTimeoutTimer;

/*!
 * LoRaMac timer used to check the LoRaMacState (runs every second)
 */
static TimerEvent_t MacStateCheckTimer;

/**************************** Delay Variables ********************************/
/*!
 * LoRaMac reception windows delay from end of Tx
 */
static uint32_t ReceiveDelay1;
static uint32_t ReceiveDelay2;
static uint32_t JoinAcceptDelay1;
static uint32_t JoinAcceptDelay2;

/*!
 * LoRaMac reception windows delay
 * \remark normal frame: RxWindowXDelay = ReceiveDelayX - RADIO_WAKEUP_TIME
 *         join frame  : RxWindowXDelay = JoinAcceptDelayX - RADIO_WAKEUP_TIME
 */
static uint32_t RxWindow1Delay;
static uint32_t RxWindow2Delay;

/************************* Acknowledge Variables *****************************/
/*!
 * Counts the number of missed ADR acknowledgements
 */
static uint32_t AdrAckCounter = 0;

/*!
 * If the node has sent a FRAME_TYPE_DATA_CONFIRMED_UP this variable indicates
 * if the nodes needs to manage the server acknowledgement.
 */
static bool NodeAckRequested = false;

/*!
 * If the server has sent a FRAME_TYPE_DATA_CONFIRMED_DOWN this variable indicates
 * if the ACK bit must be set for the next transmission
 */
static bool SrvAckRequested = false;

/*!
 * Number of trials to get a frame acknowledged
 */
static uint8_t AckTimeoutRetries = 1;

/*!
 * Number of trials to get a frame acknowledged
 */
static uint8_t AckTimeoutRetriesCounter = 1;

/*!
 * Indicates if the AckTimeout timer has expired or not
 */
static bool AckTimeoutRetry = false;

/************************** Duty Cycle Variables *****************************/
/*!
 * Maximum duty cycle
 * \remark Possibility to shutdown the device.
 */
static uint8_t MaxDCycle = 0;

/*!
 * Agregated duty cycle management
 */
static uint16_t AggregatedDCycle;
static TimerTime_t AggregatedLastTxDoneTime;
static TimerTime_t AggregatedTimeOff;

/*!
 * Enables/Disables duty cycle management (Test only)
 */
static bool DutyCycleOn;

/*!
 * Last transmission time on air
 */
static TimerTime_t TxTimeOnAir = 0;

/***************************** Mesh Variables ********************************/
/*!
 * LoRaMesh device role.
 */
static LoRaMeshRoles_t LoRaMeshDevRole = NORMAL;

/*!
 * Address of the parent node.
 */
static uint32_t ParentAddr;

/*!
 * Address of the coordinator node.
 */
static uint32_t CoordinatorAddr;

/*!
 * Child node list.
 */
static ListPointer_t ChildNodes = NULL;

/*!
 * Mutlicast channels linked list
 */
static ListPointer_t MulticastGroups = NULL;

/*!
 * Advertising slot information.
 */
static SlotInfo_t AdvertisingSlot;

/************************* Radio Driver Variables ****************************/
/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

/*****************************************************************************
 *                                                                           *
 * Event functions declaration                                               *
 *                                                                           *
 *****************************************************************************/
/*!
 * Function to be executed on Radio Tx Done event
 */
static void OnRadioTxDone( void );

/*!
 * Function to be executed on Radio Rx Done event
 */
static void OnRadioRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );

/*!
 * Function to be executed on Radio Cad Done event
 */
static void OnCadDone( bool channelActivityDetected );

/*!
 * Function executed on Radio Tx Timeout event
 */
static void OnRadioTxTimeout( void );

/*!
 * Function executed on Radio Rx error event
 */
static void OnRadioRxError( void );

/*!
 * Function executed on Radio Rx Timeout event
 */
static void OnRadioRxTimeout( void );

/*!
 * Function executed on Resend Frame timer event.
 */
static void OnMacStateCheckTimerEvent( void );

/*!
 * Function executed on duty cycle delayed Tx  timer event
 */
static void OnTxDelayedTimerEvent( void );

/*!
 * Function executed on channel check timer event
 */
static void OnChannelCheckTimerEvent( void );

/*!
 * Function executed on first Rx window timer event
 */
static void OnRxWindow1TimerEvent( void );

/*!
 * Function executed on second Rx window timer event
 */
static void OnRxWindow2TimerEvent( void );

/*!
 * Function executed on synchronized Rx window timer event
 */
static void OnRxSynchWindowTimerEvent( void );

/*!
 * Function executed on advertising beacon timer event
 */
static void OnAdvBcnTimerEvent( void );

/*!
 * Function executed on advertising beacon send delay timer event
 */
static void OnAdvBcnSendDelayTimerEvent( void );

/*!
 * Function executed on advertising beacon reception window timer event
 */
static void OnAdvBcnRxWindowTimerEvent( void );

/*!
 * Function executed on AckTimeout timer event
 */
static void OnAckTimeoutTimerEvent( void );

/*!
 * Function executed on ChannelCheck timer event
 */
static void OnChannelCheckTimerEvent( void );

/*****************************************************************************
 *                                                                           *
 * Utility functions declaration                                             *
 *                                                                           *
 *****************************************************************************/
/*!
 * LoRaMesh process received advertising beacon
 */
static void ProcessAdvertisingBeacon( uint8_t *payload, uint16_t size );

/*!
 * LoRaMesh process received data frame
 */
static void ProcessDataFrame( uint8_t* payload, uint16_t size, int16_t rssi, int8_t snr );

/*!
 * Adds a new MAC command to be sent.
 *
 * \Remark MAC layer internal function
 *
 * \param [in] cmd MAC command to be added
 *                 [MOTE_MAC_LINK_CHECK_REQ,
 *                  MOTE_MAC_LINK_ADR_ANS,
 *                  MOTE_MAC_DUTY_CYCLE_ANS,
 *                  MOTE_MAC_RX2_PARAM_SET_ANS,
 *                  MOTE_MAC_DEV_STATUS_ANS
 *                  MOTE_MAC_NEW_CHANNEL_ANS]
 * \param [in] p1  1st parameter ( optional depends on the command )
 * \param [in] p2  2nd parameter ( optional depends on the command )
 *
 * \retval status  Function status [0: OK, 1: Unknown command, 2: Buffer full]
 */
static uint8_t AddMacCommand( uint8_t cmd, uint8_t p1, uint8_t p2 );

/*!
 * Processes received MAC commands.
 *
 * \Remark MAC layer internal function
 *
 * \param [in] payload Pointer to the rx packet payload.
 * \param [in] macIndex Index of the MAC command to be processed.
 * \param [in] commandsSize Size of MAC commands to be processed.
 */
static void ProcessMacCommands( uint8_t *payload, uint8_t macIndex, uint8_t commandsSize );

/*!
 * \brief Validates if the payload fits into the frame, taking the datarate
 *        into account.
 *
 * \details Refer to chapter 4.3.2 of the LoRaWAN specification, v1.0
 *
 * \param lenN Length of the application payload. The length depends on the
 *             datarate and is region specific
 *
 * \param datarate Current datarate
 *
 * \retval [false: payload does not fit into the frame, true: payload fits into
 *          the frame]
 */
static bool ValidatePayloadLength( uint8_t lenN, int8_t datarate );

/*!
 * \brief Limits the Tx power according to the number of enabled channels
 *
 * \retval Returns the maximum valid tx power
 */
static int8_t LimitTxPower( int8_t txPower );

/*!
 * \brief Searches and set the next random available channel
 *
 * \retval status  Function status [0: OK, 1: Unable to find a free channel]
 */
static uint8_t SetNextChannel( void );

/*!
 * \brief Notify registered callback recipients of occurred MAC events.
 *
 * \param flags Event flags
 * \param info Additional event information
 */
static void Notify( LoRaMacEventFlags_t *flags, LoRaMacEventInfo_t *info );

/*!
 * \brief Evaluates probability of a node to nominate itself as coordinator and
 * returns true, if the calculated probability is bigger then a hardcoded threshold.
 *
 * \param nodeRank Calculated node rank
 * \return bool True if the node nominates itself
 */
static bool EvaluateNominationProbability( uint8_t nodeRank );
/*!
 * Calculate the nodes rank.
 *
 * \return uint8_t Rank of the node
 */
static uint8_t CalculateNodeRank( void );

/*!
 * \brief Create new child node with given data
 *
 * \param devAddr Device address of the child node
 * \param nwkSKey Network session key
 * \param appSKey Application session key
 * \param channel Channel frequency
 * \param interval Rx window interval
 */
static ChildNodeInfo_t* CreateChildNode( uint32_t devAddr, uint8_t* nwkSKey, uint8_t* appSKey,
        uint32_t channel, uint32_t interval );

/*!
 * \brief Add child node at the tail of the list.
 *
 * \param childNode Child Node to append
 */
static void ChildNodeAdd( ChildNodeInfo_t* childNode );

/*!
 * \brief Remove child node from the list.
 *
 * \param devAddr Device address of child node to remove.
 * \return LoRaMacChildNodeInfo_t Removed child node.
 */
static void ChildNodeRemove( ChildNodeInfo_t* childNode );

/*!
 * \brief Find child node with specified address.
 *
 * \param devAddr Device address of child node to find.
 * \return LoRaMacChildNodeInfo_t* Returns pointer to the found child node or NULL if not found.
 */
static ChildNodeInfo_t* ChildNodeFind( uint32_t devAddr );

/*!
 * \brief Print out child node information.
 *
 * \param childNode Pointer to child node information to print out.
 */
static void ChildNodePrint( ChildNodeInfo_t* childNode );

/*!
 * \brief Create new child node with given data
 *
 * \param devAddr Device address of the child node
 * \param nwkSKey Network session key
 * \param appSKey Application session key
 * \param channel Channel frequency
 * \param interval Rx window interval
 */
MulticastGroupInfo_t* CreateMulticastGroup( uint32_t grpAddr, uint8_t* nwkSKey, uint8_t* appSKey,
        uint32_t channel, uint32_t interval );

/*!
 * \brief Add mutlicast group.
 *
 * \param multicastGrp Pointer to information structure of the multicast group to be added.
 */
static void MulticastGroupAdd( MulticastGroupInfo_t *multicastGrp );

/*!
 * \brief Remove multicast group.
 *
 * \param multicastGrp Pointer to information structure of the multicast group to be removed.
 */
static void MulticastGroupRemove( MulticastGroupInfo_t *multicastGrp );

/*!
 * \brief Find multicast group with specified address.
 *
 * \param grpAddr Address of the group to find.
 * \return MulticastGroupInfo_t* Returns pointer to the found multicast group or NULL if not found.
 */
static MulticastGroupInfo_t* MulticastGroupFind( uint32_t grpAddr );

/*!
 * \brief Print out multicast group information.
 *
 * \param multicastGrp Pointer to multicast group information to print out.
 */
static void MulticastGroupPrint( MulticastGroupInfo_t* multicastGrp );

/*****************************************************************************
 *                                                                           *
 * API functions implementation                                              *
 *                                                                           *
 *****************************************************************************/
void LoRaMacInit( LoRaMacCallbacks_t *callbacks )
{
    LoRaMacCallbacks = callbacks;

    LoRaMacEventFlags.Value = 0;

    LoRaMacEventInfo.TxAckReceived = false;
    LoRaMacEventInfo.TxNbRetries = 0;
    LoRaMacEventInfo.TxDatarate = 7;
    LoRaMacEventInfo.RxPort = 1;
    LoRaMacEventInfo.RxBuffer = NULL;
    LoRaMacEventInfo.RxBufferSize = 0;
    LoRaMacEventInfo.RxRssi = 0;
    LoRaMacEventInfo.RxSnr = 0;
    LoRaMacEventInfo.Energy = 0;
    LoRaMacEventInfo.DemodMargin = 0;
    LoRaMacEventInfo.NbGateways = 0;
    LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_OK;

    /* Device always boots as Class A device */
    LoRaMacDeviceClass = CLASS_A;

    /* Reset Counters */
    UpLinkCounter = 1;
    DownLinkCounter = 0;

    /* MAC state */
    IsLoRaMacNetworkJoined = false;
    LoRaMacState = MAC_IDLE;

    /* Default channels mask */
    ChannelsMask[0] = LC(1); //+ LC( 2 ) + LC( 3 );

    /* Initialize default channel settings */
    ChannelsTxPower = LORAMAC_DEFAULT_TX_POWER;
    ChannelsDefaultDatarate = ChannelsDatarate = LORAMAC_DEFAULT_DATARATE;
    ChannelsNbRep = 1;
    ChannelsNbRepCounter = 0;

    /* Initialize duty cycle variables */
    MaxDCycle = 0;
    AggregatedDCycle = 1;
    AggregatedLastTxDoneTime = 0;
    AggregatedTimeOff = 0;

    DutyCycleOn = true;

    /* Initialize default delays */
    MaxRxWindow = MAX_RX_WINDOW;
    ReceiveDelay1 = RECEIVE_DELAY1;
    ReceiveDelay2 = RECEIVE_DELAY2;
    JoinAcceptDelay1 = JOIN_ACCEPT_DELAY1;
    JoinAcceptDelay2 = JOIN_ACCEPT_DELAY2;

    /* Initialize Mesh variables */
    AdvertisingSlot.Frequency = ADV_BEACON_FREQUENCY;
    AdvertisingSlot.Periodicity = ADV_BEACON_INTERVAL;
    AdvertisingSlot.Duration = ADV_BEACON_DURATION;
    CoordinatorAddr = 0;
    ParentAddr = 0;

    /* Initialize Timers */
    TimerInit(&ChannelCheckTimer, OnChannelCheckTimerEvent);
    TimerInit(&TxDelayedTimer, OnTxDelayedTimerEvent);
    TimerInit(&RxWindowTimer1, OnRxWindow1TimerEvent);
    TimerInit(&RxWindowTimer2, OnRxWindow2TimerEvent);
    TimerInit(&SynchRxWindowTimer, OnRxSynchWindowTimerEvent);
    TimerInit(&AckTimeoutTimer, OnAckTimeoutTimerEvent);
    TimerInit(&AdvBcnTimer, OnAdvBcnTimerEvent);
    TimerInit(&AdvBcnSendDelayTimer, OnAdvBcnSendDelayTimerEvent);
    TimerInit(&AdvBcnRxWindowTimer, OnAdvBcnRxWindowTimerEvent);

    TimerSetValue(&AdvBcnTimer, ADV_BEACON_INTERVAL);

    TimerInit(&MacStateCheckTimer, OnMacStateCheckTimerEvent);
    TimerSetValue(&MacStateCheckTimer, MAC_STATE_CHECK_TIMEOUT);

    /* Initialize Radio driver */
    RadioEvents.CadDone = OnCadDone;
    RadioEvents.TxDone = OnRadioTxDone;
    RadioEvents.RxDone = OnRadioRxDone;
    RadioEvents.RxError = OnRadioRxError;
    RadioEvents.TxTimeout = OnRadioTxTimeout;
    RadioEvents.RxTimeout = OnRadioRxTimeout;
    Radio.Init(&RadioEvents);

    /* Random seed initialization */
    srand1(Radio.Random());

    /* Initialize channel index. */
    Channel = LORA_MAX_NB_CHANNELS;

    PublicNetwork = true;
    LoRaMacSetPublicNetwork(PublicNetwork);
    Radio.Sleep();
}

void LoRaMacSetAdrOn( bool enable )
{
    AdrCtrlOn = enable;
}

void LoRaMacInitNwkIds( uint32_t netID, uint32_t devAddr, uint8_t *nwkSKey, uint8_t *appSKey )
{
    LoRaMacNetID = netID;
    LoRaMacDevAddr = devAddr;
    LoRaMacMemCpy(nwkSKey, LoRaMacNwkSKey, 16);
    LoRaMacMemCpy(appSKey, LoRaMacAppSKey, 16);

    /* Start advertising */
    TimerStart(&AdvBcnTimer);

    IsLoRaMacNetworkJoined = true;
}

uint8_t LoRaMacJoinReq( uint8_t *devEui, uint8_t *appEui, uint8_t *appKey )
{
    LoRaMacHeader_t macHdr;

    LoRaMacDevEui = devEui;
    LoRaMacAppEui = appEui;
    LoRaMacAppKey = appKey;

    macHdr.Value = 0;
    macHdr.Bits.MType = FRAME_TYPE_JOIN_REQ;

    IsLoRaMacNetworkJoined = false;

    return LoRaMacSend(&macHdr, NULL, 0, NULL, 0);
}

uint8_t LoRaMacLinkCheckReq( void )
{
    return AddMacCommand(MOTE_MAC_LINK_CHECK_REQ, 0, 0);
}

uint8_t LoRaMacSendFrame( uint8_t fPort, void *fBuffer, uint16_t fBufferSize )
{
    LoRaMacHeader_t macHdr;

    macHdr.Value = 0;

    macHdr.Bits.MType = FRAME_TYPE_DATA_UNCONFIRMED_UP;
    return LoRaMacSend(&macHdr, NULL, fPort, fBuffer, fBufferSize);
}

uint8_t LoRaMacSendConfirmedFrame( uint8_t fPort, void *fBuffer, uint16_t fBufferSize,
        uint8_t retries )
{
    LoRaMacHeader_t macHdr;

    if ( AdrCtrlOn == false ) {
        ChannelsDatarate = ChannelsDefaultDatarate;
    }
    AckTimeoutRetries = retries;
    AckTimeoutRetriesCounter = 1;

    macHdr.Value = 0;

    macHdr.Bits.MType = FRAME_TYPE_DATA_CONFIRMED_UP;
    return LoRaMacSend(&macHdr, NULL, fPort, fBuffer, fBufferSize);
}

void PrintChildNodes( bool reverseOrder )
{
    ListNodePointer_t tempNode;
    uint8_t i;
    if ( reverseOrder )
        tempNode = (ListNodePointer_t) ChildNodes->tail;
    else
        tempNode = (ListNodePointer_t) ChildNodes->head;

    for ( i = 0; i < ChildNodes->count; i++ ) {
        LOG_DEBUG_BARE("%u. ---------------------------------------------\r\n", (i + 1));
        ChildNodePrint((ChildNodeInfo_t*) tempNode->data);
        if ( reverseOrder )
            tempNode = (ListNodePointer_t) tempNode->prev;
        else
            tempNode = (ListNodePointer_t) tempNode->next;
    }
}

void PrintMulticastGroups( bool reverseOrder )
{
    ListNodePointer_t tempGrp;
    uint8_t i;
    if ( reverseOrder )
        tempGrp = (ListNodePointer_t) MulticastGroups->tail;
    else
        tempGrp = (ListNodePointer_t) MulticastGroups->head;

    for ( i = 0; i < MulticastGroups->count; i++ ) {
        LOG_DEBUG_BARE("%u. ---------------------------------------------\r\n", (i + 1));
        MulticastGroupPrint((MulticastGroupInfo_t*) tempGrp->data);
        if ( reverseOrder )
            tempGrp = (ListNodePointer_t) tempGrp->prev;
        else
            tempGrp = (ListNodePointer_t) tempGrp->next;
    }
}

/*****************************************************************************
 *                                                                           *
 * Test functions implementation                                             *
 *                                                                           *
 *****************************************************************************/
uint8_t LoRaMacSend( LoRaMacHeader_t *macHdr, uint8_t *fOpts, uint8_t fPort, void *fBuffer,
        uint16_t fBufferSize )
{
    LoRaMacFrameCtrl_t fCtrl;

    fCtrl.Value = 0;

    fCtrl.Bits.FOptsLen = 0;
    fCtrl.Bits.FPending = 0;
    fCtrl.Bits.Ack = false;
    fCtrl.Bits.AdrAckReq = false;
    fCtrl.Bits.Adr = AdrCtrlOn;

    if ( SetNextChannel() == 0 ) {
        return LoRaMacSendOnChannel(Channels[Channel], macHdr, &fCtrl, fOpts, fPort, fBuffer,
                fBufferSize);
    }
    return 5;
}

uint8_t LoRaMacPrepareFrame( ChannelParams_t channel, LoRaMacHeader_t *macHdr,
        LoRaMacFrameCtrl_t *fCtrl, uint8_t *fOpts, uint8_t fPort, void *fBuffer,
        uint16_t fBufferSize )
{
    uint16_t i;
    uint8_t pktHeaderLen = 0;
    uint32_t mic = 0;

    LoRaMacBufferPktLen = 0;

    NodeAckRequested = false;

    if ( fBuffer == NULL ) {
        fBufferSize = 0;
    } else {
        if ( ValidatePayloadLength(fBufferSize, ChannelsDatarate) == false ) {
            return 3;
        }
    }

    LoRaMacBuffer[pktHeaderLen++] = macHdr->Value;

    switch (macHdr->Bits.MType) {
        case FRAME_TYPE_JOIN_REQ:
            RxWindow1Delay = JoinAcceptDelay1 - RADIO_WAKEUP_TIME;
            RxWindow2Delay = JoinAcceptDelay2 - RADIO_WAKEUP_TIME;

            LoRaMacBufferPktLen = pktHeaderLen;

            LoRaMacMemCpy(LoRaMacAppEui, LoRaMacBuffer + LoRaMacBufferPktLen, 8);
            LoRaMacBufferPktLen += 8;
            LoRaMacMemCpy(LoRaMacDevEui, LoRaMacBuffer + LoRaMacBufferPktLen, 8);
            LoRaMacBufferPktLen += 8;

            LoRaMacDevNonce = Radio.Random();

            LoRaMacBuffer[LoRaMacBufferPktLen++] = LoRaMacDevNonce & 0xFF;
            LoRaMacBuffer[LoRaMacBufferPktLen++] = (LoRaMacDevNonce >> 8) & 0xFF;

            LoRaMacJoinComputeMic(LoRaMacBuffer, LoRaMacBufferPktLen & 0xFF, LoRaMacAppKey, &mic);

            LoRaMacBuffer[LoRaMacBufferPktLen++] = mic & 0xFF;
            LoRaMacBuffer[LoRaMacBufferPktLen++] = (mic >> 8) & 0xFF;
            LoRaMacBuffer[LoRaMacBufferPktLen++] = (mic >> 16) & 0xFF;
            LoRaMacBuffer[LoRaMacBufferPktLen++] = (mic >> 24) & 0xFF;

            break;
        case FRAME_TYPE_DATA_CONFIRMED_UP:
            NodeAckRequested = true;
            //Intentional falltrough
        case FRAME_TYPE_DATA_UNCONFIRMED_UP:
            if ( IsLoRaMacNetworkJoined == false ) {
                return 2; // No network has been joined yet
            }

            RxWindow1Delay = ReceiveDelay1 - RADIO_WAKEUP_TIME;
            RxWindow2Delay = ReceiveDelay2 - RADIO_WAKEUP_TIME;

            if ( fOpts == NULL ) {
                fCtrl->Bits.FOptsLen = 0;
            }

            if ( SrvAckRequested == true ) {
                SrvAckRequested = false;
                fCtrl->Bits.Ack = 1;
            }

            if ( fCtrl->Bits.Adr == true ) {
                if ( ChannelsDatarate == LORAMAC_MIN_DATARATE ) {
                    AdrAckCounter = 0;
                    fCtrl->Bits.AdrAckReq = false;
                } else {
                    if ( AdrAckCounter > ADR_ACK_LIMIT ) {
                        fCtrl->Bits.AdrAckReq = true;
                    } else {
                        fCtrl->Bits.AdrAckReq = false;
                    }
                    if ( AdrAckCounter > (ADR_ACK_LIMIT + ADR_ACK_DELAY) ) {
                        AdrAckCounter = 0;
#if defined( USE_BAND_868 )
                        if( ChannelsDatarate > LORAMAC_MIN_DATARATE )
                        {
                            ChannelsDatarate--;
                        }
                        else
                        {
                            // Re-enable default channels LC1, LC2, LC3
                            ChannelsMask[0] = ChannelsMask[0] | ( LC( 1 ) + LC( 2 ) + LC( 3 ) );
                        }
#else
#error "Please define a frequency band in the compiler options."
#endif
                    }
                }
            }

            LoRaMacBuffer[pktHeaderLen++] = (LoRaMacDevAddr) & 0xFF;
            LoRaMacBuffer[pktHeaderLen++] = (LoRaMacDevAddr >> 8) & 0xFF;
            LoRaMacBuffer[pktHeaderLen++] = (LoRaMacDevAddr >> 16) & 0xFF;
            LoRaMacBuffer[pktHeaderLen++] = (LoRaMacDevAddr >> 24) & 0xFF;

            LoRaMacBuffer[pktHeaderLen++] = fCtrl->Value;

            LoRaMacBuffer[pktHeaderLen++] = UpLinkCounter & 0xFF;
            LoRaMacBuffer[pktHeaderLen++] = (UpLinkCounter >> 8) & 0xFF;

            if ( fOpts != NULL ) {
                for ( i = 0; i < fCtrl->Bits.FOptsLen; i++ ) {
                    LoRaMacBuffer[pktHeaderLen++] = fOpts[i];
                }
            }
            if ( (MacCommandsBufferIndex + fCtrl->Bits.FOptsLen) <= 15 ) {
                if ( MacCommandsInNextTx == true ) {
                    fCtrl->Bits.FOptsLen += MacCommandsBufferIndex;

                    // Update FCtrl field with new value of OptionsLength
                    LoRaMacBuffer[0x05] = fCtrl->Value;
                    for ( i = 0; i < MacCommandsBufferIndex; i++ ) {
                        LoRaMacBuffer[pktHeaderLen++] = MacCommandsBuffer[i];
                    }
                }
            }
            MacCommandsInNextTx = false;
            MacCommandsBufferIndex = 0;

            if ( (pktHeaderLen + fBufferSize) > LORAMAC_PHY_MAXPAYLOAD ) {
                return 3;
            }

            if ( fBuffer != NULL ) {
                LoRaMacBuffer[pktHeaderLen++] = fPort;

                if ( fPort == 0 ) {
                    LoRaMacPayloadEncrypt((uint8_t*) fBuffer, fBufferSize, LoRaMacNwkSKey,
                            LoRaMacDevAddr, UP_LINK, UpLinkCounter, LoRaMacPayload);
                } else {
                    LoRaMacPayloadEncrypt((uint8_t*) fBuffer, fBufferSize, LoRaMacAppSKey,
                            LoRaMacDevAddr, UP_LINK, UpLinkCounter, LoRaMacPayload);
                }
                LoRaMacMemCpy(LoRaMacPayload, LoRaMacBuffer + pktHeaderLen, fBufferSize);
            }
            LoRaMacBufferPktLen = pktHeaderLen + fBufferSize;

            LoRaMacComputeMic(LoRaMacBuffer, LoRaMacBufferPktLen, LoRaMacNwkSKey, LoRaMacDevAddr,
                    UP_LINK, UpLinkCounter, &mic);

            if ( (LoRaMacBufferPktLen + LORAMAC_MFR_LEN) > LORAMAC_PHY_MAXPAYLOAD ) {
                return 3;
            }
            LoRaMacBuffer[LoRaMacBufferPktLen + 0] = mic & 0xFF;
            LoRaMacBuffer[LoRaMacBufferPktLen + 1] = (mic >> 8) & 0xFF;
            LoRaMacBuffer[LoRaMacBufferPktLen + 2] = (mic >> 16) & 0xFF;
            LoRaMacBuffer[LoRaMacBufferPktLen + 3] = (mic >> 24) & 0xFF;

            LoRaMacBufferPktLen += LORAMAC_MFR_LEN;
            break;
        default:
            return 4;
    }

    return 0;
}

uint8_t LoRaMacSendFrameOnChannel( ChannelParams_t channel )
{
    LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_ERROR;
    LoRaMacEventInfo.TxDatarate = ChannelsDatarate;

    ChannelsTxPower = LimitTxPower(ChannelsTxPower);

    Radio.SetChannel(channel.Frequency);
    Radio.SetMaxPayloadLength(MODEM_LORA, LoRaMacBufferPktLen);

#if defined( USE_BAND_868 )
    if( ChannelsDatarate == DR_7 )
    { // High Speed FSK channel
        Radio.SetTxConfig( MODEM_FSK, TxPowers[ChannelsTxPower], 25e3, 0, Datarates[ChannelsDatarate] * 1e3, 0, 5, false, true, 0, 0, false, 3e6 );
        TxTimeOnAir = Radio.TimeOnAir( MODEM_FSK, LoRaMacBufferPktLen );
    }
    else if( ChannelsDatarate == DR_6 )
    { // High speed LoRa channel
        Radio.SetTxConfig( MODEM_LORA, TxPowers[ChannelsTxPower], 0, 1, Datarates[ChannelsDatarate], 1, 8, false, true, 0, 0, false, 3e6 );
        TxTimeOnAir = Radio.TimeOnAir( MODEM_LORA, LoRaMacBufferPktLen );
    }
    else
    { // Normal LoRa channel
        Radio.SetTxConfig( MODEM_LORA, TxPowers[ChannelsTxPower], 0, 0, Datarates[ChannelsDatarate], 1, 8, false, true, 0, 0, false, 3e6 );
        TxTimeOnAir = Radio.TimeOnAir( MODEM_LORA, LoRaMacBufferPktLen );
    }
#else
#error "Please define a frequency band in the compiler options."
#endif

    if ( MaxDCycle == 255 ) {
        return 6;
    }
    if ( MaxDCycle == 0 ) {
        AggregatedTimeOff = 0;
    }

    LoRaMacState |= MAC_TX_RUNNING;
    // Starts the MAC layer status check timer
    TimerStart(&MacStateCheckTimer);

    if ( MAX(Bands[channel.Band].TimeOff, AggregatedTimeOff) > (TimerGetCurrentTime()) ) {
        // Schedule transmission
        LOG_TRACE("Send in %d ticks on channel %d (DR: %u).",
                MAX(Bands[channel.Band].TimeOff, AggregatedTimeOff), channel.Frequency,
                ChannelsDatarate);
        TimerSetValue(&TxDelayedTimer, MAX(Bands[channel.Band].TimeOff, AggregatedTimeOff));
        TimerStart(&TxDelayedTimer);
    } else {
        // Send now
        LOG_TRACE("Sending now on channel %d (DR: %u).", channel.Frequency, ChannelsDatarate);
        Radio.Send(LoRaMacBuffer, LoRaMacBufferPktLen);
    }
    return 0;
}

uint8_t LoRaMacSendOnChannel( ChannelParams_t channel, LoRaMacHeader_t *macHdr,
        LoRaMacFrameCtrl_t *fCtrl, uint8_t *fOpts, uint8_t fPort, void *fBuffer,
        uint16_t fBufferSize )
{
    uint8_t status = 0;

    if ( (LoRaMacState & MAC_TX_RUNNING) == MAC_TX_RUNNING ) {
        return 1; // MAC is busy transmitting a previous frame
    }

    status = LoRaMacPrepareFrame(channel, macHdr, fCtrl, fOpts, fPort, fBuffer, fBufferSize);
    if ( status != 0 ) {
        return status;
    }

    LoRaMacEventInfo.TxNbRetries = 0;
    LoRaMacEventInfo.TxAckReceived = false;

    return LoRaMacSendFrameOnChannel(channel);
}

void LoRaMacRxWindowSetup( uint32_t freq, int8_t datarate, uint32_t bandwidth, uint16_t timeout,
        bool rxContinuous )
{
    if ( Radio.GetStatus() == RF_IDLE ) {
        Radio.SetChannel(freq);
        if ( datarate == DR_7 ) {
            Radio.SetRxConfig(MODEM_FSK, 50e3, Datarates[datarate] * 1e3, 0, 83.333e3, 5, 0, false,
                    0, true, 0, 0, false, rxContinuous);
        } else {
            Radio.SetRxConfig(MODEM_LORA, bandwidth, Datarates[datarate], 1, 0, 8, timeout, false,
                    0, false, 0, 0, false, rxContinuous);
        }
        if ( rxContinuous == false ) {
            Radio.Rx(MaxRxWindow);
        } else {
            Radio.Rx(0); // Continuous mode
        }
    }
}

void LoRaMacBcnRxWindowSetup( void )
{
    Radio.SetChannel(ADV_BEACON_FREQUENCY);
    if ( ADV_BEACON_DATARATE == DR_7 ) {
        Radio.SetRxConfig(MODEM_FSK, 50e3, Datarates[ADV_BEACON_DATARATE] * 1e3, 0, 83.333e3, 5, 0,
                false, 0, true, false, 0, false, true);
    } else {
        Radio.SetRxConfig(MODEM_LORA, ADV_BEACON_BANDWIDTH, Datarates[ADV_BEACON_DATARATE], 1, 0, 8,
                5, false, 0, true, false, 0, false, true);
    }
}

void LoRaMeshAddChildNode( uint32_t nodeAddr )
{
    ChildNodeInfo_t* childNode = CreateChildNode(nodeAddr, (uint8_t*) &LoRaMacNwkSKey,
            (uint8_t*) &LoRaMacAppSKey, 868100000, 1000000);
    ChildNodeAdd(childNode);
}

void LoRaMeshAddMulticastGroup( uint32_t grpAddr )
{
    MulticastGroupInfo_t* multicastGrp = CreateMulticastGroup(grpAddr, (uint8_t*) &LoRaMacNwkSKey,
            (uint8_t*) &LoRaMacAppSKey, 868100000, 2000000);
    MulticastGroupAdd(multicastGrp);
}

uint8_t LoRaMeshSendAdvertisingBeacon( void )
{
    uint32_t timestamp;

    LOG_TRACE("Trying to send advertising beacon.");

    /* Configure LoRa transceiver */
    Radio.SetChannel(AdvertisingSlot.Frequency);
    Radio.SetTxConfig(MODEM_LORA, TxPowers[ADV_BEACON_TX_POWER], 0, ADV_BEACON_BANDWIDTH,
            Datarates[ADV_BEACON_DATARATE], 1, 8, false, true, 0, 0, false, 3e6);

    LoRaMacState |= MAC_TX_RUNNING;
    /* Starts the MAC layer status check timer */
    TimerStart(&MacStateCheckTimer);

    /* Get latest gps position */
    if ( (timestamp = GpsGetCurrentUnixTime()) == 0 ) return 1;

    /* Assemble advertising beacon */
    LoRaMacBufferPktLen = 0;
    /* Network ID */
    LoRaMacBuffer[0] = (uint8_t)(LoRaMacNetID & 0xFF);
    LoRaMacBuffer[1] = (uint8_t)((LoRaMacNetID >> 8) & 0xFF);
    LoRaMacBuffer[2] = (uint8_t)((LoRaMacNetID >> 16) & 0xFF);
    /* DevInfo (Role/Rank) */
    LoRaMacBuffer[3] = (uint8_t)(((LoRaMeshDevRole & 0xF) << 4) | (CalculateNodeRank() & 0xF));
    /* Coordinator address */
    LoRaMacBuffer[4] = (uint8_t)(CoordinatorAddr & 0xFF);
    LoRaMacBuffer[5] = (uint8_t)((CoordinatorAddr >> 8) & 0xFF);
    LoRaMacBuffer[6] = (uint8_t)((CoordinatorAddr >> 16) & 0xFF);
    LoRaMacBuffer[7] = (uint8_t)((CoordinatorAddr >> 24) & 0xFF);
    /* Advertising Slot Info */
    LoRaMacBuffer[8] = (uint8_t)(timestamp & 0xFF);
    LoRaMacBuffer[9] = (uint8_t)((timestamp >> 8) & 0xFF);
    LoRaMacBuffer[10] = (uint8_t)((timestamp >> 16) & 0xFF);
    LoRaMacBuffer[11] = (uint8_t)((timestamp >> 24) & 0xFF);
    LoRaMacBuffer[12] = (uint8_t)((AdvertisingSlot.Periodicity / 1000000) & 0xFF); // Periodicity is transmitted in seconds
    LoRaMacBuffer[13] = (uint8_t)((AdvertisingSlot.Duration / 1000) & 0xFF); // Periodicity is transmitted in milliseconds

//    LOG_TRACE_BARE("DATA: ");
//    for ( uint32_t i = 0; i < ADV_BEACON_LEN; i++ ) {
//        LOG_TRACE_BARE("0x%02x ", LoRaMacBuffer[i]);
//    }
//    LOG_TRACE_BARE("\r\n");

    LoRaMacBufferPktLen = ADV_BEACON_LEN;

    /* Start channel activity detection */
    Radio.StartCad();

    /* Set event flag */
    LoRaMacEventFlags.Bits.Advertising = 1;

    return 0;
}

/*****************************************************************************
 *                                                                           *
 * Event functions implementation                                            *
 *                                                                           *
 *****************************************************************************/
void OnChannelCheckTimerEvent( void )
{
    TimerStop(&ChannelCheckTimer);

    LoRaMacState &= ~MAC_CHANNEL_CHECK;
    if ( SetNextChannel() == 0 ) {
        if ( (LoRaMacState & MAC_TX_RUNNING) == MAC_TX_RUNNING ) {
            LoRaMacSendFrameOnChannel(Channels[Channel]);
        }
    }
}

void OnRadioTxDone( void )
{
    LOG_TRACE("Transmitted successfully.");
    TimerTime_t curTime = TimerGetCurrentTime();

    if ( LoRaMacDeviceClass != CLASS_C ) {
        Radio.Sleep();
    } else {
        OnRxWindow2TimerEvent();
    }

    // Update Band Time OFF
    Bands[Channels[Channel].Band].LastTxDoneTime = curTime;
    if ( DutyCycleOn == true ) {
        Bands[Channels[Channel].Band].TimeOff = TxTimeOnAir * Bands[Channels[Channel].Band].DCycle
                - TxTimeOnAir;
    } else {
        Bands[Channels[Channel].Band].TimeOff = 0;
    }
    // Update Agregated Time OFF
    AggregatedLastTxDoneTime = curTime;
    AggregatedTimeOff = AggregatedTimeOff + (TxTimeOnAir * AggregatedDCycle - TxTimeOnAir);

    if ( LoRaMacEventFlags.Bits.Advertising == 1 ) {
        LoRaMacEventFlags.Bits.Advertising = 0;
        /* Open advertising beacon reception window */
        LoRaMacBcnRxWindowSetup();
    } else if ( IsRxWindowsEnabled == true ) {
        if ( RxWindowTimer1.ReloadValue != RxWindow1Delay )
            TimerSetValue(&RxWindowTimer1, RxWindow1Delay);
        if ( RxWindowTimer2.ReloadValue != RxWindow2Delay )
            TimerSetValue(&RxWindowTimer2, RxWindow2Delay);
        TimerStart(&RxWindowTimer1);
        TimerStart(&RxWindowTimer2);
    } else {
        LoRaMacEventFlags.Bits.Tx = 1;
        LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_OK;
    }

    if ( NodeAckRequested == false ) {
        ChannelsNbRepCounter++;
    }
}

void OnRadioRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
    LoRaMacHeader_t macHdr;
    uint32_t mic = 0;
    uint32_t micRx = 0;

    if ( LoRaMacDeviceClass != CLASS_C ) {
        Radio.Sleep();
    }
    TimerStop(&RxWindowTimer2);

    /* Check if incoming packet is an advertising beacon */
    if ( (LoRaMacDeviceClass == CLASS_D) && (LoRaMacEventFlags.Bits.RxSlot == 0) ) {
        LOG_TRACE("Received advertising beacon.");
        ProcessAdvertisingBeacon(payload, size);
        return;
    }

    macHdr.Value = (uint8_t) * payload;

    switch (macHdr.Bits.MType) {
        case FRAME_TYPE_JOIN_REQ:
            LOG_TRACE("Received join request.");
            break;
        case FRAME_TYPE_JOIN_ACCEPT:
            if ( IsLoRaMacNetworkJoined == true ) {
                break;
            }
            LoRaMacJoinDecrypt(payload + 1, size - 1, LoRaMacAppKey, LoRaMacRxPayload + 1);

            LoRaMacRxPayload[0] = macHdr.Value;

            LoRaMacJoinComputeMic(LoRaMacRxPayload, size - LORAMAC_MFR_LEN, LoRaMacAppKey, &mic);

            micRx |= (uint32_t) LoRaMacRxPayload[size - LORAMAC_MFR_LEN];
            micRx |= ((uint32_t) LoRaMacRxPayload[size - LORAMAC_MFR_LEN + 1] << 8);
            micRx |= ((uint32_t) LoRaMacRxPayload[size - LORAMAC_MFR_LEN + 2] << 16);
            micRx |= ((uint32_t) LoRaMacRxPayload[size - LORAMAC_MFR_LEN + 3] << 24);

            if ( micRx == mic ) {
                LoRaMacEventFlags.Bits.Rx = 1;
                LoRaMacEventInfo.RxSnr = snr;
                LoRaMacEventInfo.RxRssi = rssi;

                LoRaMacJoinComputeSKeys(LoRaMacAppKey, LoRaMacRxPayload + 1, LoRaMacDevNonce,
                        LoRaMacNwkSKey, LoRaMacAppSKey);

                LoRaMacNetID = (uint32_t) LoRaMacRxPayload[4];
                LoRaMacNetID |= ((uint32_t) LoRaMacRxPayload[5] << 8);
                LoRaMacNetID |= ((uint32_t) LoRaMacRxPayload[6] << 16);

                LoRaMacDevAddr = (uint32_t) LoRaMacRxPayload[7];
                LoRaMacDevAddr |= ((uint32_t) LoRaMacRxPayload[8] << 8);
                LoRaMacDevAddr |= ((uint32_t) LoRaMacRxPayload[9] << 16);
                LoRaMacDevAddr |= ((uint32_t) LoRaMacRxPayload[10] << 24);

                // DLSettings
                Rx1DrOffset = (LoRaMacRxPayload[11] >> 4) & 0x07;
                Rx2Channel.Datarate = LoRaMacRxPayload[11] & 0x0F;
                // RxDelay
                ReceiveDelay1 = (LoRaMacRxPayload[12] & 0x0F);
                if ( ReceiveDelay1 == 0 ) {
                    ReceiveDelay1 = 1;
                }
                ReceiveDelay1 *= 1e6;
                ReceiveDelay2 = ReceiveDelay1 + 1e6;

                //CFList
                if ( (size - 1) > 16 ) {
                    ChannelParams_t param;
                    param.DrRange.Value = (DR_5 << 4) | DR_0;

                    for ( uint8_t i = 3, j = 0; i < (5 + 3); i++, j += 3 ) {
                        param.Frequency = ((uint32_t) LoRaMacRxPayload[13 + j]
                                | ((uint32_t) LoRaMacRxPayload[14 + j] << 8)
                                | ((uint32_t) LoRaMacRxPayload[15 + j] << 16)) * 100;
                        LoRaMacSetChannel(i, param);
                    }
                }

                LoRaMacEventFlags.Bits.JoinAccept = 1;
                IsLoRaMacNetworkJoined = true;
                ChannelsDatarate = ChannelsDefaultDatarate;
                LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_OK;
            } else {
                LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_JOIN_FAIL;
            }

            LoRaMacEventFlags.Bits.Tx = 1;
            break;
        case FRAME_TYPE_DATA_CONFIRMED_DOWN:
            LOG_TRACE_IF(macHdr.Bits.MType == FRAME_TYPE_DATA_CONFIRMED_DOWN,
                    "Received confirmed downlink.");
        case FRAME_TYPE_DATA_UNCONFIRMED_DOWN:
            LOG_TRACE_IF(macHdr.Bits.MType == FRAME_TYPE_DATA_UNCONFIRMED_DOWN,
                    "Received unconfirmed downlink.");
        case FRAME_TYPE_DATA_CONFIRMED_UP:
            LOG_TRACE_IF(macHdr.Bits.MType == FRAME_TYPE_DATA_CONFIRMED_UP,
                    "Received unconfirmed uplink.");
        case FRAME_TYPE_DATA_UNCONFIRMED_UP:
            LOG_TRACE_IF(macHdr.Bits.MType == FRAME_TYPE_DATA_UNCONFIRMED_UP,
                    "Received unconfirmed uplink.");
            ProcessDataFrame(payload, size, rssi, snr);
            break;
        case FRAME_TYPE_PROPRIETARY:
            //Intentional falltrough
        default:
            LoRaMacEventFlags.Bits.Tx = 1;
            LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_ERROR;
            LoRaMacState &= ~MAC_TX_RUNNING;
            break;
    }

    if ( (LoRaMacDeviceClass == CLASS_C) && (LoRaMacEventFlags.Bits.RxSlot == 1) ) {
        OnRxWindow2TimerEvent();
    }

}

void OnCadDone( bool channelActivityDetected )
{
    uint64_t curTime = TimerGetCurrentTime();
    Radio.Sleep();
    if ( !channelActivityDetected ) {
        LOG_TRACE("Channel clear. Send packet now (%d%d)", *(((int*) (&curTime)) + 1), curTime);
        Radio.Send(LoRaMacBuffer, LoRaMacBufferPktLen);
    } else {
        uint32_t delay = randr(0, (AdvertisingSlot.Duration - AdvBcnSendDelayTimer.ReloadValue));
        curTime += (uint64_t) delay;
        LOG_TRACE("Channel NOT clear. Send packet in %d (%d%d)", delay, *(((int*) (&curTime)) + 1),
                curTime);
        TimerSetValue(&TxDelayedTimer, delay);
        TimerStart(&TxDelayedTimer);
    }
}

void OnTxDelayedTimerEvent( void )
{
    TimerStop(&TxDelayedTimer);
    Radio.Send(LoRaMacBuffer, LoRaMacBufferPktLen);
}

void OnRadioTxTimeout( void )
{
    LOG_ERROR("Tx timeout occurred.");
    if ( LoRaMacDeviceClass != CLASS_C ) {
        Radio.Sleep();
    } else {
        OnRxWindow2TimerEvent();
    }

    LoRaMacEventFlags.Bits.Tx = 1;
    LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_TX_TIMEOUT;
}

void OnRadioRxTimeout( void )
{
    LOG_ERROR("Rx timeout occurred (Slot %d).", LoRaMacEventFlags.Bits.RxSlot);

    if ( LoRaMacDeviceClass != CLASS_C ) {
        Radio.Sleep();
    } else {
        if ( LoRaMacEventFlags.Bits.RxSlot == 1 ) LoRaMacEventFlags.Bits.Tx = 1;
        OnRxWindow2TimerEvent();
    }

    if ( LoRaMacEventFlags.Bits.RxSlot == 2 ) {
        LoRaMacEventFlags.Bits.Tx = 1;
        LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_RX2_TIMEOUT;
    }
}

void OnRadioRxError( void )
{
    LOG_ERROR("Rx error occurred (Slot %d).", LoRaMacEventFlags.Bits.RxSlot);
    if ( LoRaMacDeviceClass != CLASS_C ) {
        Radio.Sleep();
    } else {
        OnRxWindow2TimerEvent();
    }
    if ( LoRaMacEventFlags.Bits.RxSlot == 2 ) {
        LoRaMacEventFlags.Bits.Tx = 1;
        LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_RX2_TIMEOUT;
    }
}

void OnRxWindow1TimerEvent( void )
{
    uint16_t symbTimeout = 5; // DR_2, DR_1, DR_0
    int8_t datarate = 0;
    uint32_t bandwidth = 0; // LoRa 125 kHz

    TimerStop(&RxWindowTimer1);
    LoRaMacEventFlags.Bits.RxSlot = 1;

    /* \todo move radio to standby mode in order to open rx window 1 directly after rx window 2 */
    if ( LoRaMacDeviceClass == CLASS_C ) {
        Radio.Standby();
    }

    datarate = ChannelsDatarate - Rx1DrOffset;
    if ( datarate < 0 ) {
        datarate = DR_0;
    }

// For higher datarates, we increase the number of symbols generating a Rx Timeout
    if ( datarate >= DR_3 ) { // DR_6, DR_5, DR_4, DR_3
        symbTimeout = 8;
    }
    if ( datarate == DR_6 ) { // LoRa 250 kHz
        bandwidth = 1;
    }
    LOG_TRACE("Open Rx window 1 (Channel : %u / DR: %u).", Channels[Channel].Frequency,
            Datarates[datarate]);
    LoRaMacRxWindowSetup(Channels[Channel].Frequency, datarate, bandwidth, symbTimeout, false);
}

void OnRxWindow2TimerEvent( void )
{
    uint16_t symbTimeout = 5; // DR_2, DR_1, DR_0
    uint32_t bandwidth = 0; // LoRa 125 kHz

    TimerStop(&RxWindowTimer2);
    LoRaMacEventFlags.Bits.RxSlot = 2;

    if ( NodeAckRequested == true ) {
        TimerSetValue(&AckTimeoutTimer, ACK_TIMEOUT + randr(-ACK_TIMEOUT_RND, ACK_TIMEOUT_RND));
        TimerStart(&AckTimeoutTimer);
    }

// For higher datarates, we increase the number of symbols generating a Rx Timeout
    if ( Rx2Channel.Datarate >= DR_3 ) { // DR_6, DR_5, DR_4, DR_3
        symbTimeout = 8;
    }
    if ( Rx2Channel.Datarate == DR_6 ) { // LoRa 250 kHz
        bandwidth = 1;
    }

    if ( LoRaMacDeviceClass != CLASS_C ) {
        LOG_TRACE("Open single Rx window 2 (Channel : %u / DR: %u).", Rx2Channel.Frequency,
                Datarates[Rx2Channel.Datarate]);
        LoRaMacRxWindowSetup(Rx2Channel.Frequency, Rx2Channel.Datarate, bandwidth, symbTimeout,
                false);
    } else {
        LOG_TRACE("Open continuous Rx window 2 (Channel : %u / DR: %u).", Rx2Channel.Frequency,
                Datarates[Rx2Channel.Datarate]);
        LoRaMacRxWindowSetup(Rx2Channel.Frequency, Rx2Channel.Datarate, bandwidth, symbTimeout,
                true);
    }
}

void OnRxSynchWindowTimerEvent( void )
{

}

void OnAdvBcnRxWindowTimerEvent( void )
{
    TimerStop(&AdvBcnRxWindowTimer);

    if ( LoRaMacEventFlags.Bits.RxSlot == 0 ) {
        uint64_t curTime = TimerGetCurrentTime();
        LOG_TRACE("Advertising beacon reception window closed (%d%d)", *(((int*) (&curTime)) + 1),
                curTime);
        Radio.Sleep();
    }
}

void OnAdvBcnTimerEvent( void )
{
    uint64_t curTime = TimerGetCurrentTime();
    LOG_TRACE("Advertising beacon timer event occurred (%d%d)", *(((int*) (&curTime)) + 1),
            curTime);

    TimerStop(&AdvBcnTimer);
    LoRaMacEventFlags.Bits.Rx = 0;

    if ( AdvertisingSlot.Periodicity != AdvBcnTimer.ReloadValue ) {
        /* Check if advertising slot periodicity */
        TimerSetValue(&AdvBcnTimer, AdvertisingSlot.Periodicity);
    }
    /* Schedule next advertising beacon */
    TimerStart(&AdvBcnTimer);

    /* Randomize sending of advertising beacon */
    TimerSetValue(&AdvBcnSendDelayTimer, randr(0, AdvertisingSlot.Duration));
    /* Start advertising beacon send delay timer */
    TimerStart(&AdvBcnSendDelayTimer);

    /* Open advertising beacon reception window */
    LoRaMacBcnRxWindowSetup();

    if ( IsLoRaMacNetworkJoined ) {
        TimerSetValue(&AdvBcnRxWindowTimer, AdvertisingSlot.Duration);
    } else {
        TimerSetValue(&AdvBcnRxWindowTimer, AdvertisingSlot.Duration * 3);
    }
    /* Start advertising beacon send delay timer */
    TimerStart(&AdvBcnRxWindowTimer);
}

void OnAdvBcnSendDelayTimerEvent( void )
{
    uint64_t currTime = TimerGetCurrentTime();
    LOG_TRACE("Advertising beacon send delay timer event occurred (%d%d)",
            *(((int*) (&currTime)) + 1), currTime);

    TimerStop(&AdvBcnSendDelayTimer);
    Radio.Standby();

    /* Send advertising beacon */
    LoRaMeshSendAdvertisingBeacon();
}

void OnMacStateCheckTimerEvent( void )
{
    TimerStop(&MacStateCheckTimer);

    if ( LoRaMacEventFlags.Bits.Tx == 1 ) {
        if ( NodeAckRequested == false ) {
            if ( LoRaMacEventFlags.Bits.JoinAccept == true ) {
                // Join messages aren't repeated automatically
                ChannelsNbRepCounter = ChannelsNbRep;
                UpLinkCounter = 0;
            }
            if ( ChannelsNbRepCounter >= ChannelsNbRep ) {
                ChannelsNbRepCounter = 0;

                LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_OK;

                AdrAckCounter++;
                if ( IsUpLinkCounterFixed == false ) {
                    UpLinkCounter++;
                }

                LoRaMacState &= ~MAC_TX_RUNNING;
            } else {
                LoRaMacEventFlags.Bits.Tx = 0;
                // Sends the same frame again
                if ( SetNextChannel() == 0 ) {
                    LoRaMacSendFrameOnChannel(Channels[Channel]);
                }
            }
        }

        if ( LoRaMacEventFlags.Bits.Rx == 1 ) {
            if ( (LoRaMacEventInfo.TxAckReceived == true)
                    || (AckTimeoutRetriesCounter > AckTimeoutRetries) ) {
                AckTimeoutRetry = false;
                if ( IsUpLinkCounterFixed == false ) {
                    UpLinkCounter++;
                }
                LoRaMacEventInfo.TxNbRetries = AckTimeoutRetriesCounter;

                LoRaMacState &= ~MAC_TX_RUNNING;
            }
        }

        if ( (AckTimeoutRetry == true) && ((LoRaMacState & MAC_CHANNEL_CHECK) == 0) ) {
            AckTimeoutRetry = false;
            if ( (AckTimeoutRetriesCounter < AckTimeoutRetries)
                    && (AckTimeoutRetriesCounter <= MAX_ACK_RETRIES) ) {
                AckTimeoutRetriesCounter++;

                if ( (AckTimeoutRetriesCounter % 2) == 1 ) {
                    ChannelsDatarate = MAX(ChannelsDatarate - 1, LORAMAC_MIN_DATARATE);
                }
                LoRaMacEventFlags.Bits.Tx = 0;
                // Sends the same frame again
                if ( SetNextChannel() == 0 ) {
                    LoRaMacSendFrameOnChannel(Channels[Channel]);
                }
            } else {
                // Re-enable default channels LC1, LC2, LC3
                ChannelsMask[0] = ChannelsMask[0] | (LC(1) + LC(2) + LC(3));
                LoRaMacState &= ~MAC_TX_RUNNING;

                LoRaMacEventInfo.TxAckReceived = false;
                LoRaMacEventInfo.TxNbRetries = AckTimeoutRetriesCounter;
                if ( IsUpLinkCounterFixed == false ) {
                    UpLinkCounter++;
                }
                LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_OK;
            }
        }
    }
// Handle reception for Class B and Class C
    if ( (LoRaMacState & MAC_RX) == MAC_RX ) {
        LoRaMacState &= ~MAC_RX;
    }
    if ( LoRaMacState == MAC_IDLE ) {
        Notify(&LoRaMacEventFlags, &LoRaMacEventInfo);
    } else {
        // Operation not finished restart timer
        TimerStart(&MacStateCheckTimer);
    }
}

void OnAckTimeoutTimerEvent( void )
{
    TimerStop(&AckTimeoutTimer);

    AckTimeoutRetry = true;
    LoRaMacState &= ~MAC_ACK_REQ;
}

/*****************************************************************************
 *                                                                           *
 * Utility functions implementation                                          *
 *                                                                           *
 *****************************************************************************/
void ProcessAdvertisingBeacon( uint8_t *payload, uint16_t size )
{
    uint32_t nwkId, cAddr, advTime, advPeriodicity, advDuration;

    nwkId = (payload[0] & 0xFF);
    nwkId |= ((payload[1] & 0xFF) << 8);
    nwkId |= ((payload[2] & 0xFF) << 16);

    if ( IsLoRaMacNetworkJoined && (nwkId != LoRaMacNetID) ) return; /* Advertising beacon from different network */

    if ( !IsLoRaMacNetworkJoined ) {
        /* Send join request */
    }

    cAddr = (uint32_t)(payload[4] & 0xFF);
    cAddr |= (uint32_t)((payload[5] & 0xFF) << 8);
    cAddr |= (uint32_t)((payload[6] & 0xFF) << 16);
    cAddr |= (uint32_t)((payload[7] & 0xFF) << 24);

    if ( CoordinatorAddr != cAddr ) {
        if ( cAddr != 0 ) {
            /* Coordinator has been lost */
            if ( EvaluateNominationProbability(CalculateNodeRank()) ) {
                CoordinatorAddr = LoRaMacDevAddr;
            } else {
                CoordinatorAddr = 0U;
            }
        } else {
            /* Coordinator has changed */
            uint8_t cRank, nRank;
            cRank = (uint8_t)(payload[3] & 0xF);
            nRank = CalculateNodeRank();

            if ( (nRank > cRank) && EvaluateNominationProbability(nRank) )
                CoordinatorAddr = LoRaMacDevAddr; /* Nominate ourself */
            else
                CoordinatorAddr = cAddr; /* Vote for the other node */
        }
    }

    advTime = (uint32_t)(payload[8] & 0xFF);
    advTime |= (uint32_t)((payload[9] & 0xFF) << 8);
    advTime |= (uint32_t)((payload[10] & 0xFF) << 16);
    advTime |= (uint32_t)((payload[11] & 0xFF) << 24);
    advPeriodicity = (uint32_t)((payload[12] & 0xFF) * 1000000);
    advDuration = (uint32_t)((payload[13] & 0xFF) * 1000);

    if ( AdvertisingSlot.Periodicity != advPeriodicity ) {
        /* Advertising slot periodicity changed */
        uint32_t nextBcnDelay;
        AdvertisingSlot.Periodicity = advPeriodicity;
        nextBcnDelay = advTime - GpsGetCurrentUnixTime();
        TimerStop(&AdvBcnTimer);
        TimerSetValue(&AdvBcnTimer, nextBcnDelay);
        TimerStart(&AdvBcnTimer);
    }
    if ( AdvertisingSlot.Duration != advDuration ) {
        /* Advertising slot duration changed */
        AdvertisingSlot.Duration = advDuration;
    }
}

void ProcessDataFrame( uint8_t* payload, uint16_t size, int16_t rssi, int8_t snr )
{
    LoRaMacFrameCtrl_t fCtrl;

    uint8_t pktHeaderLen = 0;
    uint32_t address = 0;
    uint8_t appPayloadStartIndex = 0;
    uint8_t port = 0xFF;
    uint8_t frameLen = 0;
    uint32_t mic = 0;
    uint32_t micRx = 0;

    uint16_t sequenceCounter = 0;
    uint16_t sequenceCounterPrev = 0;
    uint16_t sequenceCounterDiff = 0;
    uint32_t linkCounter = 0;

    MulticastGroupInfo_t *curMulticastGrp = NULL;
    ChildNodeInfo_t *curChildNode = NULL;
    uint8_t *nwkSKey = LoRaMacNwkSKey;
    uint8_t *appSKey = LoRaMacAppSKey;

    bool isMicOk = false;
    FrameDirection_t direction;
    LoRaMacHeader_t macHdr;

    macHdr.Value = payload[pktHeaderLen++];

    if ( (macHdr.Bits.MType == FRAME_TYPE_DATA_UNCONFIRMED_UP)
            || (macHdr.Bits.MType == FRAME_TYPE_DATA_CONFIRMED_UP) ) {
        direction = UP_LINK;
    } else if ( (macHdr.Bits.MType == FRAME_TYPE_DATA_UNCONFIRMED_DOWN)
            || (macHdr.Bits.MType == FRAME_TYPE_DATA_CONFIRMED_DOWN) ) {
        direction = DOWN_LINK;
    } else {
        return;
    }

    address = payload[pktHeaderLen++];
    address |= ((uint32_t) payload[pktHeaderLen++] << 8);
    address |= ((uint32_t) payload[pktHeaderLen++] << 16);
    address |= ((uint32_t) payload[pktHeaderLen++] << 24);

    if ( direction == UP_LINK ) {
        /* Up link, therefore child node */
        curChildNode = ChildNodeFind(address);
        if ( curChildNode != NULL ) {
            nwkSKey = curChildNode->NwkSKey;
            appSKey = curChildNode->AppSKey;
            linkCounter = curChildNode->UpLinkCounter;
        } else {
            /* We are not the destination of this frame. */
            LOG_ERROR("Address didn't match any child node");
            LoRaMacEventFlags.Bits.Tx = 1;
            LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_ADDRESS_FAIL;
            LoRaMacState &= ~MAC_TX_RUNNING;
            return;
        }
    } else {
        /* Down link, therefore either from parent node or multicast group */
        if ( address != LoRaMacDevAddr ) {
            curMulticastGrp = MulticastGroupFind(address);
            if ( curMulticastGrp != NULL ) {
                LoRaMacEventFlags.Bits.Multicast = 1;
                nwkSKey = curMulticastGrp->NwkSKey;
                appSKey = curMulticastGrp->AppSKey;
                linkCounter = curMulticastGrp->DownLinkCounter;
            } else {
                /* We are not the destination of this frame. */
                LoRaMacEventFlags.Bits.Tx = 1;
                LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_ADDRESS_FAIL;
                LoRaMacState &= ~MAC_TX_RUNNING;
                return;
            }
        } else {
            LoRaMacEventFlags.Bits.Multicast = 0;
            nwkSKey = LoRaMacNwkSKey;
            appSKey = LoRaMacAppSKey;
            linkCounter = DownLinkCounter;
        }
    }

    if ( LoRaMacDeviceClass != CLASS_A ) {
        LoRaMacState |= MAC_RX;
        // Starts the MAC layer status check timer
        TimerStart(&MacStateCheckTimer);
    }
    fCtrl.Value = payload[pktHeaderLen++];

    sequenceCounter = (uint16_t) payload[pktHeaderLen++];
    sequenceCounter |= (uint16_t) payload[pktHeaderLen++] << 8;

    appPayloadStartIndex = 8 + fCtrl.Bits.FOptsLen;

    micRx |= (uint32_t) payload[size - LORAMAC_MFR_LEN];
    micRx |= ((uint32_t) payload[size - LORAMAC_MFR_LEN + 1] << 8);
    micRx |= ((uint32_t) payload[size - LORAMAC_MFR_LEN + 2] << 16);
    micRx |= ((uint32_t) payload[size - LORAMAC_MFR_LEN + 3] << 24);

    sequenceCounterPrev = (uint16_t) linkCounter;
    sequenceCounterDiff = (sequenceCounter - sequenceCounterPrev);

    if ( sequenceCounterDiff < (1 << 15) ) {
        linkCounter += sequenceCounterDiff;
        LoRaMacComputeMic(payload, size - LORAMAC_MFR_LEN, nwkSKey, address, direction, linkCounter,
                &mic);
        if ( micRx == mic ) {
            isMicOk = true;
        }
    } else {
        // check for link counter roll-over
        uint32_t linkCounterTmp = linkCounter + 0x10000 + (int16_t) sequenceCounterDiff;
        LoRaMacComputeMic(payload, size - LORAMAC_MFR_LEN, nwkSKey, address, direction,
                linkCounterTmp, &mic);
        if ( micRx == mic ) {
            isMicOk = true;
            linkCounterTmp = linkCounterTmp;
        }
    }

    if ( isMicOk ) {
        LoRaMacEventFlags.Bits.Rx = 1;
        LoRaMacEventInfo.RxSnr = snr;
        LoRaMacEventInfo.RxRssi = rssi;
        LoRaMacEventInfo.RxBufferSize = 0;
        AdrAckCounter = 0;

        // Update 32 bits downlink counter
        if ( LoRaMacEventFlags.Bits.Multicast == 1 ) {
            curMulticastGrp->DownLinkCounter = linkCounter;
        } else {
            DownLinkCounter = linkCounter;
        }

        if ( macHdr.Bits.MType == FRAME_TYPE_DATA_CONFIRMED_DOWN ) {
            SrvAckRequested = true;
        } else {
            SrvAckRequested = false;
        }

        // Check if the frame is an acknowledgement
        if ( fCtrl.Bits.Ack == 1 ) {
            LoRaMacEventInfo.TxAckReceived = true;

            // Stop the AckTimeout timer as no more retransmissions
            // are needed.
            TimerStop(&AckTimeoutTimer);
        } else {
            LoRaMacEventInfo.TxAckReceived = false;
            if ( AckTimeoutRetriesCounter > AckTimeoutRetries ) {
                // Stop the AckTimeout timer as no more retransmissions
                // are needed.
                TimerStop(&AckTimeoutTimer);
            }
        }

        if ( (fCtrl.Bits.FOptsLen > 0) && (LoRaMacEventFlags.Bits.Multicast == 0) ) {
            // Decode Options field MAC commands
            ProcessMacCommands(payload, 8, appPayloadStartIndex);
        }

        if ( ((size - 4) - appPayloadStartIndex) > 0 ) {
            port = payload[appPayloadStartIndex++];
            frameLen = (size - 4) - appPayloadStartIndex;

            if ( port == 0 ) {
                LoRaMacPayloadDecrypt(payload + appPayloadStartIndex, frameLen, nwkSKey, address,
                        direction, linkCounter, LoRaMacRxPayload);

                // Decode frame payload MAC commands
                ProcessMacCommands(LoRaMacRxPayload, 0, frameLen);
            } else {
                LoRaMacPayloadDecrypt(payload + appPayloadStartIndex, frameLen, appSKey, address,
                        direction, linkCounter, LoRaMacRxPayload);

                LoRaMacEventFlags.Bits.RxData = 1;
                LoRaMacEventInfo.RxPort = port;
                LoRaMacEventInfo.RxBuffer = LoRaMacRxPayload;
                LoRaMacEventInfo.RxBufferSize = frameLen;
            }
        }

        LoRaMacEventFlags.Bits.Tx = 1;
        LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_OK;
    } else {
        LoRaMacEventInfo.TxAckReceived = false;

        LoRaMacEventFlags.Bits.Tx = 1;
        LoRaMacEventInfo.Status = LORAMAC_EVENT_INFO_STATUS_MIC_FAIL;
        LoRaMacState &= ~MAC_TX_RUNNING;
    }
}

uint8_t AddMacCommand( uint8_t cmd, uint8_t p1, uint8_t p2 )
{
    if ( MacCommandsBufferIndex > 15 ) {
        return 2;
    }

    MacCommandsBuffer[MacCommandsBufferIndex++] = cmd;
    switch (cmd) {
        case MOTE_MAC_LINK_CHECK_REQ:
            // No payload for this command
            break;
        case MOTE_MAC_LINK_ADR_ANS:
            // Margin
            MacCommandsBuffer[MacCommandsBufferIndex++] = p1;
            break;
        case MOTE_MAC_DUTY_CYCLE_ANS:
            // No payload for this answer
            break;
        case MOTE_MAC_RX_PARAM_SETUP_ANS:
            // Status: Datarate ACK, Channel ACK
            MacCommandsBuffer[MacCommandsBufferIndex++] = p1;
            break;
        case MOTE_MAC_DEV_STATUS_ANS:
            // 1st byte Battery
            // 2nd byte Margin
            MacCommandsBuffer[MacCommandsBufferIndex++] = p1;
            MacCommandsBuffer[MacCommandsBufferIndex++] = p2;
            break;
        case MOTE_MAC_NEW_CHANNEL_ANS:
            // Status: Datarate range OK, Channel frequency OK
            MacCommandsBuffer[MacCommandsBufferIndex++] = p1;
            break;
        case MOTE_MAC_RX_TIMING_SETUP_ANS:
            // No payload for this answer
            break;
        default:
            return 1;
    }
    if ( MacCommandsBufferIndex <= 15 ) {
        MacCommandsInNextTx = true;
        return 0;
    } else {
        return 2;
    }
}

void ProcessMacCommands( uint8_t *payload, uint8_t macIndex, uint8_t commandsSize )
{
    while (macIndex < commandsSize) {
        // Decode Frame MAC commands
        switch (payload[macIndex++]) {
            case SRV_MAC_LINK_CHECK_ANS:
                LoRaMacEventFlags.Bits.LinkCheck = 1;
                LoRaMacEventInfo.DemodMargin = payload[macIndex++];
                LoRaMacEventInfo.NbGateways = payload[macIndex++];
                break;
            case SRV_MAC_LINK_ADR_REQ:
            {
                uint8_t status = 0x07;
                uint16_t chMask;
                int8_t txPower = 0;
                int8_t datarate = 0;
                uint8_t nbRep = 0;
                uint8_t chMaskCntl = 0;
                uint16_t channelsMask[6] = { 0, 0, 0, 0, 0, 0 };

                // Initialize local copy of the channels mask array
                for ( uint8_t i = 0; i < 6; i++ ) {
                    channelsMask[i] = ChannelsMask[i];
                }
                datarate = payload[macIndex++];
                txPower = datarate & 0x0F;
                datarate = (datarate >> 4) & 0x0F;

                if ( (AdrCtrlOn == false)
                        && ((ChannelsDatarate != datarate) || (ChannelsTxPower != txPower)) ) { // ADR disabled don't handle ADR requests if server tries to change datarate or txpower
                                                                                                // Answer the server with fail status
                                                                                                // Power ACK     = 0
                                                                                                // Data rate ACK = 0
                                                                                                // Channel mask  = 0
                    AddMacCommand(MOTE_MAC_LINK_ADR_ANS, 0, 0);
                    macIndex += 3;  // Skip over the remaining bytes of the request
                    break;
                }
                chMask = (uint16_t) payload[macIndex++];
                chMask |= (uint16_t) payload[macIndex++] << 8;

                nbRep = payload[macIndex++];
                chMaskCntl = (nbRep >> 4) & 0x07;
                nbRep &= 0x0F;
                if ( nbRep == 0 ) {
                    nbRep = 1;
                }
                if ( (chMaskCntl == 0) && (chMask == 0) ) {
                    status &= 0xFE; // Channel mask KO
                } else if ( (chMaskCntl >= 1) && (chMaskCntl <= 5) ) {
                    // RFU
                    status &= 0xFE; // Channel mask KO
                } else {
                    for ( uint8_t i = 0; i < LORA_MAX_NB_CHANNELS; i++ ) {
                        if ( chMaskCntl == 6 ) {
                            if ( Channels[i].Frequency != 0 ) {
                                chMask |= 1 << i;
                            }
                        } else {
                            if ( ((chMask & (1 << i)) != 0) && (Channels[i].Frequency == 0) ) { // Trying to enable an undefined channel
                                status &= 0xFE; // Channel mask KO
                            }
                        }
                    }
                    channelsMask[0] = chMask;
                }
                if ( ((datarate < LORAMAC_MIN_DATARATE) || (datarate > LORAMAC_MAX_DATARATE))
                        == true ) {
                    status &= 0xFD; // Datarate KO
                }

                //
                // Remark MaxTxPower = 0 and MinTxPower = 5
                //
                if ( ((LORAMAC_MAX_TX_POWER <= txPower) && (txPower <= LORAMAC_MIN_TX_POWER))
                        == false ) {
                    status &= 0xFB; // TxPower KO
                }
                if ( (status & 0x07) == 0x07 ) {
                    ChannelsDatarate = datarate;
                    ChannelsTxPower = txPower;
                    ChannelsMask[0] = channelsMask[0];
                    ChannelsMask[1] = channelsMask[1];
                    ChannelsMask[2] = channelsMask[2];
                    ChannelsMask[3] = channelsMask[3];
                    ChannelsMask[4] = channelsMask[4];
                    ChannelsMask[5] = channelsMask[5];
                    ChannelsNbRep = nbRep;
                }
                AddMacCommand(MOTE_MAC_LINK_ADR_ANS, status, 0);
            }
                break;
            case SRV_MAC_DUTY_CYCLE_REQ:
                MaxDCycle = payload[macIndex++];
                AggregatedDCycle = 1 << MaxDCycle;
                AddMacCommand(MOTE_MAC_DUTY_CYCLE_ANS, 0, 0);
                break;
            case SRV_MAC_RX_PARAM_SETUP_REQ:
            {
                uint8_t status = 0x07;
                int8_t datarate = 0;
                int8_t drOffset = 0;
                uint32_t freq = 0;

                drOffset = (payload[macIndex] >> 4) & 0x07;
                datarate = payload[macIndex] & 0x0F;
                macIndex++;
                freq = (uint32_t) payload[macIndex++];
                freq |= (uint32_t) payload[macIndex++] << 8;
                freq |= (uint32_t) payload[macIndex++] << 16;
                freq *= 100;

                if ( Radio.CheckRfFrequency(freq) == false ) {
                    status &= 0xFE; // Channel frequency KO
                }

                if ( ((datarate < LORAMAC_MIN_DATARATE) || (datarate > LORAMAC_MAX_DATARATE))
                        == true ) {
                    status &= 0xFD; // Datarate KO
                }

                if ( ((drOffset < LORAMAC_MIN_RX1_DR_OFFSET)
                        || (drOffset > LORAMAC_MAX_RX1_DR_OFFSET)) == true ) {
                    status &= 0xFB; // Rx1DrOffset range KO
                }

                if ( (status & 0x07) == 0x07 ) {
                    Rx2Channel.Datarate = datarate;
                    Rx2Channel.Frequency = freq;
                    Rx1DrOffset = drOffset;
                }
                AddMacCommand(MOTE_MAC_RX_PARAM_SETUP_ANS, status, 0);
            }
                break;
            case SRV_MAC_DEV_STATUS_REQ:
            {
                uint8_t batteryLevel = BAT_LEVEL_NO_MEASURE;
                if ( (LoRaMacCallbacks != NULL) && (LoRaMacCallbacks->GetBatteryLevel != NULL) ) {
                    batteryLevel = LoRaMacCallbacks->GetBatteryLevel();
                }
                AddMacCommand(MOTE_MAC_DEV_STATUS_ANS, batteryLevel, LoRaMacEventInfo.RxSnr);
            }
                break;
            case SRV_MAC_NEW_CHANNEL_REQ:
            {
                uint8_t status = 0x03;
                int8_t channelIndex = 0;
                ChannelParams_t chParam;

                channelIndex = payload[macIndex++];
                chParam.Frequency = (uint32_t) payload[macIndex++];
                chParam.Frequency |= (uint32_t) payload[macIndex++] << 8;
                chParam.Frequency |= (uint32_t) payload[macIndex++] << 16;
                chParam.Frequency *= 100;
                chParam.DrRange.Value = payload[macIndex++];

                if ( (channelIndex < 3) || (channelIndex > LORA_MAX_NB_CHANNELS) ) {
                    status &= 0xFE; // Channel frequency KO
                }

                if ( Radio.CheckRfFrequency(chParam.Frequency) == false ) {
                    status &= 0xFE; // Channel frequency KO
                }

                if ( (chParam.DrRange.Fields.Min > chParam.DrRange.Fields.Max)
                        || (((LORAMAC_MIN_DATARATE <= chParam.DrRange.Fields.Min)
                                && (chParam.DrRange.Fields.Min <= LORAMAC_MAX_DATARATE)) == false)
                        || (((LORAMAC_MIN_DATARATE <= chParam.DrRange.Fields.Max)
                                && (chParam.DrRange.Fields.Max <= LORAMAC_MAX_DATARATE)) == false) ) {
                    status &= 0xFD; // Datarate range KO
                }
                if ( (status & 0x03) == 0x03 ) {
                    LoRaMacSetChannel(channelIndex, chParam);
                }
                AddMacCommand(MOTE_MAC_NEW_CHANNEL_ANS, status, 0);
            }
                break;
            case SRV_MAC_RX_TIMING_SETUP_REQ:
            {
                uint8_t delay = payload[macIndex++] & 0x0F;

                if ( delay == 0 ) {
                    delay++;
                }
                ReceiveDelay1 = delay * 1e6;
                ReceiveDelay2 = ReceiveDelay1 + 1e6;
                AddMacCommand(MOTE_MAC_RX_TIMING_SETUP_ANS, 0, 0);
            }
                break;
            default:
                // Unknown command. ABORT MAC commands processing
                return;
        }
    }
}

// TODO: Add Documentation
void Notify( LoRaMacEventFlags_t *flags, LoRaMacEventInfo_t *info )
{
    if ( (LoRaMacCallbacks != NULL) && (LoRaMacCallbacks->MacEvent != NULL) ) {
        LoRaMacCallbacks->MacEvent(flags, info);
    }
    flags->Value = 0;
}

uint8_t SetNextChannel( void )
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
        if ( DutyCycleOn == true ) {
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
            if ( (ChannelsMask[k] & (1 << j)) != 0 ) {
                if ( Channels[i + j].Frequency == 0 ) { // Check if the channel is enabled
                    continue;
                }
                if ( ((Channels[i + j].DrRange.Fields.Min <= ChannelsDatarate)
                        && (ChannelsDatarate <= Channels[i + j].DrRange.Fields.Max)) == false ) { // Check if the current channel selection supports the given datarate
                    continue;
                }
                if ( Bands[Channels[i + j].Band].TimeOff > 0 ) { // Check if the band is available for transmission
                    continue;
                }
                if ( AggregatedTimeOff > 0 ) { // Check if there is time available for transmission
                    continue;
                }
                enabledChannels[nbEnabledChannels++] = i + j;
            }
        }
    }
    if ( nbEnabledChannels > 0 ) {
        Channel = enabledChannels[randr(0, nbEnabledChannels - 1)];
        LoRaMacState &= ~MAC_CHANNEL_CHECK;
        TimerStop(&ChannelCheckTimer);
        return 0;
    }
// No free channel found.
// Check again
    if ( (LoRaMacState & MAC_CHANNEL_CHECK) == 0 ) {
        TimerSetValue(&ChannelCheckTimer, minTime);
        TimerStart(&ChannelCheckTimer);
        LoRaMacState |= MAC_CHANNEL_CHECK;
    }
    return 1;
}

bool ValidatePayloadLength( uint8_t lenN, int8_t datarate )
{
    bool payloadSizeOk = false;
    uint8_t maxN = 0;

// Get the maximum payload length
    if ( RepeaterSupport == true ) {
        maxN = MaxPayloadOfDatarateRepeater[datarate];
    } else {
        maxN = MaxPayloadOfDatarate[datarate];
    }

// Validation of the application payload size
    if ( lenN <= maxN ) {
        payloadSizeOk = true;
    }

    return payloadSizeOk;
}

int8_t LimitTxPower( int8_t txPower )
{
    int8_t resultTxPower = txPower;

    return resultTxPower;
}

bool EvaluateNominationProbability( uint8_t nodeRank )
{
    (void) nodeRank;
    return true;
}

uint8_t CalculateNodeRank( void )
{
    return 1;
}

ChildNodeInfo_t* CreateChildNode( uint32_t devAddr, uint8_t* nwkSKey, uint8_t* appSKey,
        uint32_t channel, uint32_t interval )
{
    ChildNodeInfo_t* newNode = (ChildNodeInfo_t*) malloc(sizeof(ChildNodeInfo_t));
    newNode->Address = devAddr;
    memcpy(newNode->NwkSKey, nwkSKey, 16);
    memcpy(newNode->AppSKey, appSKey, 16);
    newNode->UpLinkCounter = 0;
    newNode->UpLinkSlot.Frequency = channel;
    newNode->UpLinkSlot.Periodicity = interval;
    newNode->UpLinkSlot.Duration = DEFAULT_RX_WINDOW;

    return newNode;
}

void ChildNodeRemove( ChildNodeInfo_t* childNode )
{
    if ( ChildNodes != NULL ) {
        ListRemove(ChildNodes, (void*) childNode);
        free(childNode);
    }
}

void ChildNodeAdd( ChildNodeInfo_t* childNode )
{
// Reset uplink counter
    childNode->UpLinkCounter = 0;

    if ( ChildNodes == NULL ) {
        ChildNodes = ListCreate();
    }
    ListPushBack(ChildNodes, (void*) childNode);
}

ChildNodeInfo_t* ChildNodeFind( uint32_t devAddr )
{
    ChildNodeInfo_t* tempNode;
    ListNodePointer_t listNode;

    if ( ChildNodes != NULL ) {
        listNode = ChildNodes->head;

        while (listNode != NULL) {
            tempNode = (ChildNodeInfo_t*) listNode->data;
            if ( tempNode->Address == devAddr ) return tempNode;
            listNode = listNode->next;
        }
    }

    return NULL;
}

void ChildNodePrint( ChildNodeInfo_t* childNode )
{
    uint8_t j;
    LOG_DEBUG_BARE("%-15s: 0x%08x\r\n", "Address", childNode->Address);
    LOG_DEBUG_BARE("%-15s: ", "NwkSKey");
    for ( j = 0; j < 16; j++ )
        LOG_DEBUG_BARE("0x%02x ", childNode->NwkSKey[j]);
    LOG_DEBUG_BARE("\r\n%-15s: ", "AppSKey");
    for ( j = 0; j < 16; j++ )
        LOG_DEBUG_BARE("0x%02x ", childNode->AppSKey[j]);
    LOG_DEBUG_BARE("%-15s: 0x%08x\r\n", "UpLinkCounter", childNode->UpLinkCounter);
    LOG_DEBUG_BARE("\r\n---- %-15s ----\r\n", "Uplink Slot Info");
    LOG_DEBUG_BARE("%-15s: %u\r\n", "Frequency", childNode->UpLinkSlot.Frequency);
    LOG_DEBUG_BARE("%-15s: %u\r\n", "Periodicity", childNode->UpLinkSlot.Periodicity);
    LOG_DEBUG_BARE("%-15s: %u\r\n", "Duration", childNode->UpLinkSlot.Duration);
}

MulticastGroupInfo_t* CreateMulticastGroup( uint32_t grpAddr, uint8_t* nwkSKey, uint8_t* appSKey,
        uint32_t channel, uint32_t interval )
{
    MulticastGroupInfo_t* newGrp = (MulticastGroupInfo_t*) malloc(sizeof(MulticastGroupInfo_t));
    newGrp->Address = grpAddr;
    memcpy(newGrp->NwkSKey, nwkSKey, 16);
    memcpy(newGrp->AppSKey, appSKey, 16);
    newGrp->DownLinkCounter = 0;
    newGrp->DownLinkSlot.Frequency = channel;
    newGrp->DownLinkSlot.Periodicity = interval;
    newGrp->DownLinkSlot.Duration = DEFAULT_RX_WINDOW;

    return newGrp;
}

void MulticastGroupAdd( MulticastGroupInfo_t *multicastGrp )
{
// Reset downlink counter
    multicastGrp->DownLinkCounter = 0;

    if ( MulticastGroups == NULL ) {
        MulticastGroups = ListCreate();
    }

    ListPushBack(MulticastGroups, (void*) multicastGrp);
}

void MulticastGroupRemove( MulticastGroupInfo_t *multicastGrp )
{
    if ( MulticastGroups != NULL ) {
        ListRemove(MulticastGroups, (void*) multicastGrp);
        free(multicastGrp);
    }
}

MulticastGroupInfo_t* MulticastGroupFind( uint32_t grpAddr )
{
    MulticastGroupInfo_t* tempGrp;
    ListNodePointer_t listNode;

    if ( ChildNodes != NULL ) {
        listNode = MulticastGroups->head;

        while (listNode != NULL) {
            tempGrp = (MulticastGroupInfo_t*) listNode->data;
            if ( tempGrp->Address == grpAddr ) return tempGrp;
            listNode = listNode->next;
        }
    }

    return NULL;
}

void MulticastGroupPrint( MulticastGroupInfo_t* multicastGrp )
{
    uint8_t j;
    LOG_DEBUG_BARE("%-15s: 0x%08x\r\n", "Address", multicastGrp->Address);
    LOG_DEBUG_BARE("%-15s: ", "NwkSKey");
    for ( j = 0; j < 16; j++ )
        LOG_DEBUG_BARE("0x%02x ", multicastGrp->NwkSKey[j]);
    LOG_DEBUG_BARE("\r\n%-15s: ", "AppSKey");
    for ( j = 0; j < 16; j++ )
        LOG_DEBUG_BARE("0x%02x ", multicastGrp->AppSKey[j]);
    LOG_DEBUG_BARE("%-15s: 0x%08x\r\n", "UpLinkCounter", multicastGrp->DownLinkCounter);
    LOG_DEBUG_BARE("\r\n---- %-15s ----\r\n", "Downlink Slot Info");
    LOG_DEBUG_BARE("%-15s: %u\r\n", "Frequency", multicastGrp->DownLinkSlot.Frequency);
    LOG_DEBUG_BARE("%-15s: %u\r\n", "Periodicity", multicastGrp->DownLinkSlot.Periodicity);
    LOG_DEBUG_BARE("%-15s: %u\r\n", "Duration", multicastGrp->DownLinkSlot.Duration);
}

/*****************************************************************************
 *                                                                           *
 * Setup functions implementation                                            *
 *                                                                           *
 *****************************************************************************/
void LoRaMacSetDeviceClass( DeviceClass_t deviceClass )
{
    LoRaMacDeviceClass = deviceClass;
}

void LoRaMacSetPublicNetwork( bool enable )
{
    PublicNetwork = enable;
    Radio.SetModem(MODEM_LORA);
    if ( PublicNetwork == true ) {
        // Change LoRa modem SyncWord
        Radio.Write(REG_LR_SYNCWORD, LORA_MAC_PUBLIC_SYNCWORD);
    } else {
        // Change LoRa modem SyncWord
        Radio.Write(REG_LR_SYNCWORD, LORA_MAC_PRIVATE_SYNCWORD);
    }
}

void LoRaMacSetChannel( uint8_t id, ChannelParams_t params )
{
    params.Band = 0;
    Channels[id] = params;
// Activate the newly created channel
    if ( id < 16 ) {
        ChannelsMask[0] |= 1 << id;
    } else if ( id < 32 ) {
        ChannelsMask[1] |= 1 << (id - 16);
    } else if ( id < 48 ) {
        ChannelsMask[2] |= 1 << (id - 32);
    } else if ( id < 64 ) {
        ChannelsMask[3] |= 1 << (id - 48);
    } else if ( id < 72 ) {
        ChannelsMask[4] |= 1 << (id - 64);
    } else {
        // Don't activate the channel
    }
#if defined( USE_BAND_868 )
    if( ( Channels[id].Frequency >= 865000000 ) && ( Channels[id].Frequency <= 868000000 ) )
    {
        if( Channels[id].Band != BAND_G1_0 )
        {
            Channels[id].Band = BAND_G1_0;
        }
    }
    else if( ( Channels[id].Frequency > 868000000 ) && ( Channels[id].Frequency <= 868600000 ) )
    {
        if( Channels[id].Band != BAND_G1_1 )
        {
            Channels[id].Band = BAND_G1_1;
        }
    }
    else if( ( Channels[id].Frequency >= 868700000 ) && ( Channels[id].Frequency <= 869200000 ) )
    {
        if( Channels[id].Band != BAND_G1_2 )
        {
            Channels[id].Band = BAND_G1_2;
        }
    }
    else if( ( Channels[id].Frequency >= 869400000 ) && ( Channels[id].Frequency <= 869650000 ) )
    {
        if( Channels[id].Band != BAND_G1_3 )
        {
            Channels[id].Band = BAND_G1_3;
        }
    }
    else if( ( Channels[id].Frequency >= 869700000 ) && ( Channels[id].Frequency <= 870000000 ) )
    {
        if( Channels[id].Band != BAND_G1_4 )
        {
            Channels[id].Band = BAND_G1_4;
        }
    }
    else
    {
        Channels[id].Frequency = 0;
        Channels[id].DrRange.Value = 0;
    }
#else
#error "Please define a frequency band in the compiler options."
#endif
// Check if it is a valid channel
    if ( Channels[id].Frequency == 0 ) {
        LoRaMacChannelRemove(id);
    }
}

void LoRaMacChannelRemove( uint8_t id )
{
    if ( (LoRaMacState & MAC_TX_RUNNING) == MAC_TX_RUNNING ) {
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
    ChannelsMask[index] &= ~(1 << (id % 16));

    return;
}

void LoRaMacSetRx2Channel( Rx2ChannelParams_t param )
{
    Rx2Channel = param;
}

void LoRaMacSetChannelsTxPower( int8_t txPower )
{
    if ( (txPower >= LORAMAC_MAX_TX_POWER) && (txPower <= LORAMAC_MIN_TX_POWER) ) {
        ChannelsTxPower = txPower;
    }
}

void LoRaMacSetChannelsDatarate( int8_t datarate )
{
    ChannelsDefaultDatarate = ChannelsDatarate = datarate;
}

void LoRaMacSetChannelsMask( uint16_t *mask )
{
    if ( (mask[0] & 0x0007) != 0x0007 ) {
    } else {
        LoRaMacMemCpy((uint8_t*) mask, (uint8_t*) ChannelsMask, 2);
    }
}

void LoRaMacSetChannelsNbRep( uint8_t nbRep )
{
    if ( nbRep < 1 ) {
        nbRep = 1;
    }
    if ( nbRep > 15 ) {
        nbRep = 15;
    }
    ChannelsNbRep = nbRep;
}

void LoRaMacSetMaxRxWindow( uint32_t delay )
{
    MaxRxWindow = delay;
}

void LoRaMacSetReceiveDelay1( uint32_t delay )
{
    ReceiveDelay1 = delay;
}

void LoRaMacSetReceiveDelay2( uint32_t delay )
{
    ReceiveDelay2 = delay;
}

void LoRaMacSetJoinAcceptDelay1( uint32_t delay )
{
    JoinAcceptDelay1 = delay;
}

void LoRaMacSetJoinAcceptDelay2( uint32_t delay )
{
    JoinAcceptDelay2 = delay;
}

uint32_t LoRaMacGetUpLinkCounter( void )
{
    return UpLinkCounter;
}

uint32_t LoRaMacGetDownLinkCounter( void )
{
    return DownLinkCounter;
}

/*****************************************************************************
 *                                                                           *
 * Override test functions implementation                                    *
 *                                                                           *
 *****************************************************************************/
void LoRaMacTestSetDutyCycleOn( bool enable )
{
    DutyCycleOn = enable;
}

void LoRaMacTestRxWindowsOn( bool enable )
{
    IsRxWindowsEnabled = enable;
}

void LoRaMacTestSetMic( uint16_t upLinkCounter )
{
    UpLinkCounter = upLinkCounter;
    IsUpLinkCounterFixed = true;
}
