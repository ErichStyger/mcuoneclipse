/*
 * IncludeMcuLibConfig.h
 *
 *  Created on: 17.02.2019
 *      Author: Erich Styger  */

#ifndef INCLUDEMCULIBCONFIG_H_
#define INCLUDEMCULIBCONFIG_H_

/* ------------------- SDK/Library ---------------------------*/
#define McuLib_CONFIG_SDK_VERSION_USED   McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_CPU_IS_LPC         (0)  /* LPC845 */
#define McuLib_CONFIG_CORTEX_M           (4)  /* K22 is a Cortex-M4 */
#define McuLib_CONFIG_CPU_IS_KINETIS     (1)  /* K22 is a Kinetis */
#define McuLib_CONFIG_CPU_VARIANT        McuLib_CONFIG_CPU_VARIANT_NXP_K22FN
/*------------------ FreeRTOS ----------------------- */
#define McuLib_CONFIG_SDK_USE_FREERTOS  (0)
#define configUSE_SEGGER_SYSTEM_VIEWER_HOOKS (0)

/* LED tinyK22: */
#define PINS_LEDBLUE_GPIO       GPIOC
#define PINS_LEDBLUE_PORT       PORTC
#define PINS_LEDBLUE_PIN        2U


#endif /* INCLUDEMCULIBCONFIG_H_ */
