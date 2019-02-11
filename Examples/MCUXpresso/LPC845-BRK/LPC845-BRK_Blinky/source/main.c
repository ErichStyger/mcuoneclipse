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
/* TODO: insert other include files here. */

#include "McuWait.h"
#include "McuLED1.h"
#include "McuLED2.h"
#include "McuLED3.h"
#include "McuHardFault.h"
#include "McuArmTools.h"
#include "fsl_gpio.h"
/* TODO: insert other definitions and declarations here. */

static bool BTN_K3_Pressed(void) {
  /* pin has 10K pull-up */
  return GPIO_PinRead(BOARD_INITPINS_BTNpin3_GPIO, BOARD_INITPINS_BTNpin3_PORT, BOARD_INITPINS_BTNpin3_PIN)==0;
}

static bool BTN_K1_Pressed(void) {
  /* pin has 10K pull-up */
  return GPIO_PinRead(BOARD_INITPINS_BTNpin1_GPIO, BOARD_INITPINS_BTNpin1_PORT, BOARD_INITPINS_BTNpin1_PIN)==0;
}
/*
 * @brief   Application entry point.
 */
int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    printf("Hello World\n");

    GPIO_PortInit(GPIO, 0); /* ungate the clocks for GPIO_0: used for push buttons */
    GPIO_PortInit(GPIO, 1); /* ungate the clocks for GPIO_1: used for LEDs */

    /* initialize driver and modules */
    McuWait_Init();
    McuHardFault_Init();
    McuArmTools_Init();
    McuLED1_Init();
    McuLED2_Init();
    McuLED3_Init();
#if 0
    McuArmTools_SoftwareReset(); /* this will perform a reset, see https://mcuoneclipse.com/2015/07/01/how-to-reset-an-arm-cortex-m-with-software/ */
#endif
    for(;;) {
      if (BTN_K1_Pressed()) { /* check push button */
        McuLED1_On(); /* green */
        while(BTN_K1_Pressed()) {}
      }
      if (BTN_K3_Pressed()) { /* check push button */
        McuLED3_On(); /* red */
        while(BTN_K3_Pressed()) {}
      }
      McuLED1_On(); /* green */
      McuWait_Waitms(100);
      McuLED1_Off();

      McuLED2_On(); /* blue */
      McuWait_Waitms(100);
      McuLED2_Off();

      McuLED3_On(); /* red */
      McuWait_Waitms(100);
      McuLED3_Off();
    }
    return 0 ;
}
