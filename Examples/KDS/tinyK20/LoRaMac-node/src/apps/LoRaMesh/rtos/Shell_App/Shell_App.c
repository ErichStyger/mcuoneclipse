/**
 * \file Shell.c
 * \author alexanderwiniger
 * \date Dec 23, 2015
 * \version 1.0
 *
 * \brief
 *
 *******************************************************************************
 *  Change log:
 *      [1.0]   Dec 23, 2015      	alexanderwiniger
 *          - created
 *******************************************************************************
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"
#include "Shell_App.h"
#include "Shell.h"
#include "LoRaMesh.h"
#include "LoRaMesh_App.h"
#include "Shell_FreeRTOS.h"

/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE TYPE DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
static const Shell_ParseCommandCallback_t CmdParserTable[] = { Shell_ParseCommand,
        FreeRTOS_ParseCommand, LoRaMesh_AppParseCommand, LoRaMesh_ParseCommand, NULL /* sentinel */
};

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES (STATIC)
 ******************************************************************************/
void ShellTask( void *pvParameters );

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
void Shell_AppInit( void )
{
    if ( xTaskCreate(ShellTask, "Shell", configMINIMAL_STACK_SIZE + 300, (void*) NULL,
            tskIDLE_PRIORITY + 1, (xTaskHandle*) NULL) != pdPASS ) {
        /*lint -e527 */
        for ( ;; ) {
        }; /* error! probably out of memory */
        /*lint +e527 */
    }
}

/*******************************************************************************
 * PRIVATE FUNCTIONS (STATIC)
 ******************************************************************************/
void ShellTask( void *pvParameters )
{
    unsigned char buf[48];

    (void) pvParameters; /* not used */
    buf[0] = '\0';

    (void) Shell_ParseWithCommandTable((unsigned char*) SHELL_CMD_HELP, Shell_GetStdio(),
            CmdParserTable);
    for ( ;; ) {
        (void) Shell_ReadAndParseWithCommandTable(buf, sizeof(buf), Shell_GetStdio(),
                CmdParserTable);
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
