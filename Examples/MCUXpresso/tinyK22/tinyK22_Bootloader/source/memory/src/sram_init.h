/*
 * Copyright (c) 2014 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __SRAM_INIT_H__
#define __SRAM_INIT_H__

#include <stdint.h>
#include "memory/memory.h"

////////////////////////////////////////////////////////////////////////////////
// Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief SRAM size-related constants of KL series (CM0+ family)
enum _kl_serials_sram_constants
{
    kMaxRamIndex = 8,
    kMinKlRamSize = (uint32_t)512
};

#if defined(__CORE_CM4_H_GENERIC) || defined(__CORE_CM7_H_GENERIC)
//! @brief valid SRAM size index of K series (CM4 family)
enum _k_serials_sram_index_constants
{
    kRamSize16kIndex = 3,
    kRamSize24kIndex = 4,
    kRamSize32kIndex = 5,
    kRamSize48kIndex = 6,
    kRamSize64kIndex = 7,
    kRamSize96kIndex = 8,
    kRamSize128kIndex = 9,
    kRamSize256kIndex = 11,
    kRamSize512kIndex = 13,
    kRamSize1024kIndex = 15
};
#endif

#if defined(__CORE_CM0PLUS_H_GENERIC)
enum _k_serials_sram_index_constants
{
    kRamSize0p5kIndex = 0,
    kRamSize1kIndex = 1,
    kRamSize2kIndex = 2,
    kRamSize4kIndex = 3,
    kRamSize8kIndex = 4,
    kRamSize16kIndex = 5,
    kRamSize32kIndex = 6,
    kRamSize64kIndex = 7,
    kRamSize128kIndex = 9
};
#endif

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

//! @brief Initialize sram interface.
status_t sram_init(void);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
