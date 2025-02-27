/*
 * triggerReader.c
 *
 * Created on: 23 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

/* This file currently has no use
 * It is a relic of trying to implement an UART-like soft-interface
 * This would have been the command processing logic
 * to be used in the MCU-Link Pro Device
 */

#include "triggerReader.h"
#include "fsl_pint.h"
#include "util.h"

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

static trigger_reader_t triggerState = TRIGGER_READY;
static uint8_t triggerPosition = 0;

void pint_IRQCallback(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    uint32_t time = MCU_GetCycleCounter() / 150000;
    SEGGER_printf("\r\nPINT Pin Interrupt %d event at time %d ms detected.", pintr, time);
}

void enable_PinInterrupt(void)
{
    /* Initialize PINT */
    PINT_Init(PINT);
    /* Setup Pin Interrupt 0 for rising edge */
    PINT_PinInterruptConfig(PINT, kPINT_PinInt0, kPINT_PinIntEnableRiseEdge, pint_IRQCallback);
    /* Enable callbacks for PINT0 by Index */
    PINT_EnableCallbackByIndex(PINT, kPINT_PinInt0);
}

void read_TriggerCallback(void)
{
    switch (triggerState)
    {
    case TRIGGER_READY:
        // record trigger start
        triggerState = TRIGGER_PROCESSING;
        break;
    case TRIGGER_PROCESSING:
        if (triggerPosition++ < 8)
        {
        }
        else
        {
            triggerState = TRIGGER_DONE;
        }
        // process trigger data
        break;
    case TRIGGER_DONE:
        // output trigger data
        triggerState = TRIGGER_READY;
        break;
    default:
        break;
    }
}
