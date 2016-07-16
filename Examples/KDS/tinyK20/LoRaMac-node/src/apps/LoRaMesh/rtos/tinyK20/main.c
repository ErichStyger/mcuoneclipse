/**
 * \file main.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 12.11.2015
 * \brief LoRaMesh implementation
 *
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include <string.h>
#include <math.h>
#include "board.h"

#include "Shell_App.h"
#include "LoRaMesh_AppConfig.h"
#include "LoRaMesh_App.h"

#define LOG_LEVEL_TRACE
#include "debug.h"

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
static uint32_t heartBeatCntr;
static bool heartBeatLedOn;

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
/*! Main application entry point. */
int main( void )
{
    BoardInitMcu();
    LOG_DEBUG_BARE("\r\n");
    LOG_DEBUG("Mcu initialized.");
    BoardInitPeriph();
    LOG_DEBUG("Peripherals initialized.");
#if defined( USE_SHELL )
    Shell_AppInit ();
#endif /* USE_SHELL */

    LoRaMesh_AppInit();

    /* Reset heartBeatCntr */
    heartBeatCntr = 0;
    heartBeatLedOn = false;

    vTaskStartScheduler();

    LOG_ERROR("Failed to create idle task. Probably out of memory.");

    for ( ;; ) {
        /* Should not be reached */
    }
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
void vApplicationIdleHook( void )
{
    uint32_t rollOverValue;
    uint8_t appState = LoRaMesh_AppStatus();

    if ( appState < ACTIVE ) {
        rollOverValue = 100000;
    } else {
        rollOverValue = 500000;
    }

    if ( (heartBeatCntr++ % rollOverValue) == 0 ) {
        if ( heartBeatLedOn )
            GpioWrite(&Led1, 1);
        else
            GpioWrite(&Led1, 0);
        heartBeatLedOn = !heartBeatLedOn;
    }
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, char *pcTaskName )
{
    /* This will get called if a stack overflow is detected during the context
     switch.  Set configCHECK_FOR_STACK_OVERFLOWS to 2 to also check for stack
     problems within nested interrupts, but only do this for debug purposes as
     it will increase the context switch time. */
    (void) pxTask;
    (void) pcTaskName;
    taskDISABLE_INTERRUPTS();
    /* Write your code here ... */
    for ( ;; ) {
    }
}

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
