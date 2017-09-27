/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file SecLib.c
* This is the source file for the security module that implements AES.
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


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "MemManager.h"
#include "FunctionLib.h"
#include "SecLib.h"
#include "fsl_device_registers.h"
#include "fsl_os_abstraction.h"
#include "Panic.h"

#if FSL_FEATURE_SOC_MMCAU_COUNT

#ifndef FREESCALE_MMCAU
#define FREESCALE_MMCAU 1
#endif

#ifndef FREESCALE_MMCAU_SHA
#define FREESCALE_MMCAU_SHA 1
#endif

#include "cau_api.h"
#endif /* FSL_FEATURE_SOC_MMCAU_COUNT */

#if FSL_FEATURE_SOC_LTC_COUNT
#include "fsl_ltc.h"
#endif

#ifndef cPWR_UsePowerDownMode
#define cPWR_UsePowerDownMode 0
#endif

#if (cPWR_UsePowerDownMode)
#include "PWR_Interface.h"
#endif


/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
/* AES constants */
#define AES128 128
#define AES128_ROUNDS 10

#define AES192 192
#define AES192_ROUNDS 12

#define AES256 256
#define AES256_ROUNDS 14

#if (cPWR_UsePowerDownMode)
    #define SecLib_DisallowToSleep() PWR_DisallowDeviceToSleep()
    #define SecLib_AllowToSleep()    PWR_AllowDeviceToSleep()
#else
    #define SecLib_DisallowToSleep()
    #define SecLib_AllowToSleep()
#endif

#if USE_RTOS && (FSL_FEATURE_SOC_LTC_COUNT || FSL_FEATURE_SOC_MMCAU_COUNT)
    #define SECLIB_MUTEX_LOCK()   OSA_MutexLock(mSecLibMutexId, osaWaitForever_c)
    #define SECLIB_MUTEX_UNLOCK() OSA_MutexUnlock(mSecLibMutexId)
#else
    #define SECLIB_MUTEX_LOCK()
    #define SECLIB_MUTEX_UNLOCK()
#endif /* USE_RTOS */


/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */
typedef union _uuint128_tag
{
    uint8_t  u8[16];
    uint64_t u64[2];
} uuint128_t;

#if FSL_FEATURE_SOC_MMCAU_COUNT
typedef struct mmcauAesContext_tag{
    uint8_t keyExpansion[44*4];
    uint8_t alignedIn[AES_BLOCK_SIZE];
    uint8_t alignedOut[AES_BLOCK_SIZE];
}mmcauAesContext_t;

/*! MMCAU AES Context Buffer for both AES Encrypt and Decrypt operations.*/
mmcauAesContext_t mmcauAesCtx;
#endif /* FSL_FEATURE_SOC_MMCAU_COUNT */

#if USE_RTOS && (FSL_FEATURE_SOC_LTC_COUNT || FSL_FEATURE_SOC_MMCAU_COUNT)
/*! Mutex used to protect the AES Context when an RTOS is used. */
osaMutexId_t mSecLibMutexId;
#endif /* USE_RTOS */


/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */

/* AES function - SW emulated*/
void sw_Aes128(const uint8_t *pData, const uint8_t *pKey, uint8_t enc, uint8_t *pReturnData);
uint8_t sw_AES128_CCM(uint8_t* pInput,   uint16_t inputLen,
                      uint8_t* pAuthData, uint16_t authDataLen,
                      uint8_t* pNonce,    uint8_t  nonceSize,
                      uint8_t* pKey,      uint8_t* pOutput,
                      uint8_t* pCbcMac,   uint8_t  macSize,
                      uint32_t flags);

/* SHA1 functions - SW emulated*/
void sw_sha1_initialize_output (uint32_t *sha1_state);
void sw_sha1_hash_n (uint8_t *msg_data, int32_t num_blks, uint32_t *sha1_state);
void sw_sha1_hash   (uint8_t *msg_data, uint32_t *sha1_state);
void sw_sha1_update (uint8_t *msg_data, int32_t num_blks, uint32_t *sha1_state);

/* SHA256 functions - SW emulated*/
void sw_sha256_initialize_output (uint32_t *sha256_state);
void sw_sha256_hash_n (uint8_t *msg_data, int32_t num_blks, uint32_t *sha256_state);
void sw_sha256_hash   (uint8_t *msg_data, uint32_t *sha256_state);
void sw_sha256_update (uint8_t *msg_data, int32_t num_blks, uint32_t *sha256_state);

ecdhStatus_t Ecdh_GenerateNewKeys
(
    ecdhPublicKey_t*    pOutPublicKey,
	ecdhPrivateKey_t*   pOutPrivateKey,
    void*               pMultiplicationBuffer
);

ecdhStatus_t Ecdh_ComputeDhKey
(
    ecdhPrivateKey_t*   pPrivateKey,
    ecdhPublicKey_t*    pPeerPublicKey,
    ecdhDhKey_t*        pOutDhKey,
    void*               pMultiplicationBuffer
);

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
static void SHA1_hash_n(uint8_t* pData, uint32_t nBlk, uint32_t* pHash);
static void SHA256_hash_n(uint8_t* pData, uint32_t nBlk, uint32_t* pHash);
static void AES_128_CMAC_Generate_Subkey(uint8_t *key, uint8_t *K1, uint8_t *K2);
static void SecLib_LeftShiftOneBit(uint8_t *input, uint8_t *output);
static void SecLib_Padding(uint8_t *lastb, uint8_t *pad, uint32_t length);
static void SecLib_Xor128(uint8_t *a, uint8_t *b, uint8_t *out);

#if FSL_FEATURE_SOC_LTC_COUNT 
#else
static void AES_128_IncrementCounter(uint8_t* ctr);
#endif


/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief  This function performs initialization of the cryptografic HW acceleration.
*
********************************************************************************** */
void SecLib_Init(void)
{
#if FSL_FEATURE_SOC_LTC_COUNT
    LTC_Init(LTC0);
#endif /* FSL_FEATURE_SOC_LTC_COUNT */
    
#if USE_RTOS && (FSL_FEATURE_SOC_LTC_COUNT || FSL_FEATURE_SOC_MMCAU_COUNT)
    /*! Initialize the MMCAU AES Context Buffer Mutex here. */
       mSecLibMutexId = OSA_MutexCreate();
    if (mSecLibMutexId == NULL)
    {
        panic( ID_PANIC(0,0), (uint32_t)SecLib_Init, 0, 0 );
        return;
    }
#endif
}

/*! *********************************************************************************
* \brief  This function performs AES-128 encryption on a 16-byte block.
*
* \param[in]  pInput Pointer to the location of the 16-byte plain text block.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte ciphered output.
*
* \pre All Input/Output pointers must refer to a memory address alligned to 4 bytes!
*
********************************************************************************** */
void AES_128_Encrypt(const uint8_t* pInput,
                     const uint8_t* pKey,
                     uint8_t* pOutput)
{
#if FSL_FEATURE_SOC_MMCAU_COUNT
    mmcauAesContext_t *pCtx = &mmcauAesCtx;
    uint8_t* pIn;
    uint8_t* pOut;
#endif
    
    SecLib_DisallowToSleep();
    SECLIB_MUTEX_LOCK();
    
#if FSL_FEATURE_SOC_MMCAU_COUNT
    /* Check if pKey is 4 bytes aligned */
    if ((uint32_t)pKey & 0x00000003)
    {
        FLib_MemCpy(pCtx->alignedIn, (uint8_t*)pKey, AES_BLOCK_SIZE);
        pIn = pCtx->alignedIn;
    }
    else
    {
        pIn = (uint8_t*)pKey;
    }

    /* Expand Key */
    mmcau_aes_set_key(pIn, AES128, pCtx->keyExpansion);

    /* Check if pData is 4 bytes aligned */
    if ((uint32_t)pInput & 0x00000003)
    {
        FLib_MemCpy(pCtx->alignedIn, (uint8_t*)pInput, AES_BLOCK_SIZE);
        pIn = pCtx->alignedIn;
    }
    else
    {
        pIn = (uint8_t*)pInput;
    }

    /* Check if pReturnData is 4 bytes aligned */
    if ((uint32_t)pOutput & 0x00000003)
    {
        pOut = pCtx->alignedOut;
    }
    else
    {
        pOut = pOutput;
    }

    /* Encrypt data */
    mmcau_aes_encrypt(pIn, pCtx->keyExpansion, AES128_ROUNDS, pOut);

    if (pOut == pCtx->alignedOut)
    {
        FLib_MemCpy(pOutput, pCtx->alignedOut, AES_BLOCK_SIZE);
    }

#elif FSL_FEATURE_SOC_LTC_COUNT
    LTC_AES_EncryptEcb(LTC0, pInput, pOutput, AES_BLOCK_SIZE, pKey, AES_BLOCK_SIZE);

#else
    sw_Aes128(pInput, pKey, 1, pOutput);
#endif
    
    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep();
}

/*! *********************************************************************************
* \brief  This function performs AES-128 decryption on a 16-byte block.
*
* \param[in]  pInput Pointer to the location of the 16-byte plain text block.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte ciphered output.
*
* \pre All Input/Output pointers must refer to a memory address alligned to 4 bytes!
*
********************************************************************************** */
void AES_128_Decrypt(const uint8_t* pInput,
                     const uint8_t* pKey,
                     uint8_t* pOutput)
{
#if FSL_FEATURE_SOC_MMCAU_COUNT
    mmcauAesContext_t *pCtx = &mmcauAesCtx;
    uint8_t* pIn;
    uint8_t* pOut;
#endif
    
    SecLib_DisallowToSleep();
    SECLIB_MUTEX_LOCK();

#if FSL_FEATURE_SOC_MMCAU_COUNT
    /* Check if pKey is 4 bytes aligned */
    if ((uint32_t)pKey & 0x00000003) 
    {
        FLib_MemCpy( pCtx->alignedIn, (uint8_t*)pKey, AES_BLOCK_SIZE);
        pIn = pCtx->alignedIn;
    }
    else
    {
        pIn = (uint8_t*)pKey;
    }

    /* Expand Key */  
    mmcau_aes_set_key(pIn, AES128, pCtx->keyExpansion);

    /* Check if pData is 4 bytes aligned */
    if ((uint32_t)pInput & 0x00000003) 
    {
        FLib_MemCpy( pCtx->alignedIn, (uint8_t*)pInput, AES_BLOCK_SIZE);
        pIn = pCtx->alignedIn;
    }
    else
    {
        pIn = (uint8_t*)pInput;
    }

    /* Check if pReturnData is 4 bytes aligned */
    if ((uint32_t)pOutput & 0x00000003)
    {
        pOut = pCtx->alignedOut;
    }
    else
    {
        pOut = pOutput;
    }

    /* Decrypt data */
    mmcau_aes_decrypt(pIn, pCtx->keyExpansion, AES128_ROUNDS, pOut);

    if (pOut == pCtx->alignedOut)
    {
        FLib_MemCpy( pOutput, pCtx->alignedOut, AES_BLOCK_SIZE);
    }

#elif FSL_FEATURE_SOC_LTC_COUNT
    LTC_AES_DecryptEcb(LTC0, pInput, pOutput, AES_BLOCK_SIZE, pKey, AES_BLOCK_SIZE, kLTC_EncryptKey);
#else 
    sw_Aes128(pInput, pKey, 0, pOutput);
#endif

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep();
}

/*! *********************************************************************************
* \brief  This function performs AES-128-ECB encryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
* \pre All Input/Output pointers must refer to a memory address alligned to 4 bytes!
*
********************************************************************************** */
void AES_128_ECB_Encrypt(uint8_t* pInput,
                         uint32_t inputLen,
                         uint8_t* pKey,
                         uint8_t* pOutput)
{
    uint8_t tempBuffIn[AES_BLOCK_SIZE] = {0};
    uint8_t tempBuffOut[AES_BLOCK_SIZE] = {0};

    /* If remaining data bigger than one AES block size */
    while( inputLen > AES_BLOCK_SIZE )
    {
        AES_128_Encrypt(pInput, pKey, pOutput);
        pInput += AES_BLOCK_SIZE;
        pOutput += AES_BLOCK_SIZE;
        inputLen -= AES_BLOCK_SIZE;
    }

    /* If remaining data is smaller then one AES block size */
    FLib_MemCpy(tempBuffIn, pInput, inputLen);
    AES_128_Encrypt(tempBuffIn, pKey, tempBuffOut);
    FLib_MemCpy(pOutput, tempBuffOut, inputLen);
}

/*! *********************************************************************************
* \brief  This function performs AES-128-ECB encryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  numBlocks Input message number of 16-byte blocks.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
* \pre All Input/Output pointers must refer to a memory address alligned to 4 bytes!
*
********************************************************************************** */
void AES_128_ECB_Block_Encrypt(uint8_t* pInput,
                               uint32_t numBlocks,
                               const uint8_t* pKey,
                               uint8_t* pOutput)
{
    while( numBlocks )
    {
        AES_128_Encrypt(pInput, pKey, pOutput);
        numBlocks--;
        pInput += AES_BLOCK_SIZE;
        pOutput += AES_BLOCK_SIZE;
    }
}

/*! *********************************************************************************
* \brief  This function performs AES-128-CBC encryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
********************************************************************************** */
void AES_128_CBC_Encrypt(uint8_t* pInput,
                         uint32_t inputLen,
                         uint8_t* pInitVector,
                         uint8_t* pKey,
                         uint8_t* pOutput)
{
#if FSL_FEATURE_SOC_LTC_COUNT
    SecLib_DisallowToSleep();
    SECLIB_MUTEX_LOCK();
    LTC_AES_EncryptCbc(LTC0, pInput, pOutput, inputLen, pInitVector, pKey, AES_BLOCK_SIZE);
    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep();

#else
    static uint8_t tempBuffIn[AES_BLOCK_SIZE] = {0};
    uint8_t tempBuffOut[AES_BLOCK_SIZE] = {0};

    if( pInitVector != NULL )
    {
        FLib_MemCpy(tempBuffIn, pInitVector, AES_BLOCK_SIZE);
    }

    /* If remaining data is bigger than one AES block size */
    while( inputLen > AES_BLOCK_SIZE )
    {
        SecLib_XorN(tempBuffIn, pInput, AES_BLOCK_SIZE);
        AES_128_Encrypt(tempBuffIn, pKey, pOutput);
        FLib_MemCpy(tempBuffIn, pOutput, AES_BLOCK_SIZE);
        pInput += AES_BLOCK_SIZE;
        pOutput += AES_BLOCK_SIZE;
        inputLen -= AES_BLOCK_SIZE;
    }

    /* If remaining data is smaller then one AES block size  */
    SecLib_XorN(tempBuffIn, pInput, inputLen);
    AES_128_Encrypt(tempBuffIn, pKey, tempBuffOut);
    FLib_MemCpy(tempBuffIn, tempBuffOut, AES_BLOCK_SIZE);
    FLib_MemCpy(pOutput, tempBuffOut, inputLen);
#endif
}

/*! *********************************************************************************
* \brief  This function performs AES-128-CBC encryption on a message block after
*padding it with 1 bit of 1 and 0 bits trail.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes. 
*
*             IMPORTANT: User must make sure that input and output
*             buffers have at least inputLen + 16 bytes size
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
* Return value: size of output buffer (after padding)
*
********************************************************************************** */
uint32_t AES_128_CBC_Encrypt_And_Pad(uint8_t* pInput, 
                         uint32_t inputLen,
                         uint8_t* pInitVector, 
                         uint8_t* pKey, 
                         uint8_t* pOutput)
{
    uint32_t newLen = 0;
    uint8_t idx;
    /*compute new length*/
    newLen = inputLen + (AES_BLOCK_SIZE - (inputLen & (AES_BLOCK_SIZE-1)));
    /*pad the input buffer with 1 bit of 1 and trail of 0's from inputLen to newLen*/
    for(idx=0; idx < (newLen - inputLen)-1; idx++)
    {
        pInput[newLen-1 - idx] = 0x00;
    }
    pInput[inputLen] = 0x80;

    /* CBC-Encrypt */
#if FSL_FEATURE_SOC_LTC_COUNT
    SecLib_DisallowToSleep();
    SECLIB_MUTEX_LOCK();
    LTC_AES_EncryptCbc(LTC0, pInput, pOutput, newLen, pInitVector, pKey, AES_BLOCK_SIZE);
    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep();
#else
    static uint8_t tempBuffIn[AES_BLOCK_SIZE] = {0};
    
    if( pInitVector != NULL )
    {
        FLib_MemCpy(tempBuffIn, pInitVector, AES_BLOCK_SIZE);
    }
    inputLen = newLen;
    while( inputLen > 0 )
    {
        SecLib_XorN(tempBuffIn, pInput, AES_BLOCK_SIZE);
        AES_128_Encrypt(tempBuffIn, pKey, pOutput);
        FLib_MemCpy(tempBuffIn, pOutput, AES_BLOCK_SIZE);
        pInput += AES_BLOCK_SIZE;
        pOutput += AES_BLOCK_SIZE;
        inputLen -= AES_BLOCK_SIZE;
    }
#endif
    return newLen;
}
/*! *********************************************************************************
* \brief  This function performs AES-128-CBC decryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
* Return value: size of output buffer (after depadding)
*
********************************************************************************** */
uint32_t AES_128_CBC_Decrypt_And_Depad(uint8_t* pInput, 
                                       uint32_t inputLen,
                                       uint8_t* pInitVector, 
                                       uint8_t* pKey, 
                                       uint8_t* pOutput)
{
    uint32_t newLen = inputLen;
#if FSL_FEATURE_SOC_LTC_COUNT
    SecLib_DisallowToSleep();
    SECLIB_MUTEX_LOCK();
    LTC_AES_DecryptCbc(LTC0, pInput, pOutput, inputLen, pInitVector, pKey, AES_BLOCK_SIZE, kLTC_DecryptKey);
    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep();

#else
    static uint8_t temp[2*AES_BLOCK_SIZE] = {0};

    if((inputLen & (AES_BLOCK_SIZE - 1)) != 0)
    {
        return 0;
    }

    if(pInitVector != NULL)
    {
        FLib_MemCpy(temp, pInitVector, AES_BLOCK_SIZE);
    }

    FLib_MemCpy(temp + AES_BLOCK_SIZE, pInput, AES_BLOCK_SIZE);

    while( inputLen > 0 )
    {
        AES_128_Decrypt(pInput, pKey, pOutput);
        
        SecLib_XorN(pOutput, temp, AES_BLOCK_SIZE);
        
        pInput += AES_BLOCK_SIZE;
        pOutput += AES_BLOCK_SIZE;
        inputLen -= AES_BLOCK_SIZE;
        
        FLib_MemCpy(temp, temp + AES_BLOCK_SIZE, AES_BLOCK_SIZE);
        if(inputLen > 0)
        {
            FLib_MemCpy(temp + AES_BLOCK_SIZE, pInput, AES_BLOCK_SIZE);
        }
    }

    pOutput -= newLen;
#endif
    while( (pOutput[--newLen] != 0x80) && (newLen !=0) ) {}
    return newLen;
}
/*! *********************************************************************************
* \brief  This function performs AES-128-CTR encryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pCounter Pointer to the location of the 128-bit counter.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
********************************************************************************** */
void AES_128_CTR(uint8_t* pInput,
                 uint32_t inputLen,
                 uint8_t* pCounter,
                 uint8_t* pKey,
                 uint8_t* pOutput)
{
#if FSL_FEATURE_SOC_LTC_COUNT
    SecLib_DisallowToSleep();
    SECLIB_MUTEX_LOCK();
    LTC_AES_EncryptCtr(LTC0, pInput, pOutput, inputLen, pCounter, pKey, AES_BLOCK_SIZE, NULL, NULL);
    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep();

#else
    uint8_t tempBuffIn[AES_BLOCK_SIZE] = {0};
    uint8_t encrCtr[AES_BLOCK_SIZE] = {0};

    /* If remaining data bigger than one AES block size */
    while( inputLen > AES_BLOCK_SIZE )
    {
        FLib_MemCpy(tempBuffIn, pInput, AES_BLOCK_SIZE);
        AES_128_Encrypt(pCounter, pKey, encrCtr);
        SecLib_XorN(tempBuffIn, encrCtr, AES_BLOCK_SIZE);
        FLib_MemCpy(pOutput, tempBuffIn, AES_BLOCK_SIZE);
        pInput += AES_BLOCK_SIZE;
        pOutput += AES_BLOCK_SIZE;
        inputLen -= AES_BLOCK_SIZE;
        AES_128_IncrementCounter(pCounter);
    }

    /* If remaining data is smaller then one AES block size  */
    FLib_MemCpy(tempBuffIn, pInput, inputLen);
    AES_128_Encrypt(pCounter, pKey, encrCtr);
    SecLib_XorN(tempBuffIn, encrCtr, AES_BLOCK_SIZE);
    FLib_MemCpy(pOutput, tempBuffIn, inputLen);
    AES_128_IncrementCounter(pCounter);
#endif
}

/*! *********************************************************************************
* \brief  This function performs AES-128-OFB encryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
********************************************************************************** */
void AES_128_OFB(uint8_t* pInput,
                 uint32_t inputLen,
                 uint8_t* pInitVector,
                 uint8_t* pKey,
                 uint8_t* pOutput)
{
    uint8_t tempBuffIn[AES_BLOCK_SIZE] = {0};
    uint8_t tempBuffOut[AES_BLOCK_SIZE] = {0};

    if( pInitVector != NULL )
    {
        FLib_MemCpy(tempBuffIn, pInitVector, AES_BLOCK_SIZE);
    }

    /* If remaining data is bigger than one AES block size */
    while( inputLen > AES_BLOCK_SIZE )
    {
        AES_128_Encrypt(tempBuffIn, pKey, tempBuffOut);
        FLib_MemCpy(tempBuffIn, tempBuffOut, AES_BLOCK_SIZE);
        SecLib_XorN(tempBuffOut, pInput, AES_BLOCK_SIZE);
        FLib_MemCpy(pOutput, tempBuffOut, AES_BLOCK_SIZE);
        pInput += AES_BLOCK_SIZE;
        pOutput += AES_BLOCK_SIZE;
        inputLen -= AES_BLOCK_SIZE;
    }

    /* If remaining data is smaller then one AES block size  */
    AES_128_Encrypt(tempBuffIn, pKey, tempBuffOut);
    FLib_MemCpy(tempBuffIn, tempBuffOut, AES_BLOCK_SIZE);
    SecLib_XorN(tempBuffOut, pInput, inputLen);
    FLib_MemCpy(pOutput, tempBuffOut, inputLen);
}

/*! *********************************************************************************
* \brief  This function performs AES-128-CMAC on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes. The input data must be provided MSB first.
*
* \param[in]  pKey Pointer to the location of the 128-bit key. The key must be provided MSB first.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code. The code will be generated MSB first.
*
* \remarks This is public open source code! Terms of use must be checked before use!
*
********************************************************************************** */
void AES_128_CMAC(uint8_t* pInput,
                  uint32_t inputLen,
                  uint8_t* pKey,
                  uint8_t* pOutput)
{
    uint8_t X[16];
    uint8_t Y[16];
    uint8_t M_last[16];
    uint8_t padded[16];

    uint8_t K1[16];
    uint8_t K2[16];

    uint8_t n;
    uint32_t i;
    uint8_t flag;

    AES_128_CMAC_Generate_Subkey(pKey, K1, K2);

    n = (uint8_t) ((inputLen + 15) / 16); /* n is number of rounds */

    if (n == 0) 
    {
        n = 1;
        flag = 0;
    } 
    else 
    {
        if ((inputLen % 16) == 0) 
        { /* last block is a complete block */
            flag = 1;
        } 
        else 
        { /* last block is not complete block */
            flag = 0;
        }
    }

    /* Process the last block  - the last part the MSB first input data */
    if (flag) 
    { /* last block is complete block */
        SecLib_Xor128(&pInput[16 * (n - 1)], K1, M_last);
    } 
    else 
    {
        SecLib_Padding(&pInput[16 * (n - 1)], padded, inputLen % 16);
        SecLib_Xor128(padded, K2, M_last);
    }

    for (i = 0; i < 16; i++)
    {
        X[i] = 0;
    }

    for (i = 0; i < n - 1; i++) 
    {
        SecLib_Xor128(X, &pInput[16 * i], Y); /* Y := Mi (+) X  */
        AES_128_Encrypt(Y, pKey, X); /* X := AES-128(KEY, Y) */
    }

    SecLib_Xor128(X, M_last, Y);
    AES_128_Encrypt(Y, pKey, X);

    for (i = 0; i < 16; i++) 
    {
        pOutput[i] = X[i];
    }
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CMAC on a message block accepting input data
*         which is in LSB first format and computing the authentication code starting fromt he end of the data.
* 
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes. The input data must be provided LSB first.
*
* \param[in]  pKey Pointer to the location of the 128-bit key. The key must be provided MSB first.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code. The code will be generated MSB first.
*
********************************************************************************** */
void AES_128_CMAC_LsbFirstInput (uint8_t* pInput,
                                 uint32_t inputLen,
                                 uint8_t* pKey,
                                 uint8_t* pOutput)
{
    uint8_t X[16];
    uint8_t Y[16];
    uint8_t M_last[16];
    uint8_t padded[16];
    uint8_t reversedBlock[16];

    uint8_t K1[16];
    uint8_t K2[16];

    uint8_t n;
    uint32_t i;
    uint8_t flag;

    AES_128_CMAC_Generate_Subkey(pKey, K1, K2);

    n = (uint8_t) ((inputLen + 15) / 16); /* n is number of rounds */

    if (n == 0)
    {
        n = 1;
        flag = 0;
    } 
    else
    {
        if ((inputLen % 16) == 0) /* last block is a complete block */
        {
            flag = 1;
        }
        else /* last block is not complete block */
        { 
            flag = 0;
        }
    }
    
    /* Process the last block  - the first part the LSB first input data */
    if (flag)  /* last block is complete block */
    {
        FLib_MemCpyReverseOrder (reversedBlock, &pInput[0], 16);
        SecLib_Xor128 (reversedBlock, K1, M_last);
    } 
    else 
    {
        FLib_MemCpyReverseOrder (reversedBlock, &pInput[0], inputLen % 16);
        SecLib_Padding(reversedBlock, padded, inputLen % 16);
        SecLib_Xor128(padded, K2, M_last);
    }

    for (i = 0; i < 16; i++)
    {
        X[i] = 0;
    }
    
    for (i = 0; i < n - 1; i++)
    {
        FLib_MemCpyReverseOrder (reversedBlock, &pInput[inputLen - 16 * (i + 1)], 16);
        SecLib_Xor128(X, reversedBlock, Y); /* Y := Mi (+) X  */
        AES_128_Encrypt(Y, pKey, X); /* X := AES-128(KEY, Y) */
    }

    SecLib_Xor128(X, M_last, Y);
    AES_128_Encrypt(Y, pKey, X);

    for (i = 0; i < 16; i++) {
        pOutput[i] = X[i];
    }
}


/*! *********************************************************************************
* \brief  This function performs AES 128 CMAC Pseudo-Random Function (AES-CMAC-PRF-128),
*         according to rfc4615, on a message block.
* 
* \details The AES-CMAC-PRF-128 algorithm behaves similar to teh AES CMAC 128 algorithm
*          but removes 128 bit key size restriction.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes.
*
* \param[in]  pVarKey Pointer to the location of the variable length key.
*
* \param[in]  varKeyLen Length of the input key in bytes
*
* \param[out]  pOutput Pointer to the location to store the 16-byte pseudo random variable.
*
********************************************************************************** */
void AES_CMAC_PRF_128(uint8_t* pInput, 
                      uint32_t inputLen, 
                      uint8_t* pVarKey,
                      uint32_t varKeyLen,
                      uint8_t* pOutput)
{
    uint8_t  K[16];  /*!< Temporary key location to be used if the key length is not 16 bytes. */
    uint8_t* pCmacKey = pVarKey; /*!<  Pointer to the key used by the CMAC operation which generates the
                                  *    output. */
    if (varKeyLen)
    {
        if (varKeyLen != 16)
        {
            uint8_t K0[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
            /*! Perform AES 128 CMAC on the variable key if it has a length which
            *  is different from 16 bytes using a 128 bit key with all zeroes and
            *  set the CMAC key to point to the result. */
            AES_128_CMAC(pVarKey, varKeyLen, K0, K);
            pCmacKey = K;
        }
        
        /*! Perform the CMAC operation which generates the output using the local
        *  key pointer whcih will be set to the initial key or the generated one. */
        AES_128_CMAC(pInput, inputLen, pCmacKey, pOutput);
    }
}

/*! *********************************************************************************
* \brief  This function performs AES-128-EAX encryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes.
*
* \param[in]  pNonce Pointer to the location of the nonce.
*
* \param[in]  nonceLen Nonce length in bytes.
*
* \param[in]  pHeader Pointer to the location of header.
*
* \param[in]  headerLen Header length in bytes.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code.
*
* \param[out]  pTag Pointer to the location to store the 128-bit tag.
*
********************************************************************************** */
secResultType_t AES_128_EAX_Encrypt(uint8_t* pInput,
                                    uint32_t inputLen,
                                    uint8_t* pNonce,
                                    uint32_t nonceLen,
                                    uint8_t* pHeader,
                                    uint8_t headerLen,
                                    uint8_t* pKey,
                                    uint8_t* pOutput,
                                    uint8_t* pTag)
{
    uint8_t *buf;
    uint32_t buf_len;
    uint8_t nonce_mac[AES_BLOCK_SIZE];
    uint8_t hdr_mac[AES_BLOCK_SIZE];
    uint8_t data_mac[AES_BLOCK_SIZE];
    uint8_t tempBuff[AES_BLOCK_SIZE];
    secResultType_t status = gSecSuccess_c;
    uint32_t i;

    if( nonceLen > inputLen )
    {
        buf_len = nonceLen;
    }
    else
    {
        buf_len = inputLen;
    }

    if( headerLen > buf_len )
    {
        buf_len = headerLen;
    }

    buf_len += 16U;

    buf = MEM_BufferAlloc(buf_len);

    if( buf == NULL )
    {
        status = gSecAllocError_c;
    }
    else
    {
        FLib_MemSet(buf, 0, 15);
        
        buf[15] = 0;
        FLib_MemCpy((buf + 16), pNonce, nonceLen);
        AES_128_CMAC(buf, 16 + nonceLen, pKey, nonce_mac);
        
        buf[15] = 1;
        FLib_MemCpy((buf + 16), pHeader, headerLen);
        AES_128_CMAC(buf, 16 + headerLen, pKey, hdr_mac);
        
        /* keep the original value of nonce_mac, because AES_128_CTR will increment it */
        FLib_MemCpy(tempBuff, nonce_mac, nonceLen);
        
        AES_128_CTR(pInput, inputLen, tempBuff, pKey, pOutput);
        
        buf[15] = 2;
        FLib_MemCpy((buf + 16), pOutput, inputLen);
        AES_128_CMAC(buf, 16 + inputLen, pKey, data_mac);
        
        for (i = 0; i < AES_BLOCK_SIZE; i++)
        {
            pTag[i] = nonce_mac[i] ^ data_mac[i] ^ hdr_mac[i];
        }
        
        MEM_BufferFree(buf);
    }

    return status;
}

/*! *********************************************************************************
* \brief  This function performs AES-128-EAX decryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes.
*
* \param[in]  pNonce Pointer to the location of the nonce.
*
* \param[in]  nonceLen Nonce length in bytes.
*
* \param[in]  pHeader Pointer to the location of header.
*
* \param[in]  headerLen Header length in bytes.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code.
*
* \param[out]  pTag Pointer to the location to store the 128-bit tag.
*
********************************************************************************** */
secResultType_t AES_128_EAX_Decrypt(uint8_t* pInput,
                                    uint32_t inputLen,
                                    uint8_t* pNonce,
                                    uint32_t nonceLen,
                                    uint8_t* pHeader,
                                    uint8_t headerLen,
                                    uint8_t* pKey,
                                    uint8_t* pOutput,
                                    uint8_t* pTag)
{
    uint8_t *buf;
    uint32_t buf_len;
    uint8_t nonce_mac[AES_BLOCK_SIZE];
    uint8_t hdr_mac[AES_BLOCK_SIZE];
    uint8_t data_mac[AES_BLOCK_SIZE];
    secResultType_t status = gSecSuccess_c;
    uint32_t i;

    if( nonceLen > inputLen )
    {
        buf_len = nonceLen;
    }
    else
    {
        buf_len = inputLen;
    }

    if( headerLen > buf_len )
    {
        buf_len = headerLen;
    }

    buf_len += 16U;

    buf = MEM_BufferAlloc(buf_len);

    if( buf == NULL )
    {
        status = gSecAllocError_c;
    }
    else
    {
        FLib_MemSet(buf, 0, 15);
        
        buf[15] = 0;
        FLib_MemCpy((buf + 16), pNonce, nonceLen);
        AES_128_CMAC(buf, 16 + nonceLen, pKey, nonce_mac);
        
        buf[15] = 1;
        FLib_MemCpy((buf + 16), pHeader, headerLen);
        AES_128_CMAC(buf, 16 + headerLen, pKey, hdr_mac);
        
        buf[15] = 2;
        FLib_MemCpy((buf + 16), pInput, inputLen);
        AES_128_CMAC(buf, 16 + inputLen, pKey, data_mac);
        
        MEM_BufferFree(buf);
        
        for (i = 0; i < AES_BLOCK_SIZE; i++)
        {
            if (pTag[i] != (nonce_mac[i] ^ data_mac[i] ^ hdr_mac[i]))
            {
                status = gSecError_c;
                break;
            }
        }
        
        if( gSecSuccess_c == status )
        {
            AES_128_CTR(pInput, inputLen, nonce_mac, pKey, pOutput);
        }
    }

    return status;
}

/*! *********************************************************************************
* \brief  This function performs AES-128-CCM on a message block.
*
* \param[in]  pInput       Pointer to the location of the input message (plaintext or cyphertext).
*
* \param[in]  inputLen     Length of the input plaintext in bytes when encrypting.
*                          Length of the input cypertext without the MAC length when decrypting.
* 
* \param[in]  pAuthData    Pointer to the additional authentication data.
*
* \param[in]  authDataLen  Length of additional authentication data.
*
* \param[in]  pNonce       Pointer to the Nonce.
*
* \param[in]  nonceSize    The size of the nonce (7-13).
*
* \param[in]  pKey         Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput     Pointer to the location to store the plaintext data when decrypting.
*                          Pointer to the location to store the cyphertext data when encrypting.
*
* \param[out]  pCbcMac     Pointer to the location to store the Message Authentication Code (MAC) when encrypting.
*                          Pointer to the location where the received MAC can be found when decrypting.
*
* \param[out]  macSize     The size of the MAC.
*
* \param[out]  flags       Select encrypt/decrypt operations (gSecLib_CCM_Encrypt_c, gSecLib_CCM_Decrypt_c)
*
* \return 0 if encryption/decryption was successfull; otherwise, error code for failed encryption/decryption
*
* \remarks At decryption, MIC fail is also signaled by returning a non-zero value.
*
********************************************************************************** */
uint8_t AES_128_CCM(uint8_t* pInput,
                    uint16_t inputLen,
                    uint8_t* pAuthData,
                    uint16_t authDataLen,
                    uint8_t* pNonce,
                    uint8_t  nonceSize,
                    uint8_t* pKey,
                    uint8_t* pOutput,
                    uint8_t* pCbcMac,
                    uint8_t  macSize,
                    uint32_t flags)
{
    uint8_t status;

    SecLib_DisallowToSleep();
    SECLIB_MUTEX_LOCK();

#if FSL_FEATURE_SOC_LTC_COUNT
    if( flags & gSecLib_CCM_Decrypt_c )
    {
        status = LTC_AES_DecryptTagCcm(LTC0, pInput, pOutput, inputLen, pNonce, nonceSize, pAuthData, authDataLen, pKey, AES_BLOCK_SIZE, pCbcMac, macSize);
    }
    else
    {
        status = LTC_AES_EncryptTagCcm(LTC0, pInput, pOutput, inputLen, pNonce, nonceSize, pAuthData, authDataLen, pKey, AES_BLOCK_SIZE, pCbcMac, macSize);
    }

#else
        status = sw_AES128_CCM(pInput, inputLen, pAuthData, authDataLen, pNonce, nonceSize, pKey, pOutput, pCbcMac, macSize, flags);
#endif

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep();

    return status;
}

/*! *********************************************************************************
* \brief  This function calculates XOR of individual byte pairs in two uint8_t arrays.
*         pDst[i] := pDst[i] ^ pSrc[i] for i=0 to n-1
*
* \param[in, out]  pDst First byte array operand for XOR and destination byte array
*
* \param[in]  pSrc Second byte array operand for XOR
*
* \param[in]  n  Length of the byte arrays which will be XORed
*
********************************************************************************** */
void SecLib_XorN(uint8_t* pDst,
                 uint8_t* pSrc,
                 uint8_t n)
{
    while( n )
    {
        *pDst = *pDst ^ *pSrc;
        pDst = pDst + 1;
        pSrc = pSrc + 1;
        n--;
    }
}

/*! *********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************** */

#if !(FSL_FEATURE_SOC_LTC_COUNT)
/*! *********************************************************************************
* \brief  Increments the value of a given counter vector.
*
* \param [in/out]     ctr         Counter.
*
* \remarks
*
********************************************************************************** */
static void AES_128_IncrementCounter(uint8_t* ctr)
{
    uint32_t i;
    uint64_t tempLow;
    uuint128_t tempCtr;

    for(i=0;i<AES_BLOCK_SIZE;i++)
    {
        tempCtr.u8[AES_BLOCK_SIZE-i-1] = ctr[i];
    }

    tempLow = tempCtr.u64[0];
    tempCtr.u64[0]++;

    if(tempLow > tempCtr.u64[0])
    {
        tempCtr.u64[1]++;
    }

    for(i=0;i<AES_BLOCK_SIZE;i++)
    {
        ctr[i] = tempCtr.u8[AES_BLOCK_SIZE-i-1];
    }
}
#endif /* !(FSL_FEATURE_SOC_LTC_COUNT) */

/*! *********************************************************************************
* \brief  Generates the two subkeys that correspond two an AES key
*
* \param [in]    key        AES Key.
*
* \param [out]   K1         First subkey.
*
* \param [out]   K2         Second subkey.
*
* \remarks   This is public open source code! Terms of use must be checked before use!
*
********************************************************************************** */
static void AES_128_CMAC_Generate_Subkey(uint8_t *key,
                                         uint8_t *K1,
                                         uint8_t *K2)
{
    uint8_t const_Rb[16] = {0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x87};
    uint8_t L[16];
    uint8_t Z[16];
    uint8_t tmp[16];
    uint32_t i;

    for ( i=0; i<16; i++ ) 
    {
        Z[i] = 0;
    }

    AES_128_Encrypt(Z,key,L);

    if ( (L[0] & 0x80) == 0 )
    {
        /* If MSB(L) = 0, then K1 = L << 1 */
        SecLib_LeftShiftOneBit(L,K1);
    }
    else
    {
        /* Else K1 = ( L << 1 ) (+) Rb */
        SecLib_LeftShiftOneBit(L,tmp);
        SecLib_Xor128(tmp,const_Rb,K1);
    }

    if ( (K1[0] & 0x80) == 0 )
    {
        SecLib_LeftShiftOneBit(K1,K2);
    }
    else
    {
        SecLib_LeftShiftOneBit(K1,tmp);
        SecLib_Xor128(tmp,const_Rb,K2);
    }
}

/*! *********************************************************************************
* \brief    Shifts a given vector to the left with one bit.
*
* \param [in]      input         Input vector.
*
* \param [out]     output        Output vector.
*
* \remarks   This is public open source code! Terms of use must be checked before use!
*
********************************************************************************** */
static void SecLib_LeftShiftOneBit(uint8_t *input,
                                   uint8_t *output)
{
    int32_t i;
    uint8_t overflow = 0;

    for ( i=15; i>=0; i-- )
    {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;
    }
}

/*! *********************************************************************************
* \brief  This function pads an incomplete 16 byte block of data, where padding is 
*         the concatenation of x and a single '1',
*         followed by the minimum number of '0's, so that the total length is equal to 128 bits.
*
* \param[in, out] lastb Pointer to the last block to be padded
*
* \param[in]  pad       Padded block destination
*
* \param[in]  length    Number of bytes in the block to be padded
*
* \remarks   This is public open source code! Terms of use must be checked before use!
*
********************************************************************************** */
static void SecLib_Padding(uint8_t *lastb,
                           uint8_t *pad,
                           uint32_t length)
{
    uint32_t j;

    /* original last block */
    for ( j=0; j<16; j++ ) {
        if ( j < length ) {
            pad[j] = lastb[j];
        } else if ( j == length ) {
            pad[j] = 0x80;
        } else {
            pad[j] = 0x00;
        }
    }
}

/*! *********************************************************************************
* \brief  This function Xors 2 blocks of 128 bits and copies the result to a set destination
*
* \param [in]    a        Pointer to the first block to XOR
*
* \param [in]    b        Pointer to the second block to XOR.
*
* \param [out]   out      Destination pointer
*
* \remarks   This is public open source code! Terms of use must be checked before use!
*
********************************************************************************** */
static void SecLib_Xor128(uint8_t *a,
                          uint8_t *b,
                          uint8_t *out)
{
    uint32_t i;

    for (i=0;i<16; i++)
    {
      out[i] = a[i] ^ b[i];
    }
}


/*! *********************************************************************************
* \brief  This function initializes the SHA1 context data
*
* \param [in]    context        Pointer to the SHA1 context data
*
********************************************************************************** */
void SHA1_Init(sha1Context_t * context)
{
    context->bytes = 0;
    context->totalBytes = 0;
#if FSL_FEATURE_SOC_MMCAU_COUNT
    (void)mmcau_sha1_initialize_output(context->hash);
#else
    sw_sha1_initialize_output(context->hash);
#endif
}

/*! *********************************************************************************
* \brief  This function performs SHA1 on multiple bytes, and updates the context data
*
* \param [in]    pData      Pointer to the input data
* \param [in]    numBytes   Number of bytes to hash
* \param [in]    context        Pointer to the SHA1 context data
*
********************************************************************************** */
void SHA1_HashUpdate(sha1Context_t* context, uint8_t* pData, uint32_t numBytes)
{
    uint16_t blocks;

    /* update total byte count */
    context->totalBytes += numBytes;
    /* Check if we have at least 1 SHA1 block */
    if( context->bytes + numBytes < SHA1_BLOCK_SIZE )
    {
        /* store bytes for later processing */
        FLib_MemCpy(&context->buffer[context->bytes], pData, numBytes);
        context->bytes += numBytes;
    }
    else
    {
        /* Check for bytes leftover from previous update */
        if( context->bytes )
        {
            uint8_t copyBytes = SHA1_BLOCK_SIZE - context->bytes;
            
            FLib_MemCpy(&context->buffer[context->bytes], pData, copyBytes);
            SHA1_hash_n(context->buffer, 1, context->hash);
            pData += copyBytes;
            numBytes -= copyBytes;
            context->bytes = 0;
        }
        /* Hash 64 bytes blocks */
        blocks = numBytes/SHA1_BLOCK_SIZE;
        SHA1_hash_n(pData, blocks, context->hash);
        numBytes -= blocks*SHA1_BLOCK_SIZE;
        pData += blocks*SHA1_BLOCK_SIZE;
        /* Check for remaining bytes */
        if( numBytes )
        {
            context->bytes = numBytes;
            FLib_MemCpy(context->buffer, pData, numBytes);
        }
    }
}

/*! *********************************************************************************
* \brief  This function performs SHA1 on the last bytes of data, and updates the context data.
*         The final hash value is stored on the context data.
*
* \param [in]    pData      Pointer to the input data
* \param [in]    numBytes   Number of bytes to hash
* \param [in]            Pointer to the SHA1 context data
*
********************************************************************************** */
void SHA1_HashFinish(sha1Context_t* context, uint8_t* pData, uint32_t numBytes)
{
    uint32_t i, temp;

    /* perform final hash update */
    SHA1_HashUpdate(context, pData, numBytes);
    /* update remaining bytes */
    numBytes = context->bytes;
    /* Add 1 bit (a 0x80 byte) after the message to begin padding */
    context->buffer[numBytes++] = 0x80;
    /* Chack for space to fit an 8 byte length field plus the 0x80 */
    if( context->bytes >= 56 )
    {
        /* Fill the rest of the chunk with zeros */
        FLib_MemSet(&context->buffer[numBytes], 0, SHA1_BLOCK_SIZE - numBytes);
        SHA1_hash_n(context->buffer, 1, context->hash);
        numBytes = 0;
    }
    /* Fill the rest of the chunk with zeros */
    FLib_MemSet(&context->buffer[numBytes], 0, SHA1_BLOCK_SIZE - numBytes);
    /* Append the total length of the message, in bits (bytes << 3) */
    context->totalBytes <<= 3;
    FLib_MemCpyReverseOrder(&context->buffer[60], &context->totalBytes, sizeof(uint32_t));
    SHA1_hash_n(context->buffer, 1, context->hash);
    /* Convert to Big Endian */
    for(i=0; i<SHA1_HASH_SIZE/sizeof(uint32_t); i++)
    {
        temp = context->hash[i];
        FLib_MemCpyReverseOrder(&context->hash[i], &temp, sizeof(uint32_t));
    }
}

/*! *********************************************************************************
* \brief  This function performs all SHA1 steps on multiple bytes: initialize, 
*         update, finish, and update context data.
*         The final hash value is stored on the context data.
*
* \param [in]    pData      Pointer to the input data
* \param [in]    numBytes   Number of bytes to hash
* \param [in]    context        Pointer to the SHA1 context data
*
********************************************************************************** */
void SHA1_Hash(sha1Context_t* context, uint8_t* pData, uint32_t numBytes)
{
    SHA1_Init(context);
    SHA1_HashFinish(context, pData, numBytes);
}

/*! *********************************************************************************
* \brief  This function initializes the SHA256 context data
*
* \param [in]    context        Pointer to the SHA256 context data
*
********************************************************************************** */
void SHA256_Init(sha256Context_t * context)
{
    context->bytes = 0;
    context->totalBytes = 0;
#if FSL_FEATURE_SOC_MMCAU_COUNT
    (void)mmcau_sha256_initialize_output(context->hash);
#else
    sw_sha256_initialize_output(context->hash);
#endif
}

/*! *********************************************************************************
* \brief  This function performs SHA256 on multiple bytes, and updates the context data
*
* \param [in]    pData      Pointer to the input data
* \param [in]    numBytes   Number of bytes to hash
* \param [in]    context        Pointer to the SHA256 context data
*
********************************************************************************** */
void SHA256_HashUpdate(sha256Context_t* context, uint8_t* pData, uint32_t numBytes)
{
    uint16_t blocks;

    /* update total byte count */
    context->totalBytes += numBytes;
    /* Check if we have at least 1 SHA256 block */
    if( context->bytes + numBytes < SHA256_BLOCK_SIZE )
    {
        /* store bytes for later processing */
        FLib_MemCpy(&context->buffer[context->bytes], pData, numBytes);
        context->bytes += numBytes;
    }
    else
    {
        /* Check for bytes leftover from previous update */
        if( context->bytes )
        {
            uint8_t copyBytes = SHA256_BLOCK_SIZE - context->bytes;
            
            FLib_MemCpy(&context->buffer[context->bytes], pData, copyBytes);
            SHA256_hash_n(context->buffer, 1, context->hash);
            pData += copyBytes;
            numBytes -= copyBytes;
            context->bytes = 0;
        }
        /* Hash 64 bytes blocks */
        blocks = numBytes/SHA256_BLOCK_SIZE;
        SHA256_hash_n(pData, blocks, context->hash);
        numBytes -= blocks*SHA256_BLOCK_SIZE;
        pData += blocks*SHA256_BLOCK_SIZE;
        /* Check for remaining bytes */
        if( numBytes )
        {
            context->bytes = numBytes;
            FLib_MemCpy(context->buffer, pData, numBytes);
        }
    }
}

/*! *********************************************************************************
* \brief  This function performs SHA256 on the last bytes of data, and updates the context data.
*         The final hash value is stored on the context data.
*
* \param [in]    pData      Pointer to the input data
* \param [in]    numBytes   Number of bytes to hash
* \param [in]    context        Pointer to the SHA256 context data
*
********************************************************************************** */
void SHA256_HashFinish(sha256Context_t* context, uint8_t* pData, uint32_t numBytes)
{
    uint32_t i, temp;

    SHA256_HashUpdate(context, pData, numBytes);
    /* update remaining bytes */
    numBytes = context->bytes;
    /* Add 1 bit (a 0x80 byte) after the message to begin padding */
    context->buffer[numBytes++] = 0x80;
    /* Chack for space to fit an 8 byte length field plus the 0x80 */
    if( context->bytes >= 56 )
    {
        /* Fill the rest of the chunk with zeros */
        FLib_MemSet(&context->buffer[numBytes], 0, SHA256_BLOCK_SIZE - numBytes);
        SHA256_hash_n(context->buffer, 1, context->hash);
        numBytes = 0;
    }
    /* Fill the rest of the chunk with zeros */
    FLib_MemSet(&context->buffer[numBytes], 0, SHA256_BLOCK_SIZE - numBytes);
    /* Append the total length of the message(Big Endian), in bits (bytes << 3) */
    context->totalBytes <<= 3;
    FLib_MemCpyReverseOrder(&context->buffer[60], &context->totalBytes, sizeof(uint32_t));
    SHA256_hash_n(context->buffer, 1, context->hash);
    /* Convert to Big Endian */
    for(i=0; i<SHA256_HASH_SIZE/sizeof(uint32_t); i++)
    {
        temp = context->hash[i];
        FLib_MemCpyReverseOrder(&context->hash[i], &temp, sizeof(uint32_t));
    }
}

/*! *********************************************************************************
* \brief  This function performs all SHA256 steps on multiple bytes: initialize, 
*         update, finish, and update context data.
*         The final hash value is stored on the context data.
*
* \param [in]    pData      Pointer to the input data
* \param [in]    numBytes   Number of bytes to hash
* \param [in]            Pointer to the SHA256 context data
*
********************************************************************************** */
void SHA256_Hash(sha256Context_t* context, uint8_t* pData, uint32_t numBytes)
{
    SHA256_Init(context);
    SHA256_HashFinish(context, pData, numBytes);
}

/*! *********************************************************************************
* \brief  This function performs the initialization of the HMAC context data, and 
*         performs the initial hash.
*
* \param [in]    context        Pointer to the HMAC context data
* \param [in]    pKey       Pointer to the key
* \param [in]    keyLen     Length of the key
*
********************************************************************************** */
void HMAC_SHA256_Init(HMAC_SHA256_context_t* context, uint8_t* pKey, uint32_t keyLen) 
{
    uint8_t i;

    if( keyLen > SHA256_BLOCK_SIZE )    
    {
        SHA256_Hash(&context->shaCtx, pKey, keyLen);
        pKey = (uint8_t*)context->shaCtx.hash;
        keyLen = SHA256_HASH_SIZE;
    }

    /* Create i_pad */
    for(i=0; i<keyLen; i++)
    {
        context->pad[i] = pKey[i] ^ gHmacIpad_c;
    }

    for(i=keyLen; i<SHA256_BLOCK_SIZE; i++)
    {
        context->pad[i] = gHmacIpad_c;
    }
    /* start hashing of the i_key_pad */
    SHA256_Init(&context->shaCtx);
    SHA256_HashUpdate(&context->shaCtx, context->pad, SHA256_BLOCK_SIZE);

    /* create o_pad by xor-ing pad[i] with 0x36 ^ 0x5C: */
    for(i=0; i<SHA256_BLOCK_SIZE; i++)
    {
        context->pad[i] ^= (gHmacIpad_c^gHmacOpad_c);
    }
}

/*! *********************************************************************************
* \brief  This function performs HMAC update on the input message.
*         The intermediar hash value is stored on the context data.
*
* \param [in]    context        Pointer to the HMAC context data
* \param [in]    pMsg       Pointer to the input data
* \param [in]    msgLen     Length of the message
*
********************************************************************************** */
void HMAC_SHA256_Update(HMAC_SHA256_context_t* context, uint8_t* pData, uint32_t numBytes)
{
    SHA256_HashUpdate(&context->shaCtx, pData, numBytes);
}

/*! *********************************************************************************
* \brief  This function performs the final step of the HMAC
*         The final hash value is stored on the context data.
*
* \param [in]    context        Pointer to the HMAC context data
*
********************************************************************************** */
void HMAC_SHA256_Finish(HMAC_SHA256_context_t* context) 
{
    uint8_t hash1[SHA256_HASH_SIZE];

    /* finalize the hash of the i_key_pad and message */
    SHA256_HashFinish(&context->shaCtx, NULL, 0);
    FLib_MemCpy(hash1, context->shaCtx.hash, SHA256_HASH_SIZE);
    /* perform hash of the o_key_pas and hash1 */
    SHA256_Init(&context->shaCtx);
    SHA256_HashUpdate(&context->shaCtx, context->pad, SHA256_BLOCK_SIZE);
    SHA256_HashFinish(&context->shaCtx, hash1, SHA256_HASH_SIZE);
}

/*! *********************************************************************************
* \brief  This function performs all HMAC steps on multiple bytes: initialize, 
*         update, finish, and update context data.
*         The final hash value is stored on the context data.
*
* \param [in]    context        Pointer to the HMAC context data
* \param [in]    pKey       Pointer to the key
* \param [in]    keyLen     Length of the key
* \param [in]    pMsg       Pointer to the input data
* \param [in]    msgLen     Length of the message
*
********************************************************************************** */
void HMAC_SHA256(HMAC_SHA256_context_t* context, uint8_t* pKey, uint32_t keyLen, uint8_t* pMsg, uint32_t msgLen)
{
    HMAC_SHA256_Init(context, pKey, keyLen);
    HMAC_SHA256_Update(context, pMsg, msgLen);
    HMAC_SHA256_Finish(context);
}

#if mDbgRevertKeys_d
static ecdhPublicKey_t mReversedPublicKey;
static ecdhPrivateKey_t mReversedPrivateKey;
#endif /* mDbgRevertKeys_d */

secResultType_t ECDH_P256_GenerateKeys
(
    ecdhPublicKey_t*    pOutPublicKey,
	ecdhPrivateKey_t*   pOutPrivateKey
)
{
    secResultType_t result;
    
    
    void* pMultiplicationBuffer = MEM_BufferAlloc(gEcP256_MultiplicationBufferSize_c);
    if (NULL == pMultiplicationBuffer)
    {
        result = gSecAllocError_c;
    }
    else
    {
#if mDbgRevertKeys_d
        if (gEcdhSuccess_c != Ecdh_GenerateNewKeys(&mReversedPublicKey, &mReversedPrivateKey, pMultiplicationBuffer))
#else /* !mDbgRevertKeys_d */
        if (gEcdhSuccess_c != Ecdh_GenerateNewKeys(pOutPublicKey, pOutPrivateKey, pMultiplicationBuffer))
#endif /* mDbgRevertKeys_d */
        {
            result = gSecError_c;
        }
        else
        {
            result = gSecSuccess_c;
#if mDbgRevertKeys_d
            FLib_MemCpyReverseOrder
            (
                pOutPublicKey->components_8bit.x,
                mReversedPublicKey.components_8bit.x,
                32
            );
            FLib_MemCpyReverseOrder
            (
                pOutPublicKey->components_8bit.y,
                mReversedPublicKey.components_8bit.y,
                32
            );
            FLib_MemCpyReverseOrder
            (
                pOutPrivateKey->raw_8bit,
                mReversedPrivateKey.raw_8bit,
                32
            );
#endif /* mDbgRevertKeys_d */
        }
        MEM_BufferFree(pMultiplicationBuffer);
    }
    
    return result;
}

#if mDbgRevertKeys_d
static ecdhDhKey_t mReversedEcdhKey;
#endif /* mDbgRevertKeys_d */

secResultType_t ECDH_P256_ComputeDhKey
(
    ecdhPrivateKey_t*   pPrivateKey,
    ecdhPublicKey_t*    pPeerPublicKey,
    ecdhDhKey_t*        pOutDhKey
)
{
    secResultType_t result;
    
    void* pMultiplicationBuffer = MEM_BufferAlloc(gEcP256_MultiplicationBufferSize_c);
    if (NULL == pMultiplicationBuffer)
    {
        result = gSecAllocError_c;
    }
    else
    {
#if mDbgRevertKeys_d
        FLib_MemCpyReverseOrder
        (            
            mReversedPublicKey.components_8bit.x,
            pPeerPublicKey->components_8bit.x,
            32
        );
        FLib_MemCpyReverseOrder
        (            
            mReversedPublicKey.components_8bit.y,
            pPeerPublicKey->components_8bit.y,
            32
        );
        FLib_MemCpyReverseOrder
        (
            mReversedPrivateKey.raw_8bit,
            pPrivateKey->raw_8bit,
            32
        );
#endif /* mDbgRevertKeys_d */
        
#if mDbgRevertKeys_d        
        if (gEcdhSuccess_c != Ecdh_ComputeDhKey(&mReversedPrivateKey, &mReversedPublicKey, &mReversedEcdhKey, pMultiplicationBuffer))
#else /* !mDbgRevertKeys_d */
        if (gEcdhSuccess_c != Ecdh_ComputeDhKey(pPrivateKey, pPeerPublicKey, pOutDhKey, pMultiplicationBuffer))    
#endif /* mDbgRevertKeys_d */
        {
            result = gSecError_c;
        }
        else
        {            
            result = gSecSuccess_c;
#if mDbgRevertKeys_d
            FLib_MemCpyReverseOrder
            (
                pOutDhKey->components_8bit.x,
                mReversedEcdhKey.components_8bit.x,
                32
            );
            FLib_MemCpyReverseOrder
            (
                pOutDhKey->components_8bit.y,
                mReversedEcdhKey.components_8bit.y,
                32
            );
#endif /* mDbgRevertKeys_d */
        }
        MEM_BufferFree(pMultiplicationBuffer);
    }
    
    return result;
}

/*! *********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
* \brief  This function performs SHA1 on multiple blocks
*
* \param [in]    pData      Pointer to the input data
* \param [in]    nBlk       Number of SHA1 blocks to hash
* \param [in]    context        Pointer to the SHA1 context data
*
********************************************************************************** */
static void SHA1_hash_n(uint8_t* pData, uint32_t nBlk, uint32_t* pHash)
{
    if( nBlk )
    {
        SecLib_DisallowToSleep();
#if FSL_FEATURE_SOC_MMCAU_COUNT
        mmcau_sha1_hash_n(pData, nBlk, pHash);
#else
        sw_sha1_hash_n(pData, nBlk, pHash);
#endif
        SecLib_AllowToSleep();
    }
}

/*! *********************************************************************************
* \brief  This function performs SHA256 on multiple blocks
*
* \param [in]    pData      Pointer to the input data
* \param [in]    nBlk       Number of SHA256 blocks to hash
* \param [in]    context        Pointer to the SHA256 context data
*
********************************************************************************** */
static void SHA256_hash_n(uint8_t* pData, uint32_t nBlk, uint32_t* pHash)
{
    if( nBlk )
    {
        SecLib_DisallowToSleep();
#if FSL_FEATURE_SOC_MMCAU_COUNT
        mmcau_sha256_hash_n(pData, nBlk, pHash);
#else
        sw_sha256_hash_n(pData, nBlk, pHash);
#endif
        SecLib_AllowToSleep();
    }
}
