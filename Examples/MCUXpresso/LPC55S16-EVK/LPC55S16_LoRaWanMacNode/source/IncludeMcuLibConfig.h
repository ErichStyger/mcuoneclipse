/*
 * Copyright (c) 2019-2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_KINETIS                (0)
#define McuLib_CONFIG_CPU_IS_LPC                    (1)
#define McuLib_CONFIG_CPU_IS_LPC55xx                (1)
#define McuLib_CONFIG_CPU_VARIANT                   McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* ---------------------------------------------------------------------------------------*/
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
#define configUSE_HEAP_SCHEME                       4 /* either 1 (only alloc), 2 (alloc/free), 3 (malloc), 4 (coalesc blocks), 5 (multiple blocks), 6 (newlib) */
#define configTOTAL_HEAP_SIZE                       (24*1024)
/* ---------------------------------------------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "LPC55S16_LoRaMacNode"
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE   (64)  /* buffer size for parsing, must be able to include multiple commands */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP            (4*1024)
#if McuLib_CONFIG_SDK_USE_FREERTOS
#define McuShellUart_CONFIG_UART 					          McuShellUart_CONFIG_UART_LPC55S16_USART0
#endif
#define McuShell_CONFIG_MULTI_CMD_ENABLED           (1)
#define McuShell_CONFIG_MULTI_CMD_SIZE              (96) /* maximum size of a single command in a multi-command string */
#define McuShell_CONFIG_PROMPT_STRING               "LoRa> "
#define McuShell_CONFIG_ECHO_ENABLED                (1)
/* ---------------------------------------------------------------------------------------*/
/* MinINI */
/* see as well platform.h about the memory layout and EEPROM reservation */
#define McuMinINI_CONFIG_FS                         McuMinINI_CONFIG_FS_TYPE_FLASH_FS
#define McuMinINI_CONFIG_FLASH_NVM_ADDR_START      (((0+244*1024)-(McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE))) /* last block in FLASH, start address of configuration data in flash */
#define McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE      (0x200)   /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#define McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS      (4)       /* number of flash blocks */
#define McuMinINI_CONFIG_FLASH_NVM_MAX_DATA_SIZE   (McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS * McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE) /* MUST be multiple of 512 for LPC55! */
/* ---------------------------------------------------------------------------------------*/
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED  (1)
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (1)
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (1)
/* -----------------------------------------------------*/
/* McuTimeDate */
#define McuTimeDate_CONFIG_TICK_TIME_MS                            (100)
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (0) /* enable external I2C RTC */
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

//#define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC)
#define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS)

#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (0) /* if using external I2C RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */
/* ---------------------------------------------------------------------------------------*/
