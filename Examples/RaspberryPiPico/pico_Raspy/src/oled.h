/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MAIN_OLED_H_
#define MAIN_OLED_H_

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#if PL_CONFIG_USE_BUTTONS
  #include "buttons.h"
  #include "McuDebounce.h"

  void OLED_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind);
#endif

void OLED_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* MAIN_OLED_H_ */
