/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
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

#if !defined(__FSL_CLOCK_KV58F24_H__)
#define __FSL_CLOCK_KV58F24_H__

#include "fsl_mcg_hal.h"
#include "fsl_mcg_hal_modes.h"
#include "fsl_osc_hal.h"

/*! @addtogroup clock_manager_kv58f24*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief ENET external clock source count. */
#define ENET_EXT_CLK_COUNT 1  /* ENET external clock source count. */
/*! @brief FTM external clock source count.  */
#define FTM_EXT_CLK_COUNT  2  /* FTM external clock source count.  */

/*! @brief ENET external clock frequency(ENET_1588_CLKIN)  */
extern uint32_t g_enet1588ClkInFreq[ENET_EXT_CLK_COUNT];  /* ENET external clock frequency (ENET_1588_CLKIN) */
/*! @brief FTM external clock frequency(FTM_CLK).  */
extern uint32_t g_ftmClkFreq[FTM_EXT_CLK_COUNT];          /* FTM_CLK          */

/*!@brief SIM configuration structure for dynamic clock setting. */
typedef struct SimConfig
{
    clock_er32k_src_t  er32kSrc;   /*!< ERCLK32K source selection.   */
    uint8_t outdiv1, outdiv2, outdiv3, outdiv4; /*!< OUTDIV setting. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_config_kv58f24_t;
#else
} sim_config_t;
#endif

/*! @} */
/*! @addtogroup clock_manager*/
/*! @{*/
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/


/*!
 * @brief Sets the clock out divider1 setting(OUTDIV1).
 *
 * This function sets divide value OUTDIV1.
 *
 * @param outdiv1      Outdivider1 setting
 */
static inline void CLOCK_SYS_SetOutDiv1(uint8_t outdiv1)
{
    CLOCK_HAL_SetOutDiv1(SIM, outdiv1);
}

/*!
 * @brief Gets the clock out divider1 setting(OUTDIV1).
 *
 * This function gets divide value OUTDIV1.
 *
 * @return Outdivider1 setting
 */
static inline uint8_t CLOCK_SYS_GetOutDiv1(void)
{
    return CLOCK_HAL_GetOutDiv1(SIM);
}

/*!
 * @brief Sets the clock out divider2 setting(OUTDIV2).
 *
 * This function sets divide value OUTDIV2.
 *
 * @param outdiv2      Outdivider2 setting
 */
static inline void CLOCK_SYS_SetOutDiv2(uint8_t outdiv2)
{
    CLOCK_HAL_SetOutDiv2(SIM, outdiv2);
}

/*!
 * @brief Gets the clock out divider2 setting(OUTDIV2).
 *
 * This function gets divide value OUTDIV2.
 *
 * @return Outdivider2 setting
 */
static inline uint8_t CLOCK_SYS_GetOutDiv2(void)
{
    return CLOCK_HAL_GetOutDiv2(SIM);
}

/*!
 * @brief Sets the clock out divider4 setting(OUTDIV4).
 *
 * This function sets divide value OUTDIV4.
 *
 * @param outdiv4      Outdivider4 setting
 */
static inline void CLOCK_SYS_SetOutDiv4(uint8_t outdiv4)
{
    CLOCK_HAL_SetOutDiv4(SIM, outdiv4);
}

/*!
 * @brief Gets the clock out divider4 setting(OUTDIV4).
 *
 * This function gets divide value OUTDIV4.
 *
 * @return Outdivider4 setting
 */
static inline uint8_t CLOCK_SYS_GetOutDiv4(void)
{
    return CLOCK_HAL_GetOutDiv4(SIM);
}

/*!
 * @brief Sets the clock out dividers setting.
 *
 * This function sets the setting for all clock out dividers at the same time.
 *
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
static inline void CLOCK_SYS_SetOutDiv(uint8_t outdiv1, uint8_t outdiv2,
                                       uint8_t outdiv3, uint8_t outdiv4)
{
    CLOCK_HAL_SetOutDiv(SIM, outdiv1, outdiv2, outdiv3, outdiv4);
}

/*!
 * @brief Gets the fast peripheral clock frequency.
 *
 * This function gets the fast peripheral clock frequency.
 *
 * @return Current clock frequency.
 */
uint32_t CLOCK_SYS_GetFastPeripheralClockFreq(void);

/*!
 * @brief Get the MCGPLLCLK/MCGFLLCLK/IRC48MCLK clock frequency.
 *
 * This function gets the frequency of the MCGPLLCLK/MCGFLLCLK/IRC48MCLK.
 *
 * @return Current clock frequency.
 */
uint32_t CLOCK_SYS_GetPllFllClockFreq(void);

/*!
 * @brief Gets the MCGFFCLK clock frequency.
 *
 * This function gets the MCG fixed frequency clock (MCGFFCLK) frequency.
 *
 * @return Current clock frequency.
 */
static inline uint32_t CLOCK_SYS_GetFixedFreqClockFreq(void)
{
    return CLOCK_HAL_GetFixedFreqClk(MCG);
}

/*!
 * @brief Get internal reference clock frequency.
 *
 * This function gets the internal reference clock frequency.
 *
 * @return Current clock frequency.
 */
static inline uint32_t CLOCK_SYS_GetInternalRefClockFreq(void)
{
    return CLOCK_HAL_GetInternalRefClk(MCG);
}

/*!
 * @brief Gets the external reference 32k clock frequency.
 *
 * This function gets the external reference (ERCLK32K) clock frequency.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetExternalRefClock32kFreq(void);

/*!
 * @brief Set the clock selecton of ERCLK32K.
 *
 * This function sets the clock selecton of ERCLK32K.
 *
 * @param src clock source.
 */
static inline void CLOCK_SYS_SetExternalRefClock32kSrc(clock_er32k_src_t src)
{
    CLOCK_HAL_SetExternalRefClock32kSrc(SIM, src);
}

/*!
 * @brief Get the clock selecton of ERCLK32K.
 *
 * This function gets the clock selecton of ERCLK32K.
 *
 * @return Current selection.
 */
static inline clock_er32k_src_t CLOCK_SYS_GetExternalRefClock32kSrc(void)
{
    return CLOCK_HAL_GetExternalRefClock32kSrc(SIM);
}

/*!
 * @brief Gets the OSC0ERCLK frequency.
 *
 * This function gets the OSC0 external reference frequency.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockFreq(void);

/*!
 * @brief Gets the OSC0ERCLK_UNDIV frequency.
 *
 * This function gets the undivided OSC0 external reference frequency.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockUndivFreq(void);

/*!
 * @brief Get flexbus clock frequency.
 *
 * This function gets the flexbus clock frequency.
 *
 * @return Current flexbus clock frequency.
 */
uint32_t CLOCK_SYS_GetFlexbusFreq(void);

/*!
 * @brief Gets the watch dog clock frequency.
 *
 * This function gets the watch dog clock frequency.
 *
 * @param instance module device instance
 * @param wdogSrc  watch dog clock source selection, WDOG_STCTRLH[CLKSRC].
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetWdogFreq(uint32_t instance, clock_wdog_src_t wdogSrc);

/*!
 * @brief Gets the debug trace clock source.
 *
 * This function gets the debug trace clock source.
 * @param instance module device instance
 *
 * @return Current source.
 */
static inline clock_trace_src_t CLOCK_SYS_GetTraceSrc(uint32_t instance)
{
    return CLOCK_HAL_GetTraceClkSrc(SIM);
}

/*!
 * @brief Sets the debug trace clock source.
 *
 * This function sets the debug trace clock source.
 * @param instance module device instance.
 * @param src   debug trace clock source.
 */
static inline void CLOCK_SYS_SetTraceSrc(uint32_t instance, clock_trace_src_t src)
{
    CLOCK_HAL_SetTraceClkSrc(SIM, src);
}

/*!
 * @brief Gets the debug trace clock frequency.
 *
 * This function gets the debug trace clock frequency.
 * @param instance module device instance
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetTraceFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for DMA module.
 *
 * This function gets the clock frequence for DMA module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetDmaFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for DMAMUX module.
 *
 * This function gets the clock frequence for DMAMUX module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetDmamuxFreq(uint32_t instance);

/*!
 * @brief Gets ethernet RMII clock source.
 *
 * This function gets the ethernet RMII clock source.
 *
 * @param instance module device instance
 *
 * @return Current source.
 */
static inline clock_rmii_src_t CLOCK_SYS_GetEnetRmiiSrc(uint32_t instance)
{
    return CLOCK_HAL_GetRmiiSrc(SIM, instance);
}

/*!
 * @brief Sets ethernet RMII clock source.
 *
 * This function sets the ethernet RMII clock source.
 *
 * @param instance module device instance.
 * @param rmiiSrc  RMII clock source.
 */
static inline void CLOCK_SYS_SetEnetRmiiSrc(uint32_t instance, clock_rmii_src_t rmiiSrc)
{
    CLOCK_HAL_SetRmiiSrc(SIM, instance, rmiiSrc);
}

/*!
 * @brief Gets ethernet RMII clock frequency.
 *
 * This function gets the ethernet RMII clock frequency.
 *
 * @param instance module device instance
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetEnetRmiiFreq(uint32_t instance);

/*!
 * @brief Gets ethernet timestamp clock frequency.
 *
 * This function gets the ethernet timestamp clock frequency.
 *
 * @param instance module device instance
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetEnetTimeStampFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for EWM module.
 *
 * This function gets the clock frequence for EWM module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetEwmFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for FTF module. (Flash Memory)
 *
 * This function gets the clock frequence for FTF module. (Flash Memory)
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetFtfFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for CRC module.
 *
 * This function gets the clock frequence for CRC module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetCrcFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for ADC module.
 *
 * This function gets the clock frequence for ADC module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetAdcFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for CMP module.
 *
 * This function gets the clock frequence for CMP module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetCmpFreq(uint32_t instance);

/*!
 * @brief Gets the  frequency.
 *
 * This function gets the OSC0 external reference frequency.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockFreq(void);


/*!
 * @brief Gets the clock frequency for PDB module.
 *
 * This function gets the clock frequence for PDB module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetPdbFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for eFlexPWM module.
 *
 * This function gets the clock frequence for eFlexPWM module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetPwmFreq(uint32_t instance);

/*!
 * @brief Gets FTM external clock frequency.
 *
 * This function gets the FTM external clock frequency.
 *
 * @param instance module device instance
 * @return freq    Current frequency.
 */
uint32_t CLOCK_SYS_GetFtmExternalFreq(uint32_t instance);

/*!
 * @brief Gets FTM external clock source.
 *
 * This function gets the FTM external clock source.
 *
 * @param instance module device instance.
 * @return Ftm external clock source.
 */
static inline sim_ftm_clk_sel_t CLOCK_SYS_GetFtmExternalSrc(uint32_t instance)
{
    return SIM_HAL_GetFtmExternalClkPinMode(SIM, instance);
}

/*!
 * @brief Sets FTM external clock source.
 *
 * This function sets the FTM external clock source.
 *
 * @param instance module device instance.
 * @param ftmSrc FTM clock source setting.
 */
static inline void CLOCK_SYS_SetFtmExternalSrc(uint32_t instance,
                                               sim_ftm_clk_sel_t ftmSrc)
{
    SIM_HAL_SetFtmExternalClkPinMode(SIM, instance, ftmSrc);
}

/*!
 * @brief Gets FTM fixed frequency clock frequency.
 *
 * This function gets the FTM fixed frequency clock frequency.
 *
 * @param instance module device instance
 * @return freq    Current frequency.
 */
static inline uint32_t CLOCK_SYS_GetFtmFixedFreq(uint32_t instance)
{
    return CLOCK_SYS_GetFixedFreqClockFreq();
}

/*!
 * @brief Gets FTM's system clock frequency.
 *
 * This function gets the FTM's system clock frequency.
 *
 * @param instance module device instance
 * @return Current frequency.
 */
static inline uint32_t CLOCK_SYS_GetFtmSystemClockFreq(uint32_t instance)
{
    return CLOCK_SYS_GetFastPeripheralClockFreq();
}

/*!
 * @brief Enable the clock for PORT module.
 *
 * This function enables the clock for PORT module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnablePortClock(uint32_t instance);

/*!
 * @brief Disable the clock for PORT module.
 *
 * This function disables the clock for PORT module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisablePortClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for PORT module.
 *
 * This function will get the clock gate state for PORT module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetPortGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for HSADC module.
 *
 * This function enables the clock for HSADC module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableHSAdcClock(uint32_t instance);

/*!
 * @brief Disable the clock for HSADC module.
 *
 * This function disables the clock for HSADC module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableHSAdcClock(uint32_t instance);

/*!
 * @brief Gets the clock frequency for PIT module.
 *
 * This function gets the clock frequence for PIT module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetPitFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for SPI module
 *
 * This function gets the clock frequence for SPI module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetSpiFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for I2C module
 *
 * This function gets the clock frequence for I2C module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetI2cFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for UART module
 *
 * This function gets the clock frequence for UART module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetUartFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for GPIO module
 *
 * This function gets the clock frequence for GPIO module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetGpioFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for ENC module
 *
 * This function gets the clock frequence for ENC module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetEncFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for XBAR module
 *
 * This function gets the clock frequence for XBAR module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetXbarFreq(uint32_t instance);

/*!
 * @brief Gets LPTMRx pre-scaler/glitch filter clock frequency.
 *
 * This function gets the LPTMRx pre-scaler/glitch filter clock frequency.
 *
 * @param instance module device instance
 * @param lptmrSrc LPTMRx clock source selection.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetLptmrFreq(uint32_t instance, clock_lptmr_src_t lptmrSrc);

/*!
 * @brief Gets the clock frequency for AOI module
 *
 * This function gets the clock frequence for AOI module.
 * @param instance module device instance
 * @return freq    clock frequence for this module
 */
uint32_t    CLOCK_SYS_GetAoiFreq(uint32_t instance);

/*!
 * @brief Enable the clock for DMA module.
 *
 * This function enables the clock for DMA module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableDmaClock(uint32_t instance)
{
    SIM_HAL_EnableDmaClock(SIM, instance);
}

/*!
 * @brief Disable the clock for DMA module.
 *
 * This function disables the clock for DMA module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableDmaClock(uint32_t instance)
{
    SIM_HAL_DisableDmaClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for DMA module.
 *
 * This function will get the clock gate state for DMA module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetDmaGateCmd(uint32_t instance)
{
    return SIM_HAL_GetDmaGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for DMAMUX module.
 *
 * This function enables the clock for DMAMUX module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableDmamuxClock(uint32_t instance)
{
    SIM_HAL_EnableDmamuxClock(SIM, instance);
}

/*!
 * @brief Disable the clock for DMAMUX module.
 *
 * This function disables the clock for DMAMUX module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableDmamuxClock(uint32_t instance)
{
    SIM_HAL_DisableDmamuxClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for DMAMUX module.
 *
 * This function will get the clock gate state for DMAMUX module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetDmamuxGateCmd(uint32_t instance)
{
    return SIM_HAL_GetDmamuxGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for MPU module.
 *
 * This function enables the clock for MPU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableMpuClock(uint32_t instance)
{
    SIM_HAL_EnableMpuClock(SIM, instance);
}

/*!
 * @brief Disable the clock for MPU module.
 *
 * This function disables the clock for MPU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableMpuClock(uint32_t instance)
{
    SIM_HAL_DisableMpuClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for MPU module.
 *
 * This function will get the clock gate state for MPU module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetMpuGateCmd(uint32_t instance)
{
    return SIM_HAL_GetMpuGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for EWM module.
 *
 * This function enables the clock for EWM module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableEwmClock(uint32_t instance)
{
    SIM_HAL_EnableEwmClock(SIM, instance);
}

/*!
 * @brief Disable the clock for EWM module.
 *
 * This function disables the clock for EWM module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableEwmClock(uint32_t instance)
{
    SIM_HAL_DisableEwmClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for EWM module.
 *
 * This function will get the clock gate state for EWM module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetEwmGateCmd(uint32_t instance)
{
    return SIM_HAL_GetEwmGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for FLEXBUS module.
 *
 * This function enables the clock for FLEXBUS module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableFlexbusClock(uint32_t instance)
{
    SIM_HAL_EnableFlexbusClock(SIM, instance);
}

/*!
 * @brief Disable the clock for FLEXBUS module.
 *
 * This function disables the clock for FLEXBUS module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableFlexbusClock(uint32_t instance)
{
    SIM_HAL_DisableFlexbusClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for FLEXBUS module.
 *
 * This function will get the clock gate state for FLEXBUS module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetFlexbusGateCmd(uint32_t instance)
{
    return SIM_HAL_GetFlexbusGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for FTF module.
 *
 * This function enables the clock for FTF module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableFtfClock(uint32_t instance)
{
    SIM_HAL_EnableFtfClock(SIM, instance);
}

/*!
 * @brief Disable the clock for FTF module.
 *
 * This function disables the clock for FTF module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableFtfClock(uint32_t instance)
{
    SIM_HAL_DisableFtfClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for FTF module.
 *
 * This function will get the clock gate state for FTF module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetFtfGateCmd(uint32_t instance)
{
    return SIM_HAL_GetFtfGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for CRC module.
 *
 * This function enables the clock for CRC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableCrcClock(uint32_t instance)
{
    SIM_HAL_EnableCrcClock(SIM, instance);
}

/*!
 * @brief Disable the clock for CRC module.
 *
 * This function disables the clock for CRC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableCrcClock(uint32_t instance)
{
    SIM_HAL_DisableCrcClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for CRC module.
 *
 * This function will get the clock gate state for CRC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetCrcGateCmd(uint32_t instance)
{
    return SIM_HAL_GetCrcGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for ADC module.
 *
 * This function enables the clock for ADC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableAdcClock(uint32_t instance)
{
    SIM_HAL_EnableAdcClock(SIM, instance);
}

/*!
 * @brief Disable the clock for ADC module.
 *
 * This function disables the clock for ADC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableAdcClock(uint32_t instance)
{
    SIM_HAL_DisableAdcClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for ADC module.
 *
 * This function will get the clock gate state for ADC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetAdcGateCmd(uint32_t instance)
{
    return SIM_HAL_GetAdcGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for HSADC module.
 *
 * This function enables the clock for HSADC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableHsadcClock(uint32_t instance)
{
    SIM_HAL_EnableHsadcClock(SIM, instance);
}

/*!
 * @brief Disable the clock for HSADC module.
 *
 * This function disables the clock for HSADC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableHsadcClock(uint32_t instance)
{
    SIM_HAL_DisableHsadcClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for HSADC module.
 *
 * This function will get the clock gate state for HSADC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetHsadcGateCmd(uint32_t instance)
{
    return SIM_HAL_GetHsadcGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for CMP module.
 *
 * This function enables the clock for CMP module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableCmpClock(uint32_t instance)
{
    SIM_HAL_EnableCmpClock(SIM, instance);
}

/*!
 * @brief Disable the clock for CMP module.
 *
 * This function disables the clock for CMP module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableCmpClock(uint32_t instance)
{
    SIM_HAL_DisableCmpClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for CMP module.
 *
 * This function will get the clock gate state for CMP module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetCmpGateCmd(uint32_t instance)
{
    return SIM_HAL_GetCmpGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for DAC module.
 *
 * This function enables the clock for DAC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableDacClock(uint32_t instance)
{
    SIM_HAL_EnableDacClock(SIM, instance);
}

/*!
 * @brief Disable the clock for DAC module.
 *
 * This function disables the clock for DAC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableDacClock(uint32_t instance)
{
    SIM_HAL_DisableDacClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for DAC module.
 *
 * This function will get the clock gate state for DAC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetDacGateCmd(uint32_t instance)
{
    return SIM_HAL_GetDacGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for PDB module.
 *
 * This function enables the clock for PDB module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnablePdbClock(uint32_t instance)
{
    SIM_HAL_EnablePdbClock(SIM, instance);
}

/*!
 * @brief Disable the clock for PDB module.
 *
 * This function disables the clock for PDB module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisablePdbClock(uint32_t instance)
{
    SIM_HAL_DisablePdbClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for PDB module.
 *
 * This function will get the clock gate state for PDB module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetPdbGateCmd(uint32_t instance)
{
    return SIM_HAL_GetPdbGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for FTM module.
 *
 * This function enables the clock for FTM module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableFtmClock(uint32_t instance)
{
    SIM_HAL_EnableFtmClock(SIM, instance);
}

/*!
 * @brief Disable the clock for FTM module.
 *
 * This function disables the clock for FTM module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableFtmClock(uint32_t instance)
{
    SIM_HAL_DisableFtmClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for FTM module.
 *
 * This function will get the clock gate state for FTM module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetFtmGateCmd(uint32_t instance)
{
    return SIM_HAL_GetFtmGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for PIT module.
 *
 * This function enables the clock for PIT module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnablePitClock(uint32_t instance)
{
    SIM_HAL_EnablePitClock(SIM, instance);
}

/*!
 * @brief Disable the clock for PIT module.
 *
 * This function disables the clock for PIT module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisablePitClock(uint32_t instance)
{
    SIM_HAL_DisablePitClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for PIT module.
 *
 * This function will get the clock gate state for PIT module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetPitGateCmd(uint32_t instance)
{
    return SIM_HAL_GetPitGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for LPTIMER module.
 *
 * This function enables the clock for LPTIMER module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableLptmrClock(uint32_t instance)
{
    SIM_HAL_EnableLptmrClock(SIM, instance);
}

/*!
 * @brief Disable the clock for LPTIMER module.
 *
 * This function disables the clock for LPTIMER module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableLptmrClock(uint32_t instance)
{
    SIM_HAL_DisableLptmrClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for LPTIMER module.
 *
 * This function will get the clock gate state for LPTIMER module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetLptmrGateCmd(uint32_t instance)
{
    return SIM_HAL_GetLptmrGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for ENET module.
 *
 * This function enables the clock for ENET module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableEnetClock(uint32_t instance)
{
    SIM_HAL_EnableEnetClock(SIM, instance);
}

/*!
 * @brief Disable the clock for ENET module.
 *
 * This function disables the clock for ENET module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableEnetClock(uint32_t instance)
{
    SIM_HAL_DisableEnetClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for ENET module.
 *
 * This function will get the clock gate state for ENET module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetEnetGateCmd(uint32_t instance)
{
    return SIM_HAL_GetEnetGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for FLEXCAN module.
 *
 * This function enables the clock for FLEXCAN module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableFlexcanClock(uint32_t instance)
{
    SIM_HAL_EnableFlexcanClock(SIM, instance);
}

/*!
 * @brief Disable the clock for FLEXCAN module.
 *
 * This function disables the clock for FLEXCAN module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableFlexcanClock(uint32_t instance)
{
    SIM_HAL_DisableFlexcanClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for FLEXCAN module.
 *
 * This function will get the clock gate state for FLEXCAN module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetFlexcanGateCmd(uint32_t instance)
{
    return SIM_HAL_GetFlexcanGateCmd(SIM, instance);
}

 /*!
 * @brief Gets FLEXCAN clock frequency.
 *
 * This function gets the FLEXCAN clock frequency.
 *
 * @param instance   module device instance
 * @param flexcanSrc clock source
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetFlexcanFreq(uint8_t instance, clock_flexcan_src_t flexcanSrc);

#if FSL_FEATURE_SOC_ENET_COUNT
/*!
 * @brief Set the ethernet timestamp clock source selection.
 *
 * This function sets the ethernet timestamp clock source selection.
 *
 * @param instance module device instance.
 * @param timeSrc  Ethernet timestamp clock source.
 */
static inline void CLOCK_SYS_SetEnetTimeStampSrc(uint32_t instance, clock_time_src_t timeSrc)
{
    CLOCK_HAL_SetTimeSrc(SIM, instance, timeSrc);
}

/*!
 * @brief Get the ethernet timestamp clock source selection.
 *
 * This function gets the ethernet timestamp clock source selection.
 *
 * @param instance IP instance.
 *
 * @return Current source.
 */
static inline clock_time_src_t CLOCK_SYS_GetEnetTimeStampSrc(uint32_t instance)
{
    return CLOCK_HAL_GetTimeSrc(SIM, instance);
}
#endif

/*!
 * @brief Enable the clock for SPI module.
 *
 * This function enables the clock for SPI module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableSpiClock(uint32_t instance)
{
    SIM_HAL_EnableSpiClock(SIM, instance);
}

/*!
 * @brief Disable the clock for SPI module.
 *
 * This function disables the clock for SPI module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableSpiClock(uint32_t instance)
{
    SIM_HAL_DisableSpiClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for SPI module.
 *
 * This function will get the clock gate state for SPI module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetSpiGateCmd(uint32_t instance)
{
    return SIM_HAL_GetSpiGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for I2C module.
 *
 * This function enables the clock for I2C module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableI2cClock(uint32_t instance)
{
    SIM_HAL_EnableI2cClock(SIM, instance);
}

/*!
 * @brief Disable the clock for I2C module.
 *
 * This function disables the clock for I2C module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableI2cClock(uint32_t instance)
{
    SIM_HAL_DisableI2cClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for I2C module.
 *
 * This function will get the clock gate state for I2C module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetI2cGateCmd(uint32_t instance)
{
    return SIM_HAL_GetI2cGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for UART module.
 *
 * This function enables the clock for UART module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableUartClock(uint32_t instance)
{
    SIM_HAL_EnableUartClock(SIM, instance);
}

/*!
 * @brief Disable the clock for UART module.
 *
 * This function disables the clock for UART module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableUartClock(uint32_t instance)
{
    SIM_HAL_DisableUartClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for UART module.
 *
 * This function will get the clock gate state for UART module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetUartGateCmd(uint32_t instance)
{
    return SIM_HAL_GetUartGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for eFlexPWM module.
 *
 * This function enables the clock for eFlexPWM module.
 * @param instance module device instance
 * @param channel PWM module channel
 */
static inline void CLOCK_SYS_EnablePwmClock(uint32_t instance, uint8_t channel)
{
    SIM_HAL_EnablePwmClock(SIM, instance, channel);
}

/*!
 * @brief Disable the clock for eFlexPWM module.
 *
 * This function disables the clock for eFlexPWM module.
 * @param instance module device instance
 * @param channel PWM module channel
 */
static inline void CLOCK_SYS_DisablePwmClock(uint32_t instance, uint8_t channel)
{
    SIM_HAL_DisablePwmClock(SIM, instance, channel);
}

/*!
 * @brief Get the the clock gate state for eFlexPWM module.
 *
 * This function will get the clock gate state for eFlexPWM module.
 * @param instance module device instance
 * @param channel PWM module channel
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetPwmGateCmd(uint32_t instance, uint8_t channel)
{
    return SIM_HAL_GetPwmGateCmd(SIM, instance, channel);
}

/*!
 * @brief Enable the clock for AOI module.
 *
 * This function enables the clock for AOI module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableAoiClock(uint32_t instance)
{
    SIM_HAL_EnableAoiClock(SIM, instance);
}

/*!
 * @brief Disable the clock for AOI module.
 *
 * This function disables the clock for AOI module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableAoiClock(uint32_t instance)
{
    SIM_HAL_DisableAoiClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for AOI module.
 *
 * This function will get the clock gate state for AOI module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetAoiGateCmd(uint32_t instance)
{
    return SIM_HAL_GetAoiGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for XBAR module.
 *
 * This function enables the clock for XBAR module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableXbarClock(uint32_t instance)
{
    SIM_HAL_EnableXbarClock(SIM, instance);
}

/*!
 * @brief Disable the clock for XBAR module.
 *
 * This function disables the clock for XBAR module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableXbarClock(uint32_t instance)
{
    SIM_HAL_DisableXbarClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for XBAR module.
 *
 * This function will get the clock gate state for XBAR module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetXbarGateCmd(uint32_t instance)
{
    return SIM_HAL_GetXbarGateCmd(SIM, instance);
}

/*!
 * @brief Enable the clock for ENC module.
 *
 * This function enables the clock for ENC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableEncClock(uint32_t instance)
{
    SIM_HAL_EnableEncClock(SIM, instance);
}

/*!
 * @brief Disable the clock for ENC module.
 *
 * This function disables the clock for ENC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableEncClock(uint32_t instance)
{
    SIM_HAL_DisableEncClock(SIM, instance);
}

/*!
 * @brief Get the the clock gate state for ENC module.
 *
 * This function will get the clock gate state for ENC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetEncGateCmd(uint32_t instance)
{
    return SIM_HAL_GetEncGateCmd(SIM, instance);
}

/*!
 * @brief Set the ENET external clock frequency(ENET_1588_CLKIN).
 *
 * This function sets the ENET external clock frequency (ENET_1588_CLKIN).
 *
 * @param  srcInstance External source instance.
 * @param  freq        Frequcney value.
 */
static inline void CLOCK_SYS_SetEnetExternalFreq(uint32_t srcInstance, uint32_t freq)
{
    assert(srcInstance < ENET_EXT_CLK_COUNT);

    g_enet1588ClkInFreq[srcInstance] = freq;
}

/*!
* @brief Enable the clock for TRNG module.
*
* This function enables the clock for TRNG module.
* @param instance module device instance
*/
static inline void CLOCK_SYS_EnableTrngClock(uint32_t instance)
{
    SIM_HAL_EnableTrngClock(SIM, instance);
}

/*!
* @brief Disable the clock for TRNG module.
*
* This function disables the clock for TRNG module.
* @param instance module device instance
*/
static inline void CLOCK_SYS_DisableTrngClock(uint32_t instance)
{
    SIM_HAL_DisableTrngClock(SIM, instance);
}

/*!
* @brief Get the the clock gate state for TRNG module.
*
* This function will get the clock gate state for TRNG module.
* @param instance module device instance
* @return state true - ungated(Enabled), false - gated (Disabled)
*/
static inline bool CLOCK_SYS_GetTrngGateCmd(uint32_t instance)
{
    return SIM_HAL_GetTrngGateCmd(SIM, instance);
}



#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_CLOCK_KV58F24_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

