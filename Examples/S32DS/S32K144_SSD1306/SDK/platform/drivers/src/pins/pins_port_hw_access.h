/*
 * Copyright 2017 NXP
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

#ifndef PINS_PORT_HW_ACCESS_H
#define PINS_PORT_HW_ACCESS_H

#include "pins_driver.h"

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 10.3, The value of an expression
 * shall not be assigned to an object with a narrower essential type or of a
 * different essential type category.
 * The cast is required to perform a conversion between an unsigned integer
 * and an enum type with many values.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 10.5, Impermissible cast; cannot cast from
 * 'essentially unsigned' type to 'essentially enum<i>'.
 * This is required by the conversion of a bit-field of a register into a enum type.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 10.5, Impermissible cast; cannot cast from
 * 'essentially unsigned' type to 'essentially Boolean'.
 * This is required by the conversion of a bit into a bool type.
 *
 */

/*!
 * @defgroup port_hal Port Control and Interrupts (PORT)
 * @ingroup pins_driver
 * @brief This module covers the functionality of the PORT peripheral.
 * <p>
 *  PORT HAL provides the API for reading and writing register bit-fields belonging to the PORT module.
 * </p>
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * given structure.
 *
 * @param[in] config the configuration structure
 * @return the status of the operation
 */
status_t PINS_Init(const pin_settings_config_t * config);

#if FEATURE_PINS_HAS_PULL_SELECTION
/*!
 * @brief Configures the internal resistor.
 *
 * Pull configuration is valid in all digital pin muxing modes.
 *
 * @param[in] base        port base pointer.
 * @param[in] pin         port pin number
 * @param[in] pullConfig  internal resistor pull feature selection
 *        - PORT_PULL_NOT_ENABLED: internal pull-down or pull-up resistor is not enabled.
 *        - PORT_PULL_DOWN_ENABLED: internal pull-down resistor is enabled.
 *        - PORT_PULL_UP_ENABLED: internal pull-up resistor is enabled.
 */
static inline void PINS_SetPullSel(PORT_Type * const base,
                                   uint32_t pin,
                                   port_pull_config_t pullConfig)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    switch (pullConfig)
    {
        case PORT_INTERNAL_PULL_NOT_ENABLED:
            {
                base->PCR[pin] &= ~(PORT_PCR_PE_MASK);
            }
            break;
        case PORT_INTERNAL_PULL_DOWN_ENABLED:
            {
                uint32_t regValue = base->PCR[pin];
                regValue &= ~(PORT_PCR_PS_MASK);
                regValue |= PORT_PCR_PE(1U);
                base->PCR[pin] = regValue;
            }
            break;
        case PORT_INTERNAL_PULL_UP_ENABLED:
            {
                uint32_t regValue = base->PCR[pin];
                regValue |= PORT_PCR_PE(1U);
                regValue |= PORT_PCR_PS(1U);
                base->PCR[pin] = regValue;
            }
            break;
        default:
            /* invalid command */
            DEV_ASSERT(false);
            break;
    }
}

#endif /* if FEATURE_PINS_HAS_PULL_SELECTION */

/*!
 * @brief Configures the pin muxing.
 *
 * @param[in] base  port base pointer
 * @param[in] pin  port pin number
 * @param[in] mux  pin muxing slot selection
 *        - PORT_PIN_DISABLED: Pin disabled.
 *        - PORT_MUX_AS_GPIO  : Set as GPIO.
 *        - others          : chip-specific.
 */
static inline void PINS_SetMuxModeSel(PORT_Type * const base,
                                      uint32_t pin,
                                      port_mux_t mux)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue &= ~(PORT_PCR_MUX_MASK);
    regValue |= PORT_PCR_MUX(mux);
    base->PCR[pin] = regValue;
}

/*@}*/

/*!
 * @name Interrupt
 * @{
 */

/*!
 * @brief Configures the port pin interrupt/DMA request.
 *
 * @param[in] base       port base pointer.
 * @param[in] pin        port pin number
 * @param[in] intConfig  interrupt configuration
 *        - PORT_INT_DISABLED     : Interrupt/DMA request disabled.
 *        - PORT_DMA_RISING_EDGE  : DMA request on rising edge.
 *        - PORT_DMA_FALLING_EDGE : DMA request on falling edge.
 *        - PORT_DMA_EITHER_EDGE  : DMA request on either edge.
 *        - PORT_FLAG_RISING_EDGE : Flag sets on rising edge only.
 *        - PORT_FLAG_FALLING_EDGE: Flag sets on falling edge only.
 *        - PORT_FLAG_EITHER_EDGE : Flag sets on either edge only.
 *        - PORT_INT_LOGIC_ZERO   : Interrupt when logic zero.
 *        - PORT_INT_RISING_EDGE  : Interrupt on rising edge.
 *        - PORT_INT_FALLING_EDGE : Interrupt on falling edge.
 *        - PORT_INT_EITHER_EDGE  : Interrupt on either edge.
 *        - PORT_INT_LOGIC_ONE    : Interrupt when logic one.
 *        - PORT_HIGH_TRIGGER_OUT : Enable active high trigger output, flag is disabled.
 *        - PORT_LOW_TRIGGER_OUT  : Enable active low trigger output, flag is disabled.
 */
static inline void PINS_SetPinIntSel(PORT_Type * const base,
                                     uint32_t pin,
                                     port_interrupt_config_t intConfig)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue &= ~(PORT_PCR_IRQC_MASK);
    regValue |= PORT_PCR_IRQC(intConfig);
    base->PCR[pin] = regValue;
}

/*!
 * @brief Gets the current port pin interrupt/DMA request configuration.
 *
 * @param[in] base  port base pointer
 * @param[in] pin   port pin number
 * @return  interrupt configuration
 *        - PORT_INT_DISABLED     : Interrupt/DMA request disabled.
 *        - PORT_DMA_RISING_EDGE  : DMA request on rising edge.
 *        - PORT_DMA_FALLING_EDGE : DMA request on falling edge.
 *        - PORT_DMA_EITHER_EDGE  : DMA request on either edge.
 *        - PORT_FLAG_RISING_EDGE : Flag sets on rising edge only.
 *        - PORT_FLAG_FALLING_EDGE: Flag sets on falling edge only.
 *        - PORT_FLAG_EITHER_EDGE : Flag sets on either edge only.
 *        - PORT_INT_LOGIC_ZERO   : Interrupt when logic zero.
 *        - PORT_INT_RISING_EDGE  : Interrupt on rising edge.
 *        - PORT_INT_FALLING_EDGE : Interrupt on falling edge.
 *        - PORT_INT_EITHER_EDGE  : Interrupt on either edge.
 *        - PORT_INT_LOGIC_ONE    : Interrupt when logic one.
 *        - PORT_HIGH_TRIGGER_OUT : Enable active high trigger output, flag is disabled.
 *        - PORT_LOW_TRIGGER_OUT  : Enable active low trigger output, flag is disabled.
 */
static inline port_interrupt_config_t PINS_GetPinIntSel(const PORT_Type * const base,
                                                        uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue = (regValue & PORT_PCR_IRQC_MASK) >> PORT_PCR_IRQC_SHIFT;

    return (port_interrupt_config_t)regValue;
}

/*!
 * @brief Clears the individual pin-interrupt status flag.
 *
 * @param[in] base  port base pointer
 * @param[in] pin   port pin number
 */
static inline void PINS_ClearPinIntFlagCmd(PORT_Type * const base,
                                           uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    uint32_t regValue = base->PCR[pin];
    regValue &= ~(PORT_PCR_ISF_MASK);
    regValue |= PORT_PCR_ISF(1U);
    base->PCR[pin] = regValue;
}

/*!
 * @brief Enables digital filter for digital pin muxing
 *
 * @param[in] base  port base pointer
 * @param[in] pin   port pin number
 */
static inline void PINS_EnableDigitalFilter(PORT_Type * const base,
                                            uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    base->DFER |= (uint32_t)1U << pin;
}

/*!
 * @brief Disables digital filter for digital pin muxing
 *
 * @param[in] base  port base pointer
 * @param[in] pin   port pin number
 */
static inline void PINS_DisableDigitalFilter(PORT_Type * const base,
                                             uint32_t pin)
{
    DEV_ASSERT(pin < PORT_PCR_COUNT);
    base->DFER &= ~((uint32_t)1U << pin);
}

/*!
 * @brief Configures digital filter clock for port with given configuration
 *
 * @param[in] base   port base pointer
 * @param[in] config configuration struct
 */
static inline void PINS_ConfigDigitalFilter(PORT_Type * const base,
                                            const port_digital_filter_config_t * const config)
{
    DEV_ASSERT(config->width <= PORT_DFWR_FILT_MASK);
    base->DFCR = PORT_DFCR_CS(config->clock);
    base->DFWR = PORT_DFWR_FILT(config->width);
}

/*!
 * @brief Reads the entire port interrupt status flag.
 *
 * @param[in] base  port base pointer
 * @return all 32 pin interrupt status flags. For specific bit:
 *         - 0: interrupt is not detected.
 *         - 1: interrupt is detected.
 */
static inline uint32_t PINS_GetPortIntFlag(const PORT_Type * const base)
{
    uint32_t regValue = base->ISFR;

    return regValue;
}

/*!
 * @brief Clears the entire port interrupt status flag.
 *
 * @param[in] base  port base pointer
 */
static inline void PINS_ClearPortIntFlagCmd(PORT_Type * const base)
{
    base->ISFR = PORT_ISFR_ISF_MASK;
}

/*!
 * @brief Quickly configures multiple pins with the same pin configuration.
 *
 * @param[in] base  port base pointer
 * @param[in] pins  pin mask where each bit represents one pin
 * @param[in] value the config value will be updated for the pins are set to '1'
 * @param[in] halfPort the lower or upper half of pin registers at the same port
 */
void PINS_SetGlobalPinControl(PORT_Type * const base,
                              uint16_t pins,
                              uint16_t value,
                              port_global_control_pins_t halfPort);

/*!
 * @brief Quickly configures multiple pins with the same interrupt configuration.
 *
 * @param[in] base  port base pointer
 * @param[in] pins  pin mask where each bit represents one pin
 * @param[in] value the config value will be updated for the pins are set to '1'
 * @param[in] halfPort the lower or upper half of pin registers at the same port
 */
void PINS_SetGlobalIntControl(PORT_Type * const base,
                              uint16_t pins,
                              uint16_t value,
                              port_global_control_pins_t halfPort);


#if FEATURE_PINS_HAS_OVER_CURRENT
/*!
 * @brief Reads the entire over current port interrupt status flag.
 *
 * @param[in] base  port base pointer
 * @return all 32 pin interrupt status flags. For specific bit:
 *         - 0: interrupt is not detected.
 *         - 1: interrupt is detected.
 */
static inline uint32_t PINS_GetOverCurPortIntFlag(const PORT_Type * const base)
{

    return (uint32_t)(base->OCFR);
}

/*!
 * @brief Clears the entire over current port interrupt status flag.
 *
 * @param[in] base  port base pointer
 */
static inline void PINS_ClearOverCurPortIntFlag(PORT_Type * const base)
{
    base->ISFR = PORT_ISFR_OCFR_MASK;
}
#endif /* FEATURE_PINS_HAS_OVER_CURRENT */

/*! @} */

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* PINS_PORT_HW_ACCESS_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
