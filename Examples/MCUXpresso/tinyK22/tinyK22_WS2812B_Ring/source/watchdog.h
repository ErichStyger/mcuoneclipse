/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include "platform.h"
#include "McuRTOS.h"
#include <stdint.h>

typedef enum {
  WDT_REPORT_ID_TASK_APP,
#if PL_CONFIG_USE_RS485
  WDT_REPORT_ID_TASK_RS485,
#endif
#if PL_CONFIG_USE_SHELL
  WDT_REPORT_ID_TASK_SHELL,
#endif
  WDT_REPORT_ID_NOF /* sentinel, must be last! */
} WDT_ReportID_e;

#define WDT_REPORT_ID_CURR_TASK (WDT_REPORT_ID_NOF) /* special id! */

void WDT_SetTaskHandle(WDT_ReportID_e id, TaskHandle_t task);
void WDT_Report(WDT_ReportID_e id, uint32_t ms);

void WDT_Init(void);

#endif /* WATCHDOG_H_ */
