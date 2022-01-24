/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_GPIO_H_
#define _FSL_GPIO_H_

#include "fsl_common.h"

/*!
 * @addtogroup gpio
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief GPIO driver version. */
#define FSL_GPIO_DRIVER_VERSION (MAKE_VERSION(2, 1, 1))
/*@}*/

/*! @brief PORT definition */
typedef enum _gpio_port_num
{
    kGPIO_PORTA = 0U,
    kGPIO_PORTB,
    kGPIO_PORTC,
    kGPIO_PORTD,
    kGPIO_PORTE,
    kGPIO_PORTF,
    kGPIO_PORTG,
    kGPIO_PORTH,
#if FSL_FEATURE_SOC_GPIO_COUNT > 2
    kGPIO_PORTI,
#endif
} gpio_port_num_t;

/*! @brief GPIO direction definition */
typedef enum _gpio_pin_direction
{
    kGPIO_DigitalInput  = 0U, /*!< Set current pin as digital input*/
    kGPIO_DigitalOutput = 1U, /*!< Set current pin as digital output*/
} gpio_pin_direction_t;

/*!
 * @brief The GPIO pin configuration structure.
 *
 * Each pin can only be configured as either an output pin or an input pin at a time.
 * If configured as an input pin, leave the outputConfig unused.
 * Note that in some use cases, the corresponding port property should be configured in advance
 *        with the PORT_SetPinConfig().
 */
typedef struct _gpio_pin_config
{
    gpio_pin_direction_t pinDirection; /*!< GPIO direction, input or output */
    /* Output configurations; ignore if configured as an input pin */
    uint8_t outputLogic; /*!< Set a default output logic, which has no use in input */
} gpio_pin_config_t;

/*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup gpio_driver
 * @{
 */

/*! @name GPIO Configuration */
/*@{*/

/*!
 * @brief Initializes a GPIO pin used by the board.
 *
 * To initialize the GPIO, define a pin configuration, as either input or output, in the user file.
 * Then, call the GPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration.
 * @code
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
 * @endcode
 *
 * @param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param pin    GPIO port pin number
 * @param config GPIO pin configuration pointer
 */
void GPIO_PinInit(gpio_port_num_t port, uint8_t pin, const gpio_pin_config_t *config);

/*@}*/

/*! @name GPIO Output Operations */
/*@{*/

/*!
 * @brief Sets the output level of the multiple GPIO pins to the logic 1 or 0.
 *
 * @param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param pin     GPIO pin number
 * @param output  GPIO pin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
void GPIO_PinWrite(gpio_port_num_t port, uint8_t pin, uint8_t output);

/*!
 * @brief Sets the output level of the multiple GPIO pins to the logic 1.
 *
 * @param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param mask GPIO pin number macro
 */
void GPIO_PortSet(gpio_port_num_t port, uint8_t mask);

/*!
 * @brief Sets the output level of the multiple GPIO pins to the logic 0.
 *
 * @param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param mask GPIO pin number macro
 */
void GPIO_PortClear(gpio_port_num_t port, uint8_t mask);

/*!
 * @brief Reverses the current output logic of the multiple GPIO pins.
 *
 * @param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param mask GPIO pin number macro
 */
void GPIO_PortToggle(gpio_port_num_t port, uint8_t mask);
/*@}*/

/*! @name GPIO Input Operations */
/*@{*/

/*!
 * @brief Reads the current input value of the GPIO port.
 *
 * @param port   GPIO PORT number, see "gpio_port_num_t".
 *  For each group GPIO (GPIOA, GPIOB,etc) control registers, they handles four PORT number controls.
 *  GPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  GPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param pin     GPIO pin number
 * @retval GPIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
uint32_t GPIO_PinRead(gpio_port_num_t port, uint8_t pin);

/*@}*/

/*@}*/

/*!
 * @addtogroup fgpio_driver
 * @{
 */

/*
 * Introduces the FGPIO feature.
 *
 * The FGPIO features are only support on some Kinetis MCUs. The FGPIO registers are aliased to the IOPORT
 * interface. Accesses via the IOPORT interface occur in parallel with any instruction fetches and
 * complete in a single cycle. This aliased Fast GPIO memory map is called FGPIO.
 */

#if defined(FSL_FEATURE_SOC_FGPIO_COUNT) && FSL_FEATURE_SOC_FGPIO_COUNT

/*! @name FGPIO Configuration */
/*@{*/

/*!
 * @brief Initializes the FGPIO peripheral.
 *
 * This function ungates the FGPIO clock.
 *
 * @param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 */
void FGPIO_PortInit(gpio_port_num_t port);

/*!
 * @brief Initializes a FGPIO pin used by the board.
 *
 * To initialize the FGPIO driver, define a pin configuration, as either input or output, in the user file.
 * Then, call the FGPIO_PinInit() function.
 *
 * This is an example to define an input pin or an output pin configuration:
 * @code
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
 * @endcode
 *
 * @param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param pin    FGPIO port pin number
 * @param config FGPIO pin configuration pointer
 */
void FGPIO_PinInit(gpio_port_num_t port, uint8_t pin, const gpio_pin_config_t *config);

/*@}*/

/*! @name FGPIO Output Operations */
/*@{*/

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 1 or 0.
 *
 * @param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param pin     FGPIO pin number
 * @param output  FGPIOpin output logic level.
 *        - 0: corresponding pin output low-logic level.
 *        - 1: corresponding pin output high-logic level.
 */
void FGPIO_PinWrite(gpio_port_num_t port, uint8_t pin, uint8_t output);

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 1.
 *
 * @param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param mask FGPIO pin number macro
 */
void FGPIO_PortSet(gpio_port_num_t port, uint8_t mask);

/*!
 * @brief Sets the output level of the multiple FGPIO pins to the logic 0.
 *
 * @param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param mask FGPIO pin number macro
 */
void FGPIO_PortClear(gpio_port_num_t port, uint8_t mask);

/*!
 * @brief Reverses the current output logic of the multiple FGPIO pins.
 *
 * @param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param mask FGPIO pin number macro
 */
void FGPIO_PortToggle(gpio_port_num_t port, uint8_t mask);

/*@}*/

/*! @name FGPIO Input Operations */
/*@{*/

/*!
 * @brief Reads the current input value of the FGPIO port.
 *
 * @param port   FGPIO PORT number, see "gpio_port_num_t".
 *  For each group FGPIO (FGPIOA, FGPIOB,etc) control registers, they handles four PORT number controls.
 *  FGPIOA serial registers ----- PTA 0 ~ 7, PTB 0 ~7 ... PTD 0 ~ 7.
 *  FGPIOB serial registers ----- PTE 0 ~ 7, PTF 0 ~7 ... PTH 0 ~ 7.
 *   ...
 * @param pin  FGPIO pin number
 * @retval FGPIO port input value
 *        - 0: corresponding pin input low-logic level.
 *        - 1: corresponding pin input high-logic level.
 */
uint32_t FGPIO_PinRead(gpio_port_num_t port, uint8_t pin);

/*@}*/

#endif /* FSL_FEATURE_SOC_FGPIO_COUNT */

/*@}*/

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif /* _FSL_GPIO_H_*/
