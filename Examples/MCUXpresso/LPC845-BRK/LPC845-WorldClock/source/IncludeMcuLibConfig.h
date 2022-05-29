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

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED    McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_LPC         (1)  /* LPC845 */
#define McuLib_CONFIG_CPU_VARIANT        McuLib_CONFIG_CPU_VARIANT_NXP_LPC845
#define McuLib_CONFIG_CORTEX_M           (0)  /* LPC845 is a Cortex-M0+ */
#define McuLib_CONFIG_CPU_IS_KINETIS     (0)  /* disabling the default Kinetis */

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configTOTAL_HEAP_SIZE                (11*1024)
//#define configUSE_HEAP_SECTION_NAME        (1)
//#define configHEAP_SECTION_NAME_STRING     ".bss.$SRAM_LOWER.FreeRTOS"
#define configMINIMAL_STACK_SIZE             (200/sizeof(StackType_t))
#define configTIMER_TASK_STACK_DEPTH         (400/sizeof(StackType_t))
#define configUSE_TIMERS                     (0)
#define INCLUDE_xTimerPendFunctionCall       (0)
#define configUSE_TRACE_FACILITY              (0)
#define configGENERATE_RUN_TIME_STATS         (0)

/* -------------------------------------------------*/
/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0)
#define SYSVIEW_APP_NAME                     "LPC845 WorldClock"
#define SYSVIEW_DEVICE_NAME                  "LPC845"
/* -------------------------------------------------*/
/* Percepio Tracealyzer */
#define configUSE_PERCEPIO_TRACE_HOOKS                  (0)
#define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START
/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "LPC845 WorldClock"
#define McuShell_MULTI_CMD_ENABLED                    (0)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (96)
/* -------------------------------------------------*/
/* McuUart485 */
#define McuUart485_CONFIG_USE_RS_485                  (1)

#endif /* INCLUDEMCULIBCONFIG_H_ */
