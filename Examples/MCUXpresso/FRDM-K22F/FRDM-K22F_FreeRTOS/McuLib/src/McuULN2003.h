/*
 * Copyright (c) 2019, Erich Styger
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUULN2003_H_
#define MCUULN2003_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McuULN2003config.h"
#include "McuGPIO.h"

#define McuLUN2003_28BYJ_48_    4076  /* 64:1 gear (actually more 63.68395:1 (4076 steps/ref), Adafruit has a 1/16 reduction (513 steps/rev) */

typedef enum {
  McuULN2003_STEP_MODE_FULL = 1,
  McuULN2003_STEP_MODE_HALF = 2,
} McuULN2003_StepMode;

typedef void *McuULN2003_Handle_t;

#define McuULN2003_NOF_MOTOR_GPIO_PINS  (4) /* number of GPIO pins for a motor */
#define McuULN2003_NOF_MOTOR_BITS       (McuULN2003_NOF_MOTOR_GPIO_PINS) /* number of bits needed if using a shift register */

#define McuULN2003_NOF_STEPS_HALF_STEP_MODE    (8)
#define McuULN2003_NOF_STEPS_FULL_STEP_MODE    (4)

/* half step logic tables: */
extern const bool McuULN2003_stepTableHalfStepsFw[McuULN2003_NOF_STEPS_HALF_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS];
extern const bool McuULN2003_stepTableHalfStepsBw[McuULN2003_NOF_STEPS_HALF_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS];

/* full step logic tables: */
extern const bool McuULN2003_stepTableFullStepsFw[McuULN2003_NOF_STEPS_FULL_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS];
extern const bool McuULN2003_stepTableFullStepsBw[McuULN2003_NOF_STEPS_FULL_STEP_MODE][McuULN2003_NOF_MOTOR_GPIO_PINS];

typedef struct {
  McuULN2003_StepMode stepMode; /* half or full steps, default McuULN2003_STEP_MODE_HALF */
  bool inverted; /* if direction is inverted, default false */
  bool isShiftReg; /* if using a shift register, default false */
  uint32_t id; /* optional ID or index, default 0 */
  bool noGPIO; /* if not using gpio, then no hardware gets allocated, useful for custom HW (e.g. shift register), default false */
  void (*stepCallback)(McuULN2003_Handle_t motor, const bool w[McuULN2003_NOF_MOTOR_GPIO_PINS]); /* optional custom call back to set motor signals. If NULL, it uses the internal GPIO HW one. Default: NULL */
  McuGPIO_HwPin_t hw[McuULN2003_NOF_MOTOR_GPIO_PINS]; /* hardware GPIO pins, default NULL */
} McuULN2003_Config_t;

void McuULN2003_GetDefaultConfig(McuULN2003_Config_t *config);
McuULN2003_Handle_t McuULN2003_InitMotor(McuULN2003_Config_t *config);
McuULN2003_Handle_t McuULN2003_DeinitMotor(McuULN2003_Handle_t motor);

void McuULN2003_PowerOff(McuULN2003_Handle_t motor);

void McuULN2003_SetStepMode(McuULN2003_Handle_t motor, McuULN2003_StepMode mode);
McuULN2003_StepMode McuULN2003_GetStepMode(McuULN2003_Handle_t motor);

bool McuULN2003_StepCallback(McuULN2003_Handle_t motor, bool forward);
bool McuULN2003_MoveCallback(McuULN2003_Handle_t motor, int32_t targetPos);

void McuULN2003_IncStep(McuULN2003_Handle_t motor);
void McuULN2003_DecStep(McuULN2003_Handle_t motor);
void McuULN2003_Step(McuULN2003_Handle_t motor, int32_t steps);

int32_t McuULN2003_GetPos(McuULN2003_Handle_t motor);
void McuULN2003_SetPos(McuULN2003_Handle_t motor, int32_t pos);

/*!
 * \brief returns the ID of the motor.
 * \param motor Motor handle
 * \return ID of the motor which has been set at creation time
 */
uint32_t McuULN2003_GetID(McuULN2003_Handle_t motor);

#if McuULN2003_CONFIG_USE_ACCELERATION

/* stepper motor acceleration table */
typedef struct McuULN2003_Accel_t {
  uint8_t nofEntries; /* number of entries in delay table */
  const uint8_t *delays; /* table of delays, with nofEntires entries */
} McuULN2003_Accel_t;

void McuULN2003_AccelerationStart(McuULN2003_Handle_t motor);
void McuULN2003_AccelerationEnd(McuULN2003_Handle_t motor);
void McuULN2003_SetAccelerationTable(McuULN2003_Handle_t motor, const McuULN2003_Accel_t *table);
#endif

void McuULN2003_Deinit(void);
void McuULN2003_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* MCUULN2003_H_ */
