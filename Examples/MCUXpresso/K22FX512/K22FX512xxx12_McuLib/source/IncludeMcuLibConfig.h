/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* header file is included with -include compiler option */

/* ---------------------------------------------------------------------------------------*/
/* SDK */
#define McuLib_CONFIG_CPU_IS_KINETIS                (1)
#define McuLib_CONFIG_SDK_VERSION_USED              McuLib_CONFIG_SDK_MCUXPRESSO_2_0
/* ---------------------------------------------------------------------------------------*/
/* FreeRTOS */
#define McuLib_CONFIG_SDK_USE_FREERTOS              (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS        (1)
#define configTOTAL_HEAP_SIZE                       (54*1024)
#define configUSE_HEAP_SECTION_NAME                 (1)
#define configHEAP_SECTION_NAME_STRING              ".bss.$SRAM_LOWER.FreeRTOS"
#define configQUEUE_REGISTRY_SIZE                   (15)
/* ---------------------------------------------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING         "MK22FX512 SumoV2"
#define McuShell_CONFIG_DEFAULT_SHELL_BUFFER_SIZE   (96)
#define McuRTT_CONFIG_RTT_BUFFER_SIZE_UP            (4096)
/* ---------------------------------------------------------------------------------------*/
/* I2C and OLED */
#define CONFIG_USE_HW_I2C                       (0)

#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD         (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS         (0)
/* I2C Pin Muxing: only for SW I2C */
#define SDA1_CONFIG_DO_PIN_MUXING               (1)
#define SCL1_CONFIG_DO_PIN_MUXING               (1)

#if CONFIG_USE_HW_I2C
  #define McuGenericI2C_CONFIG_INTERFACE_HEADER_FILE "i2clib.h"
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
  #define SCL1_CONFIG_GPIO_NAME     GPIOB
  #define SCL1_CONFIG_PORT_NAME     PORTB
  #define SCL1_CONFIG_PIN_NUMBER    2u

  #define SDA1_CONFIG_GPIO_NAME     GPIOB
  #define SDA1_CONFIG_PORT_NAME     PORTB
  #define SDA1_CONFIG_PIN_NUMBER    3u
#endif
/* ---------------------------------------------------------------------------------------*/
/* OLED and GUI */
#if 1 /* type of OLED */
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1106)
#else
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1306)
#endif
//#define McuSSD1306_CONFIG_SSD1306_START_COLUMN_OFFSET (0) /* needed for 1.3" Banggood display */
#define McuSSD1306_CONFIG_SSD1306_I2C_DELAY_US   (0)
/* ---------------------------------------------------------------------------------------*/
/* LittlevGL */
#define LV_CONFIG_DISPLAY_WIDTH        (128)
#define LV_CONFIG_DISPLAY_HEIGHT       (64)
#define LV_CONFIG_COLOR_DEPTH          (1)
//#define LV_CONFIG_DPI                  (25)
/* ---------------------------------------------------------------------------------------*/

