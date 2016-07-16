/**
 * \file LoRaTest_App.c
 * \author Alexander Winiger alexander.winiger@hslu.ch
 * \date Dec 11, 2015
 * \version 1.0
 *
 * \brief
 *
 *******************************************************************************
 *  Change log:
 *      [1.0]   Dec 11, 2015      	Alexander Winiger
 *          - created
 *******************************************************************************
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "semphr.h"
#include "LoRaMesh.h"
#include "LoRaMacCrypto.h"
#include "LoRaTest_App.h"

#if LORAMESH_TEST_APP_ACTIVATED
#define LOG_LEVEL_TRACE
#include "debug.h"
/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
/*******************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
static uint8_t msgBuffer[64/*LORAMESH_BUFFER_SIZE*/];
static uint8_t phyFlags;
static bool addMessage;
//static SemaphoreHandle_t xSemaphore;
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
/* RTOS task function */
static void LoRaTestTask(void *pvParameters);
/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
void LoRaTest_AppInit( void )
{
    /* Initialize msg buffer */
    for ( uint16_t i = 0; i < LORAMESH_BUFFER_SIZE; i++ ) {
        msgBuffer[i] = 0u;
    }

    addMessage = false;
    phyFlags = LORAPHY_PACKET_FLAGS_NONE;

//    xSemaphore = xSemaphoreCreateCounting( 5, 0 );
    if ( xTaskCreate(LoRaTestTask, "LoRaTest", configMINIMAL_STACK_SIZE, (void*) NULL,
                    tskIDLE_PRIORITY, (TaskHandle_t*)NULL) != pdPASS ) {
        LOG_ERROR("Couldn't create task. Probably out of memory.");
    }
}
#if 0
void LoRaTest_AddJoinAcc( uint8_t* devEui, uint8_t* appEui, uint8_t appKey,
        bool addChannelList )
{
    LoRaMac_Header_t mHdr;
    uint8_t payload[LORAMESH_BUFFER_SIZE];
    uint32_t mic, payloadSize = 0;
    uint32_t netId = 0x00082F1A;
    uint32_t devAddr = 0x0057193A;
    uint16_t appNonce = LoRaPhy_GenerateNonce();

    mHdr.Value = 0u;
    mHdr.Bits.MType = MSG_TYPE_JOIN_ACCEPT;

    /* MAC header */
    payload[payloadSize++] = mHdr.Value;
    /* App Nonce */
    payload[payloadSize++] = appNonce & 0xFF;
    payload[payloadSize++] = (pLoRaDevice->devNonce >> 8) & 0xFF;
    /* Net ID*/
    payload[payloadSize++] = (netId) & 0xFF;
    payload[payloadSize++] = (netId >> 8) & 0xFF;
    payload[payloadSize++] = (netId >> 16) & 0xFF;
    /* Dev address */
    payload[payloadSize++] = (devAddr) & 0xFF;
    payload[payloadSize++] = (devAddr >> 8) & 0xFF;
    payload[payloadSize++] = (devAddr >> 16) & 0xFF;
    payload[payloadSize++] = (devAddr >> 24) & 0xFF;
    /* Down link settings */
    payload[payloadSize++] = (0x05u | 0x00u); /* No Rx1 offset / Rx2 DR: DR5 */
    /* Rx delay (1s) */
    payload[payloadSize++] = 0x01u;

    if ( addChannelList ) {
        payload[payloadSize++] = 0xFF;
    }

    LoRaMacJoinComputeMic((uint8_t*) &LORAMAC_BUF_HDR(msgBuffer), payloadSize,
            pLoRaDevice->appKey, &mic);

    /* Message integrity check */
    payload[payloadSize++] = (mic) & 0xFF;
    payload[payloadSize++] = (mic >> 8) & 0xFF;
    payload[payloadSize++] = (mic >> 16) & 0xFF;
    payload[payloadSize++] = (mic >> 24) & 0xFF;

    LoRaMacJoinEncrypt(payload + 1, payloadSize - 1, pLoRaDevice->appKey,
            LORAMAC_BUF_PAYLOAD_START(msgBuffer));

    LORAMAC_BUF_HDR(msgBuffer) = mHdr.Value;
    msgBuffer[LORAPHY_BUF_IDX_FLAGS] = LORAPHY_PACKET_FLAGS_NONE;
    msgBuffer[LORAPHY_BUF_IDX_SIZE] = payloadSize;

    addMessage = true;
}
#endif

void LoRaTest_AddDataFrame(uint32_t devAddr)
{
    ChildNodeInfo_t *childNode;
    LoRaFrm_Ctrl_t fCtrl;
    LoRaMac_Header_t mHdr;
    uint32_t mic, payloadSize;
    int32_t latiBin, longiBin;
    uint8_t frmPayload[19];

    childNode = LoRaMesh_FindChildNode(devAddr);
    if(childNode == NULL) return;

    mHdr.Value = 0u;
    mHdr.Bits.MType = MSG_TYPE_DATA_UNCONFIRMED_UP;

    fCtrl.Value = 0u;
    fCtrl.Bits.Adr = pLoRaDevice->ctrlFlags.Bits.adrCtrlOn;

    latiBin = 0x42DEC4;
    longiBin = 0x05E868;

    frmPayload[0] = 0x0F;
    frmPayload[1] = ((latiBin) & 0xFF);
    frmPayload[2] = ((latiBin >> 8) & 0xFF);
    frmPayload[3] = ((latiBin >> 16) & 0xFF);
    frmPayload[4] = ((latiBin >> 24) & 0xFF);
    frmPayload[5] = ((longiBin) & 0xFF);
    frmPayload[6] = ((longiBin >> 8) & 0xFF);
    frmPayload[7] = ((longiBin >> 16) & 0xFF);
    frmPayload[8] = ((longiBin >> 24) & 0xFF);
    frmPayload[9] = 0xB9; /* 441 müM*/
    frmPayload[10] = 0x01;
    frmPayload[11] = 0xBC; /* 443 müM */
    frmPayload[12] = 0x01;
    frmPayload[13] = 0x32; /* 50 dm/s */
    frmPayload[14] = 0x00;
    frmPayload[15] = 0x1F; /* 287° */
    frmPayload[16] = 0x01;
    frmPayload[17] = 0x0C; /* 12 km/h */
    frmPayload[18] = 0x00;

    /* Encrypt with decrypt */
    LoRaMacPayloadDecrypt(frmPayload, sizeof(frmPayload), childNode->Connection.AppSKey,
            devAddr, UP_LINK, childNode->Connection.UpLinkCounter,
            LORAFRM_BUF_PAYLOAD_START_WPORT(msgBuffer));

    msgBuffer[LORAPHY_BUF_IDX_FLAGS] = LORAPHY_PACKET_FLAGS_NONE;
    msgBuffer[LORAMAC_BUF_IDX_HDR] = mHdr.Value;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR] = (devAddr) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR + 1] = (devAddr >> 8) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR + 2] = (devAddr >> 16) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR + 3] = (devAddr >> 24) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_CTRL] = fCtrl.Value;
    msgBuffer[LORAFRM_BUF_IDX_CNTR] = childNode->Connection.UpLinkCounter & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_CNTR + 1] = (childNode->Connection.UpLinkCounter >> 8)
    & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_PORT(0)] = 2;

    payloadSize = sizeof(frmPayload) + LORAFRM_HEADER_SIZE_MIN + LORAFRM_PORT_SIZE
    + LORAMAC_HEADER_SIZE;

    LoRaMacComputeMic((uint8_t*) &msgBuffer[LORAMAC_BUF_IDX_HDR], payloadSize,
            childNode->Connection.NwkSKey, devAddr, UP_LINK,
            childNode->Connection.UpLinkCounter, &mic);

    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = mic & 0xFF;
    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = (mic >> 8) & 0xFF;
    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = (mic >> 16) & 0xFF;
    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = (mic >> 24) & 0xFF;

    msgBuffer[LORAPHY_BUF_IDX_SIZE] = payloadSize;

//    xSemaphoreGive( xSemaphore );
    addMessage = true;
}
#if 0
void LoRaTest_AddFrame( void )
{
    LoRaFrm_Ctrl_t fCtrl;
    LoRaMac_Header_t mHdr;
    uint32_t mic, payloadSize;
    uint8_t frmPayload[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0'};

    mHdr.Value = 0u;
    mHdr.Bits.MType = MSG_TYPE_DATA_UNCONFIRMED_DOWN;

    fCtrl.Value = 0u;
    fCtrl.Bits.Adr = pLoRaDevice->ctrlFlags.Bits.adrCtrlOn;

    LOG_TRACE("%s - Size %d", __FUNCTION__, sizeof(frmPayload));
    LOG_TRACE_BARE("\t");
    for ( uint8_t i = 0; i < sizeof(frmPayload); i++ )
    LOG_TRACE_BARE("0x%02x ", frmPayload[i]);
    LOG_TRACE_BARE("\r\n");

    /* Encrypt with decrypt */
    LoRaMacPayloadDecrypt(frmPayload, sizeof(frmPayload), pLoRaDevice->upLinkSlot.AppSKey,
            pLoRaDevice->devAddr, DOWN_LINK, pLoRaDevice->upLinkSlot.DownLinkCounter,
            LORAFRM_BUF_PAYLOAD_START_WPORT(msgBuffer));

    msgBuffer[LORAPHY_BUF_IDX_FLAGS] = LORAPHY_PACKET_FLAGS_NONE;
    msgBuffer[LORAMAC_BUF_IDX_HDR] = mHdr.Value;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR] = (pLoRaDevice->devAddr) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR + 1] = (pLoRaDevice->devAddr >> 8) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR + 2] = (pLoRaDevice->devAddr >> 16) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_DEVADDR + 3] = (pLoRaDevice->devAddr >> 24) & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_CTRL] = fCtrl.Value;
    msgBuffer[LORAFRM_BUF_IDX_CNTR] = pLoRaDevice->upLinkSlot.DownLinkCounter & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_CNTR + 1] = (pLoRaDevice->upLinkSlot.DownLinkCounter >> 8)
    & 0xFF;
    msgBuffer[LORAFRM_BUF_IDX_PORT(0)] = 2;

    payloadSize = sizeof(frmPayload) + LORAFRM_HEADER_SIZE_MIN + LORAFRM_PORT_SIZE
    + LORAMAC_HEADER_SIZE;

    LoRaMacComputeMic((uint8_t*) &msgBuffer[LORAMAC_BUF_IDX_HDR], payloadSize,
            pLoRaDevice->upLinkSlot.NwkSKey, pLoRaDevice->devAddr, DOWN_LINK,
            pLoRaDevice->upLinkSlot.DownLinkCounter, &mic);

    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = mic & 0xFF;
    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = (mic >> 8) & 0xFF;
    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = (mic >> 16) & 0xFF;
    *LORAMAC_BUF_MIC_START(msgBuffer, payloadSize++) = (mic >> 24) & 0xFF;

    msgBuffer[LORAPHY_BUF_IDX_SIZE] = payloadSize;

    addMessage = true;
}
#endif
/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
static void LoRaTestTask(void *pvParameters)
{
    (void)pvParameters; /* not used */

    LOG_DEBUG_BARE("Starting LoRaMesh test application...\r\n");

    for(;;) {
//        if( xSemaphoreTake( xSemaphore, portMAX_DELAY ) ) {
        if( addMessage ) {
            addMessage = false;
            LoRaPhy_QueueRxMessage((uint8_t*)&msgBuffer,
                    LORAPHY_BUF_SIZE(msgBuffer), false, phyFlags);
        }
        vTaskDelay(100 / portTICK_RATE_MS);
    } /* for */
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
#endif /* LORAMESH_TEST_APP_ACTIVATED */
