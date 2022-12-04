/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "app_platform.h"
#if PL_CONFIG_USE_BUTTONS
#include "buttons.h"
#include "McuDebounce.h"

typedef enum {
  App_Event_Dummy,
} APP_Event;

void APP_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind);
#endif

void APP_Run(void);

#endif /* __APPLICATION_H__ */
