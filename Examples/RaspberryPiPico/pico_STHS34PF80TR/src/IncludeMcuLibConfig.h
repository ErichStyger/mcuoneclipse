/*
 * Copyright (c) 2023-2025 Erich Styger
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
#define configMINIMAL_STACK_SIZE                    (500)
#define configTOTAL_HEAP_SIZE                       (64*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1) /* 0: do not block if buffer full */
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (5)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (1)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (2*1024)
/* ---------------------------------------------------------------------- */
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "pico"
#define McuShell_CONFIG_PROMPT_STRING               "pico> "
#define McuShell_CONFIG_MULTI_CMD_ENABLED           (1)
#define McuShell_CONFIG_MULTI_CMD_SIZE              (96)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE   (128)
/* ---------------------------------------------------------------------- */
/* McuTimeDate */
#define McuTimeDate_CONFIG_TICK_TIME_MS             (100)
/* ---------------------------------------------------------------------- */
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
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_USE_RTT_CONSOLE           (1)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (2) /* RTT and USB CDC */
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_TIME        (1)
/* ---------------------------------------------------------------------------------------*/
/* McuShellCdcDevice with tinyUSB */
#define McuShellCdcDevice_CONFIG_IS_ENABLED     (1)
/* -------------------------------------------------*/
/* I2C */
#define CONFIG_USE_HW_I2C                             (1) /* if using HW I2C, otherwise use software bit banging */
  #define MCUI2CLIB_CONFIG_I2C_DEVICE       i2c0
  #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN     12u
  #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN     13u
#define MCUI2CLIB_CONFIG_ADD_DELAY_US      (0)
#define MCUI2CLIB_CONFIG_TIMEOUT_BYTE_US   (1000)
/* -------------------------------------------------*/
/* McuGenericI2C */
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT       (0)
#define McuGenericI2C_CONFIG_USE_ON_RELEASE_BUS_EVENT (0)
#define McuGenericI2C_CONFIG_USE_ON_REQUEST_BUS_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX                (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#if CONFIG_USE_HW_I2C /* implementation in McuI2cLib.c */
  #define McuLib_CONFIG_MCUI2CLIB_ENABLED                       (1)
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE            "McuI2clib.h"
  #define McuGenericI2C_CONFIG_RECV_BLOCK                       McuI2cLib_RecvBlock
  #define McuGenericI2C_CONFIG_SEND_BLOCK                       McuI2cLib_SendBlock
  #if McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START
  #define McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE              McuI2cLib_SendBlockContinue
  #endif
  #define McuGenericI2C_CONFIG_SEND_STOP                        McuI2cLib_SendStop
  #define McuGenericI2C_CONFIG_SELECT_SLAVE                     McuI2cLib_SelectSlave
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE      (0)
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM                McuI2cLib_RecvBlockCustom

  #define MCUI2CLIB_CONFIG_ADD_DELAY                            (0)
#else
  /* settings for McuGenericSWI2C */
  #define SDA1_CONFIG_PIN_NUMBER  (12)
  #define SCL1_CONFIG_PIN_NUMBER  (13)
  #define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
  #define McuGenericSWI2C_CONFIG_DELAY_NS (0)
#endif
/* -------------------------------------------------*/
/* Time/Date */
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (1) /* enable external I2C RTC */
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS) /* initialize first from software defaults, will update later from HW RTC */
  #define McuTimeDate_CONFIG_EXT_RTC_HEADER_FILE_NAME                "../src/extRTC.h"
  #define McuTimeDate_CONFIG_EXT_RTC_GET_TIME_FCT                    ExtRTC_GetTime
  #define McuTimeDate_CONFIG_EXT_RTC_SET_TIME_FCT                    ExtRTC_SetTimeInfo
  #define McuTimeDate_CONFIG_EXT_RTC_GET_DATE_FCT                    ExtRTC_GetDate
  #define McuTimeDate_CONFIG_EXT_RTC_SET_DATE_FCT                    ExtRTC_SetDateInfo
#else
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS)
#endif
#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC) /* if using external I2C RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */

/* start values */
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_HOUR  0
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_MIN   0
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_SEC   0
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_YEAR  2020
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_MONTH 1
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_DAY   1
/* ---------------------------------------------------------------------------------------*/
/* McuSPI */
/* RP2040: nRF24L01+ on SPI0, GP12 (MISO), GP11 (MOSI), GP18 (CLK) */
#define MCUSPI_CONFIG_HW_TEMPLATE               MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI0
//#define MCUSPI_CONFIG_HW_SCLK_PIN               18
//#define MCUSPI_CONFIG_HW_MOSI_PIN               19
#define MCUSPI_CONFIG_HW_MISO_PIN               20 /* !! */
#define MCUSPI_CONFIG_USE_CS                    (0) /* do not initialize CS pin */
#define MCUSPI_CONFIG_TRANSFER_BAUDRATE         (8*500000U)

/* ---------------------------------------------------------------------------------------*/
/* McuRNF24L01 */
#define McuNRF24L01_CONFIG_IS_ENABLED           (1)
#define McuNRF24L01_CONFIG_CE_PIN_NUMBER        (17)
#define McuNRF24L01_CONFIG_CSN_PIN_NUMBER       (21)
#define McuNRF24L01_CONFIG_IRQ_PIN_NUMBER       (16)
#define McuNRF24L01_CONFIG_USE_MUTEX            (0)
#define McuNRF24L01_CONFIG_IRQ_PIN_ENABLED      (0)
/* ---------------------------------------------------------------------------------------*/
/* McuRNET */
#define McuRNET_CONFIG_IS_ENABLED               (1)
#define RNet_App_CONFIG_DO_SANITY_CHECK         (0)
#define McuRNet_CONFIG_APPLICATION_HEADER_FILE  "RNet_AppConfig.h"
#define RNET_CONFIG_TRANSCEIVER_CHANNEL         (120) /* channel, default 81 */
#define RNET_CONFIG_NRF24_DATA_RATE             McuNRF24L01_RF_SETUP_RF_DR_2000
/* ---------------------------------------------------------------------------------------*/

#endif /* MCULIB_CONFIG_CONFIG_H_ */
