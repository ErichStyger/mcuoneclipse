/**
 * \file LoRaMesh.h
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 07.12.2015
 * \version 1.0
 *
 * \brief LoRa stack common file
 */

#ifndef __LORAMESH_H_
#define __LORAMESH_H_

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "LoRaMesh-config.h"
#include "LoRaFrm.h"
#include "LoRaMac.h"
#include "LoRaPhy.h"
#include "Shell.h"

/*******************************************************************************
 * CONSTANT DEFINITIONS
 ******************************************************************************/
#define LORAMESH_HEADER_SIZE                 (0)
#define LORAMESH_PAYLOAD_SIZE                (LORAFRM_PAYLOAD_SIZE-LORAMESH_HEADER_SIZE)
#define LORAMESH_BUFFER_SIZE                 (LORAFRM_BUFFER_SIZE)

/* PHY buffer access macros */
#define LORAMESH_BUF_IDX_HDR                 (0) /* <Hdr> index */
#define LORAMESH_BUF_IDX_PAYLOAD             (LORAMESH_HEADER_SIZE) /* <app payload> index */

/* Advertising definitions */
#define LORAMESH_ADVERTISING_MSG_LENGTH      (0x17)
#define LORAMESH_ADVERITSING_DEV_ADR_IDX     (LORAPHY_BUF_IDX_PAYLOAD)
#define LORAMESH_ADVERITSING_ROLE_RANK_IDX   (LORAPHY_BUF_IDX_PAYLOAD + 4)
#define LORAMESH_ADVERITSING_LOCATION_IDX    (LORAPHY_BUF_IDX_PAYLOAD + 5)
#define LORAMESH_ADVERITSING_COORD_ADR_IDX   (LORAPHY_BUF_IDX_PAYLOAD + 13)
#define LORAMESH_ADVERITSING_SLOT_INFO_IDX   (LORAPHY_BUF_IDX_PAYLOAD + 17)
/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/
#define LORAMESH_BUF_PAYLOAD_START(phy)      (((phy) + LORAMESH_HEADER_SIZE))

/*******************************************************************************
 * TYPE DEFINITIONS
 ******************************************************************************/
/*! LoRaWAN devices classes definition */
typedef enum {
    CLASS_A, CLASS_B, CLASS_C
} DeviceClass_t;

/*! LoRaMesh devices role definition */
typedef enum {
    NODE, ROUTER, COORDINATOR /* LoRaMesh class */,
} DeviceRole_t;

/* LoRaMesh connection info structure */
typedef struct ConnectionInfo_s {
    uint32_t Address;
    uint8_t NwkSKey[16];
    uint8_t AppSKey[16];
    uint8_t ChannelIndex;
    uint8_t DataRateIndex;
    uint8_t TxPowerIndex;
    uint32_t UpLinkCounter;
    uint32_t DownLinkCounter;
} ConnectionInfo_t;

typedef struct MulticastGroupInfo_s {
    ConnectionInfo_t Connection;
    bool isOwner;
    uint32_t Periodicity;
    struct MulticastGroupInfo_s *next;
} MulticastGroupInfo_t;

typedef struct ChildNodeInfo_s {
    ConnectionInfo_t Connection;
    uint32_t Periodicity;
    struct ChildNodeInfo_s *next;
} ChildNodeInfo_t;

/*! LoRaMesh advertising info structure. */
typedef struct AdvertisingSlotInfo_s {
    uint32_t Time;
    uint32_t Interval; /* In microseconds */
    uint32_t Duration; /* In microseconds */
} AdvertisingSlotInfo_t;

typedef union {
    uint8_t Value;
    struct {
        uint8_t upLinkCounterFixed :1; /* 1: Frame counter up link is fixed */
        uint8_t rxWindowsDisabled :1; /* 1: Reception windows disabled */
        uint8_t dutyCycleCtrlOff :1; /* 1: Duty cycle control inactive */
        uint8_t continuousRxEnabled :1; /* 1: Continuous Rx mode enabled */
        uint8_t reserved :4;
    } Bits;
} LoRaDbgFlags_t;

typedef union {
    uint8_t Value;
    struct {
        uint8_t nwkPublic :1; /* 1: Network is public */
        uint8_t nwkJoined :1; /* 1: Network joined successfully */
        uint8_t linkCheck :1; /* 1: Link check answer received */
        uint8_t adrCtrlOn :1; /* 1: Adaptive data rate control active */
        uint8_t ackPending :1; /* 1: Node has sent a confirmed packet */
        uint8_t ackRequested :1; /* 1: Node has received a confirmed packet */
        uint8_t reserved :3;
    } Bits;
} LoRaMeshCtrlFlags_t;

/*! LoRa network layer events structure */
typedef struct LoRaMeshCallbacks_s {
    /*!
     * Function callback to get the current battery level needed for status
     * request command
     *
     * \retval batteryLevel Current battery level
     */
    uint8_t (*GetBatteryLevel)( void );
    /*!
     * Function callback prototype to handle proprietary message types that can not
     * be handled by the LoRa stack
     *
     * \param buf       Pointer to received message buffer
     * \param bufSize   Length of the received message
     * \param handled   Pointer to a handled flag to be set true if the callback recipient has
     *                  dealt with the message
     */
    void (*HandleProprietaryRxMsg)( uint8_t* buf, uint8_t bufSize, bool* handled );
    /*!
     * Function callback prototype to handle received message
     *
     * \param buf       Pointer to received message buffer
     * \param bufSize   Length of the received message
     * \param fPort     Port on which the message was received
     * \param handled   Pointer to a handled flag to be set true if the callback recipient has
     *                  dealt with the message
     */
    void (*HandleRxMsg)( uint8_t* buf, uint8_t bufSize, uint8_t fPort, bool* handled );
} LoRaMeshCallbacks_t;

typedef struct {
    uint32_t netId; /* Network ID (24-Bit) */
    uint32_t devAddr; /* Network device address */
    uint8_t *devEui; /* Device extended unique identifier (64-Bit) */
    uint16_t devNonce; /* Device nonce */
    DeviceClass_t devClass; /* Device class */
    DeviceRole_t devRole; /* Device role */
    uint32_t coordinatorAddr; /* Coordinator address */
    uint8_t *appEui; /* Application extended unique identifier (64-Bit) */
    uint8_t *appKey; /* Application key AES 128-Bit */
    ConnectionInfo_t upLinkSlot; /* Up link slot information */
    AdvertisingSlotInfo_t advertisingSlot; /* Advertising slot information */
    ChildNodeInfo_t *childNodes; /* List of connected child nodes */
    MulticastGroupInfo_t *multicastGroups; /* List of joined multicast groups */
    uint8_t currChannelIndex; /* Index of the currently selected channel from the channel list */
    uint8_t currDataRateIndex; /* Currently selected data rate */
    uint8_t currTxPowerIndex; /* Currently selected output power */
    uint16_t channelsMask[6]; /* Channel mask to disable channels from the channel list */
    uint32_t adrAckCounter; /* Adaptive data rate acknowledgement counter */
    uint32_t rxWindow1Delay; /* Reception window 2 delay */
    uint32_t rxWindow2Delay; /* Reception window 1 delay */
    uint8_t nbRep; /* Configured redundancy [1:15] (automatic uplink message repetition) */
    uint8_t nbRepCounter; /* Automatic repetition counter */
    uint8_t macCmdBuffer[15]; /* MAC command buffer of commands to be added to FOpts field */
    uint8_t macCmdBufferIndex; /* MAC command buffer index */
    LoRaMeshCtrlFlags_t ctrlFlags; /* Network flags */
    LoRaDbgFlags_t dbgFlags; /* Debug flags */
} LoRaDevice_t;

typedef enum {
    EVENT_TYPE_UPLINK,
    EVENT_TYPE_MULTICAST,
    EVENT_TYPE_SYNCH_RX_WINDOW,
    EVENT_TYPE_RX1_WINDOW,
    EVENT_TYPE_RX2_WINDOW,
    EVENT_TYPE_NONE = 0xFF
} LoRaSchedulerEventType_t;

typedef void (*LoRaSchedulerEventCallback_t)( void *param );

typedef struct LoRaSchedulerEventHandler_s {
    uint16_t eventIntervalTicks;
    LoRaSchedulerEventCallback_t callback;
    void *param;
    struct LoRaSchedulerEventHandler_s *next;
} LoRaSchedulerEventHandler_t;

typedef struct LoRaSchedulerEvent_s {
    uint16_t startSlot;
    uint16_t endSlot;
    LoRaSchedulerEventType_t eventType;
    LoRaSchedulerEventHandler_t *eventHandler;
    struct LoRaSchedulerEvent_s *next;
} LoRaSchedulerEvent_t;

typedef uint8_t (*PortHandlerFunction_t)( uint8_t *payload, uint8_t payloadSize, uint32_t devAddr,
        uint8_t fPort );

typedef struct PortHandler_s {
    uint8_t fPort;
    PortHandlerFunction_t fHandler;
    struct PortHandler_s *next;
} PortHandler_t;

/*******************************************************************************
 * PUBLIC VARIABLES
 ******************************************************************************/
/*! Data rates table definition */
extern const uint8_t Datarates[8];

/*! Maximum payload with respect to the datarate index. Cannot operate with repeater. */
extern const uint8_t MaxPayloadByDatarate[8];

/*! Tx output powers table definition */
extern const uint8_t TxPowers[6];

/*! LoRa device used throughout the stack */
extern LoRaDevice_t* pLoRaDevice;

/*******************************************************************************
 * MODULE FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 * Shell command parser.
 */
byte LoRaMesh_ParseCommand( const unsigned char *cmd, bool *handled, Shell_ConstStdIO_t *io );

/*!
 * Initializind mesh network.
 *
 * \param [IN] callabcks       Pointer to a structure defining the LoRaMAC
 *                             callback functions.
 */
void LoRaMesh_Init( LoRaMeshCallbacks_t *callbacks );

/*!
 * Register an application handler on the specified port.
 *
 * \param [IN] handler Message handler to be called if a message is received on the specified port.
 * \param [IN] fPort Application port to register
 *
 * \retval status ERR_OK if port was successfully registered.
 */
uint8_t LoRaMesh_RegisterApplication( PortHandlerFunction_t fHandler, uint8_t fPort );

/*!
 * Remove an application handler from the specified port.
 *
 * \param [IN] handler Message handler to be called if a message is received on the specified port.
 * \param [IN] fPort Application port to register
 *
 * \retval status ERR_OK if port was successfully removed.
 */
uint8_t LoRaMesh_RemoveApplication( uint8_t fPort );

/*!
 * Register a scheduled data transmission
 *
 * \param[OUT] eHandler Pointer to the created event handler
 * \param[IN] interval Transmission period
 * \param[IN] callback Callback function
 * \param[IN] param Parameter to be passed to callback function
 *
 * \retval status ERR_OK if transmission was scheduled successfully
 */
uint8_t LoRaMesh_RegisterTransmission( uint16_t firstSlot, uint32_t interval,
        LoRaSchedulerEventType_t evtType, size_t transmissionLength,
        void (*callback)( void *param ), void* param );

/*!
 * Remove a scheduled data transmission
 *
 * \param[IN] eHandler Pointer to the created event handler
 *
 * \retval status ERR_OK if transmission was removed successfully
 */
uint8_t LoRaMesh_RemoveTransmission( uint32_t interval, void (*callback)( void *param ) );

/*!
 * Register a scheduled data transmission
 *
 * \param[OUT] eHandler Pointer to the created event handler
 * \param[IN] interval Transmission period
 * \param[IN] callback Callback function
 * \param[IN] param Parameter to be passed to callback function
 *
 * \retval status ERR_OK if transmission was scheduled successfully
 */
uint8_t LoRaMesh_RegisterReceptionWindow( uint16_t firstSlot, uint32_t interval,
        void (*callback)( void *param ), void* param );

/*!
 * Remove a scheduled data transmission
 *
 * \param[IN] eHandler Pointer to the created event handler
 *
 * \retval status ERR_OK if transmission was removed successfully
 */
uint8_t LoRaMesh_RemoveReceptionWindow( uint32_t interval, void (*callback)( void *param ) );

/*!
 * LoRaMAC layer send frame
 *
 * \param [IN] fBuffer     Frame data buffer to be sent
 * \param [IN] fBufferSize Frame data buffer size
 * \param [IN] fPort       Frame payload port (must be > 0)
 * \param [IN] isUpLink    Frame direction
 * \param [IN] isConfirmed Confirmed frame
 *
 * \retval status          [0: OK, 1: Busy, 2: No network joined,
 *                          3: Length or port error, 4: Unknown MAC command
 *                          5: Unable to find a free channel
 *                          6: Device switched off]
 */
uint8_t LoRaMesh_SendFrame( uint8_t *appPayload, size_t appPayloadSize, uint8_t fPort,
        bool isUpLink, bool isConfirmed );

/*!
 * LoRaMAC layer send multicast
 *
 * \param [IN] fBuffer     Frame data buffer to be sent
 * \param [IN] fBufferSize Frame data buffer size
 * \param [IN] fPort       Frame payload port (must be > 0)
 *
 * \retval status          [0: OK, 1: Busy, 2: No network joined,
 *                          3: Length or port error, 4: Unknown MAC command
 *                          5: Unable to find a free channel
 *                          6: Device switched off]
 */
uint8_t LoRaMesh_SendMulticast( uint8_t *appPayload, size_t appPayloadSize, uint8_t fPort );

/*!
 * Send advertising packet.
 *
 * \retval status [0: OK]
 */
uint8_t LoRaMesh_SendAdvertising( void );

/*!
 * Process advertising message.
 *
 * \param [IN] aPayload     Advertising data buffer
 * \param [IN] aPayloadSize Advertising payload size
 */
uint8_t LoRaMesh_ProcessAdvertising( uint8_t *aPayload, uint8_t aPayloadSize );

/*!
 * Initiates the Over-the-Air activation
 *
 * \param [IN] devEui Pointer to the device EUI array ( 8 bytes )
 * \param [IN] appEui Pointer to the application EUI array ( 8 bytes )
 * \param [IN] appKey Pointer to the application AES128 key array ( 16 bytes )
 *
 * \retval status [0: OK, 1: Tx error, 2: Already joined a network]
 */
uint8_t LoRaMesh_JoinReq( uint8_t *devEui, uint8_t *appEui, uint8_t *appKey );

/*!
 * Send Ad-hoc join request if no network server is present.
 *
 * \param [IN] devEui Pointer to the device EUI array ( 8 bytes )
 * \param [IN] appEui Pointer to the application EUI array ( 8 bytes )
 * \param [IN] appKey Pointer to the application AES128 key array ( 16 bytes )
 *
 * \retval status [0: OK, 1: Tx error, 2: Already joined a network]
 */
uint8_t LoRaMesh_JoinReqMesh( uint8_t * devEui, uint8_t * appEui, uint8_t * appKey );

/*!
 * Process join mesh request message
 *
 * \param [IN] payload Pointer to join mesh request message payload
 * \param [IN] payloadSize Join mesh request message payload size
 */
uint8_t LoRaMesh_ProcessJoinMeshReq( uint8_t *payload, uint8_t payloadSize );

/*!
 * Send rebind request because connection to prior parent node was lost.
 *
 * \retval status [0: OK, 1: Tx error]
 */
uint8_t LoRaMesh_RebindMeshReq( void );

/*!
 *  Process rebind mesh request message
 *
 * \param [IN] payload Pointer to rebind mesh request message payload
 * \param [IN] payloadSize Rebind mesh request message payload size
 */
uint8_t LoRaMesh_ProcessRebindMeshReq( uint8_t *payload, uint8_t payloadSize );

/*!
 * Sends a LinkCheckReq MAC command on the next uplink frame
 *
 * \retval status Function status [0: OK, 1: Busy]
 */
uint8_t LoRaMesh_LinkCheckReq( void );

/*!
 * Handles received message on the transport layer.
 *
 * \param [IN] buf Received frame data buffer
 * \param [IN] payloadSize Received frame payload size
 * \param [IN] fPort Frame port
 * \param [IN] fType Frame type
 *
 * \retval status ERR_OK if frame was handled successfully
 */
uint8_t LoRaMesh_OnPacketRx( uint8_t *buf, uint8_t payloadSize, uint32_t devAddr, uint8_t fPort );

/*!
 * Handles received message on the transport layer.
 *
 * \param [IN] buf Frame data buffer
 * \param [IN] bufSize Frame data buffer size
 * \param [IN] payloadSize Frame payload size
 * \param [IN] fPort Frame port
 * \param [IN] fType Frame type
 *
 * \retval status ERR_OK if frame was handled successfully
 */
uint8_t LoRaMesh_PutPayload( uint8_t* buf, uint16_t bufSize, uint8_t payloadSize, uint32_t devAddr,
        uint8_t fPort, bool isConfirmed );

/*!
 * Returns whether or not a network is joined.
 *
 * \retval bool True if network is joined.
 */
bool LoRaMesh_IsNetworkJoined( void );

/*!
 * Generates a psudo-random device address
 *
 * \param nonce Nonce provided to generate device address
 */
uint32_t LoRaMesh_GenerateDeviceAddress( uint16_t nonce );

/*!
 * \brief Find child node with specified address.
 *
 * \param devAddr Device address of child node to find.
 * \return LoRaMacChildNodeInfo_t* Returns pointer to the found child node or NULL if not found.
 */
ChildNodeInfo_t* LoRaMesh_FindChildNode( uint32_t devAddr );

/*!
 * \brief Find multicast group with specified address.
 *
 * \param grpAddr Address of the group to find.
 * \return MulticastGroupInfo_t* Returns pointer to the found multicast group or NULL if not found.
 */
MulticastGroupInfo_t* LoRaMesh_FindMulticastGroup( uint32_t grpAddr );

/*******************************************************************************
 * SETUP FUNCTION PROTOTYPES (PUBLIC)
 ******************************************************************************/
/*!
 * Initializes the network IDs. Device address,
 * network session AES128 key and application session AES128 key.
 *
 * \remark To be only used when Over-the-Air activation isn't used.
 *
 * \param [IN] netID   24 bits network identifier
 *                     ( provided by network operator )
 * \param [IN] devAddr 32 bits device address on the network
 *                     (must be unique to the network)
 * \param [IN] nwkSKey Pointer to the network session AES128 key array
 *                     ( 16 bytes )
 * \param [IN] appSKey Pointer to the application session AES128 key array
 *                     ( 16 bytes )
 */
void LoRaMesh_SetNwkIds( uint32_t netID, uint32_t devAddr, uint8_t *nwkSKey, uint8_t *appSKey );

/*!
 * Sets the LoRa end devices class
 *
 * \param devClass Device class
 */
void LoRaMesh_SetDeviceClass( DeviceClass_t devClass );

/*!
 * Sets the LoRa end devices role
 *
 * \param devRole Device role
 */
void LoRaMesh_SetDeviceRole( DeviceRole_t devRole );

/*!
 * \brief Set network to public.
 *
 * \param enable Enable public network
 */
void LoRaMesh_SetPublicNetwork( bool enable );

/*!
 * Enables/Disables the ADR (Adaptive Data Rate)
 *
 * \param [IN] enable [true: ADR ON, false: ADR OFF]
 */
void LoRaMesh_SetAdrOn( bool enable );

uint32_t LoRaMesh_GetNofChildNodes( void );

uint32_t LoRaMesh_GetNofMulticastGroups( void );

void LoRaMesh_TimeSynch( time_t gpsTime );

time_t LoRaMesh_GetSynchTime( void );

/*******************************************************************************
 * TEST FUNCTION PROTOTYPES (PUBLIC) (FOR DEBUG PURPOSES ONLY)
 ******************************************************************************/
/*!
 * Disables/Enables the duty cycle enforcement (EU868)
 *
 * \param   [IN] enable - Enabled or disables the duty cycle
 */
void LoRaMesh_TestSetDutyCycleCtrlOff( bool enable );

/*!
 * Disables/Enables the reception windows opening
 *
 * \param [IN] enable [true: enable, false: disable]
 */
void LoRaMesh_TestSetRxWindowsOn( bool enable );

/*!
 * Enables the MIC field test
 *
 * \param [IN] upLinkCounter Fixed Tx packet counter value
 */
void LoRaMesh_TestSetMicMode( uint16_t upLinkCounter );

/*!
 * Create a child node with specified parameters
 *
 * \param[IN] devAddr Device address
 * \param[IN] interval Up link interval
 * \param[IN] freqChannel Used frequency channel
 * \param[IN] nwkSKey Network session key
 * \param[IN] appSKey Application session key
 */
void LoRaMesh_TestCreateChildNode( uint32_t devAddr, uint32_t interval, uint32_t freqChannel,
        uint8_t *nwkSKey, uint8_t *appSKey );

/*!
 * Create a multicast group with specified parameters
 *
 * \param[IN] grpAddr Multicast group address
 * \param[IN] interval Down link interval
 * \param[IN] freqChannel Used frequency channel
 * \param[IN] nwkSKey Network session key
 * \param[IN] appSKey Application session key
 */
void LoRaMesh_TestCreateMulticastGroup( uint32_t grpAddr, uint32_t interval, uint32_t freqChannel,
        uint8_t *nwkSKey, uint8_t *appSKey, bool isOwner );

void LoRaMesh_TestContinuousRx( uint32_t freq, uint8_t datarate, bool enabled );

/*!
 * Open reception window
 *
 * \param[IN] channel Index of the channel to use
 * \param[IN] datarate Index of the data rate to be used
 */
void LoRaMesh_TestOpenReceptionWindow( uint8_t channel, uint8_t datarate );

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/

#endif /* __LORAMESH_H_ */
