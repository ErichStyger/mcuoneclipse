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
#define McuLib_CONFIG_SDK_VERSION_USED      McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_KINETIS        (1)  /* NXP Kinetis family */
#define McuLib_CONFIG_CPU_IS_LPC            (0)  /* LPC family */
#define McuLib_CONFIG_CORTEX_M              (4)  /*!< 0: Cortex-M0, 3: M3, 4: M4, 7: M7, 33: M33, -1 otherwise */
#define McuLib_CONFIG_CPU_VARIANT           McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)
#define configTOTAL_HEAP_SIZE                (10*1024)
#define configUSE_HEAP_SECTION_NAME          (1)
#define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS"

#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS    (1)
#define MCU_SYSTEM_VIEW_USER_ID_BUTTON_INTERRUPT (0) /* ID for button press measurement */
#define MCU_SYSTEM_VIEW_USER_ID_DRAW_SCREEN      (1) /* ID for screen drawing measurement */
#define MCU_SYSTEM_VIEW_USER_ID_SEND_SCREEN      (2) /* ID for sending data over I2c measurement */

/* ------------------- FatFS ---------------------------*/
#define McuLib_CONFIG_USE_FAT_FS              (0)
/* --------------------------------------- */
/* McuLog */
#define McuLog_CONFIG_IS_ENABLED              (1)
/* ---------------------------------------------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING             "Game with tinyK22"
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE       (128)  /* buffer size for parsing, must be able to include multiple commands */
#define McuShell_CONFIG_MULTI_CMD_SIZE                  (96)   /* maximum size of a single command in a multi-command string */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP                (4096)
#define McuShellUart_CONFIG_UART                        McuShellUart_CONFIG_UART_K22FN512_LPUART0_C3_C4
#define McuShellUart_CONFIG_UART_GET_CLOCK_FREQ_SELECT  kCLOCK_PllFllSelClk /* kCLOCK_Osc0ErClkUndiv */
/* ---------------------------------------------------------------------------------------*/
/* McuTimeDate */
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_HOUR 13
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_MIN 00
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_TIME_SEC 00
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_YEAR 2021
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_MONTH 10
#define McuTimeDate_CONFIG_DEFAULT_INITIAL_DATE_DAY 21
/* ------------------- I2C ---------------------------*/
#define CONFIG_USE_HW_I2C                             (1) /* if using HW I2C (HAT >=v4), otherwise use software bit banging */
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT       (0)
#define McuGenericI2C_CONFIG_USE_ON_REQUEST_BUS_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX                (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
#define I2C_RETRY_TIMES   (5000) /* set retry count for SDK */

#if CONFIG_USE_HW_I2C /* implementation in McuI2cLib.c */
  #define McuLib_CONFIG_MCUI2CLIB_ENABLED                       (1)
  #define MCUI2CLIB_CONFIG_USE_PORTB_B0_B1                      (1) /* using I2C on B0/B1 */
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
#else
  /* settings for GenericSWI2C */
  #define SCL1_CONFIG_GPIO_NAME     GPIOE // I2CLIB_SCL_GPIO
  #define SCL1_CONFIG_PORT_NAME     PORTE //I2CLIB_SCL_GPIO_PORT
  #define SCL1_CONFIG_PIN_NUMBER    1 //I2CLIB_SCL_GPIO_PIN

  #define SDA1_CONFIG_GPIO_NAME     GPIOE //I2CLIB_SDA_GPIO
  #define SDA1_CONFIG_PORT_NAME     PORTE //I2CLIB_SDA_GPIO_PORT
  #define SDA1_CONFIG_PIN_NUMBER    0 //I2CLIB_SDA_GPIO_PIN

  /* I2C Pin Muxing */
  #define SDA1_CONFIG_DO_PIN_MUXING (1)
  #define SCL1_CONFIG_DO_PIN_MUXING (1)

  #define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
  #define McuGenericSWI2C_CONFIG_DELAY_NS (0)
#endif
/* ---------------------------------------------------------------------------------------*/
/* McuSSD1306 */
#define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE   (1106)
#define McuSSD1306_CONFIG_DYNAMIC_DISPLAY_ORIENTATION (0)
//#define McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION      McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE180
#define McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION      McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE
#define McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US          (0)    /* no extra delay */
/* ---------------------------------------------------------------------------------------*/
/* MinINI */
#define McuMinINI_CONFIG_FS                         (McuMinINI_CONFIG_FS_TYPE_FLASH_FS)
#define McuMinINI_CONFIG_FLASH_NVM_ADDR_START       ((0+512*1024)-McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE)
#define McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE       (0x800)
#define McuMinINI_CONFIG_FLASH_NVM_MAX_DATA_SIZE    (256) /* must be 64, 128, 256, ... */
#define McuMinINI_CONFIG_READ_ONLY                  (0)
#define McuMinINI_CONFIG_USE_REAL                   (0)

/* ---------------------------------------------------------------------------------------*/
/* McuSemihost */
#define McuSemihost_CONFIG_DEBUG_PROBE    McuSemihost_DEBUG_PROBE_SEGGER

#endif /* INCLUDEMCULIBCONFIG_H_ */
