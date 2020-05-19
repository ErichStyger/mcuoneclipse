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
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#define McuLib_CONFIG_CPU_IS_KINETIS                (1)  /* default CPU is NXP Kinetis */
//#define McuLib_CONFIG_CPU_IS_LPC        (1)  /* NXP LPC845 */
//#define McuLib_CONFIG_CPU_IS_IMXRT      (0)  /* NXP i.MX RT */
//#define McuLib_CONFIG_CPU_IS_LPC55xx    (0)  /* NXP LPC55xx */
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configTOTAL_HEAP_SIZE                       (24*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"
#define configQUEUE_REGISTRY_SIZE                   (10)
/* -------------------------------------------------*/
/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)
#define SYSVIEW_APP_NAME                            "FRDM-K22F"
#define SYSVIEW_DEVICE_NAME                         "NXP K22FN512"
/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "FRDM-K22F"
#define McuShell_CONFIG_MULTI_CMD_ENABLED             (0)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (64)
#define McuShell_CONFIG_MULTI_CMD_SIZE                (128) /* max size of each command */
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (100)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (20)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (128)
/* -------------------------------------------------*/
/* FatFS */
#define McuFatFS_CONFIG_DEFAULT_DRIVE_STRING   "4:/" /* 4 is for the SPI SD card type in the SDK */
/* -------------------------------------------------*/
/* MinINI */
#define McuMinINI_CONFIG_FS                           McuMinINI_CONFIG_FS_TYPE_FAT_FS
/* -------------------------------------------------*/

#endif /* INCLUDEMCULIBCONFIG_H_ */
