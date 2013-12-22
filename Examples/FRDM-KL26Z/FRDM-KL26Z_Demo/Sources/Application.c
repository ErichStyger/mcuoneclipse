/*
 * Application.c
 *
 *  Created on: Dec 22, 2013
 *      Author: tastyger
 */
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"
#include "CLS1.h"

void APP_Run(void) {
  for(;;) {
    LED1_Neg();
    LED2_Neg();
    LED3_Neg();
    CLS1_SendStr((unsigned char*)"Hello\r\n", CLS1_GetStdio()->stdOut);
    WAIT1_Waitms(200);
  }
}
