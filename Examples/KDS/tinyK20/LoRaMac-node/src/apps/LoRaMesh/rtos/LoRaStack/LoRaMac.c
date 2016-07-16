/**
 * \file LoRaMac.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 03.12.2015
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
static LoRaMac_LinkCheck_t lastLinkCheck = { 0, 0 };

/*! */
static LoRaMac_BatteryLevelCallback_t batteryLevelCallback = NULL;
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/

/*******************************************************************************
 * API FUNCTIONS (PUBLIC)
 ******************************************************************************/
void LoRaMac_Init( LoRaMac_BatteryLevelCallback_t callback )
{
    batteryLevelCallback = callback;
}

uint8_t LoRaMac_OnPacketRx( LoRaPhy_PacketDesc *packet )
{
    uint8_t *payload, payloadSize, macRxBuffer[LORAMAC_BUFFER_SIZE], *micKey;
    uint32_t micRx = 0, mic = 0, frameCntr = 0, devAddr, rxAddr;
    uint16_t sequenceCntr = 0, sequenceCntrDiff = 0;
    MulticastGroupInfo_t *curMulticastGrp = NULL;
    ChildNodeInfo_t *curChildNode = NULL;
    LoRaFrm_Dir_t frameDir;
    LoRaMac_Header_t macHdr;

    payload = packet->phyData;
    payloadSize = LORAPHY_BUF_SIZE(packet->phyData);

    /* Check if incoming packet is an advertising beacon */
    if ( (packet->flags & LORAPHY_PACKET_FLAGS_FRM_MASK) == LORAPHY_PACKET_FLAGS_FRM_ADVERTISING ) {
        LOG_TRACE("Received advertising beacon.");
        return LoRaMesh_ProcessAdvertising(payload, payloadSize);
    }

    macHdr.Value = LORAMAC_BUF_HDR(packet->phyData);

    /* Check if message version matches*/
    if ( macHdr.Bits.Major != LORAMESH_CONFIG_MAJOR_VERSION ) return ERR_FAILED;

    switch ( macHdr.Bits.MType ) {
        case MSG_TYPE_JOIN_REQ:
        {
            if ( payloadSize == LORAMAC_JOIN_MESH_MSG_LENGTH ) {
                /* Join mesh request */
                return LoRaMesh_ProcessJoinMeshReq(payload, payloadSize);
            } else if ( payloadSize == LORAMAC_REBIND_MESH_MSG_LENGTH ) {
                /* Rebind mesh request */
                return LoRaMesh_ProcessRebindMeshReq(payload, payloadSize);
            } else {
                /* Regular join request (ignore)*/
                return ERR_INVALID_TYPE;
            }
            break;
        }
        case MSG_TYPE_JOIN_ACCEPT:
        {
            if ( pLoRaDevice->ctrlFlags.Bits.nwkJoined == 1 ) {
                return ERR_FAILED;
            }
            LoRaMacJoinDecrypt(LORAMAC_BUF_PAYLOAD_START(payload), payloadSize - 1,
                    pLoRaDevice->appKey, macRxBuffer + 1);

            macRxBuffer[0] = macHdr.Value;

            LoRaMacJoinComputeMic(macRxBuffer, payloadSize - LORAMAC_MIC_SIZE, pLoRaDevice->appKey,
                    &mic);

            micRx |= ((uint32_t) macRxBuffer[payloadSize - LORAMAC_MIC_SIZE]);
            micRx |= ((uint32_t) macRxBuffer[payloadSize - LORAMAC_MIC_SIZE + 1] << 8);
            micRx |= ((uint32_t) macRxBuffer[payloadSize - LORAMAC_MIC_SIZE + 2] << 16);
            micRx |= ((uint32_t) macRxBuffer[payloadSize - LORAMAC_MIC_SIZE + 3] << 24);

            if ( micRx == mic ) {
                uint8_t receiveDelay1, receiveDelay2;

                LoRaMacJoinComputeSKeys(pLoRaDevice->appKey, (macRxBuffer + 1),
                        pLoRaDevice->devNonce, pLoRaDevice->upLinkSlot.NwkSKey,
                        pLoRaDevice->upLinkSlot.AppSKey);

                pLoRaDevice->netId = (uint32_t) macRxBuffer[4];
                pLoRaDevice->netId |= ((uint32_t) macRxBuffer[5] << 8);
                pLoRaDevice->netId |= ((uint32_t) macRxBuffer[6] << 16);

                pLoRaDevice->devAddr = (uint32_t) macRxBuffer[7];
                pLoRaDevice->devAddr |= ((uint32_t) macRxBuffer[8] << 8);
                pLoRaDevice->devAddr |= ((uint32_t) macRxBuffer[9] << 16);
                pLoRaDevice->devAddr |= ((uint32_t) macRxBuffer[10] << 24);

                // DLSettings
                LoRaPhy_SetDownLinkSettings((macRxBuffer[11] >> 4) & 0x07, macRxBuffer[11] & 0x0F);
                // RxDelay
                receiveDelay1 = (macRxBuffer[12] & 0x0F);
                if ( receiveDelay1 == 0 ) {
                    receiveDelay1 = 1;
                }
                receiveDelay1 *= 1e3;
                receiveDelay2 = receiveDelay1 + 1e3;
                /* Set Rx1 and Rx2 delays */
                LoRaPhy_SetReceiveDelay1(receiveDelay1);
                LoRaPhy_SetReceiveDelay2(receiveDelay2);

                //CFList
                if ( (payloadSize - 1) > 16 ) {
                    LoRaPhy_ChannelParams_t param;
                    param.DrRange.Value = (DR_5 << 4) | DR_0;

                    for ( uint8_t i = 3, j = 0; i < (5 + 3); i++, j += 3 ) {
                        param.Frequency = ((uint32_t) macRxBuffer[13 + j]
                                | ((uint32_t) macRxBuffer[14 + j] << 8)
                                | ((uint32_t) macRxBuffer[15 + j] << 16)) * 100;
                        LoRaPhy_SetChannel(i, param);
                    }
                }
                pLoRaDevice->ctrlFlags.Bits.nwkJoined = 1;
                return ERR_OK;
            } else {
                return ERR_FAILED;
            }
            break;
        }
        case MSG_TYPE_DATA_CONFIRMED_DOWN: /* Intentional fall through */
            packet->flags |= LORAPHY_PACKET_FLAGS_ACK_REQ;
        case MSG_TYPE_DATA_UNCONFIRMED_DOWN:
        {
            rxAddr = payload[LORAFRM_BUF_IDX_DEVADDR];
            rxAddr |= ((uint32_t) payload[LORAFRM_BUF_IDX_DEVADDR + 1] << 8);
            rxAddr |= ((uint32_t) payload[LORAFRM_BUF_IDX_DEVADDR + 2] << 16);
            rxAddr |= ((uint32_t) payload[LORAFRM_BUF_IDX_DEVADDR + 3] << 24);

            if ( (curMulticastGrp = LoRaMesh_FindMulticastGroup(rxAddr)) != NULL ) {
                micKey = curMulticastGrp->Connection.NwkSKey;
                frameCntr = curMulticastGrp->Connection.DownLinkCounter;
                devAddr = curMulticastGrp->Connection.Address;
            } else {
                micKey = pLoRaDevice->upLinkSlot.NwkSKey;
                frameCntr = pLoRaDevice->upLinkSlot.DownLinkCounter;
                devAddr = pLoRaDevice->devAddr;
            }

            frameDir = DOWN_LINK;
            break;
        }
        case MSG_TYPE_DATA_CONFIRMED_UP: /* Intentional fall through */
            packet->flags |= LORAPHY_PACKET_FLAGS_ACK_REQ;
        case MSG_TYPE_DATA_UNCONFIRMED_UP:
        {
            rxAddr = payload[LORAFRM_BUF_IDX_DEVADDR];
            rxAddr |= ((uint32_t) payload[LORAFRM_BUF_IDX_DEVADDR + 1] << 8);
            rxAddr |= ((uint32_t) payload[LORAFRM_BUF_IDX_DEVADDR + 2] << 16);
            rxAddr |= ((uint32_t) payload[LORAFRM_BUF_IDX_DEVADDR + 3] << 24);

            curChildNode = LoRaMesh_FindChildNode(rxAddr);
            if ( curChildNode != NULL ) {
                frameCntr = curChildNode->Connection.UpLinkCounter;
                devAddr = curChildNode->Connection.Address;
                if ( rxAddr != devAddr ) return ERR_FAILED;
            }
            micKey = curChildNode->Connection.NwkSKey;
            frameDir = UP_LINK;
            break;
        }
        case MSG_TYPE_PROPRIETARY:
            //Intentional falltrough
        default:
            return ERR_INVALID_TYPE;
            break;
    }

    micRx |= ((uint32_t) payload[LORAMAC_BUF_IDX_HDR + payloadSize - LORAMAC_MIC_SIZE]);
    micRx |= ((uint32_t) payload[LORAMAC_BUF_IDX_HDR + payloadSize - LORAMAC_MIC_SIZE + 1] << 8);
    micRx |= ((uint32_t) payload[LORAMAC_BUF_IDX_HDR + payloadSize - LORAMAC_MIC_SIZE + 2] << 16);
    micRx |= ((uint32_t) payload[LORAMAC_BUF_IDX_HDR + payloadSize - LORAMAC_MIC_SIZE + 3] << 24);

    sequenceCntr = (uint16_t) payload[LORAFRM_BUF_IDX_CNTR];
    sequenceCntr |= (uint16_t) payload[LORAFRM_BUF_IDX_CNTR + 1] << 8;
    sequenceCntrDiff = (sequenceCntr - ((uint16_t)(frameCntr & 0xFFFF)));

    if ( sequenceCntrDiff < (1 << 15) )
        frameCntr += sequenceCntrDiff;
    else
        frameCntr += 0x10000 + (int16_t) sequenceCntrDiff;

    LoRaMacComputeMic((uint8_t*) &payload[LORAMAC_BUF_IDX_HDR], payloadSize - LORAMAC_MIC_SIZE,
            micKey, devAddr, frameDir, frameCntr, &mic);

    if ( mic == micRx ) {
#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
        LOG_TRACE("%s - Size %d", __FUNCTION__, payloadSize - LORAMAC_MIC_SIZE);
        LOG_TRACE_BARE("\t");
        for ( uint8_t i = 0; i < ((payloadSize - LORAMAC_MIC_SIZE) + 2); i++ )
        LOG_TRACE_BARE("0x%02x ", payload[i]);
        LOG_TRACE_BARE("\r\n");
#endif
        return LoRaFrm_OnPacketRx(packet, devAddr, frameDir, frameCntr);
    } else {
        LOG_ERROR("Message integrity code not valid.");
    }

    return ERR_FAILED;
}

uint8_t LoRaMac_PutPayload( uint8_t* buf, size_t bufSize, size_t payloadSize,
        LoRaMac_MsgType_t type, uint32_t addr, uint32_t seqCntr, uint8_t *key, bool isMulticast )
{
    LoRaMac_Header_t macHdr;
    LoRaFrm_Dir_t dir = DOWN_LINK;
    uint8_t flags = LORAPHY_PACKET_FLAGS_NONE;
    uint32_t mic = 0;

    macHdr.Value = 0;

    macHdr.Bits.MType = type;
    macHdr.Bits.Major = LORAMESH_CONFIG_MAJOR_VERSION;

    buf[LORAMAC_BUF_IDX_HDR] = macHdr.Value;
    payloadSize++;

    switch ( macHdr.Bits.MType ) {
        case MSG_TYPE_JOIN_REQ:
            LoRaMacJoinComputeMic(buf, payloadSize & 0xFF, pLoRaDevice->appKey, &mic);

            *LORAMAC_BUF_MIC_START(buf, payloadSize++) = mic & 0xFF;
            *LORAMAC_BUF_MIC_START(buf, payloadSize++) = (mic >> 8) & 0xFF;
            *LORAMAC_BUF_MIC_START(buf, payloadSize++) = (mic >> 16) & 0xFF;
            *LORAMAC_BUF_MIC_START(buf, payloadSize++) = (mic >> 24) & 0xFF;

            flags = LORAPHY_PACKET_FLAGS_JOIN_REQ;

            return LoRaPhy_PutPayload(buf, bufSize, payloadSize, flags);
        case MSG_TYPE_JOIN_ACCEPT:
            return ERR_NOTAVAIL;
        case MSG_TYPE_DATA_UNCONFIRMED_UP:
        case MSG_TYPE_DATA_CONFIRMED_UP:
            flags = LORAPHY_PACKET_FLAGS_FRM_REGULAR;
            dir = UP_LINK;
            break;
        case MSG_TYPE_DATA_UNCONFIRMED_DOWN:
            flags = (isMulticast) ?
                    LORAPHY_PACKET_FLAGS_FRM_MULTICAST : LORAPHY_PACKET_FLAGS_FRM_REGULAR;
            break;
        case MSG_TYPE_DATA_CONFIRMED_DOWN:
            flags = LORAPHY_PACKET_FLAGS_FRM_REGULAR;
            break;
        default:
            return ERR_INVALID_TYPE;
    }

    LoRaMacComputeMic((uint8_t*) &buf[LORAMAC_BUF_IDX_HDR], payloadSize, key, addr, dir, seqCntr,
            &mic);

    if ( (payloadSize + LORAMAC_MIC_SIZE - 1 /* MAC header already added */)
            > LORAMAC_PAYLOAD_SIZE ) {
        return ERR_OVERFLOW;
    }

    *LORAMAC_BUF_MIC_START(buf, payloadSize++) = mic & 0xFF;
    *LORAMAC_BUF_MIC_START(buf, payloadSize++) = (mic >> 8) & 0xFF;
    *LORAMAC_BUF_MIC_START(buf, payloadSize++) = (mic >> 16) & 0xFF;
    *LORAMAC_BUF_MIC_START(buf, payloadSize++) = (mic >> 24) & 0xFF;

#if(LORAMESH_DEBUG_OUTPUT_PAYLOAD == 1)
    LOG_TRACE("%s - Size %d", __FUNCTION__, payloadSize);
    LOG_TRACE_BARE("\t");
    for ( uint8_t i = 0; i < (payloadSize + 2); i++ )
    LOG_TRACE_BARE("0x%02x ", buf[i]);
    LOG_TRACE_BARE("\r\n");
#endif
    return LoRaPhy_PutPayload(buf, bufSize, payloadSize, flags);
}

uint8_t LoRaMac_AddCommand( uint8_t cmd, uint8_t *args, size_t argsSize )
{
    uint8_t cmdSize = 1;

    if ( pLoRaDevice->macCmdBufferIndex > 15 ) return ERR_OVERFLOW;

    switch ( cmd ) {
        case MAC_COMMAND_LINK_CHECK:
            /* No payload for this answer */
            break;
        case MAC_COMMAND_LINK_ADR:
            /* Margin */
            if ( argsSize < 1 ) return ERR_VALUE;
            pLoRaDevice->macCmdBuffer[pLoRaDevice->macCmdBufferIndex + 1] = args[0];
            cmdSize += 1;
            break;
        case MAC_COMMAND_DUTY_CYCLE:
            /* No payload for this answer */
            break;
        case MAC_COMMAND_RX_PARAM_SETUP:
            /* Status: Datarate ACK, Channel ACK */
            if ( argsSize < 1 ) return ERR_VALUE;
            pLoRaDevice->macCmdBuffer[pLoRaDevice->macCmdBufferIndex + 1] = args[0];
            cmdSize += 1;
            break;
        case MAC_COMMAND_DEV_STATUS:
            /* 1st byte Battery */
            /* 2nd byte Margin */
            if ( argsSize < 2 ) return ERR_VALUE;
            pLoRaDevice->macCmdBuffer[pLoRaDevice->macCmdBufferIndex + 1] = args[0];
            pLoRaDevice->macCmdBuffer[pLoRaDevice->macCmdBufferIndex + 2] = args[1];
            cmdSize += 2;
            break;
        case MAC_COMMAND_NEW_CHANNEL:
            /* Status: Datarate range OK, Channel frequency OK */
            if ( argsSize < 1 ) return ERR_VALUE;
            pLoRaDevice->macCmdBuffer[pLoRaDevice->macCmdBufferIndex + 1] = args[0];
            cmdSize += 1;
            break;
        case MAC_COMMAND_RX_TIMING_SETUP:
            /* No payload for this answer */
            break;
        case MAC_COMMAND_UP_LINK_SLOT_INFO:
            break;
        case MAC_COMMAND_MULTICAST_GROUP_INFO:
            break;
        case MAC_COMMAND_ROUTE_DISCOVER:
            break;
        case MAC_COMMAND_ADDR_CONF_RES:
            break;
        default:
            return ERR_UNKNOWN;
    }

    /* Add command */
    pLoRaDevice->macCmdBuffer[pLoRaDevice->macCmdBufferIndex] = cmd;
    pLoRaDevice->macCmdBufferIndex += cmdSize;
    return ERR_OK;
}

void LoRaMac_ProcessCommands( uint8_t *payload, uint8_t macIndex, uint8_t commandsSize )
{
    while ( macIndex < commandsSize ) {
        // Decode Frame MAC commands
        switch ( payload[macIndex++] ) {
            case MAC_COMMAND_LINK_CHECK:
            {
                pLoRaDevice->ctrlFlags.Bits.linkCheck = 1;
                lastLinkCheck.Margin = payload[macIndex++];
                lastLinkCheck.GwCnt = payload[macIndex++];
                break;
            }
            case MAC_COMMAND_LINK_ADR:
            {
                uint8_t status = 0x07;
                uint16_t chMask;
                int8_t txPower = 0;
                int8_t datarate = 0;
                uint8_t nbRep = 0;
                uint8_t chMaskCntl = 0;
                uint16_t channelsMask[6] = { 0, 0, 0, 0, 0, 0 };
                LoRaPhy_ChannelParams_t channels[LORA_MAX_NB_CHANNELS];

                // Initialize local copy of the channels mask array
                for ( uint8_t i = 0; i < 6; i++ ) {
                    channelsMask[i] = pLoRaDevice->channelsMask[i];
                }
                datarate = payload[macIndex++];
                txPower = datarate & 0x0F;
                datarate = (datarate >> 4) & 0x0F;

                if ( (pLoRaDevice->ctrlFlags.Bits.adrCtrlOn == 0)
                        && ((pLoRaDevice->currDataRateIndex != datarate)
                                || (pLoRaDevice->currTxPowerIndex != txPower)) ) {
                    // ADR disabled don't handle ADR requests if server tries to change datarate or txpower
                    // Answer the server with fail status
                    // Power ACK     = 0
                    // Data rate ACK = 0
                    // Channel mask  = 0
                    LoRaMac_AddCommand(MAC_COMMAND_LINK_ADR, NULL, 0);
                    macIndex += 3;         // Skip over the remaining bytes of the request
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
                    status &= 0xFE;   // Channel mask KO
                } else if ( (chMaskCntl >= 1) && (chMaskCntl <= 5) ) {
                    // RFU
                    status &= 0xFE;   // Channel mask KO
                } else {
                    for ( uint8_t i = 0; i < LORA_MAX_NB_CHANNELS; i++ ) {
                        if ( chMaskCntl == 6 ) {
                            if ( channels[i].Frequency != 0 ) {
                                chMask |= 1 << i;
                            }
                        } else {
                            if ( ((chMask & (1 << i)) != 0) && (channels[i].Frequency == 0) ) {   // Trying to enable an undefined channel
                                status &= 0xFE;   // Channel mask KO
                            }
                        }
                    }
                    channelsMask[0] = chMask;
                }
                if ( ((datarate < LORAMAC_MIN_DATARATE) || (datarate > LORAMAC_MAX_DATARATE))
                        == true ) {
                    status &= 0xFD;   // Datarate KO
                }

                //
                // Remark MaxTxPower = 0 and MinTxPower = 5
                //
                if ( ((LORAMAC_MAX_TX_POWER <= txPower) && (txPower <= LORAMAC_MIN_TX_POWER))
                        == false ) {
                    status &= 0xFB;   // TxPower KO
                }
                if ( (status & 0x07) == 0x07 ) {
                    for ( uint8_t i = 0; i < (sizeof(channelsMask) / sizeof(channelsMask)); i++ ) {
                        pLoRaDevice->channelsMask[i] = channelsMask[i];
                    }
                    pLoRaDevice->currDataRateIndex = datarate;
                    pLoRaDevice->currTxPowerIndex = txPower;
                    pLoRaDevice->nbRep = nbRep;
                }
                LoRaMac_AddCommand(MAC_COMMAND_LINK_ADR, (uint8_t*) &status, sizeof(status));
                break;
            }
            case MAC_COMMAND_DUTY_CYCLE:
            {
                LoRaPhy_SetMaxDutyCycle(payload[macIndex++]);
                LoRaMac_AddCommand(MAC_COMMAND_DUTY_CYCLE, NULL, 0);
                break;
            }
            case MAC_COMMAND_RX_PARAM_SETUP:
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
                    status &= 0xFE;   // Channel frequency KO
                }

                if ( ((datarate < LORAMAC_MIN_DATARATE) || (datarate > LORAMAC_MAX_DATARATE))
                        == true ) {
                    status &= 0xFD;   // Datarate KO
                }

                if ( ((drOffset < LORAMAC_MIN_RX1_DR_OFFSET)
                        || (drOffset > LORAMAC_MAX_RX1_DR_OFFSET)) == true ) {
                    status &= 0xFB;   // Rx1DrOffset range KO
                }

                if ( (status & 0x07) == 0x07 ) {
                    LoRaPhy_SetRxParameters(drOffset, datarate, freq);
                }
                LoRaMac_AddCommand(MAC_COMMAND_RX_PARAM_SETUP, (uint8_t*) &status, 0);
                break;
            }
            case MAC_COMMAND_DEV_STATUS:
            {
                uint8_t cmdBuf[2];
                cmdBuf[0] = BAT_LEVEL_NO_MEASURE;
                if ( batteryLevelCallback != NULL ) {
                    cmdBuf[0] = batteryLevelCallback();
                }
                LoRaMac_AddCommand(MAC_COMMAND_DEV_STATUS, (uint8_t*) cmdBuf, 2);
                break;
            }
            case MAC_COMMAND_NEW_CHANNEL:
            {
                uint8_t status = 0x03;
                int8_t channelIndex = 0;
                LoRaPhy_ChannelParams_t chParam;

                channelIndex = payload[macIndex++];
                chParam.Frequency = (uint32_t) payload[macIndex++];
                chParam.Frequency |= (uint32_t) payload[macIndex++] << 8;
                chParam.Frequency |= (uint32_t) payload[macIndex++] << 16;
                chParam.Frequency *= 100;
                chParam.DrRange.Value = payload[macIndex++];

                if ( (channelIndex < 3) || (channelIndex > LORA_MAX_NB_CHANNELS) ) {
                    status &= 0xFE;   // Channel frequency KO
                }

                if ( Radio.CheckRfFrequency(chParam.Frequency) == false ) {
                    status &= 0xFE;   // Channel frequency KO
                }

                if ( (chParam.DrRange.Fields.Min > chParam.DrRange.Fields.Max)
                        || (((LORAMAC_MIN_DATARATE <= chParam.DrRange.Fields.Min)
                                && (chParam.DrRange.Fields.Min <= LORAMAC_MAX_DATARATE)) == false)
                        || (((LORAMAC_MIN_DATARATE <= chParam.DrRange.Fields.Max)
                                && (chParam.DrRange.Fields.Max <= LORAMAC_MAX_DATARATE)) == false) ) {
                    status &= 0xFD;   // Datarate range KO
                }
                if ( (status & 0x03) == 0x03 ) {
                    LoRaPhy_SetChannel(channelIndex, chParam);
                }
                LoRaMac_AddCommand(MAC_COMMAND_NEW_CHANNEL, (uint8_t*) &status, sizeof(status));
                break;
            }
            case MAC_COMMAND_RX_TIMING_SETUP:
            {
                uint8_t delay = payload[macIndex++] & 0x0F;
                if ( delay == 0 ) {
                    delay++;
                }
                LoRaPhy_SetReceiveDelay1(delay * 1e6);
                LoRaPhy_SetReceiveDelay2((delay * 1e6) + 1e6);
                LoRaMac_AddCommand(MAC_COMMAND_RX_TIMING_SETUP, NULL, 0);
                break;
            }
            case MAC_COMMAND_UP_LINK_SLOT_INFO:
            {
                uint8_t interval = payload[macIndex++] & 0x0F;
                if ( interval < 1 ) {
                    interval = 1;
                }
                interval *= 1e6;
                break;
            }
            case MAC_COMMAND_MULTICAST_GROUP_INFO:
            {
                break;
            }
            case MAC_COMMAND_ROUTE_DISCOVER:
            {
                break;
            }
            case MAC_COMMAND_ADDR_CONF_RES:
            {
                break;
            }
            default:
                // Unknown command. ABORT MAC commands processing
                return;
        }
    }
}
/*******************************************************************************
 * PUBLIC SETUP FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
