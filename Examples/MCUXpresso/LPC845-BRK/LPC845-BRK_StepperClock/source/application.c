/*
 * application.c
 *
 *  Created on: 30.07.2019
 *      Author: Erich Styger
 */

#include "platform.h"
#include "application.h"
#include "McuWait.h"
#include "buttons.h"
#include "leds.h"


void APP_Run(void) {
	PL_Init();
	for(;;) {
    if (BTN_K1ButtonIsPressed()) { /* check push button */
      McuLED_On(LEDS_Green);
      while(BTN_K1ButtonIsPressed()) {}
    }
    if (BTN_K3ButtonIsPressed()) { /* check push button */
      McuLED_On(LEDS_Red);
      while(BTN_K3ButtonIsPressed()) {}
    }
    McuLED_On(LEDS_Green);
    McuWait_Waitms(100);
    McuLED_Off(LEDS_Green);

    McuLED_On(LEDS_Blue);
    McuWait_Waitms(100);
    McuLED_Off(LEDS_Blue);

    McuLED_On(LEDS_Red);
    McuWait_Waitms(100);
    McuLED_Off(LEDS_Red);
	}
}
