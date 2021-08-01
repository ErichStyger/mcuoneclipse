/*
 * Copyright (c) 2021, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include "platform.h"

#define STEPPER_CONFIG_NOF_STEPPER   (PL_CONFIG_NOF_UNITS)

#define STEPPER_360_STEPS            (512u) /* number of steps for a full turn */

#define STEPPER_NOF_FLAPS         (40) /* number of flaps on each drum */
#define STEPPER_STEPS_PER_FLAP    (STEPPER_CLOCK_360_STEPS_MM/STEPPER_NOF_FLAPS)

#include "McuShell.h"
uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

int32_t STEPPER_GetPos(uint8_t motorIndex);

uint8_t STEPPER_ZeroPosition(uint8_t motorIndex);

void STEPPER_Deint(void);
void STEPPER_Init(void);

#endif /* STEPPER_H_ */
