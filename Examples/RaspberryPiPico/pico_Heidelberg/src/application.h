/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "McuShell.h"

#if PL_CONFIG_USE_BUTTONS
  #include "buttons.h"
  #include "McuDebounce.h"

  void APP_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind);
#endif

#define APP_VERSION_STR  "v1.0b"

uint8_t App_GetSensorValues(float *temperature, float *humidity);

uint8_t App_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void APP_Run(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __APPLICATION_H__ */
