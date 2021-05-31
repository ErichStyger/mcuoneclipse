/*
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "fsl_ftfx_flexnvm.h"

#if FSL_FEATURE_FLASH_HAS_FLEX_NVM

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*! @brief Convert address for Flexnvm dflash.*/
static status_t flexnvm_convert_start_address(flexnvm_config_t *config, uint32_t start);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

status_t FLEXNVM_Init(flexnvm_config_t *config)
{
    status_t returnCode;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    config->ftfxConfig.flashDesc.type  = (uint8_t)kFTFx_MemTypeFlexnvm;
    config->ftfxConfig.flashDesc.index = 0U;

    /* Set Flexnvm memory operation parameters */
    config->ftfxConfig.opsConfig.addrAligment.blockWriteUnitSize = FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_WRITE_UNIT_SIZE;
    config->ftfxConfig.opsConfig.addrAligment.sectorCmd   = FSL_FEATURE_FLASH_FLEX_NVM_SECTOR_CMD_ADDRESS_ALIGMENT;
    config->ftfxConfig.opsConfig.addrAligment.sectionCmd  = FSL_FEATURE_FLASH_FLEX_NVM_SECTION_CMD_ADDRESS_ALIGMENT;
    config->ftfxConfig.opsConfig.addrAligment.resourceCmd = FSL_FEATURE_FLASH_FLEX_NVM_RESOURCE_CMD_ADDRESS_ALIGMENT;
    config->ftfxConfig.opsConfig.addrAligment.checkCmd    = FSL_FEATURE_FLASH_FLEX_NVM_CHECK_CMD_ADDRESS_ALIGMENT;

    /* Set Flexnvm memory properties */
    config->ftfxConfig.flashDesc.blockBase  = FSL_FEATURE_FLASH_FLEX_NVM_START_ADDRESS;
#if defined (FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS) && FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS
    config->ftfxConfig.flashDesc.aliasBlockBase = FSL_FEATURE_FLASH_FLEX_NVM_ALIAS_START_ADDRESS;
#endif
    config->ftfxConfig.flashDesc.sectorSize = FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_SECTOR_SIZE;
    config->ftfxConfig.flashDesc.blockCount = FSL_FEATURE_FLASH_FLEX_NVM_BLOCK_COUNT;

    /* Init FTFx Kernel */
    returnCode = FTFx_API_Init(&config->ftfxConfig);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    returnCode = FTFx_API_UpdateFlexnvmPartitionStatus(&config->ftfxConfig);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    return kStatus_FTFx_Success;
}

status_t FLEXNVM_DflashErase(flexnvm_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key)
{
    status_t returnCode;
    returnCode = flexnvm_convert_start_address(config, start);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    return FTFx_CMD_Erase(&config->ftfxConfig, start, lengthInBytes, key);
}

status_t FLEXNVM_EraseAll(flexnvm_config_t *config, uint32_t key)
{
    return FTFx_CMD_EraseAll(&config->ftfxConfig, key);
}

#if defined(FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD) && FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_UNSECURE_CMD
status_t FLEXNVM_EraseAllUnsecure(flexnvm_config_t *config, uint32_t key)
{
    return FTFx_CMD_EraseAllUnsecure(&config->ftfxConfig, key);
}
#endif

status_t FLEXNVM_DflashProgram(flexnvm_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;
    returnCode = flexnvm_convert_start_address(config, start);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    return FTFx_CMD_Program(&config->ftfxConfig, start, src, lengthInBytes);
}

#if defined(FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD) && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD
status_t FLEXNVM_DflashProgramSection(flexnvm_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;
    returnCode = flexnvm_convert_start_address(config, start);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    return FTFx_CMD_ProgramSection(&config->ftfxConfig, start, src, lengthInBytes);
}
#endif

status_t FLEXNVM_ProgramPartition(flexnvm_config_t *config,
                                  ftfx_partition_flexram_load_opt_t option,
                                  uint32_t eepromDataSizeCode,
                                  uint32_t flexnvmPartitionCode)
{
    return FTFx_CMD_ProgramPartition(&config->ftfxConfig, option, eepromDataSizeCode, flexnvmPartitionCode);
}

#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
status_t FLEXNVM_ReadResource(
    flexnvm_config_t *config, uint32_t start, uint8_t *dst, uint32_t lengthInBytes, ftfx_read_resource_opt_t option)
{
    return FTFx_CMD_ReadResource(&config->ftfxConfig, start, dst, lengthInBytes, option);
}
#endif

status_t FLEXNVM_DflashVerifyErase(flexnvm_config_t *config,
                                   uint32_t start,
                                   uint32_t lengthInBytes,
                                   ftfx_margin_value_t margin)
{
    status_t returnCode;
    returnCode = flexnvm_convert_start_address(config, start);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    return FTFx_CMD_VerifyErase(&config->ftfxConfig, start, lengthInBytes, margin);
}

status_t FLEXNVM_VerifyEraseAll(flexnvm_config_t *config, ftfx_margin_value_t margin)
{
    return FTFx_CMD_VerifyEraseAll(&config->ftfxConfig, margin);
}

status_t FLEXNVM_DflashVerifyProgram(flexnvm_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     ftfx_margin_value_t margin,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData)
{
    status_t returnCode;
    returnCode = flexnvm_convert_start_address(config, start);
    if (returnCode != kStatus_FTFx_Success)
    {
        return returnCode;
    }

    return FTFx_CMD_VerifyProgram(&config->ftfxConfig, start, lengthInBytes, expectedData, margin, failedAddress,
                                  failedData);
}

status_t FLEXNVM_GetSecurityState(flexnvm_config_t *config, ftfx_security_state_t *state)
{
    return FTFx_REG_GetSecurityState(&config->ftfxConfig, state);
}

status_t FLEXNVM_SecurityBypass(flexnvm_config_t *config, const uint8_t *backdoorKey)
{
    return FTFx_CMD_SecurityBypass(&config->ftfxConfig, backdoorKey);
}

#if defined(FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD) && FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
status_t FLEXNVM_SetFlexramFunction(flexnvm_config_t *config, ftfx_flexram_func_opt_t option)
{
    return FTFx_CMD_SetFlexramFunction(&config->ftfxConfig, option);
}
#endif

status_t FLEXNVM_EepromWrite(flexnvm_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes)
{
    status_t returnCode;
    bool needSwitchFlexRamMode = false;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* Validates the range of the given address */
    if ((start < config->ftfxConfig.flexramBlockBase) ||
        ((start + lengthInBytes) > (config->ftfxConfig.flexramBlockBase + config->ftfxConfig.eepromTotalSize)))
    {
        return kStatus_FTFx_AddressError;
    }

    returnCode = kStatus_FTFx_Success;

    /* Switch function of FlexRAM if needed */
    if (0U == (FTFx->FCNFG & FTFx_FCNFG_EEERDY_MASK))
    {
        needSwitchFlexRamMode = true;

        returnCode = FTFx_CMD_SetFlexramFunction(&config->ftfxConfig, kFTFx_FlexramFuncOptAvailableForEeprom);
        if (returnCode != kStatus_FTFx_Success)
        {
            return kStatus_FTFx_SetFlexramAsEepromError;
        }
    }

    /* Write data to FlexRAM when it is used as EEPROM emulator */
    while (lengthInBytes > 0U)
    {
        if ((0U == (start & 0x3U)) && (0U == ((uint32_t)src & 0x3U)) && (lengthInBytes >= 4U))
        {
            *(uint32_t *)start = *(uint32_t *)(uint32_t)src;
            start += 4U;
            src = &src[4];
            lengthInBytes -= 4U;
        }
        else if ((0U == (start & 0x1U)) && (0U == ((uint32_t)src & 0x1U)) && (lengthInBytes >= 2U))
        {
            *(uint16_t *)start = *(uint16_t *)(uint32_t)src;
            start += 2U;
            src = &src[2];
            lengthInBytes -= 2U;
        }
        else
        {
            *(uint8_t *)start = *src;
            start += 1U;
            src = &src[1];
            lengthInBytes -= 1U;
        }
        /* Wait till EEERDY bit is set */
        while (0U == (FTFx->FCNFG & FTFx_FCNFG_EEERDY_MASK))
        {
        }

        /* Check for protection violation error */
        if (0U != (FTFx->FSTAT & FTFx_FSTAT_FPVIOL_MASK))
        {
            return kStatus_FTFx_ProtectionViolation;
        }
    }

    /* Switch function of FlexRAM if needed */
    if (needSwitchFlexRamMode)
    {
        returnCode = FTFx_CMD_SetFlexramFunction(&config->ftfxConfig, kFTFx_FlexramFuncOptAvailableAsRam);
        if (returnCode != kStatus_FTFx_Success)
        {
            return kStatus_FTFx_RecoverFlexramAsRamError;
        }
    }

    return returnCode;
}

status_t FLEXNVM_DflashSetProtection(flexnvm_config_t *config, uint8_t protectStatus)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    if ((config->ftfxConfig.flashDesc.totalSize == 0U) || (config->ftfxConfig.flashDesc.totalSize == 0xFFFFFFFFU))
    {
        return kStatus_FTFx_CommandNotSupported;
    }

    FTFx->FDPROT = protectStatus;

    if (FTFx->FDPROT != protectStatus)
    {
        return kStatus_FTFx_CommandFailure;
    }

    return kStatus_FTFx_Success;
}

status_t FLEXNVM_DflashGetProtection(flexnvm_config_t *config, uint8_t *protectStatus)
{
    if ((config == NULL) || (protectStatus == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    if ((config->ftfxConfig.flashDesc.totalSize == 0U) || (config->ftfxConfig.flashDesc.totalSize == 0xFFFFFFFFU))
    {
        return kStatus_FTFx_CommandNotSupported;
    }

    *protectStatus = FTFx->FDPROT;

    return kStatus_FTFx_Success;
}

status_t FLEXNVM_EepromSetProtection(flexnvm_config_t *config, uint8_t protectStatus)
{
    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    if ((config->ftfxConfig.eepromTotalSize == 0U) || (config->ftfxConfig.eepromTotalSize == 0xFFFFU))
    {
        return kStatus_FTFx_CommandNotSupported;
    }

    FTFx->FEPROT = protectStatus;

    if (FTFx->FEPROT != protectStatus)
    {
        return kStatus_FTFx_CommandFailure;
    }

    return kStatus_FTFx_Success;
}

status_t FLEXNVM_EepromGetProtection(flexnvm_config_t *config, uint8_t *protectStatus)
{
    if ((config == NULL) || (protectStatus == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    if ((config->ftfxConfig.eepromTotalSize == 0U) || (config->ftfxConfig.eepromTotalSize == 0xFFFFU))
    {
        return kStatus_FTFx_CommandNotSupported;
    }

    *protectStatus = FTFx->FEPROT;

    return kStatus_FTFx_Success;
}

status_t FLEXNVM_GetProperty(flexnvm_config_t *config, flexnvm_property_tag_t whichProperty, uint32_t *value)
{
    if ((config == NULL) || (value == NULL))
    {
        return kStatus_FTFx_InvalidArgument;
    }

    if (whichProperty == kFLEXNVM_PropertyDflashSectorSize)
    {
        *value = config->ftfxConfig.flashDesc.sectorSize;
    }
    else if (whichProperty == kFLEXNVM_PropertyDflashTotalSize)
    {
        *value = config->ftfxConfig.flashDesc.totalSize;
    }
    else if (whichProperty == kFLEXNVM_PropertyDflashBlockSize)
    {
        *value = config->ftfxConfig.flashDesc.totalSize / config->ftfxConfig.flashDesc.blockCount;
    }
    else if (whichProperty == kFLEXNVM_PropertyDflashBlockCount)
    {
        *value = config->ftfxConfig.flashDesc.blockCount;
    }
    else if (whichProperty == kFLEXNVM_PropertyDflashBlockBaseAddr)
    {
        *value = config->ftfxConfig.flashDesc.blockBase;
    }
#if defined (FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS) && FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS
    else if (whichProperty == kFLEXNVM_PropertyAliasDflashBlockBaseAddr)
    {
        *value = config->ftfxConfig.flashDesc.aliasBlockBase;
    }
#endif
    else if (whichProperty == kFLEXNVM_PropertyFlexRamBlockBaseAddr)
    {
        *value = config->ftfxConfig.flexramBlockBase;
    }
    else if (whichProperty == kFLEXNVM_PropertyFlexRamTotalSize)
    {
        *value = config->ftfxConfig.flexramTotalSize;
    }
    else if (whichProperty == kFLEXNVM_PropertyEepromTotalSize)
    {
        *value = config->ftfxConfig.eepromTotalSize;
    }
    else /* catch inputs that are not recognized */
    {
        return kStatus_FTFx_UnknownProperty;
    }

    return kStatus_FTFx_Success;
}

static status_t flexnvm_convert_start_address(flexnvm_config_t *config, uint32_t start)
{
    status_t status = kStatus_FTFx_AddressError;

    if (config == NULL)
    {
        return kStatus_FTFx_InvalidArgument;
    }

    /* From Spec: When required by the command, address bit 23 selects between program flash memory
     * (=0) and data flash memory (=1).*/
    if (start >= config->ftfxConfig.flashDesc.blockBase)
    {
        config->ftfxConfig.opsConfig.convertedAddress = start - config->ftfxConfig.flashDesc.blockBase + 0x800000U;
        status = kStatus_FTFx_Success;
    }
#if defined (FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS) && FSL_FEATURE_FLASH_HAS_FLEX_NVM_ALIAS
    else if (start >= config->ftfxConfig.flashDesc.aliasBlockBase)
    {
        config->ftfxConfig.opsConfig.convertedAddress = start - config->ftfxConfig.flashDesc.aliasBlockBase + 0x800000U;
        status = kStatus_FTFx_Success;
    }
    else
    {
         status = kStatus_FTFx_Success;
    }
#endif

    return status;
}

#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */
