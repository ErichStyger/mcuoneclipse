/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    LPC845-BRK_Blinky.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"

#include "McuWait.h"
#include "leds.h"
#include "McuLED.h"
#include "buttons.h"

int array[] = {1,2,5,3,10,4,7,6,9,5};
/* gdb console:
  source plot1d.gdb
  plot1d array
 */

/*
 * @brief   Application entry point.
 */
int main(void) {
 	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    if (array[0]!=0) {
      array[0]++;
    }

//    printf("Hello World\n");
    GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0: used for push buttons */
    GPIO_PortInit(GPIO, 1); /* ungate the clocks for GPIO_1: used for LEDs */

    /* initialize driver and modules */
    /* init modules */
    LEDS_Init();
    McuLED_Init();
    BTN_Init();
    McuWait_Init();
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
    return 0 ;
}
