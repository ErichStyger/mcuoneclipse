/*
 * Application.c
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "Shell.h"
#include "74HCT595N.h"

void APP_Run(void) {
  uint8_t i=0;
  
  SHELL_Init();
  (void)HCT_Init();
  for(;;) {
    SHELL_Parse();
    (void)HCT_ShiftByte(i);
    HCT_Latch();
    i++;
  }
}

