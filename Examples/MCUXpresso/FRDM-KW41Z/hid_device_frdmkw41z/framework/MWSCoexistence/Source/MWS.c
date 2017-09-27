/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file MWS.c
* This is the source file for the Mobile Wireless Standard Interface.
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
#include "MWS.h"
#include "fsl_os_abstraction.h"
#include "GPIO_Adapter.h"

#if gMWS_UseCoexistence_d
#include "TimersManager.h"
#endif

#if (gMWS_UseCoexistence_d) && (!gTimestamp_Enabled_d)
#warning The MWS Coexistence uses the Timestamp service. Please enable the TMR Timestamp (gTimestamp_Enabled_d).
#endif


/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
#if gMWS_Enabled_d || gMWS_UseCoexistence_d
/* MWS helper function used for chaining the active protocols, ordered by priority */
static void MWS_SetPriority (mwsProtocols_t protocol, uint8_t priority);
#endif

#if gMWS_UseCoexistence_d
/* Interrupt Service Routine for handling the changes of the RF Deny pin */
static void rf_deny_pin_changed(void);
#endif


/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
#if gMWS_Enabled_d || gMWS_UseCoexistence_d
/* Stores the id of the protocol with the Highest priority */
static mwsProtocols_t  mFirstMwsPrio = gMWS_None_c;
/* Stores the priority level for every protocol id */
static uint8_t mProtocolPriority[gMWS_None_c] =
{
    gMWS_BLEPriority_d, 
    gMWS_802_15_4Priority_d, 
    gMWS_ANTPriority_d, 
    gMWS_GENFSKPriority_d
};
/* Stores the id of the protocol with the next priority */
static mwsProtocols_t mProtocolNextPrio[gMWS_None_c] =
{
    gMWS_None_c, gMWS_None_c, gMWS_None_c, gMWS_None_c
};
#endif

#if gMWS_Enabled_d
/* Stores the id of the protocol which uses the XCVR */
static mwsProtocols_t mActiveProtocol = gMWS_None_c;
/* Stores MWS callback functions for every protocol */
static pfMwsCallback mMwsCallbacks[gMWS_None_c] = {NULL, NULL, NULL, NULL};
static uint32_t mwsLockCount = 0;
#endif

#if gMWS_UseCoexistence_d
/* Assume that the Coexistence GPIO pins are controlled by hardware */
static gpioInputPinConfig_t  *rf_deny    = NULL;
static gpioOutputPinConfig_t *rf_active  = NULL;
static gpioOutputPinConfig_t *rf_status  = NULL;
static mwsRfState_t mXcvrRxState;
static uint8_t mCoexFlags;
/* Stores Coexistence callback functions for every protocol */
static pfMwsCallback mCoexCallbacks[gMWS_None_c] = {NULL, NULL, NULL, NULL};
#endif

/*** Callback example:

uint32_t protocolCallback ( mwsEvents_t event )
{
    uint32_t status = 0;

    switch(event)
    {
    case gMWS_Init_c:
        status = protocolInittFunction();
        break;
    case gMWS_Active_c:
        status = protocolSetActiveFunction();
        break;
    case gMWS_Abort_c:
        status = protocolAbortFunction();
        break;
    case gMWS_Idle_c:
        status = protocolNotifyIdleFunction();
        break;
    case gMWS_GetInactivityDuration_c:
        status = protocolGetInactiveDurationFunction();
        break;
    default:
        status = gMWS_InvalidParameter_c;
        break;
    }
    return status;
}
*/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
mwsStatus_t MWS_Register (mwsProtocols_t protocol, pfMwsCallback cb)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_Enabled_d
    static uint8_t initialized = 0;
    
    if( !initialized )
    {
        mActiveProtocol = gMWS_None_c;
        mFirstMwsPrio = gMWS_None_c;
        mwsLockCount = 0;
        initialized = 1;
    }
    
    if( (protocol >= gMWS_None_c) || (NULL == cb) )
    {
        status = gMWS_InvalidParameter_c;
    }
    else if( NULL == mMwsCallbacks[protocol] )
    {
        mMwsCallbacks[protocol] = cb;
        MWS_SetPriority(protocol, mProtocolPriority[protocol]);
        cb( gMWS_Init_c ); /* Signal the protocol */
    }
    else
    {
        /* Already registered! Only update callback */
        mMwsCallbacks[protocol] = cb;
    }
#endif
    return status;
}

/************************************************************************************/
uint32_t MWS_GetInactivityDuration (mwsProtocols_t currentProtocol)
{
    uint32_t duration = 0xFFFFFFFFU;
#if gMWS_Enabled_d
    uint32_t i, temp;

    /* Get the minimum inactivity duration from all protocols */
    for (i=0; i<NumberOfElements(mMwsCallbacks); i++)
    {
        if( (i != currentProtocol) && (mMwsCallbacks[i]) )
        {
            temp = mMwsCallbacks[i](gMWS_GetInactivityDuration_c);
            if( temp < duration )
            {
                duration = temp;
            }
        }
    }
#endif
    return duration;
}

/************************************************************************************/
mwsStatus_t MWS_Acquire (mwsProtocols_t protocol, uint8_t force)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_Enabled_d

    OSA_InterruptDisable();
    
    if (gMWS_None_c == mActiveProtocol)
    {
        mActiveProtocol = protocol;
        mwsLockCount = 1;
        mMwsCallbacks[mActiveProtocol](gMWS_Active_c);
    }
    else if( mActiveProtocol == protocol )
    { 
        mwsLockCount++;
    }
    else
    {
        /* Lower value means higher priority */
        if( (force)
#if gMWS_UsePrioPreemption_d
           || (mProtocolPriority[mActiveProtocol] > mProtocolPriority[protocol])
#endif
          )
        {
            status = (mwsStatus_t)mMwsCallbacks[mActiveProtocol](gMWS_Abort_c);
            mActiveProtocol = protocol;
            mwsLockCount = 1;
            mMwsCallbacks[mActiveProtocol](gMWS_Active_c);
        }
        else
        {
            status = gMWS_Denied_c;
        }
    }

    OSA_InterruptEnable();
#endif
    return status; 
}

/************************************************************************************/
mwsStatus_t MWS_Release (mwsProtocols_t protocol)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_Enabled_d

    if( mActiveProtocol != gMWS_None_c )
    {
        if (protocol == mActiveProtocol)
        {
            mwsLockCount--;
            
            if( 0 == mwsLockCount )
            {
                mMwsCallbacks[mActiveProtocol](gMWS_Release_c);
                mActiveProtocol = gMWS_None_c;
                
                /* Notify other protocols that XCVR is Idle, based on the priority */
                status = MWS_SignalIdle(protocol);
            }
        }
        else
        {
            /* Another protocol is using the XCVR */
            status = gMWS_Denied_c;
        }
    }
    else
    {
        status = MWS_SignalIdle(protocol);
    }
#endif
    return status;
}

/************************************************************************************/
mwsStatus_t MWS_Abort (void)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_Enabled_d

    if( mActiveProtocol != gMWS_None_c )
    {
        if( mMwsCallbacks[mActiveProtocol](gMWS_Abort_c) )
        {
            status = gMWS_Error_c;
        }
        mActiveProtocol = gMWS_None_c;
        mwsLockCount = 0;
    }
#endif
    return status;
}

/************************************************************************************/
mwsProtocols_t MWS_GetActiveProtocol (void)
{
#if gMWS_Enabled_d
    return mActiveProtocol;
#else
    return gMWS_None_c;
#endif
}

/************************************************************************************/
mwsStatus_t MWS_SignalIdle  (mwsProtocols_t protocol)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_Enabled_d
    uint32_t i = mFirstMwsPrio;
    
    while( i != gMWS_None_c )
    {
        if( mActiveProtocol != gMWS_None_c )
        {
            break;
        }

        if( (i != protocol) && (NULL != mMwsCallbacks[i]) )
        {
            if( mMwsCallbacks[i](gMWS_Idle_c) )
            {
                status = gMWS_Error_c;
            }
        }
        i = mProtocolNextPrio[i];
    }
#endif
    return status;
}

/************************************************************************************/
mwsStatus_t MWS_CoexistenceInit(void *rfDenyPin, void *rfActivePin, void *rfStatusPin)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_UseCoexistence_d
    static uint8_t initialized = 0;
    
    if( !initialized )
    {
        initialized = 1;

        MWS_CoexistenceSetPriority(gMWS_HighPriority, gMWS_HighPriority);

        rf_active = (gpioOutputPinConfig_t*)rfActivePin;
        rf_status = (gpioOutputPinConfig_t*)rfStatusPin;
        rf_deny = (gpioInputPinConfig_t*)rfDenyPin;
        mXcvrRxState = gMWS_IdleState_c;
        TMR_TimeStampInit();
        
        if( rf_active )
        {
            GpioOutputPinInit(rf_active, 1);
            GpioClearPinOutput(rf_active);
        }
        
        if( rf_status )
        {
            GpioOutputPinInit(rf_status, 1);
            GpioClearPinOutput(rf_status);
        }
        
        /* Check if the RF Confirm signal must be handles by Software */
        if( rf_deny )
        {
            GpioInputPinInit(rf_deny, 1);
            //gcapraru: GpioSetPinInterrupt(rf_deny->gpioPort, rf_deny->gpioPin, pinInt_EitherEdge_c);
            
            if( gpio_success != GpioInstallIsr(rf_deny_pin_changed, gGpioIsrPrioNormal_c, gGpioDefaultNvicPrio_c >> 1, rf_deny) )
            {
                status = gMWS_InvalidParameter_c;
            }
        }
    }
#endif
    return status;
}

/************************************************************************************/
mwsStatus_t MWS_CoexistenceRegister (mwsProtocols_t protocol, pfMwsCallback cb)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_UseCoexistence_d
    
    if( (protocol >= gMWS_None_c) || (NULL == cb) )
    {
        status = gMWS_InvalidParameter_c;
    }
    else if( NULL == mCoexCallbacks[protocol] )
    {
        mCoexCallbacks[protocol] = cb;
        MWS_SetPriority(protocol, mProtocolPriority[protocol]);
        cb( gMWS_Init_c ); /* Signal the protocol */

        if( rf_deny )
        {
            if( GpioReadPinInput(rf_deny) == gMWS_CoexRfDenyActiveState_d )
            {
                cb(gMWS_Abort_c);
            }
            else
            {
                cb(gMWS_Idle_c);
            }
        }
    }
    else
    {
        /* Already registered! Only update callback */
        mCoexCallbacks[protocol] = cb;
    }
#endif
    return status;
}

/************************************************************************************/
void MWS_CoexistenceSetPriority(mwsRfSeqPriority_t rxPrio, mwsRfSeqPriority_t txPrio)
{
#if gMWS_UseCoexistence_d
    mCoexFlags = 0;

    if( rxPrio == gMWS_HighPriority )
    {
        mCoexFlags |= 1 << gMWS_RxState_c;
    }
    
    if( txPrio == gMWS_HighPriority )
    {
        mCoexFlags |= 1 << gMWS_TxState_c;
    }
#endif
}

/************************************************************************************/
mwsStatus_t MWS_CoexistenceRequestAccess(mwsRfState_t newState)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_UseCoexistence_d
    uint64_t timestamp;
    OSA_InterruptDisable();

    timestamp = TMR_GetTimestamp();

    /* Set Priority signal */
    if( (rf_status) && (mCoexFlags & (1 << newState)) )
    {
        GpioSetPinOutput(rf_status);
    }

    /* Signal that protocol is about to become active */
    if( rf_active )
    {
        GpioSetPinOutput(rf_active);
    }

    /* wait 50us */
    while( (TMR_GetTimestamp() - timestamp) < gMWS_CoexRxSignalTime_d ) {}
    
    /* Set RF sequence type: RX/TX */
    if( rf_status )
    {
        if( newState == gMWS_RxState_c )
        {
            /* Set status line LOW to signal RX sequence */
            GpioClearPinOutput(rf_status);
        }
        else
        {
            /* Set status line HIGH to signal TX sequence */
            GpioSetPinOutput(rf_status);
        }
    }
    
    OSA_InterruptEnable();

    /* Wait for confirm signal */
    if( rf_deny )
    {
        status = gMWS_Denied_c; /* assume access is denied */

        do
        {
            if( GpioReadPinInput(rf_deny) != gMWS_CoexRfDenyActiveState_d )
            {
                status = gMWS_Success_c;
                mXcvrRxState = newState;
                break;
            }
        }
        while( (TMR_GetTimestamp() - timestamp) < gMWS_CoexConfirmWaitTime_d );
        
        if( status != gMWS_Success_c )
        {
            MWS_CoexistenceReleaseAccess();
        }
    }
#endif
    return status;
}

/************************************************************************************/
mwsStatus_t MWS_CoexistenceChangeAccess(mwsRfState_t newState)
{
    mwsStatus_t status = gMWS_Success_c;
#if gMWS_UseCoexistence_d
    if( rf_status )
    {
        if( mXcvrRxState == gMWS_IdleState_c )
        {
            status = gMWS_Denied_c;
        }
        else
        {
            mXcvrRxState = newState;
            
            if( newState == gMWS_RxState_c )
            {
                /* Set status line LOW to signal RX sequence */
                GpioClearPinOutput(rf_status);
            }
            else
            {
                /* Set status line HIGH to signal TX sequence */
                GpioSetPinOutput(rf_status);
            }
        }
    }
#endif
    return status;
}

/************************************************************************************/
void MWS_CoexistenceReleaseAccess(void)
{
#if gMWS_UseCoexistence_d
    mXcvrRxState = gMWS_IdleState_c;
    
    if( rf_status )
    {
        GpioClearPinOutput(rf_status);
    }

    if( rf_active )
    {
        GpioClearPinOutput(rf_active);
    }
#endif
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
#if gMWS_Enabled_d || gMWS_UseCoexistence_d
static void MWS_SetPriority (mwsProtocols_t protocol, uint8_t priority)
{
    mwsProtocols_t i;

    //mMwsCallbacks[protocol].priority = priority;
    
    if( (mFirstMwsPrio == gMWS_None_c) || (priority <= mProtocolPriority[mFirstMwsPrio]) )
    {
        /* Insert at the begining of the list */
        mProtocolNextPrio[protocol] = mFirstMwsPrio;
        mFirstMwsPrio = protocol;
    }
    else
    {
        i = mFirstMwsPrio;
        
        while( i != gMWS_None_c )
        {
            if( mProtocolNextPrio[i] == gMWS_None_c )
            {
                /* Insert at the end of the list */
                mProtocolNextPrio[protocol] = gMWS_None_c;
                mProtocolNextPrio[i] = protocol;
                i = gMWS_None_c;
            }
            else if (priority <= mProtocolPriority[mProtocolNextPrio[i]])
            {
                mProtocolNextPrio[protocol] = mProtocolNextPrio[i];
                mProtocolNextPrio[i] = protocol;
                i = gMWS_None_c;
            }
            else
            {
                i = mProtocolNextPrio[i];
            }
        }
    }
}
#endif

/************************************************************************************/
#if gMWS_UseCoexistence_d
static void rf_deny_pin_changed(void)
{
    uint32_t i;
    GpioClearPinIntFlag(rf_deny);

    if( GpioReadPinInput(rf_deny) == gMWS_CoexRfDenyActiveState_d )
    {
        /* Abort active protocol */
        for( i=0; i<gMWS_None_c; i++ )
        {
            if( mCoexCallbacks[i] )
            {
                mCoexCallbacks[i](gMWS_Abort_c);
            }
        }
    }
    else
    {
        i = mFirstMwsPrio;
        
        while( i != gMWS_None_c )
        {
            if( NULL != mCoexCallbacks[i] )
            {
                mCoexCallbacks[i](gMWS_Idle_c);
            }
            i = mProtocolNextPrio[i];
        }
    }
}
#endif /* gMWS_UseCoexistence_d */