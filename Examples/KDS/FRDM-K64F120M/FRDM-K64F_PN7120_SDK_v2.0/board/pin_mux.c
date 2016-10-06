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
#include "board.h" /* << EST added */

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
#if 1 /* NXP RFID */
    /* Declare and initialize for pull up configuration */
    port_pin_config_t pinConfig = {0};

#if 0 /* internal pull-up on I2C as workaround: do *not* use this for real! */
    pinConfig.pullSelect = kPORT_PullUp;
#if defined(FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && FSL_FEATURE_PORT_HAS_OPEN_DRAIN
    pinConfig.openDrainEnable = kPORT_OpenDrainEnable;
#endif /* FSL_FEATURE_PORT_HAS_OPEN_DRAIN */
#endif
#endif

    /* Initialize UART1 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Affects PORTB_PCR16 register */
    PORT_SetPinMux(PORTB, 16u, kPORT_MuxAlt3);
    /* Affects PORTB_PCR17 register */
    PORT_SetPinMux(PORTB, 17u, kPORT_MuxAlt3);

#if 1 /* NXP RFID */
    /* Initialize I2C0 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortE);
    /* I2C0 pull up resistor setting */
    PORT_SetPinConfig(PORTE, 24U, &pinConfig);
    PORT_SetPinConfig(PORTE, 25U, &pinConfig);
    /* I2C0 PIN_MUX Configuration */
    PORT_SetPinMux(PORTE, 24U, kPORT_MuxAlt5);
    PORT_SetPinMux(PORTE, 25U, kPORT_MuxAlt5);

    /* Initialize NXPNCI GPIO pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* IRQ and VEN PIN_MUX Configuration */
    PORT_SetPinMux(NXPNCI_IRQ_PORT, NXPNCI_IRQ_PIN, kPORT_MuxAsGpio);
    PORT_SetPinMux(NXPNCI_VEN_PORT, NXPNCI_VEN_PIN, kPORT_MuxAsGpio);
    /* IRQ interrupt Configuration */
    NVIC_SetPriority(NXPNCI_IRQ_PORTIRQn, 5);
    EnableIRQ(NXPNCI_IRQ_PORTIRQn);
    PORT_SetPinInterruptConfig(NXPNCI_IRQ_PORT, NXPNCI_IRQ_PIN, kPORT_InterruptRisingEdge);
#endif
}
