/*
 * Application.c
 *
 *  Created on: 14.07.2018
 *      Author: Erich Styger
 */

#include "Application.h"
#include "LED1.h"
#include "WAIT1.h"


void APP_Run(void) {
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(500);
  }
}



