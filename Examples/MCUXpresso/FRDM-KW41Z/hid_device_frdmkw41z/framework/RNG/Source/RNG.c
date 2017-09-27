/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file RNG.c
* RNG implementation file for the ARM CORTEX-M4 processor
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


#include "RNG_Interface.h"
#include "FunctionLib.h"
#include "SecLib.h"
#include "fsl_device_registers.h"
#include "fsl_os_abstraction.h"
#include "fsl_common.h"

#if (cPWR_UsePowerDownMode)
#include "PWR_Interface.h"
#endif

#if FSL_FEATURE_SOC_TRNG_COUNT
    #include "fsl_trng.h"
#elif FSL_FEATURE_SOC_RNG_COUNT
    #include "fsl_rnga.h"
#endif


/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#ifndef gRNG_UsePhyRngForInitialSeed_d
#define gRNG_UsePhyRngForInitialSeed_d 0
#endif

#define mPRNG_NoOfBits_c      (160)
#define mPRNG_NoOfBytes_c     (mPRNG_NoOfBits_c/8)
#define mPRNG_NoOfLongWords_c (mPRNG_NoOfBits_c/32)

#if (cPWR_UsePowerDownMode)
#define RNG_DisallowDeviceToSleep() PWR_DisallowDeviceToSleep()
#define RNG_AllowDeviceToSleep()    PWR_AllowDeviceToSleep()
#else
#define RNG_DisallowDeviceToSleep()
#define RNG_AllowDeviceToSleep()
#endif

/*! *********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */
static uint32_t XKEY[mPRNG_NoOfLongWords_c];
static uint32_t mPRNG_Requests = gRngMaxRequests_d;

#if FSL_FEATURE_SOC_TRNG_COUNT
uint8_t mRngDisallowMcuSleep = 0;
#endif

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
#if (FSL_FEATURE_SOC_RNG_COUNT == 0) && \
    (FSL_FEATURE_SOC_TRNG_COUNT == 0) && \
    (gRNG_UsePhyRngForInitialSeed_d)
extern void PhyGetRandomNo(uint32_t *pRandomNo);
#endif


/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
#if FSL_FEATURE_SOC_TRNG_COUNT
static void TRNG_ISR(void);
#endif


/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief  Initialize the RNG HW module
*
* \return  Status of the RNG initialization sequence
*
********************************************************************************** */
uint8_t RNG_Init(void)
{
    uint32_t seed;
    uint8_t status = gRngSuccess_d;
#if FSL_FEATURE_SOC_RNG_COUNT
    RNGA_Init(RNG);
    
    /* Get seed for pseudo RNG */
    if( RNGA_GetRandomData(RNG, &seed, sizeof(uint32_t)) )
    {
        status = gRngInternalError_d;
    }
#elif FSL_FEATURE_SOC_TRNG_COUNT
    trng_config_t config;

    TRNG_GetDefaultConfig(&config);
    config.frequencyCountLimit.minimum = 0x00000100;
    config.frequencyCountLimit.maximum = 0x000F0000;
    config.ringOscDiv = kTRNG_RingOscDiv0;
    config.entropyDelay = 1200;

    OSA_InstallIntHandler(TRNG0_IRQn, TRNG_ISR);

    if( kStatus_Success != TRNG_Init(TRNG0, &config) )
    {
        status = gRngInternalError_d;
    }
    else
    {
        /* Get seed for pseudo RNG */
        if( kStatus_Success != TRNG_GetRandomData(TRNG0, &seed, sizeof(seed)) )
        {
            status = gRngInternalError_d;
        }

        /* Check if the entropy generation ongoing */
        if( (!(TRNG0->MCTL & TRNG_MCTL_ENT_VAL_MASK)) && (!mRngDisallowMcuSleep) )
        {
            mRngDisallowMcuSleep = 1;
            RNG_DisallowDeviceToSleep();
        }
        
        /* Clear Interrupt status.*/
        TRNG0->INT_CTRL &= ~(TRNG_INT_CTRL_ENT_VAL_MASK | 
                             TRNG_INT_CTRL_HW_ERR_MASK  | 
                                 TRNG_INT_CTRL_FRQ_CT_FAIL_MASK);
        
        /* Enable interrupt.*/
        EnableIRQ(TRNG0_IRQn);
        TRNG0->INT_MASK |= TRNG_INT_MASK_ENT_VAL_MASK | 
                           TRNG_INT_MASK_HW_ERR_MASK  | 
                           TRNG_INT_MASK_FRQ_CT_FAIL_MASK;
    }

#else
    #if gRNG_UsePhyRngForInitialSeed_d
    /* Use 802.15.4 PHY to generate the seed for RNG */
    PhyGetRandomNo(&seed);
    #else
    /* Use MCU unique Id for RNG seed */
    seed = SIM->UIDL;
    #endif
#endif
    
    if( status == gRngSuccess_d )
    {
        /* Make sure that the seed is not zero */
        SecLib_set_rng_seed(seed+1);
    }

    /* Init Successfull */
    return status;
}


/*! *********************************************************************************
* \brief  Read a random number from the HW RNG module.
*         If the HW fails, the SW PRNG is used as backup.
*
* \param[out] pRandomNo - pointer to location where the value will be stored
*
* \return  status of the RNG module
*
********************************************************************************** */
uint8_t RNG_HwGetRandomNo(uint32_t* pRandomNo)
{
    uint8_t status = gRngSuccess_d;

    if(!pRandomNo)
    {
        status =  gRngNullPointer_d;
    }
    else
    {
#if FSL_FEATURE_SOC_RNG_COUNT  
        if( RNGA_GetRandomData(RNG, pRandomNo, sizeof(uint32_t)) )
        {
            status = gRngInternalError_d;
        }
        
#elif FSL_FEATURE_SOC_TRNG_COUNT
        if( !(TRNG0->MCTL & TRNG_MCTL_ENT_VAL_MASK) )
        {
            status = gRngInternalError_d;
        }
        else if( kStatus_Success != TRNG_GetRandomData(TRNG0, pRandomNo, sizeof(uint32_t)) )
        {
            status = gRngInternalError_d;
        }
        else
        {
            if( (!(TRNG0->MCTL & TRNG_MCTL_ENT_VAL_MASK)) && (!mRngDisallowMcuSleep) )
            {
                mRngDisallowMcuSleep = 1;
                RNG_DisallowDeviceToSleep();
            }
        }
        
#elif gRNG_UsePhyRngForInitialSeed_d
        PhyGetRandomNo(pRandomNo);
#else
        status = gRngInternalError_d;
#endif
    }
    return status;
}


/*! *********************************************************************************
* \brief  Generate a random number
*
* \param[out] pRandomNo - pointer to location where the value will be stored
*
********************************************************************************** */
void RNG_GetRandomNo(uint32_t* pRandomNo)
{
    /* Check for NULL pointers */
    if (NULL != pRandomNo)
    {
        uint32_t n = SecLib_get_random();
        FLib_MemCpy(pRandomNo, &n, sizeof(uint32_t));  
    }
}


/*! *********************************************************************************
* \brief  Initialize seed for the PRNG algorithm.
*
* \param[in]  pSeed - pointer to a buffer containing 20 bytes (160 bits).
*             Can be set using the RNG_GetRandomNo() function.
*
********************************************************************************** */
void RNG_SetPseudoRandomNoSeed(uint8_t* pSeed)
{
    mPRNG_Requests = 1;
    FLib_MemCpy( XKEY, pSeed, mPRNG_NoOfBytes_c );
}


/*! *********************************************************************************
* \brief  Pseudo Random Number Generator (PRNG) implementation
*         according to NIST FIPS Publication 186-2, APPENDIX 3
*
*         Let x be the signer's private key.  
*         The following may be used to generate m values of x:
*           Step 1. Choose a new, secret value for the seed-key, XKEY.
*           Step 2. In hexadecimal notation let
*             t = 67452301 EFCDAB89 98BADCFE 10325476 C3D2E1F0.
*             This is the initial value for H0 || H1 || H2 || H3 || H4 in the SHS.
*           Step 3. For j = 0 to m - 1 do
*             a. XSEEDj = optional user input.
*             b. XVAL = (XKEY + XSEEDj) mod 2^b
*             c. xj = G(t,XVAL) mod q
*             d. XKEY = (1 + XKEY + xj) mod 2^b
*
* \param[out]    pOut - pointer to the output buffer
* \param[in]     outBytes - the number of bytes to be copyed (1-20)
* \param[in]     pXSEED - optional user SEED. Should be NULL if not used.
*
* \return  The number of bytes copied or -1 if reseed is needed
*
********************************************************************************** */
int16_t RNG_GetPseudoRandomNo(uint8_t* pOut, uint8_t outBytes, uint8_t* pXSEED)
{
    uint32_t i;
    sha1Context_t ctx;

    if(pXSEED)
    {
        mPRNG_Requests = 1;
    }

    if (mPRNG_Requests == gRngMaxRequests_d)
    {
        outBytes = -1;
    }
    else
    {
        mPRNG_Requests++;
        
        /* a. XSEEDj = optional user input. */
        if (pXSEED)
        {
            /* b. XVAL = (XKEY + XSEEDj) mod 2^b */
            for (i=0; i<mPRNG_NoOfBytes_c; i++)
            {
                ctx.buffer[i] = ((uint8_t*)XKEY)[i] + pXSEED[i];
            }
        }
        else
        {
            for (i=0; i<mPRNG_NoOfBytes_c; i++)
            {
                ctx.buffer[i] = ((uint8_t*)XKEY)[i];
            }
        }
        
        /* c. xj = G(t,XVAL) mod q
        ***************************/
        SHA1_Hash(&ctx, ctx.buffer, mPRNG_NoOfBytes_c);
        
        /* d. XKEY = (1 + XKEY + xj) mod 2^b */
        XKEY[0] += 1;
        for (i=0; i<mPRNG_NoOfLongWords_c; i++)
        {
            XKEY[i] += ctx.hash[i];
        }
        
        /* Check if the length provided exceeds the output data size */
        if (outBytes > mPRNG_NoOfBytes_c)
        {
            outBytes = mPRNG_NoOfBytes_c;
        }
        
        /* Copy the generated number */
        for (i=0; i < outBytes; i++)
        {
            pOut[i] = ((uint8_t*)ctx.hash)[i];
        }
    }

    return outBytes;
}


/*! *********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************** */
#if FSL_FEATURE_SOC_TRNG_COUNT
static void TRNG_ISR(void)
{
    /* Clear Interrupt flags */
    TRNG0->INT_CTRL &= ~(TRNG_INT_CTRL_ENT_VAL_MASK | 
                         TRNG_INT_CTRL_HW_ERR_MASK  | 
                         TRNG_INT_CTRL_FRQ_CT_FAIL_MASK);

    if( (TRNG0->MCTL & TRNG_MCTL_ENT_VAL_MASK) && (mRngDisallowMcuSleep) )
    {
        mRngDisallowMcuSleep = 0;
        RNG_AllowDeviceToSleep();
    }
}
#endif

/********************************** EOF ***************************************/
