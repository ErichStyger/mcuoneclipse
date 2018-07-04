/*
 * SysView.c
 *
 *  Created on: 04.07.2018
 *      Author: Erich Styger
 */


#include "SysView.h"
#include "SEGGER_RTT.h"
#include "FreeRTOS.h"
#include "task.h"

#define SYSVIEW_DEVICE_NAME "FRDMK64F Cortex-M4"
#define SYSVIEW_RAM_BASE (0x1FFF0000)

extern SEGGER_RTT_CB _SEGGER_RTT;
extern const SEGGER_SYSVIEW_OS_API SYSVIEW_X_OS_TraceAPI;

/* The application name to be displayed in SystemViewer */
#ifndef SYSVIEW_APP_NAME
#define SYSVIEW_APP_NAME "SDK System view example"
#endif

/* The target device name */
#ifndef SYSVIEW_DEVICE_NAME
#define SYSVIEW_DEVICE_NAME "Generic Cortex device"
#endif

/* Frequency of the timestamp. Must match SEGGER_SYSVIEW_GET_TIMESTAMP in SEGGER_SYSVIEW_Conf.h */
#define SYSVIEW_TIMESTAMP_FREQ (configCPU_CLOCK_HZ)

/* System Frequency. SystemcoreClock is used in most CMSIS compatible projects. */
#define SYSVIEW_CPU_FREQ configCPU_CLOCK_HZ

/* The lowest RAM address used for IDs (pointers) */
#ifndef SYSVIEW_RAM_BASE
#define SYSVIEW_RAM_BASE 0x20000000
#endif

/*!
 * @brief Apply only for M0plus core. M4/M3 uses cycle counter.
 */
U32 SEGGER_SYSVIEW_X_GetTimestamp(void) {
    return __get_IPSR() ? xTaskGetTickCountFromISR() : xTaskGetTickCount();
}

/*!
 * @brief System View callback
 */
static void _cbSendSystemDesc(void) {
    SEGGER_SYSVIEW_SendSysDesc("N=" SYSVIEW_APP_NAME ",D=" SYSVIEW_DEVICE_NAME ",O=FreeRTOS");
    SEGGER_SYSVIEW_SendSysDesc("I#15=SysTick");
}

void SysView_Init(void) {
    SEGGER_SYSVIEW_Init(SYSVIEW_TIMESTAMP_FREQ, SYSVIEW_CPU_FREQ, &SYSVIEW_X_OS_TraceAPI, _cbSendSystemDesc);
    SEGGER_SYSVIEW_SetRAMBase(SYSVIEW_RAM_BASE);
}
