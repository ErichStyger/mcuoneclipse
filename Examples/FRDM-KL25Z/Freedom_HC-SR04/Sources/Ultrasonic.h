/*
 * Ultrasonic.h
 *
 *  Created on: Dec 30, 2012
 *      Author: Erich Styger
 *      Driver for the HC-SR04 and FRDM-KL25Z board
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "PE_LDD.h"

/* 
 * \brief Called in case of an overflow during input capture. This function is called from an interrupt!
 * \param UserDataPtr Pointer to user structure
 */
void US_EventEchoOverflow(LDD_TUserData *UserDataPtr);

/*
 * \brief Called by the input capture interrupt for a raising or falling edge of the Echo pin
 * \param UserDataPtr Pointer to user structure
 */
void US_EventEchoCapture(LDD_TUserData *UserDataPtr);

/* 
 * \brief Convert measured microseconds to centimeters.
 * \param[in] temperatureCelsius Air temperature in degree Celsius
 */
uint16_t US_usToCentimeters(uint16_t microseconds, uint8_t temperatureCelsius);


uint16_t US_Measure_us(void);

/*
 * \brief Driver initialization routine.
 */
void US_Init(void);


#endif /* ULTRASONIC_H_ */
