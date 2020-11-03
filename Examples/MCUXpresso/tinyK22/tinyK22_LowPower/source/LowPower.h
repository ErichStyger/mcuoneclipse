/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LOWPOWER_H_
#define LOWPOWER_H_

/* set of different low power modes: */
#define LP_MODE_RUN    (0)  /* run mode, actually no low power mode. */
#define LP_MODE_WAIT   (1)  /* wait mode, disables only CPU clock, wake-up is any interrupt. */
#define LP_MODE_STOP   (2)  /* stop mode, lowest power mode that retains all registers while maintaining LVD detection, wakeup by interrupt or reset.  */
#define LP_MODE_VLPR   (3)  /* VLPR mode, NYI */

/* selected low power mode: */
//#define LP_MODE LP_MODE_RUN /* the low power mode to be used */
//#define LP_MODE LP_MODE_WAIT /* the low power mode to be used */
#define LP_MODE LP_MODE_STOP /* the low power mode to be used */

void LP_EnterLowPower(void);

void LP_Init(void);

#endif /* LOWPOWER_H_ */
