/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "VS1053.h"

void APP_Run(void) {
  SHELL_Init(); /* initialize shell */
  VS_Init(); /* initialize VS1053B module */
  FRTOS1_vTaskStartScheduler();
}

