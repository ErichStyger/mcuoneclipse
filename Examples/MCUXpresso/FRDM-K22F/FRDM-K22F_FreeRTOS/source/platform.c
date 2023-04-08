/*
 * platform.c
 *
 *  Created on: 09.06.2021
 *      Author: Erich Styger
 */

#include "platform.h"
#include "McuLib.h"
#include "McuRTOS.h"
#include "McuGPIO.h"
#include "McuWait.h"
#include "McuLED.h"
#include "leds.h"
#include "fsl_clock.h"

void PL_Init(void) {
  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortD);

	McuLib_Init();
	McuGPIO_Init();
	McuLED_Init();
	McuRTOS_Init();
	McuWait_Init();
	LEDS_Init();
}
