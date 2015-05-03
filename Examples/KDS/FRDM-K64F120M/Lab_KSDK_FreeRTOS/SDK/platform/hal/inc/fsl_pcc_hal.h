/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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

#ifndef __FSL_PCC_HAL_H__
#define __FSL_PCC_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup pcc_hal
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/

/* Peripheral index in PCC0. */
#define PCC0_INDEX_DMA0       ( 0x0020U >> 2 )
#define PCC0_INDEX_XRDC0      ( 0x0050U >> 2 )
#define PCC0_INDEX_SEMA0      ( 0x006CU >> 2 )
#define PCC0_INDEX_FLASH0     ( 0x0080U >> 2 )
#define PCC0_INDEX_DMAMUX0    ( 0x0084U >> 2 )
#define PCC0_INDEX_MU0_A      ( 0x008CU >> 2 )
#define PCC0_INDEX_INTMUX0    ( 0x0090U >> 2 )
#define PCC0_INDEX_TPM2       ( 0x00B8U >> 2 )
#define PCC0_INDEX_PIT0       ( 0x00C0U >> 2 )
#define PCC0_INDEX_LPTMR0     ( 0x00D0U >> 2 )
#define PCC0_INDEX_RTC0       ( 0x00E0U >> 2 )
#define PCC0_INDEX_LPSPI2     ( 0x00F8U >> 2 )
#define PCC0_INDEX_LPI2C2     ( 0x0108U >> 2 )
#define PCC0_INDEX_LPUART2    ( 0x0118U >> 2 )
#define PCC0_INDEX_SAI0       ( 0x0130U >> 2 )
#define PCC0_INDEX_EVMSIM0    ( 0x0138U >> 2 )
#define PCC0_INDEX_USBFS0     ( 0x0154U >> 2 )
#define PCC0_INDEX_PORTA      ( 0x0168U >> 2 )
#define PCC0_INDEX_PORTB      ( 0x016CU >> 2 )
#define PCC0_INDEX_PORTC      ( 0x0170U >> 2 )
#define PCC0_INDEX_PORTD      ( 0x0174U >> 2 )
#define PCC0_INDEX_PORTE      ( 0x0178U >> 2 )
#define PCC0_INDEX_TSI0       ( 0x0188U >> 2 )
#define PCC0_INDEX_ADC0       ( 0x0198U >> 2 )
#define PCC0_INDEX_DAC0       ( 0x01A8U >> 2 )
#define PCC0_INDEX_CMP0       ( 0x01B8U >> 2 )
#define PCC0_INDEX_VREF0      ( 0x01C8U >> 2 )
#define PCC0_INDEX_ATX0       ( 0x01CCU >> 2 )
#define PCC0_INDEX_CRC0       ( 0x01E0U >> 2 )

/* Peripheral index in PCC1. */
#define PCC1_INDEX_DMA1       ( 0x0020U >> 2 )
#define PCC1_INDEX_SEMA1      ( 0x006CU >> 2 )
#define PCC1_INDEX_DMAMUX1    ( 0x0084U >> 2 )
#define PCC1_INDEX_MU0_B      ( 0x008CU >> 2 )
#define PCC1_INDEX_INTMUX1    ( 0x0090U >> 2 )
#define PCC1_INDEX_TRNG0      ( 0x0094U >> 2 )
#define PCC1_INDEX_TPM0       ( 0x00B0U >> 2 )
#define PCC1_INDEX_TPM1       ( 0x00B4U >> 2 )
#define PCC1_INDEX_PIT1       ( 0x00C4U >> 2 )
#define PCC1_INDEX_LPTMR1     ( 0x00D4U >> 2 )
#define PCC1_INDEX_LPSPI0     ( 0x00F0U >> 2 )
#define PCC1_INDEX_LPSPI1     ( 0x00F4U >> 2 )
#define PCC1_INDEX_LPI2C0     ( 0x0100U >> 2 )
#define PCC1_INDEX_LPI2C1     ( 0x0104U >> 2 )
#define PCC1_INDEX_LPUART0    ( 0x0110U >> 2 )
#define PCC1_INDEX_LPUART1    ( 0x0114U >> 2 )
#define PCC1_INDEX_FLEXIO0    ( 0x0128U >> 2 )
#define PCC1_INDEX_BBS0_PORT  ( 0x0180U >> 2 )
#define PCC1_INDEX_CMP1       ( 0x01BCU >> 2 )

/*!
 * @brief Clock source for peripherals that support various clock selections.
 */
typedef enum _clock_ip_src
{
    kClockIpSrcNone     = 0U,   /*!< Clock is off or test clock is enabled.  */
    kClockIpSrcSysOsc   = 1U,   /*!< System Oscillator.                      */
    kClockIpSrcSIrc     = 2U,   /*!< Slow IRC (max is 8MHz).                 */
    kClockIpSrcFIrc     = 3U,   /*!< Fast IRC (max is 48MHz).                */
    kClockIpSrcRtcOsc   = 4U,   /*!< RTC OSC.                                */
    kClockIpSrcSysFll   = 5U,   /*!< System FLL DIV3 or DIV2.                */
    kClockIpSrcSysPll   = 6U,   /*!< System PLL DIV3 or DIV2.                */
    kClockIpSrcPerPll   = 7U,   /*!< Perpheral PLL DIV3 or DIV2.             */
    kClockIpSrcMax      = 8U,   /*!< Max value.                              */
} clock_ip_src_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Enable clock for some IP module.
 *
 * This function enable clock for some specific IP module.
 * For example, to enable the DMA0 clock, use like this:
 * @code
   CLOCK_HAL_EnableClock(PCC0_BASE, 8);
 * @endcode
 * or use macro like this:
 * @code
   CLOCK_HAL_EnableClock(PCC0_BASE, PCC0_INDEX_DMA0);
 * @endcode
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 */
static inline void CLOCK_HAL_EnableClock(PCC_Type * base, uint8_t index)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    PCC_BWR_CLKCFGn_CGC(base, index, 1U);
}

/*!
 * @brief Disable clock for some IP module.
 *
 * This function disable clock for some specific IP module.
 * For example, to disable the DMA0 clock, use like this:
 * @code
   CLOCK_HAL_DisableClock(PCC0_BASE, 8);
 * @endcode
 * or use macro like this:
 * @code
   CLOCK_HAL_DisableClock(PCC0_BASE, PCC0_INDEX_DMA0);
 * @endcode
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 */
static inline void CLOCK_HAL_DisableClock(PCC_Type * base, uint8_t index)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    PCC_BWR_CLKCFGn_CGC(base, index, 0U);
}

/*!
 * @brief Gets the clock gate status on current core for some IP module.
 *
 * This function gets the clock gate status on current core for some IP module.
 * For example, to get the DMA0 clock gate status, use like this:
 * @code
   CLOCK_HAL_GetGateCmd(PCC0_BASE, 8);
 * @endcode
 * or use macro like this:
 * @code
   CLOCK_HAL_GetGateCmd(PCC0_BASE, PCC0_INDEX_DMA0);
 * @endcode
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_HAL_GetGateCmd(PCC_Type * base, uint8_t index)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    return (bool)PCC_BRD_CLKCFGn_CGC(base, index);
}

/*!
 * @brief Gets the clock gate status on other core for some IP module.
 *
 * This function gets the clock gate status on other core for some IP module.
 * For example, to get the DMA0 clock gate status, use like this:
 * @code
   CLOCK_HAL_GetGateCmdOnOtherCore(PCC0_BASE, 8);
 * @endcode
 * or use macro like this:
 * @code
   CLOCK_HAL_GetGateCmdOnOtherCore(PCC0_BASE, PCC0_INDEX_DMA0);
 * @endcode
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_HAL_GetGateCmdOnOtherCore(PCC_Type * base, uint8_t index)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    return (bool)PCC_BRD_CLKCFGn_CGC_ALT(base, index);
}

/*!
 * @brief Sets the clock source for some IP module.
 *
 * This function sets the clock source for some IP module.
 * For example, to set the clock source for USBFS0 to OSCCLK, use like this:
 * @code
   CLOCK_HAL_SetIpSrc(PCC0_BASE, 38, kClockIpSrcSysOsc);
 * @endcode
 * or use macro like this:
 * @code
   CLOCK_HAL_SetIpSrc(PCC0_BASE, PCC0_INDEX_USBFS0, kClockIpSrcSysOsc);
 * @endcode
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 * @param src      The clock source to set.
 *
 * @note Not all peripherals support various clock sources, please check the
 *       reference manual for more details.
 */
static inline void CLOCK_HAL_SetIpSrc(PCC_Type * base,
                                      uint8_t index,
                                      clock_ip_src_t src)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    assert(src < kClockIpSrcMax);

    PCC_BWR_CLKCFGn_PCS(base, index, src);
}

/*!
 * @brief Gets the clock source for some IP module.
 *
 * This function gets the clock source for some IP module.
 * For example, to get the clock source for USBFS0 to OSCCLK, use like this:
 * @code
   CLOCK_HAL_GetIpSrc(PCC0_BASE, 38);
 * @endcode
 * or use macro like this:
 * @code
   CLOCK_HAL_GetIpSrc(PCC0_BASE, PCC0_INDEX_USBFS0);
 * @endcode
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 * @return Current clock source for this module.
 *
 * @note Not all peripherals support various clock sources, please check the
 *       reference manual for more details.
 */
static inline clock_ip_src_t CLOCK_HAL_GetIpSrc(PCC_Type * base,
                                                uint8_t index)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    return (clock_ip_src_t)PCC_BRD_CLKCFGn_PCS(base, index);
}

/*!
 * @brief Sets the clock divider for some IP module.
 *
 * This function sets the clock divider for some IP module.
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 * @param divider  Clock divider for this module.
 *
 * @note Not all peripherals support this feature, please check the
 *       reference manual for more details.
 */
static inline void CLOCK_HAL_SetIpDiv(PCC_Type * base,
                                      uint8_t index,
                                      uint32_t divider)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    PCC_BWR_CLKCFGn_PCD(base, index, divider);
}


/*!
 * @brief Gets the clock divider for some IP module.
 *
 * This function gets the clock divider for some IP module.
 *
 * @param base Register base address for the PCC instance.
 * @param index    The control register index for the IP module in PCC.
 * @return Current clock divider for this module.
 *
 * @note Not all peripherals support this feature, please check the
 *       reference manual for more details.
 */
static inline uint32_t CLOCK_HAL_GetIpDiv(PCC_Type * base,
                                          uint8_t index)
{
    /* Make sure this IP is present. */
    assert(PCC_BRD_CLKCFGn_EN(base, index));

    return (uint32_t)PCC_BRD_CLKCFGn_PCD(base, index);
}

#if defined(__cplusplus)
extern }
#endif

/*!
 * @}
 */

#endif /* __FSL_PCC_HAL_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/

