/**
 * \file LoRaMesh.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 08.12.2015
 * \version 1.0
 *
 * \brief LoRa stack medium access layer implementation
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"

#include "LoRaMacCrypto.h"
#include "LoRaMesh.h"

#define LOG_LEVEL_ERROR
#include "debug.h"
/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
#define MAX_NOF_SCHEDULER_EVENTS            LORAMESH_CONFIG_MAX_NOF_SCHEDULER_EVENTS
#define MAX_NOF_SCHEDULER_EVENT_HANDLERS    LORAMESH_CONFIG_MAX_NOF_SCHEDULER_EVENT_HANDLERS
#define MAX_NOF_MULTICAST_GROUPS            LORAMESH_CONFIG_MAX_NOF_MULTICAST_GROUPS
#define MAX_NOF_CHILD_NODES                 LORAMESH_CONFIG_MAX_NOF_CHILD_NODES
#define MAX_NOF_PORT_HANDLERS               LORAMESH_CONFIG_MAX_NOF_PORT_HANDLERS

#define ADVERTISING_INTERVAL_US             (30000000)
#define ADVERTISING_INTERVAL_MS             (ADVERTISING_INTERVAL_US / 1000)
#define ADVERTISING_INTERVAL_SEC            (ADVERTISING_INTERVAL_MS / 1000)
#define ADVERTISING_GUARD_TIME              (2280000)
#define ADVERTISING_RESERVED_TIME           (2120000)
#define AVAILABLE_SLOT_TIME                 (ADVERTISING_INTERVAL_US-ADVERTISING_GUARD_TIME-ADVERTISING_RESERVED_TIME)
#define TIME_PER_SLOT                       (50000)
#define NOF_AVAILABLE_SLOTS                 (AVAILABLE_SLOT_TIME / TIME_PER_SLOT)

#define RECEPTION_RESERVED_TIME             (50000)
/*******************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
/*! LoRaMesh upper layer event functions */
static LoRaMeshCallbacks_t *LoRaMeshCallbacks;

/*! LoRaWAN device pointer */
static LoRaDevice_t LoRaDevice = {
    .devAddr = 0x00,
    .netId = 0x00,
    .devAddr = 0x00,
    .devEui = NULL,
    .devNonce = 0x00,
    .devClass = CLASS_A,
    .devRole = NODE,
    .coordinatorAddr = 0x00,
    .appEui = NULL,
    .appKey = NULL,
    .childNodes = NULL,
    .multicastGroups = NULL,
    .channelsMask = {0},
    .currChannelIndex = 0u,
    .currDataRateIndex = LORAMAC_DEFAULT_DATARATE,
    .currTxPowerIndex = LORAMAC_DEFAULT_TX_POWER,
    .adrAckCounter = 0u,
    .nbRep = 1u,
    .nbRepCounter = 0u,
    .macCmdBuffer = {0},
    .macCmdBufferIndex = 0u,
    .upLinkSlot = {
        .Address = 0x00,
        .AppSKey = {0},
        .NwkSKey = {0},
        .UpLinkCounter = 1u,
        .DownLinkCounter = 0u,
        .ChannelIndex = 0u,
        .DataRateIndex = LORAMAC_DEFAULT_DATARATE,
        .TxPowerIndex = LORAMAC_DEFAULT_TX_POWER
    },
    .advertisingSlot = {
        .Time = 0u,
        .Interval = 0u,
        .Duration = 0u,
    },
    .ctrlFlags.Value = 0u, /* Device flags */
    .dbgFlags.Value = 0u /* Debug flags */
};

/*!
 * LoRaMesh Event Scheduler
 */
/*! Event scheduler events list */
static LoRaSchedulerEvent_t eventSchedulerList[MAX_NOF_SCHEDULER_EVENTS];
static LoRaSchedulerEvent_t *pEventScheduler;
static LoRaSchedulerEvent_t *pNextSchedulerEvent;
static LoRaSchedulerEvent_t *pFreeSchedulerEvent;
/*! Event scheduler event handler list */
static LoRaSchedulerEventHandler_t eventHandlerList[MAX_NOF_SCHEDULER_EVENT_HANDLERS];
static LoRaSchedulerEventHandler_t *pEventHandlers;
static LoRaSchedulerEventHandler_t *pFreeEventHandler;
/*! Event scheduler timer*/
static TimerEvent_t EventSchedulerTimer;

/*! Advertising */
static uint32_t LastAdvertisingWindow;

/*! Multicast groups */
static MulticastGroupInfo_t multicastGrpList[MAX_NOF_MULTICAST_GROUPS];
static MulticastGroupInfo_t *pFreeMulticastGrp;

/*! Child nodes */
static ChildNodeInfo_t childNodeList[MAX_NOF_CHILD_NODES];
static ChildNodeInfo_t *pFreeChildNode;

/*! Rx message handlers */
static PortHandler_t portHandlers[MAX_NOF_PORT_HANDLERS];
static PortHandler_t *pPortHandlers;
static PortHandler_t *pFreePortHandler;
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
/*! \brief Evaluates probability of a node to nominate itself as coordinator. */
static bool EvaluateAcceptanceProbability( int32_t latiBin, int32_t longiBin );

/*! \brief Evaluates probability of a node to nominate itself as coordinator. */
static bool EvaluateNominationProbability( uint8_t nodeRank, DeviceClass_t nodeClass );

/*! \brief Calculate the nodes rank. */
static uint8_t CalculateNodeRank( void );

/*! brief Function executed on event scheduler timer event */
static void OnEventSchedulerTimerEvent( TimerHandle_t xTimer );

/*! \brief Function executed on advertising event */
static void AdvertisingEvent( void );

/*! \brief Schedule new event */
static uint8_t ScheduleEvent( LoRaSchedulerEventHandler_t *evtHandler,
        LoRaSchedulerEventType_t eventType, uint16_t firstSlot, TimerTime_t interval,
        TimerTime_t duration );

/*! \brief Remove scheduler event */
static uint8_t RemoveEvent( LoRaSchedulerEventHandler_t *evtHandler );

/*! \brief Find free slots for given event */
static uint8_t FindFreeSlots( uint16_t firstSlot, TimerTime_t interval, uint16_t durationInSlots,
        uint8_t *nofAllocatedSlots, uint16_t *allocatedSlots, bool scheduleRxWindows );

/*! \brief Allocate new scheduler event */
static LoRaSchedulerEvent_t *AllocateEvent( void );

/*! \brief Free allocated scheduler event */
static void FreeEvent( LoRaSchedulerEvent_t *evt );

/*! \brief Allocate scheduler event handler */
static LoRaSchedulerEventHandler_t * AllocateEventHandler( void );

/*! \brief Free allocated scheduler event handler */
static void FreeEventHandler( LoRaSchedulerEventHandler_t *evtHandler );

/*! \brief Create new child node with given data. */
ChildNodeInfo_t* CreateChildNode( uint32_t devAddr, uint8_t* nwkSKey, uint8_t* appSKey,
        uint32_t frequency, uint32_t interval );

/*! \brief Add child node at the tail of the list. */
void ChildNodeAdd( ChildNodeInfo_t* childNode );

/*! \brief Remove child node from the list. */
void ChildNodeRemove( ChildNodeInfo_t* childNode );

/*! \brief Create new child node with given data. */
MulticastGroupInfo_t* CreateMulticastGroup( uint32_t grpAddr, uint8_t* nwkSKey, uint8_t* appSKey,
        uint32_t frequency, uint32_t interval, bool isOwner );

/*! \brief Add mutlicast group. */
void MulticastGroupAdd( MulticastGroupInfo_t *multicastGrp );

/*! \brief Remove multicast group. */
void MulticastGroupRemove( MulticastGroupInfo_t *multicastGrp );

/*! \brief Print status */
static uint8_t PrintStatus( Shell_ConstStdIO_t *io );

/*! \brief Print help */
static uint8_t PrintHelp( Shell_ConstStdIO_t *io );

/*! \brief Print event scheduler list */
static uint8_t PrintEventSchedulerList( Shell_ConstStdIO_t *io );

/*! \brief Print child node information. */
static uint8_t PrintChildNodes( Shell_ConstStdIO_t *io );

/*! \brief Print multicast group information. */
static uint8_t PrintMulticastGroups( Shell_ConstStdIO_t *io );

/*******************************************************************************
 * MODULE VARIABLES (PUBLIC)
 ******************************************************************************/
/*! LoRaWAN device pointer */
LoRaDevice_t* pLoRaDevice;

/*! Data rates table definition */
const uint8_t Datarates[] = { 12, 11, 10, 9, 8, 7, 7, 50 };

/*! Maximum payload with respect to the datarate index. Cannot operate with repeater. */
const uint8_t MaxPayloadByDatarate[] = { 51, 51, 51, 115, 242, 242, 242, 242 };

/*! Tx output powers table definition */
const uint8_t TxPowers[] = { 20, 14, 11, 8, 5, 2 };

/*! LoRa device used throughout the stack */
extern LoRaDevice_t* pLoRaDevice;

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
byte LoRaMesh_ParseCommand( const unsigned char *cmd, bool *handled, Shell_ConstStdIO_t *io )
{
    if ( strcmp((char*) cmd, SHELL_CMD_HELP) == 0 || strcmp((char*) cmd, "lora help") == 0 ) {
        *handled = true;
        return PrintHelp(io);
    } else if ( (strcmp((char*) cmd, SHELL_CMD_STATUS) == 0)
            || (strcmp((char*) cmd, "lora status") == 0) ) {
        *handled = true;
        return PrintStatus(io);
    } else if ( (strcmp((char*) cmd, "lora childnodes") == 0) ) {
        *handled = true;
        return PrintChildNodes(io);
    } else if ( (strcmp((char*) cmd, "lora events") == 0) ) {
        *handled = true;
        return PrintEventSchedulerList(io);
    } else if ( (strcmp((char*) cmd, "lora multicastgroups") == 0) ) {
        *handled = true;
        return PrintMulticastGroups(io);
    }
    return ERR_OK;
}

void LoRaMesh_Init( LoRaMeshCallbacks_t *callbacks )
{
//    LoRaSchedulerEventHandler_t *handler;
    uint8_t i;

    LoRaMeshCallbacks = callbacks;

    /* Assign LoRa device structure pointer */
    pLoRaDevice = (LoRaDevice_t*) &LoRaDevice;

    /* Create a list with rx message handler */
    pPortHandlers = NULL;
    pFreePortHandler = portHandlers;
    for ( i = 0; i < MAX_NOF_PORT_HANDLERS - 1; i++ ) {
        portHandlers[i].next = &portHandlers[i + 1];
    }

    /* Init scheduler list */
    pEventScheduler = NULL;
    pNextSchedulerEvent = NULL;
    pFreeSchedulerEvent = eventSchedulerList;
    for ( i = 0; i < MAX_NOF_SCHEDULER_EVENTS - 1; i++ ) {
        eventSchedulerList[i].next = &eventSchedulerList[i + 1];
    }
    /* Init event handlers list */
    pEventHandlers = NULL;
    pFreeEventHandler = eventHandlerList;
    for ( i = 0; i < MAX_NOF_SCHEDULER_EVENT_HANDLERS - 1; i++ ) {
        eventHandlerList[i].next = &eventHandlerList[i + 1];
    }

    /* Event scheduler timer */
    TimerInit(&EventSchedulerTimer, "EventSchedulerTimer", (void*) NULL, OnEventSchedulerTimerEvent,
            false);

    /* Init child node list */
    pFreeChildNode = childNodeList;
    for ( i = 0; i < MAX_NOF_CHILD_NODES - 1; i++ ) {
        childNodeList[i].next = &childNodeList[i + 1];
    }

    /* Init multicast group list */
    pFreeMulticastGrp = multicastGrpList;
    for ( i = 0; i < MAX_NOF_MULTICAST_GROUPS - 1; i++ ) {
        multicastGrpList[i].next = &multicastGrpList[i + 1];
    }

    /* Initialize stack */
    LoRaFrm_Init();
    LoRaMac_Init(LoRaMeshCallbacks->GetBatteryLevel);
    LoRaPhy_Init();
}

uint8_t LoRaMesh_RegisterApplication( PortHandlerFunction_t fHandler, uint8_t fPort )
{
    PortHandler_t *handler;

    if ( fPort < 1 || fPort > 223 ) return ERR_RANGE;

    handler = pPortHandlers;

    /* Check if port is already registered */
    while ( handler != NULL ) {
        if ( handler->fPort == fPort ) return ERR_NOTAVAIL;
        handler = handler->next;
    }

    /* Get next free port handler */
    handler = pFreePortHandler;
    if ( handler == NULL ) return ERR_FAILED;

    /* Populate port handler */
    pFreePortHandler = handler->next;
    handler->fPort = fPort;
    handler->fHandler = fHandler;
    handler->next = pPortHandlers;
    pPortHandlers = handler;

    return ERR_OK;
}

uint8_t LoRaMesh_RemoveApplication( uint8_t fPort )
{
    PortHandler_t *handler;

    if ( fPort < 1 || fPort > 223 ) return ERR_RANGE;

    handler = pPortHandlers;

    /* Find port handler is already registered */
    while ( handler != NULL ) {
        if ( handler->fPort == fPort ) {
            /* Remove port handler */
            handler->fPort = 0;
            handler->fHandler = NULL;
            handler->next = pFreePortHandler;
            pFreePortHandler = handler;
            return ERR_OK;
        }
        handler = handler->next;
    }

    return ERR_FAILED;
}

uint8_t LoRaMesh_RegisterTransmission( uint16_t firstSlot, uint32_t interval,
        LoRaSchedulerEventType_t evtType, size_t transmissionLength,
        void (*callback)( void *param ), void* param )
{
    LoRaSchedulerEventHandler_t * evtHandler;
    uint32_t duration;
    uint8_t result;

    if ( evtType != EVENT_TYPE_UPLINK && evtType != EVENT_TYPE_MULTICAST ) return ERR_FAILED;

    evtHandler = AllocateEventHandler();
    if ( evtHandler == NULL ) {
        LOG_ERROR("Unable to allocate event handlers.");
        return ERR_NOTAVAIL;
    }
    /* Initialize event handler */
    evtHandler->eventIntervalTicks = interval / 1e2; /* 10ms per Tick */
    evtHandler->callback = callback;
    evtHandler->param = param;

    duration = 50000 + (1500 * (transmissionLength - 1));

    if ( (result = ScheduleEvent(evtHandler, evtType, firstSlot, (TimerTime_t) interval,
            (TimerTime_t) duration)) != ERR_OK ) {
        LOG_ERROR("Unable to schedule events.");
        return result;
    }

    if ( evtType == EVENT_TYPE_UPLINK ) {
        pLoRaDevice->upLinkSlot.UpLinkCounter = 0;
        pLoRaDevice->upLinkSlot.DownLinkCounter = 0;
        pLoRaDevice->upLinkSlot.DataRateIndex = LORAMAC_DEFAULT_DATARATE;
        pLoRaDevice->upLinkSlot.TxPowerIndex = LORAMAC_DEFAULT_TX_POWER;
#if defined(NODE_B)
        pLoRaDevice->upLinkSlot.ChannelIndex = 1;
#elif defined(NODE_C)
        pLoRaDevice->upLinkSlot.ChannelIndex = 2;
#elif defined(NODE_D)
        pLoRaDevice->upLinkSlot.ChannelIndex = 4;
#elif defined(NODE_E)
        pLoRaDevice->upLinkSlot.ChannelIndex = 5;
#endif
    }

    return ERR_OK;
}

uint8_t LoRaMesh_RemoveTransmission( uint32_t interval, void (*callback)( void *param ) )
{
    LoRaSchedulerEventHandler_t * evtHandler;
    uint8_t result;

    while ( evtHandler != NULL ) {
        if ( (evtHandler->eventIntervalTicks == (interval / 1e2))
                && (evtHandler->callback == callback) ) {
            if ( (result = RemoveEvent(evtHandler)) == ERR_OK ) FreeEventHandler(evtHandler);
        }
        evtHandler = evtHandler->next;
    }

    return result;
}

uint8_t LoRaMesh_RegisterReceptionWindow( uint16_t firstSlot, uint32_t interval,
        void (*callback)( void *param ), void* param )
{
    LoRaSchedulerEventHandler_t *handler;
    uint8_t result;

    handler = AllocateEventHandler();
    handler->callback = callback;
    handler->param = param;

    if ( (result = ScheduleEvent(handler, EVENT_TYPE_SYNCH_RX_WINDOW, firstSlot,
            (TimerTime_t) interval, (TimerTime_t) RECEPTION_RESERVED_TIME)) != ERR_OK ) {
        LOG_ERROR("Unable to schedule events.");
    }

    return result;
}

uint8_t LoRaMesh_RemoveReceptionWindow( uint32_t interval, void (*callback)( void *param ) )
{
    LoRaSchedulerEventHandler_t *handler;
    uint8_t result;

    while ( handler != NULL ) {
        if ( (handler->eventIntervalTicks == (interval / 1e2))
                && (handler->callback == callback) ) {
            if ( (result = RemoveEvent(handler)) == ERR_OK ) FreeEventHandler(handler);
        }
        handler = handler->next;
    }

    return result;
}

uint8_t LoRaMesh_SendFrame( uint8_t *appPayload, size_t appPayloadSize, uint8_t fPort,
        bool isUpLink, bool isConfirmed )
{
    uint8_t i, buf[LORAMESH_BUFFER_SIZE];

    if ( !LoRaMesh_IsNetworkJoined() ) {
        return ERR_NOTAVAIL;   // No network has been joined yet
    }

    if ( appPayloadSize > LORAMESH_PAYLOAD_SIZE ) {
        return ERR_OVERFLOW; /* block too large for payload */
    }

    i = 0;
    while ( i < appPayloadSize ) {
        LORAMESH_BUF_PAYLOAD_START(buf)[i] = *appPayload;
        appPayload++;
        i++;
    }

    /*! \todo this is a workaround */
    pLoRaDevice->currChannelIndex = pLoRaDevice->upLinkSlot.ChannelIndex;

    return LoRaMesh_PutPayload(buf, sizeof(buf), appPayloadSize, pLoRaDevice->devAddr, fPort,
            isConfirmed);
}

uint8_t LoRaMesh_SendMulticast( uint8_t *appPayload, size_t appPayloadSize, uint8_t fPort )
{
    uint8_t i, buf[LORAMESH_BUFFER_SIZE];
    MulticastGroupInfo_t *multicastGrp;

    if ( !LoRaMesh_IsNetworkJoined() ) return ERR_NOTAVAIL;   // No network has been joined yet
    if ( pLoRaDevice->devRole == NODE ) return ERR_DISABLED;

    if ( appPayloadSize > LORAMESH_PAYLOAD_SIZE ) {
        return ERR_OVERFLOW; /* block too large for payload */
    }

    i = 0;
    while ( i < appPayloadSize ) {
        LORAMESH_BUF_PAYLOAD_START(buf)[i] = *appPayload;
        appPayload++;
        i++;
    }

    multicastGrp = pLoRaDevice->multicastGroups;
    while ( multicastGrp != NULL ) {
        if ( multicastGrp->isOwner ) break;
        multicastGrp = multicastGrp->next;
    }

    if ( multicastGrp == NULL ) return ERR_DISABLED;

    /*! \todo this is a workaround */
    pLoRaDevice->currChannelIndex = multicastGrp->Connection.ChannelIndex;

    return LoRaMesh_PutPayload(buf, sizeof(buf), appPayloadSize, multicastGrp->Connection.Address,
            fPort, false);
}

uint8_t LoRaMesh_SendAdvertising( void )
{
    uint8_t buf[LORAMESH_ADVERTISING_MSG_LENGTH + LORAPHY_HEADER_SIZE], payloadSize, phyFlags,
            devRank;
    int32_t latiBin, longiBin;

    payloadSize = 0;
    phyFlags = LORAPHY_PACKET_FLAGS_FRM_ADVERTISING;

    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr >> 8) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr >> 16) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr >> 24) & 0xFF;

    /* Device info */
    devRank = CalculateNodeRank();
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = ((((pLoRaDevice->devRole) & 0xF) << 4)
            | (devRank & 0xF));

    GpsGetLatestGpsPositionBinary(&latiBin, &longiBin);
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (latiBin) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (latiBin >> 8) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (latiBin >> 16) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (latiBin >> 24) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (longiBin) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (longiBin >> 8) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (longiBin >> 16) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (longiBin >> 24) & 0xFF;

    /* Coordinator address */
    if ( pLoRaDevice->coordinatorAddr == 0x00
            && EvaluateNominationProbability(0, (DeviceClass_t) 0) ) {
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr) & 0xFF;
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr >> 8) & 0xFF;
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr >> 16) & 0xFF;
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->devAddr >> 24) & 0xFF;
    } else {
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->coordinatorAddr) & 0xFF;
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->coordinatorAddr >> 8) & 0xFF;
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->coordinatorAddr >> 16)
                & 0xFF;
        buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->coordinatorAddr >> 24)
                & 0xFF;
    }

    /* Advertising slot info */
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->advertisingSlot.Time) & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->advertisingSlot.Time >> 8)
            & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->advertisingSlot.Time >> 16)
            & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (pLoRaDevice->advertisingSlot.Time >> 24)
            & 0xFF;
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (uint8_t)(
            pLoRaDevice->advertisingSlot.Interval / 1e6);
    buf[LORAPHY_BUF_IDX_PAYLOAD + (payloadSize++)] = (uint8_t)(
            pLoRaDevice->advertisingSlot.Duration / 1e6);

    return LoRaPhy_PutPayload(buf, sizeof(buf), payloadSize, phyFlags);
}

uint8_t LoRaMesh_ProcessAdvertising( uint8_t *aPayload, uint8_t aPayloadSize )
{
    uint32_t coordAddr = 0x00, devAddr = 0x00;
    uint8_t rank, role;

    devAddr |= (aPayload[LORAMESH_ADVERITSING_DEV_ADR_IDX]);
    devAddr |= (aPayload[LORAMESH_ADVERITSING_DEV_ADR_IDX + 1] << 8);
    devAddr |= (aPayload[LORAMESH_ADVERITSING_DEV_ADR_IDX + 2] << 16);
    devAddr |= (aPayload[LORAMESH_ADVERITSING_DEV_ADR_IDX + 3] << 24);

    rank = (aPayload[LORAMESH_ADVERITSING_ROLE_RANK_IDX] & 0x0F);
    role = ((aPayload[LORAMESH_ADVERITSING_ROLE_RANK_IDX] & 0xF0) >> 4);

    coordAddr |= (aPayload[LORAMESH_ADVERITSING_COORD_ADR_IDX]);
    coordAddr |= (aPayload[LORAMESH_ADVERITSING_COORD_ADR_IDX + 1] << 8);
    coordAddr |= (aPayload[LORAMESH_ADVERITSING_COORD_ADR_IDX + 2] << 16);
    coordAddr |= (aPayload[LORAMESH_ADVERITSING_COORD_ADR_IDX + 3] << 24);

    if ( pLoRaDevice->coordinatorAddr != coordAddr ) {
        if ( coordAddr != 0x00 ) {
            if ( coordAddr != devAddr
                    && EvaluateNominationProbability(rank, (DeviceClass_t) role) ) {
                /* Node will nominate itself */
                pLoRaDevice->coordinatorAddr = pLoRaDevice->devAddr;
            } else {
                /* Elect propagated coordinator */
                pLoRaDevice->coordinatorAddr = coordAddr;
            }
        } else {

        }
    } else {
        if ( coordAddr == 0x00 ) {
            if ( EvaluateNominationProbability(rank, (DeviceClass_t) role) ) {
                /* Node will nominate itself */
                pLoRaDevice->coordinatorAddr = pLoRaDevice->devAddr;
            } else {
                /* Propagate loss of former coordinator */
                pLoRaDevice->coordinatorAddr = 0x00;
            }
        }
    }
    return ERR_OK;
}

uint8_t LoRaMesh_JoinReq( uint8_t * devEui, uint8_t * appEui, uint8_t * appKey )
{
    uint8_t mPayloadSize = 0, mPayload[LORAMAC_BUFFER_SIZE];

    /* Store values for key generation */
    pLoRaDevice->devNonce = (uint16_t)(LoRaPhy_GenerateNonce() & 0xFFFF);
    pLoRaDevice->appEui = appEui;
    pLoRaDevice->devEui = devEui;
    pLoRaDevice->appKey = appKey;

    memcpy(&LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize], appEui, 8);
    mPayloadSize += 8;
    memcpy(&LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize], devEui, 8);
    mPayloadSize += 8;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = pLoRaDevice->devNonce & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (pLoRaDevice->devNonce >> 8) & 0xFF;

    return LoRaMac_PutPayload((uint8_t*) &mPayload, sizeof(mPayload), mPayloadSize,
            MSG_TYPE_JOIN_REQ, 0x00, 0x00, NULL, false);
}

uint8_t LoRaMesh_JoinMeshReq( uint8_t * devEui, uint8_t * appEui, uint8_t * appKey )
{
    uint8_t mPayloadSize = 0, mPayload[LORAMAC_BUFFER_SIZE];
    int32_t latiBin, longiBin;

    /* Store values for key generation */
    pLoRaDevice->devNonce = (uint16_t)(LoRaPhy_GenerateNonce() & 0xFFFF);
    pLoRaDevice->appEui = appEui;
    pLoRaDevice->devEui = devEui;
    pLoRaDevice->appKey = appKey;

    memcpy(&LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize], appEui, 8);
    mPayloadSize += 8;
    memcpy(&LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize], devEui, 8);
    mPayloadSize += 8;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = pLoRaDevice->devNonce & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (pLoRaDevice->devNonce >> 8) & 0xFF;

    GpsGetLatestGpsPositionBinary(&latiBin, &longiBin);
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin >> 8) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin >> 16) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin >> 24) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin >> 8) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin >> 16) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin >> 24) & 0xFF;

    return LoRaMac_PutPayload((uint8_t*) &mPayload, sizeof(mPayload), mPayloadSize,
            MSG_TYPE_JOIN_REQ, 0x00, 0x00, NULL, false);
}

uint8_t LoRaMesh_ProcessJoinMeshReq( uint8_t *payload, uint8_t payloadSize )
{
    uint8_t appEui[8], devEui[8], nwkSKey[16], appSKey[16];
    int32_t latiBin, longiBin;
    uint32_t appNonce = 0x00;
    uint16_t devNonce = 0x00;

    memcpy1(appEui, (uint8_t*) &payload[LORAMAC_BUF_IDX_PAYLOAD], 8);
    memcpy1(devEui, (uint8_t*) &payload[LORAMAC_BUF_IDX_PAYLOAD + 8], 8);

    devNonce |= (payload[LORAMAC_BUF_IDX_PAYLOAD + 16] & 0xFF);
    devNonce |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 17] >> 8) & 0xFF);

    appNonce = LoRaPhy_GenerateNonce();

    LoRaMacJoinComputeSKeys(pLoRaDevice->appKey, (uint8_t*) &appNonce, devNonce, nwkSKey, appSKey);

    latiBin = (payload[LORAMAC_BUF_IDX_PAYLOAD + 18] & 0xFF);
    latiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 19] >> 8) & 0xFF);
    latiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 20] >> 16) & 0xFF);
    latiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 21] >> 24) & 0xFF);
    longiBin = (payload[LORAMAC_BUF_IDX_PAYLOAD + 22] & 0xFF);
    longiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 23] >> 8) & 0xFF);
    longiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 24] >> 16) & 0xFF);
    longiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 25] >> 24) & 0xFF);

    if ( EvaluateAcceptanceProbability(latiBin, longiBin) ) {
        ChildNodeInfo_t* newChild;
        newChild = CreateChildNode(LoRaMesh_GenerateDeviceAddress(devNonce), nwkSKey, appSKey, 0,
                0);
        if ( newChild == NULL ) return ERR_FAILED;
        ChildNodeAdd(newChild);
        if ( pLoRaDevice->devRole == NODE ) pLoRaDevice->devRole = ROUTER;
    }

    return ERR_OK;
}

uint8_t LoRaMesh_RebindMeshReq( void )
{
    uint8_t mPayloadSize = 0, mPayload[LORAMAC_BUFFER_SIZE];
    int32_t latiBin, longiBin;

    /* Store values for key generation */
    pLoRaDevice->devNonce = (uint16_t)(LoRaPhy_GenerateNonce() & 0xFFFF);

    memcpy1(&LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize], pLoRaDevice->appEui, 8);
    mPayloadSize += 8;
    memcpy1(&LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize], pLoRaDevice->devEui, 8);
    mPayloadSize += 8;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = pLoRaDevice->devNonce & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (pLoRaDevice->devNonce >> 8) & 0xFF;

    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (pLoRaDevice->devAddr) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (pLoRaDevice->devAddr >> 8) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (pLoRaDevice->devAddr >> 16) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (pLoRaDevice->devAddr >> 24) & 0xFF;

    GpsGetLatestGpsPositionBinary(&latiBin, &longiBin);
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin >> 8) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin >> 16) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (latiBin >> 24) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin >> 8) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin >> 16) & 0xFF;
    LORAMAC_BUF_PAYLOAD_START(mPayload)[mPayloadSize++] = (longiBin >> 24) & 0xFF;

    return LoRaMac_PutPayload((uint8_t*) &mPayload, sizeof(mPayload), mPayloadSize,
            MSG_TYPE_JOIN_REQ, 0x00, 0x00, NULL, false);
}

uint8_t LoRaMesh_ProcessRebindMeshReq( uint8_t *payload, uint8_t payloadSize )
{
    uint8_t appEui[8], devEui[8];
    int32_t latiBin, longiBin;
    uint32_t devAddr;
    uint16_t devNonce;

    memcpy1((uint8_t*) appEui, (uint8_t*) &payload[LORAMAC_BUF_IDX_PAYLOAD], 8);
    memcpy1((uint8_t*) devEui, (uint8_t*) &payload[LORAMAC_BUF_IDX_PAYLOAD + 8], 8);

    devNonce = (payload[LORAMAC_BUF_IDX_PAYLOAD + 16] & 0xFF);
    devNonce |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 17] >> 8) & 0xFF);

    latiBin = (payload[LORAMAC_BUF_IDX_PAYLOAD + 18] & 0xFF);
    latiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 19] >> 8) & 0xFF);
    latiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 20] >> 16) & 0xFF);
    latiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 21] >> 24) & 0xFF);
    longiBin = (payload[LORAMAC_BUF_IDX_PAYLOAD + 22] & 0xFF);
    longiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 23] >> 8) & 0xFF);
    longiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 24] >> 16) & 0xFF);
    longiBin |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 25] >> 24) & 0xFF);

    devAddr = (payload[LORAMAC_BUF_IDX_PAYLOAD + 26] & 0xFF);
    devAddr |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 27] >> 8) & 0xFF);
    devAddr |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 28] >> 16) & 0xFF);
    devAddr |= ((payload[LORAMAC_BUF_IDX_PAYLOAD + 29] >> 24) & 0xFF);

    if ( EvaluateAcceptanceProbability(latiBin, longiBin) ) {

    }

    return ERR_OK;
}

uint8_t LoRaMesh_LinkCheckReq( void )
{
    return ERR_OK;
}

uint8_t LoRaMesh_OnPacketRx( uint8_t *buf, uint8_t payloadSize, uint32_t devAddr, uint8_t fPort )
{
    if ( fPort >= LORAFRM_LOWEST_FPORT && fPort <= LORAFRM_HIGHEST_FPORT ) {
        PortHandler_t *iterHandler = pPortHandlers;
        while ( iterHandler != NULL ) {
            if ( iterHandler->fPort == fPort && iterHandler->fHandler != NULL ) {
                return iterHandler->fHandler(buf, payloadSize, devAddr, fPort);
            }
            iterHandler = iterHandler->next;
        }
    }

    return ERR_FAILED;
}

uint8_t LoRaMesh_PutPayload( uint8_t* buf, uint16_t bufSize, uint8_t payloadSize, uint32_t devAddr,
        uint8_t fPort, bool isConfirmed )
{
    /* Add app information */
#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
    LOG_TRACE("%s - Size %d", __FUNCTION__, payloadSize);
    LOG_TRACE_BARE("\t");
    for ( uint8_t i = 0; i < payloadSize; i++ )
    LOG_TRACE_BARE("0x%02x ", buf[i]);
    LOG_TRACE_BARE("\r\n");
#endif
    return LoRaFrm_PutPayload(buf, bufSize, payloadSize, devAddr, fPort, isConfirmed);
}

bool LoRaMesh_IsNetworkJoined( void )
{
    if ( pLoRaDevice != NULL ) {
        return (pLoRaDevice->ctrlFlags.Bits.nwkJoined == 1U);
    } else {
        return false;
    }
}

uint32_t LoRaMesh_GenerateDeviceAddress( uint16_t nonce )
{
    return (uint32_t)(0x13 | nonce);
}

ChildNodeInfo_t* LoRaMesh_FindChildNode( uint32_t devAddr )
{
    if ( pLoRaDevice->childNodes != NULL ) {
        ChildNodeInfo_t *childNode = pLoRaDevice->childNodes;

        while ( childNode != NULL ) {
            if ( childNode->Connection.Address == devAddr ) return childNode;
            childNode = childNode->next;
        }
    }

    return NULL;
}

MulticastGroupInfo_t* LoRaMesh_FindMulticastGroup( uint32_t grpAddr )
{
    if ( pLoRaDevice->multicastGroups != NULL ) {
        MulticastGroupInfo_t *grp = pLoRaDevice->multicastGroups;

        while ( grp != NULL ) {
            if ( grp->Connection.Address == grpAddr ) return grp;
            grp = grp->next;
        }
    }

    return NULL;
}

/*******************************************************************************
 * PUBLIC SETUP FUNCTIONS
 ******************************************************************************/
void LoRaMesh_SetNwkIds( uint32_t netID, uint32_t devAddr, uint8_t *nwkSKey, uint8_t *appSKey )
{
    pLoRaDevice->netId = netID;
    pLoRaDevice->devAddr = devAddr;

    for ( uint8_t i = 0; i < 16; i++ ) {
        pLoRaDevice->upLinkSlot.AppSKey[i] = appSKey[i];
        pLoRaDevice->upLinkSlot.NwkSKey[i] = nwkSKey[i];
    }

    pLoRaDevice->ctrlFlags.Bits.nwkJoined = 1;
}

void LoRaMesh_SetDeviceClass( DeviceClass_t devClass )
{
    pLoRaDevice->devClass = devClass;
}

void LoRaMesh_SetDeviceRole( DeviceRole_t devRole )
{
    pLoRaDevice->devRole = devRole;
}

void LoRaMesh_SetPublicNetwork( bool enable )
{
    if ( pLoRaDevice != NULL ) {
        pLoRaDevice->ctrlFlags.Bits.nwkPublic = (enable ? 1U : 0U);
    }
}

void LoRaMesh_SetAdrOn( bool enable )
{
    if ( pLoRaDevice != NULL ) {
        pLoRaDevice->ctrlFlags.Bits.adrCtrlOn = (enable ? 1U : 0U);
    }
}

uint32_t LoRaMesh_GetNofChildNodes( void )
{
    ChildNodeInfo_t* iterNode;
    uint32_t cnt = 0;

    iterNode = pLoRaDevice->childNodes;

    while ( iterNode != NULL ) {
        iterNode = iterNode->next;
        cnt++;
    }

    return cnt;
}

uint32_t LoRaMesh_GetNofMulticastGroups( void )
{
    MulticastGroupInfo_t* iterGrp;
    uint32_t cnt = 0;

    iterGrp = pLoRaDevice->multicastGroups;

    while ( iterGrp != NULL ) {
        iterGrp = iterGrp->next;
        cnt++;
    }

    return cnt;
}

void LoRaMesh_TimeSynch( time_t gpsUnixTime )
{
#if( LORAMESH_TEST_MODE_RX_ACTIVATED != 1 )
    if ( pLoRaDevice->dbgFlags.Bits.continuousRxEnabled != 1
            && gpsUnixTime % ADVERTISING_INTERVAL_SEC == 0 ) {
        AdvertisingEvent();
    }
#endif
}

/*******************************************************************************
 * TEST FUNCTIONS (PUBLIC) (FOR DEBUG PURPOSES ONLY)
 ******************************************************************************/
void LoRaMesh_TestSetDutyCycleCtrlOff( bool enable )
{
    if ( pLoRaDevice != NULL ) {
        pLoRaDevice->dbgFlags.Bits.dutyCycleCtrlOff = (enable ? 1U : 0U);
    }
}

void LoRaMesh_TestSetRxWindowsOn( bool enable )
{
    if ( pLoRaDevice != NULL ) {
        pLoRaDevice->dbgFlags.Bits.rxWindowsDisabled = (enable ? 0U : 1U);
    }
}

void LoRaMesh_TestSetMic( uint16_t upLinkCounter )
{
    if ( pLoRaDevice != NULL ) {
        pLoRaDevice->upLinkSlot.UpLinkCounter = upLinkCounter;
        pLoRaDevice->dbgFlags.Bits.upLinkCounterFixed = 1;
    }
}

void LoRaMesh_TestCreateChildNode( uint32_t devAddr, uint32_t interval, uint32_t freqChannel,
        uint8_t *nwkSKey, uint8_t *appSKey )
{
    ChildNodeInfo_t *newChildNode = CreateChildNode(devAddr, nwkSKey, appSKey, freqChannel,
            interval);

    if ( newChildNode != NULL ) {
        ChildNodeAdd(newChildNode);
    }
}

void LoRaMesh_TestCreateMulticastGroup( uint32_t grpAddr, uint32_t interval, uint32_t freqChannel,
        uint8_t *nwkSKey, uint8_t *appSKey, bool isOwner )
{
    MulticastGroupInfo_t *newGrp = CreateMulticastGroup(grpAddr, nwkSKey, appSKey, freqChannel,
            interval, isOwner);

    if ( newGrp != NULL ) {
        MulticastGroupAdd(newGrp);
    }
}

void LoRaMesh_TestContinuousRx( uint32_t freq, uint8_t datarate, bool enabled )
{
    if ( !enabled ) {
        pLoRaDevice->dbgFlags.Bits.continuousRxEnabled = 0;
        return;
    }
    pLoRaDevice->dbgFlags.Bits.continuousRxEnabled = 1;
    LoRaPhy_TestSetContinuousRx(freq, datarate);
}

void LoRaMesh_TestOpenReceptionWindow( uint8_t channel, uint8_t datarate )
{
    LoRaPhy_TestOpenRxWindow(channel, datarate);
}
/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
/*!
 * Schedule a LoRaMesh event
 *
 * \param[OUT] eHandler Allocated event handler
 * \param[IN] firstSlot First event occurrence (0xFFFF if first occurrence can be
 *            selected by the scheduler)
 * \param[IN] interval Event interval
 * \param[IN] duration Event duration
 *
 * \retval status ERR_OK Event was successfully scheduled
 */
static uint8_t ScheduleEvent( LoRaSchedulerEventHandler_t *evtHandler,
        LoRaSchedulerEventType_t eventType, uint16_t firstSlot, TimerTime_t interval,
        TimerTime_t duration )
{
    LoRaSchedulerEvent_t *evt = NULL;
    uint16_t durationInSlots;
    uint16_t allocatedSlots[32];
    bool receptionWindows = false;
    uint8_t i, j, nofAllocatedSlots;

    if ( firstSlot < 0 || (firstSlot > 512 && firstSlot != 0xFFFF) ) {
        return ERR_RANGE;
    }

    if ( eventType == EVENT_TYPE_UPLINK ) {
        receptionWindows = true;
    }

    durationInSlots = duration / TIME_PER_SLOT;
    if ( duration % TIME_PER_SLOT != 0 ) durationInSlots++;

    if ( FindFreeSlots(firstSlot, interval, durationInSlots, (uint8_t*) &nofAllocatedSlots,
            (uint16_t*) &allocatedSlots, receptionWindows) != ERR_OK ) return ERR_FAILED;

    for ( i = 0; i < nofAllocatedSlots; i++ ) {
        evt = AllocateEvent();

        if ( evt == NULL ) {
            LOG_ERROR("Unable to allocate event.");
            return ERR_NOTAVAIL;
        }
        evt->eventType = eventType;
        evt->eventHandler = evtHandler;
        evt->startSlot = allocatedSlots[i];
        evt->endSlot = evt->startSlot + durationInSlots;

        if ( pEventScheduler == NULL ) {
            evt->next = NULL;
            pNextSchedulerEvent = evt;
            pEventScheduler = evt;
        } else {
            LoRaSchedulerEvent_t *iterEvt = pEventScheduler;
            while ( iterEvt != NULL ) {
                if ( iterEvt == pEventScheduler && evt->endSlot < iterEvt->startSlot ) {
                    evt->next = iterEvt;
                    pNextSchedulerEvent = evt;
                    pEventScheduler = evt;
                    break;
                } else if ( ((iterEvt->endSlot < evt->startSlot) && (iterEvt->next != NULL)
                        && (iterEvt->next->startSlot > evt->endSlot))
                        || ((iterEvt->next == NULL) && (iterEvt->endSlot < evt->startSlot)) ) {
                    evt->next = iterEvt->next;
                    iterEvt->next = evt;
                    break;
                }
                iterEvt = iterEvt->next;
            }
        }

        if ( receptionWindows ) {
            LoRaSchedulerEvent_t *rxEvt;
            for ( j = 0; j < 2; j++ ) {
                rxEvt = AllocateEvent();
                if ( rxEvt == NULL ) {
                    LOG_ERROR("Coulnd't allocate reception window %u", j);
                    return ERR_NOTAVAIL;
                }
                rxEvt->eventType = (j == 0) ? EVENT_TYPE_RX1_WINDOW : EVENT_TYPE_RX2_WINDOW;
                rxEvt->eventHandler = NULL;   //&eventHandlerList[j];
                rxEvt->startSlot = allocatedSlots[(i + 1) + j];
                rxEvt->endSlot = rxEvt->startSlot + (RECEPTION_RESERVED_TIME / TIME_PER_SLOT);

                /* Place in scheduler event list */
                LoRaSchedulerEvent_t *iterEvt = pEventScheduler;
                while ( iterEvt != NULL ) {
                    if ( ((iterEvt->endSlot < rxEvt->startSlot) && (iterEvt->next != NULL)
                            && (iterEvt->next->startSlot > rxEvt->endSlot))
                            || ((iterEvt->next == NULL) && (iterEvt->endSlot < rxEvt->startSlot)) ) {
                        rxEvt->next = iterEvt->next;
                        iterEvt->next = rxEvt;
                        break;
                    }
                    iterEvt = iterEvt->next;
                }
            }
            i += 2;
        }
    }

//    (PrintEventSchedulerList(Shell_GetStdio()));
    return ERR_OK;
}

/*!
 * Remove event
 *
 * \param[IN] evtHandler Pointer to scheduler event handler to remove
 *
 * \retval status ERR_OK if removed successfully
 */
static uint8_t RemoveEvent( LoRaSchedulerEventHandler_t *evtHandler )
{
    LoRaSchedulerEvent_t *iterEvt;

    /* Find and remove all related scheduler events */
    iterEvt = pEventScheduler;
    while ( iterEvt != NULL ) {
        if ( iterEvt->eventHandler == evtHandler ) {
            /* In case it's an uplink event we also have to remove related rx windows */
            if ( iterEvt->eventType == EVENT_TYPE_UPLINK ) {
                LoRaSchedulerEvent_t *iterRxEvt = pEventScheduler;
                /* Remove rx1 window */
                while ( iterRxEvt != NULL ) {
                    if ( iterRxEvt->startSlot
                            == (iterEvt->startSlot + (pLoRaDevice->rxWindow1Delay / TIME_PER_SLOT)) ) {
                        /* Corresponding rx1 window found */
                        FreeEvent(iterRxEvt);
                        break;
                    }
                    iterRxEvt = iterRxEvt->next;
                }
                /* Remove rx2 window */
                iterRxEvt = pEventScheduler;
                while ( iterRxEvt != NULL ) {
                    if ( iterRxEvt->startSlot
                            == (iterEvt->startSlot + (pLoRaDevice->rxWindow2Delay / TIME_PER_SLOT)) ) {
                        /* Corresponding rx2 window found */
                        FreeEvent(iterRxEvt);
                        break;
                    }
                    iterRxEvt = iterRxEvt->next;
                }
            }
            FreeEvent(iterEvt);
        }
        iterEvt = iterEvt->next;
    }

    /* Check if scheduler list is empty */
    if ( pEventScheduler == NULL ) {
        TimerStop(&EventSchedulerTimer);
        pNextSchedulerEvent = NULL;
    }
    /* Free event handler */
    FreeEventHandler(evtHandler);
    return ERR_OK;
}

/*!
 * Find a specified number of free slots within the advertising window
 *
 * \param[IN] interval Time between slots
 * \param[IN] durationInSlots Duration of a single allocation
 * \param[OUT] nofAllocatedSlots  Number of allocated slots
 * \param[OUT] allocatedSlots Allocated slot numbers
 * \param[IN] scheduleRxWindows Schedule rx1 and rx2 windows (only for uplinks)
 *
 * \retval status ERR_OK if slot allocation was successful
 */
static uint8_t FindFreeSlots( uint16_t firstSlot, TimerTime_t interval, uint16_t durationInSlots,
        uint8_t *nofAllocatedSlots, uint16_t *allocatedSlots, bool scheduleRxWindows )
{
    uint8_t nofAllocationTries = 10, maxNofSlots;
    uint16_t slots[32];
    LoRaSchedulerEvent_t *evt;
    uint16_t i = 0;

    *(nofAllocatedSlots) = 0;

    /* Calculate max number of slot allocations */
    maxNofSlots = (AVAILABLE_SLOT_TIME / interval);
    if ( (AVAILABLE_SLOT_TIME % interval) > 0 ) maxNofSlots += 1;

    if ( pEventScheduler == NULL ) {
        uint16_t slot;
        if ( firstSlot == 0xFFFF ) firstSlot = 0;
        for ( i = 0; i < maxNofSlots; i++ ) {
            slot = firstSlot + ((interval / TIME_PER_SLOT) * i);
            if ( scheduleRxWindows ) {
                uint16_t slotRx1, slotRx2;
                slotRx1 = slot + durationInSlots + (pLoRaDevice->rxWindow1Delay / TIME_PER_SLOT);
                slotRx2 = slot + durationInSlots + (pLoRaDevice->rxWindow2Delay / TIME_PER_SLOT);
                /* Make sure Rx windows fit in as well */
                if ( (slotRx2 + durationInSlots) < NOF_AVAILABLE_SLOTS ) {
                    *(allocatedSlots++) = slot;
                    *(allocatedSlots++) = slotRx1;
                    *(allocatedSlots++) = slotRx2;
                    *(nofAllocatedSlots) += 3;
                    continue;
                }
                break;
            } else {
                if ( (slot + durationInSlots) < NOF_AVAILABLE_SLOTS ) {
                    *(allocatedSlots++) = slot;
                    *(nofAllocatedSlots) += 1;
                }
            }
        }
    } else {
        bool allocationDone = false, allocationAborted = false;
        uint16_t nextSlot = 0, offSet = 0;
        uint32_t timeFrame = 0;

        if ( scheduleRxWindows ) maxNofSlots *= 3;

        slots[0] = 0xFFFF;

        while ( !allocationDone && !allocationAborted && nofAllocationTries > 0 ) {
            /* Find first free slot */
            evt = pEventScheduler;
            while ( evt != NULL ) {
                if ( firstSlot == 0xFFFF ) { /* Free to select any free slot */
                    if ( evt->next != NULL ) {
                        timeFrame = (evt->next->startSlot - evt->endSlot);
                    } else {
                        timeFrame = NOF_AVAILABLE_SLOTS - evt->endSlot - 1;
                    }

                    if ( timeFrame > durationInSlots ) {
                        /* Potential first slot found */
                        slots[0] = (evt->endSlot + 1 + offSet);
                        *(nofAllocatedSlots) += 1;
                        break;
                    }
                } else { /* Check if requested first slot is available */
                    if ( (evt == pEventScheduler && evt->startSlot > firstSlot) ) {
                        if ( (firstSlot + durationInSlots) < evt->startSlot ) {
                            /* First slot available */
                            slots[0] = firstSlot;
                            *(nofAllocatedSlots) += 1;
                            break;
                        }
                    } else if ( firstSlot > evt->endSlot && evt->next != NULL
                            && firstSlot < evt->next->startSlot ) {
                        if ( (evt->endSlot + firstSlot + durationInSlots + 1)
                                < evt->next->startSlot ) {
                            /* First slot available */
                            slots[0] = firstSlot;
                            *(nofAllocatedSlots) += 1;
                            break;
                        }
                    }
                }
                evt = evt->next;
            }

            if ( slots[0] == 0xFFFF ) {
                /* Unable to allocate first slot */
                return ERR_FAILED;
            }

            /* Allocate recurring events */
            for ( i = 1; i < maxNofSlots; i++ ) {
                if ( scheduleRxWindows ) {
                    if ( (i % 3) == 1 ) {
                        nextSlot = slots[0] + durationInSlots
                                + ((interval / TIME_PER_SLOT) * (i / 3))
                                + (pLoRaDevice->rxWindow1Delay / TIME_PER_SLOT);
                    } else if ( (i % 3) == 2 ) {
                        nextSlot = slots[0] + durationInSlots
                                + ((interval / TIME_PER_SLOT) * (i / 3))
                                + (pLoRaDevice->rxWindow2Delay / TIME_PER_SLOT);
                    } else {
                        nextSlot = slots[0] + ((interval / TIME_PER_SLOT) * (i / 3));
                        /* Check if rx2 window fits within available slots */
                        if ( (nextSlot + (pLoRaDevice->rxWindow2Delay / TIME_PER_SLOT))
                                > NOF_AVAILABLE_SLOTS ) {
                            allocationDone = true;
                            break;
                        }
                    }
                } else {
                    nextSlot = slots[0] + ((interval / TIME_PER_SLOT) * i);
                }
                slots[i] = 0xFFFF;
                while ( evt != NULL ) {
                    if ( evt->endSlot < nextSlot ) {
                        if ( ((evt->next != NULL) && (evt->next->startSlot > nextSlot))
                                || ((evt->next == NULL)
                                        && ((NOF_AVAILABLE_SLOTS - durationInSlots) > nextSlot)) ) {
                            slots[i] = nextSlot;
                            *(nofAllocatedSlots) += 1;
                            break;
                        }
                    } else {
                        offSet +=
                                ((evt->startSlot + (evt->endSlot - evt->startSlot)) - nextSlot + 1);
                        break;
                    }
                    evt = evt->next;
                }
                /* Allocation not possible */
                if ( firstSlot != 0xFFFF && slots[i] == 0xFFFF ) {
                    allocationAborted = true;
                    break;
                } else if ( slots[i] == 0xFFFF ) {
                    *(nofAllocatedSlots) = 0; /* Reset */
                    nofAllocationTries--;
                    break;
                }
            }
            if ( i == (maxNofSlots) ) allocationDone = true;
        }

        if ( nofAllocationTries == 0 ) {
            return ERR_FAILED;
        } else {
            for ( i = 0; i < (*nofAllocatedSlots); i++ ) {
                *(allocatedSlots++) = slots[i];
            }
        }
    }
    return ERR_OK;
}

/*!
 * \brief Advertising event.
 */
static void AdvertisingEvent( void )
{
    PTB_BASE_PTR->PSOR |= (0x1 << 0);   // Set PB_0
    LOG_TRACE("Advertising timer event at %lu.", (timer_t)(GpsGetCurrentUnixTime()));

    /* Add packet to message queue */
    LoRaMesh_SendAdvertising();

    LastAdvertisingWindow = TimerGetCurrentTime();

    /* Restart event scheduler */
    if ( pEventScheduler != NULL ) {
        TimerStop(&EventSchedulerTimer);
        TimerSetValue(&EventSchedulerTimer,
                (ADVERTISING_RESERVED_TIME + (pEventScheduler->startSlot * TIME_PER_SLOT)));
        TimerStart(&EventSchedulerTimer);
    }
}

/*!
 * Function executed when event schedule FreeRTOS software timer expires.
 *
 * \param xTimer FreeRTOS timer handle
 */
static void OnEventSchedulerTimerEvent( TimerHandle_t xTimer )
{
    uint32_t nextEvtTime, currTime;
    uint16_t slot;

    TimerStop(&EventSchedulerTimer);
    PTB_BASE_PTR->PCOR |= (0x1 << 0);   // Clear PB_0

    if ( pNextSchedulerEvent == NULL ) return;

    currTime = TimerGetCurrentTime();
    slot = ((((currTime - LastAdvertisingWindow) * portTICK_PERIOD_MS) * 1000)
            - ADVERTISING_RESERVED_TIME) / TIME_PER_SLOT;

    LOG_TRACE("Event scheduler at slot %u (%u ms)", slot, currTime);

    if ( pNextSchedulerEvent->next == NULL ) {
        /* Restart scheduler */
        pNextSchedulerEvent = pEventScheduler;
        return;
    } else if ( pNextSchedulerEvent->startSlot == slot ) {
        /* Start scheduler timer */
        nextEvtTime = ((pNextSchedulerEvent->next->startSlot - pNextSchedulerEvent->startSlot)
                * TIME_PER_SLOT);
        /* Start scheduler timer */
        TimerSetValue(&EventSchedulerTimer, nextEvtTime);
        TimerStart(&EventSchedulerTimer);
        /* Invoke callback function */
        if ( pNextSchedulerEvent->eventHandler != NULL
                && pNextSchedulerEvent->eventHandler->callback != NULL ) {
            pNextSchedulerEvent->eventHandler->callback(pNextSchedulerEvent->eventHandler->param);
        }
    } else {
        LOG_ERROR("Drift occurred. Skip event. (Start %u / Current %u)",
                pNextSchedulerEvent->startSlot, slot);
        /* Start scheduler timer */
        nextEvtTime = ((pNextSchedulerEvent->next->startSlot - slot) * TIME_PER_SLOT);
        /* Start scheduler timer */
        TimerSetValue(&EventSchedulerTimer, nextEvtTime);
        TimerStart(&EventSchedulerTimer);
    }

    /* Move pointer forward */
    pNextSchedulerEvent = pNextSchedulerEvent->next;
}

/*!
 * Evaluates probability of a node to accept a join mesh or rebind
 * mesh request depending on distance to the node and the current
 * role
 *
 * \param[IN] latiBin Latitude in binary form
 * \param[IN] longiBin Longitude in binary form
 *
 * \retval bool True if request should be accpted
 */
bool EvaluateAcceptanceProbability( int32_t latiBin, int32_t longiBin )
{
    uint32_t distance;

    GpsGetDistanceToLatestGpsPositionBinary(latiBin, longiBin, &distance);
    return true;
}

/*!
 * Evaluates probability of a node to nominate itself as coordinator and
 * returns true, if the calculated probability is bigger then a hard coded threshold.
 *
 * \param[IN] nodeRank Remote nodes rank
 * \param[IN] nodeClass Remote nodes role
 *
 * \retval bool True if the node nominates itself
 */
bool EvaluateNominationProbability( uint8_t nodeRank, DeviceClass_t nodeClass )
{
    (void) nodeRank;
    return true;
}

/*!
 * Calculate the nodes rank.
 *
 * \return uint8_t Rank of the node
 */
uint8_t CalculateNodeRank( void )
{
    return 1;
}

/*!
 * Allocate LoRa scheduler event
 *
 * \retval Pointer to allocated scheduler event
 */
static LoRaSchedulerEvent_t *AllocateEvent( void )
{
    LoRaSchedulerEvent_t *evt = pFreeSchedulerEvent;

    if ( evt != NULL ) {
        pFreeSchedulerEvent = evt->next;
        evt->startSlot = 0;
        evt->startSlot = 0;
        evt->next = NULL;
        evt->eventType = EVENT_TYPE_NONE;
        evt->eventHandler = NULL;
    }

    return evt;
}

/*!
 * Free allocated LoRa scheduler event
 *
 * \param[IN] evt LoRa scheduler event to be freed
 */
static void FreeEvent( LoRaSchedulerEvent_t *evt )
{
    if ( pEventScheduler != NULL ) {
        LoRaSchedulerEvent_t *prevEvt, *iterEvt;
        prevEvt = NULL;
        iterEvt = pEventScheduler;

        while ( iterEvt != NULL ) {
            if ( iterEvt == evt ) {
                if ( prevEvt == NULL ) {
                    pEventScheduler = iterEvt->next;
                } else {
                    prevEvt->next = iterEvt->next;
                }
                iterEvt->next = pFreeSchedulerEvent;
                iterEvt->startSlot = 0;
                iterEvt->endSlot = 0;
                evt->eventType = EVENT_TYPE_NONE;
                iterEvt->eventHandler = NULL;
                pFreeSchedulerEvent = iterEvt;
                break;
            }
            prevEvt = iterEvt;
            iterEvt = iterEvt->next;
        }
    }
}

/*!
 * Allocate LoRa scheduler event handler
 *
 * \retval Pointer to allocated scheduler event handler
 */
static LoRaSchedulerEventHandler_t *AllocateEventHandler( void )
{
    LoRaSchedulerEventHandler_t *handler = pFreeEventHandler;

    if ( handler != NULL ) {
        pFreeEventHandler = handler->next;
        handler->eventIntervalTicks = 0;
        handler->callback = NULL;
        handler->param = (void*) NULL;
        handler->next = pEventHandlers;
        pEventHandlers = handler;
        return pEventHandlers;
    }

    return NULL;
}

/*!
 * Free allocated LoRa scheduler event handler
 *
 * \param[IN] evt LoRa scheduler event handler to be freed
 */
static void FreeEventHandler( LoRaSchedulerEventHandler_t *handler )
{
    if ( pEventHandlers != NULL ) {
        LoRaSchedulerEventHandler_t* iterHandler, *prevHandler;

        prevHandler = NULL;
        iterHandler = pEventHandlers;

        while ( iterHandler != NULL ) {
            if ( iterHandler == handler ) {
                if ( prevHandler == NULL ) {
                    pEventHandlers = iterHandler->next;
                } else {
                    prevHandler->next = iterHandler->next;
                }
                iterHandler->next = pFreeEventHandler;
                iterHandler->callback = NULL;
                iterHandler->param = (void*) NULL;
                pFreeEventHandler = iterHandler;
                break;
            }
            prevHandler = iterHandler;
            iterHandler = iterHandler->next;
        }
    }
}

/*!
 * \brief Create new child node with given data
 *
 * \param devAddr Device address of the child node
 * \param nwkSKey Network session key
 * \param appSKey Application session key
 * \param channel Channel frequency
 * \param interval Rx window interval
 *
 * \retval
 */
ChildNodeInfo_t* CreateChildNode( uint32_t devAddr, uint8_t* nwkSKey, uint8_t* appSKey,
        uint32_t frequency, uint32_t interval )
{
    ChildNodeInfo_t* newNode = pFreeChildNode;

    if ( newNode != NULL ) {
        pFreeChildNode = newNode->next;
        newNode->Connection.Address = devAddr;
        memcpy1(newNode->Connection.AppSKey, appSKey, 16);
        memcpy1(newNode->Connection.NwkSKey, nwkSKey, 16);
        newNode->Connection.UpLinkCounter = 0;
        newNode->Connection.ChannelIndex = LoRaPhy_GetChannelIndex(frequency);
        newNode->Connection.DataRateIndex = LORAMAC_DEFAULT_DATARATE;
        newNode->Connection.TxPowerIndex = LORAMAC_DEFAULT_TX_POWER;
        newNode->Periodicity = interval;
        return newNode;
    }
    return NULL;
}

/*!
 * \brief Add child node at the tail of the list.
 *
 * \param childNode Child Node to append
 */
void ChildNodeAdd( ChildNodeInfo_t* childNode )
{
// Reset uplink counter
    childNode->Connection.UpLinkCounter = 0;

    if ( pLoRaDevice->childNodes == NULL ) {
        childNode->next = NULL;
        pLoRaDevice->childNodes = childNode;
    } else {
        childNode->next = pLoRaDevice->childNodes;
        pLoRaDevice->childNodes = childNode;
    }
}

/*!
 * \brief Remove child node from the list.
 *
 * \param childNode Pointer to child node that should be removed.
 */
void ChildNodeRemove( ChildNodeInfo_t* childNode )
{
    if ( pLoRaDevice->childNodes != NULL ) {
        ChildNodeInfo_t* iterNode = pLoRaDevice->childNodes;

        while ( iterNode->next != NULL ) {
            if ( iterNode->next == childNode ) {
                iterNode->next = childNode->next;
                childNode->next = pFreeChildNode;
                pFreeChildNode = childNode;
            }
            iterNode = iterNode->next;
        }
    }
}

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
        uint32_t frequency, uint32_t interval, bool isOwner )
{
    MulticastGroupInfo_t* newGrp = pFreeMulticastGrp;

    if ( newGrp != NULL ) {
        pFreeMulticastGrp = newGrp->next;
        newGrp->Connection.Address = grpAddr;
        memcpy1(newGrp->Connection.AppSKey, appSKey, 16);
        memcpy1(newGrp->Connection.NwkSKey, nwkSKey, 16);
        newGrp->Connection.DownLinkCounter = 0;
        newGrp->Connection.ChannelIndex = LoRaPhy_GetChannelIndex(frequency);
        newGrp->Connection.DataRateIndex = LORAMAC_DEFAULT_DATARATE;
        newGrp->Connection.TxPowerIndex = LORAMAC_DEFAULT_TX_POWER;
        newGrp->Periodicity = interval;
        newGrp->isOwner = isOwner;
        return newGrp;
    }
    return NULL;
}

/*!
 * \brief Add mutlicast group.
 *
 * \param multicastGrp Pointer to information structure of the multicast group to be added.
 */
void MulticastGroupAdd( MulticastGroupInfo_t *multicastGrp )
{
// Reset downlink counter
    multicastGrp->Connection.DownLinkCounter = 0;

    if ( pLoRaDevice->multicastGroups == NULL ) {
        multicastGrp->next = NULL;
        pLoRaDevice->multicastGroups = multicastGrp;
    } else {
        multicastGrp->next = pLoRaDevice->multicastGroups;
        pLoRaDevice->multicastGroups = multicastGrp;
    }
}

/*!
 * \brief Remove multicast group.
 *
 * \param multicastGrp Pointer to information structure of the multicast group to be removed.
 */
void MulticastGroupRemove( MulticastGroupInfo_t *multicastGrp )
{
    if ( pLoRaDevice->multicastGroups != NULL ) {
        MulticastGroupInfo_t* iterGrp = pLoRaDevice->multicastGroups;

        while ( iterGrp->next != NULL ) {
            if ( iterGrp->next == multicastGrp ) {
                iterGrp->next = multicastGrp->next;
                multicastGrp->next = pFreeMulticastGrp;
                pFreeMulticastGrp = multicastGrp;
            }
            iterGrp = iterGrp->next;
        }
    }
}

/*******************************************************************************
 * SHELL FUNCTIONS (STATIC)
 ******************************************************************************/
/*!
 * \brief Print out LoRaMesh status.
 *
 * \param io Std io to be used for print out.
 */
static uint8_t PrintStatus( Shell_ConstStdIO_t *io )
{
    byte buf[64];

    Shell_SendStatusStr((unsigned char*) "lora", (unsigned char*) "\r\n", io->stdOut);
    /* Address */
    custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
    strcatNum32Hex(buf, sizeof(buf), pLoRaDevice->devAddr);
    Shell_SendStatusStr((unsigned char*) "  Address", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    /* Nwk Id */
    custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
    strcatNum32Hex(buf, sizeof(buf), pLoRaDevice->netId);
    Shell_SendStatusStr((unsigned char*) "  Net Id", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    /* Network joined */
    Shell_SendStatusStr((unsigned char*) "  Nwk Joined?",
            (unsigned char*) ((pLoRaDevice->ctrlFlags.Bits.nwkJoined == 1) ? "Yes" : "No"),
            io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    /* Nof child nodes */
    custom_strcpy((unsigned char*) buf, sizeof(""), (unsigned char*) "");
    strcatNum32u(buf, sizeof(buf), LoRaMesh_GetNofChildNodes());
    Shell_SendStatusStr((unsigned char*) "  Child Nodes", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    /* Nof multicast groups */
    custom_strcpy((unsigned char*) buf, sizeof(""), (unsigned char*) "");
    strcatNum32u(buf, sizeof(buf), LoRaMesh_GetNofMulticastGroups());
    Shell_SendStatusStr((unsigned char*) "  Mcast Grps", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    return ERR_OK;
}

/*!
 * \brief Print out LoRaMesh command help.
 *
 * \param io Std io to be used for print out.
 */
static uint8_t PrintHelp( Shell_ConstStdIO_t *io )
{
    Shell_SendHelpStr((unsigned char*) "lora", (unsigned char*) "Group of lora commands\r\n",
            io->stdOut);
    Shell_SendHelpStr((unsigned char*) "  help|status",
            (unsigned char*) "Print help or status information\r\n", io->stdOut);
    Shell_SendHelpStr((unsigned char*) "  events",
            (unsigned char*) "Print event scheduler list\r\n", io->stdOut);
    Shell_SendHelpStr((unsigned char*) "  childnodes",
            (unsigned char*) "Print child nodes list\r\n", io->stdOut);
    Shell_SendHelpStr((unsigned char*) "  multicastgroups",
            (unsigned char*) "Print multicast groups list\r\n", io->stdOut);

    return ERR_OK;
}

/*!
 * \brief Print out scheduler list.
 *
 * \param io Std io to be used for print out.
 */
static uint8_t PrintEventSchedulerList( Shell_ConstStdIO_t *io )
{
    LoRaSchedulerEvent_t* evt = pEventScheduler;
    byte buf[64];
    uint8_t i = 0;

    Shell_SendStr((unsigned char*) SHELL_DASH_LINE, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n\tEvent \t\tStart \tEnd\r\n", io->stdOut);
    while ( evt != NULL ) {
        custom_strcpy((unsigned char*) buf, sizeof(""), (unsigned char*) "");
        strcatNum8u(buf, sizeof(buf), (i + 1));
        switch ( evt->eventType ) {
            case EVENT_TYPE_UPLINK:
                custom_strcat(buf, sizeof(buf), (byte*) "\tUplink\t\t");
                break;
            case EVENT_TYPE_MULTICAST:
                custom_strcat(buf, sizeof(buf), (byte*) "\tMulticast\t");
                break;
            case EVENT_TYPE_SYNCH_RX_WINDOW:
                custom_strcat(buf, sizeof(buf), (byte*) "\tSynch Rx\t");
                break;
            case EVENT_TYPE_RX1_WINDOW:
                custom_strcat(buf, sizeof(buf), (byte*) "\tRx1\t\t");
                break;
            case EVENT_TYPE_RX2_WINDOW:
                custom_strcat(buf, sizeof(buf), (byte*) "\tRx2\t\t");
                break;
            default:
                continue;
        }
        strcatNum16u(buf, sizeof(buf), evt->startSlot);
        custom_strcat(buf, sizeof(buf), (byte*) "\t");
        strcatNum16u(buf, sizeof(buf), evt->endSlot);
        custom_strcat(buf, sizeof(buf), (byte*) "\r\n");
        Shell_SendStr((unsigned char*) buf, io->stdOut);
        i++;
        evt = evt->next;
    }

    return ERR_OK;
}

/*!
 * \brief Print out child node list.
 *
 * \param io Std io to be used for print out.
 */
static uint8_t PrintChildNodes( Shell_ConstStdIO_t *io )
{
    uint8_t j;
    byte buf[64];
    ChildNodeInfo_t* childNode = pLoRaDevice->childNodes;

    while ( childNode != NULL ) {
        Shell_SendStr((unsigned char*) SHELL_DASH_LINE, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Address */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        strcatNum32Hex(buf, sizeof(buf), childNode->Connection.Address);
        Shell_SendStatusStr((unsigned char*) "Address", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Network session key */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        for ( j = 0; j < 16; j++ )
            strcatNum8Hex(buf, sizeof(buf), childNode->Connection.NwkSKey[j]);
        Shell_SendStatusStr((unsigned char*) "  NwkSKey", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Application session key */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        for ( j = 0; j < 16; j++ )
            strcatNum8Hex(buf, sizeof(buf), childNode->Connection.AppSKey[j]);
        Shell_SendStatusStr((unsigned char*) "  AppSKey", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* UpLink counter */
        custom_strcpy((unsigned char*) buf, sizeof(""), (unsigned char*) "");
        strcatNum32u(buf, sizeof(buf), childNode->Connection.UpLinkCounter);
        Shell_SendStatusStr((unsigned char*) "  UpLinkCounter", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* UpLink slot infor */
        Shell_SendStr((unsigned char*) "---- Uplink Slot Info ----", io->stdOut);
        /* UpLink frequency */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        strcatNum32u(buf, sizeof(buf),
                LoRaPhy_GetChannelFrequency(childNode->Connection.ChannelIndex));
        Shell_SendStatusStr((unsigned char*) "  Frequency", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* UpLink periodicity */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        strcatNum32u(buf, sizeof(buf), childNode->Periodicity);
        Shell_SendStatusStr((unsigned char*) "  Periodicity", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

        childNode = childNode->next;
    }
    return ERR_OK;
}

/*!
 * \brief Print out multicast group list.
 *
 * \param io Std io to be used for print out.
 */
static uint8_t PrintMulticastGroups( Shell_ConstStdIO_t *io )
{
    uint8_t j;
    byte buf[64];
    MulticastGroupInfo_t* multicastGrp = pLoRaDevice->multicastGroups;

    while ( multicastGrp != NULL ) {
        Shell_SendStr((unsigned char*) SHELL_DASH_LINE, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Address */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        strcatNum32Hex(buf, sizeof(buf), multicastGrp->Connection.Address);
        Shell_SendStatusStr((unsigned char*) "Address", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Network session key */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        for ( j = 0; j < 16; j++ )
            strcatNum8Hex(buf, sizeof(buf), multicastGrp->Connection.NwkSKey[j]);
        Shell_SendStatusStr((unsigned char*) "  NwkSKey", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Application session key */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        for ( j = 0; j < 16; j++ )
            strcatNum8Hex(buf, sizeof(buf), multicastGrp->Connection.AppSKey[j]);
        Shell_SendStatusStr((unsigned char*) "  AppSKey", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* DownLink counter */
        custom_strcpy((unsigned char*) buf, sizeof(""), (unsigned char*) "");
        strcatNum32u(buf, sizeof(buf), multicastGrp->Connection.DownLinkCounter);
        Shell_SendStatusStr((unsigned char*) "  DL Counter", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Is owner */
        Shell_SendStatusStr((unsigned char*) "  Is Owner",
                (unsigned char*) ((multicastGrp->isOwner) ? "true" : "false"), io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* DownLink slot info */
        Shell_SendStr((unsigned char*) "---- Downlink Slot Info ----", io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* DownLink frequency */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        strcatNum32u(buf, sizeof(buf),
                LoRaPhy_GetChannelFrequency(multicastGrp->Connection.ChannelIndex));
        Shell_SendStatusStr((unsigned char*) "  Frequency", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* DownLink periodicity */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        strcatNum32u(buf, sizeof(buf), multicastGrp->Periodicity);
        Shell_SendStatusStr((unsigned char*) "  Periodicity", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

        multicastGrp = multicastGrp->next;
    }
    return ERR_OK;
}

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
