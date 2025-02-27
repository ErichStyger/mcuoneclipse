/*
 * commandParser.c
 *
 * Created on: 31 May 2022
 *     Author: Peter Allenspach
 *     For HSLU T&A VM2 "Open Source MCU-Link Pro Energy Probe"
 */

#include <mytimer.h>
#include <stdio.h>
#include <string.h>
#include "SEGGER_RTT.h"
#include "commandParser.h"

#include "usart.h"
#include "lpadc.h"

#include "util.h"

static char rttCmdBuf[RTT_CMD_BUF_SIZE + 1]; // +1 to always have terminating \0

void init_commandParser(void)
{
    memset(rttCmdBuf, '\0', RTT_CMD_BUF_SIZE + 1); // +1 to always have terminating \0
}

static void commandParser_parseCommand(char *cmd, uint16_t cmd_size)
{
    if (0 == strncmp(cmd, "help", 4))
    {
        SEGGER_printf("Available Commands:\n"
                      "meas (start|stop) - starts or stops measurement\n"
                      "uart baud (9600|115200) - sets UART baud rate\n"
                      "uart (enable|disable) - enables or disables UART\n"
                      "calibrate - returns calibration values for low and high current mode\n"
                      "current (low|high) - sets to low or high current mode - low up to 2mA, high up to 400mA");
    }
    else if (0 == strncmp(cmd, "meas", 4))
    {
        if (0 == strncmp(cmd + 5, "start", 5))
        {
            SEGGER_printf("Start Measurement\n");
            MeasurementTimer_start();
        }
        if (0 == strncmp(cmd + 5, "stop", 4))
        {
            SEGGER_printf("Stop Measurement\n");
            MeasurementTimer_stop();
        }
    }
    else if (0 == strncmp(cmd, "uart", 4))
    {
        if (0 == strncmp(cmd + 5, "enable", 6))
        {
            SEGGER_printf("Enable UART output\n");
            USART_setOutput(1);
        }
        else if (0 == strncmp(cmd + 5, "disable", 7))
        {
            SEGGER_printf("Disable UART output\n");
            USART_setOutput(0);
        }
        else if (0 == strncmp(cmd + 5, "baud", 4))
        { // uart baud
            if (0 == strncmp(cmd + 10, "9600", 4))
            {
                SEGGER_printf("Set UART input to 9600 Baud\n");
                USART_setBaud(9600);
            }
            if (0 == strncmp(cmd + 10, "115200", 6))
            {
                SEGGER_printf("Set UART input to 115200 Baud\n");
                USART_setBaud(115200);
            }
        }
    }
    else if (0 == strncmp(cmd, "calibrate", 9))
    {
        SEGGER_printf("Generating calibration values, disconnecting DUT and disabling measurement\n");
        set_CalDisc(1);
        MeasurementTimer_stop();
        uint8_t high_flag = 0;
        for (uint8_t i = 0; i < 2; i++)
        {
            if (high_flag)
            {
                SEGGER_printf("High Power measurement values:\n"
                              "Max value 65535: 418.59mA");
                set_LowCurrent(0);
            }
            else
            {
                SEGGER_printf("Low Power measurement values:\n"
                              "Max value 65535: 2mA\n");
                set_LowCurrent(1);
                high_flag = 1;
            }

            set_CalRes(0b0000);
            SysTick_DelayTicks(10);
            LPADC_DoSoftwareTrigger(LPADC_BASE, 1U);
            SysTick_DelayTicks(10);
            SEGGER_printf("only bleed value, open (5uA): %d\n", get_LPADC0B_res());

            set_CalRes(0b0001);
            SysTick_DelayTicks(10);
            LPADC_DoSoftwareTrigger(LPADC_BASE, 1U);
            SysTick_DelayTicks(10);
            SEGGER_printf("R1 (6650 Ohm, 501uA @ 3.3V): %d\n", get_LPADC0B_res());

            set_CalRes(0b0010);
            SysTick_DelayTicks(10);
            LPADC_DoSoftwareTrigger(LPADC_BASE, 1U);
            SysTick_DelayTicks(10);
            SEGGER_printf("R2 (66.5 Ohm, 49.629mA @ 3.3V): %d\n", get_LPADC0B_res());

            set_CalRes(0b0100);
            SysTick_DelayTicks(10);
            LPADC_DoSoftwareTrigger(LPADC_BASE, 1U);
            SysTick_DelayTicks(10);
            SEGGER_printf("R3 (1650Ohm, 2.005mA @ 3.3V): %d\n", get_LPADC0B_res());

            set_CalRes(0b1000);
            SysTick_DelayTicks(10);
            LPADC_DoSoftwareTrigger(LPADC_BASE, 1U);
            SysTick_DelayTicks(10);
            SEGGER_printf("R4 (16.5 Ohm, 200mA @ 3.3V): %d\n", get_LPADC0B_res());
        }

        SEGGER_printf("Calibration done, reconnecting DUT, going to low current mode");
        set_CalRes(0b0000);
        set_LowCurrent(1);
        set_CalDisc(0);
    }
    else if (0 == strncmp(cmd, "current", 7))
    {
        if (0 == strncmp(cmd + 8, "high", 4))
        {
            SEGGER_printf("Current range set to high\n");
            set_LowCurrent(0);
        }
        else if (0 == strncmp(cmd + 8, "low", 3))
        {
            SEGGER_printf("Current range set to low\n");
            set_LowCurrent(1);
        }
    }
    else
    {
        SEGGER_printf("Command not recognized!\n");
    }
}

void commandParser_checkInputParse(void)
{
    if (SEGGER_RTT_HasData(0))
    {
        memset(rttCmdBuf, '\0', RTT_CMD_BUF_SIZE);
        SEGGER_RTT_Read(0, rttCmdBuf, RTT_CMD_BUF_SIZE);
        SEGGER_printf("\nCommand received: %s", rttCmdBuf);
        commandParser_parseCommand(rttCmdBuf, strlen(rttCmdBuf));
    }
}
