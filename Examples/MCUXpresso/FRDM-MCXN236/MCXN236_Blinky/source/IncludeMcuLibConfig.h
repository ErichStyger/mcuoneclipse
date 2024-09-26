/*
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_MCXN       (1)
#define McuLib_CONFIG_CORTEX_M          (33)  /* MCXN947 is dual-core M33 */
#define McuLib_CONFIG_CPU_IS_KINETIS    (0)  /* disabling the default Kinetis */
/* ---------------------------------------------------------------------- */
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configMINIMAL_STACK_SIZE                    (500/sizeof(StackType_t))
#define configTOTAL_HEAP_SIZE                       (50*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
#define INCLUDE_vTaskEndScheduler                   (0)
#define configUSE_IDLE_HOOK                         (0)
#define configUSE_TICK_HOOK                         (0)
#define configUSE_MALLOC_FAILED_HOOK                (0)
#define configCHECK_FOR_STACK_OVERFLOW              (0)
#define configTIMER_TASK_STACK_DEPTH                (280/sizeof(StackType_t)) /* timer task */
/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING       "FRDM-MCXN947"
#define McuShell_CONFIG_MULTI_CMD_ENABLED         (1)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE (96)
#define McuShell_CONFIG_MULTI_CMD_SIZE            (48)
//#define McuShellUart_CONFIG_UART                  McuShellUart_CONFIG_UART_LPC845_USART0
#define McuShell_CONFIG_PROMPT_STRING             "MCXN947> "
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED          (1) /* might need to switch to -O1 if enabling this to fit into available flash space */
#define McuLog_CONFIG_USE_COLOR           (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER  (1)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE  (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_TIME  (0)

#endif /* INCLUDEMCULIBCONFIG_H_ */
