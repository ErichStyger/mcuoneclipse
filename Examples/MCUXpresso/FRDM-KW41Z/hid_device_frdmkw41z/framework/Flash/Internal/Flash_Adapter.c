/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Flash_Adapter.c
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
#include "Flash_Adapter.h"
#include "FunctionLib.h"
#include "fsl_os_abstraction.h"

/*****************************************************************************
 *****************************************************************************
 * Private macros
 *****************************************************************************
 *****************************************************************************/
#if (PGM_SIZE_BYTE == 4)
#define mProgBuffSizeInPgmWrUnits_c  16
#elif (PGM_SIZE_BYTE == 8)
#define mProgBuffSizeInPgmWrUnits_c  8
#else
#define mProgBuffSizeInPgmWrUnits_c  4
#endif

/* Generator for CRC calculations. */
#define POLGEN  0x1021              
/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */
static uint32_t NV_FlashProgramAdaptation(uint32_t dest, uint32_t size, uint8_t* pData);
static uint8_t  NV_VerifyCrcOverHWParameters(hardwareParameters_t* pHwParams);
static uint16_t NV_ComputeCrcOverHWParameters(hardwareParameters_t* pHwParams);
/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
extern uint32_t FREESCALE_PROD_DATA_BASE_ADDR[];

/* Hardware parameters */
hardwareParameters_t gHardwareParameters;
flash_config_t gFlashConfig;
static const uint8_t mProdDataIdentifier[10] = {"PROD_DATA:"};
/*****************************************************************************
 *****************************************************************************
 * Private functions
 *****************************************************************************
 *****************************************************************************/
/*! *********************************************************************************
 * \brief  Write alligned data to FLASH
 *
 * \param[in] dest        The address of the Flash location
 * \param[in] size        The number of bytes to be programed
 * \param[in] pData       Pointer to the data to be programmed to Flash
 *
 * \return error code
 *
********************************************************************************** */
static uint32_t NV_FlashProgramAdaptation(uint32_t dest, uint32_t size, uint8_t* pData)
{
  uint32_t status = kStatus_FLASH_Success;
  
  if( ((uint32_t)pData)%sizeof(uint32_t) == 0)
  {
    status = FLASH_Program(&gFlashConfig,dest, (uint32_t*) pData, size);    
    return status;
  }
  if( (size & (PGM_SIZE_BYTE - 0x01U)) != 0 )
  {
    return kStatus_FLASH_AlignmentError;
  }
  {
    uint32_t progBuf[PGM_SIZE_BYTE * mProgBuffSizeInPgmWrUnits_c / 4];
    uint32_t progSize;
    while(size)
    {
      progSize = PGM_SIZE_BYTE * mProgBuffSizeInPgmWrUnits_c;
      if(progSize > size)
      {
        progSize = size;
      }
      FLib_MemCpy (progBuf, pData, progSize);
      status = FLASH_Program(&gFlashConfig,dest, progBuf, progSize);
      if(status != kStatus_FLASH_Success)
      {
        break;
      }
      pData += progSize;
      size -= progSize;
      dest += progSize;
    }  
  }
  return status;
}

/*! *********************************************************************************
 * \brief  Verifies if the CRC field matches computed CRC over stored values 
 * 
 * \param[in] pHwParams  pointer to a structure containing HW parameters
 *
 * \return 1 on success, 0 otherwise
 *
********************************************************************************** */
static uint8_t NV_VerifyCrcOverHWParameters(hardwareParameters_t* pHwParams)
{
    uint8_t status = 0;
    
    if(NV_ComputeCrcOverHWParameters(pHwParams) == pHwParams->hardwareParamsCrc)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

/*! *********************************************************************************
 * \brief  Computes the CRC for the hardware parameters and stores it 
 * 
 * \param[in] pHwParams  pointer to a structure containing HW parameters
 *
 * \return Computed CRC value. 
 *
********************************************************************************** */
static uint16_t NV_ComputeCrcOverHWParameters(hardwareParameters_t* pHwParams)
{  
    uint16_t  computedCRC = 0;
    uint8_t crcA;
    uint8_t byte = 0;
    if(NULL != pHwParams)
    {
        uint8_t *ptr = (uint8_t *)(&pHwParams->reserved);
        uint16_t len = (uint8_t *)(&pHwParams->hardwareParamsCrc) - 
                           (uint8_t *)(&pHwParams->reserved);
        while(len)
        {
            byte = *ptr;
            computedCRC ^= ((uint16_t)byte << 8);
            for(crcA = 8; crcA; crcA--) 
            {
                if(computedCRC & 0x8000) {
                    computedCRC <<= 1;
                    computedCRC ^= POLGEN;
                } 
                else computedCRC <<= 1;
            }  
            --len;
            ++ptr;
        }
    }
    return computedCRC;
}
/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
 * \brief  Initialize the FLASH driver
 *
********************************************************************************** */
void NV_Init(void)
{
  static bool_t nvmInit = 0;
  if(nvmInit == 0)
  {
    FLASH_Init(&gFlashConfig);
    nvmInit = 1;
  }
}

/*! *********************************************************************************
 * \brief  Write alligned data to FLASH
 *
 * \param[in] start                The address of the Flash location
 * \param[in] lengthInBytes        The number of bytes to be programed
 * \param[in] margin      
  * \return error code
 *
********************************************************************************** */
uint32_t NV_FlashVerifyErase ( uint32_t start, uint32_t lengthInBytes, flash_margin_value_t margin)
{
  uint32_t status;
#if gNvDisableIntCmdSeq_c
    OSA_InterruptDisable();
#endif
  status = FLASH_VerifyErase(&gFlashConfig, start, lengthInBytes, margin);
#if gNvDisableIntCmdSeq_c
    OSA_InterruptEnable();
#endif
  return status;
}
/*! *********************************************************************************
 * \brief  Write alligned data to FLASH
 *
 * \param[in] pSSDConfig  Pointer to a flash config structure
 * \param[in] dest        The address of the Flash location
 * \param[in] size        The number of bytes to be programed
 * \param[in] pData       Pointer to the data to be programmed to Flash
 * \param[in] pFlashCommandSequence  Pointer to the Flash RAM function
 *
 * \return error code
 *
********************************************************************************** */
uint32_t NV_FlashProgram (         uint32_t dest,
                                   uint32_t size,
                                   uint8_t* pData)
{
    uint32_t status;
    #if gNvDisableIntCmdSeq_c
        OSA_InterruptDisable();
    #endif
    status = NV_FlashProgramAdaptation(dest, size, pData);
    #if gNvDisableIntCmdSeq_c
        OSA_InterruptEnable();
    #endif
    return status;
}

/*! *********************************************************************************
 * \brief  Write data to FLASH
 * 
 * \param[in] pSSDConfig  Pointer to a flash config structure  
 * \param[in] dest        The address of the Flash location
 * \param[in] size        The number of bytes to be programed
 * \param[in] pData       Pointer to the data to be programmed to Flash
 * \param[in] pFlashCommandSequence  Pointer to the Flash RAM function
 *
 * \return error code
 *
********************************************************************************** */
uint32_t NV_FlashProgramUnaligned(
                                  uint32_t dest,
                                  uint32_t size,
                                  uint8_t* pData)
{
    uint8_t  buffer[PGM_SIZE_BYTE];
    uint16_t bytes = dest & (PGM_SIZE_BYTE-1);
    uint32_t status;

    if( bytes )
    {
        uint16_t unalignedBytes = PGM_SIZE_BYTE - bytes;

        if( unalignedBytes > size )
        {
            unalignedBytes = size;
        }

        FLib_MemCpy(buffer, (void*)(dest - bytes), PGM_SIZE_BYTE);
        FLib_MemCpy(&buffer[bytes], pData, unalignedBytes);
#if gNvDisableIntCmdSeq_c
        OSA_InterruptDisable();
#endif
        status = NV_FlashProgramAdaptation(dest - bytes, PGM_SIZE_BYTE, buffer);
#if gNvDisableIntCmdSeq_c
        OSA_InterruptEnable();
#endif
        if( status != kStatus_FLASH_Success )
        {
            return status;
        }

        dest += PGM_SIZE_BYTE - bytes;
        pData += unalignedBytes;
        size -= unalignedBytes;
    }

    bytes = size & ~(PGM_SIZE_BYTE - 1U);

    if( bytes )
    {
#if gNvDisableIntCmdSeq_c
        OSA_InterruptDisable();
#endif
        status = NV_FlashProgramAdaptation(dest, bytes, pData);
#if gNvDisableIntCmdSeq_c
        OSA_InterruptEnable();
#endif
        if( status != kStatus_FLASH_Success )
        {
            return status;
        }

        dest  += bytes;
        pData += bytes;
        size  -= bytes;
    }
    
    if( size )
    {
        FLib_MemCpy(buffer, (void*)dest, PGM_SIZE_BYTE);
        FLib_MemCpy(buffer, pData, size);
#if gNvDisableIntCmdSeq_c
        OSA_InterruptDisable();
#endif
        status = NV_FlashProgramAdaptation(dest, PGM_SIZE_BYTE, buffer);
#if gNvDisableIntCmdSeq_c
        OSA_InterruptEnable();
#endif
        if( status != kStatus_FLASH_Success )
        {
            return status;
        }
    }
    
    return kStatus_FLASH_Success;
}

/*! *********************************************************************************
 * \brief  Erase to 0xFF one ore more FLASH sectors.
 * 
 * \param[in] pSSDConfig  Pointer to a flash config structure  
 * \param[in] dest        The start address of the first sector to be erased
 * \param[in] size        The amount of flash to be erased (multiple of sector size)
 * \param[in] pFlashCommandSequence  Pointer to the Flash RAM function
 *
 * \return error code
 *
********************************************************************************** */
uint32_t NV_FlashEraseSector(uint32_t dest, uint32_t size)
{
    uint32_t status;
#if gNvDisableIntCmdSeq_c
    OSA_InterruptDisable();
#endif
    status = FLASH_Erase(&gFlashConfig, dest, size, kFLASH_ApiEraseKey);
#if gNvDisableIntCmdSeq_c
    OSA_InterruptEnable();
#endif
    return status;
}

/*! *********************************************************************************
 * \brief  Load the HW parameters from Flash to RAM
 * 
 * \param[in] pHwParams  pointer to a structure where HW parameters will be stored
 *
 * \return error code
 *
********************************************************************************** */
uint32_t NV_ReadHWParameters(hardwareParameters_t *pHwParams)
{
    hardwareParameters_t* pLocalParams = (hardwareParameters_t*)FREESCALE_PROD_DATA_BASE_ADDR;
    uint32_t status = 0;
    if(NULL != pHwParams)
    {
        if(FLib_MemCmp(FREESCALE_PROD_DATA_BASE_ADDR, (void*)mProdDataIdentifier, sizeof(mProdDataIdentifier)) &&
           NV_VerifyCrcOverHWParameters(pLocalParams))
        {
            FLib_MemCpy(pHwParams, FREESCALE_PROD_DATA_BASE_ADDR, sizeof(hardwareParameters_t));
        }
        else
        {
            FLib_MemSet(pHwParams, 0xFF, sizeof(hardwareParameters_t));
            status = 1;
        }
    }
    else
    {
        status = 2;
    }
    return status;
}

/*! *********************************************************************************
 * \brief  Store the HW parameters to Flash 
 * 
 * \param[in] pHwParams  pointer to a structure containing HW parameters
 *
 * \return error code of the Flash erase/write functions
 *
********************************************************************************** */
uint32_t NV_WriteHWParameters(hardwareParameters_t *pHwParams)
{
    uint32_t status = 0;
    NV_Init();
    
    if(!FLib_MemCmp(pHwParams, (void*)FREESCALE_PROD_DATA_BASE_ADDR, sizeof(hardwareParameters_t)))
    {
        pHwParams->hardwareParamsCrc = NV_ComputeCrcOverHWParameters(pHwParams);
        FLib_MemCpy(pHwParams->identificationWord, (void*)mProdDataIdentifier, sizeof(mProdDataIdentifier));
        
        status = NV_FlashEraseSector((uint32_t)FREESCALE_PROD_DATA_BASE_ADDR, FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE);
        if( 0 == status )
        {
            status = NV_FlashProgramUnaligned((uint32_t)FREESCALE_PROD_DATA_BASE_ADDR,
                                              sizeof(hardwareParameters_t),
                                              (uint8_t*)pHwParams);
        }
    }
    return status;
}