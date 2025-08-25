/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#define SIM_UIDH       /* FIX: SDK does not define this one, but should be! See https://mcuoneclipse.com/2020/11/30/getting-a-96bit-unique-id-for-each-kinetis-device-using-mcuxpresso-sdk/ */

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
#define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
#define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* ---------------------------------------------------------------------------------------*/
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
#define configUSE_HEAP_SCHEME                       4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                       (32*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"
#define configUSE_IDLE_HOOK                         (0)
#define configUSE_TICK_HOOK                         (0)
#define configUSE_MALLOC_FAILED_HOOK                (0)
#define configCHECK_FOR_STACK_OVERFLOW              (0)
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_IS_ENABLED               (1)
//#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_LINKSERVER
#define McuSemihost_CONFIG_LOG_ENABLED              (0)
/* -----------------------------------------------------*/
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING              "LPC55S69"
#define McuShell_CONFIG_ECHO_ENABLED                     (1)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE        (96)
#define McuSemihost_CONFIG_RETARGET_STDLIB               (1)
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                    (1)
#define McuLog_CONFIG_USE_FILE                      (0)
#define McuLog_CONFIG_USE_COLOR                     (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE            (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_TIME            (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER            (2) /* UART and RTT */
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED                     (1)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/
/* McuShellUart */
#define McuShellUart_CONFIG_UART                         McuShellUart_CONFIG_UART_LPC55S16_USART0
/* -----------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP          (1*1024)
#define McuRTT_CONFIG_BLOCKING_SEND               (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS    (20)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS       (5)
/* ---------------------------------------------------------------------------------------*/
