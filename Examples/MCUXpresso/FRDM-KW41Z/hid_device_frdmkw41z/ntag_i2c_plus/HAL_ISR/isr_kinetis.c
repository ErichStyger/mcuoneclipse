/*
 * Copyright (c) 2016, NXP Semiconductor
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
 * o Neither the name of NXP Semiconductor nor the names of its
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
 *
 */
/***********************************************************************/
/* INCLUDES                                                            */
/***********************************************************************/
#include "board.h"
#include "fsl_port.h"
#include "HAL_timer_driver.h"
#include "isr_driver_intern.h"
/***********************************************************************/
/* DEFINES                                                             */
/***********************************************************************/

/***********************************************************************/
/* GLOBAL VARIABLES                                                    */
/***********************************************************************/
/***********************************************************************/
/* LOCAL FUNCTION PROTOTYPES                                           */
/***********************************************************************/
/***********************************************************************/
/* GLOBAL FUNCTIONS                                                    */
/***********************************************************************/

void HAL_ISR_Init()
{
    size_t i = 0;

    for (i = 0; i < ISR_MAX_CALLBACKS; i++)
    {
        SELECT_CALLBACK(i);

        /* disable interrupt */
        DISABLE_INTERRUPT();

        /* setup interrupt mode */
        setupMode(EXT_INT_FD_PORT, callback->pin_func, callback->mode);
    }
}

void setupMode(void *port, uint32_t pin, ISR_MODE_T mode)
{
    switch (mode)
    {
        case ISR_LEVEL_HI:
            PORT_SetPinInterruptConfig(port, pin, kPORT_InterruptLogicOne);
            break;
        case ISR_LEVEL_LO:
            PORT_SetPinInterruptConfig(port, pin, kPORT_InterruptLogicZero);
            break;
        case ISR_EDGE_RISE:
            PORT_SetPinInterruptConfig(port, pin, kPORT_InterruptRisingEdge);
            break;
        case ISR_EDGE_FALL:
            PORT_SetPinInterruptConfig(port, pin, kPORT_InterruptFallingEdge);
            break;
        default:
            break;
    }
}

void disableInterrupt(uint32_t channel)
{
    NVIC_DisableIRQ(GPIO_PININT_NVIC(channel));
}

void enableInterrupt(uint32_t channel)
{
    /* Enable interrupt in the NVIC */
    NVIC_ClearPendingIRQ(GPIO_PININT_NVIC(channel));
    NVIC_EnableIRQ(GPIO_PININT_NVIC(channel));
}

/***********************************************************************/
/* LOCAL FUNCTIONS                                                     */
/***********************************************************************/
/***********************************************************************/
/* INTERUPT SERVICE ROUTINES                                           */
/***********************************************************************/
void PORTA_IRQHandler(void)
{
    SELECT_CALLBACK(0);
    CHECK_VALID_AND_CALL_HANDLER();
    WAKEUP_TASKS();
    DISABLE_INTERRUPT();
}
void PORTB_IRQHandler(void)
{
    SELECT_CALLBACK(0);
    CHECK_VALID_AND_CALL_HANDLER();
    WAKEUP_TASKS();
    DISABLE_INTERRUPT();
}
void PORTB_PORTC_IRQHandler(void)
{
    SELECT_CALLBACK(0);
    CHECK_VALID_AND_CALL_HANDLER();
    WAKEUP_TASKS();
    DISABLE_INTERRUPT();
}
void PORTC_IRQHandler(void)
{
    SELECT_CALLBACK(0);
    CHECK_VALID_AND_CALL_HANDLER();
    WAKEUP_TASKS();
    DISABLE_INTERRUPT();
}
void PORTD_IRQHandler(void)
{
    SELECT_CALLBACK(0);
    CHECK_VALID_AND_CALL_HANDLER();
    WAKEUP_TASKS();
    DISABLE_INTERRUPT();
}
void PORTB_PORTC_PORTD_PORTE_IRQHandler(void)
{
    SELECT_CALLBACK(0);
    CHECK_VALID_AND_CALL_HANDLER();
    WAKEUP_TASKS();
    DISABLE_INTERRUPT();
}
void PORTC_PORTD_IRQHandler(void)
{
    SELECT_CALLBACK(0);
    CHECK_VALID_AND_CALL_HANDLER();
    WAKEUP_TASKS();
    DISABLE_INTERRUPT();
}
