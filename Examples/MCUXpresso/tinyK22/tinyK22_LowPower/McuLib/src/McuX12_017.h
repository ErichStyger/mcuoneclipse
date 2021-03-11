/*
 * Copyright (c) 2019, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Driver for the X12.017 Quad-Stepper motor driver
 */

#ifndef MCU_X12_017_H_
#define MCU_X12_017_H_

#include <stdint.h>
#include <stdbool.h>
#include "McuGPIO.h"
#include "McuX12_017config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *McuX12_017_Handle_t;

typedef enum {
  X12_017_M0 = 0,
  X12_017_M1 = 1,
#if McuX12_017_CONFIG_QUAD_DRIVER
  X12_017_M2 = 2,
  X12_017_M3 = 3,
#endif
  X12_017_NOF_M /* number of stepper motors the X12.017 can drive */
} McuX12_017_Motor_e;

typedef struct {
  bool isInverted; /* if direction is inverted */
  McuGPIO_HwPin_t hw_dir; /* direction pin */
  McuGPIO_HwPin_t hw_step; /* step pin */
} McuX12_017_Motor_t;

typedef struct {
  bool hasReset;  /* if using reset pin on driver */
  McuGPIO_HwPin_t hw_reset; /* reset pin */
  McuX12_017_Motor_t motor[X12_017_NOF_M]; /* motors */
} McuX12_017_Config_t;

void McuX12_017_GetDefaultConfig(McuX12_017_Config_t *config);

McuX12_017_Handle_t McuX12_017_InitDevice(McuX12_017_Config_t *config);
McuX12_017_Handle_t McuX12_017_DeinitDevice(McuX12_017_Handle_t device);

void McuX12_017_ResetDriver(McuX12_017_Handle_t device);
void McuX12_017_SetResetLine(McuX12_017_Handle_t device, bool setHigh);

void McuX12_017_SetForward(McuX12_017_Handle_t device, McuX12_017_Motor_e motor);
void McuX12_017_SetBackward(McuX12_017_Handle_t device, McuX12_017_Motor_e motor);

void McuX12_017_Step(McuX12_017_Handle_t device, McuX12_017_Motor_e motor);
void McuX12_017_DoSteps(McuX12_017_Handle_t device, McuX12_017_Motor_e motor, int32_t steps);

void McuX12_017_SingleStep(McuX12_017_Handle_t device, McuX12_017_Motor_e motor, int step);

int32_t X12_017_GetPos(McuX12_017_Handle_t device, McuX12_017_Motor_e motor);
void X12_017_SetPos(McuX12_017_Handle_t device, McuX12_017_Motor_e motor, int32_t pos);

void McuX12_017_GetDeviceStatusString(McuX12_017_Handle_t device, unsigned char *buf, size_t bufSize);

void McuX12_017_DisableDevice(McuX12_017_Handle_t device);
void McuX12_017_EnableDevice(McuX12_017_Handle_t device);

void McuX12_017_Deinit(void);
void McuX12_017_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* MCU_X12_017_H_ */
