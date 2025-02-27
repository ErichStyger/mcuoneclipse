/*
 * util.h
 *
 *  Created on: 28 Mar 2022
 *      Author: Peter Allenspach
 * 		For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>

void SysTick_DelayTicks(uint32_t n);

/* DWT (Data Watchpoint and Trace) registers, only exists on ARM Cortex with a DWT unit */
#define MCU_DWT_CONTROL (*((volatile uint32_t *)0xE0001000))
/*!< DWT Control register */
#define MCU_DWT_CYCCNTENA_BIT (1UL << 0)
/*!< CYCCNTENA bit in DWT_CONTROL register */
#define MCU_DWT_CYCCNT (*((volatile uint32_t *)0xE0001004))
/*!< DWT Cycle Counter register */
#define MCU_DEMCR (*((volatile uint32_t *)0xE000EDFC))
/*!< DEMCR: Debug Exception and Monitor Control Register */
#define MCU_TRCENA_BIT (1UL << 24)
/*!< Trace enable bit in DEMCR register */

/* MCU_CycleCounter definitions
 * These functions could be used to access the cycle counter of the MCU-Link Pro to
 * provide time measurements with the highest possible accuracy on device
 * taken from https://mcuoneclipse.com/2017/01/30/cycle-counting-on-arm-cortex-m-with-dwt/
 */

#define MCU_InitCycleCounter() \
  MCU_DEMCR |= MCU_TRCENA_BIT
/*!< TRCENA: Enable trace and debug block DEMCR (Debug Exception and Monitor Control Register */

#define MCU_ResetCycleCounter() \
  MCU_DWT_CYCCNT = 0
/*!< Reset cycle counter */

#define MCU_EnableCycleCounter() \
  MCU_DWT_CONTROL |= MCU_DWT_CYCCNTENA_BIT
/*!< Enable cycle counter */

#define MCU_DisableCycleCounter() \
  MCU_DWT_CONTROL &= ~MCU_DWT_CYCCNTENA_BIT
/*!< Disable cycle counter */

#define MCU_GetCycleCounter() \
  MCU_DWT_CYCCNT
/*!< Read cycle counter register */

#endif /* UTIL_H_ */
