/*
 * Copyright (c) 2013-2014 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/*
 * File:        smc.h
 * Purpose:     Provides low power mode entry routines
 *
 * Notes:
 */

#ifndef __SMC_H__
#define __SMC_H__

/********************************************************************/

// function prototypes
void sleep(void);
void deepsleep(void);
void enter_wait(void);
void enter_stop(uint8_t partial_stop_opt);
int32_t enter_vlpr(void);
void exit_vlpr(void);
void enter_vlps(void);
#if !defined(CPU_PKE18F512VLH15)
void enter_lls(void);
void enter_vlls3(void);
void enter_vlls2(void);
void enter_vlls1(void);
#endif
void enter_vlls0(uint8_t PORPO_value);
void enter_vlls0_nopor(void);

/********************************************************************/
#endif /* __SMC_H__ */
