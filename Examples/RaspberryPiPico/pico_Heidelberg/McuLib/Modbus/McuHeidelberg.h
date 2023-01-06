/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef MODBUS_MCUHEIDELBERG_H_
#define MODBUS_MCUHEIDELBERG_H_

#include "McuShell.h"

/* types of charging strategies and modes */
typedef enum McuHeidelberg_ChargingMode_e {
  ChargingMode_Stop,        /* stop immediately the charging */
  ChargingMode_Fast,        /* charge immediately with maximum power */
  ChargingMode_Slow,        /* charge immediately with the minimal power */
  ChargingMode_SlowPlusPV,  /* charge immediately with the minimal power. If PV supports more power, the power level gets increased */
  ChargingMode_OnlyPV,      /* charge only with the PV power available */
  ChargingMode_NofChargingMode, /* sentinel, must be last in list! */
} McuHeidelberg_ChargingMode_e;

McuHeidelberg_ChargingMode_e McuHeidelberg_GetChargingMode(void);
void McuHeidelberg_SetChargingMode(McuHeidelberg_ChargingMode_e mode);

uint8_t McuHeidelberg_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void McuHeidelberg_Deinit(void);
void McuHeidelberg_Init(void);

#endif /* MODBUS_MCUHEIDELBERG_H_ */
