/*
 * Application.c
 *
 *  Created on: 04.03.2016
 *      Author: Erich Styger
 */

#include "Application.h"
#include "CLS1.h"
#include "LED1.h"
#include "Shell.h"
#include "WAIT1.h"
#include "A3967.h"

void APP_Start(void) {
  SHELL_Init();
  A3967_Init();
  for(;;) { /* main loop */
    LED1_Neg();
    WAIT1_Waitms(50);
    SHELL_Parse(); /* call command line parser */
  }
}
