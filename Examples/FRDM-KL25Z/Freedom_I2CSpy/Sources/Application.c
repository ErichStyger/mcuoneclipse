/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"

void APP_Run(void) {
  SHELL_Init();
  FRTOS1_vTaskStartScheduler();
}

