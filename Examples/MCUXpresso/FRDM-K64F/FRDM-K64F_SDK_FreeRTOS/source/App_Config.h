/*
 * App_Config.h
 *
 *  Created on: 06.07.2018
 *      Author: Erich Styger
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

#if defined(FSL_RTOS_FREE_RTOS)
  #define APP_CONFIG_USE_FREERTOS            (1) /* 1: using FreeRTOS, 0: no FreeRTOS */
#else
  #define APP_CONFIG_USE_FREERTOS            (0) /* 1: using FreeRTOS, 0: no FreeRTOS */
#endif

#define APP_CONFIG_USE_SEGGER_SYSTEMVIEW   (0 && APP_CONFIG_USE_FREERTOS)  /* 1: SEGGER SystemView enabled; 0: disabled */

#endif /* APP_CONFIG_H_ */
