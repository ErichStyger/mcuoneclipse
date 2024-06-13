/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "platform.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_BOARD_TEST_LED_PORT BOARD_LED_BLUE_GPIO_PORT
#define APP_BOARD_TEST_LED_PIN  BOARD_LED_BLUE_GPIO_PIN
#define APP_SW_PORT             BOARD_SW2_GPIO_PORT
#define APP_SW_PIN              BOARD_SW2_GPIO_PIN
#define APP_SW_STATE_RELEASED         0U
#define APP_SW_STATE_CONFIRM_PRESSED  1U
#define APP_SW_STATE_PRESSED          2U
#define APP_SW_STATE_CONFIRM_RELEASED 3U
#define APP_SW_FILTER_PERIOD          5

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;
uint8_t swState = APP_SW_STATE_RELEASED;
int8_t filter   = -1;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

/*!
 * @brief Main function
 */
int main(void) {
  PL_Init();

    uint32_t port_state = 0;

    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

    /* Board pin, clock, debug console init */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n The LED is taking turns to shine.\r\n");

    /* Init output LED GPIO. */
    GPIO_PortInit(GPIO, APP_BOARD_TEST_LED_PORT);
    GPIO_PortInit(GPIO, APP_SW_PORT);
    GPIO_PinInit(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, &led_config);
    GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, 1);

    /* Port masking */
    GPIO_PortMaskedSet(GPIO, APP_BOARD_TEST_LED_PORT, 0x0000FFFF);
    GPIO_PortMaskedWrite(GPIO, APP_BOARD_TEST_LED_PORT, 0xFFFFFFFF);
    port_state = GPIO_PortRead(GPIO, APP_BOARD_TEST_LED_PORT);
    PRINTF("\r\n Standard port read: %x\r\n", port_state);
    port_state = GPIO_PortMaskedRead(GPIO, APP_BOARD_TEST_LED_PORT);
    PRINTF("\r\n Masked port read: %x\r\n", port_state);

    /* Set systick reload value to generate 1ms interrupt */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    for(;;) {
      GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
      SysTick_DelayTicks(5*100U);
    }

    while (1)
    {
        port_state = GPIO_PortRead(GPIO, APP_SW_PORT);

        switch (swState)
        {
            case APP_SW_STATE_RELEASED:
                if (!(port_state & (1 << APP_SW_PIN)))
                {
                    swState = APP_SW_STATE_CONFIRM_PRESSED;
                    filter  = APP_SW_FILTER_PERIOD;
                }
                break;
            case APP_SW_STATE_CONFIRM_PRESSED:
                if (!(port_state & (1 << APP_SW_PIN)))
                {
                    if (filter == 0)
                    {
                        PRINTF("\r\n Port state: %x\r\n", port_state);
                        GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
                        swState = APP_SW_STATE_PRESSED;
                    }
                    else
                    {
                        filter--;
                    }
                }
                else
                {
                    swState = APP_SW_STATE_RELEASED;
                }
                break;
            case APP_SW_STATE_PRESSED:
                if ((port_state & (1 << APP_SW_PIN)))
                {
                    swState = APP_SW_STATE_CONFIRM_RELEASED;
                    filter  = APP_SW_FILTER_PERIOD;
                }
                break;
            case APP_SW_STATE_CONFIRM_RELEASED:
                if ((port_state & (1 << APP_SW_PIN)))
                {
                    if (filter == 0)
                    {
                        swState = APP_SW_STATE_RELEASED;
                    }
                    else
                    {
                        filter--;
                    }
                }
                else
                {
                    swState = APP_SW_STATE_PRESSED;
                }
                break;
            default:
                swState = APP_SW_STATE_RELEASED;
                break;
        }
        SysTick_DelayTicks(1U);
    }
}
