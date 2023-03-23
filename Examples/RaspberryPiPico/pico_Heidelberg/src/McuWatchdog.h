/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_WDT_H_
#define SRC_WDT_H_

#include "McuRTOS.h"
#include "app_platform.h"
#include <stdint.h>

#if PL_CONFIG_USE_WATCHDOG

/* list of IDs to identify items monitored by the watchdog task */
typedef enum {
  WDT_REPORT_ID_TASK_APP,
#if PL_CONFIG_USE_GUI
  WDT_REPORT_ID_TASK_GUI,
#endif
#if PL_CONFIG_USE_SHELL
  WDT_REPORT_ID_TASK_SHELL,
#endif
#if PL_CONFIG_USE_LIGHTS
  WDT_REPORT_ID_TASK_LIGHTS,
#endif
#if PL_CONFIG_USE_GUI_ENERGY_DASHBOARD
  WDT_REPORT_ID_TASK_EMONITOR,
#endif
#if PL_CONFIG_USE_ROAD
  WDT_REPORT_ID_TASK_ROAD,
#endif
  WDT_REPORT_ID_NOF /* sentinel, must be last! */
} WDT_ReportID_e;

#define WDT_REPORT_ID_CURR_TASK (WDT_REPORT_ID_NOF) /* special id to report time for the current task, which has been registered earlier with WDT_SetTaskHandle()  */

/*!
 * \brief Set the task handle for an id. With this we can report time using WDT_REPORT_ID_CURR_TASK
 * \param id ID of item
 * \param task FreeRTOS task handle
 */
void WDT_SetTaskHandle(WDT_ReportID_e id, TaskHandle_t task);

/*!
 * \brief Report the time spent for an item (id)
 * \param id ID of item
 * \param ms Time in milliseconds
 */
void WDT_Report(WDT_ReportID_e id, uint32_t ms);

/*!
 * \brief Enable the watchdog. Do this early in the application.
 */
void WDT_EnableWatchdog(void);

/*!
 * \brief Module initialization.
 */
void WDT_Init(void);

#endif /* PL_CONFIG_USE_WATCHDOG */

#endif /* SRC_WDT_H_ */
