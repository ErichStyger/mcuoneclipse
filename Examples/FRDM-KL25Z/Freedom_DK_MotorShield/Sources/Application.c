/*
 * Application.c
 *
 *  Created on: May 27, 2013
 *      Author: tastyger
 */

#include "Platform.h"
#include "Application.h"
#include "Servos.h"
#include "Servo1.h"
#include "Shell.h"

//static uint16_t pos = 0;
//static uint8_t percent = 0;
static uint16_t oldUs, us = 1000;

void APP_Run(void) {
  SHELL_Init();
  //Servo1_SetDutyUS(20000-us);
  oldUs = us;
  for(;;) {
    if (us!=oldUs) {
    //  Servo1_SetDutyUS(20000-us);
      oldUs = us;
    }
    SHELL_Parse();
    //CLS1_SendStr("hello\r\n", CLS1_GetStdio()->stdOut);
    //SERVO_SetPos(SERVO1, pos);
    //SERVO_SetPos(SERVO2, pos);
    //SERVO_SetPos(SERVO1, percent);
  }
}

