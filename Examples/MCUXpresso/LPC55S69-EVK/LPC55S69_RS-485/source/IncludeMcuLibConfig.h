/*
 * Copyright (c) 2016-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#define McuLib_CONFIG_CPU_IS_KINETIS    (0)  /* LPC family */
#define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
#define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
#define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS          (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS    (0)
#define configTOTAL_HEAP_SIZE                   (24*1024)
/* -----------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING              "LPC55S59"
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

#endif /* INCLUDEMCULIBCONFIG_H_ */
