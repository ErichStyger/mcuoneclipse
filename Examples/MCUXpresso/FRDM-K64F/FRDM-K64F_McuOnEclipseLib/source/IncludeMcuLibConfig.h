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
/* turn on the following in FreeRTOSconfig.h: */
//#define configUSE_TIMERS                          1

#define McuGenericSWI2C_CONFIG_DO_YIELD (0) /* Yield Msg in GenericSWI2C */

#endif /* INCLUDEMCULIBCONFIG_H_ */
