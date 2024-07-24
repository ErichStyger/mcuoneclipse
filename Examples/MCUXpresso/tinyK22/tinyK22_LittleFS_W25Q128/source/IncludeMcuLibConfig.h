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

#define SIM_UIDH       /* FIX: SDK does not define this one, but should be! See https://mcuoneclipse.com/2020/11/30/getting-a-96bit-unique-id-for-each-kinetis-device-using-mcuxpresso-sdk/ */

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED   McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_LPC         (0)  /* LPC845 */
#define McuLib_CONFIG_CORTEX_M           (4)  /* K22 is a Cortex-M4 */
#define McuLib_CONFIG_CPU_IS_KINETIS     (1)  /* K22 is a Kinetis */
#define McuLib_CONFIG_CPU_VARIANT        McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configUSE_HEAP_SCHEME                 4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                (63*1024)
#define configUSE_HEAP_SECTION_NAME          (1)
#define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS"
#define configQUEUE_REGISTRY_SIZE            (70)
#define configMINIMAL_STACK_SIZE             (200/sizeof(StackType_t))
#define configTIMER_TASK_STACK_DEPTH         (400/sizeof(StackType_t))
#define configUSE_TIMERS                     (1)
#define INCLUDE_xTimerPendFunctionCall       (0 && configUSE_TIMERS)
#define configSYSTICK_USE_LOW_POWER_TIMER       (0)
#define configSYSTICK_LOW_POWER_TIMER_CLOCK_HZ  (CLOCK_GetFreq(kCLOCK_LpoClk))

/* performance counter: */
#define configGENERATE_RUN_TIME_STATS_USE_TICKS     (1)
#define configGET_RUNTIMER_COUNTER_VALUE_FROM_ISR   AppGetRuntimeCounterValueFromISR
#define configCONFIGURE_TIMER_FOR_RUNTIME_STATS     AppConfigureTimerForRuntimeStats
/* -------------------------------------------------*/
/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (1)
#define SYSVIEW_APP_NAME                     "tinyK22 LittleFS W25Q128"
#define SYSVIEW_DEVICE_NAME                  "NXP K22FN512"
#define McuSystemView_CONFIG_RTT_BUFFER_SIZE (512)
#define McuSystemView_CONFIG_RTT_CHANNEL     (1)
/* -------------------------------------------------*/
/* Percepio Tracealyzer */
#define configUSE_PERCEPIO_TRACE_HOOKS                  (0)
#define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START
/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "tinyK22 LittleFS W25Q128"
#define McuShell_CONFIG_MULTI_CMD_ENABLED             (1)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (256)
#define McuShell_CONFIG_MULTI_CMD_SIZE                (200) /* max size of each command */
#define McuShellUart_CONFIG_UART                      McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4
#define McuShell_CONFIG_PROMPT_STRING                 "W25Q128> "
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (150)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (1024)
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS          (2)
  #define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS        (2)
#else
  #define McuRTT_CONFIG_RTT_MAX_NUM_UP_BUFFERS          (1)
  #define McuRTT_CONFIG_RTT_MAX_NUM_DOWN_BUFFERS        (1)
#endif
/* -------------------------------------------------*/
/* Time/Date */
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (0) /* enable external I2C RTC */
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

//#define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC)
#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (1) /* if using external I2C RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                      (1)
#define McuLog_CONFIG_USE_COLOR                       (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER              (3) /* RTT, UART and USB CDC */
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE              (0)
#define McuLog_CONFIG_USE_RTT_DATA_LOGGER             (0)
#define McuLog_CONFIG_RTT_DATA_LOGGER_BUFFER_SIZE     (128)
/* -------------------------------------------------*/
/* RTC */
#define McuExtRTC_CONFIG_DEVICE                 3232  /* RTC device used */
/* -------------------------------------------------*/
/* EEPROM */
#define McuEE24_CONFIG_DEVICE_ID                32    /* AT24C32 */
#define McuEE24_CONFIG_DEVICE_I2C_ADDRESS_BITS  (7)   /* device is on address 0x57 */
#define McuEE24_CONFIG_HAS_WP_PIN               (0)   /* no WP Pin */
#define McuEE24_CONFIG_DO_ACKNOWLEDGE_POLLING   (0)   /* no acknowledge polling */
#define McuEE24_CONFIG_USE_TIMEOUT              (0)   /* no timeout */
/* ------------------- McuSPI --------------------------*/
#define MCUSPI_CONFIG_HW_TEMPLATE               MCUSPI_CONFIG_HW_TEMPLATE_KINETIS_K22_SPI1
#define MCUSPI_CONFIG_TRANSFER_BAUDRATE         (4*500000U)
/* -------------------------------------------------*/
/* LittleFS */
#define LITTLEFS_CONFIG_ENABLED                 (1)
#define MCUW25Q128_CONFIG_ENABLED               (1)
#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE   McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
/* -------------------------------------------------*/
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED              (0)
/* -------------------------------------------------*/
/* McuMinIni */
#define McuMinINI_CONFIG_FS                     McuMinINI_CONFIG_FS_TYPE_LITTLE_FS

#endif /* INCLUDEMCULIBCONFIG_H_ */
