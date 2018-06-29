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

#include "pins_port_hw_access.h"
#include "pins_gpio_hw_access.h"

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External could be made static.
 * Function is defined for usage by application code.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 10.5, Impermissible cast; cannot cast from 'essentially Boolean'
 * to 'essentially unsigned'. This is required by the conversion of a bool into a bit.
 * Impermissible cast; cannot cast from 'essentially unsigned' to 'essentially enum<i>'.
 * This is required by the conversion of a bitfield of a register into a enum.
 *
 */

#if FEATURE_SOC_PORT_COUNT > 0

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_Init
 * Description   : This function configures the pins with the options provided
 * in the provided structure.
 *
 *END**************************************************************************/
status_t PINS_Init(const pin_settings_config_t * config)
{
    DEV_ASSERT(config->base != NULL);
    DEV_ASSERT((PORT_MUX_AS_GPIO != config->mux) || (config->gpioBase != NULL));
    DEV_ASSERT(config->pinPortIdx < PORT_PCR_COUNT);
    uint32_t regValue = config->base->PCR[config->pinPortIdx];
    uint32_t directions;
    uint32_t digitalFilters;

#if FEATURE_PINS_HAS_PULL_SELECTION
    switch (config->pullConfig)
    {
        case PORT_INTERNAL_PULL_NOT_ENABLED:
            {
                regValue &= ~(PORT_PCR_PE_MASK);
            }
            break;
        case PORT_INTERNAL_PULL_DOWN_ENABLED:
            {
                regValue &= ~(PORT_PCR_PS_MASK);
                regValue |= PORT_PCR_PE(1U);
            }
            break;
        case PORT_INTERNAL_PULL_UP_ENABLED:
            {
                regValue |= PORT_PCR_PE(1U);
                regValue |= PORT_PCR_PS(1U);
            }
            break;
        default:
            /* invalid command */
            DEV_ASSERT(false);
            break;
    }
#endif /* FEATURE_PINS_HAS_PULL_SELECTION */
#if FEATURE_PINS_HAS_OVER_CURRENT
    switch (config->overCurConfig)
    {
        case PORT_OVER_CURRENT_DISABLED:
            {
                regValue &= ~(PORT_PCR_OCE_MASK);
            }
            break;
        case PORT_OVER_CURRENT_INT_DISABLED:
            {
                regValue &= ~(PORT_PCR_OCIE_MASK);
                regValue |= PORT_PCR_OCE_MASK;
            }
            break;
        case PORT_OVER_CURRENT_INT_ENABLED:
            {
                regValue |= PORT_PCR_OCIE_MASK;
                regValue |= PORT_PCR_OCE_MASK;
            }
            break;
        default:
            /* invalid command */
            DEV_ASSERT(false);
            break;
    }
#endif /* FEATURE_PINS_HAS_OVER_CURRENT */

#if FEATURE_PINS_HAS_SLEW_RATE
    regValue &= ~(PORT_PCR_SRE_MASK);
    regValue |= PORT_PCR_SRE(config->rateSelectValue);
#endif
#if FEATURE_PORT_HAS_PASSIVE_FILTER
    regValue &= ~(PORT_PCR_PFE_MASK);
    regValue |= PORT_PCR_PFE(config->passiveFilter);
#endif
#if FEATURE_PINS_HAS_OPEN_DRAIN
    regValue &= ~(PORT_PCR_ODE_MASK);
    regValue |= PORT_PCR_ODE(isOpenDrainEnabled);
#endif
#if FEATURE_PINS_HAS_DRIVE_STRENGTH
    regValue &= ~(PORT_PCR_DSE_MASK);
    regValue |= PORT_PCR_DSE(config->driveSelect);
#endif
    regValue &= ~(PORT_PCR_MUX_MASK);
    regValue |= PORT_PCR_MUX(config->mux);
#if FEATURE_PORT_HAS_PIN_CONTROL_LOCK
    regValue &= ~(PORT_PCR_LK_MASK);
    regValue |= PORT_PCR_LK(config->pinLock);
#endif
    regValue &= ~(PORT_PCR_IRQC_MASK);
    regValue |= PORT_PCR_IRQC(config->intConfig);
    if (config->clearIntFlag)
    {
        regValue &= ~(PORT_PCR_ISF_MASK);
        regValue |= PORT_PCR_ISF(1U);
    }

    config->base->PCR[config->pinPortIdx] = regValue;

    /* Read current digital filter of port */
    digitalFilters = (uint32_t)(config->base->DFER);
    digitalFilters &= ~(1UL << (config->pinPortIdx));
    digitalFilters |= (((uint32_t)(config->digitalFilter)) << (config->pinPortIdx));
    /* Write to digital filter enable register */
    config->base->DFER = digitalFilters;

    /* If gpioBase address not null setup the direction of pin */
    if (PORT_MUX_AS_GPIO == config->mux)
    {
        /* Read current direction */
        directions = (uint32_t)(config->gpioBase->PDDR);
        switch (config->direction)
        {
            case GPIO_INPUT_DIRECTION:
                directions &= ~(1UL << config->pinPortIdx);
                break;
            case GPIO_OUTPUT_DIRECTION:
                directions |= (1UL << config->pinPortIdx);
                break;
            case GPIO_UNSPECIFIED_DIRECTION:
            /* pass-through */
            default:
                /* nothing to configure */
                DEV_ASSERT(false);
                break;
        }

        /* Configure direction */
        config->gpioBase->PDDR = GPIO_PDDR_PDD(directions);

        /* Configure initial value for output */
        if (config->direction == GPIO_OUTPUT_DIRECTION)
        {
            PINS_GPIO_WritePin(config->gpioBase, config->pinPortIdx, config->initValue);
        }
    }

    return STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_SetGlobalPinControl
 * Description   : Quickly configures multiple pins with the same pin configuration.
 *
 *END**************************************************************************/
void PINS_SetGlobalPinControl(PORT_Type * const base,
                              uint16_t pins,
                              uint16_t value,
                              port_global_control_pins_t halfPort)
{
    uint16_t mask = 0;
    /* keep only available fields */
    mask |= PORT_PCR_PS_MASK;
    mask |= PORT_PCR_PE_MASK;
#if FEATURE_PINS_HAS_SLEW_RATE
    mask |= PORT_PCR_SRE_MASK;
#endif /* FEATURE_PINS_HAS_OPEN_DRAIN */
    mask |= PORT_PCR_PFE_MASK;
#if FEATURE_PINS_HAS_OPEN_DRAIN
    mask |= PORT_PCR_ODE_MASK;
#endif /* FEATURE_PINS_HAS_OPEN_DRAIN */
    mask |= PORT_PCR_DSE_MASK;
    mask |= PORT_PCR_MUX_MASK;
#if FEATURE_PINS_HAS_OVER_CURRENT
    mask |= PORT_PCR_OCE_MASK;
#endif /* FEATURE_PINS_HAS_OVER_CURRENT */
    mask |= PORT_PCR_LK_MASK;
    mask &= value;

    switch (halfPort)
    {
        case PORT_GLOBAL_CONTROL_LOWER_HALF_PINS:
            base->GPCLR = (((uint32_t)pins) << PORT_GPCLR_GPWE_SHIFT) | (uint32_t)mask;
            break;
        case PORT_GLOBAL_CONTROL_UPPER_HALF_PINS:
            base->GPCHR = (((uint32_t)pins) << PORT_GPCLR_GPWE_SHIFT) | (uint32_t)mask;
            break;
        default:
            /* nothing to configure */
            DEV_ASSERT(false);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_SetGlobalIntControl
 * Description   : Quickly configures multiple pins with the same interrupt configuration.
 *
 *END**************************************************************************/
void PINS_SetGlobalIntControl(PORT_Type * const base,
                              uint16_t pins,
                              uint16_t value,
                              port_global_control_pins_t halfPort)
{
    uint32_t mask;
    mask = (((uint32_t)value) << PORT_GICLR_GIWD_SHIFT) & PORT_PCR_IRQC_MASK;

    switch (halfPort)
    {
        case PORT_GLOBAL_CONTROL_LOWER_HALF_PINS:
            base->GICLR = ((uint32_t)pins) | mask;
            break;
        case PORT_GLOBAL_CONTROL_UPPER_HALF_PINS:
            base->GICHR = ((uint32_t)pins) | mask;
            break;
        default:
            /* nothing to configure */
            DEV_ASSERT(false);
            break;
    }
}

#endif /* FEATURE_SOC_PORT_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/
