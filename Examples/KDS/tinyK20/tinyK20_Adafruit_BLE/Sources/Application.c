/*
 * Application.c
 *
 *  Created on: 27.12.2015
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
  #include "bleuart_cmdmode.h"
#endif

void APP_Run(void) {
  SHELL_Init();
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
  BLEUART_CMDMODE_Init();
#endif
  vTaskStartScheduler(); /* run the RTOS */
}
