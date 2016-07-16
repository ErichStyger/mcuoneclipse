/**
 * \file LoRaMesh_App.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 03.12.2015
 * \version 1.0
 *
 * \brief LoRa mesh application
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"

#include "LoRaMesh.h"
#include "LoRaMesh_App.h"
#include "LoRaMesh_AppConfig.h"
#include "LoRaTest_App.h"

#define LOG_LEVEL_DEBUG
#include "debug.h"
/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
#define RADIO_PROCESS_INTERVAL                      10 /* in [ms] = 10ms */
#define RADIO_RTOS_DELAY_MS                         (RADIO_PROCESS_INTERVAL/portTICK_RATE_MS)

/*******************************************************************************
 * MACRO DEFINITIONS
 ******************************************************************************/
#define APP_CNTR_VALUE(interval)                    (interval/(RADIO_PROCESS_INTERVAL*1000))

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/

static LoRaMeshCallbacks_t sLoRaMeshCallbacks;
#if( OVER_THE_AIR_ACTIVATION != 0 )

static uint8_t DevEui[] = LORAWAN_DEVICE_EUI;
static uint8_t AppEui[] = LORAWAN_APPLICATION_EUI;
static uint8_t AppKey[] = LORAWAN_APPLICATION_KEY;

#else

static uint8_t NwkSKey[] = LORAWAN_NWKSKEY;
static uint8_t AppSKey[] = LORAWAN_APPSKEY;

/*! Device address */
static uint32_t DevAddr;
#endif

/*! Application multicast group address */
static const uint32_t McGrpAddr1 = 0x00A5EF01;
static const uint32_t McGrpAddr2 = 0x00A5EF02;

/*! Application port */
static uint8_t AppPort = LORAMESH_APP_PORT;

/*! User application data */
static uint8_t AppData[LORAMESH_APP_DATA_MAX_SIZE];

/*! Indicates if the node is sending confirmed or unconfirmed messages */
static uint8_t IsTxConfirmed = LORAWAN_CONFIRMED_MSG_ON;

/*! Data entries */
static DataEntry_t dataEntries[LORAMESH_APP_NOF_DATA_ENTRIES];
static DataEntry_t *pDataEntries;
static DataEntry_t *pFreeDataEntries;

/*! Helper variables */
#if( LORAMESH_TEST_MODE_TX_ACTIVATED == 1)
static uint8_t testFrame[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};
#endif
#if( LORAMESH_TEST_MODE_RX_ACTIVATED == 1)
static bool rxTestActivated = false;
#endif
static uint8_t lineBreakCntr;
static uint32_t cntr;

/*! App status */
static LoRaMesh_AppState_t appState;
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
/* Mesh app state machine function */
static void Process( void );

/* Send frame on configured app port */
static void SendDataFrame( void *param );

/* Send frame on configured app port */
static void SendMulticastDataFrame( void *param );

/**/
static void ReceiveDataFrame( void *param );

/* Process data frame */
static uint8_t ProcessDataFrame( uint8_t *buf, uint8_t payloadSize, uint32_t devAddr,
        uint8_t fPort );

static uint8_t AquireData( void );

/**/
static DataEntry_t *FindEntry( uint32_t devAddr );

/**/
static DataEntry_t *AllocateEntry( void );

/**/
static void FreeEntry( DataEntry_t *entry );

/*! \brief Print status */
static uint8_t PrintStatus( Shell_ConstStdIO_t *io );

/*! \brief Print help */
static uint8_t PrintHelp( Shell_ConstStdIO_t *io );

/*! \brief Print entry list */
static uint8_t PrintEntries( Shell_ConstStdIO_t *io );

/*! \brief Print entry */
static uint8_t PrintEntry( DataEntry_t * entry, Shell_ConstStdIO_t *io );

/* RTOS task function */
static void LoRaMeshTask( void *pvParameters );

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
byte LoRaMesh_AppParseCommand( const unsigned char *cmd, bool *handled, Shell_ConstStdIO_t *io )
{
    if ( strcmp((char*) cmd, SHELL_CMD_HELP) == 0 || strcmp((char*) cmd, "app help") == 0 ) {
        *handled = true;
        return PrintHelp(io);
    } else if ( (strcmp((char*) cmd, SHELL_CMD_STATUS) == 0)
            || (strcmp((char*) cmd, "app status") == 0) ) {
        *handled = true;
        return PrintStatus(io);
    } else if ( (strcmp((char*) cmd, "app entries") == 0) ) {
        *handled = true;
        return PrintEntries(io);
    }
    return ERR_OK;
}

void LoRaMesh_AppInit( void )
{
    LoRaMesh_Init(&sLoRaMeshCallbacks);

    /* Initialize data entries structure */
    pDataEntries = NULL;
    pFreeDataEntries = dataEntries;
    for ( uint8_t i = 0; i < LORAMESH_APP_NOF_DATA_ENTRIES - 1; i++ ) {
        dataEntries[i].next = (DataEntry_t*) &dataEntries[i + 1];
    }
#if(LORAMESH_TEST_APP_ACTIVATED == 1)
    LoRaTest_AppInit();
#endif /* LORAMESH_TEST_APP_ACTIVATED */

#if( OVER_THE_AIR_ACTIVATION == 0 )
    // NwkAddr
#if defined(NODE_A)
    LOG_DEBUG("Configuration for Node A.");
    DevAddr = 0x013AE27A;
#elif defined(NODE_B)
    LOG_DEBUG("Configuration for Node B.");
    DevAddr = 0x013A1024;
#elif defined(NODE_C)
    LOG_DEBUG("Configuration for Node C.");
    DevAddr = 0x013AD5F1;
#elif defined(NODE_D)
    LOG_DEBUG("Configuration for Node D.");
    DevAddr = 0x013AFA23;
#elif defined(NODE_E)
    LOG_DEBUG("Configuration for Node E.");
    DevAddr = 0x013ACB01;
#endif

    LoRaMesh_SetNwkIds(LORAWAN_NETWORK_ID, DevAddr, NwkSKey, AppSKey);
    LOG_DEBUG("LoRaMesh network IDs initialized. Network ID: %u, DevAddr: 0x%08x.",
            LORAWAN_NETWORK_ID, DevAddr);
#else
    // Initialize LoRaMac device unique ID
    BoardGetUniqueId (DevEui);
#endif /* OVER_THE_AIR_ACTIVATION */

    LoRaMesh_SetAdrOn (LORAWAN_ADR_ON);
    LoRaMesh_SetPublicNetwork (LORAWAN_PUBLIC_NETWORK);
    LoRaMesh_TestSetDutyCycleCtrlOff (LORAWAN_DUTYCYCLE_OFF);
#if defined(NODE_A)
    LoRaMesh_SetDeviceRole (COORDINATOR);
#elif defined(NODE_C)
    LoRaMesh_SetDeviceRole (ROUTER);
#endif

    LoRaMesh_RegisterApplication((PortHandlerFunction_t) & ProcessDataFrame, AppPort);

#if defined(NODE_A)
    /* Test child node */
    LoRaMesh_TestCreateChildNode(0x013A1024, 5000000, 868300000, NwkSKey, AppSKey);
    LoRaMesh_RegisterReceptionWindow(0, 5000000, &ReceiveDataFrame, (void*) 0x013A1024);
    /* Multicast group */
    LoRaMesh_TestCreateMulticastGroup(McGrpAddr1, LORAMESH_APP_TX_INTERVAL, 868100000, NwkSKey,
            AppSKey, true);
    LoRaMesh_RegisterTransmission(3, LORAMESH_APP_TX_INTERVAL, EVENT_TYPE_MULTICAST,
            ((4 * LORAMESH_APP_DATA_SIZE) + 1), &SendMulticastDataFrame, (void*) NULL);
    /* Test child node */
    LoRaMesh_TestCreateChildNode(0x013AD5F1, 4000000, 868500000, NwkSKey, AppSKey);
    LoRaMesh_RegisterReceptionWindow(9, 4000000, &ReceiveDataFrame, (void*) 0x013AD5F1);
#elif defined(NODE_B)
    /* Up Link */
    LoRaMesh_RegisterTransmission(0, 5000000, EVENT_TYPE_UPLINK,
            LORAMESH_APP_DATA_SIZE, &SendDataFrame, (void*) NULL);
    /* Multicast group */
    LoRaMesh_TestCreateMulticastGroup(McGrpAddr1, LORAMESH_APP_TX_INTERVAL, 868100000, NwkSKey,
            AppSKey, false);
    LoRaMesh_RegisterReceptionWindow(3, LORAMESH_APP_TX_INTERVAL, &ReceiveDataFrame,
            (void*) McGrpAddr1);
#elif defined(NODE_C)
    /* Up Link */
    LoRaMesh_RegisterTransmission(9, 4000000, EVENT_TYPE_UPLINK, LORAMESH_APP_DATA_SIZE,
            &SendDataFrame, (void*) NULL);
    /* Multicast group */
    LoRaMesh_TestCreateMulticastGroup(McGrpAddr1, LORAMESH_APP_TX_INTERVAL, 868100000, NwkSKey,
            AppSKey, false);
    LoRaMesh_RegisterReceptionWindow(3, LORAMESH_APP_TX_INTERVAL, &ReceiveDataFrame,
            (void*) McGrpAddr1);
#if 1
    /* Test child node */
    LoRaMesh_TestCreateChildNode(0x013AFA23, 5000000, 867300000, NwkSKey, AppSKey);
    LoRaMesh_RegisterReceptionWindow(0, 5000000, &ReceiveDataFrame, (void*) 0x013AFA23);
    /* Multicast group 2 */
    LoRaMesh_TestCreateMulticastGroup(McGrpAddr2, (LORAMESH_APP_TX_INTERVAL+1000000), 867100000, NwkSKey,
            AppSKey, true);
    LoRaMesh_RegisterTransmission(12, (LORAMESH_APP_TX_INTERVAL+1000000), EVENT_TYPE_MULTICAST,
            ((4 * LORAMESH_APP_DATA_SIZE) + 1), &SendMulticastDataFrame, (void*) NULL);
#endif
#elif defined(NODE_D)
    LoRaMesh_RegisterTransmission(0, 5000000, EVENT_TYPE_UPLINK, LORAMESH_APP_DATA_SIZE,
            &SendDataFrame, (void*) NULL);
    /* Multicast group */
    LoRaMesh_TestCreateMulticastGroup(McGrpAddr2, (LORAMESH_APP_TX_INTERVAL+1000000), 867100000, NwkSKey,
            AppSKey, false);
    LoRaMesh_RegisterReceptionWindow(12, (LORAMESH_APP_TX_INTERVAL+1000000), &ReceiveDataFrame,
            (void*) McGrpAddr2);
#endif

    if ( xTaskCreate(LoRaMeshTask, "LoRaMesh", configMINIMAL_STACK_SIZE + 150, (void*) NULL,
            tskIDLE_PRIORITY, (xTaskHandle*) NULL) != pdPASS ) {
        /*lint -e527 */
        for ( ;; ) {
        }; /* error! probably out of memory */
        /*lint +e527 */
    }
}

uint8_t LoRaMesh_AppStatus( void )
{
    return (uint8_t) appState;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
static void Process( void )
{
    for ( ;; ) {
        switch ( appState ) {
            case INITIAL:
                Shell_SendStr((unsigned char *) "\r\n\r\nStarting LoRaMesh application...",
                        Shell_GetStdio()->stdOut);
                lineBreakCntr = 32;
                appState = WAIT_GPS_FIX;
                continue;
            case WAIT_GPS_FIX:
                /* Wait for GPS fix */
                if ( !GpsHasFix() || !GpsHasValidDateTime() ) {
                    cntr++;
                    if ( cntr >= 100 ) {
                        Shell_SendStr((unsigned char *) ".", Shell_GetStdio()->stdOut);
                        lineBreakCntr++;
                        cntr = 0;
                        if ( lineBreakCntr >= 64 ) {
                            Shell_SendStr((unsigned char *) "\r\n", Shell_GetStdio()->stdOut);
                            lineBreakCntr = 0;
                        }
                    }
                } else {
                    Shell_SendStr((unsigned char *) "\r\n", Shell_GetStdio()->stdOut);
                    LOG_DEBUG("Gps has fix. Application process started");
                    appState = WAIT_NWK_JOIN;
                }
                break;
            case WAIT_NWK_JOIN:
#if( OVER_THE_AIR_ACTIVATION != 0 )
                LOG_TRACE("Send join request.");
                LoRaMesh_JoinReq((uint8_t*) &DevEui, (uint8_t*) &AppEui, (uint8_t*) &AppKey);
#else
                appState = ACTIVE;
#endif
                continue;
            case ACTIVE:
                if ( !GpsHasFix() ) {
                    appState = WAIT_GPS_FIX;
                    Shell_SendStr((unsigned char *) "\r\n", Shell_GetStdio()->stdOut);
                    lineBreakCntr = 0;
                    break;
                }
                (void) LoRaPhy_Process();
                if ( (cntr % APP_CNTR_VALUE(LORAMESH_APP_TX_INTERVAL)) == 0 ) {
                    (uint8_t) AquireData();
                } else {
                    cntr++;
                }
#if( OVER_THE_AIR_ACTIVATION != 0 )
                if((cntr % APP_CNTR_VALUE(LORAWAN_OTAA_INTERVAL)) == 0) {
                    appState = WAIT_NWK_JOIN;
                    continue;
                } else {
                    cntr++;
                }
#endif
#if( LORAMESH_TEST_MODE_RX_ACTIVATED != 0)
                if(!rxTestActivated) {
                    appState = TEST_MODE_RX;
                    rxTestActivated = true;
                }
#endif
#if( LORAMESH_TEST_MODE_TX_ACTIVATED != 0)
                if((cntr % APP_CNTR_VALUE(LORAMESH_APP_TX_INTERVAL)) == 0) {
                    appState = TEST_MODE_TX;
                    continue;
                } else {
                    cntr++;
                }
#endif
                break;
            case TEST_MODE_RX:
#if( LORAMESH_TEST_MODE_RX_ACTIVATED != 0)
                LOG_TRACE("Continuous rx test mode activated.");
                LoRaMesh_TestContinuousRx(868500000, DR_5, true);
#endif
                appState = ACTIVE;
                continue;
            case TEST_MODE_TX:
#if( LORAMESH_TEST_MODE_TX_ACTIVATED != 0)
                LOG_TRACE("Send test frame");
                pLoRaDevice->currChannelIndex = 2;
                LoRaPhy_TestSendFrame(testFrame, 16);
#endif
                appState = ACTIVE;
                continue;
            case STANDBY:
                break;
        } /* end switch */
        break; /* break for loop */
    } /* end for loop */
}

static uint8_t ProcessDataFrame( uint8_t *buf, uint8_t payloadSize, uint32_t devAddr,
        uint8_t fPort )
{
    uint8_t payloadIndex = 0;
    uint8_t nofEntries = 0;
    uint32_t rxAddr;
    DataEntry_t * entry;

    LOG_TRACE("Received %u bytes from 0x%08x on port %u.", payloadSize, devAddr, fPort);

    if ( fPort == AppPort ) {
        nofEntries = (uint8_t) LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xF;

        while ( nofEntries > 0 ) {
            rxAddr = (LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF);
            rxAddr |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 8);
            rxAddr |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 16);
            rxAddr |= ((pLoRaDevice->netId & 0xFF) << 24);

            if ( rxAddr == pLoRaDevice->devAddr ) {
                /* this is our own data */
                DataEntryInfo_t entryInfo;
                payloadIndex += 4; /* Timestamp offset */
                entryInfo.Value = (uint8_t) LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
                payloadIndex += 8; /* Longitude/Latitude offset */
                payloadIndex += ((entryInfo.Bits.AltitudeBar * 2) + (entryInfo.Bits.AltitudeGPS * 2)
                        + (entryInfo.Bits.VectorTrack * 4) + (entryInfo.Bits.WindSpeed * 2));
                nofEntries--;
                continue;
            }

            entry = FindEntry(rxAddr);

            if ( entry == NULL ) {
                entry = AllocateEntry();
                if ( entry == NULL ) return ERR_FAILED;
                entry->DevAddr = rxAddr;
            }

            /* Timestamp */
            entry->Timestamp = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
            entry->Timestamp |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 8);
            entry->Timestamp |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 16);
            entry->Timestamp |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 24);
            /* Entry info */
            entry->EntryInfo.Value = (uint8_t) LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
            /* Latitude */
            entry->LatitudeBinary = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
            entry->LatitudeBinary |=
                    ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 8);
            entry->LatitudeBinary |=
                    ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 16);
            entry->LatitudeBinary |=
                    ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 24);
            /* Longitude */
            entry->LongitudeBinary = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
            entry->LongitudeBinary |=
                    ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 8);
            entry->LongitudeBinary |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF)
                    << 16);
            entry->LongitudeBinary |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF)
                    << 24);
            /* Store barometric altitude if present */
            if ( entry->EntryInfo.Bits.AltitudeBar == 1 ) {
                entry->Altitude.Barometric = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
                entry->Altitude.Barometric |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++]
                        & 0xFF) << 8);
            } else {
                entry->Altitude.Barometric = 0x00;
            }
            /* Store gps altitude if present */
            if ( entry->EntryInfo.Bits.AltitudeGPS == 1 ) {
                entry->Altitude.GPS = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
                entry->Altitude.GPS |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF)
                        << 8);
            } else {
                entry->Altitude.GPS = 0x00;
            }
            /* Store barometric altitude if present */
            if ( entry->EntryInfo.Bits.VectorTrack == 1 ) {
                entry->VectorTrack.GroundSpeed = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
                entry->VectorTrack.GroundSpeed |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++]
                        & 0xFF) << 8);
                entry->VectorTrack.Track = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
                entry->VectorTrack.Track |=
                        ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 8);
            } else {
                entry->VectorTrack.GroundSpeed = 0x00;
                entry->VectorTrack.Track = 0x00;
            }
            /* Store gps altitude if present */
            if ( entry->EntryInfo.Bits.WindSpeed == 1 ) {
                entry->WindSpeed = LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++];
                entry->WindSpeed |= ((LORAMESH_BUF_PAYLOAD_START(buf)[payloadIndex++] & 0xFF) << 8);
            } else {
                entry->WindSpeed = 0x00;
            }
            nofEntries--;
        }
    } else {
        return ERR_NOTAVAIL;
    }
    return ERR_OK;
}

static void SendDataFrame( void* param )
{
    uint8_t dataSize = 0, i;
    DataEntry_t *iterEntry;

    iterEntry = FindEntry(pLoRaDevice->devAddr);

    if ( iterEntry == NULL ) return; /* No data yet aquired */

    AppData[dataSize++] = 0x00; /* Reset SDS Header */

    AppData[dataSize++] = ((iterEntry->DevAddr) & 0xFF); /* Nwk addr */
    AppData[dataSize++] = ((iterEntry->DevAddr >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->DevAddr >> 16) & 0xFF);
    AppData[dataSize++] = ((iterEntry->Timestamp) & 0xFF); /* Timestamp */
    AppData[dataSize++] = ((iterEntry->Timestamp >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->Timestamp >> 16) & 0xFF);
    AppData[dataSize++] = ((iterEntry->Timestamp >> 24) & 0xFF);
    AppData[dataSize++] = ((iterEntry->EntryInfo.Value) & 0xFF); /* Entry Info */
    AppData[dataSize++] = ((iterEntry->LatitudeBinary) & 0xFF); /* Latitude */
    AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 16) & 0xFF);
    AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 24) & 0xFF);
    AppData[dataSize++] = ((iterEntry->LongitudeBinary) & 0xFF); /* Longitude */
    AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 16) & 0xFF);
    AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 24) & 0xFF);
    AppData[dataSize++] = ((iterEntry->Altitude.GPS) & 0xFF);
    AppData[dataSize++] = ((iterEntry->Altitude.GPS >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->Altitude.Barometric) & 0xFF);
    AppData[dataSize++] = ((iterEntry->Altitude.Barometric >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->VectorTrack.GroundSpeed) & 0xFF);
    AppData[dataSize++] = ((iterEntry->VectorTrack.GroundSpeed >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->VectorTrack.Track) & 0xFF);
    AppData[dataSize++] = ((iterEntry->VectorTrack.Track >> 8) & 0xFF);
    AppData[dataSize++] = ((iterEntry->WindSpeed) & 0xFF);
    AppData[dataSize++] = ((iterEntry->WindSpeed >> 8) & 0xFF);

    /* Second, add child nodes data */
    i = 1;
    iterEntry = pDataEntries;
    while ( iterEntry != NULL ) {
        ChildNodeInfo_t* childNode;
        if ( (childNode = LoRaMesh_FindChildNode(iterEntry->DevAddr)) != NULL ) {
            AppData[dataSize++] = ((iterEntry->DevAddr) & 0xFF); /* Nwk addr */
            AppData[dataSize++] = ((iterEntry->DevAddr >> 8) & 0xFF);
            AppData[dataSize++] = ((iterEntry->DevAddr >> 16) & 0xFF);
            AppData[dataSize++] = ((iterEntry->Timestamp) & 0xFF); /* Timestamp */
            AppData[dataSize++] = ((iterEntry->Timestamp >> 8) & 0xFF);
            AppData[dataSize++] = ((iterEntry->Timestamp >> 16) & 0xFF);
            AppData[dataSize++] = ((iterEntry->Timestamp >> 24) & 0xFF);
            AppData[dataSize++] = ((iterEntry->EntryInfo.Value) & 0xFF); /* Entry Info */
            AppData[dataSize++] = ((iterEntry->LatitudeBinary) & 0xFF); /* Latitude */
            AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 8) & 0xFF);
            AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 16) & 0xFF);
            AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 24) & 0xFF);
            AppData[dataSize++] = ((iterEntry->LongitudeBinary) & 0xFF); /* Longitude */
            AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 8) & 0xFF);
            AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 16) & 0xFF);
            AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 24) & 0xFF);
            if ( iterEntry->EntryInfo.Bits.AltitudeGPS == 1 ) {
                AppData[dataSize++] = ((iterEntry->Altitude.GPS) & 0xFF);
                AppData[dataSize++] = ((iterEntry->Altitude.GPS >> 8) & 0xFF);
            }
            if ( iterEntry->EntryInfo.Bits.AltitudeBar == 1 ) {
                AppData[dataSize++] = ((iterEntry->Altitude.Barometric) & 0xFF);
                AppData[dataSize++] = ((iterEntry->Altitude.Barometric >> 8) & 0xFF);
            }
            if ( iterEntry->EntryInfo.Bits.VectorTrack == 1 ) {
                AppData[dataSize++] = ((iterEntry->VectorTrack.GroundSpeed) & 0xFF);
                AppData[dataSize++] = ((iterEntry->VectorTrack.GroundSpeed >> 8) & 0xFF);
                AppData[dataSize++] = ((iterEntry->VectorTrack.Track) & 0xFF);
                AppData[dataSize++] = ((iterEntry->VectorTrack.Track >> 8) & 0xFF);
            }
            if ( iterEntry->EntryInfo.Bits.WindSpeed == 1 ) {
                AppData[dataSize++] = ((iterEntry->WindSpeed) & 0xFF);
                AppData[dataSize++] = ((iterEntry->WindSpeed >> 8) & 0xFF);
            }
            i++;
        }
        iterEntry = iterEntry->next;
    }

    AppData[0] = i & 0xF;

    LOG_TRACE("Sending data frame at %u ms.",
            (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS));
    LoRaMesh_SendFrame(AppData, dataSize, AppPort, true, IsTxConfirmed);
}

static void SendMulticastDataFrame( void* param )
{
    uint8_t dataSize = 0, i;
    DataEntry_t *iterEntry;

    AppData[dataSize++] = 0x00; /* Reset SDS Header */

    /* Add all data entries */
    i = 0;
    iterEntry = pDataEntries;
    while ( iterEntry != NULL || iterEntry->DevAddr == 0x00 ) {
        AppData[dataSize++] = ((iterEntry->DevAddr) & 0xFF); /* Nwk addr */
        AppData[dataSize++] = ((iterEntry->DevAddr >> 8) & 0xFF);
        AppData[dataSize++] = ((iterEntry->DevAddr >> 16) & 0xFF);
        AppData[dataSize++] = ((iterEntry->Timestamp) & 0xFF); /* Timestamp */
        AppData[dataSize++] = ((iterEntry->Timestamp >> 8) & 0xFF);
        AppData[dataSize++] = ((iterEntry->Timestamp >> 16) & 0xFF);
        AppData[dataSize++] = ((iterEntry->Timestamp >> 24) & 0xFF);
        AppData[dataSize++] = ((iterEntry->EntryInfo.Value) & 0xFF); /* Entry Info */
        AppData[dataSize++] = ((iterEntry->LatitudeBinary) & 0xFF); /* Latitude */
        AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 8) & 0xFF);
        AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 16) & 0xFF);
        AppData[dataSize++] = ((iterEntry->LatitudeBinary >> 24) & 0xFF);
        AppData[dataSize++] = ((iterEntry->LongitudeBinary) & 0xFF); /* Longitude */
        AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 8) & 0xFF);
        AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 16) & 0xFF);
        AppData[dataSize++] = ((iterEntry->LongitudeBinary >> 24) & 0xFF);
        if ( iterEntry->EntryInfo.Bits.AltitudeGPS == 1 ) {
            AppData[dataSize++] = ((iterEntry->Altitude.GPS) & 0xFF);
            AppData[dataSize++] = ((iterEntry->Altitude.GPS >> 8) & 0xFF);
        }
        if ( iterEntry->EntryInfo.Bits.AltitudeBar == 1 ) {
            AppData[dataSize++] = ((iterEntry->Altitude.Barometric) & 0xFF);
            AppData[dataSize++] = ((iterEntry->Altitude.Barometric >> 8) & 0xFF);
        }
        if ( iterEntry->EntryInfo.Bits.VectorTrack == 1 ) {
            AppData[dataSize++] = ((iterEntry->VectorTrack.GroundSpeed) & 0xFF);
            AppData[dataSize++] = ((iterEntry->VectorTrack.GroundSpeed >> 8) & 0xFF);
            AppData[dataSize++] = ((iterEntry->VectorTrack.Track) & 0xFF);
            AppData[dataSize++] = ((iterEntry->VectorTrack.Track >> 8) & 0xFF);
        }
        if ( iterEntry->EntryInfo.Bits.WindSpeed == 1 ) {
            AppData[dataSize++] = ((iterEntry->WindSpeed) & 0xFF);
            AppData[dataSize++] = ((iterEntry->WindSpeed >> 8) & 0xFF);
        }
        i++;
        iterEntry = iterEntry->next;
    }
    AppData[0] = i & 0xF;

    LOG_TRACE("Sending multicast data frame at %u ms.",
            (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS));

    LoRaMesh_SendMulticast(AppData, dataSize, AppPort);
}

static void ReceiveDataFrame( void *param )
{
#if(LORAMESH_TEST_APP_ACTIVATED == 1)
    if(LoRaMesh_IsNetworkJoined()) {
        LoRaTest_AddDataFrame((uint32_t)param);
    }
#else
    uint32_t addr = (uint32_t) param;
    uint8_t ch, dr;
    ChildNodeInfo_t* childNode;
    MulticastGroupInfo_t* multicastGrp;

    if ( (childNode = LoRaMesh_FindChildNode(addr)) != NULL ) {
        ch = childNode->Connection.ChannelIndex;
        dr = childNode->Connection.DataRateIndex;
        LOG_TRACE("Open child node reception window at %u ms.",
                (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS));
    } else if ( (multicastGrp = LoRaMesh_FindMulticastGroup(addr)) != NULL ) {
        ch = multicastGrp->Connection.ChannelIndex;
        dr = multicastGrp->Connection.DataRateIndex;
        LOG_TRACE("Open multicast group reception window at %u ms.",
                (uint32_t)(TimerGetCurrentTime() * portTICK_PERIOD_MS));
    } else {
        return;
    }

    LoRaMesh_TestOpenReceptionWindow(ch, dr);
#endif
}

static uint8_t AquireData( void )
{
    DataEntry_t *entry;
    int32_t latiBin, longiBin;
    uint16_t groundSpeed, track;

    entry = FindEntry(pLoRaDevice->devAddr);

    if ( entry == NULL ) {
        entry = AllocateEntry();
        if ( entry == NULL ) return ERR_FAILED;
        entry->DevAddr = pLoRaDevice->devAddr;
    }

    GpsGetLatestGpsPositionBinary(&latiBin, &longiBin);
    GpsGetLatestTrack(&groundSpeed, &track);

    entry->Timestamp = GpsGetCurrentUnixTime();
    entry->EntryInfo.Value = 0xF;
    /* Latitude */
    entry->LatitudeBinary = latiBin;
    /* Longitude */
    entry->LongitudeBinary = longiBin;
    /* Store barometric altitude if present */
    entry->Altitude.Barometric = GpsGetLatestGpsAltitude();
    /* Store gps altitude if present */
    entry->Altitude.GPS = GpsGetLatestGpsAltitude() - 5;
    /* Store barometric altitude if present */
    entry->VectorTrack.GroundSpeed = groundSpeed;
    entry->VectorTrack.Track = track;
    /* Store gps altitude if present */
    entry->WindSpeed = 0x13AF;

    return ERR_OK;
}

static DataEntry_t *FindEntry( uint32_t devAddr )
{
    DataEntry_t *iterEntry = pDataEntries;

    while ( iterEntry != NULL ) {
        if ( iterEntry->DevAddr == devAddr ) {
            return iterEntry;
        }
        iterEntry = iterEntry->next;
    }

    return NULL;
}

static DataEntry_t *AllocateEntry( void )
{
    DataEntry_t *entry = pFreeDataEntries;

    if ( entry != NULL ) {
        pFreeDataEntries = entry->next;
        entry->DevAddr = 0x00;
        entry->Timestamp = 0x00;
        entry->EntryInfo.Value = 0x00;
        entry->LatitudeBinary = 0x00;
        entry->LongitudeBinary = 0x00;
        entry->Altitude.Barometric = 0x00;
        entry->Altitude.GPS = 0x00;
        entry->VectorTrack.GroundSpeed = 0x00;
        entry->VectorTrack.Track = 0x00;
        entry->WindSpeed = 0x00;
        entry->next = pDataEntries;
        pDataEntries = entry;
        return pDataEntries;
    }

    return NULL;
}

static void FreeEntry( DataEntry_t *entry )
{
    if ( pDataEntries != NULL ) {
        DataEntry_t* iterEntry, *prevEntry;

        prevEntry = NULL;
        iterEntry = pDataEntries;

        while ( iterEntry != NULL ) {
            if ( iterEntry == entry ) {
                if ( prevEntry == NULL ) {
                    pDataEntries = iterEntry->next;
                } else {
                    prevEntry->next = iterEntry->next;
                }
                iterEntry->next = pFreeDataEntries;
                pFreeDataEntries = iterEntry;
                break;
            }
            prevEntry = iterEntry;
            iterEntry = iterEntry->next;
        }
    }
}

static void LoRaMeshTask( void *pvParameters )
{
    (void) pvParameters; /* not used */
    appState = INITIAL; /* initialize state machine state */

    for ( ;; ) {
        Process(); /* process state machine */
        /* Task interval of 10 ms */
        vTaskDelay(RADIO_RTOS_DELAY_MS);
    } /* while */

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
    byte buf[16], cntr;
    DataEntry_t * iterEntry;

    iterEntry = pDataEntries;
    buf[0] = '\0';
    cntr = 0;

    while ( iterEntry != NULL ) {
        cntr++;
        iterEntry = iterEntry->next;
    }

    Shell_SendStatusStr((unsigned char*) "app", (unsigned char*) "\r\n", io->stdOut);
    /* Node # */
    custom_strcpy((unsigned char*) buf, sizeof(buf), (unsigned char*) "Node ");
#if defined(NODE_A)
    chcat(buf, sizeof(buf), 'A');
#elif defined(NODE_B)
    chcat(buf, sizeof(buf), 'B');
#elif defined(NODE_C)
    chcat(buf, sizeof(buf), 'C');
#elif defined(NODE_D)
    chcat(buf, sizeof(buf), 'D');
#elif defined(NODE_E)
    chcat(buf, sizeof(buf), 'E');
#endif
    Shell_SendStatusStr((unsigned char*) "  Name", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    /* Number of entries */
    buf[0] = '\0';
    strcatNum8u(buf, sizeof(buf), cntr);
    Shell_SendStatusStr((unsigned char*) "  # Entries", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    /* Class */
    if ( pLoRaDevice->devClass == CLASS_C )
        custom_strcpy((unsigned char*) buf, sizeof("C"), (unsigned char*) "C");
    else if ( pLoRaDevice->devClass == CLASS_B )
        custom_strcpy((unsigned char*) buf, sizeof("B"), (unsigned char*) "B");
    else
        custom_strcpy((unsigned char*) buf, sizeof("A"), (unsigned char*) "A");
    Shell_SendStatusStr((unsigned char*) "  Klasse", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    /* Role */
    if ( pLoRaDevice->devRole == COORDINATOR )
        custom_strcpy((unsigned char*) buf, sizeof("Koordinator"), (unsigned char*) "Koordinator");
    else if ( pLoRaDevice->devRole == ROUTER )
        custom_strcpy((unsigned char*) buf, sizeof("Router"), (unsigned char*) "Router");
    else
        custom_strcpy((unsigned char*) buf, sizeof("Leaf"), (unsigned char*) "Leaf");
    Shell_SendStatusStr((unsigned char*) "  Role", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);

    PrintEntry(FindEntry(pLoRaDevice->devAddr), io);

    return ERR_OK;
}

/*!
 * \brief Print out LoRaMesh App command help.
 *
 * \param io Std io to be used for print out.
 */
static uint8_t PrintHelp( Shell_ConstStdIO_t *io )
{
    Shell_SendHelpStr((unsigned char*) "app", (unsigned char*) "Group of app commands\r\n",
            io->stdOut);
    Shell_SendHelpStr((unsigned char*) "  help|status",
            (unsigned char*) "Print help or status information\r\n", io->stdOut);
    Shell_SendHelpStr((unsigned char*) "  entries", (unsigned char*) "Print data entries\r\n",
            io->stdOut);

    return ERR_OK;
}

/*!
 * \brief Print out entries.
 *
 * \param io Std io to be used for print out.
 */
static uint8_t PrintEntries( Shell_ConstStdIO_t *io )
{
    DataEntry_t * iterEntry;
    byte buf[32];

    iterEntry = pDataEntries;

    while ( iterEntry != NULL ) {
        /* Address */
        custom_strcpy((unsigned char*) buf, sizeof("0x"), (unsigned char*) "0x");
        strcatNum32Hex(buf, sizeof(buf), iterEntry->DevAddr);
        Shell_SendStatusStr((unsigned char*) "Node Addr", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        PrintEntry(iterEntry, io);
        iterEntry = iterEntry->next;
    }

    return ERR_OK;
}

static uint8_t PrintEntry( DataEntry_t * entry, Shell_ConstStdIO_t *io )
{
    int32_t valTmp1, valTmp2, valTmp3;
    uint16_t valTmp4;
    byte buf[64], pole;

    if ( entry == NULL ) return ERR_FAILED;

    /* Timestamp */
    buf[0] = '\0';
    strcatNum32u(buf, sizeof(buf), GpsGetCurrentUnixTime());
    Shell_SendStatusStr((unsigned char*) "  Timestamp", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    /* Latitude */
    buf[0] = '\0';
    valTmp1 = (entry->LatitudeBinary / 10000000);
    if ( valTmp1 < 0 ) {
        valTmp1 *= -1;
        pole = 'S';
    } else {
        pole = 'N';
    }
    strcatNum32u(buf, sizeof(buf), (uint32_t) valTmp1);
    chcat(buf, sizeof(buf), 0xB0);
    chcat(buf, sizeof(buf), ' ');
    valTmp2 = (entry->LatitudeBinary - (valTmp1 * 10000000)) / 100000;
    strcatNum32u(buf, sizeof(buf), (uint32_t) valTmp2);
    chcat(buf, sizeof(buf), '.');
    valTmp3 = entry->LatitudeBinary - (valTmp1 * 10000000) - (valTmp2 * 100000);
    if ( valTmp3 < 10000 ) chcat(buf, sizeof(buf), '0');
    strcatNum32u(buf, sizeof(buf), (uint32_t) valTmp3);
    chcat(buf, sizeof(buf), 0x27);
    chcat(buf, sizeof(buf), ' ');
    chcat(buf, sizeof(buf), (unsigned char) pole);
    Shell_SendStatusStr((unsigned char*) "  Latitude", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    /* Longitude */
    buf[0] = '\0';
    valTmp1 = (entry->LongitudeBinary / 1000000);
    if ( valTmp1 < 0 ) {
        valTmp1 *= -1;
        pole = 'W';
    } else {
        pole = 'E';
    }
    strcatNum32u(buf, sizeof(buf), (uint32_t) valTmp1);
    chcat(buf, sizeof(buf), 0xB0);
    chcat(buf, sizeof(buf), ' ');
    valTmp2 = (entry->LongitudeBinary - (valTmp1 * 1000000)) / 10000;
    strcatNum32u(buf, sizeof(buf), (uint32_t) valTmp2);
    chcat(buf, sizeof(buf), '.');
    valTmp3 = entry->LongitudeBinary - (valTmp1 * 1000000) - (valTmp2 * 10000);
    if ( valTmp3 < 10000 ) chcat(buf, sizeof(buf), '0');
    strcatNum32u(buf, sizeof(buf), (uint32_t) valTmp3);
    chcat(buf, sizeof(buf), 0x27);
    chcat(buf, sizeof(buf), ' ');
    chcat(buf, sizeof(buf), (unsigned char) pole);
    Shell_SendStatusStr((unsigned char*) "  Longitude", buf, io->stdOut);
    Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    /* Altitude GPS */
    if ( entry->EntryInfo.Bits.AltitudeGPS == 1 ) {
        buf[0] = '\0';
        valTmp4 = entry->Altitude.GPS / 10;
        strcatNum16u(buf, sizeof(buf), valTmp4);
        chcat(buf, sizeof(buf), '.');
        valTmp4 = entry->Altitude.GPS - (valTmp4 * 10);
        strcatNum16u(buf, sizeof(buf), valTmp4);
        custom_strcat((unsigned char*) buf, sizeof(buf), (unsigned char*) " m");
        Shell_SendStatusStr((unsigned char*) "  Alt. (GPS)", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    }
    /* Altitude Barometric */
    if ( entry->EntryInfo.Bits.AltitudeBar == 1 ) {
        buf[0] = '\0';
        valTmp4 = entry->Altitude.Barometric / 10;
        strcatNum16u(buf, sizeof(buf), valTmp4);
        chcat(buf, sizeof(buf), '.');
        valTmp4 = entry->Altitude.Barometric - (valTmp4 * 10);
        strcatNum16u(buf, sizeof(buf), valTmp4);
        custom_strcat((unsigned char*) buf, sizeof(buf), (unsigned char*) " m");
        Shell_SendStatusStr((unsigned char*) "  Alt. (bar.)", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    }
    /* Vector ground speed */
    if ( entry->EntryInfo.Bits.VectorTrack == 1 ) {
        buf[0] = '\0';
        valTmp4 = entry->VectorTrack.GroundSpeed / 100;
        strcatNum16u(buf, sizeof(buf), valTmp4);
        chcat(buf, sizeof(buf), '.');
        valTmp4 = entry->VectorTrack.GroundSpeed - (valTmp4 * 100);
        strcatNum16u(buf, sizeof(buf), valTmp4);
        custom_strcat((unsigned char*) buf, sizeof(buf), (unsigned char*) " dm/s");
        Shell_SendStatusStr((unsigned char*) "  Grnd speed", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
        /* Vector track */
        buf[0] = '\0';
        valTmp4 = entry->VectorTrack.Track / 100;
        strcatNum16u(buf, sizeof(buf), valTmp4);
        chcat(buf, sizeof(buf), '.');
        valTmp4 = entry->VectorTrack.Track - (valTmp4 * 100);
        strcatNum16u(buf, sizeof(buf), valTmp4);
        chcat(buf, sizeof(buf), 0xB0);
        custom_strcat((unsigned char*) buf, sizeof(buf), (unsigned char*) " N");
        Shell_SendStatusStr((unsigned char*) "  Track", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    }
    /* Wind speed */
    if ( entry->EntryInfo.Bits.WindSpeed == 1 ) {
        buf[0] = '\0';
        valTmp4 = entry->WindSpeed / 100;
        strcatNum16u(buf, sizeof(buf), valTmp4);
        chcat(buf, sizeof(buf), '.');
        valTmp4 = entry->WindSpeed - (valTmp4 * 100);
        strcatNum16u(buf, sizeof(buf), valTmp4);
        custom_strcat((unsigned char*) buf, sizeof(buf), (unsigned char*) " km/h");
        Shell_SendStatusStr((unsigned char*) "  Wind speed", buf, io->stdOut);
        Shell_SendStr((unsigned char*) "\r\n", io->stdOut);
    }

    return ERR_OK;
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
