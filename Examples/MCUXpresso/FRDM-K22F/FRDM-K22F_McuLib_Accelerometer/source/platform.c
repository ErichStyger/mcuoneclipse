/*
 * platform.c
 *
 *  Created on: 06.06.2019
 *      Author: Erich Styger Local
 */


#include "platform.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"

#include "leds.h"

void PL_Init(void) {
  /* LEDs are on PTA1, PTA2 and PTD5 */
  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortD);

  McuLib_Init();
  McuWait_Init();
  McuGPIO_Init();
  McuLED_Init();

  LEDS_Init();
}
