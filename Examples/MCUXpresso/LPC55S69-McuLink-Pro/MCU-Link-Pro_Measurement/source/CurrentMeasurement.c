
/*
 * commandParser.h
 *
 * Created on: 15 Feb 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

/**
 * @file    CurrentMeasurement.c
 * @brief   Application entry point.
 */
#include <mytimer.h>
#include <stdio.h>
#include "IncludeMcuLibConfig.h"

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "lpadc.h"
#include "util.h"
#include "usart.h"

#include "commandParser.h"
#include "fsl_lpadc.h"
#include "fsl_inputmux.h"
#include "fsl_ctimer.h"
#include "fsl_power.h"
/* TODO: insert other definitions and declarations here. */

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

/*
 * @brief   Application entry point.
 */

int main(void)
{

    /* Init board hardware. */

    POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    /* Turn off clock to inputmux to save power (and possibly increase accuracy of measurements). Clock is only needed to make changes */
    INPUTMUX_Deinit(INPUTMUX);
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    // enable cycle counter
    MCU_InitCycleCounter();   /* enable DWT hardware */
    MCU_ResetCycleCounter();  /* reset cycle counter */
    MCU_EnableCycleCounter(); /* start counting */

    init_MeasurementTimer();
    init_USART();

    // init_trigger_command_timer();

    // enable pin interrupt
    // enable_PinInterrupt();

    set_CalDisc(1);
    init_LPADC0B();
    SEGGER_printf("Current Measurement\n"
                  "-------------------\n"
                  "Default Settings:\n"
                  "Current measurement range: LOW\n"
                  "Calibration Resistors: DISCONNECTED\n"
                  "Device Under Test: CONNECTED\n"
                  "Measurement Timer: STOPPED\n"
                  "UART: DISABLED\n"
                  "Send \"help\" in RTT terminal to see available commands\n"
                  "Note: Always send lines! Input -> Sending -> Send on Enter\n");

    set_CalR1(0);
    set_CalDisc(0);
    set_LowCurrent(0);
    init_commandParser();
    while (1)
    {
        SysTick_DelayTicks(10U);
        // CTIMER_StartTimer(CTIMER1);
        commandParser_checkInputParse();
    }
    return 0;
}
