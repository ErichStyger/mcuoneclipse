/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SRC_MCUWATCHDOG_H_
#define SRC_MCUWATCHDOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuWatchdog_config.h"
#if McuWatchdog_CONFIG_USE_WATCHDOG
#include "McuRTOS.h"
#include <stdint.h>

#include McuWatchdog_CONFIG_REPORT_ID_INCLUDE_HEADER_FILE

/* list of IDs to identify items monitored by the watchdog task */
typedef enum McuWatchdog_ReportID_e {
  #include McuWatchdog_CONFIG_REPORT_ID_INCLUDE_FILE
  McuWatchdog_REPORT_ID_NOF /* sentinel, must be last! */
} McuWatchdog_ReportID_e;

#define McuWatchdog_REPORT_ID_CURR_TASK (McuWatchdog_REPORT_ID_NOF) /* special id to report time for the current task, which has been registered earlier with McuWatchdog_SetTaskHandle()  */

/*!
 * \brief Initialize the report structure
 * @param id ID of the entry
 * @param name Name for the entry
 * @param msForOneSec Number of average milliseconds reporting time per second, usually 1000
 * @param minPercent Minimum percentage of time reporting needed
 * @param maxPercent Maximum percentage of allowed time reporting
 */
void McuWatchdog_InitReportEntry(McuWatchdog_ReportID_e id, const unsigned char *name, uint32_t msForOneSec, uint8_t minPercent, uint8_t maxPercent);

/*!
 * \brief Used to start measuring a time for later reporting
 * \return Number of RTOS ticks at the start, at the time of call.
 */
TickType_t McuWatchdog_ReportTimeStart(void);

/*!
 * \brief Report the time spent, which has been recorded with McuWatchdog_ReportTimeStart()
 * \param id Task ID
 * \param startTickCount Tick count previously recorded with McuWatchdog_ReportTimeStart()
 */
void McuWatchdog_ReportTimeEnd(McuWatchdog_ReportID_e id, TickType_t startTickCount) ;

/*!
 * \brief Delay a task with vTaskDelay for a given number of times, each time for ms, and report the delay.
 * \param id Task ID
 * \param ms Iteration delay time in milliseconds
 * \param nof Number of delays
 */
void McuWatchdog_DelayAndReport(McuWatchdog_ReportID_e id, uint32_t nof, uint32_t ms);

/*!
 * \brief Set the task handle for an id. With this we can report time using McuWatchdog_REPORT_ID_CURR_TASK
 * \param id ID of item
 * \param task FreeRTOS task handle
 */
void McuWatchdog_SetTaskHandle(McuWatchdog_ReportID_e id, TaskHandle_t task);

/*!
 * \brief Suspend checking for a given id
 * \param id ID of item to be suspended
 */
void McuWatchdog_SuspendCheck(McuWatchdog_ReportID_e id);

/*!
 * \brief Resume checking for a given id
 * \param id ID of item to be suspended
 */
void McuWatchdog_ResumeCheck(McuWatchdog_ReportID_e id);


/*!
 * \brief Report the time spent for an item (id)
 * \param id ID of item
 * \param ms Time in milliseconds
 */
void McuWatchdog_Report(McuWatchdog_ReportID_e id, uint32_t ms);

/*!
 * \brief Enable the watchdog timer. Do this early in the application.
 */
void McuWatchdog_EnableTimer(void);

/*!
 * \brief Module de-initialization.
 */
void McuWatchdog_Deinit(void);

/*!
 * \brief Module initialization. This creates the monitoring watchdog task.
 */
void McuWatchdog_Init(void);

#endif /* McuWatchdog_CONFIG_USE_WATCHDOG */

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* SRC_MCUWATCHDOG_H_ */
