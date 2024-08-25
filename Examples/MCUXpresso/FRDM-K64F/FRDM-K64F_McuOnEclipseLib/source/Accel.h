/**
 * \file
 * \brief This is the interface to Accelerometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 * \license SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __ACCEL_H_
#define __ACCEL_H_

#include "platform.h"
#include <stdint.h>
#include <stdbool.h>

#if PL_CONFIG_HAS_ACCEL
/*!
 * \brief Returns the current accelerometer sensor values
 * \param[out] x X value
 * \param[out] y Y value
 * \param[out] z Z value
 */
void ACCEL_GetValues(int16_t *x, int16_t *y, int16_t *z);

/*! \brief Deinitialization of the module */
void ACCEL_Deinit(void);

/*! \brief Initialization of the module */
void ACCEL_Init(void);

/*!
 * \brief Mutex to request access to device
 */
void ACCEL_RequestDevice(void);

/*!
 * \brief Mutex to release access to device
 */
void ACCEL_ReleaseDevice(void);

/*! \brief Initialization of the module. This communicates to the device and needs interrupts enabled! */
uint8_t ACCEL_LowLevelInit(void);

/*!
 * \brief Enables the device
 * \return Error code, ERR_OK for no failure.
 */
uint8_t ACCEL_Enable(void);

/*!
 * \brief Routine to find out if the accelerometer is enabled or not.
 * \param isEnabled Reflects the status of the sensor.
 * \return Error code, ERR_OK for no error.
 */
uint8_t ACCEL_isEnabled(bool *isEnabled);

#endif /* PL_CONFIG_HAS_ACCEL */

#endif /* __ACCEL_H_ */
