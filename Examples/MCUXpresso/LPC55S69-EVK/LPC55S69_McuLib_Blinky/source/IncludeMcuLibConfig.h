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
#define McuLib_CONFIG_CPU_IS_KINETIS    (0)
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0

/* ------------------- RTOS ---------------------------*/
/* Note: set configTOTAL_HEAP_SIZE to 16k in FreeRTOSConfig.h */
#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0 && McuLib_CONFIG_SDK_USE_FREERTOS)

/* ------------------- I2C ---------------------------*/
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (1 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)
/* I2C Pin Muxing */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

//  #define SCL1_CONFIG_GPIO_NAME     GPIOA
//  #define SCL1_CONFIG_PORT_NAME     PORTA
//  #define SCL1_CONFIG_PIN_NUMBER    12u
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

#endif /* INCLUDEMCULIBCONFIG_H_ */

