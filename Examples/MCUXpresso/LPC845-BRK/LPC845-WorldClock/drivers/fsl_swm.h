/*
 * Copyright  2017-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_SWM_H_
#define _FSL_SWM_H_

#include "fsl_swm_connections.h"

/*!
 * @addtogroup swm
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
#define FSL_SWM_DRIVER_VERSION (MAKE_VERSION(2, 0, 2)) /*!< Version 2.0.2 */
/*@}*/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Assignment of digital peripheral functions to pins.
 *
 * This function will selects a pin (designated by its GPIO port and
 * bit numbers) to a function.
 *
 * @param base SWM peripheral base address.
 * @param func any function name that is movable.
 * @param swm_port_pin any pin which has a GPIO port number and bit number.
 */
void SWM_SetMovablePinSelect(SWM_Type *base, swm_select_movable_t func, swm_port_pin_type_t swm_port_pin);

#if (defined(FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER) && (FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER == 1))
/*!
 * @brief Assignment of digital peripheral functions to pins.
 *
 * This function will selects a pin (designated by its GPIO port and
 * bit numbers) to a function.
 *
 * @param base SWM peripheral base address.
 * @param func any function name that is movable.
 * @param swm_port_pin any pin which has a GPIO port number and bit number.
 */
void SWM_SetFixedMovablePinSelect(SWM_Type *base,
                                  swm_select_fixed_movable_t func,
                                  swm_fixed_port_pin_type_t swm_port_pin);
#endif /* FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER */

/*!
 * @brief Enable the fixed-pin function.
 *
 * This function will enables a fixed-pin function in PINENABLE0 or PINENABLE1.
 *
 * @param base SWM peripheral base address.
 * @param func any function name that is fixed pin.
 * @param enable enable or disable.
 */
void SWM_SetFixedPinSelect(SWM_Type *base, swm_select_fixed_pin_t func, bool enable);

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* _FSL_SWM_H_ */
