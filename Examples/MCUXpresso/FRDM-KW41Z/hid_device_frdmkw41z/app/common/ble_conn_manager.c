/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*!
* Copyright (c) 2016, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file ble_conn_manager.c
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "Panic.h"

#include "ble_general.h"
#include "gap_types.h"
#include "gap_interface.h"

#include "ble_conn_manager.h"
#include "app.h"
#include "ble_config.h"

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static void BleConnManager_GapCommonConfig(void);
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
static bleDeviceAddress_t   maBleDeviceAddress;

#if gAppUseBonding_d
uint8_t gcBondedDevices = 0;
#if gAppUsePrivacy_d
static uint8_t mcDevicesInResolvingList = 0;
#endif /* gAppUsePrivacy_d */
#endif /* gAppUseBonding_d */

#if gAppUsePairing_d
static bleDeviceAddress_t   maPeerDeviceAddress;
static bleAddressType_t     mPeerDeviceAddressType;
#endif
/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

void BleConnManager_GenericEvent(gapGenericEvent_t* pGenericEvent)
{
    switch (pGenericEvent->eventType)
    {
        case gPublicAddressRead_c:
        {
            /* Use address read from the controller */
            FLib_MemCpy(maBleDeviceAddress, pGenericEvent->eventData.aAddress, sizeof(bleDeviceAddress_t));
#if gAppUsePairing_d            
            gSmpKeys.addressType = gBleAddrTypePublic_c;
            gSmpKeys.aAddress = maBleDeviceAddress;
#endif            
        }
        break;

        case gInternalError_c:
        {
            panic(0,0,0,0);
        }
        break;

        default:
            break;
    }
}

void BleConnManager_GapDualRoleConfig(void)
{
    BleConnManager_GapCommonConfig();

#if gAppUsePrivacy_d
   gAdvParams.peerAddressType = gBleAddrTypeRandom_c;    
   gScanParams.ownAddressType = gBleAddrTypeRandom_c;       
#endif    

    /* Setup Advertising and scanning data */
    Gap_SetAdvertisingData(&gAppAdvertisingData, &gAppScanRspData);    
}

void BleConnManager_GapPeripheralConfig(void)
{
    BleConnManager_GapCommonConfig();
    
#if gAppUsePrivacy_d
   gAdvParams.peerAddressType = gBleAddrTypeRandom_c; 
#endif
   
    /* Setup Advertising and scanning data */
    Gap_SetAdvertisingData(&gAppAdvertisingData, &gAppScanRspData);    
}

void BleConnManager_GapCentralConfig(void)
{  
#if gAppUsePrivacy_d
    gScanParams.ownAddressType = gBleAddrTypeRandom_c;    
#endif  
   
    BleConnManager_GapCommonConfig();
}

void BleConnManager_GapPeripheralEvent(deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {
#if gAppUsePairing_d          
#if gAppUseBonding_d
            bool_t isBonded = FALSE;

            /* Copy peer device address information */
            mPeerDeviceAddressType = pConnectionEvent->eventData.connectedEvent.peerAddressType;
            FLib_MemCpy(maPeerDeviceAddress, pConnectionEvent->eventData.connectedEvent.peerAddress, sizeof(bleDeviceAddress_t));

            if (gBleSuccess_c == Gap_CheckIfBonded(peerDeviceId, &isBonded) &&
                FALSE == isBonded)
#endif
            {
                Gap_SendSlaveSecurityRequest(peerDeviceId,
                                gPairingParameters.withBonding,
                                gPairingParameters.securityModeAndLevel);
            }
#endif

#if gConnUpdateAlwaysAccept_d
                Gap_EnableUpdateConnectionParameters(peerDeviceId, TRUE);
#endif            
        }
        break;

        case gConnEvtParameterUpdateRequest_c:
        {
#if !gConnUpdateAlwaysAccept_d
        	gapConnParamsUpdateReq_t *pUpdateReq = &pConnectionEvent->eventData.connectionUpdateRequest;
        	bool_t result;

                /* Check values match the configured intervals */
        	result = (pUpdateReq->intervalMin > gConnUpdateIntervalMin_d) &&
                            (pUpdateReq->intervalMax < gConnUpdateIntervalMax_d) &&
                            (pUpdateReq->slaveLatency > gConnUpdateLatencyMin_d) &&
                            (pUpdateReq->slaveLatency < gConnUpdateLatencyMax_d) &&
                            (pUpdateReq->timeoutMultiplier > gConnUpdateIntervalMin_d) &&
                            (pUpdateReq->timeoutMultiplier > gConnUpdateIntervalMin_d);

        	Gap_EnableUpdateConnectionParameters(peerDeviceId, result);
#else
        	Gap_EnableUpdateConnectionParameters(peerDeviceId, TRUE);
#endif
        }
        break;

        case gConnEvtPairingRequest_c:
        {
#if gAppUsePairing_d
            gPairingParameters.centralKeys = pConnectionEvent->eventData.pairingEvent.centralKeys;
            Gap_AcceptPairingRequest(peerDeviceId, &gPairingParameters);
#else
            Gap_RejectPairing(peerDeviceId, gPairingNotSupported_c);
#endif
        }
        break;

#if gAppUsePairing_d
        case gConnEvtKeyExchangeRequest_c:
        {
            gapSmpKeys_t sentSmpKeys = gSmpKeys;

            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gLtk_c))
            {
                sentSmpKeys.aLtk = NULL;
                /* When the LTK is NULL EDIV and Rand are not sent and will be ignored. */
            }

            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gIrk_c))
            {
                sentSmpKeys.aIrk = NULL;
                /* When the IRK is NULL the Address and Address Type are not sent and will be ignored. */
            }

            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gCsrk_c))
            {
                sentSmpKeys.aCsrk = NULL;
            }

            Gap_SendSmpKeys(peerDeviceId, &sentSmpKeys);
            break;
        }

        case gConnEvtKeysReceived_c:
        {
            /* Copy peer device address information when IRK is used */
            if (pConnectionEvent->eventData.keysReceivedEvent.pKeys->aIrk != NULL)
            {
                mPeerDeviceAddressType = pConnectionEvent->eventData.keysReceivedEvent.pKeys->addressType;
                FLib_MemCpy(maPeerDeviceAddress, pConnectionEvent->eventData.keysReceivedEvent.pKeys->aAddress, sizeof(bleDeviceAddress_t));
            }
        }
        break;

        case gConnEvtPairingComplete_c:
        {
#if gAppUseBonding_d
            if (pConnectionEvent->eventData.pairingCompleteEvent.pairingSuccessful &&
                pConnectionEvent->eventData.pairingCompleteEvent.pairingCompleteData.withBonding)
            {
                /* If a bond is created, write device address in controller’s White List */
                Gap_AddDeviceToWhiteList(mPeerDeviceAddressType, maPeerDeviceAddress);
#if gAppUsePrivacy_d
                gapIdentityInformation_t aOutIdentityAddresses[gcGapControllerResolvingListSize_c];
                uint8_t identitiesCount = 0;
                bleResult_t result = Gap_GetBondedDevicesIdentityInformation(aOutIdentityAddresses,
                                                 gcGapControllerResolvingListSize_c, &identitiesCount);
               if (gBleSuccess_c == result &&
                   (identitiesCount <= gcGapControllerResolvingListSize_c) &&
                   (identitiesCount == mcDevicesInResolvingList + 1))
                {
                    /* Disable existing Privacy. */
                    if (mcDevicesInResolvingList == 0)
                    {
                        Gap_EnableHostPrivacy(FALSE, NULL);
                    }
                    else
                    {
                        Gap_EnableControllerPrivacy(FALSE, NULL, 0, NULL);
                    }
                    /* (Re)enable Controller Privacy. */
                    Gap_EnableControllerPrivacy(TRUE, gSmpKeys.aIrk, identitiesCount, aOutIdentityAddresses);
                }
#endif
            }
#endif /* gAppUseBonding_d */
        }
        break;

        case gConnEvtLongTermKeyRequest_c:
        {
            if (pConnectionEvent->eventData.longTermKeyRequestEvent.ediv == gSmpKeys.ediv &&
                pConnectionEvent->eventData.longTermKeyRequestEvent.randSize == gSmpKeys.cRandSize)
            {
                /* EDIV and RAND both matched */
                Gap_ProvideLongTermKey(peerDeviceId, gSmpKeys.aLtk, gSmpKeys.cLtkSize);
            }
            else
            /* EDIV or RAND size did not match */
            {
                Gap_DenyLongTermKey(peerDeviceId);
            }
        }
        break;

        case gConnEvtLeScDisplayNumericValue_c:
        {
            (void) pConnectionEvent->eventData.numericValueForDisplay;
            /* Display on a screen for user confirmation then validate/invalidate based on value. */
            Gap_LeScValidateNumericValue(peerDeviceId, TRUE);
        }
        break;

#endif /* gAppUsePairing_d */

    default:
        break;
    }
}


void BleConnManager_GapCentralEvent(deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    switch (pConnectionEvent->eventType)
    {
		case gConnEvtConnected_c:
		{
#if gConnUpdateAlwaysAccept_d
			Gap_EnableUpdateConnectionParameters(peerDeviceId, TRUE);
#endif
		}
    break;
        case gConnEvtSlaveSecurityRequest_c:
        {
#if gAppUsePairing_d          
            bool_t isBonded = FALSE;
           
            if ((gBleSuccess_c == Gap_CheckIfBonded(peerDeviceId, &isBonded)) &&
                (isBonded))
            {
                Gap_EncryptLink(peerDeviceId);
            }              
            else
            {
                Gap_Pair(peerDeviceId, &gPairingParameters);
            }
#else
            Gap_RejectPairing(peerDeviceId, gPairingNotSupported_c);
#endif            
        }
        break;
        
        case gConnEvtPairingRequest_c:
        {
#if gAppUsePairing_d
            gPairingParameters.peripheralKeys = pConnectionEvent->eventData.pairingEvent.peripheralKeys;
            Gap_AcceptPairingRequest(peerDeviceId, &gPairingParameters);
#else
            Gap_RejectPairing(peerDeviceId, gPairingNotSupported_c);
#endif
        }
        break;

#if gAppUsePairing_d
        case gConnEvtPasskeyRequest_c:
            /* NOTE: demo with NTAG chip requires if .securityModeAndLevel = gSecurityMode_1_Level_1_c,
             *        in all cases where the .securityModeAndLevel is used */
            Gap_EnterPasskey(peerDeviceId, gPasskeyValue_c);
            break;

        case gConnEvtPasskeyDisplay_c:
            /* Display on a screen or simply ignore */
            break;

        case gConnEvtLeScDisplayNumericValue_c:
            (void) pConnectionEvent->eventData.numericValueForDisplay;
            /* Display on a screen for user confirmation then validate/invalidate based on value. */
            Gap_LeScValidateNumericValue(peerDeviceId, TRUE);
        break;

        case gConnEvtKeyExchangeRequest_c:
        {
            gapSmpKeys_t sentSmpKeys = gSmpKeys;

            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gLtk_c))
            {
                sentSmpKeys.aLtk = NULL;
                /* When the LTK is NULL EDIV and Rand are not sent and will be ignored. */
            }

            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gIrk_c))
            {
                sentSmpKeys.aIrk = NULL;
                /* When the IRK is NULL the Address and Address Type are not sent and will be ignored. */
            }

            if (!(pConnectionEvent->eventData.keyExchangeRequestEvent.requestedKeys & gCsrk_c))
            {
                sentSmpKeys.aCsrk = NULL;
            }

            Gap_SendSmpKeys(peerDeviceId, &sentSmpKeys);
            break;
        }

        case gConnEvtLongTermKeyRequest_c:
            if (pConnectionEvent->eventData.longTermKeyRequestEvent.ediv == gSmpKeys.ediv &&
                pConnectionEvent->eventData.longTermKeyRequestEvent.randSize == gSmpKeys.cRandSize)
            {
                Gap_LoadEncryptionInformation(peerDeviceId, gSmpKeys.aLtk, &gSmpKeys.cLtkSize);
                /* EDIV and RAND both matched */
                Gap_ProvideLongTermKey(peerDeviceId, gSmpKeys.aLtk, gSmpKeys.cLtkSize);
            }
            else
            /* EDIV or RAND size did not match */
            {
                Gap_DenyLongTermKey(peerDeviceId);
            }
            break;
        case gConnEvtEncryptionChanged_c:
        {
        }
        break;

        case gConnEvtPairingComplete_c:
        {
#if gAppUseBonding_d
            if (pConnectionEvent->eventData.pairingCompleteEvent.pairingSuccessful &&
                pConnectionEvent->eventData.pairingCompleteEvent.pairingCompleteData.withBonding)
            {
                /* If a bond is created, write device address in controller’s White List */
                Gap_AddDeviceToWhiteList(mPeerDeviceAddressType, maPeerDeviceAddress);
#if gAppUsePrivacy_d
                gapIdentityInformation_t aOutIdentityAddresses[gcGapControllerResolvingListSize_c];
                uint8_t identitiesCount = 0;
                bleResult_t result = Gap_GetBondedDevicesIdentityInformation(aOutIdentityAddresses,
                                                 gcGapControllerResolvingListSize_c, &identitiesCount);
               if (gBleSuccess_c == result &&
                   (identitiesCount <= gcGapControllerResolvingListSize_c) &&
                   (identitiesCount == mcDevicesInResolvingList + 1))
                {
                    /* Disable existing Privacy. */
                    if (mcDevicesInResolvingList == 0)
                    {
                        Gap_EnableHostPrivacy(FALSE, NULL);
                    }
                    else
                    {
                        Gap_EnableControllerPrivacy(FALSE, NULL, 0, NULL);
                    }
                    /* (Re)enable Controller Privacy. */
                    Gap_EnableControllerPrivacy(TRUE, gSmpKeys.aIrk, identitiesCount, aOutIdentityAddresses);
                }
#endif
            }

#endif /* gAppUseBonding_d */
        }
#endif /* gAppUsePairing_d */

    default:
        break;
    }
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
static void BleConnManager_GapCommonConfig(void)
{
    /* Read public address from controller */
    Gap_ReadPublicDeviceAddress();

#if gAppUsePairing_d
    /* Register security requirements if pairing is used */
    Gap_RegisterDeviceSecurityRequirements(&deviceSecurityRequirements);

#ifdef gPasskeyValue_c
    /* Set local passkey. If not defined, passkey will be generated random in SMP */
    Gap_SetLocalPasskey(gPasskeyValue_c);
#endif

#endif /* gAppUsePairing_d */

    /* Populate White List if bonding is supported */
#if gAppUseBonding_d
    bleDeviceAddress_t aBondedDevAdds[gMaxBondedDevices_c];
    bleResult_t result = Gap_GetBondedStaticAddresses(aBondedDevAdds, gMaxBondedDevices_c, &gcBondedDevices);

    if (gBleSuccess_c == result && gcBondedDevices > 0)
    {
        for (uint8_t i = 0; i < gcBondedDevices; i++)
        {
            Gap_AddDeviceToWhiteList(gBleAddrTypePublic_c, aBondedDevAdds[i]);
        }
    }
#endif

#if gAppUsePrivacy_d
#if gAppUseBonding_d
    gapIdentityInformation_t   aOutIdentityAddresses[gcGapControllerResolvingListSize_c];
    uint8_t identitiesCount = 0;

    result = Gap_GetBondedDevicesIdentityInformation(aOutIdentityAddresses,
                                     gcGapControllerResolvingListSize_c, &identitiesCount);
    if (gBleSuccess_c == result && identitiesCount > 0)
    {
        mcDevicesInResolvingList = identitiesCount;
        if (mcDevicesInResolvingList > gcGapControllerResolvingListSize_c)
        {
            mcDevicesInResolvingList = gcGapControllerResolvingListSize_c;
        }
        result = Gap_EnableControllerPrivacy(TRUE, gSmpKeys.aIrk, mcDevicesInResolvingList, aOutIdentityAddresses);
    }
    else
    {
        /* Use Resolvable Private Addresses */
        Gap_EnableHostPrivacy(TRUE, gSmpKeys.aIrk);
    }
#else
    /* Use Non-Resolvable Private Addresses */
    Gap_EnableHostPrivacy(TRUE, NULL);
#endif /* gAppUseBonding_d */
#endif /* gAppUsePrivacy_d */
}

/*! *********************************************************************************
* @}
********************************************************************************** */
