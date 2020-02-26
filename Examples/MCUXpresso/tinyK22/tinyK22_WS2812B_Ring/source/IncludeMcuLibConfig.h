/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option
Instructions:
 - Remove the 'Template_' from the name and place this file into your 'src' folder.
 - Include it with the -include compiler option with:  "${ProjDirPath}/source/IncludeMcuLibConfig.h"
 - Add the following to the -I compiler option:
../McuLib
../McuLib/config
../McuLib/config/fonts
../McuLib/fonts
../McuLib/src
../McuLib/FreeRTOS/Source/include
../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuLib/SEGGER_RTT
../McuLib/SEGGER_Sysview
../McuLib/TraceRecorder/config
../McuLib/TraceRecorder/include
../McuLib/TraceRecorder/streamports/Jlink_RTT/include
../McuLib/HD44780
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define McuLib_CONFIG_CPU_IS_KINETIS                (1)

#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_HEAP_SCHEME                       4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                       (32*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"

/* performance counter: */
#define configGENERATE_RUN_TIME_STATS_USE_TICKS     (1)
#define configGET_RUNTIMER_COUNTER_VALUE_FROM_ISR   AppGetRuntimeCounterValueFromISR
#define configCONFIGURE_TIMER_FOR_RUNTIME_STATS     AppConfigureTimerForRuntimeStats


/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)
#define SYSVIEW_APP_NAME                            "tinyK22 LedRing"
#define SYSVIEW_DEVICE_NAME                         "NXP K22FN512"

/* Percepio Tracealyzer */
#define configUSE_PERCEPIO_TRACE_HOOKS                  (0)
#define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START

/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "tinyK22 LedRing"
#define McuShell_MULTI_CMD_ENABLED                    (0)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (96)

#endif /* INCLUDEMCULIBCONFIG_H_ */
