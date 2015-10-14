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
#include "Relay.h"
#include "TRG1.h"
//#include "MOTL.h"

static void APP_TestServos(void) {
  uint16_t pos;
  
  for(pos=0;pos<=255;pos+=5) {
    SERVO1_SetPos(pos);
    SERVO2_SetPos(pos);
    WAIT1_Waitms(20);
  }
  SERVO1_MovePos(200, 5000);
}

static void APP_TestRelais(void) {
  int8_t i;
  
  for(i=0;i<REL_NOF_RELAYS;i++) {
    REL_On(i);
  }
  for(i=REL_NOF_RELAYS-1;i>=0;i--) {
    REL_Off(i);
  }
}

//static uint16_t oldDuty, duty = 0xffff;

void APP_Run(void) {
  SHELL_Init();
  APP_TestServos();
  REL_Init();
  APP_TestRelais();
  for(;;) {
    SHELL_Parse();
#if 0
    if (duty!=oldDuty) {
      MOTL_SetRatio16(duty);
      oldDuty = duty;
    }
#endif
  }
}

