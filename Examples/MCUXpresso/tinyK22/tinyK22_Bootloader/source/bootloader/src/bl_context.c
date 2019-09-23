/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader/bl_context.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Bootloader global context data.
//!
//! @ingroup context
bootloader_context_t g_bootloaderContext = {.memoryInterface = &g_memoryInterface,
                                            .memoryMap = g_memoryMap,
#if BL_FEATURE_EXPAND_MEMORY
                                            .externalMemoryMap = g_externalMemoryMap,
#endif // BL_FEATURE_EXPAND_MEMORY
                                            .allPeripherals = g_peripherals,
                                            .activePeripheral = NULL, // Filled in at run time.
                                            .propertyInterface = &g_propertyInterface,
                                            .commandInterface = &g_commandInterface,
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
                                            .flashDriverInterface = &g_flashDriverInterface,
#if !BL_DEVICE_IS_LPC_SERIES
                                            .allFlashState = &g_flashState,
                                            .allFlashCacheState = &g_flashcacheState,
#if BL_FEATURE_SUPPORT_DFLASH
                                            .dflashDriverInterface = &g_dflashDriverInterface,
                                            .dFlashState = &g_dflashState,
#endif // BL_FEATURE_SUPPORT_DFLASH
                                            
#else
                                            .allFlashState = g_flashiapState,
#endif // !BL_DEVICE_IS_LPC_SERIES
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if AES_SECURITY_SUPPORTED
                                            .aesInterface = &g_aesInterface,
#endif

};
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
