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

#if !defined(PMC_HW_ACCESS_H)
#define PMC_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>

/*!
 * @file pmc_hw_access.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 */

/*!
 * @ingroup pmc_hw_access
 * @defgroup pmc_hw_access
 * @{
 */


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


/*!
 * @brief Enables/Disables the Low Power Oscillator.
 *
 * This function  enables/disables the Low Power Oscillator.
 *
 * @param[in] baseAddr  Base address for current PMC instance.
 * @param[in] enable    enable/disable the Low Power Oscillator.
 * Implements PMC_SetLpoMode_Activity
 */
static inline void PMC_SetLpoMode(PMC_Type* const baseAddr, const bool enable)
{
    uint8_t regValue = baseAddr->REGSC;
    regValue &= (uint8_t)(~(PMC_REGSC_LPODIS_MASK));
    regValue |= (uint8_t)PMC_REGSC_LPODIS(enable?0U:1U);
    baseAddr->REGSC = regValue;
}


/*!
 * @brief Gets the Low Power Oscillator status.
 *
 * This function provides the current status of
 * the Low Power Oscillator.
 *
 * @param[in] baseAddr  Base address for current PMC instance.
 * @return value LPO status
 *               0 - Low power oscillator in low phase.
 *               1 - Low power oscillator in high phase.
 * Implements PMC_GetLpoStatus_Activity
 */
static inline uint8_t PMC_GetLpoStatus(const PMC_Type* const baseAddr)
{
    uint8_t regValue = baseAddr->REGSC;
    regValue = (uint8_t)((regValue & PMC_REGSC_LPOSTAT_MASK) >> PMC_REGSC_LPOSTAT_SHIFT);
    return regValue;
}

/*!
 * @brief Gets the Low Power Oscillator status.
 *
 * This function gets the Low Power Oscillator status.
 *
 * @param[in] baseAddr  Base address for current PMC instance.
 * @return value LPO status
 *               false - LPO is disabled
 *               true - LPO is enabled
 * Implements PMC_GetLpoMode_Activity
 */
static inline bool PMC_GetLpoMode(const PMC_Type * const baseAddr)
{
    uint8_t regValue = baseAddr->REGSC;
    regValue = (uint8_t)((regValue & PMC_REGSC_LPODIS_MASK) >> PMC_REGSC_LPODIS_SHIFT);
    return (regValue == 0U) ? true : false;
}


/*!
 * @brief Low Power Oscillator Trimming Value
 *
 * This function sets the trimming value for the low power oscillator
 *
 * @param[in] baseAddr  Base address for current PMC instance.
 * @param[in] value     Trimming value
 * Implements PMC_SetLpoTrimValue_Activity
 */
static inline void PMC_SetLpoTrimValue(PMC_Type* const baseAddr, const int8_t decimalValue)
{
    int8_t decValue = decimalValue;
    uint8_t lpotrim, trimval, regValue;

    if (decValue < 0)
    {
        lpotrim = ((uint8_t)1U) << (PMC_LPOTRIM_LPOTRIM_WIDTH);
        decValue = (int8_t)(decValue + (int8_t)(lpotrim));
    }
    trimval = (uint8_t)decValue;

    DEV_ASSERT(trimval <= (1U << (PMC_LPOTRIM_LPOTRIM_WIDTH - 1U)));

    regValue = baseAddr->LPOTRIM;
    regValue &= (uint8_t)(~(PMC_LPOTRIM_LPOTRIM_MASK));
    regValue |= (uint8_t)PMC_LPOTRIM_LPOTRIM(trimval);
    baseAddr->LPOTRIM = regValue;
}


#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* PMC_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/

