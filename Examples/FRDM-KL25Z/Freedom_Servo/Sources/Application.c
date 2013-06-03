/*
 * Application.c
 *
 *  Created on: May 30, 2013
 *      Author: Erich Styger
 */
#include "Application.h"
#include "WAIT1.h"
#include "SERVO1.h"
#include "SERVO2.h"

void APP_Run(void) {
  uint8_t pos;
  
  for(;;) {
    for(pos=0;pos<256;pos++) {
      SERVO1_SetPos(pos);
      SERVO2_SetPos(pos);
      WAIT1_Waitms(50);
    }
  }
}


