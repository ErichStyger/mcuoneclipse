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

#if !defined (CLOCK_S32K1xx_H)
#define CLOCK_S32K1xx_H

/*!
 * @file clock_S32K1xx.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.3, A project should not contain unused type declarations.
 * The types are defined here to be used by other drivers or application.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * This is required to implement enumeration entries as macro.
 * Enumeration entries (macros) are referenced from application code.
 */

#include "device_registers.h"
#include "status.h"
#include <stdint.h>
#include <stdbool.h>


/*!
 * @ingroup clock_manager
 * @defgroup clock_manager_s32k1xx
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Peripheral features list
 *         Constant array storing the mappings between clock names of the peripherals and feature lists.
 */
extern const uint8_t peripheralFeaturesList[CLOCK_NAME_COUNT];


/* @brief TClk clock frequency. */
#define NUMBER_OF_TCLK_INPUTS 3U
extern uint32_t g_TClkFreq[NUMBER_OF_TCLK_INPUTS];      /* TCLKx clocks */

/* @brief EXTAL0 clock frequency. */
extern uint32_t g_xtal0ClkFreq;

/* @brief RTC_CLKIN clock frequency. */
extern uint32_t g_RtcClkInFreq;

/* The maximum number of system clock dividers */
#define MAX_NO_SYS_CLOCK_DIVS 7

/*!
 * @brief SIM CLK32KSEL clock source select
 * Implements sim_rtc_clk_sel_src_t_Class
 */
typedef enum
{
    SIM_RTCCLK_SEL_SOSCDIV1_CLK   = 0x0U,           /* SOSCDIV1 clock          */
    SIM_RTCCLK_SEL_LPO_32K        = 0x1U,           /* 32 kHz LPO clock        */
    SIM_RTCCLK_SEL_RTC_CLKIN      = 0x2U,           /* RTC_CLKIN clock         */
    SIM_RTCCLK_SEL_FIRCDIV1_CLK   = 0x3U,           /* FIRCDIV1 clock          */
} sim_rtc_clk_sel_src_t;

/*!
 * @brief SIM LPOCLKSEL clock source select
 * Implements sim_lpoclk_sel_src_t_Class
 */
typedef enum
{
    SIM_LPO_CLK_SEL_LPO_128K    = 0x0,           /* 128 kHz LPO clock */
    SIM_LPO_CLK_SEL_NO_CLOCK    = 0x1,           /* No clock */
    SIM_LPO_CLK_SEL_LPO_32K     = 0x2,           /* 32 kHz LPO clock which is divided by the 128 kHz LPO clock */
    SIM_LPO_CLK_SEL_LPO_1K      = 0x3,           /* 1 kHz LPO clock which is divided by the 128 kHz LPO clock */
} sim_lpoclk_sel_src_t;

/*!
 * @brief SIM CLKOUT select
 */
typedef enum
{
    SIM_CLKOUT_SEL_SYSTEM_SCG_CLKOUT     = 0U,     /*!< SCG CLKOUT                                   */
    SIM_CLKOUT_SEL_SYSTEM_SOSC_DIV2_CLK  = 2U,     /*!< SOSC DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_SIRC_DIV2_CLK  = 4U,     /*!< SIRC DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_FIRC_DIV2_CLK  = 6U,     /*!< FIRC DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_HCLK           = 7U,     /*!< HCLK                                         */
    SIM_CLKOUT_SEL_SYSTEM_SPLL_DIV2_CLK  = 8U,     /*!< SPLL DIV2 CLK                                */
    SIM_CLKOUT_SEL_SYSTEM_BUS_CLK        = 9U,     /*!< BUS_CLK                                      */
    SIM_CLKOUT_SEL_SYSTEM_LPO_128K_CLK   = 10U,    /*!< LPO_CLK 128 Khz                              */
    SIM_CLKOUT_SEL_SYSTEM_LPO_CLK        = 12U,    /*!< LPO_CLK as selected by SIM LPO CLK Select    */
    SIM_CLKOUT_SEL_SYSTEM_RTC_CLK        = 14U,    /*!< RTC CLK as selected by SIM CLK 32 KHz Select */

#if defined (QuadSPI_INSTANCE_COUNT)
    SIM_CLKOUT_SEL_SYSTEM_SFIF_CLK_HYP   = 5U,     /*!< SFIF_CLK_HYP                                 */
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK        = 11U,    /*!< IPG_CLK                                      */
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK_SFIF   = 13U,    /*!< IPG_CLK_SFIF                                 */
    SIM_CLKOUT_SEL_SYSTEM_IPG_CLK_2XSFIF = 15U     /*!< IP_CLK_2XSFIF                                */
#endif
} sim_clkout_src_t;

/*!
 * @brief SIM CLKOUT divider
 */
typedef enum
{
    SIM_CLKOUT_DIV_BY_1 = 0x0U,        /*!< Divided by 1 */
    SIM_CLKOUT_DIV_BY_2 = 0x1U,        /*!< Divided by 2 */
    SIM_CLKOUT_DIV_BY_3 = 0x2U,        /*!< Divided by 3 */
    SIM_CLKOUT_DIV_BY_4 = 0x3U,        /*!< Divided by 4 */
    SIM_CLKOUT_DIV_BY_5 = 0x4U,        /*!< Divided by 5 */
    SIM_CLKOUT_DIV_BY_6 = 0x5U,        /*!< Divided by 6 */
    SIM_CLKOUT_DIV_BY_7 = 0x6U,        /*!< Divided by 7 */
    SIM_CLKOUT_DIV_BY_8 = 0x7U,        /*!< Divided by 8 */
} sim_clkout_div_t;


/*!
 * @brief SIM ClockOut configuration.
 * Implements sim_clock_out_config_t_Class
 */
typedef struct
{
    bool              initialize;     /*!< Initialize or not the ClockOut clock.  */
    bool              enable;         /*!< SIM ClockOut enable.                   */
    sim_clkout_src_t  source;         /*!< SIM ClockOut source select.            */
    sim_clkout_div_t  divider;        /*!< SIM ClockOut divide ratio.             */
} sim_clock_out_config_t;


/*!
 * @brief SIM LPO Clocks configuration.
 * Implements sim_lpo_clock_config_t_Class
 */
typedef struct
{
    bool                  initialize;       /*!< Initialize or not the LPO clock.     */
    sim_rtc_clk_sel_src_t sourceRtcClk;     /*!< RTC_CLK source select.               */
    sim_lpoclk_sel_src_t  sourceLpoClk;     /*!< LPO clock source select.             */
    bool                  enableLpo32k;     /*!< MSCM Clock Gating Control enable.    */
    bool                  enableLpo1k;      /*!< MSCM Clock Gating Control enable.    */
} sim_lpo_clock_config_t;

/*!
 * @brief SIM  Platform Gate Clock configuration.
 * Implements sim_tclk_config_t_Class
 */
typedef struct
{
    bool      initialize;                         /*!< Initialize or not the Trace clock.  */
    uint32_t  tclkFreq[NUMBER_OF_TCLK_INPUTS];    /*!< TCLKx frequency.                    */
} sim_tclk_config_t;

/*!
 * @brief SIM  Platform Gate Clock configuration.
 * Implements sim_plat_gate_config_t_Class
 */
typedef struct
{
    bool initialize;     /*!< Initialize or not the Trace clock.  */
    bool enableMscm;     /*!< MSCM Clock Gating Control enable.   */
    bool enableMpu;      /*!< MPU Clock Gating Control enable.    */
    bool enableDma;      /*!< DMA Clock Gating Control enable.    */
    bool enableErm;      /*!< ERM Clock Gating Control enable.    */
    bool enableEim;      /*!< EIM Clock Gating Control enable.    */
} sim_plat_gate_config_t;

/*!
 * @brief SIM QSPI reference clock gating.
 * Implements sim_qspi_ref_clk_gating_t_Class
 */
typedef struct
{
    bool enableQspiRefClk;      /*!< qspi internal reference clock gating control enable.          */
} sim_qspi_ref_clk_gating_t;


/*!
 * @brief Debug trace clock source select
 * Implements clock_trace_src_t_Class
 */
typedef enum
{
    CLOCK_TRACE_SRC_CORE_CLK            = 0x0,         /*!< core clock     */
    CLOCK_TRACE_SRC_PLATFORM_CLK        = 0x1          /*!< platform clock */
} clock_trace_src_t;


/*!
 * @brief SIM Debug Trace clock configuration.
 * Implements sim_trace_clock_config_t_Class
 */
typedef struct
{
    bool               initialize;    /*!< Initialize or not the Trace clock.  */
    bool               divEnable;     /*!< Trace clock divider enable.         */
    clock_trace_src_t  source;        /*!< Trace clock select.                 */
    uint8_t            divider;       /*!< Trace clock divider divisor.        */
    bool               divFraction;   /*!< Trace clock divider fraction.       */
} sim_trace_clock_config_t;

/*!
 * @brief SIM configure structure.
 * Implements sim_clock_config_t_Class
 */
typedef struct
{
    sim_clock_out_config_t    clockOutConfig;                 /*!< Clock Out configuration.           */
    sim_lpo_clock_config_t    lpoClockConfig;                 /*!< Low Power Clock configuration.     */
    sim_tclk_config_t         tclkConfig;                     /*!< Platform Gate Clock configuration. */
    sim_plat_gate_config_t    platGateConfig;                 /*!< Platform Gate Clock configuration. */
    sim_trace_clock_config_t  traceClockConfig;               /*!< Trace clock configuration.         */
    sim_qspi_ref_clk_gating_t qspiRefClkGating;               /*!< Qspi Reference Clock Gating.       */
} sim_clock_config_t;


/*!
 * @brief SCG system clock source.
 * Implements scg_system_clock_src_t_Class
 */
typedef enum
{
    SCG_SYSTEM_CLOCK_SRC_SYS_OSC  = 1U,       /*!< System OSC. */
    SCG_SYSTEM_CLOCK_SRC_SIRC     = 2U,       /*!< Slow IRC.   */
    SCG_SYSTEM_CLOCK_SRC_FIRC     = 3U,       /*!< Fast IRC.   */
    SCG_SYSTEM_CLOCK_SRC_SYS_PLL  = 6U,       /*!< System PLL. */
    SCG_SYSTEM_CLOCK_SRC_NONE     = 255U      /*!< MAX value.  */
} scg_system_clock_src_t;

/*!
 * @brief SCG system clock divider value.
 * Implements scg_system_clock_div_t_Class
 */
typedef enum
{
    SCG_SYSTEM_CLOCK_DIV_BY_1   = 0U,     /*!< Divided by 1. */
    SCG_SYSTEM_CLOCK_DIV_BY_2   = 1U,     /*!< Divided by 2. */
    SCG_SYSTEM_CLOCK_DIV_BY_3   = 2U,     /*!< Divided by 3. */
    SCG_SYSTEM_CLOCK_DIV_BY_4   = 3U,     /*!< Divided by 4. */
    SCG_SYSTEM_CLOCK_DIV_BY_5   = 4U,     /*!< Divided by 5. */
    SCG_SYSTEM_CLOCK_DIV_BY_6   = 5U,     /*!< Divided by 6. */
    SCG_SYSTEM_CLOCK_DIV_BY_7   = 6U,     /*!< Divided by 7. */
    SCG_SYSTEM_CLOCK_DIV_BY_8   = 7U,     /*!< Divided by 8. */
    SCG_SYSTEM_CLOCK_DIV_BY_9   = 8U,     /*!< Divided by 9. */
    SCG_SYSTEM_CLOCK_DIV_BY_10  = 9U,     /*!< Divided by 10. */
    SCG_SYSTEM_CLOCK_DIV_BY_11  = 10U,    /*!< Divided by 11. */
    SCG_SYSTEM_CLOCK_DIV_BY_12  = 11U,    /*!< Divided by 12. */
    SCG_SYSTEM_CLOCK_DIV_BY_13  = 12U,    /*!< Divided by 13. */
    SCG_SYSTEM_CLOCK_DIV_BY_14  = 13U,    /*!< Divided by 14. */
    SCG_SYSTEM_CLOCK_DIV_BY_15  = 14U,    /*!< Divided by 15. */
    SCG_SYSTEM_CLOCK_DIV_BY_16  = 15U,    /*!< Divided by 16. */
} scg_system_clock_div_t;

/*!
 * @brief SCG system clock configuration.
 * Implements scg_system_clock_config_t_Class
 */
typedef struct
{
    scg_system_clock_div_t divSlow;  /*!< Slow clock divider.      */
    scg_system_clock_div_t divBus;   /*!< BUS clock divider.       */
    scg_system_clock_div_t divCore;  /*!< Core clock divider.      */
    scg_system_clock_src_t src;      /*!< System clock source.     */
} scg_system_clock_config_t;

/* @} */
/*!
 * @name SCG Clockout.
 * @{
 */

/*!
 * @brief SCG ClockOut type.
 * Implements scg_clockout_src_t_Class
 */
typedef enum
{
    SCG_CLOCKOUT_SRC_SCG_SLOW = 0U,   /*!< SCG SLOW.   */
    SCG_CLOCKOUT_SRC_SOSC     = 1U,   /*!< System OSC. */
    SCG_CLOCKOUT_SRC_SIRC     = 2U,   /*!< Slow IRC.   */
    SCG_CLOCKOUT_SRC_FIRC     = 3U,   /*!< Fast IRC.   */
    SCG_CLOCKOUT_SRC_SPLL     = 6U,   /*!< System PLL. */
} scg_clockout_src_t;
/* @} */


/*!
 * @brief SCG asynchronous clock divider value.
 */
typedef enum
{
    SCG_ASYNC_CLOCK_DISABLE   = 0U,        /*!< Clock output is disabled.  */
    SCG_ASYNC_CLOCK_DIV_BY_1  = 1U,        /*!< Divided by 1.              */
    SCG_ASYNC_CLOCK_DIV_BY_2  = 2U,        /*!< Divided by 2.              */
    SCG_ASYNC_CLOCK_DIV_BY_4  = 3U,        /*!< Divided by 4.              */
    SCG_ASYNC_CLOCK_DIV_BY_8  = 4U,        /*!< Divided by 8.              */
    SCG_ASYNC_CLOCK_DIV_BY_16 = 5U,        /*!< Divided by 16.             */
    SCG_ASYNC_CLOCK_DIV_BY_32 = 6U,        /*!< Divided by 32.             */
    SCG_ASYNC_CLOCK_DIV_BY_64 = 7U         /*!< Divided by 64.             */
} scg_async_clock_div_t;


/*!
 * @brief SCG system OSC monitor mode.
 * Implements scg_sosc_monitor_mode_t_Class
 */
typedef enum
{
    SCG_SOSC_MONITOR_DISABLE = 0U,                         /*!< Monitor disable.                          */
    SCG_SOSC_MONITOR_INT     = 1U,                         /*!< Interrupt when system OSC error detected. */
    SCG_SOSC_MONITOR_RESET   = 2U,                          /*!< Reset when system OSC error detected.     */
} scg_sosc_monitor_mode_t;

/*!
 * @brief SCG OSC frequency range select
 * Implements scg_sosc_range_t_Class
 */
typedef enum
{
    SCG_SOSC_RANGE_LOW    = 1U,  /*!< Low frequency range selected for the crystal OSC (32 kHz to 40 kHz).   */
    SCG_SOSC_RANGE_MID    = 2U,  /*!< Medium frequency range selected for the crystal OSC (1 Mhz to 8 Mhz).  */
    SCG_SOSC_RANGE_HIGH   = 3U,  /*!< High frequency range selected for the crystal OSC (8 Mhz to 40 Mhz).   */
} scg_sosc_range_t;

/*!
 * @brief SCG OSC high gain oscillator select.
 * Implements scg_sosc_gain_t_Class
 */
typedef enum
{
    SCG_SOSC_GAIN_LOW    = 0x0,  /* Configure crystal oscillator for low-power operation */
    SCG_SOSC_GAIN_HIGH   = 0x1,  /* Configure crystal oscillator for high-gain operation */
} scg_sosc_gain_t;

/*!
 * @brief SCG OSC external reference clock select.
 * Implements scg_sosc_ext_ref_t_Class
 */
typedef enum
{
    SCG_SOSC_REF_EXT   = 0x0,     /* External reference clock requested    */
    SCG_SOSC_REF_OSC   = 0x1,     /* Internal oscillator of OSC requested. */
} scg_sosc_ext_ref_t;

/*!
 * @brief SCG system OSC configuration.
 * Implements scg_sosc_config_t_Class
 */
typedef struct
{
    uint32_t  freq;                        /*!< System OSC frequency.                                 */

    scg_sosc_monitor_mode_t monitorMode;   /*!< System OSC Clock monitor mode.                       */

    scg_sosc_ext_ref_t extRef;             /*!< System OSC External Reference Select.                */
    scg_sosc_gain_t    gain;               /*!< System OSC high-gain operation.                      */

    scg_sosc_range_t   range;              /*!< System OSC frequency range.                          */

    scg_async_clock_div_t div1;            /*!< Divider for platform asynchronous clock.             */
    scg_async_clock_div_t div2;            /*!< Divider for bus asynchronous clock.                  */

    bool enableInStop;                     /*!< System OSC is enable or not in stop mode.            */
    bool enableInLowPower;                 /*!< System OSC is enable or not in low power mode.       */

    bool locked;                           /*!< System OSC Control Register can be written.          */

    bool initialize;                       /*!< Initialize or not the System OSC module.             */
} scg_sosc_config_t;

/*!
 * @brief SCG slow IRC clock frequency range.
 * Implements scg_sirc_range_t_Class
 */
typedef enum
{
    SCG_SIRC_RANGE_LOW,   /*!< Slow IRC low range clock (2 MHz).  */
    SCG_SIRC_RANGE_HIGH,  /*!< Slow IRC high range clock (8 MHz). */
} scg_sirc_range_t;

/*!
 * @brief SCG slow IRC clock configuration.
 * Implements scg_sirc_config_t_Class
 */
typedef struct
{
    scg_sirc_range_t range;         /*!< Slow IRC frequency range.                 */

    scg_async_clock_div_t div1;     /*!< Divider for platform asynchronous clock.  */
    scg_async_clock_div_t div2;     /*!< Divider for bus asynchronous clock.       */

    bool initialize;                /*!< Initialize or not the SIRC module.        */
    bool enableInStop;              /*!< SIRC is enable or not in stop mode.       */
    bool enableInLowPower;          /*!< SIRC is enable or not in low power mode.  */

    bool locked;                    /*!< SIRC Control Register can be written.     */
} scg_sirc_config_t;

/*!
 * @brief SCG fast IRC clock frequency range.
 * Implements scg_firc_range_t_Class
 */
typedef enum
{
    SCG_FIRC_RANGE_48M,   /*!< Fast IRC is trimmed to 48MHz.  */
    SCG_FIRC_RANGE_52M,   /*!< Fast IRC is trimmed to 52MHz.  */
    SCG_FIRC_RANGE_56M,   /*!< Fast IRC is trimmed to 56MHz.  */
    SCG_FIRC_RANGE_60M,   /*!< Fast IRC is trimmed to 60MHz.  */
} scg_firc_range_t;

/*!
 * @brief SCG fast IRC clock configuration.
 * Implements scg_firc_config_t_Class
 */
typedef struct
{
    scg_firc_range_t range;            /*!< Fast IRC frequency range.                 */

    scg_async_clock_div_t div1;        /*!< Divider for platform asynchronous clock.  */
    scg_async_clock_div_t div2;        /*!< Divider for bus asynchronous clock.       */

    bool enableInStop;                 /*!< FIRC is enable or not in stop mode.       */
    bool enableInLowPower;             /*!< FIRC is enable or not in lowpower mode.   */
    bool regulator;                    /*!< FIRC regulator is enable or not.          */
    bool locked;                       /*!< FIRC Control Register can be written.     */

    bool initialize;                   /*!< Initialize or not the FIRC module.        */
} scg_firc_config_t;

/*!
 * @brief SCG system PLL monitor mode.
 * Implements scg_spll_monitor_mode_t_Class
 */
typedef enum
{
    SCG_SPLL_MONITOR_DISABLE = 0U,                         /*!< Monitor disable.                          */
    SCG_SPLL_MONITOR_INT     = 1U,                         /*!< Interrupt when system PLL error detected. */
    SCG_SPLL_MONITOR_RESET   = 2U                          /*!< Reset when system PLL error detected.     */
} scg_spll_monitor_mode_t;


/*!
 * @brief SCG system PLL predivider.
 * Implements scg_spll_clock_prediv_t_Class
 */
typedef enum
{
    SCG_SPLL_CLOCK_PREDIV_BY_1 = 0U,
    SCG_SPLL_CLOCK_PREDIV_BY_2 = 1U,
    SCG_SPLL_CLOCK_PREDIV_BY_3 = 2U,
    SCG_SPLL_CLOCK_PREDIV_BY_4 = 3U,
    SCG_SPLL_CLOCK_PREDIV_BY_5 = 4U,
    SCG_SPLL_CLOCK_PREDIV_BY_6 = 5U,
    SCG_SPLL_CLOCK_PREDIV_BY_7 = 6U,
    SCG_SPLL_CLOCK_PREDIV_BY_8 = 7U

} scg_spll_clock_prediv_t;

/*!
 * @brief SCG system PLL multiplier.
 * Implements scg_spll_clock_multiply_t_Class
 */
typedef enum
{
    SCG_SPLL_CLOCK_MULTIPLY_BY_16 = 0U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_17 = 1U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_18 = 2U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_19 = 3U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_20 = 4U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_21 = 5U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_22 = 6U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_23 = 7U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_24 = 8U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_25 = 9U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_26 = 10U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_27 = 11U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_28 = 12U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_29 = 13U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_30 = 14U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_31 = 15U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_32 = 16U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_33 = 17U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_34 = 18U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_35 = 19U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_36 = 20U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_37 = 21U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_38 = 22U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_39 = 23U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_40 = 24U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_41 = 25U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_42 = 26U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_43 = 27U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_44 = 28U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_45 = 29U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_46 = 30U,
    SCG_SPLL_CLOCK_MULTIPLY_BY_47 = 31U
} scg_spll_clock_multiply_t;

/*!
 * @brief SCG system PLL configuration.
 * Implements scg_spll_config_t_Class
 */
typedef struct
{
    scg_spll_monitor_mode_t monitorMode; /*!< Clock monitor mode selected.                    */

    uint8_t        prediv;               /*!< PLL reference clock divider.                    */
    uint8_t        mult;                 /*!< System PLL multiplier.                          */
    uint8_t        src;                  /*!< System PLL source.                              */

    scg_async_clock_div_t div1;          /*!< Divider for platform asynchronous clock.        */
    scg_async_clock_div_t div2;          /*!< Divider for bus asynchronous clock.             */

    bool enableInStop;                   /*!< System PLL clock is enable or not in stop mode. */

    bool locked;                         /*!< System PLL Control Register can be written.     */
    bool initialize;                     /*!< Initialize or not the System PLL module.        */
} scg_spll_config_t;

/*!
 * @brief SCG RTC configuration.
 * Implements scg_rtc_config_t_Class
 */
typedef struct
{
    uint32_t rtcClkInFreq;              /*!< RTC_CLKIN frequency.                            */
    bool initialize;                    /*!< Initialize or not the RTC.                      */
} scg_rtc_config_t;

/*!
 * @brief SCG Clock Mode Configuration structure.
 * Implements scg_clock_mode_config_t_Class
 */
typedef struct
{
    scg_system_clock_config_t rccrConfig;      /*!< Run Clock Control configuration.                 */
    scg_system_clock_config_t vccrConfig;      /*!< VLPR Clock Control configuration.                */
    scg_system_clock_config_t hccrConfig;      /*!< HSRUN Clock Control configuration.               */
    scg_system_clock_src_t    alternateClock;  /*!< Alternate clock used during initialization       */
    bool                      initialize;      /*!< Initialize or not the Clock Mode Configuration.  */
} scg_clock_mode_config_t;

/*!
 * @brief SCG ClockOut Configuration structure.
 * Implements scg_clockout_config_t_Class
 */
typedef struct
{
    scg_clockout_src_t        source;          /*!< ClockOut source select.                          */
    bool                      initialize;      /*!< Initialize or not the ClockOut.                  */
} scg_clockout_config_t;

/*!
 * @brief SCG configure structure.
 * Implements scg_config_t_Class
 */
typedef struct
{
    scg_sirc_config_t         sircConfig;      /*!< Slow internal reference clock configuration.     */
    scg_firc_config_t         fircConfig;      /*!< Fast internal reference clock configuration.     */
    scg_sosc_config_t         soscConfig;      /*!< System oscillator configuration.                 */
    scg_spll_config_t         spllConfig;      /*!< System Phase locked loop configuration.          */
    scg_rtc_config_t          rtcConfig;       /*!< Real Time Clock configuration.                   */
    scg_clockout_config_t     clockOutConfig;  /*!< SCG ClockOut Configuration.                      */
    scg_clock_mode_config_t   clockModeConfig; /*!< SCG Clock Mode Configuration.                    */
} scg_config_t;

/*! @brief PCC clock source select
 *  Implements peripheral_clock_source_t_Class
 */
typedef uint8_t peripheral_clock_source_t;

#define    CLK_SRC_OFF          0x00U             /* Clock is off */
#define    CLK_SRC_SOSC         0x01U             /* OSCCLK - System Oscillator Bus Clock */
#define    CLK_SRC_SIRC         0x02U             /* SCGIRCLK - Slow IRC Clock */
#define    CLK_SRC_FIRC         0x03U             /* SCGFIRCLK - Fast IRC Clock */
#define    CLK_SRC_SPLL         0x06U             /* SCGPCLK System PLL clock */
#define    CLK_SRC_SOSC_DIV1    0x01U             /* OSCCLK - System Oscillator Bus Clock */
#define    CLK_SRC_SIRC_DIV1    0x02U             /* SCGIRCLK - Slow IRC Clock */
#define    CLK_SRC_FIRC_DIV1    0x03U             /* SCGFIRCLK - Fast IRC Clock */
#define    CLK_SRC_SPLL_DIV1    0x06U             /* SCGPCLK System PLL clock */
#define    CLK_SRC_SOSC_DIV2    0x01U             /* OSCCLK - System Oscillator Bus Clock */
#define    CLK_SRC_SIRC_DIV2    0x02U             /* SCGIRCLK - Slow IRC Clock */
#define    CLK_SRC_FIRC_DIV2    0x03U             /* SCGFIRCLK - Fast IRC Clock */
#define    CLK_SRC_SPLL_DIV2    0x06U             /* SCGPCLK System PLL clock */

/*! @brief PCC fractional value select
 *  Implements peripheral_clock_frac_t_Class
 */
typedef enum
{
    MULTIPLY_BY_ONE   = 0x00U,             /* Fractional value is zero */
    MULTIPLY_BY_TWO   = 0x01U              /* Fractional value is one */
} peripheral_clock_frac_t;

/*! @brief PCC divider value select
 *  Implements peripheral_clock_divider_t_Class
 */
typedef enum
{
    DIVIDE_BY_ONE     = 0x00U,             /* Divide by 1 (pass-through, no clock divide) */
    DIVIDE_BY_TWO     = 0x01U,             /* Divide by 2 */
    DIVIDE_BY_THREE   = 0x02U,             /* Divide by 3 */
    DIVIDE_BY_FOUR    = 0x03U,             /* Divide by 4 */
    DIVIDE_BY_FIVE    = 0x04U,             /* Divide by 5 */
    DIVIDE_BY_SIX     = 0x05U,             /* Divide by 6 */
    DIVIDE_BY_SEVEN   = 0x06U,             /* Divide by 7 */
    DIVIDE_BY_EIGTH   = 0x07U              /* Divide by 8 */
} peripheral_clock_divider_t;

/*! @brief PCC peripheral instance clock configuration.
 *  Implements peripheral_clock_config_t_Class
 */
typedef struct
{
    /* clockName   is the name of the peripheral clock
     *    must be one of the following values (see the clock_names_t type from S32K1xx_clock_names.h)
     *    PCC_DMA0_CLOCK
     *    PCC_MPU0_CLOCK
     *    ...
     *    PCC_LPUART3_CLOCK
     */
    clock_names_t clockName;
    bool clkGate;                                      /*!< Peripheral clock gate.                     */
    peripheral_clock_source_t clkSrc;                  /*!< Peripheral clock source.                   */
    peripheral_clock_frac_t frac;                      /*!< Peripheral clock fractional value.         */
    peripheral_clock_divider_t divider;                /*!< Peripheral clock divider value.            */
} peripheral_clock_config_t;

/*! @brief PCC configuration.
 *  Implements pcc_config_t_Class
 */
typedef struct
{
    uint32_t count;                                    /*!< Number of peripherals to be configured.               */
    peripheral_clock_config_t * peripheralClocks;       /*!< Pointer to the peripheral clock configurations array. */
} pcc_config_t;

/*! @brief PMC LPO configuration. */
typedef struct
{
    bool                  initialize;       /*!< Initialize or not the PMC LPO settings. */
    bool                  enable;           /*!< Enable/disable LPO     */
    int8_t                trimValue;        /*!< LPO trimming value     */
} pmc_lpo_clock_config_t;

/*!
 * @brief PMC configure structure.
 */
typedef struct
{
    pmc_lpo_clock_config_t lpoClockConfig;   /*!< Low Power Clock configuration.     */
} pmc_config_t;

/*!
 * @brief Clock configuration structure.
 * Implements clock_manager_user_config_t_Class
 */
typedef struct
{
    scg_config_t                scgConfig;      /*!< SCG Clock configuration.      */
    sim_clock_config_t          simConfig;      /*!< SIM Clock configuration.      */
    pcc_config_t                pccConfig;      /*!< PCC Clock configuration.      */
    pmc_config_t                pmcConfig;      /*!< PMC Clock configuration.      */
} clock_manager_user_config_t;

/*!
 * @brief Power mode.
 * Implements pwr_modes_t_Class
 */
typedef enum {

    NO_MODE       = 0U,
    RUN_MODE      = (1U<<0U),
    VLPR_MODE     = (1U<<1U),
    HSRUN_MODE    = (1U<<2U),
    STOP_MODE     = (1U<<3U),
    VLPS_MODE     = (1U<<4U),
    ALL_MODES     = 0x7FFFFFFF

} pwr_modes_t;

/*! @brief Clock source type
 *  Implements clk_src_type_t_Class
 */
typedef enum
{
    IRC_CLK_SRC_TYPE,                  /* Internal oscillator clock source type */
    XOSC_CLK_SRC_TYPE,                 /* External oscillator clock source type */
    PLL_CLK_SRC_TYPE,                  /* Phase lock loop clock source type */

} clk_src_type_t;

/*!
 * @brief clock frequency
 * Implements clk_freq_range_t_Class
 */
typedef enum
{
    NO_CLOCK            = 0U,     /*!< Disable clock source or module input clock. */
    LOWEST_FREQUENCY    = 1U,     /*!< Lowest frequency of clock source or module input clock. */
    MEDIUM_FREQUENCY    = 2U,     /*!< Medium frequency of clock source or module input clock. */
    HIGHEST_FREQUENCY   = 3U,     /*!< Highest frequency of clock source or module input clock. */

} clk_freq_range_t;

/*!
 * @brief XOSC reference clock select (internal oscillator is bypassed or not)
 * Implements xosc_ref_t_Class
 */
typedef enum
{
    XOSC_EXT_REF  = 0U,      /* Internal oscillator is bypassed, external reference clock requested. */
    XOSC_INT_OSC  = 1U,      /* Internal oscillator of XOSC requested. */
} xosc_ref_t;

/*! @brief module clock configuration.
 *  Implements module_clk_config_t_Class
 */
typedef struct
{
    clk_src_type_t   clkSrcType;         /*!< Type of the input peripheral clock source.  */
    clk_freq_range_t clkSrcFreq;         /*!< Frequency of the input peripheral clock source (disabled, lowest, medium, highest) */

}module_clk_config_t;

/*!
 * @brief System clock configuration.
 * Implements sys_clk_config_t_Class
 */
typedef struct
{
    clock_names_t src;                         /*!< System clock source. */
    uint16_t dividers[MAX_NO_SYS_CLOCK_DIVS];  /*!< System clock dividers. Value by which system clock is divided. 0 means that system clock is not divided. */
} sys_clk_config_t;

/*!
 * @brief Clock source configuration.
 * Implements clock_source_config_t_Class
 */
typedef struct
{
    uint32_t refFreq;                    /*!< Frequency of the input reference clock. It applies to external oscillator clock sources */
    xosc_ref_t refClk;                   /*!< Bypass option. It applies to external oscillator clock sources                          */
    clk_freq_range_t clkSrcFreq;         /*!< Output frequency of the clock source (disabled, lowest, medium, highest)                */
    pwr_modes_t modes;                   /*!< Modes in which clock source is enabled                                                  */

} clock_source_config_t;


/*******************************************************************************
 * API
 ******************************************************************************/

#if defined (__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*
 * @brief Initialize clocking modules
 *
 * This function initializes clocking modules according to a provided
 * configuration.
 *
 * @param[out] config    Pointer to the configuration structure
 */
status_t CLOCK_DRV_Init(clock_manager_user_config_t const * config);

/*
 * @brief Return frequency
 *
 * This function returns the frequency according to a provided
 * clock.
 *
 * @param[in] clockName        Clock name of the configured peripheral clock
 * @param[out] frequency    Pointer to the clock frequency
 */
status_t CLOCK_DRV_GetFreq(clock_names_t clockName, uint32_t * frequency);

/*!
 * @brief Configures module clock
 *
 * This function configures a module clock according to the configuration.
 * If no configuration is provided (moduleClkConfig is null), then a default one is used
 *
 * @param[in] clockName         Clock name of the configured module clock
 * @param[in] moduleClkConfig   Pointer to the configuration structure.
 */
void CLOCK_DRV_SetModuleClock(clock_names_t clockName, const module_clk_config_t * moduleClkConfig);

/*!
 * @brief Configures the system clocks.
 *
 * This function configures the system clocks (core, bus and flash clocks) in the specified power mode.
 * If no power mode is specified (null parameter) then it is the current power mode.
 *
 * @param[in] mode              Pointer to power mode for which the configured system clocks apply
 * @param[in] sysClkConfig      Pointer to the system clocks configuration structure.
 */
status_t CLOCK_DRV_SetSystemClock(const pwr_modes_t * mode,
                                  const sys_clk_config_t * sysClkConfig);

/*!
 * @brief Gets the system clock source.
 *
 * This function gets the current system clock source.
 *
 * @return Value of the current system clock source.
 */
void CLOCK_DRV_GetSystemClockSource(sys_clk_config_t *sysClkConfig);

/*!
 * @brief This function configures a clock source.
 *
 * The clock source is configured based on the provided configuration.
 * All values from the previous configuration of clock source are overwritten.
 * If no configuration is provided, then a default one is used.
 *
 * @param[in] clockName    Clock name of the configured peripheral clock
 * @param[in] clkSrcConfig Pointer to the configuration structure
 * @return Status of module initialization
 */
status_t CLOCK_DRV_SetClockSource(clock_names_t clockName, const clock_source_config_t * clkSrcConfig);

#if defined (__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_S32K1xx_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
