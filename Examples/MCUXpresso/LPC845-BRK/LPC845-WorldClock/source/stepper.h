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
#include "McuRTOS.h"

typedef void *STEPPER_Handle_t;

typedef struct STEPPER_Config_t {
  void *device; /* point to the motor device */
  void (*stepFn)(void *device, int step); /* function pointer to perform a single step forward (1) or backward (-1) */
} STEPPER_Config_t;

void STEPPER_GetDefaultConfig(STEPPER_Config_t *config);

STEPPER_Handle_t STEPPER_InitDevice(STEPPER_Config_t *config);

void STEPPER_StopTimer(void);
void STEPPER_StartTimer(void);
bool STEPPER_TimerClockCallback(STEPPER_Handle_t stepper);

uint8_t STEPPER_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

#define STEPPER_NOF_CLOCKS        (4)    /* number of clocks on a board */
#define STEPPER_NOF_CLOCK_MOTORS  (2)    /* number of motors for each clock */
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

bool STEPPER_IsIdle(STEPPER_Handle_t stepper);

void STEPPER_MoveClockDegreeAbs(STEPPER_Handle_t stepper, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown);
void STEPPER_MoveClockDegreeRel(STEPPER_Handle_t stepper, int32_t degree, STEPPER_MoveMode_e mode, uint8_t delay, bool speedUp, bool slowDown);
void STEPPER_MoveMotorStepsRel(STEPPER_Handle_t stepper, int32_t steps, uint16_t delay);
void STEPPER_MoveMotorDegreeRel(STEPPER_Handle_t stepper, int32_t degree, uint16_t delay);

void STEPPER_SetPos(STEPPER_Handle_t stepper, int32_t pos);
int32_t STEPPER_GetPos(STEPPER_Handle_t stepper);
void STEPPER_NormalizePosition(STEPPER_Handle_t stepper);

void STEPPER_StrCatStatus(STEPPER_Handle_t stepper, unsigned char *buf, size_t bufSize);
QueueHandle_t STEPPER_GetQueue(STEPPER_Handle_t stepper);

void *STEPPER_GetDevice(STEPPER_Handle_t stepper);

void STEPPER_Deinit(void);
void STEPPER_Init(void);

#endif /* STEPPER_H_ */
