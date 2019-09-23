/*
 * Copyright (c) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__FLASH_MEMORY_INTERFACE_H__)
#define __FLASH_MEMORY_INTERFACE_H__

#include "memory/memory.h"
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#include "fsl_flash.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define BL_IS_FLASH_SECTION_PROGRAMMING_ENABLED \
    (BL_FEATURE_ENABLE_FLASH_PROGRAM_SECTION && FSL_FEATURE_FLASH_HAS_PROGRAM_SECTION_CMD)

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

//! @brief flash memory array.
#if !BL_FEATURE_HAS_NO_INTERNAL_FLASH
#if !BL_DEVICE_IS_LPC_SERIES
extern flash_config_t g_flashState;
extern ftfx_cache_config_t g_flashcacheState;
#endif // !BL_DEVICE_IS_LPC_SERIES
#endif // #if !BL_FEATURE_HAS_NO_INTERNAL_FLASH


////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @name Flash memory
//! @note Flash read is done through the normal memory interface.
//@{

//! @brief Init selected Flash memory
status_t flash_mem_init(void);

//! @brief Read selected Flash memory.
status_t flash_mem_read(uint32_t address, uint32_t length, uint8_t *restrict buffer);

//! @brief Write selected Flash memory.
status_t flash_mem_write(uint32_t address, uint32_t length, const uint8_t *buffer);

//! @brief Fill selected Flash memory with a word pattern.
status_t flash_mem_fill(uint32_t address, uint32_t length, uint32_t pattern);

//! @brief Flush final buffer or cached data into selected FLASH memory.
status_t flash_mem_flush(void);

//! @brief Erase selected Flash memory.
status_t flash_mem_erase(uint32_t address, uint32_t length);

//@}

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __FLASH_MEMORY_INTERFACE_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
