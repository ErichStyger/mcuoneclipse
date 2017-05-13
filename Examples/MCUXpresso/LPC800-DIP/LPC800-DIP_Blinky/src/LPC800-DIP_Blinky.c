/*
===============================================================================
 Name        : LPC800-DIP_Blinky.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "gpio_8xx.h"

/* GPIO pin numbers for LEDs */
#define RED_LED   15
#define GREEN_LED 16
#define BLUE_LED  17

// TODO: insert other definitions and declarations here
static void BoardInit(void) {
	/* Enable the clock GPIO */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO);

	/* red */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, RED_LED);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, RED_LED, true);
	/* green */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, GREEN_LED);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, GREEN_LED, true);
	/* blue */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, BLUE_LED);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, BLUE_LED, true);
}

static void delay(void) {
	/* very simply delay routine */
	volatile uint32_t cntr = 0x80000;
	while(cntr>0) { /* burn some cycles */
		cntr--;
		__asm volatile ("nop\r\n");
	}
}

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here
    BoardInit();

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
    	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, RED_LED, true);
    	delay();
    	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, RED_LED, false);
    	delay();
    	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, GREEN_LED, true);
    	delay();
    	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, GREEN_LED, false);
    	delay();
    	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, BLUE_LED, true);
    	delay();
    	Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, BLUE_LED, false);
    	delay();
        i++ ;
    }
    return 0 ;
}
