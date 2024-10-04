/*
 * Copyright (c) 2023-2024 Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef MCULIB_CONFIG_CONFIG_H_
#define MCULIB_CONFIG_CONFIG_H_

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_KINETIS                (0)
#define McuLib_CONFIG_CORTEX_M                      (0) /* RP2040 is a Cortex-M0+ */
#define McuLib_CONFIG_CPU_IS_RPxxxx                 (1)
#define McuLib_CONFIG_CPU_VARIANT                   McuLib_CONFIG_CPU_VARIANT_RP2040
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_RPI_PICO
/* ---------------------------------------------------------------------- */
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configMINIMAL_STACK_SIZE                    (500/sizeof(StackType_t))
#define configTOTAL_HEAP_SIZE                       (50*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
#define INCLUDE_vTaskEndScheduler                   (1)
#define configUSE_IDLE_HOOK                         (0)
#define configUSE_TICK_HOOK                         (0)
#define configUSE_MALLOC_FAILED_HOOK                (0)
#define configCHECK_FOR_STACK_OVERFLOW              (0)
/* ---------------------------------------------------------------------------------------*/
/* Unity */
#if ENABLE_UNIT_TESTS
    #if !__ASSEMBLER__ /* set if file is included by GNU as (assembler). Do not include normal C header files if running the assembler for example to assemble the pico startup code */
    #include "McuUnity.h"
    #define UNITY_OUTPUT_CHAR(a)                        McuUnity_putc(a)
    #define UNITY_OUTPUT_FLUSH()                        McuUnity_flush()
    #define UNITY_OUTPUT_START()                        McuUnity_start()
    #define UNITY_OUTPUT_COMPLETE()                     McuUnity_complete()
    #define UNITY_OUTPUT_COLOR                          /* use colored output */
    #endif
#endif
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_IS_ENABLED               (1)
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
#define McuSemihost_CONFIG_LOG_ENABLED              (0)
#define McuSemihost_CONFIG_RETARGET_STDLIB          (1)
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED                 (0)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/
/* McuCoverage */
#define McuCoverage_CONFIG_IS_ENABLED               (1)
#define McuCoverage_CONFIG_USE_FREESTANDING         (0 && McuCoverage_CONFIG_IS_ENABLED)
/* ---------------------------------------------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_USE_RTT_CONSOLE           (1)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (1) /* RTT and USB CDC */
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_TIME        (0)
/* ---------------------------------------------------------------------------------------*/
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING     "pico_USB-Host"
/* ---------------------------------------------------------------------------------------*/

#endif /* MCULIB_CONFIG_CONFIG_H_ */
