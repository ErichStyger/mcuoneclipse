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
#include "HC595.h"

static void APP_TestServos(void) {
  uint16_t pos;
  
  for(pos=0;pos<=255;pos+=5) {
    SERVO1_SetPos(pos);
    SERVO2_SetPos(pos);
    WAIT1_Waitms(20);
  }
}

void APP_Run(void) {
  uint8_t i=0;
  
  APP_TestServos();
  SHELL_Init();
  for(;;) {
    SHELL_Parse();
    HC595_ShiftByte(i);
    HC595_Latch();
    i++;
  }
}

