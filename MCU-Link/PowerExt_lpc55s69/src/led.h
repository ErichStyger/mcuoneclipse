/*!
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __LED_H_
#define __LED_H_

#include "platform.h"

void Led1_On(void);

void Led1_Off(void);

void Led1_Toggle(void);

#define LED_CONFIG_HAS_2_LED   (McuLib_CONFIG_CPU_IS_LPC55xx || PL_CONFIG_IS_FRDM_K22F)

#if LED_CONFIG_HAS_2_LED
  void Led2_On(void);

  void Led2_Off(void);

  void Led2_Toggle(void);
#endif

void Led_Init(void);

 #endif /* __LED_H_ */