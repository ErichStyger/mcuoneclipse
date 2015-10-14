/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Application.h"
#include "LEDR.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "Hoval.h"

void APP_Run(void) {
  SHELL_Init();
  HOVAL_Init();
  FRTOS1_vTaskStartScheduler();
}
