/*
 * Application.c
 *
 *  Created on: May 27, 2013
 *      Author: Erich Styger
 */

#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#include "SERVO1.h"
#include "SERVO2.h"
#include "Shell.h"
#include "74HCT595N.h"

static void APP_TestServos(void) {
  uint8_t pos;
  
  for(pos=0;pos<256;pos++) {
    SERVO1_SetPos(pos);
    SERVO2_SetPos(pos);
    WAIT1_Waitms(50);
  }
}

void APP_Run(void) {
  uint8_t i=0;
  
  APP_TestServos();
  SHELL_Init();
  (void)HCT_Init();
  for(;;) {
    SHELL_Parse();
    HCT_ShiftByte(i);
    HCT_Latch();
    i++;
  }
}

