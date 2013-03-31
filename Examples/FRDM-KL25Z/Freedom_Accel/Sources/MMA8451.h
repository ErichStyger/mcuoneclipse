/*
 * MMA8451.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Erich Styger
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include "PE_Types.h"

uint8_t MMA8451_GetRaw8XYZ(uint8_t xyz[3]);

uint8_t MMA8451_Deinit(void);

uint8_t MMA8451_Init(void);

#endif /* MMA8451_H_ */
