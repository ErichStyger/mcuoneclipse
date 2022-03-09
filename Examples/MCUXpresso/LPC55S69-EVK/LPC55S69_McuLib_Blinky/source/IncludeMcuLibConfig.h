/*
 * IncludeMcuLibConfig.h
 *
 *  Created on: 17.02.2019
 *      Author: Erich Styger
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define McuLib_CONFIG_CPU_IS_LPC        (1)
#define McuLib_CONFIG_CPU_IS_LPC55xx    (1)
#define McuLib_CONFIG_CPU_VARIANT       McuLib_CONFIG_CPU_VARIANT_NXP_LPC55S69
#define McuLib_CONFIG_CPU_IS_KINETIS    (0)
#define McuLib_CONFIG_CORTEX_M          (33)
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0

#define configRUN_FREERTOS_SECURE_ONLY (0)
#define configENABLE_TRUSTZONE         (0)

/* ------------------- RTOS ---------------------------*/
/* Note: set configTOTAL_HEAP_SIZE to 16k in FreeRTOSConfig.h */
#define McuLib_CONFIG_SDK_USE_FREERTOS       (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0 && McuLib_CONFIG_SDK_USE_FREERTOS)

/* ------------------- I2C ---------------------------*/
#define USE_HW_I2C           (0)  /* otherwise uses GPIO bit-banging */

#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (1 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)
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

  /* using SCL/SDA on the Mikro Bus connector */
  #define SCL1_CONFIG_GPIO_NAME     GPIO
  #define SCL1_CONFIG_PORT_NAME     0
  #define SCL1_CONFIG_PIN_NUMBER    19u

  #define SDA1_CONFIG_GPIO_NAME     GPIO
  #define SDA1_CONFIG_PORT_NAME     0
  #define SDA1_CONFIG_PIN_NUMBER    5u
#endif
/* -------------------------------------------------*/
#if 1 /* type of OLED */
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1106)
#else
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1306)
#endif
//#define McuSSD1306_CONFIG_SSD1306_START_COLUMN_OFFSET (0) /* needed for 1.3" Banggood display */
/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING "LPC55S69-EVK"
/* -----------------------------------------------------*/
/* McuSWO */
#define McuSWO_CONFIG_HAS_SWO         (1) /* enable SWO support */
//#define McuSWO_CONFIG_SPEED_BAUD      (5625000) /* J-Link supports up to 5625 kHz */
#define McuSWO_CONFIG_SPEED_BAUD      (96000000) /* needed for LinkServer and MCUXpresso IDE 11.5.0 */

#endif /* INCLUDEMCULIBCONFIG_H_ */

