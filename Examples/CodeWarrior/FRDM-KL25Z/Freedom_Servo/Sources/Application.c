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
  uint16_t pos;
  
  /* move each servo from 0 to 255 */
  for(pos=0;pos<256;pos++) {
    SERVO1_SetPos(pos);
    SERVO2_SetPos(pos);
    WAIT1_Waitms(50);
  }
  /* Use timed move */
  for(;;) {
    SERVO1_MovePos(0, 4000);
    SERVO2_MovePos(0, 1000);
    WAIT1_Waitms(8000); /* wait some time */
    SERVO1_MovePos(150, 2000);
    SERVO2_MovePos(150, 500);
    WAIT1_Waitms(4000); /* wait some time */
  }
}


