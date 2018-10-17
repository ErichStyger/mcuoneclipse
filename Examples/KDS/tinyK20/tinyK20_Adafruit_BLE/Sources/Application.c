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
#include "PORT_PDD.h"

void APP_Run(void) {
  /* need pull-up on UART Rx pin (PTC3) */
  PORT_PDD_SetPinPullSelect(PORTC_BASE_PTR, 3, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTC_BASE_PTR, 3, PORT_PDD_PULL_ENABLE);
  SHELL_Init();
#if PL_CONFIG_BLEUART_CMDMODE_ENABLED
  BLEUART_CMDMODE_Init();
#endif
  vTaskStartScheduler(); /* run the RTOS */
}
