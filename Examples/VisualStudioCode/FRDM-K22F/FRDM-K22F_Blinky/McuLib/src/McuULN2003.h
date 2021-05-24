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

#include "McuGPIO.h"

#define McuLUN2003_28BYJ_48_    4076  /* 64:1 gear (actually more 63.68395:1 (4076 steps/ref), Adafruit has a 1/16 reduction (513 steps/rev) */

typedef enum {
  McuULN2003_STEP_MODE_FULL = 1,
  McuULN2003_STEP_MODE_HALF = 2,
} McuULN2003_StepMode;

typedef void *McuULN2003_Handle_t;

#define McuULN2003_NOF_MOTOR_GPIO_PINS  (4)

typedef struct {
  McuULN2003_StepMode stepMode; /* half or full steps */
  bool inverted; /* if direction is inverted */
  McuGPIO_HwPin_t hw[McuULN2003_NOF_MOTOR_GPIO_PINS]; /* hardware pins */
} McuULN2003_Config_t;

void McuULN2003_GetDefaultConfig(McuULN2003_Config_t *config);
McuULN2003_Handle_t McuULN2003_InitMotor(McuULN2003_Config_t *config);
McuULN2003_Handle_t McuULN2003_DeinitMotor(McuULN2003_Handle_t motor);

void McuULN2003_PowerOff(McuULN2003_Handle_t motor);

void McuULN2003_SetStepMode(McuULN2003_Handle_t motor, McuULN2003_StepMode mode);
McuULN2003_StepMode McuULN2003_GetStepMode(McuULN2003_Handle_t motor);

bool McuULN2003_MoveCallback(McuULN2003_Handle_t motor, int32_t targetPos);

void McuULN2003_IncStep(McuULN2003_Handle_t motor);
void McuULN2003_DecStep(McuULN2003_Handle_t motor);
void McuULN2003_Step(McuULN2003_Handle_t motor, int32_t steps);

int32_t McuULN2003_GetPos(McuULN2003_Handle_t motor);
void McuULN2003_SetPos(McuULN2003_Handle_t motor, int32_t pos);

void McuULN2003_Deinit(void);
void McuULN2003_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* MCUULN2003_H_ */
