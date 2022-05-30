/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define McuLib_USE_ASAN                             (1) /* if using address sanitizer */

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for LPC55xx */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 1 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_HEAP_SCHEME                       4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                       (16*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"

#define configUSE_TICKLESS_IDLE                     (0)

#define configTICK_RATE_HZ                          (1000)

/* -----------------------------------------------------*/
/* performance counter: */
#include <stdint.h>
#define configGENERATE_RUN_TIME_STATS_USE_TICKS     (0)
extern void AppConfigureTimerForRuntimeStats(void);
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()   AppConfigureTimerForRuntimeStats()
extern uint32_t AppGetRuntimeCounterValueFromISR(void);
#define portGET_RUN_TIME_COUNTER_VALUE()           AppGetRuntimeCounterValueFromISR()
/* -----------------------------------------------------*/
/* Segger SystemViewer: */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        	(1)
#define SYSVIEW_APP_NAME                            	"FreeRTOS on tinyK22"
#define SYSVIEW_DEVICE_NAME                         	"NXP K22FN512"
/* -----------------------------------------------------*/
/* Percepio Tracealyzer */
#define configUSE_PERCEPIO_TRACE_HOOKS                  (0)
#define McuPercepio_CONFIG_START_TRACE_IN_STARTUP_MODE  TRC_START
/* -----------------------------------------------------*/
/* Shell */
#define McuShellUart_CONFIG_UART             McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4
#define McuShell_CONFIG_PROJECT_NAME_STRING  "tinyK22 FatFS"
#define McuShell_CONFIG_PROMPT_STRING        "tiny> "
#define McuShell_CONFIG_ECHO_ENABLED         (1)
#define McuShell_CONFIG_HISTORY_ENABLED      (1)
#define McuShell_CONFIG_HISTORY_NOF_ITEMS    (3)
#define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT  /*kCLOCK_Osc0ErClkUndiv */ kCLOCK_PllFllSelClk  /* has to match Clocks setting! */
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (150)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (5)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (1024)
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS             (1)
#define McuFatFS_CONFIG_DEFAULT_DRIVE_STRING   "0:/" /* 0: is for the SPI SD card type, and 1: for USB, see diskio.h */
#define McuFatFS_CONFIG_HAS_CARD_DETECT_PIN           (1)
#define McuFatFS_CONFIG_CARD_DETECT_GPIO              GPIOC
#define McuFatFS_CONFIG_CARD_DETECT_PORT              PORTC
#define McuFatFS_CONFIG_CARD_DETECT_PIN               0U
#define McuFatFS_CONFIG_CARD_DETECT_PULL              McuGPIO_PULL_DOWN
#define McuFatFS_CONFIG_CARD_DETECT_IS_HIGH_ACTIVE    (1)
#define McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN         (0)
/* -------------------------------------------------*/
/* MinINI */
#define McuMinINI_CONFIG_FS                           McuMinINI_CONFIG_FS_TYPE_FAT_FS
/* -----------------------------------------------------*/
/* time/Date */
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC  (1)
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_YEAR  2020
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_MONTH 6
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_DAY   14
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_HOUR 10
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_MIN 12
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_SEC 30
//#define McuTimeDate_CONFIG_TICK_TIME_MS         (50)
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (2)
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)

#endif /* INCLUDEMCULIBCONFIG_H_ */
