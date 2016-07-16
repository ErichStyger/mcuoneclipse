/**
 * \file gps-board.c
 * \author Alexander Winiger (alexander.winiger@hslu.ch)
 * \date 02.11.2015
 * \brief Target board driver for GPS receiver
 *
 */

/*******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "board.h"

#define LOG_LEVEL_TRACE
#include "debug.h"

/*******************************************************************************
 * PRIVATE CONSTANT DEFINITIONS
 ******************************************************************************/
/*!
 * FIFO buffers size
 */
//#define FIFO_TX_SIZE                                128
#define FIFO_RX_SIZE                                128

/*******************************************************************************
 * PRIVATE VARIABLES (STATIC)
 ******************************************************************************/
/*! FIFO buffers */
//uint8_t TxBuffer[FIFO_TX_SIZE];
uint8_t RxBuffer[FIFO_RX_SIZE];

/*! Nmea string */
int8_t NmeaString[128];
uint8_t NmeaStringSize = 0;

/*******************************************************************************
 * MODULE FUNCTIONS (PUBLIC)
 ******************************************************************************/
void GpsMcuOnPpsSignal( void )
{
    bool parseData = false;

    GpsPpsHandler(&parseData);

    if ( parseData == true ) {
//        UartInit(&Uart0, UART_0, UART0_TX, UART0_RX);
//        UartConfig(&Uart0, RX_ONLY, 4800, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY, NO_FLOW_CTRL);
    }
}

void GpsMcuInit( void )
{
    NmeaStringSize = 0;

    //FifoInit( &Uart0.FifoTx, TxBuffer, FIFO_TX_SIZE );
    FifoInit(&Uart0.FifoRx, RxBuffer, FIFO_RX_SIZE);
    Uart0.IrqNotify = GpsMcuIrqNotify;

    GpioInit(&GpsPps, PPS, PIN_INPUT, PIN_PUSH_PULL, PIN_NO_PULL, 1);
    GpioSetInterrupt(&GpsPps, IRQ_FALLING_EDGE, IRQ_VERY_LOW_PRIORITY,
            &GpsMcuOnPpsSignal);

    UartInit(&Uart0, UART_0, UART0_TX, UART0_RX);
    UartConfig(&Uart0, RX_ONLY, 4800, UART_8_BIT, UART_1_STOP_BIT, NO_PARITY,
            NO_FLOW_CTRL);
}

void GpsMcuIrqNotify( UartNotifyId_t id )
{
    uint8_t data;
    if ( id == UART_NOTIFY_RX ) {
        if ( UartGetChar(&Uart0, &data) == 0 ) {
            if ( (data == '$') || (NmeaStringSize >= 128) ) {
                NmeaStringSize = 0;
            }

            NmeaString[NmeaStringSize++] = (int8_t) data;

            if ( data == '\n' ) {
                NmeaString[NmeaStringSize] = '\0';
                LOG_TRACE_BARE("%s", NmeaString);
                GpsParseGpsData(NmeaString, NmeaStringSize);
//                UartDeInit (&Uart0);
                BlockLowPowerDuringTask(false);
            }
        }
    }
}
/*******************************************************************************
 * END OF CODE
 ******************************************************************************/
