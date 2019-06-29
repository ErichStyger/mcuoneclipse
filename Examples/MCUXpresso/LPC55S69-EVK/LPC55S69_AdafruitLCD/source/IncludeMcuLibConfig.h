/*
 * IncludeMcuLibConfig.h
 *
 *  Created on: 17.02.2019
 *      Author: Erich Styger
 */

/* header file is included with -include compiler option */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_KINETIS    (0)
#define McuLib_CONFIG_CPU_IS_LPC        (1)
#define McuLib_CONFIG_CPU_IS_LPC55xx    (1)
#define McuLib_CONFIG_CORTEX_M          (33)

/* ------------------- RTOS ---------------------------*/
#define configTOTAL_HEAP_SIZE                 (16*1024)
#define McuLib_CONFIG_SDK_USE_FREERTOS        (1)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS  (0)  /* \todo */
#define configRUN_FREERTOS_SECURE_ONLY        (0)
#define configENABLE_TRUSTZONE                (0)
#define configENABLE_FPU                      (1) /* \todo */
#define configENABLE_MPU                      (0) /* \todo */

#if 0
/* ------------------- I2C ---------------------------*/
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)
/* I2C Pin Muxing */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

#if USE_HW_I2C
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
#endif

#define SCL1_CONFIG_GPIO_NAME     GPIOA
#define SCL1_CONFIG_PORT_NAME     PORTA
#define SCL1_CONFIG_PIN_NUMBER    12u

#define SDA1_CONFIG_GPIO_NAME     GPIOA
#define SDA1_CONFIG_PORT_NAME     PORTA
#define SDA1_CONFIG_PIN_NUMBER    13u

/* -------------------------------------------------*/
/* Shell */
#define McuShell_CONFIG_PROJECT_NAME_STRING "Raspberry Pi UPS and Gateway"

#define LV_CONFIG_DISPLAY_WIDTH        (128)
#define LV_CONFIG_DISPLAY_HEIGHT       (64)
#define LV_CONFIG_COLOR_DEPTH          (1)
#define LV_CONFIG_DPI                  (25)

#endif

#endif /* INCLUDEMCULIBCONFIG_H_ */

