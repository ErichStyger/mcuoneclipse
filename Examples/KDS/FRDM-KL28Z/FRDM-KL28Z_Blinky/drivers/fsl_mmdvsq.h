/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#ifndef _FSL_MMDVSQ_H_
#define _FSL_MMDVSQ_H_

#include "fsl_common.h"

/*!
 * @addtogroup mmdvsq
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FSL_MMSVSQ_DRIVER_VERSION (MAKE_VERSION(2, 0, 0)) /*!< Version 2.0.0. */

/*! @brief MMDVSQ execution status */
typedef enum _mmdvsq_execution_status
{
    kMMDVSQ_IdleSquareRoot = 0x01U, /*!< MMDVSQ is idle, last calculation was a square root */
    kMMDVSQ_IdleDivide = 0x02U,     /*!< MMDVSQ is idle, last calculation was a divide */
    kMMDVSQ_BusySquareRoot = 0x05U, /*!< MMDVSQ is busy processing a square root calculation */
    kMMDVSQ_BusyDivide = 0x06U      /*!< MMDVSQ is busy processing a divide calculation */
} mmdvsq_execution_status_t;

/*! @brief MMDVSQ divide fast start select */
typedef enum _mmdvsq_fast_start_select
{
    kMMDVSQ_EnableFastStart = 0U, /*!< Divide operation is initiated by a write to the DSOR register */
    kMMDVSQ_DisableFastStart =
        1U /*!< Divide operation is initiated by a write to CSR[SRT] = 1, normal start instead fast start */
} mmdvsq_fast_start_select_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name MMDVSQ functional Operation
 * @{
 */

/*!
 * @brief Perform the MMDVSQ divide operation and returns the remainder.
 *
 * @param   base        MMDVSQ peripheral address
 * @param   dividend    Dividend value
 * @param   divisor     Divisor value
 * @param   isUnsigned  Mode of unsigned divide
 *                      - true   unsigned divide
 *                      - false  signed divide
 *
 */
int32_t MMDVSQ_GetDivideRemainder(MMDVSQ_Type *base, int32_t dividend, int32_t divisor, bool isUnsigned);

/*!
 * @brief Perform the MMDVSQ divide operation and returns the quotient.
 *
 * @param   base        MMDVSQ peripheral address
 * @param   dividend    Dividend value
 * @param   divisor     Divisor value
 * @param   isUnsigned  Mode of unsigned divide
 *                      - true   unsigned divide
 *                      - false  signed divide
 *
 */
int32_t MMDVSQ_GetDivideQuotient(MMDVSQ_Type *base, int32_t dividend, int32_t divisor, bool isUnsigned);

/*!
 * @brief Perform the MMDVSQ square root operation
 *
 * This function performs the MMDVSQ square root operation and return the square root
 * result of given radicand value.
 *
 * @param   base        MMDVSQ peripheral address
 * @param   radicand    Radicand value
 *
 */
uint16_t MMDVSQ_Sqrt(MMDVSQ_Type *base, uint32_t radicand);

/* @} */

/*!
 * @name MMDVSQ status Operation
 * @{
 */

/*!
 * @brief Get the MMDVSQ execution status
 *
 * This function checks the current MMDVSQ execution status of the combined
 * CSR[BUSY, DIV, SQRT] indicators.
 *
 * @param   base       MMDVSQ peripheral address
 *
 * @return  Current MMDVSQ execution status
 */
static inline mmdvsq_execution_status_t MMDVSQ_GetExecutionStatus(MMDVSQ_Type *base)
{
    return (mmdvsq_execution_status_t)(base->CSR >> MMDVSQ_CSR_SQRT_SHIFT);
}

/*!
 * @brief Configure MMDVSQ fast start mode
 *
 * This function sets the MMDVSQ divide fast start.The MMDVSQ supports two
 * mechanisms for initiating a divide operation. The default mechanism is
 * a “fast start” where a write to the DSOR register begins the divide.
 * Alternatively, the start mechanism can begin after a write to the CSR
 * register with CSR[SRT] set.
 *
 * @param   base        MMDVSQ peripheral address
 * @param   mode        Mode of Divide-Fast-Start
 *                      - kMmdvsqDivideFastStart   = 0
 *                      - kMmdvsqDivideNormalStart = 1
 */
static inline void MMDVSQ_SetFastStartConfig(MMDVSQ_Type *base, mmdvsq_fast_start_select_t mode)
{
    if (mode)
    {
        base->CSR |= MMDVSQ_CSR_DFS_MASK;
    }
    else
    {
        base->CSR &= ~MMDVSQ_CSR_DFS_MASK;
    }
}

/*!
 * @brief Configure MMDVSQ divide-by-zero mode
 *
 * This function configures the MMDVSQ’s response to divide-by-zero
 * calculations. If both CSR[DZ] and CSR[DZE] are set, then a subsequent read
 * of the RES register is error terminated to signal the processor of the
 * attempted divide-by-zero, else the register contents are returned.
 *
 * @param   base           MMDVSQ peripheral address
 * @param   isDivByZero    Mode of Divide-By-Zero
 *                          - kMmdvsqDivideByZeroDis = 0
 *                          - kMmdvsqDivideByZeroEn  = 1
 */
static inline void MMDVSQ_SetDivideByZeroConfig(MMDVSQ_Type *base, bool isDivByZero)
{
    if (isDivByZero)
    {
        base->CSR |= MMDVSQ_CSR_DZE_MASK;
    }
    else
    {
        base->CSR &= ~MMDVSQ_CSR_DZE_MASK;
    }
}

/* @} */

#if defined(__cplusplus)
}

#endif /* __cplusplus */

/*! @}*/

#endif /* _FSL_MMDVSQ_H_ */
