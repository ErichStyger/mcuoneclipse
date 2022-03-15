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
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0)
#define configTOTAL_HEAP_SIZE                (24*1024)
/* #define configUSE_HEAP_SECTION_NAME          (1) */
/* #define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS" */
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
#define McuMinINI_CONFIG_FS                           McuMinINI_CONFIG_FS_TYPE_FAT_FS
/* -----------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING              "LPC55S16"
#define McuShell_CONFIG_ECHO_ENABLED                     (1)
#define McuShellUart_CONFIG_UART                         McuShellUart_CONFIG_UART_LPC55S16_USART0
/* -----------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP    (1*1024)
#define McuRTT_CONFIG_BLOCKING_SEND           (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS  (20)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS   (5)
/* -------------------------------------------------*/
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED                (1)
#define McuLog_CONFIG_USE_FILE                  (0)
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (2)
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
/* -----------------------------------------------------*/
/* McuTimeDate */
#define McuTimeDate_CONFIG_TICK_TIME_MS   (100)

/* -----------------------------------------------------*/
/* I2C and OLED */
#define USE_HW_I2C                              (1)  /* otherwise uses GPIO bit-banging */

#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)

/* I2C Pin Muxing */

#if USE_HW_I2C
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE    "i2clib.h"
  #define McuGenericI2C_CONFIG_RECV_BLOCK                        I2CLIB_RecvBlock
  #define McuGenericI2C_CONFIG_SEND_BLOCK                        I2CLIB_SendBlock
  #if McuGenericI2C_CONFIG_SUPPORT_STOP_NO_START
  #define McuGenericI2C_CONFIG_SEND_BLOCK_CONTINUE               I2CLIB_SendBlockContinue
  #endif
  #define McuGenericI2C_CONFIG_SEND_STOP                         I2CLIB_SendStop
  #define McuGenericI2C_CONFIG_SELECT_SLAVE                      I2CLIB_SelectSlave
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM_AVAILABLE       (0)
  #define McuGenericI2C_CONFIG_RECV_BLOCK_CUSTOM                 I2CLIB_RecvBlockCustom
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

#if 1 /* type of OLED */
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1106)
#else
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1306)
#endif

#define McuSSD1306_CONFIG_INIT_DELAY_MS (500)  /* extra delay to give hardware time for power-up */
//#define McuSSD1306_CONFIG_SSD1306_START_COLUMN_OFFSET (0) /* needed for 1.3" Banggood display */
#define McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US   (0)

/* -----------------------------------------------------*/
/* McuWait */
#define McuWait_CONFIG_USE_CYCLE_COUNTER (1)

/* -----------------------------------------------------*/
/* McuSWO */
#define McuSWO_CONFIG_HAS_SWO         (1) /* enable SWO support */
//#define McuSWO_CONFIG_SPEED_BAUD      (5625000) /* J-Link supports up to 5625 kHz */
#define McuSWO_CONFIG_SPEED_BAUD      (96000000) /* needed for LinkServer and MCUXpresso IDE 11.5.0 */

#endif /* INCLUDEMCULIBCONFIG_H_ */
