/*
 * Copyright 2017 , NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_port.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.port_ke02"
#endif
#define PORT_PINNUMS_EACHPORT (8U)   /* PORT pin numbers in each PTA/PTB etc. */
#define PORT_NUM_EACH_PULLUPREG (4U) /* The port numbers in each pull up register. */

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Enables or disables the port pull up.
 *
 * param base   PORT peripheral base pointer.
 * param port   PORT type, such as PTA/PTB/PTC etc, see "port_type_t".
 * param num    PORT Pin number, such as 0, 1, 2....
 *               There are seven pins not exists in this device:
 *               PTG: PTG4, PTG5, PTG6, PTG7. PTH: PTH3, PTH4, PTH5.
 *               so, when set PTG, and PTH, please don't set the pins mentioned above.
 *               Please take refer to the reference manual.
 * param enable  Enable or disable the pull up feature switch.
 */
void PORT_SetPinPullUpEnable(PORT_Type *base, port_type_t port, uint8_t num, bool enable)
{
    if (enable)
    {
        /* Enable the pull up */
        if (port < kPORT_PTE)
        {
            base->PUEL |= (1UL << (PORT_PINNUMS_EACHPORT * (uint32_t)port + (uint32_t)num));
        }
        else
        {
            base->PUEH |= (1UL << (PORT_PINNUMS_EACHPORT * ((uint32_t)port - PORT_NUM_EACH_PULLUPREG) + (uint32_t)num));
        }
    }
    else
    {
        /* Disable the pull up */
        if (port < kPORT_PTE)
        {
            base->PUEL &= ~(1UL << (PORT_PINNUMS_EACHPORT * (uint32_t)port + (uint32_t)num));
        }
        else
        {
            base->PUEH &=
                ~(1UL << (PORT_PINNUMS_EACHPORT * ((uint32_t)port - PORT_NUM_EACH_PULLUPREG) + (uint32_t)num));
        }
    }
}

void PORT_SetPinSelect(port_module_t module, port_pin_select_t pin)
{
    if ((uint32_t)pin != 0U)
    {
        if (module > kPORT_SWDE)
        {
            SIM->PINSEL |= (uint32_t)module;
        }
        else
        {
            SIM->SOPT |= (uint32_t)module;
        }
    }
    else
    {
        if (module > kPORT_SWDE)
        {
            SIM->PINSEL &= ~(uint32_t)module;
        }
        else
        {
            SIM->SOPT &= ~(uint32_t)module;
        }
    }
}
