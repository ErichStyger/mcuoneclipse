/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader/bootloader.h"
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
#include "fsl_flash.h"
#include "memory/src/flash_memory.h"
#if BL_FEATURE_SUPPORT_DFLASH
#include "memory/src/flexNVM_memory.h"
#endif // BL_FEATURE_SUPPORT_DFLASH
#else
#include "flashiap_wrapper/fsl_flashiap_wrapper.h"
#include "memory/src/flashiap_memory.h"
#endif
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if BL_FEATURE_ENCRYPTION
#include "aes_security.h"
#endif // #if BL_FEATURE_ENCRYPTION

//! @addtogroup context
//! @{

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Function table for flash driver.
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
const flash_driver_interface_t g_flashDriverInterface = {
    {.version = FSL_FLASH_DRIVER_VERSION},
    .flash_init = FLASH_Init,
    .flash_erase_all = FLASH_EraseAll,
#if BL_FEATURE_ERASEALL_UNSECURE
    .flash_erase_all_unsecure = FLASH_EraseAllUnsecure,
#else
    .flash_erase_all_unsecure = NULL,
#endif
    .flash_erase = FLASH_Erase,
    .flash_program = FLASH_Program,
    .flash_get_security_state = FLASH_GetSecurityState,
    .flash_security_bypass = FLASH_SecurityBypass,
    .flash_verify_erase_all = FLASH_VerifyEraseAll,
    .flash_verify_erase = FLASH_VerifyErase,
    .flash_verify_program = FLASH_VerifyProgram,
    .flash_get_property = FLASH_GetProperty,
#if !BL_FEATURE_MIN_PROFILE
    .flash_program_once = FTFx_CMD_ProgramOnce,
    .flash_read_once = FTFx_CMD_ReadOnce,
#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
    .flash_read_resource = FLASH_ReadResource,
#else
    .flash_read_resource = NULL,
#endif
#else
    .flash_program_once = NULL,
    .flash_read_once = NULL,
    .flash_read_resource = NULL,
#endif
#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
    .flash_is_execute_only = FLASH_IsExecuteOnly,
#endif
#if BL_FEATURE_FAC_ERASE
    .flash_erase_all_execute_only_segments = FLASH_EraseAllExecuteOnlySegments,
    .flash_verify_erase_all_execute_only_segments = FLASH_VerifyEraseAllExecuteOnlySegments,
#else
    .flash_erase_all_execute_only_segments = NULL,
    .flash_verify_erase_all_execute_only_segments = NULL,
#endif
#if BL_IS_FLASH_SECTION_PROGRAMMING_ENABLED
#if FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
    .flash_set_flexram_function = FLASH_SetFlexramFunction,
#else
    .flash_set_flexram_function = NULL,
#endif
    .flash_program_section = FLASH_ProgramSection,
#else
    .flash_set_flexram_function = NULL,
    .flash_program_section = NULL,
#endif
};
#else // BL_DEVICE_IS_LPC_SERIES
const flashiap_driver_interface_t g_flashDriverInterface = {
    .version = {.name = kFLASHIAP_DriverVersionName,
                .major = kFLASHIAP_DriverVersionMajor,
                .minor = kFLASHIAP_DriverVersionMinor,
                .bugfix = kFLASHIAP_DriverVersionBugfix },
    .flash_init = FLASHIAP_Init,
    .flash_erase = FLASHIAP_Erase,
    .flash_program = FLASHIAP_Program,
    .flash_verify_erase = FLASHIAP_VerifyErase,
    .flash_verify_program = FLASHIAP_VerifyProgram,
    .flash_get_property = FLASHIAP_GetProperty,
#if BL_FEATURE_BYPASS_WATCHDOG
    .flash_register_callback = FLASHIAP_SetCallback,
#else
    .flash_register_callback = NULL,
#endif
};
#endif // !BL_DEVICE_IS_LPC_SERIES
#endif // !BL_FEATURE_HAS_NO_INTERNAL_FLASH


//! @brief Function table for flash driver.
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if (BL_FEATURE_SUPPORT_DFLASH)
const dflash_driver_interface_t g_dflashDriverInterface = {
    .version = {.name = kFLASH_DriverVersionName,
                .major = kFLASH_DriverVersionMajor,
                .minor = kFLASH_DriverVersionMinor,
                .bugfix = kFLASH_DriverVersionBugfix },
    .flash_init = FLEXNVM_Init,
    .flash_erase_all = FLEXNVM_EraseAll,
#if BL_FEATURE_ERASEALL_UNSECURE
    .flash_erase_all_unsecure = FLEXNVM_EraseAllUnsecure,
#else
    .flash_erase_all_unsecure = NULL,
#endif
    .flash_erase = FLEXNVM_DflashErase,
    .flash_program = FLEXNVM_DflashProgram,
    .flash_get_security_state = FLEXNVM_GetSecurityState,
    .flash_security_bypass = FLEXNVM_SecurityBypass,
    .flash_verify_erase_all = FLEXNVM_VerifyEraseAll,
    .flash_verify_erase = FLEXNVM_DflashVerifyErase,
    .flash_verify_program = FLEXNVM_DflashVerifyProgram,
    .flash_get_property = FLEXNVM_GetProperty,
#if !BL_FEATURE_MIN_PROFILE
    .flash_program_once = NULL,  //FTFx_CMD_ProgramOnce,
    .flash_read_once = NULL, //FTFx_CMD_ReadOnce,
#if defined(FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD) && FSL_FEATURE_FLASH_HAS_READ_RESOURCE_CMD
    .flash_read_resource = FLEXNVM_ReadResource,
#else
    .flash_read_resource = NULL,
#endif
#else
    .flash_program_once = NULL,
    .flash_read_once = NULL,
    .flash_read_resource = NULL,
#endif
    .flash_is_execute_only = NULL,
    .flash_erase_all_execute_only_segments = NULL,
    .flash_verify_erase_all_execute_only_segments = NULL,
#if BL_IS_FLASH_SECTION_PROGRAMMING_ENABLED
#if FSL_FEATURE_FLASH_HAS_SET_FLEXRAM_FUNCTION_CMD
    .flash_set_flexram_function = FLEXNVM_SetFlexramFunction,
#else
    .flash_set_flexram_function = NULL,
#endif
    .flash_program_section = FLEXNVM_DflashProgramSection,
#else
    .flash_set_flexram_function = NULL,
    .flash_program_section = NULL,
#endif
};
#endif
#endif


const aes_driver_interface_t g_aesInterface = {
#if AES_SECURITY_SUPPORTED
    .aes_init = aes_init, .aes_encrypt = aes_encrypt, .aes_decrypt = aes_decrypt
};
#else
    0
};
#endif

//! @brief Copyright string for the bootloader.
const char bootloaderCopyright[] = "Copyright (c) 2013-2016 Freescale Semiconductor, Inc. All rights reserved.";

//! @brief Static API tree.
const bootloader_tree_t g_bootloaderTree = {.runBootloader = bootloader_user_entry,
                                            .version = {.name = kBootloader_Version_Name,
                                                        .major = kBootloader_Version_Major,
                                                        .minor = kBootloader_Version_Minor,
                                                        .bugfix = kBootloader_Version_Bugfix },
                                            .copyright = bootloaderCopyright,
                                            .runtimeContext = &g_bootloaderContext,
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
                                            .flashDriver = &g_flashDriverInterface,
#endif // !BL_FEATURE_HAS_NO_INTERNAL_FLASH
                                            .aesDriver = &g_aesInterface };

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
