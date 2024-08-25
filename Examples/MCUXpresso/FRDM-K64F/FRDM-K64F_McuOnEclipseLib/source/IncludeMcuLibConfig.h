/*
 * IncludeMcuLibConfig.h
 *
 *  Created on: 17.02.2019
 *      Author: Erich Styger
 */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* McuLibConfig.h */
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_LPC         (0)  /* e.g. LPC845 */
#define McuLib_CONFIG_CORTEX_M           (4)  /* K64 is a Cortex-M4 */
#define McuLib_CONFIG_CPU_IS_KINETIS     (1)  /* K64 is a Kinetis */

#define configENABLE_HEAP_PROTECTOR      (1)

/* generic I2C */
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)

/* I2C Pins */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

/*------------------ FreeRTOS ----------------------- */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (1)
#define McuSystemView_CONFIG_SYSVIEW_CONFIG_CALLBACK    App_SysView_ConfigCallback
/* turn on the following in FreeRTOSconfig.h: */
//#define configUSE_TIMERS                          1

/* ---------------------------------------------------------------------------------------*/
/* I2C and OLED */
//#define CONFIG_I2C_USE_PORT_B     (1) /* tinyK22: PTB0, PTB1 */
#define CONFIG_I2C_USE_PORT_B     (0) /* Robot: PTB2, PTB3 */
#define CONFIG_I2C_USE_PORT_E     (0) /* PTE0, PTE1 */
#define CONFIG_I2C_USE_PORT_E24_E25     (1) /* PTE24, PTE25 */ /* FRDM-K64: I2C0, SCL PTE24, SDA PTE25 */

#if CONFIG_I2C_USE_PORT_B /* robot */
  #define SCL1_CONFIG_GPIO_NAME     GPIOB
  #define SCL1_CONFIG_PORT_NAME     PORTB
  #define SCL1_CONFIG_PIN_NUMBER    2u

  #define SDA1_CONFIG_GPIO_NAME     GPIOB
  #define SDA1_CONFIG_PORT_NAME     PORTB
  #define SDA1_CONFIG_PIN_NUMBER    3u
#elif 0 /* tinyK22 */
  #define SCL1_CONFIG_GPIO_NAME     GPIOB
  #define SCL1_CONFIG_PORT_NAME     PORTB
  #define SCL1_CONFIG_PIN_NUMBER    0u

  #define SDA1_CONFIG_GPIO_NAME     GPIOB
  #define SDA1_CONFIG_PORT_NAME     PORTB
  #define SDA1_CONFIG_PIN_NUMBER    1u
#elif CONFIG_I2C_USE_PORT_E
  #define SCL1_CONFIG_GPIO_NAME     GPIOE
  #define SCL1_CONFIG_PORT_NAME     PORTE
  #define SCL1_CONFIG_PIN_NUMBER    1u

  #define SDA1_CONFIG_GPIO_NAME     GPIOE
  #define SDA1_CONFIG_PORT_NAME     PORTE
  #define SDA1_CONFIG_PIN_NUMBER    0u
#elif CONFIG_I2C_USE_PORT_E24_E25
  #define SCL1_CONFIG_GPIO_NAME     GPIOE
  #define SCL1_CONFIG_PORT_NAME     PORTE
  #define SCL1_CONFIG_PIN_NUMBER    24u

  #define SDA1_CONFIG_GPIO_NAME     GPIOE
  #define SDA1_CONFIG_PORT_NAME     PORTE
  #define SDA1_CONFIG_PIN_NUMBER    25u
#endif
#define CONFIG_USE_HW_I2C                       (0)
/* ------------------- I2C ---------------------------*/
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (1250)
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
/*-------------------------------------------------------------*/
/* McuFXOS8700 */
#define McuFXOS8700_CONFIG_I2C_DEVICE_ADDRESS  (0x1D)

#endif /* INCLUDEMCULIBCONFIG_H_ */
