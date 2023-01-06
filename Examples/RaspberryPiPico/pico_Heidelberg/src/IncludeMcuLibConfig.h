/*
 * Copyright (c) 2022, Erich Styger
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
/* ---------------------------------------------------------------------- */
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configMINIMAL_STACK_SIZE                    (500)
#define configTOTAL_HEAP_SIZE                       (52*1024)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (0)
/* -------------------------------------------------*/
/* I2C */
#define CONFIG_USE_HW_I2C                             (1) /* if using HW I2C, otherwise use software bit banging */
#define CONFIG_USE_HW_RTC                             (0) /* if using external HW RTC */
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
#define McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC                     (CONFIG_USE_HW_RTC) /* enable external I2C RTC */
#define McuTimeDate_CONFIG_USE_INTERNAL_HW_RTC                     (0) /* no internal RTC */

#if McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_EXTERNAL_RTC)
#else
  #define McuTimeDate_CONFIG_INIT_SOFTWARE_RTC_METHOD                (McuTimeDate_INIT_SOFTWARE_RTC_FROM_DEFAULTS)
#endif
#define McuTimeDate_CONFIG_USE_GET_TIME_DATE_METHOD                (McuTimeDate_GET_TIME_DATE_METHOD_SOFTWARE_RTC)
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_SOFTWARE_RTC  (1) /* if using software RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_EXTERNAL_RTC  (McuTimeDate_CONFIG_USE_EXTERNAL_HW_RTC) /* if using external I2C RTC */
#define McuTimeDate_CONFIG_SET_TIME_DATE_METHOD_USES_INTERNAL_RTC  (0) /* if using internal HW RTC */
/* ---------------------------------------------------------------------------------------*/
/* McuSSD1306 */
#define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE         (1106)
#define McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION    McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE180 /* PL_CONFIG_HW_VERSION_0_1 */
//#define McuSSD1306_CONFIG_FIXED_DISPLAY_ORIENTATION    McuSSD1306_CONFIG_ORIENTATION_LANDSCAPE /* version with road */
/* -------------------------------------------------*/
/* RTT */
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_DOWN            (128)
#define McuRTT_CONFIG_BLOCKING_SEND                   (1)
#define McuRTT_CONFIG_BLOCKING_SEND_TIMEOUT_MS        (10)
#define McuRTT_CONFIG_BLOCKING_SEND_WAIT_MS           (5)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP              (256)
/* ---------------------------------------------------------------------- */
/* McuShell */
#define McuShell_CONFIG_PROJECT_NAME_STRING  "picoCharger"
#define McuShell_CONFIG_PROMPT_STRING        "pico> "
/* ---------------------------------------------------------------------- */
/* McuFlash */
#define McuFlash_CONFIG_IS_ENABLED          (1) /* enable for MinINI with Flash FS */
#if 0
#define CONFIG_FLASH_TARGET_OFFSET     (256*4*1024) /* offset from XIP where we want to use the memory */
#define CONFIG_FLASH_ADDRESS_START     (XIP_BASE + CONFIG_FLASH_TARGET_OFFSET)
#define CONFIG_FLASH_NUMBER_OF_PAGES   (4) /* number of block (4K each) */
#define CONFIG_FLASH_SIZE              (CONFIG_FLASH_NUMBER_OF_PAGES*McuFlash_CONFIG_FLASH_BLOCK_SIZE)
#endif
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
#define McuLog_CONFIG_NOF_CONSOLE_LOGGER        (1)
#define McuLog_CONFIG_USE_COLOR                 (0)
#define McuLog_CONFIG_LOG_TIMESTAMP_DATE        (0)
/* -------------------------------------------------*/
/* McuSPI */
#define MCUSPI_CONFIG_HW_TEMPLATE               (MCUSPI_CONFIG_HW_TEMPLATE_RP2040_SPI1) /* using SPI1 with template */
#define MCUSPI_CONFIG_TRANSFER_BAUDRATE         (24*1000*1000)
/* -------------------------------------------------*/
/* McuW25Q128 */
#define MCUW25Q128_CONFIG_ENABLED               (1)
#define MCUW25Q128_CONFIG_SIZE_KBYTES           (16*1024*1024)
/* -------------------------------------------------*/
/* McuLittleFS */
//#define LITTLEFS_CONFIG_ENABLED                       (1)
//#define McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE     McuLittleFSBlockDevice_CONFIG_MEMORY_TYPE_WINBOND_W25Q128
//#define McuLittleFS_CONFIG_BLOCK_SIZE                 (4096) /* W25Q128 has blocks of 4 KByte */
//#define McuLittleFS_CONFIG_BLOCK_COUNT                ((MCUW25Q128_CONFIG_SIZE_KBYTES*1024)/McuLittleFS_CONFIG_BLOCK_SIZE) /* W25Q128 has 16 MByte */
//#define McuLittleFS_CONFIG_BLOCK_OFFSET               (0)
/* ---------------------------------------------------------------------------------------*/
/* LittlevGL */
#define LV_CONFIG_DPI                  (25)
#define LV_CONF_INCLUDE_SIMPLE   /* use lv_conf.h inside src folder */
//#define LV_CONF_SUPPRESS_DEFINE_CHECK  /* avoid bogus warning with gcc about including lv_conf.h */

#if !__ASSEMBLER__ /* set if file is included by GNU as. Do not include normal C header files if running the assembler for example to assemble the pico startup code */
  #include "lv_conf.h"
#endif /* !__ASSEMBLER__ */
/* ---------------------------------------------------------------------------------------*/
/* McuModBus */
#define McuModbus_CONFIG_IS_ENABLED           (1) /* Modbus with Heidelberg wallbox */
/* ---------------------------------------------------------------------------------------*/
/* McuUart485 */
#define McuUart485_CONFIG_USE_RS_485          (1)
#define McuUart485_CONFIG_USE_MODBUS          (McuModbus_CONFIG_IS_ENABLED)
#define McuUart485_CONFIG_USE_LOGGER          (1)
#if McuModbus_CONFIG_IS_ENABLED
  #define McuUart485_CONFIG_UART_BAUDRATE      (19200)
  #define McuUart485_CONFIG_UART_PARITY        UART_PARITY_EVEN
#else
  #define McuUart485_CONFIG_UART_BAUDRATE      (115200)
#endif

