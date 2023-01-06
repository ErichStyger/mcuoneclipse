/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef MODBUS_MCUHEIDELBERG_H_
#define MODBUS_MCUHEIDELBERG_H_

typedef enum McuHeidelberg_Event_e {
  McuHeidelberg_Event_HW_State_Changed, /* hardware charger state has changed */
} McuHeidelberg_Event_e;

typedef void (*McuHeidelberg_EventCallback)(McuHeidelberg_Event_e);
  /*!< Event callback function prototype */

/*!
 * \brief Register a callback for events
 * \param callback function pointer for the callback
 */
void McuHeidelberg_RegisterEventCallback(McuHeidelberg_EventCallback callback);

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

/* state of the hardware wallbox */
typedef enum McuHeidelbergChargerState_e {
  McuHeidelberg_ChargerState_A1       = 2, /* no vehicle, charging not possible */
  McuHeidelberg_ChargerState_A2       = 3, /* no vehicle, charging possible */
  McuHeidelberg_ChargerState_B1       = 4, /* vehicle plugged, charging not possible */
  McuHeidelberg_ChargerState_B2       = 5, /* vehicle plugged, charging possible */
  McuHeidelberg_ChargerState_C1       = 6, /* vehicle charging request, charging not possible */
  McuHeidelberg_ChargerState_C2       = 7, /* vehicle charging request, charging possible */
  McuHeidelberg_ChargerState_Derating = 8, /* charging current derating due temperature */
  McuHeidelberg_ChargerState_E        = 9, /* error state */
  McuHeidelberg_ChargerState_F        = 10, /* wallbox locked or not ready */
  McuHeidelberg_ChargerState_Error    = 11, /* error state */
} McuHeidelbergChargerState_e;

McuHeidelbergChargerState_e McuHeidelberg_GetHWChargerState(void);
const unsigned char *McuHeidelberg_GetShortHWChargerStateString(McuHeidelbergChargerState_e state);

#include "McuShell.h"
uint8_t McuHeidelberg_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void McuHeidelberg_Deinit(void);
void McuHeidelberg_Init(void);

#endif /* MODBUS_MCUHEIDELBERG_H_ */
