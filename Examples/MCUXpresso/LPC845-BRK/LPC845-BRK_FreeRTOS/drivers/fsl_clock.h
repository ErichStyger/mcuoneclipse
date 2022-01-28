/*
 * Copyright 2017-2021 NXP
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
/*! @brief CLOCK driver version 2.3.3. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 3, 3))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (30000000UL)
#endif

/*! @brief watchdog oscilltor clock frequency.
 *
 * This variable is used to store the watchdog oscillator frequency which is
 * set by CLOCK_InitWdtOsc, and it is returned by CLOCK_GetWdtOscFreq.
 */
extern volatile uint32_t g_Wdt_Osc_Freq;

/*! @brief external clock frequency.
 *
 * This variable is used to store the external clock frequency which is include
 * external oscillator clock and external clk in clock frequency value, it is
 * set by CLOCK_InitExtClkin when CLK IN is used as external clock or by CLOCK_InitSysOsc
 * when external oscillator is used as external clock ,and it is returned by
 * CLOCK_GetExtClkFreq.
 */
extern volatile uint32_t g_Ext_Clk_Freq;

/*! @brief FRO clock setting API address in ROM. */
#define CLOCK_FRO_SETTING_API_ROM_ADDRESS (0x0F0026F5U)
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
#define DAC_CLOCKS                \
    {                             \
        kCLOCK_Dac0, kCLOCK_Dac1, \
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
#define SRAM_CLOCKS    \
    {                  \
        kCLOCK_Ram0_1, \
    }
/*! @brief Clock ip name array for IOCON. */
#define IOCON_CLOCKS  \
    {                 \
        kCLOCK_Iocon, \
    }
/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS                 \
    {                               \
        kCLOCK_Gpio0, kCLOCK_Gpio1, \
    }
/*! @brief Clock ip name array for GPIO_INT. */
#define GPIO_INT_CLOCKS \
    {                   \
        kCLOCK_GpioInt, \
    }
/*! @brief Clock ip name array for DMA. */
#define DMA_CLOCKS  \
    {               \
        kCLOCK_Dma, \
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
#define I2C_CLOCKS                                          \
    {                                                       \
        kCLOCK_I2c0, kCLOCK_I2c1, kCLOCK_I2c2, kCLOCK_I2c3, \
    }
/*! @brief Clock ip name array for I2C. */
#define USART_CLOCKS                                                          \
    {                                                                         \
        kCLOCK_Uart0, kCLOCK_Uart1, kCLOCK_Uart2, kCLOCK_Uart3, kCLOCK_Uart4, \
    }
/*! @brief Clock ip name array for SPI. */
#define SPI_CLOCKS                \
    {                             \
        kCLOCK_Spi0, kCLOCK_Spi1, \
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
/*! @brief Clock ip name array for MTB. */
#define MTB_CLOCKS  \
    {               \
        kCLOCK_Mtb, \
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

/*! @brief Internal used Clock definition only. */
#define CLK_GATE_DEFINE(reg, bit)  ((((reg)&0xFFU) << 8U) | ((bit)&0xFFU))
#define CLK_GATE_GET_REG(x)        (((uint32_t)(x) >> 8U) & 0xFFU)
#define CLK_GATE_GET_BITS_SHIFT(x) ((uint32_t)(x)&0xFFU)
/* clock mux register definition */
#define CLK_MUX_DEFINE(reg, mux)             (((offsetof(SYSCON_Type, reg) & 0xFFU) << 8U) | ((mux)&0xFFU))
#define CLK_MUX_GET_REG(x)                   ((volatile uint32_t *)(((uint32_t)(SYSCON)) + (((uint32_t)(x) >> 8U) & 0xFFU)))
#define CLK_MUX_GET_MUX(x)                   (((uint32_t)(x)) & 0xFFU)
#define CLK_MAIN_CLK_MUX_DEFINE(preMux, mux) ((preMux) << 8U | (mux))
#define CLK_MAIN_CLK_MUX_GET_PRE_MUX(x)      (((uint32_t)(x) >> 8U) & 0xFFU)
#define CLK_MAIN_CLK_MUX_GET_MUX(x)          ((uint32_t)(x)&0xFFU)
/* clock divider register definition */
#define CLK_DIV_DEFINE(reg) (((uint32_t)offsetof(SYSCON_Type, reg)) & 0xFFFU)
#define CLK_DIV_GET_REG(x)  *((volatile uint32_t *)(((uint32_t)(SYSCON)) + ((uint32_t)(x)&0xFFFU)))
/* watch dog oscillator definition */
#define CLK_WDT_OSC_DEFINE(freq, regValue) (((freq)&0xFFFFFFU) | (((regValue)&0xFFU) << 24U))
#define CLK_WDT_OSC_GET_FREQ(x)            ((uint32_t)(x)&0xFFFFFFU)
#define CLK_WDT_OSC_GET_REG(x)             (((x) >> 24U) & 0xFFU)
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
    kCLOCK_IpInvalid = 0U,                                     /*!< Invalid Ip Name. */
    kCLOCK_Rom       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 1U), /*!< Clock gate name: Rom. */

    kCLOCK_Ram0_1 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 2U), /*!< Clock gate name: Ram0_1. */

    kCLOCK_I2c0 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 5U), /*!< Clock gate name: I2c0. */

    kCLOCK_Gpio0 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 6U), /*!< Clock gate name: Gpio0. */

    kCLOCK_Swm = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 7U), /*!< Clock gate name: Swm. */

    kCLOCK_Sct = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 8U), /*!< Clock gate name: Sct. */

    kCLOCK_Wkt = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 9U), /*!< Clock gate name: Wkt. */

    kCLOCK_Mrt = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 10U), /*!< Clock gate name: Mrt. */

    kCLOCK_Spi0 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 11U), /*!< Clock gate name: Spi0. */

    kCLOCK_Spi1 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 12U), /*!< Clock gate name: Spi1. */

    kCLOCK_Crc = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 13U), /*!< Clock gate name: Crc. */

    kCLOCK_Uart0 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 14U), /*!< Clock gate name: Uart0. */

    kCLOCK_Uart1 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 15U), /*!< Clock gate name: Uart1. */

    kCLOCK_Uart2 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 16U), /*!< Clock gate name: Uart2. */

    kCLOCK_Wwdt = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 17U), /*!< Clock gate name: Wwdt. */

    kCLOCK_Iocon = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 18U), /*!< Clock gate name: Iocon. */

    kCLOCK_Acmp = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 19U), /*!< Clock gate name: Acmp. */

    kCLOCK_Gpio1 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 20U), /*!< Clock gate name: Gpio1. */

    kCLOCK_I2c1 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 21U), /*!< Clock gate name: I2c1. */

    kCLOCK_I2c2 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 22U), /*!< Clock gate name: I2c2. */

    kCLOCK_I2c3 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 23U), /*!< Clock gate name: I2c3. */

    kCLOCK_Adc = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 24U), /*!< Clock gate name: Adc. */

    kCLOCK_Ctimer0 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 25U), /*!< Clock gate name: Ctimer0. */

    kCLOCK_Mtb = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 26U), /*!< Clock gate name: Mtb. */

    kCLOCK_Dac0 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 27U), /*!< Clock gate name: Dac0. */

    kCLOCK_GpioInt = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 28U), /*!< Clock gate name: GpioInt. */

    kCLOCK_Dma = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 29U), /*!< Clock gate name: Dma. */

    kCLOCK_Uart3 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 30U), /*!< Clock gate name: Uart3. */

    kCLOCK_Uart4 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 31U), /*!< Clock gate name: Uart4. */

    kCLOCK_Capt = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL1, 0U), /*!< Clock gate name: Capt. */

    kCLOCK_Dac1 = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL1, 1U), /*!< Clock gate name: Dac1. */

} clock_ip_name_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreSysClk, /*!< Cpu/AHB/AHB matrix/Memories,etc */
    kCLOCK_MainClk,    /*!< Main clock */

    kCLOCK_Fro,    /*!< FRO18/24/30 */
    kCLOCK_FroDiv, /*!< FRO div clock */
    kCLOCK_ExtClk, /*!< External Clock */
    kCLOCK_PllOut, /*!< PLL Output */
    kCLOCK_WdtOsc, /*!< Watchdog Oscillator */
    kCLOCK_Frg0,   /*!< fractional rate0 */
    kCLOCK_Frg1,   /*!< fractional rate1 */
} clock_name_t;

/*! @brief Clock Mux Switches
 *CLK_MUX_DEFINE(reg, mux)
 *reg is used to define the mux register
 *mux is used to define the mux value
 *
 */
typedef enum _clock_select
{
    kCAPT_Clk_From_Fro = CLK_MUX_DEFINE(CAPTCLKSEL, 0U), /*!< Mux CAPT_Clk from Fro. */

    kCAPT_Clk_From_MainClk = CLK_MUX_DEFINE(CAPTCLKSEL, 1U), /*!< Mux CAPT_Clk from MainClk. */

    kCAPT_Clk_From_SysPll = CLK_MUX_DEFINE(CAPTCLKSEL, 2U), /*!< Mux CAPT_Clk from SysPll. */

    kCAPT_Clk_From_Fro_Div = CLK_MUX_DEFINE(CAPTCLKSEL, 3U), /*!< Mux CAPT_Clk from Fro_Div. */

    kCAPT_Clk_From_WdtOsc = CLK_MUX_DEFINE(CAPTCLKSEL, 4U), /*!< Mux CAPT_Clk from WdtOsc. */

    kADC_Clk_From_Fro = CLK_MUX_DEFINE(ADCCLKSEL, 0U), /*!< Mux ADC_Clk from Fro. */

    kADC_Clk_From_SysPll = CLK_MUX_DEFINE(ADCCLKSEL, 1U), /*!< Mux ADC_Clk from SysPll. */

    kSCT_Clk_From_Fro = CLK_MUX_DEFINE(SCTCLKSEL, 0U), /*!< Mux SCT_Clk from Fro. */

    kSCT_Clk_From_MainClk = CLK_MUX_DEFINE(SCTCLKSEL, 1U), /*!< Mux SCT_Clk from MainClk. */

    kSCT_Clk_From_SysPll = CLK_MUX_DEFINE(SCTCLKSEL, 2U), /*!< Mux SCT_Clk from SysPll. */

    kEXT_Clk_From_SysOsc = CLK_MUX_DEFINE(EXTCLKSEL, 0U), /*!< Mux EXT_Clk from SysOsc. */

    kEXT_Clk_From_ClkIn = CLK_MUX_DEFINE(EXTCLKSEL, 1U), /*!< Mux EXT_Clk from ClkIn. */

    kUART0_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[0U], 0U), /*!< Mux UART0_Clk from Fro. */

    kUART0_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[0U], 1U), /*!< Mux UART0_Clk from MainClk. */

    kUART0_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[0U], 2U), /*!< Mux UART0_Clk from Frg0Clk. */

    kUART0_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[0U], 3U), /*!< Mux UART0_Clk from Frg1Clk. */

    kUART0_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[0U], 4U), /*!< Mux UART0_Clk from Fro_Div. */

    kUART1_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[1U], 0U), /*!< Mux UART1_Clk from Fro. */

    kUART1_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[1U], 1U), /*!< Mux UART1_Clk from MainClk. */

    kUART1_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[1U], 2U), /*!< Mux UART1_Clk from Frg0Clk. */

    kUART1_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[1U], 3U), /*!< Mux UART1_Clk from Frg1Clk. */

    kUART1_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[1U], 4U), /*!< Mux UART1_Clk from Fro_Div. */

    kUART2_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[2U], 0U), /*!< Mux UART2_Clk from Fro. */

    kUART2_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[2U], 1U), /*!< Mux UART2_Clk from MainClk. */

    kUART2_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[2U], 2U), /*!< Mux UART2_Clk from Frg0Clk. */

    kUART2_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[2U], 3U), /*!< Mux UART2_Clk from Frg1Clk. */

    kUART2_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[2U], 4U), /*!< Mux UART2_Clk from Fro_Div. */

    kUART3_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[3U], 0U), /*!< Mux UART3_Clk from Fro. */

    kUART3_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[3U], 1U), /*!< Mux UART3_Clk from MainClk. */

    kUART3_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[3U], 2U), /*!< Mux UART3_Clk from Frg0Clk. */

    kUART3_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[3U], 3U), /*!< Mux UART3_Clk from Frg1Clk. */

    kUART3_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[3U], 4U), /*!< Mux UART3_Clk from Fro_Div. */

    kUART4_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[4U], 0U), /*!< Mux UART4_Clk from Fro. */

    kUART4_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[4U], 1U), /*!< Mux UART4_Clk from MainClk. */

    kUART4_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[4U], 2U), /*!< Mux UART4_Clk from Frg0Clk. */

    kUART4_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[4U], 3U), /*!< Mux UART4_Clk from Frg1Clk. */

    kUART4_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[4U], 4U), /*!< Mux UART4_Clk from Fro_Div. */

    kI2C0_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[5U], 0U), /*!< Mux I2C0_Clk from Fro. */

    kI2C0_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[5U], 1U), /*!< Mux I2C0_Clk from MainClk. */

    kI2C0_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[5U], 2U), /*!< Mux I2C0_Clk from Frg0Clk. */

    kI2C0_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[5U], 3U), /*!< Mux I2C0_Clk from Frg1Clk. */

    kI2C0_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[5U], 4U), /*!< Mux I2C0_Clk from Fro_Div. */

    kI2C1_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[6U], 0U), /*!< Mux I2C1_Clk from Fro. */

    kI2C1_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[6U], 1U), /*!< Mux I2C1_Clk from MainClk. */

    kI2C1_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[6U], 2U), /*!< Mux I2C1_Clk from Frg0Clk. */

    kI2C1_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[6U], 3U), /*!< Mux I2C1_Clk from Frg1Clk. */

    kI2C1_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[6U], 4U), /*!< Mux I2C1_Clk from Fro_Div. */

    kI2C2_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[7U], 0U), /*!< Mux I2C2_Clk from Fro. */

    kI2C2_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[7U], 1U), /*!< Mux I2C2_Clk from MainClk. */

    kI2C2_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[7U], 2U), /*!< Mux I2C2_Clk from Frg0Clk. */

    kI2C2_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[7U], 3U), /*!< Mux I2C2_Clk from Frg1Clk. */

    kI2C2_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[7U], 4U), /*!< Mux I2C2_Clk from Fro_Div. */

    kI2C3_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[8U], 0U), /*!< Mux I2C3_Clk from Fro. */

    kI2C3_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[8U], 1U), /*!< Mux I2C3_Clk from MainClk. */

    kI2C3_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[8U], 2U), /*!< Mux I2C3_Clk from Frg0Clk. */

    kI2C3_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[8U], 3U), /*!< Mux I2C3_Clk from Frg1Clk. */

    kI2C3_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[8U], 4U), /*!< Mux I2C3_Clk from Fro_Div. */

    kSPI0_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[9U], 0U), /*!< Mux SPI0_Clk from Fro. */

    kSPI0_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[9U], 1U), /*!< Mux SPI0_Clk from MainClk. */

    kSPI0_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[9U], 2U), /*!< Mux SPI0_Clk from Frg0Clk. */

    kSPI0_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[9U], 3U), /*!< Mux SPI0_Clk from Frg1Clk. */

    kSPI0_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[9U], 4U), /*!< Mux SPI0_Clk from Fro_Div. */

    kSPI1_Clk_From_Fro = CLK_MUX_DEFINE(FCLKSEL[10U], 0U), /*!< Mux SPI1_Clk from Fro. */

    kSPI1_Clk_From_MainClk = CLK_MUX_DEFINE(FCLKSEL[10U], 1U), /*!< Mux SPI1_Clk from MainClk. */

    kSPI1_Clk_From_Frg0Clk = CLK_MUX_DEFINE(FCLKSEL[10U], 2U), /*!< Mux SPI1_Clk from Frg0Clk. */

    kSPI1_Clk_From_Frg1Clk = CLK_MUX_DEFINE(FCLKSEL[10U], 3U), /*!< Mux SPI1_Clk from Frg1Clk. */

    kSPI1_Clk_From_Fro_Div = CLK_MUX_DEFINE(FCLKSEL[10U], 4U), /*!< Mux SPI1_Clk from Fro_Div. */

    kFRG0_Clk_From_Fro = CLK_MUX_DEFINE(FRG[0U].FRGCLKSEL, 0U), /*!< Mux FRG0_Clk from Fro. */

    kFRG0_Clk_From_MainClk = CLK_MUX_DEFINE(FRG[0U].FRGCLKSEL, 1U), /*!< Mux FRG0_Clk from MainClk. */

    kFRG0_Clk_From_SysPll = CLK_MUX_DEFINE(FRG[0U].FRGCLKSEL, 2U), /*!< Mux FRG0_Clk from SysPll. */

    kFRG1_Clk_From_Fro = CLK_MUX_DEFINE(FRG[1U].FRGCLKSEL, 0U), /*!< Mux FRG1_Clk from Fro. */

    kFRG1_Clk_From_MainClk = CLK_MUX_DEFINE(FRG[1U].FRGCLKSEL, 1U), /*!< Mux FRG1_Clk from MainClk. */

    kFRG1_Clk_From_SysPll = CLK_MUX_DEFINE(FRG[1U].FRGCLKSEL, 2U), /*!< Mux FRG1_Clk from SysPll. */

    kCLKOUT_From_Fro = CLK_MUX_DEFINE(CLKOUTSEL, 0U), /*!< Mux CLKOUT from Fro. */

    kCLKOUT_From_MainClk = CLK_MUX_DEFINE(CLKOUTSEL, 1U), /*!< Mux CLKOUT from MainClk. */

    kCLKOUT_From_SysPll = CLK_MUX_DEFINE(CLKOUTSEL, 2U), /*!< Mux CLKOUT from SysPll. */

    kCLKOUT_From_ExtClk = CLK_MUX_DEFINE(CLKOUTSEL, 3U), /*!< Mux CLKOUT from ExtClk. */

    kCLKOUT_From_WdtOsc = CLK_MUX_DEFINE(CLKOUTSEL, 4U), /*!< Mux CLKOUT from WdtOsc. */

} clock_select_t;

/*! @brief Clock divider
 */
typedef enum _clock_divider
{
    kCLOCK_DivAdcClk = CLK_DIV_DEFINE(ADCCLKDIV), /*!< Adc Clock Divider. */

    kCLOCK_DivSctClk = CLK_DIV_DEFINE(SCTCLKDIV), /*!< Sct Clock Divider. */

    kCLOCK_DivClkOut = CLK_DIV_DEFINE(CLKOUTDIV), /*!< Clk Out Divider. */

    kCLOCK_IOCONCLKDiv6 = CLK_DIV_DEFINE(IOCONCLKDIV6), /*!< IOCON Clock Div6 Divider. */

    kCLOCK_IOCONCLKDiv5 = CLK_DIV_DEFINE(IOCONCLKDIV5), /*!< IOCON Clock Div5 Divider. */

    kCLOCK_IOCONCLKDiv4 = CLK_DIV_DEFINE(IOCONCLKDIV4), /*!< IOCON Clock Div4 Divider. */

    kCLOCK_IOCONCLKDiv3 = CLK_DIV_DEFINE(IOCONCLKDIV3), /*!< IOCON Clock Div3 Divider. */

    kCLOCK_IOCONCLKDiv2 = CLK_DIV_DEFINE(IOCONCLKDIV2), /*!< IOCON Clock Div2 Divider. */

    kCLOCK_IOCONCLKDiv1 = CLK_DIV_DEFINE(IOCONCLKDIV1), /*!< IOCON Clock Div1 Divider. */

    kCLOCK_IOCONCLKDiv0 = CLK_DIV_DEFINE(IOCONCLKDIV0), /*!< IOCON Clock Div0 Divider. */

} clock_divider_t;

/*! @brief watch dog analog output frequency */
typedef enum _clock_wdt_analog_freq
{
    kCLOCK_WdtAnaFreq0HZ = CLK_WDT_OSC_DEFINE(0U, 0U), /*!< Watch dog analog output frequency is 0HZ. */

    kCLOCK_WdtAnaFreq600KHZ = CLK_WDT_OSC_DEFINE(600000U, 1U), /*!< Watch dog analog output frequency is 600KHZ. */

    kCLOCK_WdtAnaFreq1050KHZ = CLK_WDT_OSC_DEFINE(1050000U, 2u), /*!< Watch dog analog output frequency is 1050KHZ. */

    kCLOCK_WdtAnaFreq1400KHZ = CLK_WDT_OSC_DEFINE(1400000U, 3U), /*!< Watch dog analog output frequency is 1400KHZ. */

    kCLOCK_WdtAnaFreq1750KHZ = CLK_WDT_OSC_DEFINE(1750000U, 4U), /*!< Watch dog analog output frequency is 1750KHZ. */

    kCLOCK_WdtAnaFreq2100KHZ = CLK_WDT_OSC_DEFINE(2100000U, 5U), /*!< Watch dog analog output frequency is 2100KHZ. */

    kCLOCK_WdtAnaFreq2400KHZ = CLK_WDT_OSC_DEFINE(2400000U, 6U), /*!< Watch dog analog output frequency is 2400KHZ. */

    kCLOCK_WdtAnaFreq2700KHZ = CLK_WDT_OSC_DEFINE(2700000U, 7U), /*!< Watch dog analog output frequency is 2700KHZ. */

    kCLOCK_WdtAnaFreq3000KHZ = CLK_WDT_OSC_DEFINE(3000000U, 8U), /*!< Watch dog analog output frequency is 3000KHZ. */

    kCLOCK_WdtAnaFreq3250KHZ = CLK_WDT_OSC_DEFINE(3250000U, 9U), /*!< Watch dog analog output frequency is 3250KHZ. */

    kCLOCK_WdtAnaFreq3500KHZ = CLK_WDT_OSC_DEFINE(3500000U, 10U), /*!< Watch dog analog output frequency is 3500KHZ. */

    kCLOCK_WdtAnaFreq3750KHZ = CLK_WDT_OSC_DEFINE(3750000U, 11U), /*!< Watch dog analog output frequency is 3750KHZ. */

    kCLOCK_WdtAnaFreq4000KHZ = CLK_WDT_OSC_DEFINE(4000000U, 12U), /*!< Watch dog analog output frequency is 4000KHZ. */

    kCLOCK_WdtAnaFreq4200KHZ = CLK_WDT_OSC_DEFINE(4200000U, 13U), /*!< Watch dog analog output frequency is 4200KHZ. */

    kCLOCK_WdtAnaFreq4400KHZ = CLK_WDT_OSC_DEFINE(4400000U, 14U), /*!< Watch dog analog output frequency is 4400KHZ. */

    kCLOCK_WdtAnaFreq4600KHZ = CLK_WDT_OSC_DEFINE(4600000U, 15U), /*!< Watch dog analog output frequency is 4600KHZ. */

} clock_wdt_analog_freq_t;

/*! @brief fro output frequency source definition */
typedef enum _clock_fro_src
{
    kCLOCK_FroSrcLpwrBootValue = 0U, /*!< fro source from the fro oscillator divided by low power boot value */
    kCLOCK_FroSrcFroOsc = 1U << SYSCON_FROOSCCTRL_FRO_DIRECT_SHIFT, /*!< fre source from the fro oscillator directly  */
} clock_fro_src_t;

/*! @brief fro oscillator output frequency value definition */
typedef enum _clock_fro_osc_freq
{
    kCLOCK_FroOscOut18M = 18000U, /*!< FRO oscillator output 18M */
    kCLOCK_FroOscOut24M = 24000U, /*!< FRO oscillator output 24M */
    kCLOCK_FroOscOut30M = 30000U, /*!< FRO oscillator output 30M */
} clock_fro_osc_freq_t;

/*! @brief PLL clock definition.*/
typedef enum _clock_sys_pll_src
{
    kCLOCK_SysPllSrcFRO    = 0U, /*!< system pll source from FRO */
    kCLOCK_SysPllSrcExtClk = 1U, /*!< system pll source from external clock */
    kCLOCK_SysPllSrcWdtOsc = 2U, /*!< system pll source from watchdog oscillator */
    kCLOCK_SysPllSrcFroDiv = 3U, /*!< system pll source from FRO divided clock */
} clock_sys_pll_src;

/*! @brief Main clock source definition */
typedef enum _clock_main_clk_src
{
    kCLOCK_MainClkSrcFro    = CLK_MAIN_CLK_MUX_DEFINE(0U, 0U), /*!< main clock source from FRO */
    kCLOCK_MainClkSrcExtClk = CLK_MAIN_CLK_MUX_DEFINE(1U, 0U), /*!< main clock source from Ext clock */
    kCLOCK_MainClkSrcWdtOsc = CLK_MAIN_CLK_MUX_DEFINE(2U, 0U), /*!< main clock source from watchdog oscillator */
    kCLOCK_MainClkSrcFroDiv = CLK_MAIN_CLK_MUX_DEFINE(3U, 0U), /*!< main clock source from FRO Div */
    kCLOCK_MainClkSrcSysPll = CLK_MAIN_CLK_MUX_DEFINE(0U, 1U), /*!< main clock source from system pll */
} clock_main_clk_src_t;

/*! @brief PLL configuration structure */
typedef struct _clock_sys_pll
{
    uint32_t targetFreq;   /*!< System pll fclk output frequency, the output frequency should be lower than 100MHZ*/
    clock_sys_pll_src src; /*!< System pll clock source */
} clock_sys_pll_t;

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
 * @param src Refer to clock_main_clk_src_t to set the main clock source.
 */
void CLOCK_SetMainClkSrc(clock_main_clk_src_t src);

/*! @brief Set FRO clock source
 * @param src Please refer to _clock_fro_src definition.
 *
 */
void CLOCK_SetFroOutClkSrc(clock_fro_src_t src);

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
/* @} */

/*!
 * @name Get frequency
 * @{
 */

/*! @brief  Return Frequency of FRG0 Clock.
 *  @return Frequency of FRG0 Clock.
 */
uint32_t CLOCK_GetFRG0ClkFreq(void);

/*! @brief  Return Frequency of FRG1 Clock.
 *  @return Frequency of FRG1 Clock.
 */
uint32_t CLOCK_GetFRG1ClkFreq(void);

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

/*! @brief  Get UART2 frequency
 * @retval UART2 frequency value.
 */
uint32_t CLOCK_GetUart2ClkFreq(void);

/*! @brief  Get UART3 frequency
 * @retval UART3 frequency value.
 */
uint32_t CLOCK_GetUart3ClkFreq(void);

/*! @brief  Get UART4 frequency
 * @retval UART4 frequency value.
 */
uint32_t CLOCK_GetUart4ClkFreq(void);

/*! @brief	Return Frequency of selected clock
 *  @return	Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*! @brief  Return System PLL input clock rate
 *  @return System PLL input clock rate
 */
uint32_t CLOCK_GetSystemPLLInClockRate(void);

/*! @brief  Return Frequency of System PLL
 *  @return Frequency of PLL
 */
static inline uint32_t CLOCK_GetSystemPLLFreq(void)
{
    return CLOCK_GetSystemPLLInClockRate() * ((SYSCON->SYSPLLCTRL & SYSCON_SYSPLLCTRL_MSEL_MASK) + 1U);
}

/*! @brief  Get watch dog OSC frequency
 * @retval watch dog OSC frequency value.
 */
static inline uint32_t CLOCK_GetWdtOscFreq(void)
{
    return g_Wdt_Osc_Freq;
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
void CLOCK_InitSystemPll(const clock_sys_pll_t *config);

/*! @brief  System PLL Deinitialize.*/
static inline void CLOCK_DenitSystemPll(void)
{
    /* Power off PLL */
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_SYSPLL_PD_MASK;
}

/* @} */

/*!
 * @name Fractional clock operations
 * @{
 */

/*! @brief Set FRG0 output frequency.
 * @param freq Target output frequency, freq < input and (input / freq) < 2 should be satisfy.
 * @retval true - successfully, false - input argument is invalid.
 *
 */
bool CLOCK_SetFRG0ClkFreq(uint32_t freq);

/*! @brief Set FRG1 output frequency.
 * @param freq Target output frequency, freq < input and (input / freq) < 2 should be satisfy.
 * @retval true - successfully, false - input argument is invalid.
 *
 */
bool CLOCK_SetFRG1ClkFreq(uint32_t freq);

/* @} */

/*!
 * @name External/internal oscillator clock operations
 * @{
 */

/*! @brief  Init external CLK IN, select the CLKIN as the external clock source.
 * @param clkInFreq external clock in frequency.
 */
void CLOCK_InitExtClkin(uint32_t clkInFreq);

/*! @brief	Init SYS OSC
 * @param oscFreq oscillator frequency value.
 */
void CLOCK_InitSysOsc(uint32_t oscFreq);

/*! @brief  XTALIN init function
 *  system oscillator is bypassed, sys_osc_clk is fed driectly from the XTALIN.
 *  @param xtalInFreq XTALIN frequency value
 *  @return Frequency of PLL
 */
void CLOCK_InitXtalin(uint32_t xtalInFreq);

/*! @brief  Deinit SYS OSC
 */
static inline void CLOCK_DeinitSysOsc(void)
{
    /* Deinit system osc power */
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_SYSOSC_PD_MASK;
}

/*! @brief  Init watch dog OSC
 * Any setting of the FREQSEL bits will yield a Fclkana value within 40% of the
 * listed frequency value. The watchdog oscillator is the clock source with the lowest power
 * consumption. If accurate timing is required, use the FRO or system oscillator.
 * The frequency of the watchdog oscillator is undefined after reset. The watchdog
 * oscillator frequency must be programmed by writing to the WDTOSCCTRL register before
 * using the watchdog oscillator.
 * Watchdog osc output frequency = wdtOscFreq / wdtOscDiv, should in range 9.3KHZ to 2.3MHZ.
 * @param wdtOscFreq watch dog analog part output frequency, reference _wdt_analog_output_freq.
 * @param wdtOscDiv watch dog analog part output frequency divider, shoule be a value >= 2U and multiple of 2
 */
void CLOCK_InitWdtOsc(clock_wdt_analog_freq_t wdtOscFreq, uint32_t wdtOscDiv);

/*! @brief  Deinit watch dog OSC
 */
static inline void CLOCK_DeinitWdtOsc(void)
{
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_WDTOSC_PD_MASK;
}

/*! @brief Set FRO oscillator output frequency.
 *  Initialize the FRO clock to given frequency (18, 24 or 30 MHz).
 * @param freq Please refer to clock_fro_osc_freq_t definition, frequency must be one of 18000, 24000 or 30000 KHz.
 *
 */
static inline void CLOCK_SetFroOscFreq(clock_fro_osc_freq_t freq)
{
    (*((void (*)(uint32_t freq))(CLOCK_FRO_SETTING_API_ROM_ADDRESS)))(freq);
}

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
