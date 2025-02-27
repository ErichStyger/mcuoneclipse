/*
 * usart.c
 *
 * Created on: 24 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include "usart.h"
#include "fsl_usart.h"
#include "pin_mux.h"
#include "fsl_clock.h"

#include "SEGGER_RTT.h"

static uint8_t enableUSARTOutput = 0;

void FLEXCOMM0_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
    if ((kUSART_RxFifoNotEmptyFlag | kUSART_RxError) & USART_GetStatusFlags(USART0))
    {
        data = USART_ReadByte(USART0);
        if (enableUSARTOutput)
        {
            if (data < 128)
            {
                SEGGER_printf(",B%d", data % 128);
            }
            else
            {
                SEGGER_printf(",E%d", data % 128);
            }
        }
    }
    SDK_ISR_EXIT_BARRIER;
}

void USART_setOutput(uint8_t val)
{
    if (val)
    {
        enableUSARTOutput = 1;
    }
    else
    {
        enableUSARTOutput = 0;
    }
}

void USART_setBaud(uint32_t baud)
{
    USART_SetBaudRate(USART0, baud, CLOCK_GetFlexCommClkFreq(0U));
}

void init_USART(void)
{
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUSART_ParityDisabled;
     * config.stopBitCount = kUSART_OneStopBit;
     * config.loopback = false;
     * config.enableTxFifo = false;
     * config.enableRxFifo = false;
     */
    usart_config_t config;
    USART_GetDefaultConfig(&config);
    config.baudRate_Bps = 9600;
    config.enableTx = true;
    config.enableRx = true;

    USART_Init(USART0, &config, CLOCK_GetFlexCommClkFreq(0U));

    /* Enable RX interrupt. */
    USART_EnableInterrupts(USART0, kUSART_RxLevelInterruptEnable | kUSART_RxErrorInterruptEnable);
    EnableIRQ(FLEXCOMM0_IRQn);
}
