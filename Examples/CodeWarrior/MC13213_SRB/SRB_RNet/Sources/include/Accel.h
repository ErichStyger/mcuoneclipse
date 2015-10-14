/**
 * \file
 * \brief This is the interface to Accelerometer Module
 * \author Erich Styger, erich.styger@hslu.ch
 */

#ifndef __ACCEL_H_
#define __ACCEL_H_

#include "Platform.h"

#if PL_HAS_ACCEL
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

/*! \brief Initialization of the module. This communicates to the device and needs interrupts enabled! */
uint8_t ACCEL_LowLevelInit(void);

#endif /* PL_HAS_ACCEL */

#endif /* __ACCEL_H_ */
