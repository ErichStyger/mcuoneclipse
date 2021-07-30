/*
 * stepper.h
 *
 *  Created on: 08.08.2019
 *      Author: Erich Styger
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#define STEPPER_CLOCK_360_STEPS_HH   (512u) /* number of steps for a full turn on the clock for the hours */
#define STEPPER_CLOCK_360_STEPS_MM   (512u) /* number of steps for a full turn */

#define STEPPER_CLOCK_HH_ZERO_OFFSET (12)   /* offset from the zero position */
#define STEPPER_CLOCK_MM_ZERO_OFFSET (12)   /* offset from the zero position */

#define STEPPER_NOF_FLAPS         (40)
#define STEPPER_STEPS_PER_FLAP    (STEPPER_CLOCK_360_STEPS_MM/STEPPER_NOF_FLAPS)


#include "McuShell.h"
uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

int32_t STEPPER_GetPos(void);

uint8_t STEPPER_ZeroHourHand(void);
uint8_t STEPPER_ZeroMinuteHand(void);

void STEPPER_ShowTime(uint8_t hour, uint8_t minute);

void STEPPER_Init(void);

#endif /* STEPPER_H_ */
