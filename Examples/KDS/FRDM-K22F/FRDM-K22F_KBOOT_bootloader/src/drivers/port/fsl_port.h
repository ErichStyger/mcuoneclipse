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
 * DISCLAIMED. IN NO EVENT SDRVL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _FSL_PORT_H_
#define _FSL_PORT_H_

#include "fsl_common.h"

/*!
 * @addtogroup port_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*!< Version 2.0.0. */
#define FSL_PORT_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))

/*! @brief Internal resistor pull feature selection */
enum _port_pull
{
    kPORT_PullDisable = 0U, /*!< internal pull-up/down resistor is disabled. */
    kPORT_PullDown = 2U,    /*!< internal pull-down resistor is enabled. */
    kPORT_PullUp = 3U,      /*!< internal pull-up resistor is enabled. */
};

/*! @brief Slew rate selection */
enum _port_slew_rate
{
    kPORT_FastSlewRate = 0U, /*!< fast slew rate is configured. */
    kPORT_SlowSlewRate = 1U, /*!< slow slew rate is configured. */
};

#if defined(FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && FSL_FEATURE_PORT_HAS_OPEN_DRAIN
/*! @brief Internal resistor pull feature enable/disable */
enum _port_open_drain_enable
{
    kPORT_OpenDrainDisable = 0U, /*!< internal pull-down resistor is disabled. */
    kPORT_OpenDrainEnable = 1U,  /*!< internal pull-up resistor is enabled. */
};
#endif /* FSL_FEATURE_PORT_HAS_OPEN_DRAIN */

/*! @brief Passive filter feature enable/disable */
enum _port_passive_filter_enable
{
    kPORT_PassiveFilterDisable = 0U, /*!< fast slew rate is configured. */
    kPORT_PassiveFilterEnable = 1U,  /*!< slow slew rate is configured. */
};

/*! @brief Configures the drive strength.*/
enum _port_drive_strength
{
    kPORT_LowDriveStrength = 0U,  /*!< low drive strength is configured. */
    kPORT_HighDriveStrength = 1U, /*!< high drive strength is configured. */
};

#if defined(FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK) && FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK
/*! @brief unlock/lock the pin control register field[15:0] */
enum _port_lock_register
{
    kPORT_UnLockRegister = 0U, /*!< Pin Control Register fields [15:0] are not locked. */
    kPORT_LockRegister = 1U,   /*!< Pin Control Register fields [15:0] are locked. */
};
#endif /* FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK */

/*! @brief Pin mux selection*/
typedef enum _port_mux
{
    kPORT_PinDisabledOrAnalog = 0U, /*!< corresponding pin is disabled, but is used as an analog pin.*/
    kPORT_MuxAsGpio = 1U,           /*!< corresponding pin is configured as GPIO.*/
    kPORT_MuxAlt2 = 2U,             /*!< chip-specific*/
    kPORT_MuxAlt3 = 3U,             /*!< chip-specific*/
    kPORT_MuxAlt4 = 4U,             /*!< chip-specific*/
    kPORT_MuxAlt5 = 5U,             /*!< chip-specific*/
    kPORT_MuxAlt6 = 6U,             /*!< chip-specific*/
    kPORT_MuxAlt7 = 7U,             /*!< chip-specific*/
} port_mux_t;

/*! @brief Configures the interrupt generation condition.*/
typedef enum _port_interrupt
{
    kPORT_InterruptOrDMADisabled = 0x0U, /*!< Interrupt/DMA request is disabled.*/
#if defined(FSL_FEATURE_PORT_HAS_DMA_REQUEST) && FSL_FEATURE_PORT_HAS_DMA_REQUEST
    kPORT_DmaRisingEdge = 0x1U,  /*!< DMA request on rising edge.*/
    kPORT_DmaFallingEdge = 0x2U, /*!< DMA request on falling edge.*/
    kPORT_DmaEitherEdge = 0x3U,  /*!< DMA request on either edge.*/
#endif
    kPORT_InterruptLogicZero = 0x8U,            /*!< Interrupt when logic zero. */
    kPORT_InterruptRisingEdge = 0x9U,           /*!< Interrupt on rising edge. */
    kPORT_InterruptFallingEdge = 0xAU,          /*!< Interrupt on falling edge. */
    kPORT_InterruptEitherEdge = 0xBU,           /*!< Interrupt on either edge. */
    kPORT_InterruptLogicOne = 0xCU,             /*!< Interrupt when logic one. */
    kPORT_ActiveHighTriggerOutputEnable = 0xDU, /*!< Enable active high trigger output. */
    kPORT_ActiveLowTriggerOutputEnable = 0xEU,  /*!< Enable active low trigger output. */
} port_interrupt_t;

#if defined(FSL_FEATURE_PORT_HAS_DIGITAL_FILTER) && FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
/*! @brief Digital filter clock source selection*/
typedef enum _port_digital_filter_clock_source
{
    kPORT_BusClock = 0U, /*!< Digital filters are clocked by the bus clock.*/
    kPORT_LpoClock = 1U, /*!< Digital filters are clocked by the 1 kHz LPO clock.*/
} port_digital_filter_clock_source_t;

/*! @brief PORT digital filter feature configuration definition*/
typedef struct _port_digital_filter_config
{
    uint32_t digitalFilterWidth;                    /*!< Set digital filter width */
    port_digital_filter_clock_source_t clockSource; /*!< Set digital filter clockSource */
} port_digital_filter_config_t;
#endif /* FSL_FEATURE_PORT_HAS_DIGITAL_FILTER */

/*! @brief PORT pin config structure */
typedef struct _port_pin_config
{
    uint16_t pullSelect : 2; /*!< no-pull/pull-down/pull-up select */
    uint16_t slewRate : 1;   /*!< fast/slow slew rate Configure */
    uint16_t : 1;
    uint16_t passiveFilterEnable : 1; /*!< passive filter enable/disable */
#if defined(FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && FSL_FEATURE_PORT_HAS_OPEN_DRAIN
    uint16_t openDrainEnable : 1; /*!< open drain enable/disable */
#else
    uint16_t : 1;
#endif                          /* FSL_FEATURE_PORT_HAS_OPEN_DRAIN */
    uint16_t driveStrength : 1; /*!< fast/slow drive strength configure */
    uint16_t : 1;
    uint16_t mux : 3; /*!< pin mux Configure */
    uint16_t : 4;
#if defined(FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK) && FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK
    uint16_t lockRegister : 1; /*!< lock/unlock the pcr field[15:0] */
#else
    uint16_t : 1;
#endif /* FSL_FEATURE_PORT_HAS_PIN_CONTROL_LOCK */
} port_pin_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @name Configuration */
/*@{*/

/*!
 * @brief Sets the port PCR register.
 *
 * This is an example to define an input pin or output pin PCR configuration:
 * @code
 * // Define a digital input pin PCR configuration
 * port_pin_config_t config = {
 *      kPORT_PullUp,
 *      kPORT_FastSlewRate,
 *      kPORT_PassiveFilterDisable,
 *      kPORT_OpenDrainDisable,
 *      kPORT_LowDriveStrength,
 *      kPORT_MuxAsGpio,
 *      kPORT_UnLockRegister,
 * };
 * @endcode
 *
 * @param base   PORT peripheral base pointer.
 * @param pin    PORT pin number.
 * @param config PORT PCR register configure structure.
 */
static inline void PORT_SetPinConfig(PORT_Type *base, uint32_t pin, const port_pin_config_t *config)
{
    assert(config);
    uint32_t addr = (uint32_t)&base->PCR[pin];
    *(volatile uint16_t *)(addr) = *((const uint16_t *)config);
}

/*!
 * @brief Sets the port PCR register.
 *
 * This is an example to define an input pin or output pin PCR configuration:
 * @code
 * // Define a digital input pin PCR configuration
 * port_pin_config_t config = {
 *      kPORT_PullUp ,
 *      kPORT_PullEnable,
 *      kPORT_FastSlewRate,
 *      0,
 *      kPORT_PassiveFilterDisable,
 *      kPORT_OpenDrainDisable,
 *      kPORT_LowDriveStrength,
 *      0,
 *      kPORT_MuxAsGpio,
 *      0,
 *      kPORT_UnLockRegister,
 * };
 * @endcode
 *
 * @param base   PORT peripheral base pointer.
 * @param mask    PORT pin mask.
 * @param config PORT PCR register configure structure.
 */
static inline void PORT_SetMultiplePinsConfig(PORT_Type *base, uint32_t mask, const port_pin_config_t *config)
{
    assert(config);

    uint16_t PCRL = *((const uint16_t *)config);

    if (mask & 0xffffU)
    {
        base->GPCLR = (mask & 0xffffU) | PCRL;
    }
    if (mask >> 16)
    {
        base->GPCHR = (mask >> 16) | PCRL;
    }
}

/*!
 * @brief Configures the pin muxing.
 *
 * @param base  PORT peripheral base pointer.
 * @param pin   PORT pin number.
 * @param mux   pin muxing slot selection.
 *        - kPORT_PinDisabledOrAnalog: Pin disabled or work in analog function.
 *        - kPORT_MuxAsGpio          : Set as GPIO.
 *        - others                : chip-specific.
 *
 * Note : This function is NOT recommended to use together with the PORT_SetPinsConfig, because
 *        the PORT_SetPinsConfig need to configure the pin mux anyway(Otherwise the pin mux will
 *        be reset to zero : kPORT_PinDisabledOrAnalog).
 *        This function is recommended to use in the case you just need to reset the pin mux
 */
static inline void PORT_SetPinMux(PORT_Type *base, uint32_t pin, port_mux_t mux)
{
    base->PCR[pin] = (base->PCR[pin] & ~PORT_PCR_MUX_MASK) | PORT_PCR_MUX(mux);
}

#if defined(FSL_FEATURE_PORT_HAS_DIGITAL_FILTER) && FSL_FEATURE_PORT_HAS_DIGITAL_FILTER
/*!
 * @brief Enables the digital filter in one port.
 *        Each bit of the 32-bit register represents one pin.
 *
 * @param base  PORT peripheral base pointer.
 * @param mask  PORT pins' numbers macro.
 */
static inline void PORT_EnablePinsDigitalFilter(PORT_Type *base, uint32_t mask, bool enable)
{
    if (enable == true)
    {
        base->DFER |= mask;
    }
    else
    {
        base->DFER &= ~mask;
    }
}

/*!
 * @brief set the digital filter in one port.
 *        Each bit of the 32-bit register represents one pin.
 *
 * @param base   PORT peripheral base pointer.
 * @param config PORT digital filter configuration structure.
 */
static inline void PORT_SetDigitalFilterConfig(PORT_Type *base, const port_digital_filter_config_t *config)
{
    assert(config);

    base->DFCR = PORT_DFCR_CS(config->clockSource);
    base->DFWR = PORT_DFWR_FILT(config->digitalFilterWidth);
}

#endif /* FSL_FEATURE_PORT_HAS_DIGITAL_FILTER */

/*@}*/

/*! @name Interrupt */
/*@{*/

/*!
 * @brief Configures the port pin interrupt/DMA request.
 *
 * @param base    PORT peripheral base pointer.
 * @param pin     PORT pin number.
 * @param config  PORT pin interrupt configuration.
 *        - kPORT_InterruptOrDMADisabled: Interrupt/DMA request disabled.
 *        - kPORT_DmaRisingEdge : DMA request on rising edge.
 *        - kPORT_DmaFallingEdge: DMA request on falling edge.
 *        - kPORT_DmaEitherEdge : DMA request on either edge.
 *        - kPORT_InterruptLogicZero  : Interrupt when logic zero.
 *        - kPORT_InterruptRisingEdge : Interrupt on rising edge.
 *        - kPORT_InterruptFallingEdge: Interrupt on falling edge.
 *        - kPORT_InterruptEitherEdge : Interrupt on either edge.
 *        - kPORT_InterruptLogicOne   : Interrupt when logic one.
 *        - kPORT_ActiveHighTriggerOutputEnable : Enable active high trigger output.
 *        - kPORT_ActiveLowTriggerOutputEnable  : Enable active low trigger output.
 */
static inline void PORT_SetPinInterruptConfig(PORT_Type *base, uint32_t pin, const port_interrupt_t config)
{
    base->PCR[pin] = (base->PCR[pin] & ~PORT_PCR_IRQC_MASK) | PORT_PCR_IRQC(config);
}

/*!
 * @brief Reads the whole port status flag.
 *
 * If a pin is configured to generate the DMA request,  the corresponding flag
 * is cleared automatically at the completion of the requested DMA transfer.
 * Otherwise, the flag remains set until a logic one is written to that flag.
 * If configured for a level sensitive interrupt that remains asserted, the flag
 * is set again immediately.
 *
 * @param base PORT peripheral base pointer.
 * @retval Current port interrupt status flags, for example, 0x00010001 means the
 *         pin 0 and 17 have the interrupt.
 */
static inline uint32_t PORT_GetPinsInterruptFlags(PORT_Type *base)
{
    return base->ISFR;
}
/*!
 * @brief Clears the multiple pins' interrupt status flag.
 *
 * @param base PORT peripheral base pointer.
 * @param mask PORT pins' numbers macro.
 */
static inline void PORT_ClearPinsInterruptFlags(PORT_Type *base, uint32_t mask)
{
    base->ISFR = mask;
}
/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_PORT_H_ */
