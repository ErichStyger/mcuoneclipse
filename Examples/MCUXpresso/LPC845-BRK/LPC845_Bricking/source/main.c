#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "fsl_debug_console.h"
#include "leds.h"
#include "McuLib.h"
#include "McuWait.h"
#include "McuGPIO.h"
#include "McuLED.h"

int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    McuLib_Init();
    McuWait_Init();
    McuGPIO_Init();
    McuLED_Init();
    LEDS_Init();

    for(int i=0; i<10; i++) {
      McuWait_Waitms(100);
      McuLED_Toggle(LEDS_Blue);
    }
    McuLED_Off(LEDS_Blue);
    BOARD_DisableDebug();
    for(;;) {
      McuWait_Waitms(1000);
      McuLED_Toggle(LEDS_Red);
    }
    PRINTF("Hello World\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
