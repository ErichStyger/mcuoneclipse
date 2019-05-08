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
#define McuLib_CONFIG_SDK_USE_FREERTOS  (1)

/* LED1 -> LedPin1 */
#define LEDpin1_CONFIG_PORT_NAME       PORTB
#define LEDpin1_CONFIG_GPIO_NAME       GPIOB
#define LEDpin1_CONFIG_PIN_NUMBER      22u

/* generic I2C */
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)

/* I2C Pins */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

/*------------------ FreeRTOS ----------------------- */
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (1)
/* turn on the following in FreeRTOSconfig.h: */
//#define configUSE_TIMERS                          1

#define McuGenericSWI2C_CONFIG_DO_YIELD (0) /* Yield Msg in GenericSWI2C */

#endif /* INCLUDEMCULIBCONFIG_H_ */
