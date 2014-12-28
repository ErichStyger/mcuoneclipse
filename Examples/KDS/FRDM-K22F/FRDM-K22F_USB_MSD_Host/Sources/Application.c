/*
 * Application.c
 *      Author: Erich Styger
 */
#include "Platform.h"
#include "Application.h"
#include "FRTOS1.h"
#include "Shell.h"
#include "host.h"

void APP_Run(void) {
#if PL_HAS_HOST
  HOST_Init();
#endif
  SHELL_Init();
  FRTOS1_vTaskStartScheduler();
}

