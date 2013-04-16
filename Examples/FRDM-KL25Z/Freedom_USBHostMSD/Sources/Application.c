/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "host.h"

void APP_Run(void) {
  HOST_Init();
  SHELL_Init();
  FRTOS1_vTaskStartScheduler();
}

