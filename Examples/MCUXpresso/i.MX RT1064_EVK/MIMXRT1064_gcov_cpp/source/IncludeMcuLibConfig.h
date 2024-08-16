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

#define SIM_UIDH    /* fix for wrong SIM_GetUniqueID() in the SDK */

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED   McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_LPC         (0)  /* not LPC */
#define McuLib_CONFIG_CORTEX_M           (7)  /* Cortex-M^7 */
#define McuLib_CONFIG_CPU_IS_KINETIS     (0)  /* not Kinetis */
#define McuLib_CONFIG_CPU_IS_IMXRT       (1)

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)
#define configUSE_HEAP_SCHEME                (4) /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                (8*1024)
#define configUSE_HEAP_SECTION_NAME          (1)
#define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS"
#define configQUEUE_REGISTRY_SIZE            (16)
#define configMINIMAL_STACK_SIZE             (600/sizeof(StackType_t))
#define configTIMER_TASK_STACK_DEPTH         (600/sizeof(StackType_t))
#define configUSE_TIMERS                     (0)
#define INCLUDE_xTimerPendFunctionCall       (0)
#define INCLUDE_vTaskEndScheduler            (1)
#define configSYSTICK_USE_LOW_POWER_TIMER       (0)
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ  (CLOCK_GetFreq(kCLOCK_LpoClk))

/* performance counter: */
#define configGENERATE_RUN_TIME_STATS_USE_TICKS     (1)
#define configGET_RUNTIMER_COUNTER_VALUE_FROM_ISR   AppGetRuntimeCounterValueFromISR
#define configCONFIGURE_TIMER_FOR_RUNTIME_STATS     AppConfigureTimerForRuntimeStats
/* -------------------------------------------------*/
/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0)
#define SYSVIEW_APP_NAME                     "K64 gcov"
#define SYSVIEW_DEVICE_NAME                  "NXP K64F"
#define McuSystemView_CONFIG_RTT_BUFFER_SIZE (512)
#define McuSystemView_CONFIG_RTT_CHANNEL     (2)
/* -------------------------------------------------*/
/* Percepio Tracealyzer */
#define configUSE_PERCEPIO_TRACE_HOOKS                  (0)
#define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START
/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "K64 gcov"
#define McuShell_CONFIG_MULTI_CMD_ENABLED             (1)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (256)
#define McuShell_CONFIG_MULTI_CMD_SIZE                (200) /* max size of each command */
#define McuShellUart_CONFIG_UART                      McuShellUart_CONFIG_UART_NONE
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (150)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (128)
#define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS          (1)
#define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS        (1)
/* ------------------- I2C ---------------------------*/
#define CONFIG_USE_HW_I2C                             (0) /* if using HW I2C, otherwise use software bit banging */
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT       (0)
#define McuGenericI2C_CONFIG_USE_ON_REQUEST_BUS_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX                (0 && McuLib_CONFIG_SDK_USE_FREERTOS)
/* -------------------------------------------------*/
/* stepper motor driver */
#define McuX12_017_CONFIG_QUAD_DRIVER                 (1)  /* using quad driver */
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                      (1)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE              (0)
#define McuLog_CONFIG_USE_RTT_DATA_LOGGER             (0)
#define McuLog_CONFIG_RTT_DATA_LOGGER_BUFFER_SIZE     (128)
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED                 (1)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_IS_ENABLED               (1)
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
//#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_PEMICRO
#define McuSemihost_CONFIG_RETARGET_STDLIB          (0) /* _kill, _exit, _getpid, _sbrk */
/* -------------------------------------------------*/
/* McuCoverage */
#define McuCoverage_CONFIG_IS_ENABLED           (1)
#define McuCoverage_CONFIG_USE_FREESTANDING     (0)

#endif /* INCLUDEMCULIBCONFIG_H_ */
