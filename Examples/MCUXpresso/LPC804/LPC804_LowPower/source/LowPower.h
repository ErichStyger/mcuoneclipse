/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LOWPOWER_H_
#define LOWPOWER_H_

/* low power modes, see data sheet page 33 */
#define LP_MODE_SLEEP             1  /* ARM SLEEP, core not clocked: ISR wakeup, WAIT/WFI with clock on FRO18M */
#define LP_MODE_DEEP_SLEEP        2  /* plus peripheral clocks off, except FRO or low power oscillator, analog blocks off, flash in standby. ISR wakeup, disables debug block, wake-up with WKT */
#define LP_MODE_POWER_DOWN        3  /* disables debug block, wake-up with WKT */
#define LP_MODE_DEEP_POWER_DOWN   4  /* not supported yet, wake-up with pin interrupt */

/* select low power mode: */
#if 1
  #define LP_LOW_POWER_MODE   LP_MODE_SLEEP
#elif 1
  #define LP_LOW_POWER_MODE   LP_MODE_DEEP_SLEEP
#else
  #define LP_LOW_POWER_MODE   LP_MODE_POWER_DOWN
#endif

/* hook below get called from FreeRTOS Idle and Tickless Idle */
void LP_EnterLowPowerMode(void);

void LP_Init(void);

#endif /* LOWPOWER_H_ */
