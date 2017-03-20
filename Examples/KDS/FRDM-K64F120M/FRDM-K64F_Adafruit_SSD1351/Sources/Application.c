/*
 * Application.c
 *
 *  Created on: 20.03.2017
 *      Author: Erich Styger Local
 */

#include "Application.h"
#include "LED1.h"
#include "LED2.h"
#include "LED3.h"
#include "WAIT1.h"

void APP_Run(void) {
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(100);
    LED2_Neg();
    WAIT1_Waitms(100);
    LED3_Neg();
    WAIT1_Waitms(100);
  }
}

