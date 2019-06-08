/*
 * Application.c
 *
 *  Created on: 06.06.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "application.h"
#include "leds.h"
#include "McuWait.h"

void APP_Run(void) {
  PL_Init();

  for(;;) {
    McuLED_On(LED_red);
    McuWait_Waitms(100);
    McuLED_Off(LED_red);
    McuLED_On(LED_green);
    McuWait_Waitms(100);
    McuLED_Off(LED_green);
    McuLED_On(LED_blue);
    McuWait_Waitms(100);
  }
}
