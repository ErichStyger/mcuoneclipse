/*
 * Application.c
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "Shell.h"

void APP_Run(void) {
  SHELL_Init();
  for(;;) {
    SHELL_Parse();
  }
}

