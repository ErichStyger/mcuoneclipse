/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);
uint8_t STEPPER_CheckAndExecuteQueue(const McuShell_StdIOType *io);

#define STEPPER_NOF_CLOCKS        (4)
#define STEPPER_NOF_CLOCK_MOTORS  (2)
#define STEPPER_CLOCK_360_STEPS   (4320) /* number of steps for a full turn on the clock */

typedef enum {
  STEPPER_MOVE_MODE_SHORT,  /* shortest move to position */
  STEPPER_MOVE_MODE_CW,     /* clock-wise move */
  STEPPER_MOVE_MODE_CCW,    /* counter-clock-wise move */
} STEPPER_MoveMode_e;

typedef enum {
  STEPPER_HAND_MM = 0, /* inner, mm */
  STEPPER_HAND_HH = 1  /* outer, hh */
} STEPPER_Hand_e;

typedef enum {
  STEPPER_CLOCK_0=0,
  STEPPER_CLOCK_1=1,
  STEPPER_CLOCK_2=2,
  STEPPER_CLOCK_3=3,
} STEPPER_Clock_e;

bool STEPPER_IsIdle(void);

void STEPPER_MoveClockDegreeAbs(STEPPER_Clock_e clk, STEPPER_Hand_e motorIndex, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown);
void STEPPER_MoveClockDegreeRel(STEPPER_Clock_e clk, STEPPER_Hand_e motorIndex, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown);

uint8_t STEPPER_ZeroAllHands(void);

void STEPPER_MoveAndWait(uint32_t waitMs);

void STEPPER_ShowLEDs(void);

void STEPPER_Deinit(void);
void STEPPER_Init(void);

#endif /* STEPPER_H_ */
