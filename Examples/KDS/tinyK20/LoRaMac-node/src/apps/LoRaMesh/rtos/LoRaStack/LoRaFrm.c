/**
 * \file LoRaFrm.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 03.12.2015
 * \version 1.0
 *
 * \brief LoRa stack network layer implementation
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "LoRaMacCrypto.h"
#include "LoRaMesh.h"

#define LOG_LEVEL_TRACE
#include "debug.h"
/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
/*! Maximum network layer payload size in absence of FOpts field */
#define ADR_ACK_LIMIT                       LORAMESH_CONFIG_ADR_ACK_LIMIT
#define ADR_ACK_DELAY                       LORAMESH_CONFIG_ADR_ACK_DELAY

/*******************************************************************************
 * API FUNCTIONS (PUBLIC)
 ******************************************************************************/
void LoRaFrm_Init( void )
{

}

uint8_t LoRaFrm_OnPacketRx( LoRaPhy_PacketDesc *packet, uint32_t devAddr, LoRaFrm_Dir_t fDir,
        uint32_t fCnt )
{
    uint8_t fPayloadSize = 0, fBuffer[LORAFRM_BUFFER_SIZE], *nwkSKey, *appSKey;
    MulticastGroupInfo_t *multicastGrp;
    ChildNodeInfo_t *childNode;
    LoRaFrm_Ctrl_t fCtrl;
    uint8_t fPort;
    bool isMulticast = false;

    fCtrl.Value = LORAFRM_BUF_CTRL(packet->phyData);
    fPort = packet->phyData[LORAFRM_BUF_IDX_PORT(fCtrl.Bits.FOptsLen)];

    if ( packet->flags & LORAPHY_PACKET_FLAGS_ACK_REQ ) {
        pLoRaDevice->ctrlFlags.Bits.ackRequested = 1;
    }

    fPayloadSize = LORAPHY_BUF_SIZE(packet->phyData) - LORAFRM_HEADER_SIZE_MIN - LORAFRM_PORT_SIZE
            - LORAMAC_HEADER_SIZE - LORAMAC_MIC_SIZE - fCtrl.Bits.FOptsLen;

    /* Evaluate what kind of message it is */
    if ( pLoRaDevice->devAddr == devAddr ) {
        nwkSKey = pLoRaDevice->upLinkSlot.NwkSKey;
        appSKey = pLoRaDevice->upLinkSlot.AppSKey;
    } else if ( (childNode = LoRaMesh_FindChildNode(devAddr)) != NULL ) {
        nwkSKey = childNode->Connection.NwkSKey;
        appSKey = childNode->Connection.AppSKey;
    } else if ( (multicastGrp = LoRaMesh_FindMulticastGroup(devAddr)) != NULL ) {
        nwkSKey = multicastGrp->Connection.NwkSKey;
        appSKey = multicastGrp->Connection.AppSKey;
        isMulticast = true;
    }

    /* Down link link from parent node or network server received */
    if ( fPort == 0 && !isMulticast ) {
        /* Decrypt with encrypt function */
        LoRaMacPayloadEncrypt(LORAFRM_BUF_PAYLOAD_START_WPORT(packet->phyData), fPayloadSize,
                nwkSKey, devAddr, fDir, fCnt, fBuffer);

        // Decode frame payload MAC commands
        LoRaMac_ProcessCommands(fBuffer, 0, fPayloadSize);
    } else {
        /* Decrypt with encrypt function */
        LoRaMacPayloadEncrypt(LORAFRM_BUF_PAYLOAD_START_WPORT(packet->phyData), fPayloadSize,
                appSKey, devAddr, fDir, fCnt, fBuffer);
    }

    // Decode frame options MAC commands
    if ( !isMulticast && fCtrl.Bits.FOptsLen > 0 )
        LoRaMac_ProcessCommands(fBuffer, LORAFRM_HEADER_SIZE_MIN + LORAMAC_HEADER_SIZE,
                fPayloadSize);

#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
    LOG_TRACE("%s - Size %d", __FUNCTION__, fPayloadSize);
    LOG_TRACE_BARE("\t");
    for ( uint8_t i = 0; i < fPayloadSize; i++ )
    LOG_TRACE_BARE("0x%02x ", fBuffer[i]);
    LOG_TRACE_BARE("\r\n");
#endif

    return LoRaMesh_OnPacketRx((uint8_t*) &fBuffer, fPayloadSize, devAddr, fPort); /* Pass message up the stack */
}

uint8_t LoRaFrm_PutPayload( uint8_t* buf, uint16_t bufSize, uint8_t payloadSize, uint32_t devAddr,
        uint8_t fPort, bool isConfirmed )
{
    uint8_t pktHdrSize = 0, fBuffer[LORAFRM_BUFFER_SIZE], *nwkSKey, *appSKey;
    MulticastGroupInfo_t *multicastGrp;
    ChildNodeInfo_t *childNode;
    LoRaMac_MsgType_t msgType;
    LoRaFrm_Ctrl_t fCtrl;
    LoRaFrm_Dir_t fDir;
    uint32_t fCnt;
    bool isMulticast = false;

    /* Initialize buffer */
    memset1(fBuffer, 0U, LORAFRM_BUFFER_SIZE);

    /* Evaluate what kind of message it is */
    if ( pLoRaDevice->devAddr == devAddr ) {
        msgType = (isConfirmed ? MSG_TYPE_DATA_CONFIRMED_UP : MSG_TYPE_DATA_UNCONFIRMED_UP);
        fDir = UP_LINK;
        nwkSKey = pLoRaDevice->upLinkSlot.NwkSKey;
        appSKey = pLoRaDevice->upLinkSlot.AppSKey;
        fCnt = pLoRaDevice->upLinkSlot.UpLinkCounter;
    } else if ( (childNode = LoRaMesh_FindChildNode(devAddr)) != NULL ) {
        msgType = (isConfirmed ? MSG_TYPE_DATA_CONFIRMED_DOWN : MSG_TYPE_DATA_UNCONFIRMED_DOWN);
        fDir = DOWN_LINK;
        nwkSKey = childNode->Connection.NwkSKey;
        appSKey = childNode->Connection.AppSKey;
        fCnt = childNode->Connection.DownLinkCounter;
    } else if ( (multicastGrp = LoRaMesh_FindMulticastGroup(devAddr)) != NULL ) {
        msgType = MSG_TYPE_DATA_UNCONFIRMED_DOWN;
        fDir = DOWN_LINK;
        nwkSKey = multicastGrp->Connection.NwkSKey;
        appSKey = multicastGrp->Connection.AppSKey;
        fCnt = multicastGrp->Connection.DownLinkCounter;
        isMulticast = true;
        isConfirmed = false;
    }

    fCtrl.Value = 0;

    fCtrl.Bits.FOptsLen = 0;
    fCtrl.Bits.FPending = 0;
    fCtrl.Bits.Ack = (isConfirmed ? 1 : 0);
    fCtrl.Bits.AdrAckReq = 0;
    fCtrl.Bits.Adr = pLoRaDevice->ctrlFlags.Bits.adrCtrlOn;

    /* Payload encryption */
    if ( (payloadSize > 0) && !isMulticast && (fPort == 0) ) { /* Encrypt frame payload with NwkSKey */
        LoRaMacPayloadEncrypt(buf, payloadSize, nwkSKey, devAddr, fDir, fCnt,
                (LORAFRM_BUF_PAYLOAD_START_WPORT(fBuffer) + pLoRaDevice->macCmdBufferIndex));
    } else if ( payloadSize > 0 ) { /* Encrypt frame payload with AppSKey */
        LoRaMacPayloadEncrypt(buf, payloadSize, appSKey, devAddr, fDir, fCnt,
                (LORAFRM_BUF_PAYLOAD_START_WPORT(fBuffer) + pLoRaDevice->macCmdBufferIndex));
    }

    /* Send ACK if pending */
    if ( !isMulticast && pLoRaDevice->ctrlFlags.Bits.ackRequested == 1U ) {
        pLoRaDevice->ctrlFlags.Bits.ackRequested = 0;
        fCtrl.Bits.Ack = 1;
    }

    /* Adjust datarate if adr is enabled */
    if ( fCtrl.Bits.Adr == true ) {
        if ( pLoRaDevice->upLinkSlot.DataRateIndex == LORAMAC_MIN_DATARATE ) {
            pLoRaDevice->adrAckCounter = 0;
            fCtrl.Bits.AdrAckReq = false;
        } else {
            if ( pLoRaDevice->adrAckCounter > ADR_ACK_LIMIT ) {
                fCtrl.Bits.AdrAckReq = true;
            } else {
                fCtrl.Bits.AdrAckReq = false;
            }
            if ( pLoRaDevice->adrAckCounter > (ADR_ACK_LIMIT + ADR_ACK_DELAY) ) {
                pLoRaDevice->adrAckCounter = 0;
                if ( pLoRaDevice->upLinkSlot.DataRateIndex > LORAMAC_MIN_DATARATE ) {
                    pLoRaDevice->upLinkSlot.DataRateIndex--;
                } else {
                    // Re-enable default channels LC1, LC2, LC3
                    pLoRaDevice->channelsMask[0] |= (LC(1) + LC(2) + LC(3));
                }
            }
        }
    }

    fBuffer[LORAFRM_BUF_IDX_DEVADDR] = (devAddr) & 0xFF;
    fBuffer[LORAFRM_BUF_IDX_DEVADDR + 1] = (devAddr >> 8) & 0xFF;
    fBuffer[LORAFRM_BUF_IDX_DEVADDR + 2] = (devAddr >> 16) & 0xFF;
    fBuffer[LORAFRM_BUF_IDX_DEVADDR + 3] = (devAddr >> 24) & 0xFF;

    fBuffer[LORAFRM_BUF_IDX_CTRL] = fCtrl.Value;

    fBuffer[LORAFRM_BUF_IDX_CNTR] = fCnt & 0xFF;
    fBuffer[LORAFRM_BUF_IDX_CNTR + 1] = (fCnt >> 8) & 0xFF;

    pktHdrSize += LORAFRM_HEADER_SIZE_MIN;

    if ( !isMulticast && fCtrl.Bits.FOptsLen > 0 ) {
//        LoRaMac_AddCommands(&buf[LORAFRM_BUF_IDX_OPTS], 15);
        pktHdrSize += fCtrl.Bits.FOptsLen;
    }

    if ( payloadSize > 0 || isMulticast ) {
        fBuffer[LORAFRM_BUF_IDX_PORT(fCtrl.Bits.FOptsLen)] = fPort;
        pktHdrSize++;
    }

    payloadSize += pktHdrSize;

#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
    LOG_TRACE("%s - Size %d", __FUNCTION__, payloadSize);
    LOG_TRACE_BARE("\t");
    for ( uint8_t i = 0; i < (payloadSize + 3); i++ )
    LOG_TRACE_BARE("0x%02x ", fBuffer[i]);
    LOG_TRACE_BARE("\r\n");
#endif
    return LoRaMac_PutPayload(fBuffer, sizeof(fBuffer), payloadSize, msgType, devAddr, fCnt,
            nwkSKey, isMulticast);
}

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
