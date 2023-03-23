/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_MCUWATCHDOG_H_
#define SRC_MCUWATCHDOG_H_

#include "McuWatchdog_config.h"
#if McuWatchdog_CONFIG_USE_WATCHDOG
#include "McuRTOS.h"
#include "app_platform.h"
#include <stdint.h>

#define WDT_REPORT_ID_CURR_TASK (WDT_REPORT_ID_NOF) /* special id to report time for the current task, which has been registered earlier with WDT_SetTaskHandle()  */

/*!
 * \brief Set the task handle for an id. With this we can report time using WDT_REPORT_ID_CURR_TASK
 * \param id ID of item
 * \param task FreeRTOS task handle
 */
void McuWatchdog_SetTaskHandle(WDT_ReportID_e id, TaskHandle_t task);

/*!
 * \brief Report the time spent for an item (id)
 * \param id ID of item
 * \param ms Time in milliseconds
 */
void McuWatchdog_Report(WDT_ReportID_e id, uint32_t ms);

/*!
 * \brief Enable the watchdog timer. Do this early in the application.
 */
void McuWatchdog_EnableTimer(void);

/*!
 * \brief Module initialization. This creates the monitoring watchdog task.
 */
void McuWatchdog_Init(void);

#endif /* McuWatchdog_CONFIG_USE_WATCHDOG */

#endif /* SRC_MCUWATCHDOG_H_ */
