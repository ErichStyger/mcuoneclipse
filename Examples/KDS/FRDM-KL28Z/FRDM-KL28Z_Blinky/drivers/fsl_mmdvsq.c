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

#include "fsl_mmdvsq.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

int32_t MMDVSQ_GetDivideRemainder(MMDVSQ_Type *base, int32_t dividend, int32_t divisor, bool isUnsigned)
{
    uint32_t temp = 0;

    temp = base->CSR;
    temp &= ~(MMDVSQ_CSR_USGN_MASK | MMDVSQ_CSR_REM_MASK);
    /* Prepare setting for calculation */
    temp |= MMDVSQ_CSR_USGN(isUnsigned) | MMDVSQ_CSR_REM(true);
    /* Write setting to CSR register */
    base->CSR = temp;
    /* Write dividend to DEND register */
    base->DEND = dividend;
    /* Write divisor to DSOR register and start calculation if Fast-Start is enabled */
    base->DSOR = divisor;
    /* Start calculation by writing 1 to SRT bit in case Fast-Start is disabled */
    base->CSR |= MMDVSQ_CSR_SRT_MASK;
    /* Return remainder, if divide-by-zero is enabled and occurred, reading from
    * RES result is error terminated */
    return base->RES;
}

int32_t MMDVSQ_GetDivideQuotient(MMDVSQ_Type *base, int32_t dividend, int32_t divisor, bool isUnsigned)
{
    uint32_t temp = 0;

    temp = base->CSR;
    temp &= ~(MMDVSQ_CSR_USGN_MASK | MMDVSQ_CSR_REM_MASK);
    /* Prepare setting for calculation */
    temp |= MMDVSQ_CSR_USGN(isUnsigned) | MMDVSQ_CSR_REM(false);
    /* Write setting mode to CSR register */
    base->CSR = temp;
    /* Write dividend to DEND register */
    base->DEND = dividend;
    /* Write divisor to DSOR register and start calculation when Fast-Start is enabled */
    base->DSOR = divisor;
    /* Start calculation by writing 1 to SRT bit in case Fast-Start is disabled */
    base->CSR |= MMDVSQ_CSR_SRT_MASK;
    /* Return quotient, if divide-by-zero is enabled and occurred, reading from
    * RES result is error terminated */
    return base->RES;
}

uint16_t MMDVSQ_Sqrt(MMDVSQ_Type *base, uint32_t radicand)
{
    /* Write radicand to RCND register , and start calculation */
    base->RCND = radicand;
    /* Return result */
    return base->RES;
}
