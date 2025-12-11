/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef MCULIB_CONFIG_CONFIG_H_
#define MCULIB_CONFIG_CONFIG_H_

#define SIM_UIDH       /* FIX: K22 SDK does not define this one, but should be! See https://mcuoneclipse.com/2020/11/30/getting-a-96bit-unique-id-for-each-kinetis-device-using-mcuxpresso-sdk/ */

#define PL_CONFIG_IS_FRDM_K22F                      (0) /* FRDM board, otherwise tinyK22 */
#define PL_CONFIG_IS_LPC55S69_EVK                   (0) /* if EVK, otherwise MCU-Link Pro */
/* ---------------------------------------------------------------------------------------*/
/* SDK */
#if 1 /* LPC55S69 */
  #define McuLib_CONFIG_CPU_IS_LPC                    (1)
  #define McuLib_CONFIG_CPU_IS_LPC55xx                (1)
  #define McuLib_CONFIG_CPU_VARIANT                   McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
  #define McuLib_CONFIG_CORTEX_M                      (33)
#else /* tinyK22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS                (1)
  #define McuLib_CONFIG_CPU_VARIANT                   McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
#endif
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* ---------------------------------------------------------------------------------------*/
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)
#define configUSE_HEAP_SCHEME                       4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                       (63*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"
#define configUSE_IDLE_HOOK                         (0)
#define configUSE_TICK_HOOK                         (0)
#define configUSE_MALLOC_FAILED_HOOK                (1)
#define configCHECK_FOR_STACK_OVERFLOW              (1)
#define INCLUDE_vTaskEndScheduler                   (0)

#define configGENERATE_RUN_TIME_STATS               (1) /* 1: generate runtime statistics; 0: no runtime statistics */
#define configUSE_TRACE_FACILITY                    (1) /* 1: include additional structure members and functions to assist with execution visualization and tracing, 0: no runtime stats/trace */
#define configGENERATE_RUN_TIME_STATS_USE_TICKS     (1)
#if 0
/* performance counter: */
#ifndef __ASSEMBLER__ /* because of startup code in assembly */
  void AppConfigureTimerForRuntimeStats(void);
  #define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()   AppConfigureTimerForRuntimeStats()
  unsigned int AppGetRuntimeCounterValueFromISR(void);
  #define portGET_RUN_TIME_COUNTER_VALUE()           AppGetRuntimeCounterValueFromISR()
#endif
#endif
/* ------------------- McuRTT--------------------------------*/
#define McuRTT_CONFIG_RTT_UP_BUFFER_MODE              (SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (1024)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (150)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_IS_ENABLED               (1)
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
//#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_LINKSERVER
#define McuSemihost_CONFIG_LOG_ENABLED              (1)
#define McuSemihost_CONFIG_RETARGET_STDLIB          (0)
/* ---------------------------------------------------------------------- */
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "Power Measurement"
#define McuShell_CONFIG_PROMPT_STRING               "lpc> "
/* ------------------- McuShellUart -----------------------*/
#if McuLib_CONFIG_CPU_IS_KINETIS
  #if PL_CONFIG_IS_FRDM_K22F
    #define McuShellUart_CONFIG_UART    McuShellUart_CONFIG_UART_K22FN512_UART1_E1_E0
  #else
    #define McuShellUart_CONFIG_UART    McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4
  #endif
#elif McuLib_CONFIG_CPU_IS_LPC55xx
  #if PL_CONFIG_IS_LPC55S69_EVK
    #define McuShellUart_CONFIG_UART    McuShellUart_CONFIG_UART_LPC55S69_USART0
  #else /* MCU-Link Pro, UART FC1 on J26 */
    #define McuShellUart_CONFIG_UART    McuShellUart_CONFIG_UART_LPC55S69_USART1
  #endif
#endif
#define McuShellUart_CONFIG_UART_RX_QUEUE_LENGTH   (0x200)
/* ------------------- McuLog -----------------------*/
#define McuLog_CONFIG_IS_ENABLED            (1)
#define McuLog_CONFIG_USE_COLOR             (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE    (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_TIME    (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER    (2) /* UART and RTT */
#if 1
  #define McuLog_CONFIG_LOG_FILENAME          (1) /* if file names are used for the log */
  #define McuLog_CONFIG_LOG_LINE_NUMBER       (1) /* if line numbers are used for the log */
  #define McuLog_CONFIG_USE_FILE_MACRO        __FILE__
#endif

 /* Redefine the __FILE__ macro so it contains just the file name and no path
  * Add -Wno-builtin-macro-redefined to the compiler options to suppress the warning about this.
  * See https://mcuoneclipse.com/2021/01/23/assert-__file__-path-and-other-cool-gnu-gcc-tricks-to-be-aware-of/
  */
// #define __FILE__ (__builtin_strrchr("/"__BASE_FILE__, '/') + 1)
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED         (0)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED          (0)       /* 1: McuFlash is enabled; 0: McuFlash is disabled*/
/* ---------------------------------------------------------------------------------------*/
/* McuSPI */
#define MCUSPI_CONFIG_HW_TEMPLATE          MCUSPI_CONFIG_HW_TEMPLATE_LPC55S59_FC8 /* hardware template */
#define MCUSPI_CONFIG_TRANSFER_BAUDRATE    (2*1000000U)

#endif /* MCULIB_CONFIG_CONFIG_H_ */
