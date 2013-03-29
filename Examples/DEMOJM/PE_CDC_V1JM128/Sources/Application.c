/*
 * Application.c
 *
 *  Created on: 09.12.2011
 *      Author: Erich Styger
 */
#include "Application.h"
#include "Shell.h"
#include "FRTOS1.h"

void APP_Run(void) {
  SHELL_Init();
  FRTOS1_vTaskStartScheduler();
}
