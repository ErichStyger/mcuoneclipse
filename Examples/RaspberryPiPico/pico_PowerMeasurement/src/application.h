/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "platform.h"

#if PL_CONFIG_USE_DEBOUNCE
    #include "buttons.h"
    #include "McuDebounce.h"

    void App_OnDebounceButtonEvent(Buttons_e button, McuDbnc_EventKinds kind);
#endif

#if PL_CONFIG_USE_BUTTONS_ISR
  #include <stdint.h>
  void App_OnISRButtonPressed(uint32_t buttonBits);
#endif

#if PL_CONFIG_USE_FROM_ISR_YIELD
  #include "McuRTOS.h"
  BaseType_t App_SendSignalFromISR(void);
#endif

void App_Run(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __APPLICATION_H__ */
