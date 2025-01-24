/*
 * Copyright (c) 2016-2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option
Instructions:
 - Remove the 'Template_' from the name and place this file into your 'src' folder.
 - Include it with the -include compiler option with:  "${ProjDirPath}/source/IncludeMcuLibConfig.h"
 - Add the following to the -I compiler option:
../McuLib
../McuLib/config
../McuLib/config/fonts
../McuLib/fonts
../McuLib/src
../McuLib/FreeRTOS/Source/include
../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F
../McuLib/SEGGER_RTT
../McuLib/SEGGER_Sysview
../McuLib/TraceRecorder
../McuLib/TraceRecorder/config
../McuLib/TraceRecorder/include
../McuLib/TraceRecorder/streamports/Jlink_RTT/include
../McuLib/HD44780
../McuLib/FatFS
../McuLib/FatFS/source
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* global platform configuration */
#define PL_CONFIG_USE_LORA_SHIELD         (0) /* if using the LoRa Shield developed by Corsin Obrist */

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* set the CPU. See McuLibConfig.h for all supported CPUs */
#if 0 /* example configuration for LPC845 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CORTEX_M          (0)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       (McuLib_CONFIG_CPU_VARIANT_NXP_LPC845) /* for LPC need to specify the actual device */
#elif 1 /* example configuration for LPC55S16 */
  #define McuLib_CONFIG_CPU_IS_LPC        (1)  /* LPC family */
  #define McuLib_CONFIG_CPU_IS_LPC55xx    (1)  /* LPC55xx */
  #define McuLib_CONFIG_CORTEX_M          (33)    /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
  #define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S16
/* note: M33 port not functional yet! */
  #define configRUN_FREERTOS_SECURE_ONLY (0)
  #define configENABLE_TRUSTZONE         (0)
  #define configENABLE_MPU               (0)
  #define configENABLE_FPU               (1)
  #define configMINIMAL_SECURE_STACK_SIZE  (600)

#elif 0 /* example configuration for Kinetis K22 */
  #define McuLib_CONFIG_CPU_IS_KINETIS    (1)  /* NXP Kinetis family */
  #define McuLib_CONFIG_CORTEX_M          (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#elif 0 /* example configuration for i.MX RT */
  #define McuLib_CONFIG_CPU_IS_IMXRT      (1)  /* i.MX RT family */
  #define McuLib_CONFIG_CORTEX_M          (7)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#endif
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS          (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS    (0)
#define configTOTAL_HEAP_SIZE                   (24*1024)
/* #define configUSE_HEAP_SECTION_NAME          (1) */
/* #define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS" */
/* ------------------- McuSPI --------------------------*/
#define MCUSPI_CONFIG_HW_TEMPLATE               MCUSPI_CONFIG_HW_TEMPLATE_LPC55S16_FC3
#define MCUSPI_CONFIG_TRANSFER_BAUDRATE         (4*500000U)
/* ---------------------------------------------------------------------------------------*/
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED                    (0) /* enable McuFlash module */
#define McuFlash_CONFIG_NOF_BLOCKS                    (32) /* number of flash blocks */
#define McuFlash_CONFIG_MEM_START                     (((0+244*1024)-((McuFlash_CONFIG_NOF_BLOCKS)*(McuFlash_CONFIG_FLASH_BLOCK_SIZE))))
/* ------------------- McuLittleFS --------------------------*/
#define LITTLEFS_CONFIG_ENABLED                       (1) /* enable the LittleFS file system */
#if 0 /* using Winbond external flash */
  #define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE     McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
#else /* using internal flash with McuFlash */
  #define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE     McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_MCU_FLASH
  #define McuLittleFS_CONFIG_BLOCK_SIZE                 (McuFlash_CONFIG_FLASH_BLOCK_SIZE)
  #define McuLittleFS_CONFIG_BLOCK_COUNT                (McuFlash_CONFIG_NOF_BLOCKS)
  #define McuLittleFS_CONFIG_BLOCK_OFFSET               ((McuFlash_CONFIG_MEM_START)/(McuFlash_CONFIG_FLASH_BLOCK_SIZE))
#endif
/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS                      (0)
#define McuFatFS_CONFIG_HAS_CARD_DETECT_PIN           (0)
#define McuFatFS_CONFIG_CARD_DETECT_GPIO              GPIO
#define McuFatFS_CONFIG_CARD_DETECT_PORT              0
#define McuFatFS_CONFIG_CARD_DETECT_PIN               16U
#define McuFatFS_CONFIG_CARD_DETECT_PULL              McuGPIO_PULL_DISABLE /* https://www.pololu.com/product/2587 */
#define McuFatFS_CONFIG_CARD_DETECT_IS_HIGH_ACTIVE    (1)  /*  https://www.pololu.com/product/2587 */
#define McuFatFS_CONFIG_HAS_WRITE_PROTECT_PIN         (0)
//#define McuFatFS_CONFIG_WRITE_PROTECT_GPIO            GPIO
//#define McuFatFS_CONFIG_WRITE_PROTECT_PORT            0
//#define McuFatFS_CONFIG_WRITE_PROTECT_PIN             17U
//#define McuFatFS_CONFIG_WRITE_PROTECT_PULL            McuGPIO_PULL_DISABLE /* https://www.pololu.com/product/2587 */
/* -------------------------------------------------*/
/* MinINI */
#if 0
  #define McuMinINI_CONFIG_FS                           McuMinINI_CONFIG_FS_TYPE_FAT_FS
#else
  #define McuMinINI_CONFIG_FS                           McuMinINI_CONFIG_FS_TYPE_LITTLE_FS
#endif
/* -----------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING              "LPC55S16"
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
/* McuTimeDate */
#define McuTimeDate_CONFIG_TICK_TIME_MS                            (100)
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (1) /* enable software RTC */
#if PL_CONFIG_USE_LORA_SHIELD
  #define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (1) /* enable external I2C RTC */
#else
  #define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (0) /* not using external I2C RTC */
#endif
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

#if PL_CONFIG_USE_LORA_SHIELD
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC)
#else
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS)
#endif

#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
#if PL_CONFIG_USE_LORA_SHIELD
  #define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (1) /* if using external I2C RTC */
#else
  #define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (0) /* if using external I2C RTC */
#endif
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */
/* -------------------------------------------------*/
/* McuExtRTC */
#define McuExtRTC_CONFIG_DEVICE                 3232  /* RTC device used */
/* -----------------------------------------------------*/
/* I2C and OLED */
#define USE_HW_I2C                              (1)  /* otherwise uses GPIO bit-banging */

#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)

/* I2C Pin Muxing */
#if USE_HW_I2C
  #define McuLib_CONFIG_MCUI2CLIB_ENABLED                        (1)
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE             "McuI2cLib.h"
  #define McuGenericI2C_CONFIG_RECV_BLOCK                        McuI2cLib_RecvBlock
  #define McuGenericI2C_CONFIG_SEND_BLOCK                        McuI2cLib_SendBlock
  #if McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START
  #define McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE               McuI2cLib_SendBlockContinue
  #endif
  #define McuGenericI2C_CONFIG_SEND_STOP                         McuI2cLib_SendStop
  #define McuGenericI2C_CONFIG_SELECT_SLAVE                      McuI2cLib_SelectSlave
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE       (0)
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM                 McuI2cLib_RecvBlockCustom
#else
  #define SDA1_CONFIG_DO_PIN_MUXING (1)
  #define SCL1_CONFIG_DO_PIN_MUXING (1)
  
  #define SCL1_CONFIG_GPIO_NAME     GPIO
  #define SCL1_CONFIG_PORT_NAME     0
  #define SCL1_CONFIG_PIN_NUMBER    14u

  #define SDA1_CONFIG_GPIO_NAME     GPIO
  #define SDA1_CONFIG_PORT_NAME     0
  #define SDA1_CONFIG_PIN_NUMBER    13u
#endif
#define MCUI2CLIB_CONFIG_ADD_DELAY  (0)
/* -------------------------------------------------*/
#if 1 /* type of OLED */
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1106)
#else
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1306)
#endif

#define McuSSD1306_CONFIG_INIT_DELAY_MS (500)  /* extra delay to give hardware time for power-up */
//#define McuSSD1306_CONFIG_SSD1306_START_COLUMN_OFFSET (0) /* needed for 1.3" Banggood display */
#define McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US         (0)
#define McuSSD1306_CONFIG_DYNAMIC_DISPLAY_ORIENTATION  (0)
/* -----------------------------------------------------*/
/* McuWait */
#define McuWait_CONFIG_USE_CYCLE_COUNTER         (1)
/* -----------------------------------------------------*/
/* McuSWO */
#define McuSWO_CONFIG_HAS_SWO         (1) /* enable SWO support */
//#define McuSWO_CONFIG_SPEED_BAUD      (115200) /* J-Link supports up to 5625 kHz */
//#define McuSWO_CONFIG_SPEED_BAUD      (5625000) /* J-Link supports up to 5625 kHz */
#define McuSWO_CONFIG_SPEED_BAUD      (9300000) /* J-Link could support up to 9.6 MHz */
//#define McuSWO_CONFIG_SPEED_BAUD      (96000000) /* needed for LinkServer and MCUXpresso IDE 11.5.0 */
#define McuSWO_CONFIG_DO_MUXING       (1) /* use own muxing */
#define McuSWO_CONFIG_DO_CLOCKING     (1) /* do clock settings */
#define McuSWO_CONFIG_DO_SWO_INIT     (1) /* SWO configuration is done by module */
/* -----------------------------------------------------*/
/* McuW25Q128 */
#define MCUW25Q128_CONFIG_ENABLED     (1)
/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_IS_ENABLED               (1)
//#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_SEGGER
#define McuSemihost_CONFIG_DEBUG_CONNECTION         McuSemihost_DEBUG_CONNECTION_LINKSERVER
/* ---------------------------------------------------------------------------------------*/
/* McuRdimon */
#define McuRdimon_CONFIG_IS_ENABLED                 (0)       /* 1: RdiMon is enabled; 0: RdiMon is disabled*/
/* ---------------------------------------------------------------------------------------*/


#endif /* INCLUDEMCULIBCONFIG_H_ */
