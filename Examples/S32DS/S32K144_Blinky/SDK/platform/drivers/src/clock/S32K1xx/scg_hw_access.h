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

#if !defined(SCG_HW_ACCESS_H)
#define SCG_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>

/*!
 * @file scg_hw_access.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 */

/*!
 * @ingroup scg_hw_access
 * @defgroup scg_hw_access
 * @{
 */




#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


/*!
 * @brief Get SCG ClockOut source select
 *
 * This function gets the SCG clockOut source
 *
 * @param[in] base Register base address for the SCG instance.
 * @return ClockOut source.
 * Implements SCG_GetClockoutSourceSel_Activity
 */
static inline uint32_t SCG_GetClockoutSourceSel(const SCG_Type * base)
{
    return (base->CLKOUTCNFG & SCG_CLKOUTCNFG_CLKOUTSEL_MASK) >> SCG_CLKOUTCNFG_CLKOUTSEL_SHIFT;
}


/*!
 * @brief Gets SCG current system clock source
 *
 * This function gets the current system clock source.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current system clock source.
 */
static inline uint32_t SCG_GetCurrentSystemClockSource(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT);
}

/*!
 * @brief Gets SCG Current Core Clock Divide Ratio
 *
 * This function gets the Current Core Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current Core Clock Divide Ratio.
 */
static inline uint32_t SCG_GetCurrentCoreClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVCORE_MASK) >> SCG_CSR_DIVCORE_SHIFT);
}

/*!
 * @brief Gets SCG Current Bus Clock Divide Ratio
 *
 * This function gets the Current Bus Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current Bus Clock Divide Ratio.
 */
static inline uint32_t SCG_GetCurrentBusClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVBUS_MASK) >> SCG_CSR_DIVBUS_SHIFT);
}

/*!
 * @brief Gets SCG Current Slow Clock Divide Ratio
 *
 * This function gets the Current Slow Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Current Slow Clock Divide Ratio.
 */
static inline uint32_t SCG_GetCurrentSlowClockDividerRatio(const SCG_Type * base)
{
    return ((base->CSR & SCG_CSR_DIVSLOW_MASK) >> SCG_CSR_DIVSLOW_SHIFT);
}


/*!
 * @brief Gets SCG Run system clock source
 *
 * This function gets the Run system clock source.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Run system clock source.
 */
static inline uint32_t SCG_GetRunSystemClockSource(const SCG_Type * base)
{
    return ((base->RCCR & SCG_RCCR_SCS_MASK) >> SCG_RCCR_SCS_SHIFT);
}

/*!
 * @brief Gets SCG Run Core Clock Divide Ratio
 *
 * This function gets the Run Core Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Run Core Clock Divide Ratio.
 */
static inline uint32_t SCG_GetRunCoreClockDividerRatio(const SCG_Type * base)
{
    return ((base->RCCR & SCG_RCCR_DIVCORE_MASK) >> SCG_RCCR_DIVCORE_SHIFT);
}

/*!
 * @brief Gets SCG Run Bus Clock Divide Ratio
 *
 * This function gets the Run Bus Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Run Bus Clock Divide Ratio.
 */
static inline uint32_t SCG_GetRunBusClockDividerRatio(const SCG_Type * base)
{
    return ((base->RCCR & SCG_RCCR_DIVBUS_MASK) >> SCG_RCCR_DIVBUS_SHIFT);
}

/*!
 * @brief Gets SCG Run Slow Clock Divide Ratio
 *
 * This function gets the Run Slow Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Run Slow Clock Divide Ratio.
 */
static inline uint32_t SCG_GetRunSlowClockDividerRatio(const SCG_Type * base)
{
    return ((base->RCCR & SCG_RCCR_DIVSLOW_MASK) >> SCG_RCCR_DIVSLOW_SHIFT);
}


/*!
 * @brief Sets SCG run system clock
 *
 * This function sets the RUN clock control (system clock source, bus, core and slow dividers).
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base System clock configuration address.
 */
static inline void SCG_SetRunClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
    uint32_t value = (uint32_t)(((source      << SCG_RCCR_SCS_SHIFT)     & SCG_RCCR_SCS_MASK)     |
                                ((coreDivider << SCG_RCCR_DIVCORE_SHIFT) & SCG_RCCR_DIVCORE_MASK) |
                                ((busDivider  << SCG_RCCR_DIVBUS_SHIFT)  & SCG_RCCR_DIVBUS_MASK)  |
                                ((slowDivider << SCG_RCCR_DIVSLOW_SHIFT) & SCG_RCCR_DIVSLOW_MASK) );
    base->RCCR = value;
}

/*!
 * @brief Gets SCG Vlpr system clock source
 *
 * This function gets the Vlpr system clock source.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Vlpr system clock source.
 */
static inline uint32_t SCG_GetVlprSystemClockSource(const SCG_Type * base)
{
    return ((base->VCCR & SCG_VCCR_SCS_MASK) >> SCG_VCCR_SCS_SHIFT);
}

/*!
 * @brief Gets SCG Vlpr Core Clock Divide Ratio
 *
 * This function gets the Vlpr Core Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Vlpr Core Clock Divide Ratio.
 */
static inline uint32_t SCG_GetVlprCoreClockDividerRatio(const SCG_Type * base)
{
    return ((base->VCCR & SCG_VCCR_DIVCORE_MASK) >> SCG_VCCR_DIVCORE_SHIFT);
}

/*!
 * @brief Gets SCG Vlpr Bus Clock Divide Ratio
 *
 * This function gets the Vlpr Bus Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Vlpr Bus Clock Divide Ratio.
 */
static inline uint32_t SCG_GetVlprBusClockDividerRatio(const SCG_Type * base)
{
    return ((base->VCCR & SCG_VCCR_DIVBUS_MASK) >> SCG_VCCR_DIVBUS_SHIFT);
}

/*!
 * @brief Gets SCG Vlpr Slow Clock Divide Ratio
 *
 * This function gets the Vlpr Slow Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Vlpr Slow Clock Divide Ratio.
 */
static inline uint32_t SCG_GetVlprSlowClockDividerRatio(const SCG_Type * base)
{
    return ((base->VCCR & SCG_VCCR_DIVSLOW_MASK) >> SCG_VCCR_DIVSLOW_SHIFT);
}

/*!
 * @brief Sets SCG vlpr system clock
 *
 * This function sets the VLPR clock control (system clock source, bus, core and slow dividers).
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base System clock configuration address.
 */
static inline void SCG_SetVlprClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
	uint32_t value = (uint32_t)(((source      << SCG_VCCR_SCS_SHIFT)     & SCG_VCCR_SCS_MASK)     |
								((coreDivider << SCG_VCCR_DIVCORE_SHIFT) & SCG_VCCR_DIVCORE_MASK) |
								((busDivider  << SCG_VCCR_DIVBUS_SHIFT)  & SCG_VCCR_DIVBUS_MASK)  |
								((slowDivider << SCG_VCCR_DIVSLOW_SHIFT) & SCG_VCCR_DIVSLOW_MASK) );

    base->VCCR = value;
}

/*!
 * @brief Gets SCG Hsrun system clock source
 *
 * This function gets the Hsrun system clock source.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Hsrun system clock source.
 */
static inline uint32_t SCG_GetHsrunSystemClockSource(const SCG_Type * base)
{
    return ((base->VCCR & SCG_HCCR_SCS_MASK) >> SCG_HCCR_SCS_SHIFT);
}

/*!
 * @brief Gets SCG Hsrun Core Clock Divide Ratio
 *
 * This function gets the Hsrun Core Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Hsrun Core Clock Divide Ratio.
 */
static inline uint32_t SCG_GetHsrunCoreClockDividerRatio(const SCG_Type * base)
{
    return ((base->VCCR & SCG_HCCR_DIVCORE_MASK) >> SCG_HCCR_DIVCORE_SHIFT);
}

/*!
 * @brief Gets SCG Hsrun Bus Clock Divide Ratio
 *
 * This function gets the Hsrun Bus Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Hsrun Bus Clock Divide Ratio.
 */
static inline uint32_t SCG_GetHsrunBusClockDividerRatio(const SCG_Type * base)
{
    return ((base->VCCR & SCG_HCCR_DIVBUS_MASK) >> SCG_HCCR_DIVBUS_SHIFT);
}

/*!
 * @brief Gets SCG Hsrun Slow Clock Divide Ratio
 *
 * This function gets the Hsrun Slow Clock Divide Ratio.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Hsrun Slow Clock Divide Ratio.
 */
static inline uint32_t SCG_GetHsrunSlowClockDividerRatio(const SCG_Type * base)
{
    return ((base->VCCR & SCG_HCCR_DIVSLOW_MASK) >> SCG_HCCR_DIVSLOW_SHIFT);
}


/*!
 * @brief Sets SCG hsrun system clock
 *
 * This function sets the HSRUN clock control (system clock source, bus, core and slow dividers).
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base System clock configuration address.
 */
static inline void SCG_SetHsrunClockControl(SCG_Type * base, uint32_t source, uint32_t coreDivider, uint32_t busDivider, uint32_t slowDivider)
{
	uint32_t value = (uint32_t)(((source      << SCG_HCCR_SCS_SHIFT)     & SCG_HCCR_SCS_MASK)     |
								((coreDivider << SCG_HCCR_DIVCORE_SHIFT) & SCG_HCCR_DIVCORE_MASK) |
								((busDivider  << SCG_HCCR_DIVBUS_SHIFT)  & SCG_HCCR_DIVBUS_MASK)  |
								((slowDivider << SCG_HCCR_DIVSLOW_SHIFT) & SCG_HCCR_DIVSLOW_MASK) );

	base->HCCR = value;
}


/*!
 * @brief Gets the first asynchronous divider for FIRC.
 *
 * This function gets the first asynchronous divider for FIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return FIRC first asynchronous divider
 */
static inline uint32_t SCG_GetFircFirstAsyncDivider(const SCG_Type * base)
{
    return (base->FIRCDIV & SCG_FIRCDIV_FIRCDIV1_MASK) >> SCG_FIRCDIV_FIRCDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for FIRC.
 *
 * This function gets the second asynchronous divider for FIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return FIRC second asynchronous divider
 */
static inline uint32_t SCG_GetFircSecondAsyncDivider(const SCG_Type * base)
{
    return (base->FIRCDIV & SCG_FIRCDIV_FIRCDIV2_MASK) >> SCG_FIRCDIV_FIRCDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for FIRC.
 *
 * This function sets SCG asynchronous dividers for FIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
static inline void SCG_SetFircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_FIRCDIV_FIRCDIV1_SHIFT) & SCG_FIRCDIV_FIRCDIV1_MASK)     |
                                ((div2 << SCG_FIRCDIV_FIRCDIV2_SHIFT) & SCG_FIRCDIV_FIRCDIV2_MASK) );
    base->FIRCDIV = value;
}


/*!
 * @brief Gets the first asynchronous divider for SIRC.
 *
 * This function gets the first asynchronous divider for SIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SIRC first asynchronous divider
 */
static inline uint32_t SCG_GetSircFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SIRCDIV & SCG_SIRCDIV_SIRCDIV1_MASK) >> SCG_SIRCDIV_SIRCDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for SIRC.
 *
 * This function gets the second asynchronous divider for SIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SIRC second asynchronous divider
 */
static inline uint32_t SCG_GetSircSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SIRCDIV & SCG_SIRCDIV_SIRCDIV2_MASK) >> SCG_SIRCDIV_SIRCDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for SIRC.
 *
 * This function sets SCG asynchronous dividers for SIRC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
static inline void SCG_SetSircAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SIRCDIV_SIRCDIV1_SHIFT) & SCG_SIRCDIV_SIRCDIV1_MASK)     |
                                ((div2 << SCG_SIRCDIV_SIRCDIV2_SHIFT) & SCG_SIRCDIV_SIRCDIV2_MASK) );
    base->SIRCDIV = value;
}



/*!
 * @brief Gets the first asynchronous divider for SOSC.
 *
 * This function gets the first asynchronous divider for SOSC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SOSC first asynchronous divider
 */
static inline uint32_t SCG_GetSoscFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SOSCDIV & SCG_SOSCDIV_SOSCDIV1_MASK) >> SCG_SOSCDIV_SOSCDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for SOSC.
 *
 * This function gets the second asynchronous divider for SOSC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SOSC second asynchronous divider
 */
static inline uint32_t SCG_GetSoscSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SOSCDIV & SCG_SOSCDIV_SOSCDIV2_MASK) >> SCG_SOSCDIV_SOSCDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for SOSC.
 *
 * This function sets SCG asynchronous dividers for SOSC.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
static inline void SCG_SetSoscAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SOSCDIV_SOSCDIV1_SHIFT) & SCG_SOSCDIV_SOSCDIV1_MASK)     |
                                ((div2 << SCG_SOSCDIV_SOSCDIV2_SHIFT) & SCG_SOSCDIV_SOSCDIV2_MASK) );
    base->SOSCDIV = value;
}

/*!
 * @brief Gets the first asynchronous divider for SPLL.
 *
 * This function gets the first asynchronous divider for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SPLL first asynchronous divider
 */
static inline uint32_t SCG_GetSpllFirstAsyncDivider(const SCG_Type * base)
{
    return (base->SPLLDIV & SCG_SPLLDIV_SPLLDIV1_MASK) >> SCG_SPLLDIV_SPLLDIV1_SHIFT;
}

/*!
 * @brief Gets the second asynchronous divider for SPLL.
 *
 * This function gets the second asynchronous divider for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return SPLL second asynchronous divider
 */
static inline uint32_t SCG_GetSpllSecondAsyncDivider(const SCG_Type * base)
{
    return (base->SPLLDIV & SCG_SPLLDIV_SPLLDIV2_MASK) >> SCG_SPLLDIV_SPLLDIV2_SHIFT;
}


/*!
 * @brief Sets SCG asynchronous dividers for SPLL.
 *
 * This function sets SCG asynchronous dividers for SPLL.
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] base Asynchronous first divider
 * @param[in] base Asynchronous second divider
 */
static inline void SCG_SetSpllAsyncConfig(SCG_Type * base, uint32_t div1, uint32_t div2)
{
    uint32_t value = (uint32_t)(((div1 << SCG_SPLLDIV_SPLLDIV1_SHIFT) & SCG_SPLLDIV_SPLLDIV1_MASK)     |
                                ((div2 << SCG_SPLLDIV_SPLLDIV2_SHIFT) & SCG_SPLLDIV_SPLLDIV2_MASK) );
    base->SPLLDIV = value;
}


/*!
 * @brief Set SCG ClockOut source select
 *
 * This function sets the SCG ClockOut source
 *
 * @param[in] base Register base address for the SCG instance.
 * @param[in] source used for ClockOut
 * Implements SCG_SetClockoutSourceSel_Activity
 */
static inline void SCG_SetClockoutSourceSel(SCG_Type * base, uint32_t source)
{
	uint32_t regValue;

    regValue = base->CLKOUTCNFG;
    regValue &= ~(SCG_CLKOUTCNFG_CLKOUTSEL_MASK);
    regValue |= SCG_CLKOUTCNFG_CLKOUTSEL(source);
    base->CLKOUTCNFG = regValue;
}

/* @} */

/*!
 * @name System OSC Clock.
 * @{
 */

/*!
 * @brief Get SCG system OSC clock frequency (SYSOSC).
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Clock frequency, if clock is invalid, return 0.
 */
uint32_t SCG_GetSysOscFreq(const SCG_Type * base);


/* @} */

/*!
 * @name Slow IRC Clock.
 * @{
 */


/*!
 * @brief Get SCG SIRC clock frequency.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return Clock frequency, if clock is invalid, return 0.
 */
uint32_t SCG_GetSircFreq(const SCG_Type * base);

/* @} */

/*!
 * @name Fast IRC Clock.
 * @{
 */


/*!
 * @brief Get SCG FIRC clock frequency.
 *
 * @param[in] base Register base address for the SCG instance.
 * @return  Clock frequency, if clock is invalid, return 0.
 */
uint32_t SCG_GetFircFreq(const SCG_Type * base);


/*!
 * @brief Gets sirc system clock mode status
 *
 * This function checks whether SIRC is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sirc system clock mode status
 *        - false : SIRC is not the system clock source
 *        - true : SIRC is the system clock source
 */
static inline bool SCG_GetSircSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SIRCCSR;
    regValue = (regValue & SCG_SIRCCSR_SIRCSEL_MASK) >> SCG_SIRCCSR_SIRCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets sirc clock status
 * This function checks whether SIRC is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sirc  clock status
 *        - false : SIRC is not enabled or clock is not valid
 *        - true  : SIRC is enabled and clock is valid
 */
static inline bool SCG_GetSircStatus(const SCG_Type* const base)
{
    return (((base->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK) >> SCG_SIRCCSR_SIRCVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets sirc clock range
 *
 * @param[in] base        scg base pointer
 *
 * @return  sirc  range value
 */
static inline uint32_t SCG_GetSircRange(const SCG_Type* const base)
{
    return ((base->SIRCCFG & SCG_SIRCCFG_RANGE_MASK) >> SCG_SIRCCFG_RANGE_SHIFT);
}

/*!
 * @brief Clears SIRC lock register
 *
 * @param[in] base        scg base pointer
 */
static inline void SCG_ClearSircLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->SIRCCSR &= (uint32_t)(~(SCG_SIRCCSR_LK_MASK));
}


/*!
 * @brief Clears SIRC control register
 *
 * @param[in] base        scg base pointer
 */
static inline void SCG_ClearSircControl(SCG_Type* base)
{
    /* Clear configuration. */
    base->SIRCCSR = 0U;
}


/*!
 * @brief Sets SIRC configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] range       sirc range value
 */
static inline void SCG_SetSircConfiguration(SCG_Type* base, uint8_t range)
{
    /* Set PLL configuration: frequency range */
    base->SIRCCFG = SCG_SIRCCFG_RANGE(range);
}

/*!
 * @brief Sets SIRC control register
 *
 * @param[in] base                scg base pointer
 * @param[in] enableInStop        enable in stop modes
 * @param[in] enableInLowPower    enable in very low power modes
 * @param[in] lockMode            control register can be written or not
 */
static inline void SCG_SetSircControl(SCG_Type* base, bool enableInStop, bool enableInLowPower, bool lockMode)
{
    uint32_t value = SCG_SIRCCSR_SIRCEN(1U)                                  |
                     SCG_SIRCCSR_SIRCSTEN(((enableInStop)     ? 1UL : 0UL )) |
                     SCG_SIRCCSR_SIRCLPEN(((enableInLowPower) ? 1UL : 0UL )) |
                     SCG_SIRCCSR_LK((lockMode) ? 1UL : 0UL);

    base->SIRCCSR = value;
}


/*!
 * @brief Gets firc system clock mode status
 *
 * This function checks whether FIRC is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  firc system clock mode status
 *        - false : FIRC is not the system clock source
 *        - true : FIRC is the system clock source
 */
static inline bool SCG_GetFircSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->FIRCCSR;
    regValue = (regValue & SCG_FIRCCSR_FIRCSEL_MASK) >> SCG_FIRCCSR_FIRCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets firc clock status
 * This function checks whether FIRC is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  firc  clock status
 *        - false : FIRC is not enabled or clock is not valid
 *        - true  : FIRC is enabled and clock is valid
 */
static inline bool SCG_GetFircStatus(const SCG_Type* const base)
{
    return (((base->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK) >> SCG_FIRCCSR_FIRCVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets firc clock range
 *
 * @param[in] base        scg base pointer
 *
 * @return  firc  frequency range value
 */
static inline uint32_t SCG_GetFircRange(const SCG_Type* const base)
{
    return ((base->FIRCCFG & SCG_FIRCCFG_RANGE_MASK) >> SCG_FIRCCFG_RANGE_SHIFT);
}

/*!
 * @brief Clears FIRC lock register
 *
 * This function clears FIRC lock.
 *
 * @param[in] base        scg base pointer
 *
 */
static inline void SCG_ClearFircLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->FIRCCSR &= (uint32_t)(~(SCG_FIRCCSR_LK_MASK));
}


/*!
 * @brief Clears FIRC control register
 *
 * @param[in] base        scg base pointer
 *
 */
static inline void SCG_ClearFircControl(SCG_Type* base)
{
    /* Disable monitor, disable clock and clear error. */
    base->FIRCCSR = SCG_FIRCCSR_FIRCERR_MASK;
}


/*!
 * @brief Sets FIRC configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] range       firc range value
 */
static inline void SCG_SetFircConfiguration(SCG_Type* base, uint8_t range)
{
    /* Set PLL configuration: frequency range */
    base->FIRCCFG = SCG_FIRCCFG_RANGE(range);
}

/*!
 * @brief Sets FIRC control register
 *
 * @param[in] base        scg base pointer
 * @param[in] monitorMode clock monitor enablement
 * @param[in] lockMode    control register can be written or not
 */
static inline void SCG_SetFircControl(SCG_Type* base, bool regulator, bool lockMode)
{
    uint32_t value = SCG_FIRCCSR_FIRCEN(1U)                             |
                     SCG_FIRCCSR_FIRCREGOFF((regulator) ? 1UL : 0UL)    |
                     SCG_FIRCCSR_LK((lockMode) ? 1UL : 0UL);

    base->FIRCCSR = value;
}


/*!
 * @brief Gets sosc system clock mode status
 *
 * This function checks whether SOSC is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sosc system clock mode status
 *        - false : SOSC is not the system clock source
 *        - true : SOSC is the system clock source
 */
static inline bool SCG_GetSoscSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SOSCCSR;
    regValue = (regValue & SCG_SOSCCSR_SOSCSEL_MASK) >> SCG_SOSCCSR_SOSCSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets sosc clock status
 * This function checks whether SOSC is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  sosc  clock status
 *        - false : SOSC is not enabled or clock is not valid
 *        - true  : SOSC is enabled and clock is valid
 */
static inline bool SCG_GetSoscStatus(const SCG_Type* const base)
{
    return (((base->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK) >> SCG_SOSCCSR_SOSCVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Clears SOSC lock register
 *
 * @param[in] base        scg base pointer
 */
static inline void SCG_ClearSoscLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->SOSCCSR &= (uint32_t)(~(SCG_SOSCCSR_LK_MASK));
}


/*!
 * @brief Clears SOSC control register
 *
 * @param[in] base        scg base pointer
 */
static inline void SCG_ClearSoscControl(SCG_Type* base)
{
    /* Disable monitor, disable clock and clear error. */
    base->SOSCCSR = SCG_SOSCCSR_SOSCERR_MASK;
}

/*!
 * @brief Sets SOSC configuration register
 *
 * @param[in] base        scg base pointer
 */


/*!
 * @brief Sets SOSC configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] range       sosc range
 * @param[in] gain        sosc gain
 * @param[in] extRef      external reference
 */
static inline void SCG_SetSoscConfiguration(SCG_Type* base, uint32_t range, uint32_t gain, uint32_t extRef)
{
    /* Set SOSC configuration. */
    base->SOSCCFG = SCG_SOSCCFG_RANGE(range)        |
                    SCG_SOSCCFG_HGO(gain)           |
                    SCG_SOSCCFG_EREFS(extRef);
}

/*!
 * @brief Sets SOSC control register
 *
 * @param[in] base        scg base pointer
 * @param[in] monitorMode clock monitor enablement
 * @param[in] resetMode   clock monitor reset enablement
 * @param[in] lockMode    control register can be written or not
 */
static inline void SCG_SetSoscControl(SCG_Type* base, bool monitorMode, bool resetMode, bool lockMode)
{
    uint32_t value = SCG_SOSCCSR_SOSCEN(1U)                        |
    		         SCG_SOSCCSR_SOSCCM((monitorMode) ? 1UL : 0UL) |
					 SCG_SOSCCSR_SOSCCMRE((resetMode) ? 1UL : 0UL) |
                     SCG_SOSCCSR_LK((lockMode) ? 1UL : 0UL);

    base->SOSCCSR = value;
}


/*!
 * @brief Gets spll system clock mode status
 *
 * This function checks whether SPLL is used as system clock source.
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll system clock mode status
 *        - false : SPLL is not the system clock source
 *        - true : SPLL is the system clock source
 */
static inline bool SCG_GetSpllSystemClockMode(const SCG_Type* const base)
{
    uint32_t regValue = (uint32_t)base->SPLLCSR;
    regValue = (regValue & SCG_SPLLCSR_SPLLSEL_MASK) >> SCG_SPLLCSR_SPLLSEL_SHIFT;
    return (regValue == 0U) ? false : true;
}

/*!
 * @brief Gets spll clock status
 * This function checks whether SPLL is enabled and output clock is valid.
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll  clock status
 *        - false : SPLL is not enabled or clock is not valid
 *        - true  : SPLL is enabled and clock is valid
 */
static inline bool SCG_GetSpllStatus(const SCG_Type* const base)
{
    return (((base->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK) >> SCG_SPLLCSR_SPLLVLD_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets spll predivider
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll predivider value
 */
static inline uint32_t SCG_GetSpllPredivider(const SCG_Type* const base)
{
    return ((base->SPLLCFG & SCG_SPLLCFG_PREDIV_MASK) >> SCG_SPLLCFG_PREDIV_SHIFT);
}

/*!
 * @brief Gets spll multiplier
 *
 * @param[in] base        scg base pointer
 *
 * @return  spll multiplier value
 */
static inline uint32_t SCG_GetSpllMultiplier(const SCG_Type* const base)
{
    return ((base->SPLLCFG & SCG_SPLLCFG_MULT_MASK) >> SCG_SPLLCFG_MULT_SHIFT);
}

/*!
 * @brief Clears SPLL lock register
 *
 * This function clears SPLL lock.
 *
 * @param[in] base        scg base pointer
 *
 */
static inline void SCG_ClearSpllLock(SCG_Type*  base)
{
    /* Clear LK bit field */
    base->SPLLCSR &= (uint32_t)(~(SCG_SPLLCSR_LK_MASK));
}


/*!
 * @brief Clears SPLL control register
 *
 * @param[in] base        scg base pointer
 *
 */
static inline void SCG_ClearSpllControl(SCG_Type* base)
{
    /* Disable monitor, disable clock and clear error. */
    base->SPLLCSR = SCG_SPLLCSR_SPLLERR_MASK;
}

/*!
 * @brief Sets SPLL configuration register
 *
 * @param[in] base        scg base pointer
 * @param[in] divider     spll predivider value
 * @param[in] multiplier  spll multiplier value
 */
static inline void SCG_SetSpllConfiguration(SCG_Type* base, uint8_t divider, uint8_t multiplier)
{
    /* Set PLL configuration. */
    base->SPLLCFG = SCG_SPLLCFG_PREDIV(divider)  |
                    SCG_SPLLCFG_MULT(multiplier);
}

/*!
 * @brief Sets SPLL control register
 *
 * @param[in] base        scg base pointer
 * @param[in] monitorMode clock monitor enablement
 * @param[in] resetMode   clock monitor reset enablement
 * @param[in] lockMode    control register can be written or not
 */
static inline void SCG_SetSpllControl(SCG_Type* base, bool monitorMode, bool resetMode, bool lockMode)
{
    uint32_t value = SCG_SPLLCSR_SPLLEN(1U)                        |
    		         SCG_SPLLCSR_SPLLCM((monitorMode) ? 1UL : 0UL) |
					 SCG_SPLLCSR_SPLLCMRE((resetMode) ? 1UL : 0UL) |
                     SCG_SPLLCSR_LK((lockMode) ? 1UL : 0UL);

    base->SPLLCSR = value;
}



#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* SCG_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
