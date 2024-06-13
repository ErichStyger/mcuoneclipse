/*
** ###################################################################
**     Processors:          MIMXRT685SFAWBR_cm33
**                          MIMXRT685SFFOB_cm33
**                          MIMXRT685SFVKB_cm33
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    MIMXRT685 User manual Rev. 0.95 11 November 2019
**     Version:             rev. 2.0, 2019-11-12
**     Build:               b201016
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2020 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-06-19)
**         Initial version.
**     - rev. 2.0 (2019-11-12)
**         Base on rev 0.95 RM (B0 Header)
**
** ###################################################################
*/

/*!
 * @file MIMXRT685S_cm33
 * @version 2.0
 * @date 2019-11-12
 * @brief Device specific configuration file for MIMXRT685S_cm33 (header file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#ifndef _SYSTEM_MIMXRT685S_cm33_H_
#define _SYSTEM_MIMXRT685S_cm33_H_               /**< Symbol preventing repeated inclusion */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define DEFAULT_SYSTEM_CLOCK           12000000u           /* Default System clock value */
#ifndef CLK_XTAL_OSC_CLK
#define CLK_XTAL_OSC_CLK               24000000u           /* Default XTAL OSC clock */
#endif
#define CLK_RTC_32K_CLK                   32768u           /* RTC oscillator 32 kHz (32k_clk) */
#define CLK_LPOSC_1MHZ                  1000000u           /* Low power oscillator 1 MHz (1m_lposc) */
#define CLK_FRO_16MHZ                  16000000u           /* Slow FRO 16 MHz (fro_16m) */
#define CLK_FRO_48MHZ                  48000000u           /* Fast FRO 48 MHz (fro_48m) */
#define CLK_FRO_60MHZ                  60000000u           /* Fast FRO 60 MHz (fro_60m) */
#ifndef CLK_EXT_CLKIN
#define CLK_EXT_CLKIN                         0u           /* Default external CLKIN pin clock */
#endif


/**
 * @brief System clock frequency (core clock)
 *
 * The system clock frequency supplied to the SysTick timer and the processor
 * core clock. This variable can be used by the user application to setup the
 * SysTick timer or configure other parameters. It may also be used by debugger to
 * query the frequency of the debug timer or configure the trace clock speed
 * SystemCoreClock is initialized with a correct predefined value.
 */
extern uint32_t SystemCoreClock;

/**
 * @brief Setup the microcontroller system.
 *
 * Typically this function configures the oscillator (PLL) that is part of the
 * microcontroller device. For systems with variable clock speed it also updates
 * the variable SystemCoreClock. SystemInit is called from startup_device file.
 */
void SystemInit (void);

/**
 * @brief Updates the SystemCoreClock variable.
 *
 * It must be called whenever the core clock is changed during program
 * execution. SystemCoreClockUpdate() evaluates the clock register settings and calculates
 * the current core clock.
 */
void SystemCoreClockUpdate (void);

/**
 * @brief SystemInit function hook.
 *
 * This weak function allows to call specific initialization code during the
 * SystemInit() execution.This can be used when an application specific code needs
 * to be called as close to the reset entry as possible (for example the Multicore
 * Manager MCMGR_EarlyInit() function call).
 * NOTE: No global r/w variables can be used in this hook function because the
 * initialization of these variables happens after this function.
 */
void SystemInitHook (void);

#ifdef __cplusplus
}
#endif

#endif  /* _SYSTEM_MIMXRT685S_cm33_H_ */
