/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PINS_GPIO_HW_ACCESS_H
#define PINS_GPIO_HW_ACCESS_H

#include "pins_driver.h"

/*! @file */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Local macro not referenced.
 * The defined macro is used as include guard.
 *
 */

/*!
 * pins_gpio_hw_access
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name GPIO
 * General GPIO functions.
 */
/*! @{*/

#if defined(FEATURE_PINS_DRIVER_USING_PORT)
/*!
 * @brief Get the pins directions configuration for a port
 *
 * This function returns the current pins directions for a port. Pins
 * corresponding to bits with value of '1' are configured as output and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO directions. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
static inline pins_channel_type_t PINS_GPIO_GetPinsDirection(const GPIO_Type * const base)
{
    return (pins_channel_type_t)base->PDDR;
}

/*!
 * @brief Configure the direction for a certain pin from a port
 *
 * This function configures the direction for the given pin, with the
 * given value('1' for pin to be configured as output and '0' for pin to
 * be configured as input)
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pin the pin number for which to configure the direction
 * @param direction the pin direction:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
static inline void PINS_GPIO_SetPinDirection(GPIO_Type * const base,
                                             pins_channel_type_t pin,
                                             pins_level_type_t direction)
{
    pins_channel_type_t pinsDirections = (pins_channel_type_t)base->PDDR;
    pinsDirections &= (pins_channel_type_t)(~((pins_channel_type_t)1U << pin));
    pinsDirections |= (pins_channel_type_t)((pins_channel_type_t)direction << pin);
    base->PDDR = GPIO_PDDR_PDD(pinsDirections);
}

/*!
 * @brief Set the pins directions configuration for a port
 *
 * This function sets the direction configuration for all pins
 * in a port. Pins corresponding to bits with value of '1' will be configured as
 * output and pins corresponding to bits with value of '0' will be configured as
 * input.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pins pin mask where each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is set to output
 */
static inline void PINS_GPIO_SetPinsDirection(GPIO_Type * const base,
                                              pins_channel_type_t pins)
{
    base->PDDR = GPIO_PDDR_PDD(pins);
}

#if FEATURE_PORT_HAS_INPUT_DISABLE
/*!
 * @brief Set the pins input disable state for a port
 *
 * This function sets the pins input state for a port.
 * Pins corresponding to bits with value of '1' will not be configured
 * as input and pins corresponding to bits with value of '0' will be configured
 * as input.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pins pin mask where each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
static inline void PINS_GPIO_SetPortInputDisable(GPIO_Type * const base,
                                                 pins_channel_type_t pins)
{
    base->PIDR = GPIO_PIDR_PID(pins);
}

/*!
 * @brief Get the pins input disable state for a port
 *
 * This function returns the current pins input state for a port. Pins
 * corresponding to bits with value of '1' are not configured as input and
 * pins corresponding to bits with value of '0' are configured as input.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO input state. Each bit represents one pin (LSB is pin 0, MSB is
 * pin 31). For each bit:
 *        - 0: corresponding pin is set to input
 *        - 1: corresponding pin is not set to input
 */
static inline pins_channel_type_t PINS_GPIO_GetPortInputDisable(const GPIO_Type * const base)
{
    return (pins_channel_type_t)base->PIDR;
}
#endif /* FEATURE_PORT_HAS_INPUT_DISABLE */

#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
/* Reverse bit order in each halfword independently */
static inline uint16_t REV_BIT_16(uint16_t value)
{
    uint8_t i;
    uint16_t ret = 0U;

    for (i = 0U; i < 8U; i++)
    {
        ret |= (uint16_t)((((value >> i) & 1U) << (15U - i)) | (((value << i) & 0x8000U) >> (15U - i)));
    }

    return ret;
}

#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */

/*!
 * @brief Write a pin of a port with a given value
 *
 * This function writes the given pin from a port, with the given value
 * ('0' represents LOW, '1' represents HIGH).
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pin pin number to be written
 * @param value pin value to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
static inline void PINS_GPIO_WritePin(GPIO_Type * const base,
                                      pins_channel_type_t pin,
                                      pins_level_type_t value)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    pins_channel_type_t pinsValues = (pins_channel_type_t)base->PDOR;
    pinsValues &= (pins_channel_type_t)(~((pins_channel_type_t)1U << pin));
    pinsValues |= (pins_channel_type_t)((pins_channel_type_t)value << pin);
    base->PDOR = GPIO_PDOR_PDO(pinsValues);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    pins_channel_type_t pinsValues = (pins_channel_type_t)base->PGPDO;
    pinsValues &= (pins_channel_type_t)(~((pins_channel_type_t)1U << (15U - pin)));
    pinsValues |= (pins_channel_type_t)((pins_channel_type_t)value << (15U - pin));
    base->PGPDO = pinsValues;
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */
}

/*!
 * @brief Write all pins of a port
 *
 * This function writes all pins configured as output with the values given in
 * the parameter pins. '0' represents LOW, '1' represents HIGH.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pins pin mask to be written
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
static inline void PINS_GPIO_WritePins(GPIO_Type * const base,
                                       pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PDOR = GPIO_PDOR_PDO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO = REV_BIT_16(pins);
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */
}

/*!
 * @brief Get the current output from a port
 *
 * This function returns the current output that is written to a port. Only pins
 * that are configured as output will have meaningful values.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO outputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is set to LOW
 *        - 1: corresponding pin is set to HIGH
 */
static inline pins_channel_type_t PINS_GPIO_GetPinsOutput(const GPIO_Type * const base)
{
    pins_channel_type_t returnValue = 0U;

#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    returnValue = (pins_channel_type_t)(base->PDOR);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    returnValue = (pins_channel_type_t)REV_BIT_16(base->PGPDO);
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */

    return returnValue;
}

/*!
 * @brief Write pins with 'Set' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a value of 'set' (HIGH). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pins pin mask of bits to be set.  Each bit represents one pin (LSB is
 * pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is set to HIGH
 */
static inline void PINS_GPIO_SetPins(GPIO_Type * const base,
                                     pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PSOR = GPIO_PSOR_PTSO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO |= REV_BIT_16(pins);
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */
}

/*!
 * @brief Write pins to 'Clear' value
 *
 * This function configures output pins listed in parameter pins (bits that are
 * '1') to have a 'cleared' value (LOW). Pins corresponding to '0' will be
 * unaffected.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pins pin mask of bits to be cleared.  Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is cleared(set to LOW)
 */
static inline void PINS_GPIO_ClearPins(GPIO_Type * const base,
                                       pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PCOR = GPIO_PCOR_PTCO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO &= (pins_channel_type_t)(~REV_BIT_16(pins));
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */
}

/*!
 * @brief Toggle pins value
 *
 * This function toggles output pins listed in parameter pins (bits that are
 * '1'). Pins corresponding to '0' will be unaffected.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @param pins pin mask of bits to be toggled.  Each bit represents one pin (LSB
 * is pin 0, MSB is pin 31). For each bit:
 *        - 0: corresponding pin is unaffected
 *        - 1: corresponding pin is toggled
 */
static inline void PINS_GPIO_TogglePins(GPIO_Type * const base,
                                        pins_channel_type_t pins)
{
#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    base->PTOR = GPIO_PTOR_PTTO(pins);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    base->PGPDO ^= REV_BIT_16(pins);
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */
}

/*!
 * @brief Read input pins
 *
 * This function returns the current input values from a port. Only pins
 * configured as input will have meaningful values.
 *
 * @param base  GPIO base pointer (PTA, PTB, PTC, etc.)
 * @return GPIO inputs. Each bit represents one pin (LSB is pin 0, MSB is pin
 * 31). For each bit:
 *        - 0: corresponding pin is read as LOW
 *        - 1: corresponding pin is read as HIGH
 */
static inline pins_channel_type_t PINS_GPIO_ReadPins(const GPIO_Type * const base)
{
    pins_channel_type_t returnValue = 0U;

#if defined(FEATURE_PINS_DRIVER_USING_PORT)
    returnValue = (pins_channel_type_t)(base->PDIR);
#elif defined(FEATURE_PINS_DRIVER_USING_SIUL2)
    returnValue = (pins_channel_type_t)REV_BIT_16(base->PGPDI);
#endif /* if defined(FEATURE_PINS_DRIVER_USING_PORT) */

    return returnValue;
}

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* PINS_GPIO_HW_ACCESS_H*/
/*******************************************************************************
 * EOF
 ******************************************************************************/
