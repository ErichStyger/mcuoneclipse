/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(SMC_HW_ACCESS_H)
#define SMC_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>

/*!
 * @file smc_hw_access.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 */

/*!
 * @ingroup smc_hw_access
 * @defgroup smc_hw_access
 * @{
 */


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


/*!
 * @brief Gets the current running power mode.
 *
 * This function  returns the current running power mode.
 *
 * @param[in] baseAddr  Base address for current SMC instance.
 * @return stat  Current power mode stat
 */
static inline uint32_t SMC_GetCurrentRunningMode(const SMC_Type* const baseAddr)
{
    return (baseAddr->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) >> SMC_PMSTAT_PMSTAT_SHIFT;
}


#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* SMC_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/

