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

/* ------------------- RTOS ---------------------------*/
#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)

/* ------------------- I2C ---------------------------*/
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)
#define McuGenericI2C_CONFIG_USE_MUTEX          (1 && McuLib_CONFIG_SDK_USE_FREERTOS)

#define McuGenericSWI2C_CONFIG_DO_YIELD (0 && McuLib_CONFIG_SDK_USE_FREERTOS) /* because of Yield in GenericSWI2C */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)
/* I2C Pin Muxing */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

#define SCL1_CONFIG_GPIO_NAME     GPIOB
#define SCL1_CONFIG_PORT_NAME     PORTB
#define SCL1_CONFIG_PIN_NUMBER    2u

#define SDA1_CONFIG_GPIO_NAME     GPIOB
#define SDA1_CONFIG_PORT_NAME     PORTB
#define SDA1_CONFIG_PIN_NUMBER    3u

/* -------------------------------------------------*/
/* tinyK22 blue: PTC2
 * HAT LED blue: PTC8
 * HAT LED green: PTC9
 * HAT LED yellow: PTC10
 * HAT LED red: PTC11
 */
#define PINS_LEDBLUE_GPIO       GPIOC
#define PINS_LEDBLUE_PORT       PORTC
#define PINS_LEDBLUE_PIN        2U



#endif /* INCLUDEMCULIBCONFIG_H_ */

