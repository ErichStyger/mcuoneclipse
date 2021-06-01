/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdbool.h>
#include "McuShell.h"
#include "McuDebounce.h"

typedef enum CLOCK_Mode_e {
  CLOCK_MODE_ON,
  CLOCK_MODE_OFF,
  CLOCK_MODE_TOGGLE,
} CLOCK_Mode_e;

typedef enum CLOCK_Notify_e { /* direct task notification bits */
  CLOCK_NOTIFY_BUTTON_PRESSED_USR       = (1<<0),
  CLOCK_NOTIFY_BUTTON_PRESSED_USR_LONG  = (1<<1),
  CLOCK_NOTIFY_BUTTON_PRESSED_RST       = (1<<2),
  CLOCK_NOTIFY_BUTTON_PRESSED_UP        = (1<<3),
  CLOCK_NOTIFY_BUTTON_PRESSED_DOWN      = (1<<4),
  CLOCK_NOTIFY_BUTTON_PRESSED_LEFT      = (1<<5),
  CLOCK_NOTIFY_BUTTON_PRESSED_RIGHT     = (1<<6),
  CLOCK_NOTIFY_BUTTON_PRESSED_MID       = (1<<7),
  CLOCK_NOTIFY_BUTTON_PRESSED_SET       = (1<<8),
} CLOCK_Notify_e;

void CLOCK_Notify(CLOCK_Notify_e msg);
void CLOCK_ButtonHandler(McuDbnc_EventKinds event, uint32_t buttons);
void CLOCK_On(CLOCK_Mode_e mode);

uint8_t CLOCK_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

bool CLOCK_GetClockIsOn(void);

void CLOCK_Init(void);

#endif /* CLOCK_H_ */
