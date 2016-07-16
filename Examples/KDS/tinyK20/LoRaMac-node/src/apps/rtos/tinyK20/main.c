/**
 * \file main.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 28.11.2015
 * \brief FreeRTOS test implementation
 *
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"

#define LOG_LEVEL_DEBUG
#include "debug.h"

/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
/* led task priority */
#define LED_TASK_PRIO               (7U)
/* led task stack size */
#define LED_TASK_STACK_SIZE         (0x200U)

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
static bool IsLedActive = true;

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
/*!
 * task to blink led rtos between 1 seconds.
 */
void LedTask( void* pvArguments )
{
    // Switch LED 1 ON
    GpioWrite(&Led1, 0);

    while (1) {
        if ( IsLedActive ) {
            IsLedActive = false;
            // Switch LED 1 OFF
            GpioWrite(&Led1, 1);
        } else {
            IsLedActive = true;
            // Switch LED 1 ON
            GpioWrite(&Led1, 0);
            UartPutChar(&Uart2, 'H');
            UartPutChar(&Uart2, 'e');
            UartPutChar(&Uart2, 'l');
            UartPutChar(&Uart2, 'l');
            UartPutChar(&Uart2, 'o');
            UartPutChar(&Uart2, ' ');
            UartPutChar(&Uart2, 'W');
            UartPutChar(&Uart2, 'o');
            UartPutChar(&Uart2, 'r');
            UartPutChar(&Uart2, 'l');
            UartPutChar(&Uart2, 'd');
            UartPutChar(&Uart2, '\r');
            UartPutChar(&Uart2, '\n');
        }

        vTaskDelay(500 / portTICK_RATE_MS);
    }
}

int main( void )
{
    uint8_t TxBuffer[128];
    uint8_t RxBuffer[128];
    TaskHandle_t xHandle = NULL;

    // Target board initialisation
    BoardInitMcu();
    LOG_DEBUG("Mcu initialized.");
    BoardInitPeriph();
    LOG_DEBUG("Peripherals initialized.");

    FifoInit(&Uart2.FifoTx, TxBuffer, sizeof(TxBuffer));
    FifoInit(&Uart2.FifoRx, RxBuffer, sizeof(RxBuffer));

    UartInit(&Uart2, UART_2, UART2_TX, UART2_RX);
    UartConfig(&Uart2, RX_TX, 115200, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY,
            NO_FLOW_CTRL);

    xTaskCreate(LedTask, "LedTask", LED_TASK_STACK_SIZE, (void*) NULL, LED_TASK_PRIO,
            &xHandle);
    configASSERT(xHandle);

    // Print the initial banner
    LOG_DEBUG("Hello World!\r\n");

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for ( ;; ) {
    }   // Should not be reached here
}

/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
