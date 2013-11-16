/*
    FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.


    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest information,
    license and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/*
 * This is a very simple demo that demonstrates task and queue usages only.
 * Details of other FreeRTOS features (API functions, tracing features,
 * diagnostic hook functions, memory management, etc.) can be found on the
 * FreeRTOS web site (http://www.FreeRTOS.org) and in the FreeRTOS book.
 * Details of this demo (what it does, how it should behave, etc.) can be found
 * in the accompanying PDF application note.
 *
*/

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Port include files. */
#include "PE_Types.h"
#include "IO_Map.h"
#include "Events.h"

/* Priorities at which the tasks are created. */
#define	mainCHECK_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* The bit of port 0 that the MC56F8400 LED is connected. */
#define mainLED_MAX							( 8 )		//Maximum LED number, no greater than 8
#define mainLED_BIT 						( 0 )		//Port number, less than mainLED_MAX

/* The rate at which data is sent to the check task, specified in milliseconds. */
#define mainCHECK_DELAY_MS			( 500 / portTICK_RATE_MS )

/*
 * The check tasks.
 */
static void prvCheckTask( void *pvParameters );

/*
 * Simple function to initialize hardware platform board.
 */
static void prvSetupHardware( void );

/*
 * Simple function to toggle the LED on the MC56F8400 tower board.
 */
static void prvToggleLED( void );


/*-----------------------------------------------------------*/

void LEDTestwithRTOS (void)
{
	/* Configure any hardware required for this demo. */
	prvSetupHardware();

	/* Create the check task. */
	xTaskCreate( prvCheckTask, ( signed char * ) "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );

	/* Start the tasks running. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
}
/*-----------------------------------------------------------*/

static void prvSetupHardware(void)
{
	/* Enable GPIOE/F ports clock. */
	setReg16Bits(SIM_PCE0,0x06);
	/* Configure GPIOE0-7,GPIOF6 as output function. */
	clrReg16Bits(GPIOE_PER, 0x0FFU);
	setReg16Bits(GPIOE_DDR, 0x0FFU);
	clrReg16Bits(GPIOF_PER, 0x40U);
	setReg16Bits(GPIOF_DDR, 0x40U);
	/* Output 0 to turn off all LEDs. */
	clrReg16Bits(GPIOE_DR, 0x0FFU);
	clrReg16Bits(GPIOF_DR, 0x40U);
}

static void prvCheckTask( void *pvParameters )
{
portTickType xNextWakeTime;
const portTickType xTicksToWait = mainCHECK_DELAY_MS;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again.
		The block state is specified in ticks, the constant used converts ticks
		to ms.  While in the blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, xTicksToWait );

		/* Toggle its LED */
		prvToggleLED();
	}
}
/*-----------------------------------------------------------*/

static void prvToggleLED( void )
{
	portENTER_CRITICAL();
	/* Toggle the LED. */
	if(mainLED_BIT < mainLED_MAX)
	{
		invertReg16Bits(GPIOE_DR, (UWord16)( 1 << mainLED_BIT ));
	}
	portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

