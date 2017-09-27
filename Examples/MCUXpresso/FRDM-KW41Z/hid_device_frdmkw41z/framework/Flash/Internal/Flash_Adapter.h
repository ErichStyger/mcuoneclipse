/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file Flash_Adapter.h
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

#ifndef __FLASH_ADAPTER_H__
#define __FLASH_ADAPTER_H__

/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "EmbeddedTypes.h"
#include "fsl_flash.h"


/*! *********************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
********************************************************************************** */
/*
 * Name: gNvDisableIntCmdSeq_c
 * Description: this macro is used to enable/disable interrupts when the
 *              FTFL controller executes a command sequence. This macro
 *              has to be set according to NVM configuration. Therefore,
 *              if the FLASH region used by the NVM is placed in the same
 *              program block as the ISR's executable code, the interrupts 
 *              MUST be disabled (because no code pre-fetching can be performed
 *              while FTFL controller executes a command sequence, i.e. 
 *              program/erase). If the interrupts are not disabled, the 
 *              system will assert a hard fault when the flash controller 
 *              executes a command sequnce and an IRQ is about to be handled.
 *              If the NVM region is placed in a different program block than
 *              the ISR's code, this macro shall be set to FALSE (recommended).
 */      
#ifndef gNvDisableIntCmdSeq_c
#define gNvDisableIntCmdSeq_c           (1)
#endif

/* size of array to copy__Launch_Command function to.*/
/* It should be at least equal to actual size of __Launch_Command func */
/* User can change this value based on RAM size availability and actual size of __Launch_Command function */
#define LAUNCH_CMD_SIZE         64
#define PGM_SIZE_BYTE           FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE
#define P_BLOCK_NUM             FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT
#define P_SECTOR_SIZE           FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE
/* Data Flash block information */
#define FLEXNVM_BASE            FSL_FEATURE_FLASH_FLEX_NVM_START_ADDRESS
#define FLEXNVM_SECTOR_SIZE     FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_SECTOR_SIZE
#define FLEXNVM_BLOCK_SIZE      FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_SIZE
#define FLEXNVM_BLOCK_NUM       FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_COUNT
/* Other defines */
#define DEBUGENABLE             0x00
#define FTFx_REG_BASE           0x40020000
#define P_FLASH_BASE            0x00000000

/* Flex Ram block information */
#define EERAM_BASE              FSL_FEATURE_FLASH_FLEX_RAM_START_ADDRESS
#define EERAM_SIZE              FSL_FEATURE_FLASH_FLEX_RAM_SIZE

#define READ_NORMAL_MARGIN        0x00
#define READ_USER_MARGIN          0x01
#define READ_FACTORY_MARGIN       0x02

#define NV_FlashRead(pSrc, pDest, size) FLib_MemCpy((void*)(pDest), (void*)(pSrc), size);

/*! *********************************************************************************
*************************************************************************************
* Public type definitions
*************************************************************************************
********************************************************************************** */
typedef PACKED_STRUCT hardwareParameters_tag
{
    uint8_t  identificationWord[10];   /* valid data present */
    uint8_t  reserved[32];             /* for backward compatibillity */
    uint8_t  ieee_802_15_4_address[8]; /* IEEE 802.15.4 MAC address */
    uint8_t  bluetooth_address[6];     /* Bluetooth address */
    uint32_t xtalTrim;                 /* KW4x only */
    uint32_t edCalibrationOffset;      /* KW01 ED offset */
    uint32_t pllFStepOffset;           /* KW01 fine tune pll */
    uint32_t gInternalStorageAddr;     /* The start address of the internal storage used for OTA update.
                                          A value of 0xFFFFFFFF means that the External storage is used.
                                          Warning: The offset to this field in respect to the start address of the structure 
                                          must not be changed.*/
    /* For forward compatibility additional fields may be added here 
       Existing data in flash will not be compatible after modifying the hardwareParameters_t typedef*/
    uint16_t hardwareParamsCrc;        /* crc for data between start of reserved area and start of hardwareParamsCrc field (not included). */ 
}hardwareParameters_t;

/*! *********************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
extern flash_config_t gFlashConfig;
extern hardwareParameters_t gHardwareParameters;

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */
void NV_Init(void);

uint32_t NV_FlashProgram(         uint32_t dest,
                                  uint32_t size,
                                  uint8_t* pData);

uint32_t NV_FlashProgramUnaligned(uint32_t dest,
                                  uint32_t size,
                                  uint8_t* pData);

uint32_t NV_FlashEraseSector(     uint32_t dest,
                                  uint32_t size);
uint32_t NV_FlashVerifyErase ( uint32_t start, uint32_t lengthInBytes, flash_margin_value_t margin);

uint32_t NV_ReadHWParameters(hardwareParameters_t *pHwParams);

uint32_t NV_WriteHWParameters(hardwareParameters_t *pHwParams);

#endif /* __FLASH_ADAPTER_H__ */