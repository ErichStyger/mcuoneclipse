/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_KINETIS                (0)
#define McuLib_CONFIG_CORTEX_M                      (0) /* RP2040 is a Cortex-M0+ */
#define McuLib_CONFIG_CPU_IS_RPxxxx                 (1)
#define McuLib_CONFIG_CPU_VARIANT                   McuLib_CONFIG_CPU_VARIANT_RP2040
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_RPI_PICO
/* ---------------------------------------------------------------------------------------*/
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configMINIMAL_STACK_SIZE                    (500)
#define configTOTAL_HEAP_SIZE                       (52*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
/* ---------------------------------------------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (256)
/* ---------------------------------------------------------------------------------------*/
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING           "picoBLE"
#define McuShell_CONFIG_PROMPT_STRING                 "pico> "
#define McuShell_CONFIG_MULTI_CMD_ENABLED             (1)
#define McuShell_CONFIG_MULTI_CMD_SIZE                (96)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE     (128)
/* ---------------------------------------------------------------------------------------*/
/* McuTimeDate */
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_HOUR  0
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_MIN   0
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_SEC   0
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_YEAR  2023
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_MONTH 1
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_DAY   1
/* ---------------------------------------------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (2)
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
/* ---------------------------------------------------------------------------------------*/
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED          (1) /* enable for MinINI with Flash FS */
/* ---------------------------------------------------------------------------------------*/
/* MinINI */
#define McuMinINI_CONFIG_FS                         (McuMinINI_CONFIG_FS_TYPE_FLASH_FS)
#define McuMinINI_CONFIG_FLASH_NVM_ADDR_START       ((XIP_BASE+2048*1024)-(McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE)) /* pico has 2 MB Flash, starting from XIP_BASE */
#define McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS       (1)
#define McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE       (0x1000) /* just use a single block */
#define McuMinINI_CONFIG_FLASH_NVM_MAX_DATA_SIZE    (0x1000) /* must be multiple of 4K */
#define McuMinINI_CONFIG_BUFFER_SIZE                (128) /* maximum line and path length */
/* ---------------------------------------------------------------------------------------*/
