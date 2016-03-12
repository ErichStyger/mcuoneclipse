/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
#include "fsl_port.h"
#include "pin_mux.h"

#include "fsl_gpio.h" /* include SDK GPIO interface */

static const gpio_pin_config_t LED_configOutput = {
  kGPIO_DigitalOutput,  /* use as output pin */
  1,  /* initial value */
};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize all pins used in this example
 *
 * @param disablePortClockAfterInit disable port clock after pin
 * initialization or not.
 */

void BOARD_InitPins(void)
{
    /* Initialize LPUART0 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Affects PORTA_PCR1 register */
    PORT_SetPinMux(PORTA, 1u, kPORT_MuxAlt2);
    /* Affects PORTA_PCR2 register */
    PORT_SetPinMux(PORTA, 2u, kPORT_MuxAlt2);

    /* additional clock and configuration for RGB LEDs (PTA13, PTB18 and PTB19) */
    CLOCK_EnableClock(kCLOCK_PortB); /* enable clocks for port B */
    PORT_SetPinMux(PORTA, 13u, kPORT_MuxAsGpio); /* blue led, PTA13 */
    PORT_SetPinMux(PORTB, 18u, kPORT_MuxAsGpio); /* red led, PTB18 */
    PORT_SetPinMux(PORTB, 19u, kPORT_MuxAsGpio); /* green led, PTB19 */

    GPIO_PinInit(GPIOA, 13u, &LED_configOutput); /* mux PTA13 as output */
    GPIO_PinInit(GPIOB, 18u, &LED_configOutput); /* mux PTB18 as output */
    GPIO_PinInit(GPIOB, 19u, &LED_configOutput); /* mux PTB19 as output */
}
