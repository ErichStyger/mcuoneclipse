/*
 * Copyright (c) 2023-2024 Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

#ifndef MCULIB_CONFIG_CONFIG_H_
#define MCULIB_CONFIG_CONFIG_H_

/* different HW/PCB versions: */
#define PL_CONFIG_HW_VERSION_0_1    (1)  /* V0.1, 65x65mm green PCB with Pico, only with USB battery charger, without road */
#define PL_CONFIG_HW_VERSION_0_2    (2)  /* V0.2, 95x95mm green PCB with Pico, added slots for house and solar connector, without road */
#define PL_CONFIG_HW_VERSION_0_3    (3)  /* V0.3, 165x200 mm green 4-Layer PCB by Christian Jost, with road */
#define PL_CONFIG_HW_VERSION_0_4    (4)  /* V0.4, 'House of LEDs' with LED countdown application */
#define PL_CONFIG_HW_VERSION_0_5    (5)  /* V0.5, new PCB (January 2023): added on/off circuit, energy storage, extra sensor */
#define PL_CONFIG_HW_VERSION_0_6    (6)  /* V0.6, EVCC January 2023 */
#define PL_CONFIG_HW_VERSION_0_7    (7)  /* V0.7, new VHS PCB (07-Feb-2023), used for workshops April 2023 */
#define PL_CONFIG_HW_VERSION_0_8    (8)  /* V0.8, new 'large' VHS PCB (15-Mar-2023), with large PMMA/Plexi */

/* active PCB/Hardware version */
#define LIB_CONFIG_HW_VERSION  (PL_CONFIG_HW_VERSION_0_1)

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
#define configMINIMAL_STACK_SIZE                    (200/sizeof(StackType_t)) /* stack size for IDLE task */
#define configUSE_TIMERS                            (1)
#define configTIMER_TASK_STACK_DEPTH                (2048/sizeof(StackType_t)) /* stack size for Timer Service task */
#define configTIMER_QUEUE_LENGTH                    (24)
#define configTOTAL_HEAP_SIZE                       (64*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
/* -------------------------------------------------*/
/* I2C */
#define CONFIG_USE_HW_I2C                             (1) /* if using HW I2C, otherwise use software bit banging */
#define CONFIG_USE_HW_RTC                             (0) /* if using external HW RTC */
#if (LIB_CONFIG_HW_VERSION==PL_CONFIG_HW_VERSION_0_5) || (LIB_CONFIG_HW_VERSION==PL_CONFIG_HW_VERSION_0_7)
  #define MCUI2CLIB_CONFIG_I2C_DEVICE       i2c0
  #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN     12u
  #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN     13u
#else
  #define MCUI2CLIB_CONFIG_I2C_DEVICE       i2c0
  #define MCUI2CLIB_CONFIG_SDA_GPIO_PIN     16u
  #define MCUI2CLIB_CONFIG_SCL_GPIO_PIN     17u
#endif
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
  #define SDA1_CONFIG_PIN_NUMBER  (16)
  #define SCL1_CONFIG_PIN_NUMBER  (17)

  #define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
  #define McuGenericSWI2C_CONFIG_DELAY_NS (0)
#endif
/* -------------------------------------------------*/
/* Time/Date */
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (LIB_CONFIG_HW_VERSION==PL_CONFIG_HW_VERSION_0_7) /* enable external I2C RTC, only for DSxxx RTC */
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS) /* initialize first from software defaults, will update later from HW RTC */
  #define McuTimeDate_CONFIG_EXT_RTC_HEADER_FILE_NAME                "../../src/extRTC.h"
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
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1) /* 0: do not block if buffer full */
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (5)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (1)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (1024)
/* ---------------------------------------------------------------------- */
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "PicoHID"
#define McuShell_CONFIG_PROMPT_STRING               "pico> "
#define McuShell_CONFIG_MULTI_CMD_ENABLED           (1)
#define McuShell_CONFIG_MULTI_CMD_SIZE              (128)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE   (128)
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
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_USE_RTT_CONSOLE           (1)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (2) /* RTT and USB CDC */
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (1)
#define McuLog_CONFIG_LOG_TIMESTAMP_TIME        (1)
/* ---------------------------------------------------------------------------------------*/
/* McuWatchdog */
#define McuWatchdog_CONFIG_USE_WATCHDOG                     (0)
//#define McuWatchdog_CONFIG_REPORT_ID_INCLUDE_HEADER_FILE    "../../RaspberryPiPico/pico_Heidelberg/src/platform.h"
//#define McuWatchdog_CONFIG_REPORT_ID_INCLUDE_FILE           "../../RaspberryPiPico/pico_Heidelberg/src/McuWatchdog_IDs.inc"
//#define McuWatchdog_CONFIG_HEALTH_CHECK_TIME_SEC            (15) /* longer time than usual, as WiFi network stack sometimes takes 10 secs to connect */
/* ---------------------------------------------------------------------------------------*/
/* McuShellCdcDevice with tinyUSB */
#define McuShellCdcDevice_CONFIG_IS_ENABLED     (0)

#endif /* MCULIB_CONFIG_CONFIG_H_ */
