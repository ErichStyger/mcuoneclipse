/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__PATTERN_FILL_H__)
#define __PATTERN_FILL_H__

#include <stdint.h>
#include <stdbool.h>
#include "bootloader_common.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @brief Fill memory with a pattern.
//!
//! Fills memory with a 32-bit pattern starting at the given address and continuing
//! for the specified number of bytes. The start address and length do not have to
//! be word aligned or sized.
status_t pattern_fill(uint32_t address, uint32_t pattern, uint32_t length, bool allowMultiword);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // __PATTERN_FILL_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
