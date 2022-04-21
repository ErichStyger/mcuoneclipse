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
#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0)
#define configTOTAL_HEAP_SIZE                (24*1024)
/* #define configUSE_HEAP_SECTION_NAME          (1) */
/* #define configHEAP_SECTION_NAME_STRING       ".bss.$SRAM_LOWER.FreeRTOS" */
/* ---------------------------------------------------------------------------------------*/
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



/* -----------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING              "LPC55S16"
#define McuShell_CONFIG_ECHO_ENABLED                     (1)
#define McuShellUart_CONFIG_UART                         McuShellUart_CONFIG_UART_LPC55S16_USART0
#if McuLib_CONFIG_SDK_USE_FREERTOS
#define McuShellUart_CONFIG_UART 					          McuShellUart_CONFIG_UART_LPC55S16_USART0
#endif
#define McuShell_CONFIG_MULTI_CMD_ENABLED           (1)
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE   (96)
#define McuShell_CONFIG_MULTI_CMD_SIZE              (96) /* maximum size of a single command in a multi-command string */
#define McuShell_CONFIG_PROMPT_STRING               "LoRa> "
#define McuShell_CONFIG_ECHO_ENABLED                (1)
/* ---------------------------------------------------------------------------------------*/
/* MinINI */
/* see as well platform.h about the memory layout and EEPROM reservation */
#define McuMinINI_CONFIG_FS                         McuMinINI_CONFIG_FS_TYPE_FLASH_FS
#define McuMinINI_CONFIG_FLASH_NVM_ADDR_START      (((0+240*1024)-(McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS*McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE))) /* last block in FLASH, start address of configuration data in flash */
#define McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE      (0x200)   /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#define McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS      (4)       /* number of flash blocks */
#define McuMinINI_CONFIG_FLASH_NVM_MAX_DATA_SIZE   (McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS * McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE) /* MUST be multiple of 512 for LPC55! */
/* ---------------------------------------------------------------------------------------*/

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

/* -------------------------------------------------*/
/* Time/Date */
#define McuTimeDate_CONFIG_USE_SOFTWARE_RTC                        (0) /* enable software RTC */
#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (1) /* enable external I2C RTC */
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

#define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC)
#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_EXTERNAL_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (0) /* if using software RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (1) /* if using external I2C RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */
/* -------------------------------------------------*/

/* -------------------------------------------------*/
/* RTC */
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


/**
 * SPI definitions
 */
//#define LPC_NUMBER_OF_SPI                       1
//
//#if(LPC_NUMBER_OF_SPI > 0)
//  /* LoRa Transceiver is on FlexComm 8 */
//  #define LPC_SPI3_TYPE                           SPI3 /* LoRa Transceiver */
//  #define LPC_SPI3_CLK_FRQ                        CLOCK_GetFlexCommClkFreq(3U)
//  #define LPC_SPI3_SPI_MASTER_IRQ      			  FLEXCOMM3_IRQn
//  #define LPC_SPI3_CONFIG_POLARITY                kSPI_ClockPolarityActiveHigh
//  #define LPC_SPI3_CONFIG_PHASE                   kSPI_ClockPhaseFirstEdge
//  #define LPC_SPI3_CONFIG_DIRECTION               kSPI_MsbFirst
//  #define LPC_SPI3_CONFIG_BAUDRATE                500000U
//  #define LPC_SPI3_CONFIG_DATAWIDTH               kSPI_Data8Bits
//  #define LPC_SPI3_CONFIG_SS                      kSPI_Ssel0
//  #define LPC_SPI3_CONFIG_SPOL                    kSPI_SpolActiveAllLow
//#endif
//#if(LPC_NUMBER_OF_SPI > 1)
//  #define LPC_SPI2_TYPE                           SPI7 /* Free */
//  #define LPC_SPI2_CLK_FRQ                        CLOCK_GetFlexCommClkFreq(7U)
//  #define LPC_SPI2_CONFIG_POLARITY                kSPI_ClockPolarityActiveHigh
//  #define LPC_SPI2_CONFIG_PHASE                   kSPI_ClockPhaseFirstEdge
//  #define LPC_SPI2_CONFIG_DIRECTION               kSPI_MsbFirst
//  #define LPC_SPI2_CONFIG_BAUDRATE                500000U
//  #define LPC_SPI2_CONFIG_DATAWIDTH               kSPI_Data8Bits
//  #define LPC_SPI2_CONFIG_SS                      kSPI_Ssel0
//  #define LPC_SPI2_CONFIG_SPOL                    kSPI_SpolActiveAllLow
//#endif




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
#define McuSWO_CONFIG_HAS_SWO         (0) /* enable SWO support */
//#define McuSWO_CONFIG_SPEED_BAUD      (5625000) /* J-Link supports up to 5625 kHz */
#define McuSWO_CONFIG_SPEED_BAUD      (96000000) /* needed for LinkServer and MCUXpresso IDE 11.5.0 */


/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED  (1)
/* ---------------------------------------------------------------------------------------*/

#endif /* INCLUDEMCULIBCONFIG_H_ */
