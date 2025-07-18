/*
 * Copyright (c) 2016-2020, Erich Styger
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
../McuLib/TraceRecorder
../McuLib/TraceRecorder/config
../McuLib/TraceRecorder/include
../McuLib/TraceRecorder/streamports/Jlink_RTT/include
../McuLib/HD44780
../McuLib/FatFS
../McuLib/FatFS/source
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* global platform configuration */
#define PL_CONFIG_USE_LORA_SHIELD         (0) /* if using the LoRa Shield developed by Corsin Obrist */

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       (McuLib_CONFIG_CPU_VARIANT_NXP_LPC845) /* for LPC need to specify the actual device */
#elif 1 /* example configuration for LPC55S16 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
/* note: M33 port not functional yet! */
  #define configRUN_FREERTOS_SECURE_ONLY (0)
  #define configENABLE_TRUSTZONE         (0)
  #define configENABLE_MPU               (0)
  #define configENABLE_FPU               (1)
  #define configMINIMAL_SECURE_STACK_SIZE  (600)

#elif 0 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS          (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS    (0)
#define configTOTAL_HEAP_SIZE                   (24*1024)
/* #define configUSE_HEAP_SECTION_NAME          (1) */
/* #define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS" */
/* ---------------------------------------------------------------------------------------*/
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED                    (0) /* enable McuFlash module */
#define McuFlash_CONFIG_NOF_BLOCKS                    (32) /* number of flash blocks */
#define McuFlash_CONFIG_MEM_START                     (((0+244*1024)-((McuFlash_CONFIG_NOF_BLOCKS)*(McuFlash_CONFIG_FLASH_BLOCK_SIZE))))
/* -----------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING              "LPC55S16"
#define McuShell_CONFIG_ECHO_ENABLED                     (1)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE        (96)
#define McuShellUart_CONFIG_UART                         McuShellUart_CONFIG_UART_LPC55S16_USART0
/* -----------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP          (1*1024)
#define McuRTT_CONFIG_BLOCKING_SEND               (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS    (20)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS       (5)
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (2)
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
/* -----------------------------------------------------*/
/* McuTimeDate */
#define McuTimeDate_CONFIG_TICK_TIME_MS                            (100)
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
#if PL_CONFIG_USE_LORA_SHIELD
  #define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (1) /* enable external I2C RTC */
#else
  #define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (0) /* not using external I2C RTC */
#endif
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

#if PL_CONFIG_USE_LORA_SHIELD
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC)
#else
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS)
#endif

#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
#if PL_CONFIG_USE_LORA_SHIELD
  #define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (1) /* if using external I2C RTC */
#else
  #define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (0) /* if using external I2C RTC */
#endif
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */
/* -----------------------------------------------------*/
/* McuWait */
#define McuWait_CONFIG_USE_CYCLE_COUNTER         (1)
/* -----------------------------------------------------*/
/* McuSWO */
#define McuSWO_CONFIG_HAS_SWO         (0) /* enable SWO support */
//#define McuSWO_CONFIG_SPEED_BAUD      (115200) /* J-Link supports up to 5625 kHz */
//#define McuSWO_CONFIG_SPEED_BAUD      (5625000) /* J-Link supports up to 5625 kHz */
#define McuSWO_CONFIG_SPEED_BAUD      (9300000) /* J-Link could support up to 9.6 MHz */
//#define McuSWO_CONFIG_SPEED_BAUD      (96000000) /* needed for LinkServer and MCUXpresso IDE 11.5.0 */
#define McuSWO_CONFIG_DO_MUXING       (1) /* use own muxing */
#define McuSWO_CONFIG_DO_CLOCKING     (1) /* do clock settings */
#define McuSWO_CONFIG_DO_SWO_INIT     (1) /* SWO configuration is done by module */
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_IS_ENABLED               (1)
//#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_LINKSERVER
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED                 (0)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/


#endif /* INCLUDEMCULIBCONFIG_H_ */
