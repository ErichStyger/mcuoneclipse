/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "platform.h"
#if PL_CONFIG_PULL_NAV
#include "nav.h"
#include "McuGPIO.h"
#include "McuLog.h"

/* GPIO Pin Numbers */
typedef enum NavButtons_e {
  NavButton_Up_Pin = 15,
  NavButton_Down_Pin = 14,
  NavButton_Left_Pin = 13,
  NavButton_Right_Pin = 12,
  NavButton_Mid_Pin = 11,
} NavButtons_e;

static McuGPIO_Handle_t navHandles[5];

void Nav_Init(void) {
  McuGPIO_Config_t config;

  McuGPIO_GetDefaultConfig(&config);

  config.hw.pull = McuGPIO_PULL_UP;
  config.isInput = true;

  config.hw.pin = NavButton_Up_Pin;
  navHandles[0] = McuGPIO_InitGPIO(&config);
  if (navHandles[0]==NULL) {
    McuLog_fatal("failed creating pin");
  }
  config.hw.pin = NavButton_Down_Pin;
  navHandles[1] = McuGPIO_InitGPIO(&config);
  if (navHandles[1]==NULL) {
    McuLog_fatal("failed creating pin");
  }
  config.hw.pin = NavButton_Left_Pin;
  navHandles[2] = McuGPIO_InitGPIO(&config);
  if (navHandles[2]==NULL) {
    McuLog_fatal("failed creating pin");
  }
  config.hw.pin = NavButton_Right_Pin;
  navHandles[3] = McuGPIO_InitGPIO(&config);
  if (navHandles[3]==NULL) {
    McuLog_fatal("failed creating pin");
  }
  config.hw.pin = NavButton_Mid_Pin;
  navHandles[4] = McuGPIO_InitGPIO(&config);
  if (navHandles[4]==NULL) {
    McuLog_fatal("failed creating pin");
  }
}

#endif /* PL_CONFIG_PULL_NAV */
