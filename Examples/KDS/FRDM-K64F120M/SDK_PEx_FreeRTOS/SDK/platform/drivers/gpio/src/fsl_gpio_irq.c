/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
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
 
#include <assert.h>
#include "fsl_gpio_driver.h"

/*!
 * @addtogroup gpio_irq
 * @{
 */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined (KL25Z4_SERIES)
/*!
 * @brief Table to save gpio IRQ enum numbers defined in CMSIS files. They are
 *  used by gpio_init to enable or disable gpio interrupts. 
 */
const IRQn_Type gpio_irq_ids[HW_PORT_INSTANCE_COUNT] = 
{
    PORTA_IRQn, NULL, NULL, PORTD_IRQn, NULL
};
#elif defined (K64F12_SERIES) || defined (K70F12_SERIES) || defined (K22F51212_SERIES)
const IRQn_Type gpio_irq_ids[HW_PORT_INSTANCE_COUNT] = 
{
    PORTA_IRQn, PORTB_IRQn, PORTC_IRQn, PORTD_IRQn, PORTE_IRQn,
#if defined (K70F12_SERIES) 
    PORTF_IRQn
#endif
};
#endif

/*!
 * @brief Function table to save gpio isr callback function pointers. Call
 * gpio_register_isr_callback_function to install isr callback functions.
 */
gpio_isr_callback_t gpio_isr_callback_table[HW_PORT_INSTANCE_COUNT] = {NULL};

/*******************************************************************************
 * Code
 ******************************************************************************/
#if defined (KL25Z4_SERIES) || defined (K64F12_SERIES) ||\
    defined (K70F12_SERIES) || defined (K22F51212_SERIES)
/*! 
 * @brief gpio IRQ handler with the same name in startup code
 */
void PORTA_IRQHandler(void)
{
    /* Run callback function if it exists.*/
    if (gpio_isr_callback_table[HW_PORTA])
    {
        (*gpio_isr_callback_table[HW_PORTA])();
    }
    
    /* Clear interrupt flag.*/
    port_hal_clear_port_interrupt_flag(HW_PORTA);
}

/*! 
 * @brief gpio IRQ handler with the same name in startup code
 */
void PORTD_IRQHandler(void)
{
    /* Run callback function if it exists.*/
    if (gpio_isr_callback_table[HW_PORTD])
    {
        (*gpio_isr_callback_table[HW_PORTD])();
    }

    /* Clear interrupt flag.*/
    port_hal_clear_port_interrupt_flag(HW_PORTD);
}

#if defined (K64F12_SERIES) || defined (K22F51212_SERIES) || defined (K70F12_SERIES)

/*! 
 * @brief gpio IRQ handler with the same name in startup code
 */
void PORTB_IRQHandler(void)
{
    /* Run callback function if it exists.*/
    if (gpio_isr_callback_table[HW_PORTB])
    {
        (*gpio_isr_callback_table[HW_PORTB])();
    }

    /* Clear interrupt flag.*/
    port_hal_clear_port_interrupt_flag(HW_PORTB);
}

/*! 
 * @brief gpio IRQ handler with the same name in startup code
 */
void PORTC_IRQHandler(void)
{
    /* Run callback function if it exists.*/
    if (gpio_isr_callback_table[HW_PORTC])
    {
        (*gpio_isr_callback_table[HW_PORTC])();
    }

    /* Clear interrupt flag.*/
    port_hal_clear_port_interrupt_flag(HW_PORTC);
}

/*! 
 * @brief gpio IRQ handler with the same name in startup code
 */
void PORTE_IRQHandler(void)
{
    /* Run callback function if it exists.*/
    if (gpio_isr_callback_table[HW_PORTE])
    {
        (*gpio_isr_callback_table[HW_PORTE])();
    }

    /* Clear interrupt flag.*/
    port_hal_clear_port_interrupt_flag(HW_PORTE);
}

#if defined (K70F12_SERIES)
/*! 
 * @brief gpio IRQ handler with the same name in startup code
 */
void PORTF_IRQHandler(void)
{
    /* Run callback function if it exists.*/
    if (gpio_isr_callback_table[HW_PORTF])
    {
        (*gpio_isr_callback_table[HW_PORTF])();
    }

    /* Clear interrupt flag.*/
    port_hal_clear_port_interrupt_flag(HW_PORTF);
}
#endif

#endif

#endif

/*! @} */

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_register_isr_callback_function 
 * Description   : Register gpio isr callback function. 
 *
 *END**************************************************************************/
void gpio_register_isr_callback_function(uint32_t pinName, gpio_isr_callback_t function)
{
    assert(function != NULL);
    
    uint32_t gpioInstance = pinName >> GPIO_PORT_SHIFT;  
    gpio_isr_callback_table[gpioInstance] = function;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

