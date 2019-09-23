/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__NORMAL_MEMORY_INTERFACE_H__)
#define __NORMAL_MEMORY_INTERFACE_H__

#include "memory/memory.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @name Normal memory
//@{

//! @brief Init Normal memory
status_t normal_mem_init(void);

//! @brief Read memory.
status_t normal_mem_read(uint32_t address, uint32_t length, uint8_t *restrict buffer);

//! @brief Write memory.
status_t normal_mem_write(uint32_t address, uint32_t length, const uint8_t *restrict buffer);

//! @brief Fill memory with a word pattern.
status_t normal_mem_fill(uint32_t address, uint32_t length, uint32_t pattern);

//@}

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __NORMAL_MEMORY_INTERFACE_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
