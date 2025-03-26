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
#define configMINIMAL_STACK_SIZE                    (128/sizeof(StackType_t)) /* stack size for IDLE task */
#define configTIMER_TASK_STACK_DEPTH                (600/sizeof(StackType_t)) /* stack size for Timer Service task */
#define configTOTAL_HEAP_SIZE                       (64*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)

/* SMP port only */
#define configTICK_CORE                         0 /* indicate which core should handle the SysTick */

/* RP2040 specific */
#define configSUPPORT_PICO_SYNC_INTEROP         1
#define configSUPPORT_PICO_TIME_INTEROP         1

/* Set configNUMBER_OF_CORES to the number of available processor cores. Defaults to 1 if left undefined. */
#define configNUMBER_OF_CORES                       (1)

#if configNUMBER_OF_CORES>1
  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), set
  * configRUN_MULTIPLE_PRIORITIES to 0 to allow multiple tasks to run
  * simultaneously only if they do not have equal priority, thereby maintaining
  * the paradigm of a lower priority task never running if a higher priority task
  * is able to run. If configRUN_MULTIPLE_PRIORITIES is set to 1, multiple tasks
  * with different priorities may run simultaneously - so a higher and lower
  * priority task may run on different cores at the same time. */
  #define configRUN_MULTIPLE_PRIORITIES             0

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), set
  * configUSE_CORE_AFFINITY to 1 to enable core affinity feature. When core
  * affinity feature is enabled, the vTaskCoreAffinitySet and vTaskCoreAffinityGet
  * APIs can be used to set and retrieve which cores a task can run on. If
  * configUSE_CORE_AFFINITY is set to 0 then the FreeRTOS scheduler is free to
  * run any task on any available core. */
  #define configUSE_CORE_AFFINITY                   1

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), if
  * configUSE_TASK_PREEMPTION_DISABLE is set to 1, individual tasks can be set to
  * either pre-emptive or co-operative mode using the vTaskPreemptionDisable and
  * vTaskPreemptionEnable APIs. */
  #define configUSE_TASK_PREEMPTION_DISABLE         0

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one), set
  * configUSE_PASSIVE_IDLE_HOOK to 1 to allow the application writer to use
  * the passive idle task hook to add background functionality without the overhead
  * of a separate task. Defaults to 0 if left undefined. */
  #define configUSE_PASSIVE_IDLE_HOOK               0

  /* When using SMP (i.e. configNUMBER_OF_CORES is greater than one),
  * configTIMER_SERVICE_TASK_CORE_AFFINITY allows the application writer to set
  * the core affinity of the RTOS Daemon/Timer Service task. Defaults to
  * tskNO_AFFINITY if left undefined. */
  #define configTIMER_SERVICE_TASK_CORE_AFFINITY    tskNO_AFFINITY
#endif

/* -------------------------------------------------*/
/* I2C */
#define CONFIG_USE_HW_I2C                           (1) /* if using HW I2C, otherwise use software bit banging */
#define CONFIG_USE_HW_RTC                           (0) /* if using external HW RTC */
#define MCUI2CLIB_CONFIG_I2C_DEVICE                 i2c0
#define MCUI2CLIB_CONFIG_SDA_GPIO_PIN               16u
#define MCUI2CLIB_CONFIG_SCL_GPIO_PIN               17u
#define MCUI2CLIB_CONFIG_ADD_DELAY_US               (0)
#define MCUI2CLIB_CONFIG_TIMEOUT_BYTE_US            (1000)
/* -------------------------------------------------*/
/* McuGenericI2C */
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT       (0)
#define McuGenericI2C_CONFIG_USE_ON_RELEASE_BUS_EVENT (0)
#define McuGenericI2C_CONFIG_USE_ON_REQUEST_BUS_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX                (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#if CONFIG_USE_HW_I2C /* implementation in McuI2cLib.c */
  #define McuLib_CONFIG_MCUI2CLIB_ENABLED                       (1)
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE            "McuI2cLib.h"
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
/* ---------------------------------------------------------------------------------------*/
/* McuSSD1306 */
#define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE         (1106)
#define McuSSD1306_CONFIG_DYNAMIC_DISPLAY_ORIENTATION  (0)
#define McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION    McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1) /* 0: do not block if buffer full */
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (1)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (2*1024)
/* ---------------------------------------------------------------------- */
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "RP2040 Feather"
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
#define McuLog_CONFIG_USE_COLOR                 (1)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_TIME        (0)
/* ---------------------------------------------------------------------------------------*/
/* McuSPI */
/* Feather: nRF24L01+ on SPI1, GPIO20 (MISO, Pin13), GPIO19 (MOSI, Pin12), GPIO18 (SCK, Pin11) */
#define MCUSPI_CONFIG_HW_TEMPLATE               MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI0
#define MCUSPI_CONFIG_HW_MISO_PIN               (20)
#define MCUSPI_CONFIG_HW_MOSI_PIN               (19)
#define MCUSPI_CONFIG_HW_SCLK_PIN               (18)
#define MCUSPI_CONFIG_USE_CS                    (0) /* do not initialize CS pin */
#define MCUSPI_CONFIG_TRANSFER_BAUDRATE         500000U
/* ---------------------------------------------------------------------------------------*/
/* McuRNF24L01 */
#define McuNRF24L01_CONFIG_IS_ENABLED           (1)
#define McuNRF24L01_CONFIG_USE_MUTEX            (0)
#define McuNRF24L01_CONFIG_CE_PIN_NUMBER        (29) /* GPIO29 -> A3/pin8 on feather */
#define McuNRF24L01_CONFIG_CSN_PIN_NUMBER       (24) /* GPIO14 -> D24/pin9 on feather */
#define McuNRF24L01_CONFIG_IRQ_PIN_NUMBER       (7)  /* GPIO7 -> D5 - > A5/pin10 on feather */
#define McuNRF24L01_CONFIG_IRQ_PIN_ENABLED      (1)
/* ---------------------------------------------------------------------------------------*/
/* McuRNET */
#define McuRNET_CONFIG_IS_ENABLED               (1)
#define RNet_App_CONFIG_DO_SANITY_CHECK         (0)
#define McuRNet_CONFIG_APPLICATION_HEADER_FILE  "RNet_AppConfig.h"
#define RNET_CONFIG_TRANSCEIVER_CHANNEL         (120) /* channel, default 81 */
#define RNET_CONFIG_NRF24_DATA_RATE             McuNRF24L01_RF_SETUP_RF_DR_2000
#define RSTDIO_CONFIG_QUEUE_LENGTH              (5*48) /* default is 48 */
#define RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS      (32) /* default is 15 */
#define RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS      (32) /* default is 15 */
/* ---------------------------------------------------------------------------------------*/
/* McuShellCdcDevice with tinyUSB */
#define McuShellCdcDevice_CONFIG_IS_ENABLED     (1)
/* ---------------------------------------------------------------------------------------*/

#endif /* MCULIB_CONFIG_CONFIG_H_ */
