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
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
/*! Main application entry point. */
void main( void )
{
    BoardInitMcu();

    LOG_DEBUG("Mcu initialized.");
    OSA_Init();
    LOG_DEBUG("OS initialized.");
    BoardInitPeriph();
    LOG_DEBUG("Peripherals initialized.");

#if defined( USE_SHELL )
#if defined (USE_USB_CDC)
    Shell_Init (&UartUsb);
#else
    Shell_Init (&Uart1);
#endif /* USE_USB_CDC */
#endif /* USE_SHELL */

    LoRaMesh_AppInit();

    vTaskStartScheduler();

    for ( ;; ) {
        /* Should not be reached */
    }
}

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
