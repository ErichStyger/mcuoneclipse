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

#if !defined(SIM_HW_ACCESS_H)
#define SIM_HW_ACCESS_H

#include "device_registers.h"
#include <stdbool.h>
#include <stddef.h>

/*!
 * @file sim_hw_access.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 */

/*!
 * @ingroup sim_hw_access
 * @defgroup sim_hw_access
 * @{
 */


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


/*!
 * @brief Get the clock selection of RTCCLKSEL.
 *
 * This function gets the clock selection of RTCCLKSEL.
 *
 * @param[in] base Base address for current SIM instance.
 * @return Current selection.
 */
static inline uint32_t SIM_GetRtcClkSrc(const SIM_Type * base)
{
    return ((base->LPOCLKS & SIM_LPOCLKS_RTCCLKSEL_MASK) >> SIM_LPOCLKS_RTCCLKSEL_SHIFT);
}


/*!
 * @brief Set the clock selection of LPOCLKSEL.
 *
 * This function sets the clock selection of LPOCLKSEL.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] setting The value to set.
 * @note This function ignores initialize member
 */
static inline void SIM_SetLpoClocks(SIM_Type* base, bool enableLpo1k, bool enableLpo32k, uint32_t sourceLpoClk, uint32_t sourceRtcClk)
{
    uint32_t regValue = base->LPOCLKS;

    regValue &= ~( SIM_LPOCLKS_LPO1KCLKEN_MASK  |
                   SIM_LPOCLKS_LPO32KCLKEN_MASK |
                   SIM_LPOCLKS_LPOCLKSEL_MASK   |
                   SIM_LPOCLKS_RTCCLKSEL_MASK   );

    regValue |= SIM_LPOCLKS_LPO1KCLKEN(enableLpo1k ? 1UL : 0UL);
    regValue |= SIM_LPOCLKS_LPO32KCLKEN(enableLpo32k ? 1UL : 0UL);
    regValue |= SIM_LPOCLKS_LPOCLKSEL(sourceLpoClk);
    regValue |= SIM_LPOCLKS_RTCCLKSEL(sourceRtcClk);

    /* Write value to register. */
    base->LPOCLKS = regValue;
}

/*!
 * @brief Set the EIM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function configures the EIM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] EIM clock gate enable setting
 */
static inline void SIM_SetEimClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCEIM_MASK));
    regValue |= SIM_PLATCGC_CGCEIM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

/*!
 * @brief Gets the EIM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function gets the EIM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return EIM Clock Gating
 */
static inline bool SIM_GetEimClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCEIM_MASK) >> SIM_PLATCGC_CGCEIM_SHIFT;
    return (regValue != 0U) ? true : false;
}

/*!
 * @brief Set the ERM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function configures the ERM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable ERM clock gate enable setting
 */
static inline void SIM_SetErmClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCERM_MASK));
    regValue |= SIM_PLATCGC_CGCERM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}



/*!
 * @brief Gets the ERM Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function gets the ERM Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return ERM Clock Gating
 */
static inline bool SIM_GetErmClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCERM_MASK) >> SIM_PLATCGC_CGCERM_SHIFT;
    return (regValue != 0U) ? true : false;
}

/*!
 * @brief Set the DMA Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function configures the DMA Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable DMA clock gate enable setting
 */
static inline void SIM_SetDmaClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCDMA_MASK));
    regValue |= SIM_PLATCGC_CGCDMA(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}



/*!
 * @brief Gets the DMA Clock Gate from the Platform Clock Gating Control Register.
 *
 * This function gets the DMA Clock Gate in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return DMA Clock Gating
 */
static inline bool SIM_GetDmaClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCDMA_MASK) >> SIM_PLATCGC_CGCDMA_SHIFT;
    return (regValue != 0U) ? true : false;
}


/*!
 * @brief Configure the MPU Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function configures the MPU Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable MPU clock gate enable setting
 */
static inline void SIM_SetMpuClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCMPU_MASK));
    regValue |= SIM_PLATCGC_CGCMPU(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

/*!
 * @brief Gets the MPU Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function gets the MPU Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return MPU Clock Gating
 */
static inline bool SIM_GetMpuClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCMPU_MASK) >> SIM_PLATCGC_CGCMPU_SHIFT;
    return (regValue != 0U) ? true : false;
}

/*!
 * @brief Configure the MSCM Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function configures the MSCM Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] enable MPU clock gate enable setting
 */
static inline void SIM_SetMscmClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue &= (uint32_t)(~(SIM_PLATCGC_CGCMSCM_MASK));
    regValue |= SIM_PLATCGC_CGCMSCM(enable ? 1UL : 0UL);
    base->PLATCGC = (uint32_t)regValue;
}

/*!
 * @brief Gets the MSCM Clock Gating from the Platform Clock Gating Control Register.
 *
 * This function gets the MSCM Clock Gating in the Platform Clock Gating Control Register.
 *
 * @param[in] base Base address for current SIM instance.
 * @return MSCM Clock Gating
 */
static inline bool SIM_GetMscmClockGate(const SIM_Type * base)
{
    uint32_t regValue = (uint32_t)base->PLATCGC;
    regValue = (regValue & SIM_PLATCGC_CGCMSCM_MASK) >> SIM_PLATCGC_CGCMSCM_SHIFT;
    return (regValue != 0U) ? true : false;
}

#if defined(QuadSPI_INSTANCE_COUNT)
/*!
 * @brief Configure the QuadSPI Internal Reference Clock Gating
 *
 * This function configures the QuadSPI Internal Reference Clock Gating.
 *
 * @param[in] base Base address for current SIM instance.
 * @param[in] configures QuadSPI Internal Reference Clock Gating
 */
static inline void SIM_SetQspiIntRefClockGate(SIM_Type* base, bool enable)
{
    uint32_t regValue = (uint32_t)base->MISCTRL0;
    regValue &= (uint32_t)(~(SIM_MISCTRL0_QSPI_CLK_SEL_MASK));
    regValue |= SIM_MISCTRL0_QSPI_CLK_SEL(enable ? 1UL : 0UL);
    base->MISCTRL0 = (uint32_t)regValue;
}
#endif


/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm0ExternalClkPinMode
 * Description   : Get FlexTimer 0 external clock pin select setting
 * This function will get FlexTimer 0 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm0ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM0CLKSEL_MASK) >> SIM_FTMOPT0_FTM0CLKSEL_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm1ExternalClkPinMode
 * Description   : Get FlexTimer 1 external clock pin select setting
 * This function will get FlexTimer 1 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm1ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM1CLKSEL_MASK) >> SIM_FTMOPT0_FTM1CLKSEL_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm2ExternalClkPinMode
 * Description   : Get FlexTimer 2 external clock pin select setting
 * This function will get FlexTimer 2 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm2ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM2CLKSEL_MASK) >> SIM_FTMOPT0_FTM2CLKSEL_SHIFT;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm3ExternalClkPinMode
 * Description   : Get FlexTimer 3 external clock pin select setting
 * This function will get FlexTimer 3 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm3ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM3CLKSEL_MASK) >> SIM_FTMOPT0_FTM3CLKSEL_SHIFT;
}

#if FTM_INSTANCE_COUNT > 4U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm4ExternalClkPinMode
 * Description   : Get FlexTimer 4 external clock pin select setting
 * This function will get FlexTimer 4 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm4ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM4CLKSEL_MASK) >> SIM_FTMOPT0_FTM4CLKSEL_SHIFT;
}
#endif

#if FTM_INSTANCE_COUNT > 5U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm5ExternalClkPinMode
 * Description   : Get FlexTimer 5 external clock pin select setting
 * This function will get FlexTimer 5 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm5ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM5CLKSEL_MASK) >> SIM_FTMOPT0_FTM5CLKSEL_SHIFT;
}
#endif

#if FTM_INSTANCE_COUNT > 6U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm6ExternalClkPinMode
 * Description   : Get FlexTimer 6 external clock pin select setting
 * This function will get FlexTimer 6 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm6ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM6CLKSEL_MASK) >> SIM_FTMOPT0_FTM6CLKSEL_SHIFT;
}
#endif


#if FTM_INSTANCE_COUNT > 7U
/*FUNCTION**********************************************************************
 *
 * Function Name : SIM_GetFtm7ExternalClkPinMode
 * Description   : Get FlexTimer 7 external clock pin select setting
 * This function will get FlexTimer 7 external clock pin select setting.
 *END**************************************************************************/
static inline uint32_t SIM_GetFtm7ExternalClkPinMode(const SIM_Type * base)
{
    return (base->FTMOPT0 & SIM_FTMOPT0_FTM7CLKSEL_MASK) >> SIM_FTMOPT0_FTM7CLKSEL_SHIFT;
}
#endif

/*FUNCTION*********************************************************************
 *
 * Function Name : SIM_GetLpo32KStatus
 * Description   : Get SIM LPO 32KHz clock gating status (LPO_32K_CLOCK).
 *END*************************************************************************/
static inline bool SIM_GetLpo32KStatus(const SIM_Type * base)
{
    return (((base->LPOCLKS & SIM_LPOCLKS_LPO32KCLKEN_MASK) >> SIM_LPOCLKS_LPO32KCLKEN_SHIFT) != 0U) ? true : false;
}

/*FUNCTION*********************************************************************
 *
 * Function Name : SIM_GetLpo1KStatus
 * Description   : Get SIM LPO 1KHz clock gating status (LPO_1K_CLOCK).
 *END*************************************************************************/
static inline bool SIM_GetLpo1KStatus(const SIM_Type * base)
{
    return (((base->LPOCLKS & SIM_LPOCLKS_LPO1KCLKEN_MASK) >> SIM_LPOCLKS_LPO1KCLKEN_SHIFT) != 0U) ? true : false;
}

/*!
 * @brief Gets the LPO selector value
 *
 * This function gets the LPO selector value
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout status
 */
static inline uint32_t SIM_GetLpoClkSelectorValue(const SIM_Type * base)
{
    return ((base->LPOCLKS & SIM_LPOCLKS_LPOCLKSEL_MASK) >> SIM_LPOCLKS_LPOCLKSEL_SHIFT);
}

/*!
 * @brief Gets the clock out status
 *
 * This function gets the clock out status (enabled or disabled)
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout status
 */
static inline bool SIM_GetClockoutStatus(const SIM_Type * base)
{
    return (((base->CHIPCTL & SIM_CHIPCTL_CLKOUTEN_MASK) >> SIM_CHIPCTL_CLKOUTEN_SHIFT) == 0U) ? false : true;
}

/*!
 * @brief Gets the clock out divider value
 *
 * This function gets the clock out divider value
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout divider
 */
static inline uint32_t SIM_GetClockoutDividerValue(const SIM_Type * base)
{
    return ((base->CHIPCTL & SIM_CHIPCTL_CLKOUTDIV_MASK) >> SIM_CHIPCTL_CLKOUTDIV_SHIFT);
}

/*!
 * @brief Gets the clock out source
 *
 * This function gets the clock out source
 *
 * @param[in] base Base address for current SIM instance.
 * @return clockout source
 */
static inline uint32_t SIM_GetClockoutSelectorValue(const SIM_Type * base)
{
    return ((base->CHIPCTL & SIM_CHIPCTL_CLKOUTSEL_MASK) >> SIM_CHIPCTL_CLKOUTSEL_SHIFT);
}

/*!
 * @brief Sets clockout
 *
 * @param[in] base        sim base pointer
 * @param[in] source      clock source
 * @param[in] divider     clock divider
 */
static inline void SIM_SetClockout(SIM_Type* base, bool enable, uint32_t source, uint32_t divider)
{
    uint32_t regValue = base->CHIPCTL;

    regValue &= ~( SIM_CHIPCTL_CLKOUTEN_MASK  |
    		       SIM_CHIPCTL_CLKOUTDIV_MASK |
			       SIM_CHIPCTL_CLKOUTSEL_MASK );

    regValue |= SIM_CHIPCTL_CLKOUTEN(enable ? 1UL : 0UL);
    regValue |= SIM_CHIPCTL_CLKOUTSEL(source);
    regValue |= SIM_CHIPCTL_CLKOUTDIV(divider);

    base->CHIPCTL = regValue;
}

/*!
 * @brief Configure clock trace source
 *
 * @param[in] base        sim base pointer
 * @param[in] source      clock trace source
 */
static inline void SIM_SetTraceClockSource(SIM_Type* base, uint32_t clTraceSrc)
{
    uint32_t regValue;

    /* Configure trace source. */
    regValue = (uint32_t)base->CHIPCTL;
    regValue &= (uint32_t)(~(SIM_CHIPCTL_TRACECLK_SEL_MASK));
    regValue |= SIM_CHIPCTL_TRACECLK_SEL(clTraceSrc);
    base->CHIPCTL = (uint32_t)regValue;
}

/*!
 * @brief Clears SIM Debug Trace configuration.
 *
 * This function disables the SIM Debug Trace clock.
 *
 * @param[in] base Register base address for the SIM instance.
 */
static inline void SIM_ClearTraceClockConfig(SIM_Type * base)
{
    /* Disable divider. */
    base->CLKDIV4 &= 0U;
}

/*!
 * @brief Set SIM Debug Trace configuration.
 *
 * This function disables the SIM Debug Trace clock.
 *
 * @param[in] base        sim base pointer
 * @param[in] source      clock trace source
 */
static inline void SIM_SetTraceClockConfig(SIM_Type * base, bool enable, uint32_t divider, uint32_t multiplier)
{
    base->CLKDIV4 = SIM_CLKDIV4_TRACEDIVEN(enable ? 1UL : 0UL) |
                    SIM_CLKDIV4_TRACEDIV(divider)              |
                    SIM_CLKDIV4_TRACEFRAC(multiplier);
}



#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* SIM_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/

