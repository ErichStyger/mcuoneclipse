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
#define McuShellUart_CONFIG_UART                      McuShellUart_CONFIG_UART_K22FN512_UART1
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (150)
#define McuRTT_CONFIG_BLOCKING_SEND                   (0)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (100)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (20)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (1024)
/* -------------------------------------------------*/
/* FatFS */
#define McuFatFS_CONFIG_DEFAULT_DRIVE_STRING   "0:/" /* 0: is for the SPI SD card type, and 1: for USB, see diskio.h */
/* -------------------------------------------------*/
/* MinINI */
#define McuMinINI_CONFIG_FS                           McuMinINI_CONFIG_FS_TYPE_FAT_FS
/* -------------------------------------------------*/
/* Time/Date */
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (0) /* enable external I2C RTC */
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

#define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS)
#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (0) /* if using external I2C RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */

#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_YEAR  2020
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_MONTH 6
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_DAY   1

#define McuTimeDate_CONFIG_TICK_TIME_MS               50
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_USE_FILE                  (1)
/* -------------------------------------------------*/
/* FatFS */
#define McuLib_CONFIG_USE_FAT_FS                (1)

#endif /* INCLUDEMCULIBCONFIG_H_ */
