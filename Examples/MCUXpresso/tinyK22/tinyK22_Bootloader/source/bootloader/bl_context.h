/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__CONTEXT_H__)
#define __CONTEXT_H__

#include "bootloader_common.h"
#include "bootloader/bl_peripheral.h"
#include "memory/memory.h"
#include "packet/command_packet.h"
#include "bootloader/bl_command.h"
#include "property/property.h"

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
#endif //#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if BL_FEATURE_ENCRYPTION
#include "aes_security.h"
#endif // #if BL_FEATURE_ENCRYPTION

//! @addtogroup context
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
//! @brief Interface for the flash driver.
typedef struct FlashDriverInterface
{
    standard_version_t version; //!< flash driver API version number.
    status_t (*flash_init)(flash_config_t *config);
    status_t (*flash_erase_all)(flash_config_t *config, uint32_t key);
    status_t (*flash_erase_all_unsecure)(flash_config_t *config, uint32_t key);
    status_t (*flash_erase)(flash_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program)(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_get_security_state)(flash_config_t *config, ftfx_security_state_t *state);
    status_t (*flash_security_bypass)(flash_config_t *config, const uint8_t *backdoorKey);
    status_t (*flash_verify_erase_all)(flash_config_t *config, ftfx_margin_value_t margin);
    status_t (*flash_verify_erase)(flash_config_t *config,
                                   uint32_t start,
                                   uint32_t lengthInBytes,
                                   ftfx_margin_value_t margin);
    status_t (*flash_verify_program)(flash_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     ftfx_margin_value_t margin,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flash_get_property)(flash_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);
    status_t (*flash_program_once)(ftfx_config_t *config, uint32_t index, const uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_read_once)(ftfx_config_t *config, uint32_t index, uint8_t *dst, uint32_t lengthInBytes);
    status_t (*flash_read_resource)(flash_config_t *config,
                                    uint32_t start,
                                    uint8_t *dst,
                                    uint32_t lengthInBytes,
                                    ftfx_read_resource_opt_t option);
#if defined(FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL) && FSL_FEATURE_FLASH_HAS_ACCESS_CONTROL
    status_t (*flash_is_execute_only)(flash_config_t *config,
                                      uint32_t start,
                                      uint32_t lengthInBytes,
                                      flash_xacc_state_t *access_state);
#endif
    status_t (*flash_erase_all_execute_only_segments)(flash_config_t *config, uint32_t key);
    status_t (*flash_verify_erase_all_execute_only_segments)(flash_config_t *config, ftfx_margin_value_t margin);
    status_t (*flash_set_flexram_function)(flash_config_t *config, ftfx_flexram_func_opt_t option);
    status_t (*flash_program_section)(flash_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
} flash_driver_interface_t;
#else // BL_DEVICE_IS_LPC_SERIES
typedef struct FlashiapDriverInterface
{
    standard_version_t version; //!< flash driver API version number.
    status_t (*flash_init)(flashiap_config_t *config);
    status_t (*flash_erase)(flashiap_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program)(flashiap_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_verify_erase)(flashiap_config_t *config, uint32_t start, uint32_t lengthInBytes);
    status_t (*flash_verify_program)(flashiap_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     ftfx_margin_value_t margin,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flash_get_property)(flashiap_config_t *config, flash_property_tag_t whichProperty, uint32_t *value);
    status_t (*flash_register_callback)(flashiap_config_t *config, flash_callback_t callback);
} flashiap_driver_interface_t;
#endif // !BL_DEVICE_IS_LPC_SERIES
#endif //#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH

#if BL_DEVICE_IS_LPC_SERIES
typedef struct PowerDriverInterface
{
    uint32_t (*power_set_pll)(uint32_t multiply_by, uint32_t input_freq);
    uint32_t (*power_set_voltage)( unsigned int mode, unsigned int frequency );
    void (*power_mode_configure)(unsigned int power_mode, unsigned int peripheral_ctrl);
    void (*power_set_low_power_mode)( unsigned int high_current_level );
    void (*power_set_vd_level)(uint32_t domain, uint32_t level);
    void (*power_set_lpvd_level)(uint32_t vd1LpLevel, uint32_t vd2LpLevel, uint32_t vd3LpLevel, uint32_t vd8LpLevel, uint32_t vddflashLpLevel,
                                 uint32_t flevel);
    void (*power_energy_reclaim)( void );
    void (*power_enter_RBB)(void);
    void (*power_enter_NBB)(void);
    void (*power_enter_FBB)(uint32_t FBB_HP_Enable);
    void (*power_disable_energy_reclaim)(void);
    uint32_t (*power_PVT_interrupt)(void);
    uint32_t (*power_set_pll_with_fracdiv)(uint32_t FinKHz, uint32_t FoutKHz, uint32_t spreadSpec);
    uint32_t (*power_get_firmware_version)( void );
} power_driver_interface_t;
#endif

#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if BL_FEATURE_SUPPORT_DFLASH
//! @brief Interface for the Dflash driver.
typedef struct DFlashDriverInterface
{
    standard_version_t version; //!< flash driver API version number.
    status_t (*flash_init)(flexnvm_config_t *config);
    status_t (*flash_erase_all)(flexnvm_config_t *config, uint32_t key);
    status_t (*flash_erase_all_unsecure)(flexnvm_config_t *config, uint32_t key);
    status_t (*flash_erase)(flexnvm_config_t *config, uint32_t start, uint32_t lengthInBytes, uint32_t key);
    status_t (*flash_program)(flexnvm_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_get_security_state)(flexnvm_config_t *config, ftfx_security_state_t *state);
    status_t (*flash_security_bypass)(flexnvm_config_t *config, const uint8_t *backdoorKey);
    status_t (*flash_verify_erase_all)(flexnvm_config_t *config, ftfx_margin_value_t margin);
    status_t (*flash_verify_erase)(flexnvm_config_t *config,
                                   uint32_t start,
                                   uint32_t lengthInBytes,
                                   ftfx_margin_value_t margin);
    status_t (*flash_verify_program)(flexnvm_config_t *config,
                                     uint32_t start,
                                     uint32_t lengthInBytes,
                                     const uint8_t *expectedData,
                                     ftfx_margin_value_t margin,
                                     uint32_t *failedAddress,
                                     uint32_t *failedData);
    status_t (*flash_get_property)(flexnvm_config_t *config, flexnvm_property_tag_t whichProperty, uint32_t *value);
    status_t (*flash_program_once)(flexnvm_config_t *config, uint32_t index, uint8_t *src, uint32_t lengthInBytes);
    status_t (*flash_read_once)(flexnvm_config_t *config, uint32_t index, uint8_t *dst, uint32_t lengthInBytes);
    status_t (*flash_read_resource)(flexnvm_config_t *config,
                                    uint32_t start,
                                    uint8_t *dst,
                                    uint32_t lengthInBytes,
                                    ftfx_read_resource_opt_t option);
    status_t (*flash_is_execute_only)(flexnvm_config_t *config,
                                      uint32_t start,
                                      uint32_t lengthInBytes,
                                      flash_xacc_state_t *access_state);
    status_t (*flash_erase_all_execute_only_segments)(flexnvm_config_t *config, uint32_t key);
    status_t (*flash_verify_erase_all_execute_only_segments)(flexnvm_config_t *config, ftfx_margin_value_t margin);
    status_t (*flash_set_flexram_function)(flexnvm_config_t *config, ftfx_flexram_func_opt_t option);
    status_t (*flash_program_section)(flexnvm_config_t *config, uint32_t start, uint8_t *src, uint32_t lengthInBytes);
} dflash_driver_interface_t;
#endif // #if BL_FEATURE_SUPPORT_DFLASH
#endif //#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH




//! @brief Interface for AES 128 functions
typedef struct AesDriverInterface
{
    void (*aes_init)(uint32_t *key);
    void (*aes_encrypt)(uint32_t *in, uint32_t *key, uint32_t *out);
    void (*aes_decrypt)(uint32_t *in, uint32_t *key, uint32_t *out);
} aes_driver_interface_t;

//! @brief Structure of bootloader global context.
typedef struct _bootloaderContext
{
    //! @name API tree
    //@{
    const memory_interface_t *memoryInterface; //!< Abstract interface to memory operations.
    const memory_map_entry_t *memoryMap;       //!< Memory map used by abstract memory interface.
#if BL_FEATURE_EXPAND_MEMORY
    const external_memory_map_entry_t *externalMemoryMap; //!< Memory map used by external memory devices.
#endif                                                    // BL_FEATURE_EXPAND_MEMORY
    const property_interface_t *propertyInterface;        //!< Interface to property store.
    const command_interface_t *commandInterface;          //!< Interface to command processor operations.
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
    const flash_driver_interface_t *flashDriverInterface;    //!< Kinetis Flash driver interface.
#if BL_FEATURE_SUPPORT_DFLASH
    const dflash_driver_interface_t *dflashDriverInterface;    //!< Kinetis DFlash driver interface.
#endif // BL_FEATURE_SUPPORT_DFLASH
#else
    const flashiap_driver_interface_t *flashDriverInterface; //!< LPC Flash driver interface.
#endif // !BL_DEVICE_IS_LPC_SERIES
#endif // !BL_FEATURE_HAS_NO_INTERNAL_FLASH
    const peripheral_descriptor_t *allPeripherals;        //!< Array of all peripherals.
    const aes_driver_interface_t *aesInterface;           //!< Interface to the AES driver
    //@}

    //! @name Runtime state
    //@{
    const peripheral_descriptor_t *activePeripheral; //!< The currently active peripheral.
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
    flash_config_t *allFlashState;                   //!< Kinetis Flash driver instance.
    ftfx_cache_config_t *allFlashCacheState;                   //!< FTFx cache driver state information
#if BL_FEATURE_SUPPORT_DFLASH
    flexnvm_config_t *dFlashState;             //!< Kinetis DFlash driver instance.
#endif     
#else
    flashiap_config_t *allFlashState;                //!< LPC Flash driver instance.
#endif
#endif
    //@}
} bootloader_context_t;

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

extern bootloader_context_t g_bootloaderContext;
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
extern const flash_driver_interface_t g_flashDriverInterface;
#if BL_FEATURE_SUPPORT_DFLASH
extern const dflash_driver_interface_t g_dflashDriverInterface;
#endif // BL_FEATURE_SUPPORT_DFLASH
#else
extern const flashiap_driver_interface_t g_flashDriverInterface;
#endif
#endif
extern const aes_driver_interface_t g_aesInterface;

//! @}

#endif // __CONTEXT_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
