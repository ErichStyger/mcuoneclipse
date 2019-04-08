/*
 * IncludeMcuLibConfig.h
 *
 *  Created on: 17.02.2019
 *      Author: Erich Styger  */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/*------------------ FreeRTOS ----------------------- */
#define McuLib_CONFIG_SDK_USE_FREERTOS  (0)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0)

/* LED tinyK22: */
#define PINS_LEDBLUE_GPIO       GPIOC
#define PINS_LEDBLUE_PORT       PORTC
#define PINS_LEDBLUE_PIN        2U


#endif /* INCLUDEMCULIBCONFIG_H_ */
