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
 
#include "fsl_gpio_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
extern IRQn_Type gpio_irq_ids[HW_PORT_INSTANCE_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_init
 * Description   : Initialize all GPIO pins used by board.
 * To initialize the GPIO driver, two arrays similar with gpio_input_pin_user_config_t
 * inputPin[] and gpio_output_pin_user_config_t outputPin[] should be defined in user's file.
 * Then simply call gpio_init() and pass into these two arrays. If input or output
 * pins are not needed, pass in a NULL.  
 *
 *END**************************************************************************/
void gpio_init(const gpio_input_pin_user_config_t * inputPins, const gpio_output_pin_user_config_t * outputPins)
{
    if (inputPins)
    {
        /* Initialize input pins.*/
        while (inputPins->pinName != GPIO_PINS_OUT_OF_RANGE)
        {
            gpio_input_pin_init(inputPins++);
        }
    }

    if (outputPins)
    {
        /* Initialize output pins.*/
        while (outputPins->pinName != GPIO_PINS_OUT_OF_RANGE)
        {
            gpio_output_pin_init(outputPins++);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_input_pin_init
 * Description   : Initialize one GPIO input pin used by board.
 *
 *END**************************************************************************/
void gpio_input_pin_init(const gpio_input_pin_user_config_t *inputPin)
{
    /* Get actual port and pin number.*/
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(inputPin->pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(inputPin->pinName);

    /* Un-gate port clock*/
    clock_manager_set_gate(kClockModulePORT, gpioInstance, true);

    /* Set current pin as digital input.*/
    gpio_hal_set_pin_direction(gpioInstance, pin, kGpioDigitalInput);

    /* Configure GPIO input features. */
    port_hal_configure_pull(gpioInstance, pin, inputPin->config.isPullEnable);
    port_hal_pull_select(gpioInstance, pin, inputPin->config.pullSelect);
    port_hal_configure_passive_filter(gpioInstance, pin,
            inputPin->config.isPassiveFilterEnabled);
    #if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
    port_hal_configure_digital_filter(gpioInstance, pin, 
            inputPin->config.isDigitalFilterEnabled); 
    #endif
    port_hal_configure_pin_interrupt(gpioInstance, pin, inputPin->config.interrupt);

    /* Configure NVIC */
    if ((inputPin->config.interrupt) && (gpio_irq_ids[gpioInstance]))
    {
        /* Enable GPIO interrupt.*/
        interrupt_enable(gpio_irq_ids[gpioInstance]);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_output_pin_init
 * Description   : Initialize one GPIO output pin used by board.
 *
 *END**************************************************************************/
void gpio_output_pin_init(const gpio_output_pin_user_config_t *outputPin)
{
    /* Get actual port and pin number.*/
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(outputPin->pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(outputPin->pinName);

    /* Un-gate port clock*/
    clock_manager_set_gate(kClockModulePORT, gpioInstance, true);

    /* Set current pin as digital output.*/
    gpio_hal_set_pin_direction(gpioInstance, pin, kGpioDigitalOutput);

    /* Configure GPIO output features. */
    gpio_hal_write_pin_output(gpioInstance, pin, outputPin->config.outputLogic);
    port_hal_configure_slew_rate(gpioInstance, pin, outputPin->config.slewRate);
    port_hal_configure_drive_strength(gpioInstance, pin, outputPin->config.driveStrength);
    #if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
    port_hal_configure_open_drain(gpioInstance, pin, outputPin->config.isOpenDrainEnabled);
    #endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_get_pin_direction
 * Description   : Get current direction of individual GPIO pin.
 *
 *END**************************************************************************/
uint32_t gpio_get_pin_direction(uint32_t pinName)
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    return gpio_hal_get_pin_direction(gpioInstance, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_set_pin_direction
 * Description   : Set current direction of individual GPIO pin.
 *
 *END**************************************************************************/
void gpio_set_pin_direction(uint32_t pinName, gpio_pin_direction_t direction)
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    gpio_hal_set_pin_direction(gpioInstance, pin, direction);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_write_pin_output
 * Description   : Set output level of individual GPIO pin to logic 1 or 0.
 *
 *END**************************************************************************/
void gpio_write_pin_output(uint32_t pinName, uint32_t output)
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    gpio_hal_write_pin_output(gpioInstance, pin, output);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_set_pin_output
 * Description   : Set output level of individual GPIO pin to logic 1.
 *
 *END**************************************************************************/
void gpio_set_pin_output(uint32_t pinName) 
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);

    gpio_hal_set_pin_output(gpioInstance, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_clear_pin_output
 * Description   : Set output level of individual GPIO pin to logic 0.
 *
 *END**************************************************************************/
void gpio_clear_pin_output(uint32_t pinName) 
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);
   
    gpio_hal_clear_pin_output(gpioInstance, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_toggle_pin_output
 * Description   : Reverse current output logic of individual GPIO pin.
 *
 *END**************************************************************************/
void gpio_toggle_pin_output(uint32_t pinName) 
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);
 
    gpio_hal_toggle_pin_output(gpioInstance, pin);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_read_pin_input
 * Description   : Read current input value of individual GPIO pin.
 *
 *END**************************************************************************/
uint32_t gpio_read_pin_input(uint32_t pinName)
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);
    
    return gpio_hal_read_pin_input(gpioInstance, pin);
}

#if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_configure_digital_filter
 * Description   : Enable or disable digital filter in one single port.
 *
 *END**************************************************************************/
void gpio_configure_digital_filter(uint32_t pinName, bool isDigitalFilterEnabled)
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);
 
    port_hal_configure_digital_filter(gpioInstance, pin, isDigitalFilterEnabled);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : gpio_clear_pin_interrupt_flag
 * Description   : Clear individual GPIO pin interrupt status flag.
 *
 *END**************************************************************************/
void gpio_clear_pin_interrupt_flag(uint32_t pinName)
{
    uint32_t gpioInstance = GPIO_EXTRACT_PORT(pinName);
    uint32_t pin = GPIO_EXTRACT_PIN(pinName);
 
    port_hal_clear_pin_interrupt_flag(gpioInstance, pin);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

