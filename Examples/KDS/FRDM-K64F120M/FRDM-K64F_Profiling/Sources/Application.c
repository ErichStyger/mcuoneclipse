/*
 * Application.c
 *
 *  Created on: 07.06.2015
 *      Author: tastyger
 */

#include "Application.h"
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "gpio1.h"
#include "coverage_stubs.h"
#include <stdio.h>

typedef enum {
	LED_COLOR_RED = (1<<0),
	LED_COLOR_GREEN = (1<<1),
	LED_COLOR_BLUE = (1<<2)
} LED_COLOR;

static LED_COLOR whichLED = LED_COLOR_RED; /* default: red */
static int nofButtonPresses;
static bool doExit=false;

static void CheckButton(void) {
	uint32_t val;

  val = GPIO_DRV_ReadPinInput(BUTTON_SW2);
  if (val==0) { /* SW2 pressed! */
	  nofButtonPresses++;
	  whichLED <<= 1;
	  if (whichLED>LED_COLOR_BLUE) {
		  whichLED = LED_COLOR_RED; /* back to red */
	  }
	  while(GPIO_DRV_ReadPinInput(BUTTON_SW2)==0) {
		  /* wait until button is released */
	  }
  }
  val = GPIO_DRV_ReadPinInput(BUTTON_SW3);
  if (val==0) { /* SW3 pressed! */
	  nofButtonPresses++;
	  whichLED >>= 1;
	  if (whichLED==0) {
		  whichLED = LED_COLOR_BLUE;
	  }
	  while(GPIO_DRV_ReadPinInput(BUTTON_SW3)==0) {
		  /* wait until button is released */
	  }
  }
}

void APP_Run(void) {
  printf("Lab program using semihosting!\r\nProgram will NOT run without debugger attached!\r\n");
  for(;;) {
	CheckButton();
	if (whichLED==LED_COLOR_RED) {
	  GPIO_DRV_TogglePinOutput(led_red); /* red toggle */
	}
	if (whichLED==LED_COLOR_GREEN) {
	  GPIO_DRV_TogglePinOutput(led_green); /* green toggle */
	}
	if (whichLED==LED_COLOR_BLUE) {
	  GPIO_DRV_TogglePinOutput(led_blue); /* blue toggle */
	}
	OSA_TimeDelay(100); /* wait 100 ms */
	doExit = nofButtonPresses>5;
	if (doExit) {
	  GPIO_DRV_SetPinOutput(led_red);
	  GPIO_DRV_SetPinOutput(led_green);
	  GPIO_DRV_SetPinOutput(led_blue);
	  _exit(0); /* write coverage/profiling information */
	}
  }
}


