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
#ifndef __FSL_GPIO_DRIVER_H__
#define __FSL_GPIO_DRIVER_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"

/*! 
 * @addtogroup gpio_driver
 * @{
 */

/*!
 * @file
 *
 * The GPIO driver uses the virtual GPIO name rather than an actual port and a pin number.
 * By using the virtual name, each pin name is self-explanatory.
 * To use the GPIO driver, an enumeration variable must be predefined in the user application files.
 * The variable  saves all GPIO pin information used in a project.
 *
 * This is an example to define the enumeration variable. 
   @code
   // This is the enum to define  virtual GPIO pin names.
   // These members will be used by "uint32_t pinName" in gpio_output_pin_user_config_t 
   // and gpio_input_pin_user_config_t. Usually defined in a header file.
   enum _gpio_pins 
   {
       kGpioLED1  = GPIO_MAKE_PIN(HW_GPIOA, 5), // Orange LED.
       kGpioLED2  = GPIO_MAKE_PIN(HW_GPIOA, 6), // Yellow LED.
       kGpioLED3  = GPIO_MAKE_PIN(HW_GPIOA, 7), // Breen LED.
       kGpioLED4  = GPIO_MAKE_PIN(HW_GPIOB, 8), // Red LED.
   };
   @endcode
 */ 

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! 
 * @name GPIO Pin Macros
 * @{
 */

/*! @brief Indicates the end of a pin configuration structure.*/
#define GPIO_PINS_OUT_OF_RANGE (0xFFFFFFFFU)

/*! @brief Bits shifted for the GPIO port number. */
#define GPIO_PORT_SHIFT (0x8U)

/*! @brief Combines the port number and the pin number into a single scalar value. */
#define GPIO_MAKE_PIN(r,p) (((r)<< GPIO_PORT_SHIFT) | (p))

/*! @brief Extracts the port number from a combined port and pin value.*/
#define GPIO_EXTRACT_PORT(v) (((v) >> GPIO_PORT_SHIFT) & 0xFFU)

/*! @brief Extracts the pin number from a combined port and pin value.*/
#define GPIO_EXTRACT_PIN(v) ((v) & 0xFFU)

/* @} */

/*!
 * @brief The GPIO input pin configuration structure.
 *
 * Although every pin is configurable, valid configurations
 * depend on a specific SoC. Users should check the related reference manual to
 * ensure that the specific feature is valid in an individual pin. A configuration of
 * unavailable features is harmless, but  takes no effect.
 */
typedef struct GpioInputPin {
    bool isPullEnable;                  /*!< Enable or disable pull. */
    port_pull_t pullSelect;             /*!< Select internal pull(up/down) resistor.*/
    bool isPassiveFilterEnabled;        /*!< Enable or disable passive filter.*/
    #if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
    /* Digital filter clock source and width should be pre-configured using the port HAL.*/
    bool isDigitalFilterEnabled;        /*!< Enable or disable digital filter.*/
    #endif
    port_interrupt_config_t interrupt;  /*!< Select interrupt/DMA request.*/
} gpio_input_pin_t;

/*!
 * @brief The GPIO output pin configuration structure.
 *
 * Although every pin is configurable, valid configurations
 * depend on a specific SoC. Users should check the related reference manual to
 * ensure that the specific feature is valid in an individual pin. The configuration of
 * unavailable features is harmless, but  takes no effect.
 */
typedef struct GpioOutputPin {
    uint32_t outputLogic;               /*!< Set default output logic.*/
    port_slew_rate_t slewRate;          /*! Select fast/slow slew rate.*/
    port_drive_strength_t driveStrength;/*!< Select low/high drive strength.*/
    #if FSL_FEATURE_PORT_HAS_OPEN_DRAIN
    bool isOpenDrainEnabled;            /*!< Enable or disable open drain.*/
    #endif
} gpio_output_pin_t;

/*!
 * @brief The GPIO input pin structure.
 *
 * Although the pinName is defined as a uint32_t type, values assigned to the pinName
 * should be the enumeration names defined in the enum _gpio_pins.
 */
typedef struct GpioInputPinUserConfig {
    uint32_t pinName;               /*!< Virtual pin name from enum defined by the user.*/
    gpio_input_pin_t config; /*!< Input pin configuration structure.*/
} gpio_input_pin_user_config_t;

/*!
 * @brief The GPIO output pin structure.
 *
 * Although the pinName is defined as a uint32_t type, values assigned to the pinName
 * should be the enumeration names defined in the enum _gpio_pins.
 */
typedef struct GpioOutputPinUserConfig {
    uint32_t pinName;               /*!< Virtual pin name from enum defined by the user.*/
    gpio_output_pin_t config;/*!< Input pin configuration structure.*/
} gpio_output_pin_user_config_t;

/*! @brief The GPIO ISR callback function*/
typedef void (*gpio_isr_callback_t)(void);

/*******************************************************************************
 * API
 ******************************************************************************/
 
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization 
 * @{
 */

/*!
 * @brief Initialize all GPIO pins used by board.
 *
 * To initialize the GPIO driver, define two arrays similar to the gpio_input_pin_user_config_t
 * inputPin[] and the gpio_output_pin_user_config_t outputPin[] in the user file.
 * Then, call the gpio_init() function and pass in the two arrays. If the input or output
 * pins are not needed, pass in a NULL.
 * 
 * This is an example to define an input pin array:
   @code
   // Configure the kGpioPTA2 as digital input.
   gpio_input_pin_user_config_t inputPin[] = {
     {
         .pinName = kGpioPTA2,
         .config.isPullEnable = false,
         .config.pullSelect = kPortPullDown,
         .config.isPassiveFilterEnabled = false,
         .config.interrupt = kPortIntDisabled,
     },
     {
        // Note: This pinName must be defined here to indicate the end of the array.
        .pinName = GPIO_PINS_OUT_OF_RANGE,
     }
   };
   @endcode
 *
 * @param inputPins input GPIO pins pointer.
 * @param outputPins output GPIO pins pointer.
 */
void gpio_init(const gpio_input_pin_user_config_t * inputPins, const gpio_output_pin_user_config_t * outputPins);

/*!
 * @brief Initializes one GPIO input pin used by board.
 *
 * @param inputPins input GPIO pins pointer.
 */
void gpio_input_pin_init(const gpio_input_pin_user_config_t *inputPin);

/*!
 * @brief Initializes one GPIO output pin used by board.
 *
 * @param outputPins output GPIO pins pointer.
 */
void gpio_output_pin_init(const gpio_output_pin_user_config_t *outputPin);

/* @} */

/*! 
 * @name Pin Direction
 * @{
 */

/*!
 * @brief Gets the current direction of the individual GPIO pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @return GPIO directions.
 *         - 0: corresponding pin is set as digital input.
 *         - 1: corresponding pin is set as digital output.
 */
uint32_t gpio_get_pin_direction(uint32_t pinName);

/*!
 * @brief Sets the current direction of the individual GPIO pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @param direction GPIO directions.
 *         - kGpioDigitalInput: corresponding pin is set as digital input.
 *         - kGpioDigitalOutput: corresponding pin is set as digital output.
 */

void gpio_set_pin_direction(uint32_t pinName, gpio_pin_direction_t direction);
/* @} */

/*!
 * @name Output Operations
 * @{
 */

/*!
 * @brief Sets the output level of the individual GPIO pin to the logic 1 or 0.
 * 
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @param output  pin output logic level.
 *        - 0: corresponding pin output low logic level.
 *        - Non-0: corresponding pin output high logic level.
 */
void gpio_write_pin_output(uint32_t pinName, uint32_t output);

/*!
 * @brief Sets the output level of the individual GPIO pin to the logic 1.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void gpio_set_pin_output(uint32_t pinName); 

/*!
 * @brief Sets the output level of the individual GPIO pin to the logic 0.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void gpio_clear_pin_output(uint32_t pinName); 

/*!
 * @brief Reverses current output logic of the individual GPIO pin.
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void gpio_toggle_pin_output(uint32_t pinName); 

/* @} */

/*!
 * @name Input Operations
 * @{
 */

/*!
 * @brief Reads the current input value of the individual GPIO pin.
 * 
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @return GPIO port input value.
 *         - 0: Pin logic level is 0, or is not configured for use by digital function.
 *         - 1: Pin logic level is 1.
 */
uint32_t gpio_read_pin_input(uint32_t pinName);

#if FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
/*!
 * @brief Enables or disables the digital filter in a single port.
 *
 * Each bit of the 32-bit register represents one pin.
 *  
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @param isDigitalFilterEnabled  digital filter enable/disable.
 *        - false: digital filter is disabled on the corresponding pin.
 *        - true : digital filter is enabled on the corresponding pin.
 */
void gpio_configure_digital_filter(uint32_t pinName, bool isDigitalFilterEnabled);
#endif

/* @} */

/*!
 * @name Interrupt
 * @{
 */

/*!
 * @brief Clears the individual GPIO pin interrupt status flag.
 * 
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 */
void gpio_clear_pin_interrupt_flag(uint32_t pinName);

/*!
 * @brief Registers the GPIO ISR callback function. 
 *
 * @param pinName GPIO pin name defined by the user in the GPIO pin enumeration list.
 * @param function Pointer to the GPIO ISR callback function.
 */
void gpio_register_isr_callback_function(uint32_t pinName, gpio_isr_callback_t function);

/* @} */

#if defined(__cplusplus)
}
#endif
 
/*! @} */
 
#endif /* __FSL_GPIO_DRIVER_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

