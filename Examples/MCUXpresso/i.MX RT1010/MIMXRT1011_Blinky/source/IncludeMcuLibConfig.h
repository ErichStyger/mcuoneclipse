/*
 * Copyright (c) 2019, Erich Styger
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
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_KINETIS    (0)  /* default CPU is NXP Kinetis */
#define McuLib_CONFIG_CPU_IS_IMXRT      (1)
//#define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_IMXRT1064

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configTOTAL_HEAP_SIZE                (24*1024)
#define configUSE_HEAP_SCHEME                (4)  /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
//#define configUSE_HEAP_SECTION_NAME                 (1)
//#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"

/* performance counter: see https://mcuoneclipse.com/2018/08/02/tutorial-using-runtime-statistics-with-amazon-freertos-v10/ */
#define configGENERATE_RUN_TIME_STATS_USE_TICKS     (1)

/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
#define SYSVIEW_APP_NAME                            "i.MX RT1010 with FreeRTOS"
#define SYSVIEW_DEVICE_NAME                         "NXP i.MX RT1010"

/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "i.MX RT1010 with FreeRTOS"
#define McuShell_MULTI_CMD_ENABLED                    (0)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (96)

#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (100)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (20)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (1024)

#endif /* INCLUDEMCULIBCONFIG_H_ */
