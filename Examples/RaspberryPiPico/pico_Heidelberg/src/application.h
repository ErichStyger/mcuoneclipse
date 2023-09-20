/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "platform.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if PL_CONFIG_USE_BUTTONS
  #include "buttons.h"
  #include "McuDebounce.h"

  void APP_OnButtonEvent(BTN_Buttons_e button, McuDbnc_EventKinds kind);
#endif

#define APP_VERSION_STR  "v1.0b"

uint8_t App_GetSensorValues(float *temperature, float *humidity);

#if PL_CONFIG_USE_SHELL
  #include "McuShell.h"
  uint8_t App_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
#endif

void App_Run(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* __APPLICATION_H__ */
