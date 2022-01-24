/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.gpio_1"
#endif

#define PORT_NUMBERS_EACH_GPIO (4U)
#define PIN_NUMBERS_EACH_PORT  (8UL)
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_SOC_GPIO_COUNT) && FSL_FEATURE_SOC_GPIO_COUNT
static GPIO_Type *const s_gpioBases[] = GPIO_BASE_PTRS;
#endif

#if defined(FSL_FEATURE_SOC_FGPIO_COUNT) && FSL_FEATURE_SOC_FGPIO_COUNT
static FGPIO_Type *const s_fgpioBases[] = FGPIO_BASE_PTRS;
#if defined(FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL) && FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Array to map FGPIO instance number to clock name. */
static const clock_ip_name_t s_fgpioClockName[] = FGPIO_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#endif /* FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL */

#endif /* FSL_FEATURE_SOC_FGPIO_COUNT */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Initializes a GPIO pin used by the board.
 *
 * To initialize the GPIO, define a pin configuration, as either input or output, in the user file.
 * Then, call the GPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration.
 * code
 * Define a digital input pin configuration,
 * gpio_pin_config_t config =
 * {
 *   kGPIO_DigitalInput,
 *   0,
 * }
 * Define a digital output pin configuration,
 * gpio_pin_config_t config =
 * {
 *   kGPIO_DigitalOutput,
 *   0,
 * }
 * endcode
 *
 * param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param pin    GPIO port pin number
 * param config GPIO pin configuration pointer
 */
void GPIO_PinInit(gpio_port_num_t port, uint8_t pin, const gpio_pin_config_t *config)
{
    assert(config);

    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    GPIO_Type *base  = s_gpioBases[instance];

    if (config->pinDirection == kGPIO_DigitalInput)
    {
        base->PDDR &= ~(1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT)));
        base->PIDR &= ~(1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT)));
    }
    else
    {
        GPIO_PinWrite(port, pin, config->outputLogic);
        base->PDDR |= (1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT)));
        base->PIDR |= (1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT)));
    }
}

/*!
 * brief Sets the output level of the multiple GPIO pins to the logic 1 or 0.
 *
 * param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param pin     GPIO pin number
 * param output  GPIO pin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
void GPIO_PinWrite(gpio_port_num_t port, uint8_t pin, uint8_t output)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    GPIO_Type *base  = s_gpioBases[instance];

    if (output == 0U)
    {
        base->PCOR = 1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT));
    }
    else
    {
        base->PSOR = 1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT));
    }
}

/*!
 * brief Sets the output level of the multiple GPIO pins to the logic 1.
 *
 * param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param mask GPIO pin number macro
 */
void GPIO_PortSet(gpio_port_num_t port, uint8_t mask)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    GPIO_Type *base  = s_gpioBases[instance];

    base->PSOR = ((uint32_t)mask << (shift * PIN_NUMBERS_EACH_PORT));
}

/*!
 * brief Sets the output level of the multiple GPIO pins to the logic 0.
 *
 * param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param mask GPIO pin number macro
 */
void GPIO_PortClear(gpio_port_num_t port, uint8_t mask)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    GPIO_Type *base  = s_gpioBases[instance];

    base->PCOR = ((uint32_t)mask << (shift * PIN_NUMBERS_EACH_PORT));
}

/*!
 * brief Reverses the current output logic of the multiple GPIO pins.
 *
 * param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param mask GPIO pin number macro
 */
void GPIO_PortToggle(gpio_port_num_t port, uint8_t mask)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    GPIO_Type *base  = s_gpioBases[instance];

    base->PTOR = ((uint32_t)mask << (shift * PIN_NUMBERS_EACH_PORT));
}

/*!
 * brief Reads the current input value of the GPIO port.
 *
 * param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param pin     GPIO pin number
 * retval GPIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
uint32_t GPIO_PinRead(gpio_port_num_t port, uint8_t pin)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    GPIO_Type *base  = s_gpioBases[instance];

    return (((base->PDIR) >> ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT))) & 0x01UL);
}

#if defined(FSL_FEATURE_SOC_FGPIO_COUNT) && FSL_FEATURE_SOC_FGPIO_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Enable the FGPIO clock.
 *
 * @param port FGPIO PORT number.
 */
static void FGPIO_EnableClock(gpio_port_num_t port);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void FGPIO_EnableClock(gpio_port_num_t port)
{
#if defined(FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL) && FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    FGPIO_Type *base = s_fgpioBases[instance];

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Ungate FGPIO periphral clock */
    CLOCK_EnableClock(s_fgpioClockName[FGPIO_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
#endif /* FSL_FEATURE_PCC_HAS_FGPIO_CLOCK_GATE_CONTROL */
}

void FGPIO_PortInit(gpio_port_num_t port)
{
    FGPIO_EnableClock(port);
}

/*!
 * brief Initializes a FGPIO pin used by the board.
 *
 * To initialize the FGPIO driver, define a pin configuration, as either input or output, in the user file.
 * Then, call the FGPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration:
 * code
 * Define a digital input pin configuration,
 * gpio_pin_config_t config =
 * {
 *   kGPIO_DigitalInput,
 *   0,
 * }
 * Define a digital output pin configuration,
 * gpio_pin_config_t config =
 * {
 *   kGPIO_DigitalOutput,
 *   0,
 * }
 * endcode
 *
 * param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param pin    FGPIO port pin number
 * param config FGPIO pin configuration pointer
 */
void FGPIO_PinInit(gpio_port_num_t port, uint8_t pin, const gpio_pin_config_t *config)
{
    assert(config);

    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    FGPIO_Type *base = s_fgpioBases[instance];

    FGPIO_EnableClock(port);

    if (config->pinDirection == kGPIO_DigitalInput)
    {
        base->PDDR &= ~(1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT)));
    }
    else
    {
        FGPIO_PinWrite(port, pin, config->outputLogic);
        base->PDDR |= (1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT)));
    }
}

/*!
 * brief Sets the output level of the multiple FGPIO pins to the logic 1 or 0.
 *
 * param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param pin     FGPIO pin number
 * param output  FGPIOpin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
void FGPIO_PinWrite(gpio_port_num_t port, uint8_t pin, uint8_t output)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    FGPIO_Type *base = s_fgpioBases[instance];

    if (output == 0U)
    {
        base->PCOR = 1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT));
    }
    else
    {
        base->PSOR = 1UL << ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT));
    }
}

/*!
 * brief Sets the output level of the multiple FGPIO pins to the logic 1.
 *
 * param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param mask FGPIO pin number macro
 */
void FGPIO_PortSet(gpio_port_num_t port, uint8_t mask)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    FGPIO_Type *base = s_fgpioBases[instance];

    base->PSOR = ((uint32_t)mask << (shift * PIN_NUMBERS_EACH_PORT));
}

/*!
 * brief Sets the output level of the multiple FGPIO pins to the logic 0.
 *
 * param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param mask FGPIO pin number macro
 */
void FGPIO_PortClear(gpio_port_num_t port, uint8_t mask)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    FGPIO_Type *base = s_fgpioBases[instance];

    base->PCOR = ((uint32_t)mask << (shift * PIN_NUMBERS_EACH_PORT));
}

/*!
 * brief Reverses the current output logic of the multiple FGPIO pins.
 *
 * param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param mask FGPIO pin number macro
 */
void FGPIO_PortToggle(gpio_port_num_t port, uint8_t mask)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    FGPIO_Type *base = s_fgpioBases[instance];

    base->PTOR = ((uint32_t)mask << (shift * PIN_NUMBERS_EACH_PORT));
}

/*!
 * brief Reads the current input value of the FGPIO port.
 *
 * param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * param pin  FGPIO pin number
 * retval FGPIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
uint32_t FGPIO_PinRead(gpio_port_num_t port, uint8_t pin)
{
    uint8_t instance = (uint8_t)port / PORT_NUMBERS_EACH_GPIO;
    uint8_t shift    = (uint8_t)port % PORT_NUMBERS_EACH_GPIO;
    FGPIO_Type *base = s_fgpioBases[instance];

    return (((base->PDIR) >> ((uint32_t)pin + (shift * PIN_NUMBERS_EACH_PORT))) & 0x01UL);
}

#endif /* FSL_FEATURE_SOC_FGPIO_COUNT */
