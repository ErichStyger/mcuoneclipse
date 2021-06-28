/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
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
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.3.2. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 3, 2))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (15000000UL)
#endif

/*! @brief lower power oscilltor clock frequency.
 *
 * This variable is used to store the lower power oscillator frequency which is
 * set by CLOCK_InitLPOsc, and it is returned by CLOCK_GetLPOscFreq.
 */
extern volatile uint32_t g_LP_Osc_Freq;

/*! @brief external clock frequency.
 *
 * This variable is used to store the external clock frequency which is include
 * external oscillator clock and external clk in clock frequency value, it is
 * set by CLOCK_InitExtClkin when CLK IN is used as external clock or by CLOCK_InitSysOsc
 * when external oscillator is used as external clock ,and it is returned by
 * CLOCK_GetExtClkFreq.
 */
extern volatile uint32_t g_Ext_Clk_Freq;

/*! @brief external clock frequency.
 *
 * This variable is used to store the FRO osc clock frequency.
 */
extern volatile uint32_t g_Fro_Osc_Freq;

/*! @brief FRO clock setting API address in ROM. */
#define CLOCK_FRO_SETTING_API_ROM_ADDRESS (0x0F001CD3U)
/*! @brief FAIM base address*/
#define CLOCK_FAIM_BASE (0x50010000U)

/*! @brief Clock ip name array for ADC. */
#define ADC_CLOCKS  \
    {               \
        kCLOCK_Adc, \
    }
/*! @brief Clock ip name array for ACMP. */
#define ACMP_CLOCKS  \
    {                \
        kCLOCK_Acmp, \
    }
/*! @brief Clock ip name array for DAC. */
#define DAC_CLOCKS  \
    {               \
        kCLOCK_Dac, \
    }
/*! @brief Clock ip name array for SWM. */
#define SWM_CLOCKS  \
    {               \
        kCLOCK_Swm, \
    }
/*! @brief Clock ip name array for ROM. */
#define ROM_CLOCKS  \
    {               \
        kCLOCK_Rom, \
    }
/*! @brief Clock ip name array for SRAM. */
#define SRAM_CLOCKS  \
    {                \
        kCLOCK_Ram0, \
    }
/*! @brief Clock ip name array for IOCON. */
#define IOCON_CLOCKS  \
    {                 \
        kCLOCK_Iocon, \
    }
/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS   \
    {                 \
        kCLOCK_Gpio0, \
    }
/*! @brief Clock ip name array for GPIO_INT. */
#define GPIO_INT_CLOCKS \
    {                   \
        kCLOCK_GpioInt, \
    }
/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc, \
    }
/*! @brief Clock ip name array for WWDT. */
#define WWDT_CLOCKS  \
    {                \
        kCLOCK_Wwdt, \
    }
/*! @brief Clock ip name array for SCT0. */
#define SCT_CLOCKS  \
    {               \
        kCLOCK_Sct, \
    }
/*! @brief Clock ip name array for I2C. */
#define I2C_CLOCKS                \
    {                             \
        kCLOCK_I2c0, kCLOCK_I2c1, \
    }
/*! @brief Clock ip name array for I2C. */
#define USART_CLOCKS                \
    {                               \
        kCLOCK_Uart0, kCLOCK_Uart1, \
    }
/*! @brief Clock ip name array for SPI. */
#define SPI_CLOCKS   \
    {                \
        kCLOCK_Spi0, \
    }
/*! @brief Clock ip name array for CAPT. */
#define CAPT_CLOCKS  \
    {                \
        kCLOCK_Capt, \
    }
/*! @brief Clock ip name array for CTIMER. */
#define CTIMER_CLOCKS   \
    {                   \
        kCLOCK_Ctimer0, \
    }
/*! @brief Clock ip name array for MRT. */
#define MRT_CLOCKS  \
    {               \
        kCLOCK_Mrt, \
    }
/*! @brief Clock ip name array for WKT. */
#define WKT_CLOCKS  \
    {               \
        kCLOCK_Wkt, \
    }
/*! @brief Clock ip name array for PLU. */
#define PLU_CLOCKS  \
    {               \
        kCLOCK_PLU, \
    }

/*! @brief Internal used Clock definition only. */
#define CLK_GATE_DEFINE(reg, bit)  ((((reg)&0xFFU) << 8U) | ((bit)&0xFFU))
#define CLK_GATE_GET_REG(x)        (((uint32_t)(x) >> 8U) & 0xFFU)
#define CLK_GATE_GET_BITS_SHIFT(x) ((uint32_t)(x)&0xFFU)
/* clock mux register definition */
#define CLK_MUX_DEFINE(reg, mux)             (((offsetof(SYSCON_Type, reg) & 0xFFU) << 8U) | ((mux)&0xFFU))
#define CLK_MUX_GET_REG(x)                   ((volatile uint32_t *)(((uint32_t)(SYSCON)) + (((uint32_t)(x) >> 8U) & 0xFFU)))
#define CLK_MUX_GET_MUX(x)                   ((uint32_t)(x)&0xFFU)
#define CLK_MAIN_CLK_MUX_DEFINE(preMux, mux) ((preMux) << 8U | (mux))
#define CLK_MAIN_CLK_MUX_GET_PRE_MUX(x)      (((uint32_t)(x) >> 8U) & 0xFFU)
#define CLK_MAIN_CLK_MUX_GET_MUX(x)          ((uint32_t)(x)&0xFFU)
/* clock divider register definition */
#define CLK_DIV_DEFINE(reg) (((uint32_t)offsetof(SYSCON_Type, reg)) & 0xFFFU)
#define CLK_DIV_GET_REG(x)  *((volatile uint32_t *)(((uint32_t)(SYSCON)) + ((uint32_t)(x)&0xFFFU)))
/* watch dog oscillator definition */
//#define CLK_WDT_OSC_DEFINE(freq, regValue) ((freq & 0xFFFFFFU) | ((regValue & 0xFFU) << 24U))
//#define CLK_WDT_OSC_GET_FREQ(x) ((uint32_t)x & 0xFFFFFFU)
//#define CLK_WDT_OSC_GET_REG(x) ((x >> 24U) & 0xFFU)
/* Fractional clock register map */
/* Fractional clock register map */
#define CLK_FRG_DIV_REG_MAP(base) (*(base))
#define CLK_FRG_MUL_REG_MAP(base) (*((uint32_t *)((uint32_t)(base) + 4U)))
#define CLK_FRG_SEL_REG_MAP(base) (*((uint32_t *)((uint32_t)(base) + 8U)))
/* register offset */
#define SYS_AHB_CLK_CTRL0 (0U)
#define SYS_AHB_CLK_CTRL1 (4U)
/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,
    kCLOCK_Sys       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 0U),
    kCLOCK_Rom       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 1U),
    kCLOCK_Ram0      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 2U),
    kCLOCK_Flash     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 4U),
    kCLOCK_I2c0      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 5U),
    kCLOCK_Gpio0     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 6U),
    kCLOCK_Swm       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 7U),
    kCLOCK_Wkt       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 9U),
    kCLOCK_Mrt       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 10U),
    kCLOCK_Spi0      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 11U),
    kCLOCK_Crc       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 13U),
    kCLOCK_Uart0     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 14U),
    kCLOCK_Uart1     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 15U),
    kCLOCK_Wwdt      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 17U),
    kCLOCK_Iocon     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 18U),
    kCLOCK_Acmp      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 19U),
    kCLOCK_I2c1      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 21U),
    kCLOCK_Adc       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 24U),
    kCLOCK_Ctimer0   = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 25U),
    kCLOCK_Dac       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 27U),
    kCLOCK_GpioInt   = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 28U),
    kCLOCK_Capt      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL1, 0U),
    kCLOCK_PLU       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL1, 5U),
} clock_ip_name_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreSysClk, /*!< Cpu/AHB/AHB matrix/Memories,etc */
    kCLOCK_MainClk,    /*!< Main clock */
    kCLOCK_Fro,        /*!< FRO18/24/30 */
    kCLOCK_FroDiv,     /*!< FRO div clock */
    kCLOCK_ExtClk,     /*!< External Clock */
    kCLOCK_LPOsc,      /*!< Watchdog Oscillator */
    kCLOCK_Frg0,       /*!< fractional rate0 */
} clock_name_t;

/*! @brief Clock Mux Switches
 *CLK_MUX_DEFINE(reg, mux)
 *reg is used to define the mux register
 *mux is used to define the mux value
 *
 */
typedef enum _clock_select
{
    kCAPT_Clk_From_Fro     = CLK_MUX_DEFINE(CAPTCLKSEL, 0U),
    kCAPT_Clk_From_MainClk = CLK_MUX_DEFINE(CAPTCLKSEL, 1U),
    kCAPT_Clk_From_Fro_Div = CLK_MUX_DEFINE(CAPTCLKSEL, 3U),
    kCAPT_Clk_From_LPOsc   = CLK_MUX_DEFINE(CAPTCLKSEL, 4U),

    kADC_Clk_From_Fro    = CLK_MUX_DEFINE(ADCCLKSEL, 0U),
    kADC_Clk_From_Extclk = CLK_MUX_DEFINE(ADCCLKSEL, 1U),

    kUART0_Clk_From_Fro     = CLK_MUX_DEFINE(UART0CLKSEL, 0U),
    kUART0_Clk_From_MainClk = CLK_MUX_DEFINE(UART0CLKSEL, 1U),
    kUART0_Clk_From_Frg0Clk = CLK_MUX_DEFINE(UART0CLKSEL, 2U),
    kUART0_Clk_From_Fro_Div = CLK_MUX_DEFINE(UART0CLKSEL, 4U),

    kUART1_Clk_From_Fro     = CLK_MUX_DEFINE(UART1CLKSEL, 0U),
    kUART1_Clk_From_MainClk = CLK_MUX_DEFINE(UART1CLKSEL, 1U),
    kUART1_Clk_From_Frg0Clk = CLK_MUX_DEFINE(UART1CLKSEL, 2U),
    kUART1_Clk_From_Fro_Div = CLK_MUX_DEFINE(UART1CLKSEL, 4U),

    kI2C0_Clk_From_Fro     = CLK_MUX_DEFINE(I2C0CLKSEL, 0U),
    kI2C0_Clk_From_MainClk = CLK_MUX_DEFINE(I2C0CLKSEL, 1U),
    kI2C0_Clk_From_Frg0Clk = CLK_MUX_DEFINE(I2C0CLKSEL, 2U),
    kI2C0_Clk_From_Fro_Div = CLK_MUX_DEFINE(I2C0CLKSEL, 4U),

    kI2C1_Clk_From_Fro     = CLK_MUX_DEFINE(I2C1CLKSEL, 0U),
    kI2C1_Clk_From_MainClk = CLK_MUX_DEFINE(I2C1CLKSEL, 1U),
    kI2C1_Clk_From_Frg0Clk = CLK_MUX_DEFINE(I2C1CLKSEL, 2U),
    kI2C1_Clk_From_Fro_Div = CLK_MUX_DEFINE(I2C1CLKSEL, 4U),

    kSPI0_Clk_From_Fro     = CLK_MUX_DEFINE(SPI0CLKSEL, 0U),
    kSPI0_Clk_From_MainClk = CLK_MUX_DEFINE(SPI0CLKSEL, 1U),
    kSPI0_Clk_From_Frg0Clk = CLK_MUX_DEFINE(SPI0CLKSEL, 2U),
    kSPI0_Clk_From_Fro_Div = CLK_MUX_DEFINE(SPI0CLKSEL, 4U),

    kFRG0_Clk_From_Fro     = CLK_MUX_DEFINE(FRG[0].FRGCLKSEL, 0U),
    kFRG0_Clk_From_MainClk = CLK_MUX_DEFINE(FRG[0].FRGCLKSEL, 1U),

    kCLKOUT_From_Fro     = CLK_MUX_DEFINE(CLKOUTSEL, 0U),
    kCLKOUT_From_MainClk = CLK_MUX_DEFINE(CLKOUTSEL, 1U),
    kCLKOUT_From_ExtClk  = CLK_MUX_DEFINE(CLKOUTSEL, 3U),
    kCLKOUT_From_Lposc   = CLK_MUX_DEFINE(CLKOUTSEL, 4U),
} clock_select_t;

/*! @brief Clock divider
 */
typedef enum _clock_divider
{
    kCLOCK_DivAhbClk = CLK_DIV_DEFINE(SYSAHBCLKDIV),
    kCLOCK_DivAdcClk = CLK_DIV_DEFINE(ADCCLKDIV),
    kCLOCK_DivClkOut = CLK_DIV_DEFINE(CLKOUTDIV),
} clock_divider_t;

//
// typedef enum _clock_wdt_analog_freq
//{
//    kCLOCK_WdtAnaFreq0HZ = CLK_WDT_OSC_DEFINE(0U, 0U),
//    kCLOCK_WdtAnaFreq600KHZ = CLK_WDT_OSC_DEFINE(600000U, 1U),
//    kCLOCK_WdtAnaFreq1050KHZ = CLK_WDT_OSC_DEFINE(1050000U, 2u),
//    kCLOCK_WdtAnaFreq1400KHZ = CLK_WDT_OSC_DEFINE(1400000U, 3U),
//    kCLOCK_WdtAnaFreq1750KHZ = CLK_WDT_OSC_DEFINE(1750000U, 4U),
//    kCLOCK_WdtAnaFreq2100KHZ = CLK_WDT_OSC_DEFINE(2100000U, 5U),
//    kCLOCK_WdtAnaFreq2400KHZ = CLK_WDT_OSC_DEFINE(2400000U, 6U),
//    kCLOCK_WdtAnaFreq2700KHZ = CLK_WDT_OSC_DEFINE(2700000U, 7U),
//    kCLOCK_WdtAnaFreq3000KHZ = CLK_WDT_OSC_DEFINE(3000000U, 8U),
//    kCLOCK_WdtAnaFreq3250KHZ = CLK_WDT_OSC_DEFINE(3250000U, 9U),
//    kCLOCK_WdtAnaFreq3500KHZ = CLK_WDT_OSC_DEFINE(3500000U, 10U),
//    kCLOCK_WdtAnaFreq3750KHZ = CLK_WDT_OSC_DEFINE(3750000U, 11U),
//    kCLOCK_WdtAnaFreq4000KHZ = CLK_WDT_OSC_DEFINE(4000000U, 12U),
//    kCLOCK_WdtAnaFreq4200KHZ = CLK_WDT_OSC_DEFINE(4200000U, 13U),
//    kCLOCK_WdtAnaFreq4400KHZ = CLK_WDT_OSC_DEFINE(4400000U, 14U),
//    kCLOCK_WdtAnaFreq4600KHZ = CLK_WDT_OSC_DEFINE(4600000U, 15U),
//} clock_wdt_analog_freq_t;

/*! @brief fro output frequency source definition */
// typedef enum _clock_fro_src
//{
//   kCLOCK_FroSrcLpwrBootValue = 0U,
//    kCLOCK_FroSrcFroOsc = 1U << SYSCON_FROOSCCTRL_DIRECT_SHIFT,
//} clock_fro_src_t;

/*! @brief fro oscillator output frequency value definition */
typedef enum _clock_fro_osc_freq
{
    kCLOCK_FroOscOut18M = 18000U, /*!< FRO oscillator output 18M */
    kCLOCK_FroOscOut24M = 24000U, /*!< FRO oscillator output 24M */
    kCLOCK_FroOscOut30M = 30000U, /*!< FRO oscillator output 30M */
} clock_fro_osc_freq_t;

/*! @brief PLL clock definition.*/
// typedef enum _clock_sys_pll_src
//{
//    kCLOCK_SysPllSrcFRO = 0U,
//    kCLOCK_SysPllSrcExtClk = 1U,
//    kCLOCK_SysPllSrcWdtOsc = 2U,
//    kCLOCK_SysPllSrcFroDiv = 3U,
//} clock_sys_pll_src;

/*!< Main clock source definition */
typedef enum _clock_main_clk_src
{
    kCLOCK_MainClkSrcFro    = CLK_MAIN_CLK_MUX_DEFINE(0U, 0U), /*!< main clock source from FRO */
    kCLOCK_MainClkSrcExtClk = CLK_MAIN_CLK_MUX_DEFINE(1U, 0U), /*!< main clock source from Ext clock */
    kCLOCK_MainClkSrcLPOsc  = CLK_MAIN_CLK_MUX_DEFINE(2U, 0U), /*!< main clock source from lower power oscillator */
    kCLOCK_MainClkSrcFroDiv = CLK_MAIN_CLK_MUX_DEFINE(3U, 0U), /*!< main clock source from FRO Div */
    // kCLOCK_MainClkSrcSysPll = CLK_MAIN_CLK_MUX_DEFINE(0U, 1U),
} clock_main_clk_src_t;

/*! @brief PLL configuration structure */
// typedef struct _clock_sys_pll
//{
//    uint32_t targetFreq;
//    clock_sys_pll_src src;
//} clock_sys_pll_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name Clock gate, mux, and divider.
 * @{
 */

/*
 *! @brief enable ip clock.
 *
 * @param clk clock ip definition.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t clk)
{
    *(volatile uint32_t *)(((uint32_t)(&SYSCON->SYSAHBCLKCTRL0)) + CLK_GATE_GET_REG(clk)) |=
        1UL << CLK_GATE_GET_BITS_SHIFT(clk);
}

/*
 *!@brief disable ip clock.
 *
 * @param clk clock ip definition.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t clk)
{
    *(volatile uint32_t *)(((uint32_t)(&SYSCON->SYSAHBCLKCTRL0)) + CLK_GATE_GET_REG(clk)) &=
        ~(1UL << CLK_GATE_GET_BITS_SHIFT(clk));
}

/*
 *! @brief	Configure the clock selection muxes.
 * @param	mux	: Clock to be configured.
 * @return	Nothing
 */
static inline void CLOCK_Select(clock_select_t sel)
{
    *(CLK_MUX_GET_REG(sel)) = CLK_MUX_GET_MUX(sel);
}

/*
 *! @brief	Setup peripheral clock dividers.
 * @param	name	: Clock divider name
 * @param   value: Value to be divided
 * @return	Nothing
 */
static inline void CLOCK_SetClkDivider(clock_divider_t name, uint32_t value)
{
    CLK_DIV_GET_REG(name) = value & 0xFFU;
}

/*
 *! @brief  Get peripheral clock dividers.
 * @param   name    : Clock divider name
 * @return  clock divider value
 */
static inline uint32_t CLOCK_GetClkDivider(clock_divider_t name)
{
    return CLK_DIV_GET_REG(name) & 0xFFU;
}

/*
 *! @brief   Setup Core clock dividers.
 * Be careful about the core divider value, due to core/system frequency should be lower than 30MHZ.
 * @param   value: Value to be divided
 * @return  Nothing
 */
static inline void CLOCK_SetCoreSysClkDiv(uint32_t value)
{
    assert(value != 0U);

    SYSCON->SYSAHBCLKDIV = (SYSCON->SYSAHBCLKDIV & (~SYSCON_SYSAHBCLKDIV_DIV_MASK)) | SYSCON_SYSAHBCLKDIV_DIV(value);
}

/*! @brief  Set main clock reference source.
 * @param src Reference clock_main_clk_src_t to set the main clock source.
 */
void CLOCK_SetMainClkSrc(clock_main_clk_src_t src);

/*
 *! @brief	Set Fractional generator multiplier value.
 * @param   base: Fractional generator register address
 * @param	mul	: FRG multiplier value.
 * @return	Nothing
 */
static inline void CLOCK_SetFRGClkMul(uint32_t *base, uint32_t mul)
{
    CLK_FRG_DIV_REG_MAP(base) = SYSCON_FRG_FRGDIV_DIV_MASK;
    CLK_FRG_MUL_REG_MAP(base) = SYSCON_FRG_FRGMULT_MULT(mul);
}

/*! @brief Set FRO clock source
 * @param src, please reference _clock_fro_src definition.
 *
 */
// void CLOCK_SetFroOutClkSrc(clock_fro_src_t src);

/* @} */

/*!
 * @name Get frequency
 * @{
 */

/*! @brief  Return Frequency of FRG0 Clock.
 *  @return Frequency of FRG0 Clock.
 */
uint32_t CLOCK_GetFRG0ClkFreq(void);

/*! @brief  Return Frequency of Main Clock.
 *  @return Frequency of Main Clock.
 */
uint32_t CLOCK_GetMainClkFreq(void);

/*! @brief  Return Frequency of FRO.
 *  @return Frequency of FRO.
 */
uint32_t CLOCK_GetFroFreq(void);

/*! @brief  Return Frequency of core.
 *  @return Frequency of core.
 */
static inline uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetMainClkFreq() / (SYSCON->SYSAHBCLKDIV & 0xffU);
}

/*! @brief  Return Frequency of ClockOut
 *  @return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void);

/*! @brief  Get UART0 frequency
 * @retval UART0 frequency value.
 */
uint32_t CLOCK_GetUart0ClkFreq(void);

/*! @brief  Get UART1 frequency
 * @retval UART1 frequency value.
 */
uint32_t CLOCK_GetUart1ClkFreq(void);

/*! @brief	Return Frequency of selected clock
 *  @return	Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*! @brief  Get watch dog OSC frequency
 * @retval watch dog OSC frequency value.
 */
static inline uint32_t CLOCK_GetLPOscFreq(void)
{
    return g_LP_Osc_Freq;
}

/*! @brief  Get external clock frequency
 * @retval external clock frequency value.
 */
static inline uint32_t CLOCK_GetExtClkFreq(void)
{
    return g_Ext_Clk_Freq;
}
/* @} */

/*!
 * @name PLL operations
 * @{
 */

/*! @brief  System PLL initialize.
 *  @param config System PLL configurations.
 */
// void CLOCK_InitSystemPll(const clock_sys_pll_t *config);

/* @} */

/*!
 * @name Fractional clock operations
 * @{
 */

/*! @brief Set FRG0 output frequency.
 * @param freq  target output frequency,freq < input and (input / freq) < 2 should be satisfy.
 * @retval true - successfully, false - input argument is invalid.
 *
 */
bool CLOCK_SetFRG0ClkFreq(uint32_t freq);

/* @} */

/*!
 * @name External/internal oscillator clock operations
 * @{
 */

/*! @brief  Init external CLK IN, select the CLKIN as the external clock source.
 * @param clkInFreq external clock in frequency.
 */
void CLOCK_InitExtClkin(uint32_t clkInFreq);

/*! @brief  Deinit watch dog OSC */
static inline void CLOCK_DeinitLpOsc(void)
{
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_LPOSC_PD_MASK;
}

// void CLOCK_InitSysOsc(uint32_t oscFreq);

// static inline void CLOCK_DeinitSysOsc(void)
//{
//
//    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_SYSOSC_PD_MASK;
//}

// void CLOCK_InitWdtOsc(clock_wdt_analog_freq_t wdtOscFreq, uint32_t wdtOscDiv);

// static inline void CLOCK_DeinitWdtOsc(void)
//{
//    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_LPOSC_PD_MASK;
//}

/*! @brief Set FRO oscillator output frequency.
 *  Initialize the FRO clock to given frequency (18, 24 or 30 MHz).
 * @param freq Please refer to definition of clock_fro_osc_freq_t, frequency must be one of 18000, 24000 or 30000 KHz.
 *
 */
void CLOCK_SetFroOscFreq(clock_fro_osc_freq_t freq);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
