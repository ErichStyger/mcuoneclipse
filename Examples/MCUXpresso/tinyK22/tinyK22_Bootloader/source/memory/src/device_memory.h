/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__DEVICE_MEMORY_INTERFACE_H__)
#define __DEVICE_MEMORY_INTERFACE_H__

#include "memory/memory.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @name Device memory
//@{

//! @brief Read memory.
status_t device_mem_read(uint32_t address, uint32_t length, uint8_t *restrict buffer);

//! @brief Write memory.
status_t device_mem_write(uint32_t address, uint32_t length, const uint8_t *restrict buffer);

//! @brief Fill memory with a word pattern.
status_t device_mem_fill(uint32_t address, uint32_t length, uint32_t pattern);

//@}

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __DEVICE_MEMORY_INTERFACE_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
