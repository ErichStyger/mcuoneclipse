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
#include "LoRaMesh_App.h"
#include "LoRaMacCrypto.h"

#define LOG_LEVEL_TRACE
#include "debug.h"

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
void LedTask( void *pvParameters );

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
/*! Main application entry point. */
int main( void )
{
    BoardInitMcu();
    LOG_DEBUG("Mcu initialized.");
    BoardInitPeriph();
    LOG_DEBUG("Peripherals initialized.");

    if ( xTaskCreate(LedTask, "Led", configMINIMAL_STACK_SIZE, (void*) NULL,
            tskIDLE_PRIORITY, (xTaskHandle*) NULL) != pdPASS ) {
        /*lint -e527 */
        for ( ;; ) {
        }; /* error! probably out of memory */
        /*lint +e527 */
    }

#if defined( USE_SHELL )
    Shell_AppInit ();
#endif /* USE_SHELL */

    LoRaMesh_AppInit();

    vTaskStartScheduler();

    for ( ;; ) {
        /* Should not be reached */
    }
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
void LedTask( void *pvParameters )
{
    bool isLedActive = false;

    for ( ;; ) {
        if ( isLedActive ) GpioWrite(&Led1, 1);
        else GpioWrite(&Led1, 0);
        isLedActive = !isLedActive;
        vTaskDelay(500 / portTICK_RATE_MS);
    }
}

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
