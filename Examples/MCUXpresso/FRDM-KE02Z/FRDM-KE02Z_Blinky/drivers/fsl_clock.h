/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016 - 2020, NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Configurations
 ******************************************************************************/

/*! @brief Configures whether to check a parameter in a function.
 *
 * Some ICS settings must be changed with conditions, for example:
 *  1. ICSIRCLK settings, such as the source, divider, and the trim value should not change when
 *     ICSIRCLK is used as a system clock source.
 *  2. ICS_C7[OSCSEL] should not be changed  when the external reference clock is used
 *     as a system clock source. For example, in FBE/BELP/PBE modes.
 *  3. The users should only switch between the supported clock modes.
 *
 * ICS functions check the parameter and ICS status before setting, if not allowed
 * to change, the functions return error. The parameter checking increases code size,
 * if code size is a critical requirement, change #ICS_CONFIG_CHECK_PARAM to 0 to
 * disable parameter checking.
 */
#ifndef ICS_CONFIG_CHECK_PARAM
#define ICS_CONFIG_CHECK_PARAM 0U
#endif

/*! @brief Configure whether driver controls clock
 *
 * When set to 0, peripheral drivers will enable clock in initialize function
 * and disable clock in de-initialize function. When set to 1, peripheral
 * driver will not control the clock, application could control the clock out of
 * the driver.
 *
 * @note All drivers share this feature switcher. If it is set to 1, application
 * should handle clock enable and disable for all drivers.
 */
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL))
#define FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL 0
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.2.1. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 2, 1))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (40000000UL)
#endif

/*! @brief External XTAL0 (OSC0) clock frequency.
 *
 * The XTAL0/EXTAL0 (OSC0) clock frequency in Hz. When the clock is set up, use the
 * function CLOCK_SetXtal0Freq to set the value in the clock driver. For example,
 * if XTAL0 is 8 MHz:
 * @code
 * CLOCK_InitOsc0(...);
 * CLOCK_SetXtal0Freq(80000000)
 * @endcode
 *
 * This is important for the multicore platforms where only one core needs to set up the
 * OSC0 using the CLOCK_InitOsc0. All other cores need to call the CLOCK_SetXtal0Freq
 * to get a valid clock frequency.
 */
extern volatile uint32_t g_xtal0Freq;

#if (defined(OSC) && !(defined(OSC0)))
#define OSC0 OSC
#endif

/*! @brief Clock ip name array for UART. */
#define UART_CLOCKS                              \
    {                                            \
        kCLOCK_Uart0, kCLOCK_Uart1, kCLOCK_Uart2 \
    }

/*! @brief Clock ip name array for ADC16. */
#define ADC_CLOCKS  \
    {               \
        kCLOCK_Adc0 \
    }

/*! @brief Clock ip name array for IRQ. */
#define IRQ_CLOCKS  \
    {               \
        kCLOCK_Irq0 \
    }

/*! @brief Clock ip name array for KBI. */
#define KBI_CLOCKS               \
    {                            \
        kCLOCK_Kbi0, kCLOCK_Kbi1 \
    }

/*! @brief Clock ip name array for SPI. */
#define SPI_CLOCKS               \
    {                            \
        kCLOCK_Spi0, kCLOCK_Spi1 \
    }

/*! @brief Clock ip name array for I2C. */
#define I2C_CLOCKS  \
    {               \
        kCLOCK_I2c0 \
    }

/*! @brief Clock ip name array for FTM. */
#define FTM_CLOCKS                            \
    {                                         \
        kCLOCK_Ftm0, kCLOCK_Ftm1, kCLOCK_Ftm2 \
    }

/*! @brief Clock ip name array for CMP. */
#define ACMP_CLOCKS                \
    {                              \
        kCLOCK_Acmp0, kCLOCK_Acmp1 \
    }

/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS   \
    {                \
        kCLOCK_Crc0, \
    }

/*! @brief Clock ip name array for PIT. */
#define PIT_CLOCKS   \
    {                \
        kCLOCK_Pit0, \
    }

/*! @brief Clock ip name array for RTC. */
#define RTC_CLOCKS   \
    {                \
        kCLOCK_Rtc0, \
    }

/*!
 * @brief LPO clock frequency.
 */
#define LPO_CLK_FREQ 1000U

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{

    /* ----------------------------- System layer clock -------------------------------*/
    kCLOCK_CoreSysClk, /*!< Core/system clock                                         */
    kCLOCK_PlatClk,    /*!< Platform clock                                            */
    kCLOCK_BusClk,     /*!< Bus clock                                                 */
    kCLOCK_FlashClk,   /*!< Flash clock                                               */

    /* ---------------------------------- OSC clock -----------------------------------*/
    kCLOCK_Osc0ErClk, /*!< OSC0 external reference clock (OSC0ERCLK)                 */

    /* ----------------------------- ICS and ICS-Lite clock ---------------------------*/
    kCLOCK_ICSFixedFreqClk,   /*!< ICS fixed frequency clock (ICSFFCLK)                      */
    kCLOCK_ICSInternalRefClk, /*!< ICS internal reference clock (ICSIRCLK)                   */
    kCLOCK_ICSFllClk,         /*!< ICSFLLCLK                                                 */
    kCLOCK_ICSOutClk,         /*!< ICS Output clock                                          */

    /* --------------------------------- Other clock ----------------------------------*/
    kCLOCK_LpoClk, /*!< LPO clock                                                 */

} clock_name_t;

/*------------------------------------------------------------------------------

 clock_gate_t definition:

 31                              16                              0
 -----------------------------------------------------------------
 | SIM_SCGC register offset       |   control bit offset in SCGC |
 -----------------------------------------------------------------

 For example, the SDHC clock gate is controlled by SIM_SCGC3[17], the
 SIM_SCGC3 offset in SIM is 0x1030, then kCLOCK_GateSdhc0 is defined as

              kCLOCK_GateSdhc0 = (0x1030 << 16) | 17;

------------------------------------------------------------------------------*/

#define CLK_GATE_REG_OFFSET_SHIFT 16U
#define CLK_GATE_REG_OFFSET_MASK 0xFFFF0000U
#define CLK_GATE_BIT_SHIFT_SHIFT 0U
#define CLK_GATE_BIT_SHIFT_MASK 0x0000FFFFU

#define CLK_GATE_DEFINE(reg_offset, bit_shift)                                  \
    ((((reg_offset) << CLK_GATE_REG_OFFSET_SHIFT) & CLK_GATE_REG_OFFSET_MASK) | \
     (((bit_shift) << CLK_GATE_BIT_SHIFT_SHIFT) & CLK_GATE_BIT_SHIFT_MASK))

#define CLK_GATE_ABSTRACT_REG_OFFSET(x) (((x)&CLK_GATE_REG_OFFSET_MASK) >> CLK_GATE_REG_OFFSET_SHIFT)
#define CLK_GATE_ABSTRACT_BITS_SHIFT(x) (((x)&CLK_GATE_BIT_SHIFT_MASK) >> CLK_GATE_BIT_SHIFT_SHIFT)

/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,

    kCLOCK_I2c0 = CLK_GATE_DEFINE(0xCU, 17U),

    kCLOCK_Uart0 = CLK_GATE_DEFINE(0xCU, 20U),
    kCLOCK_Uart1 = CLK_GATE_DEFINE(0xCU, 21U),
    kCLOCK_Uart2 = CLK_GATE_DEFINE(0xCU, 22U),

    kCLOCK_Acmp0 = CLK_GATE_DEFINE(0xCU, 30U),
    kCLOCK_Acmp1 = CLK_GATE_DEFINE(0xCU, 31U),

    kCLOCK_Spi0 = CLK_GATE_DEFINE(0xCU, 18U),
    kCLOCK_Spi1 = CLK_GATE_DEFINE(0xCU, 19U),

    kCLOCK_Irq0 = CLK_GATE_DEFINE(0xCU, 27U),

    kCLOCK_Kbi0 = CLK_GATE_DEFINE(0xCU, 24U),
    kCLOCK_Kbi1 = CLK_GATE_DEFINE(0xCU, 25U),

    kCLOCK_Adc0 = CLK_GATE_DEFINE(0xCU, 29U),

    kCLOCK_Crc0 = CLK_GATE_DEFINE(0xCU, 10U),

    kCLOCK_Ftm0 = CLK_GATE_DEFINE(0xCU, 5U),
    kCLOCK_Ftm1 = CLK_GATE_DEFINE(0xCU, 6U),
    kCLOCK_Ftm2 = CLK_GATE_DEFINE(0xCU, 7U),

    kCLOCK_Pit0 = CLK_GATE_DEFINE(0xCU, 1U),
    kCLOCK_Rtc0 = CLK_GATE_DEFINE(0xCU, 0U),
} clock_ip_name_t;

/*!@brief SIM configuration structure for clock setting. */
typedef struct _sim_clock_config
{
    uint32_t busDiv;         /*!< SIM_BUSDIV. */
    uint8_t busClkPrescaler; /*!< A option prescaler for bus clock */
} sim_clock_config_t;

/*! @brief OSC work mode. */
enum _osc_work_mode
{
    kOSC_ModeExt         = 0U,                                  /*!< OSC source from external clock. */
    kOSC_ModeOscLowPower = OSC_CR_OSCOS_MASK,                   /*!< Oscillator low freq low power. */
    kOSC_ModeOscHighGain = OSC_CR_HGO_MASK | OSC_CR_OSCOS_MASK, /*!< Oscillator low freq high gain. */
};

/*! @brief OSC enable mode. */
enum _osc_enable_mode
{
    kOSC_Enable       = OSC_CR_OSCEN_MASK,  /*!< Enable.              */
    kOSC_EnableInStop = OSC_CR_OSCSTEN_MASK /*!< Enable in stop mode. */
};

/*!
 * @brief OSC Initialization Configuration Structure
 *
 * Defines the configuration data structure to initialize the OSC.
 * When porting to a new board, set the following members
 * according to the board setting:
 * 1. freq: The external frequency.
 * 2. workMode: The OSC module mode.
 * 3. enableMode: The OSC enable mode.
 */
typedef struct _osc_config
{
    uint32_t freq;      /*!< External clock frequency.    */
    uint8_t workMode;   /*!< OSC work mode setting.       */
    uint8_t enableMode; /*!< Configuration for OSCERCLK.  */
} osc_config_t;

/*! @brief ICS FLL reference clock source select. */
typedef enum _ics_fll_src
{
    kICS_FllSrcExternal, /*!< External reference clock is selected          */
    kICS_FllSrcInternal  /*!< The slow internal reference clock is selected */
} ics_fll_src_t;

/*! @brief ICSOUT clock source. */
typedef enum _ics_clkout_src
{
    kICS_ClkOutSrcFll,      /*!< Output of the FLL is selected (reset default)  */
    kICS_ClkOutSrcInternal, /*!< Internal reference clock is selected, FLL is bypassed */
    kICS_ClkOutSrcExternal, /*!< External reference clock is selected, FLL is bypassed */
} ics_clkout_src_t;

/*! @brief ICS status. */
enum _ics_status
{
    kStatus_ICS_ModeUnreachable = MAKE_STATUS(kStatusGroup_ICS, 0), /*!< Can't switch to target mode. */
    kStatus_ICS_SourceUsed      = MAKE_STATUS(kStatusGroup_ICS, 1)  /*!< Can't change the clock source because
                                                                         it is in use. */
};

/*! @brief ICS internal reference clock (ICSIRCLK) enable mode definition. */
enum _ics_irclk_enable_mode
{
    kICS_IrclkDisable      = 0U,                  /*!< ICSIRCLK disable. */
    kICS_IrclkEnable       = ICS_C1_IRCLKEN_MASK, /*!< ICSIRCLK enable.              */
    kICS_IrclkEnableInStop = ICS_C1_IREFSTEN_MASK /*!< ICSIRCLK enable in stop mode. */
};

/*! @brief ICS mode definitions */
typedef enum _ics_mode
{
    kICS_ModeFEI = 0U, /*!< FEI   - FLL Engaged Internal         */
    kICS_ModeFBI,      /*!< FBI   - FLL Bypassed Internal        */
    kICS_ModeBILP,     /*!< BILP  - Bypassed Low Power Internal  */
    kICS_ModeFEE,      /*!< FEE   - FLL Engaged External         */
    kICS_ModeFBE,      /*!< FBE   - FLL Bypassed External        */
    kICS_ModeBELP,     /*!< BELP  - Bypassed Low Power External  */
    kICS_ModeError     /*!< Unknown mode                         */
} ics_mode_t;

/*! @brief ICS configuration structure
 *
 * When porting to a new board, set the following members
 * according to the board setting:
 * 1. icsMode:  ICS mode
 * 2. irClkEnableMode: ICSIRCLK enable mode
 * 3. rDiv: If the FLL uses the external reference clock, set this
 *    value to ensure that the external reference clock divided by rDiv is
 *    in the 31.25 kHz to 39.0625 kHz range.
 * 4. bDiv, this divider determine the ISCOUT clock
 */
typedef struct _ics_config
{
    ics_mode_t icsMode;      /*!< ICS mode.                   */
    uint8_t irClkEnableMode; /*!< ICSIRCLK enable mode.       */
    uint8_t rDiv;            /*!< Divider for external reference clock, ICS_C1[RDIV].    */
    uint8_t bDiv;            /*!< Divider for ICS output clock ICS_C2[BDIV].      */
} ics_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Enable the clock for specific IP.
 *
 * @param name  Which clock to enable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t name)
{
    uint32_t regAddr = SIM_BASE + CLK_GATE_ABSTRACT_REG_OFFSET((uint32_t)name);
    (*(volatile uint32_t *)regAddr) |= (1UL << CLK_GATE_ABSTRACT_BITS_SHIFT((uint32_t)name));
}

/*!
 * @brief Disable the clock for specific IP.
 *
 * @param name  Which clock to disable, see \ref clock_ip_name_t.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t name)
{
    uint32_t regAddr = SIM_BASE + CLK_GATE_ABSTRACT_REG_OFFSET((uint32_t)name);
    (*(volatile uint32_t *)regAddr) &= ~(1UL << CLK_GATE_ABSTRACT_BITS_SHIFT((uint32_t)name));
}

/*!
 * @brief clock divider
 *
 * Set the SIM_BUSDIV.
 * Carefully configure the SIM_BUSDIV to avoid bus/flash clock frequency higher
 * than 24MHZ.
 * @param busDiv bus clock output divider value.
 */
static inline void CLOCK_SetBusClkDiv(uint32_t busDiv)
{
    SIM->BUSDIV = SIM_BUSDIV_BUSDIV(busDiv);
}

/*!
 * @brief Gets the clock frequency for a specific clock name.
 *
 * This function checks the current clock configurations and then calculates
 * the clock frequency for a specific clock name defined in clock_name_t.
 * The ICS must be properly configured before using this function.
 *
 * @param clockName Clock names defined in clock_name_t
 * @return Clock frequency value in Hertz
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*!
 * @brief Get the core clock or system clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetCoreSysClkFreq(void);

/*!
 * @brief Get the bus clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetBusClkFreq(void);

/*!
 * @brief Get the flash clock frequency.
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetFlashClkFreq(void);

/*!
 * @brief Get the OSC0 external reference clock frequency (OSC0ERCLK).
 *
 * @return Clock frequency in Hz.
 */
uint32_t CLOCK_GetOsc0ErClkFreq(void);

/*!
 * @brief Set the clock configure in SIM module.
 *
 * This function sets system layer clock settings in SIM module.
 *
 * @param config Pointer to the configure structure.
 */
void CLOCK_SetSimConfig(sim_clock_config_t const *config);

/*!
 * @brief Set the system clock dividers in SIM to safe value.
 *
 * The system level clocks (core clock, bus clock, and flash clock)
 * must be in allowed ranges. During ICS clock mode switch, the ICS output clock
 * changes then the system level clocks may be out of range. This function could
 * be used before ICS mode change, to make sure system level clocks are in allowed
 * range.
 *
 */
static inline void CLOCK_SetSimSafeDivs(void)
{
    SIM->BUSDIV = 0x1U;
}

/*! @name ICS frequency functions. */
/*@{*/

/*!
 * @brief Gets the ICS output clock (ICSOUTCLK) frequency.
 *
 * This function gets the ICS output clock frequency in Hz based on the current ICS
 * register value.
 *
 * @return The frequency of ICSOUTCLK.
 */
uint32_t CLOCK_GetICSOutClkFreq(void);

/*!
 * @brief Gets the ICS FLL clock (ICSFLLCLK) frequency.
 *
 * This function gets the ICS FLL clock frequency in Hz based on the current ICS
 * register value. The FLL is enabled in FEI/FBI/FEE/FBE mode and
 * disabled in low power state in other modes.
 *
 * @return The frequency of ICSFLLCLK.
 */
uint32_t CLOCK_GetFllFreq(void);

/*!
 * @brief Gets the ICS internal reference clock (ICSIRCLK) frequency.
 *
 * This function gets the ICS internal reference clock frequency in Hz based
 * on the current ICS register value.
 *
 * @return The frequency of ICSIRCLK.
 */
uint32_t CLOCK_GetInternalRefClkFreq(void);

/*!
 * @brief Gets the ICS fixed frequency clock (ICSFFCLK) frequency.
 *
 * This function gets the ICS fixed frequency clock frequency in Hz based
 * on the current ICS register value.
 *
 * @return The frequency of ICSFFCLK.
 */
uint32_t CLOCK_GetICSFixedFreqClkFreq(void);

/*@}*/

/*! @name ICS clock configuration. */
/*@{*/

/*!
 * @brief Enables or disables the ICS low power.
 *
 * Enabling the ICS low power disables the PLL and FLL in bypass modes. In other words,
 * in FBE and PBE modes, enabling low power sets the ICS to BELP mode. In FBI and
 * PBI modes, enabling low power sets the ICS to BILP mode.
 * When disabling the ICS low power, the PLL or FLL are enabled based on ICS settings.
 *
 * @param enable True to enable ICS low power, false to disable ICS low power.
 */
static inline void CLOCK_SetLowPowerEnable(bool enable)
{
    if (enable)
    {
        ICS->C2 |= ICS_C2_LP_MASK;
    }
    else
    {
        ICS->C2 &= (uint8_t)(~ICS_C2_LP_MASK);
    }
}

/*!
 * @brief Configures the Internal Reference clock (ICSIRCLK).
 *
 * This function sets the ICSIRCLK base on parameters.
 * This function also sets whether the \c ICSIRCLK is enabled in stop mode.
 *
 * @param enableMode ICSIRCLK enable mode, OR'ed value of _ICS_irclk_enable_mode.
 * @retval kStatus_ICS_SourceUsed Because the internal reference clock is used as a clock source,
 * the configuration should not be changed. Otherwise, a glitch occurs.
 * @retval kStatus_Success ICSIRCLK configuration finished successfully.
 */
static inline void CLOCK_SetInternalRefClkConfig(uint8_t enableMode)
{
    /* Set internal reference clock selection. */
    ICS->C1 = (uint8_t)((ICS->C1 & ~(ICS_C1_IRCLKEN_MASK | ICS_C1_IREFSTEN_MASK)) | (uint8_t)enableMode);
}

/*!
 * @brief Set the FLL external reference clock divider value.
 *
 * Sets the FLL external reference clock divider value, the register ICS_C1[RDIV].
 * Resulting frequency must be in the range 31.25KHZ to 39.0625KHZ.
 *
 * @param rdiv The FLL external reference clock divider value, ICS_C1[RDIV].
 */
static inline void CLOCK_SetFllExtRefDiv(uint8_t rdiv)
{
    ICS->C1 = (uint8_t)((ICS->C1 & ~ICS_C1_RDIV_MASK) | ICS_C1_RDIV(rdiv));
}

/*@}*/

/*! @name ICS clock lock monitor functions. */
/*@{*/

/*!
 * @brief Sets the OSC0 clock monitor mode.
 *
 * This function sets the OSC0 clock monitor mode. See ics_monitor_mode_t for details.
 *
 * @param enable True to enable clock monitor, false to disable clock monitor.
 */
static inline void CLOCK_SetOsc0MonitorMode(bool enable)
{
    if (enable)
    {
        ICS->C4 |= ICS_C4_CME_MASK;
    }
    else
    {
        ICS->C4 &= (uint8_t)(~ICS_C4_CME_MASK);
    }
}

/*@}*/

/*!
 * @name OSC configuration
 * @{
 */

/*!
 * @brief Initializes the OSC0.
 *
 * This function initializes the OSC0 according to the board configuration.
 *
 * @param  config Pointer to the OSC0 configuration structure.
 */
void CLOCK_InitOsc0(osc_config_t const *config);

/*!
 * @brief Deinitializes the OSC0.
 *
 * This function deinitializes the OSC0.
 */
void CLOCK_DeinitOsc0(void);

/* @} */

/*!
 * @name External clock frequency
 * @{
 */

/*!
 * @brief Sets the XTAL0 frequency based on board settings.
 *
 * @param freq The XTAL0/EXTAL0 input clock frequency in Hz.
 */
static inline void CLOCK_SetXtal0Freq(uint32_t freq)
{
    g_xtal0Freq = freq;
}

/*!
 * @brief Sets the OSC enable.
 *
 * @param enable osc enable mode.
 */
static inline void CLOCK_SetOsc0Enable(uint8_t enable)
{
    OSC0->CR |= (uint8_t)((OSC0->CR & (~(OSC_CR_OSCSTEN_MASK | OSC_CR_OSCEN_MASK))) | enable);
}

/* @} */

/*! @name ICS mode functions. */
/*@{*/

/*!
 * @brief Gets the current ICS mode.
 *
 * This function checks the ICS registers and determines the current ICS mode.
 *
 * @return Current ICS mode or error code; See @ref ics_mode_t.
 */
ics_mode_t CLOCK_GetMode(void);

/*!
 * @brief Sets the ICS to FEI mode.
 *
 * This function sets the ICS to FEI mode. If setting to FEI mode fails
 * from the current mode, this function returns an error.
 *
 * @param       bDiv bus clock divider
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetFeiMode(uint8_t bDiv);

/*!
 * @brief Sets the ICS to FEE mode.
 *
 * This function sets the ICS to FEE mode. If setting to FEE mode fails
 * from the current mode, this function returns an error.
 *
 * @param   bDiv bus clock divider
 * @param   rDiv  FLL reference clock divider setting, RDIV.
 *
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetFeeMode(uint8_t bDiv, uint8_t rDiv);

/*!
 * @brief Sets the ICS to FBI mode.
 *
 * This function sets the ICS to FBI mode. If setting to FBI mode fails
 * from the current mode, this function returns an error.
 *
 * @param bDiv bus clock divider
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.s
 */
status_t CLOCK_SetFbiMode(uint8_t bDiv);

/*!
 * @brief Sets the ICS to FBE mode.
 *
 * This function sets the ICS to FBE mode. If setting to FBE mode fails
 * from the current mode, this function returns an error.
 *
 * @param   bDiv bus clock divider
 * @param   rDiv  FLL reference clock divider setting, RDIV.
 *
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetFbeMode(uint8_t bDiv, uint8_t rDiv);

/*!
 * @brief Sets the ICS to BILP mode.
 *
 * This function sets the ICS to BILP mode. If setting to BILP mode fails
 * from the current mode, this function returns an error.
 *
 * @param   bDiv bus clock divider
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetBilpMode(uint8_t bDiv);

/*!
 * @brief Sets the ICS to BELP mode.
 *
 * This function sets the ICS to BELP mode. If setting to BELP mode fails
 * from the current mode, this function returns an error.
 *
 * @param   bDiv bus clock divider
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_SetBelpMode(uint8_t bDiv);

/*!
 * @brief Sets the ICS to FEI mode during system boot up.
 *
 * This function sets the ICS to FEI mode from the reset mode. It can also be used to
 * set up ICS during system boot up.
 *
 * @param  bDiv bus clock divider.
 *
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToFeiMode(uint8_t bDiv);

/*!
 * @brief Sets the ICS to FEE mode during system bootup.
 *
 * This function sets ICS to FEE mode from the reset mode. It can also be used to
 * set up the ICS during system boot up.
 *
 * @param   bDiv bus clock divider.
 * @param   rDiv  FLL reference clock divider setting, RDIV.
 *
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToFeeMode(uint8_t bDiv, uint8_t rDiv);

/*!
 * @brief Sets the ICS to BILP mode during system boot up.
 *
 * This function sets the ICS to BILP mode from the reset mode. It can also be used to
 * set up the ICS during system boot up.
 *
 * @param   bDiv bus clock divider.
 * @retval kStatus_ICS_SourceUsed Could not change ICSIRCLK setting.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToBilpMode(uint8_t bDiv);

/*!
 * @brief Sets the ICS to BELP mode during system boot up.
 *
 * This function sets the ICS to BELP mode from the reset mode. It can also be used to
 * set up the ICS during system boot up.
 *
 * @param   bDiv bus clock divider.
 * @retval kStatus_ICS_ModeUnreachable Could not switch to the target mode.
 * @retval kStatus_Success Switched to the target mode successfully.
 */
status_t CLOCK_BootToBelpMode(uint8_t bDiv);

/*!
 * @brief Sets the ICS to a target mode.
 *
 * This function sets ICS to a target mode defined by the configuration
 * structure. If switching to the target mode fails, this function
 * chooses the correct path.
 *
 * @param  config Pointer to the target ICS mode configuration structure.
 * @return Return kStatus_Success if switched successfully; Otherwise, it returns an error code _ICS_status.
 *
 * @note If the external clock is used in the target mode, ensure that it is
 * enabled. For example, if the OSC0 is used, set up OSC0 correctly before calling this
 * function.
 */
status_t CLOCK_SetIcsConfig(ics_config_t const *config);

/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
