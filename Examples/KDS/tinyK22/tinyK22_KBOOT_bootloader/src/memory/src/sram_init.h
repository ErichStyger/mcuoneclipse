/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
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
    kMaxRamIndex = 7,
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
    kRamSize256kIndex = 11
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
    kRamSize64kIndex = 7
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
