/*
 * Application.c
 *
 *  Created on: 13.03.2019
 *      Author: Erich Styger Local
 */

#include "Application.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuLED1.h"

void APP_Run(void) {
  McuLib_Init();
  McuWait_Init();
  McuLED1_Init();

  McuLED1_On();
  McuLED1_Off();
  for(;;) {
	  McuWait_Waitms(100);
	  McuLED1_Neg();
  }
}
