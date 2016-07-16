/**
 * \file main.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 17.11.2015
 * \brief Hello World application implementation
 *
 */

#include "board.h"
#include "uart.h"

#define LOG_LEVEL_TRACE
#include "debug.h"

/*------------------------- Local Defines --------------------------------*/

/*------------------------ Local Variables -------------------------------*/
static TimerEvent_t Led1Timer;
volatile bool Led1TimerEvent = false;

static bool AppLedStateOn;

/*!
 * \brief Function executed on Led 1 Timeout event
 */
void OnLed1TimerEvent( void )
{
    Led1TimerEvent = true;
}

/*!
 * \brief Main application entry point.
 */
int main( void )
{
    // Target board initialisation
    BoardInitMcu();
    LOG_TRACE("Mcu initialized.");
    BoardInitPeriph();
    LOG_TRACE("Peripherals initialized.");

    TimerInit(&Led1Timer, OnLed1TimerEvent);
    TimerSetValue(&Led1Timer, 250000);

    // Switch LED 1 ON
    GpioWrite(&Led1, 0);
    AppLedStateOn = true;
    TimerStart(&Led1Timer);

    // Print the initial banner
    LOG_DEBUG_BARE("\r\nHello World!\r\n\r\n");

    while ( 1 ) {
        if ( Led1TimerEvent == true ) {
            Led1TimerEvent = false;

            // Switch LED 1 OFF
            if ( AppLedStateOn )
                GpioWrite(&Led1, 1);
            else
                GpioWrite(&Led1, 0);
            AppLedStateOn = !AppLedStateOn;
            TimerStart(&Led1Timer);
        }
    }
}
