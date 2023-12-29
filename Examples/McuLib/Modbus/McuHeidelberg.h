/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MODBUS_MCUHEIDELBERG_H_
#define MODBUS_MCUHEIDELBERG_H_

#include "McuShell.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum McuHeidelberg_Event_e {
  McuHeidelberg_Event_HW_State_Changed,           /* hardware charger state has changed */
  McuHeidelberg_Event_UserChargingMode_Changed,   /* user charging mode has changed */
  McuHeidelberg_Event_ChargingSetCurrent_Changed, /* current in the charger has changed */
  McuHeidelberg_Event_SolarPower_Changed,         /* produced solar power has changed */
  McuHeidelberg_Event_SitePower_Changed,          /* used power by site has changed */
  McuHeidelberg_Event_ChargerPower_Changed,       /* charging value of car changed */
  McuHeidelberg_Event_GridPower_Changed,          /* grid power value changed */
  McuHeidelberg_Event_BatteryPower_Changed,       /* battery power value changed */
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
  McuHeidelberg_User_ChargingMode_Stop,             /* stop immediately the charging */
  McuHeidelberg_User_ChargingMode_OnlyPV,           /* charge only with the PV power available */
  McuHeidelberg_User_ChargingMode_Slow,             /* charge immediately with the minimal power */
  McuHeidelberg_User_ChargingMode_SlowPlusPV,       /* charge immediately with the minimal power. If PV supports more power, the power level gets increased */
  McuHeidelberg_User_ChargingMode_Fast,             /* charge immediately with maximum power */
  McuHeidelberg_User_ChargingMode_6_Amp,
  McuHeidelberg_User_ChargingMode_7_Amp,
  McuHeidelberg_User_ChargingMode_8_Amp,
  McuHeidelberg_User_ChargingMode_9_Amp,
  McuHeidelberg_User_ChargingMode_10_Amp,
  McuHeidelberg_User_ChargingMode_11_Amp,
  McuHeidelberg_User_ChargingMode_12_Amp,
  McuHeidelberg_User_ChargingMode_13_Amp,
  McuHeidelberg_User_ChargingMode_14_Amp,
  McuHeidelberg_User_ChargingMode_15_Amp,
  McuHeidelberg_User_ChargingMode_16_Amp,
  McuHeidelberg_User_ChargingMode_NofChargingMode,  /* sentinel, must be last in list! */
} McuHeidelberg_UserChargingMode_e;

McuHeidelberg_UserChargingMode_e McuHeidelberg_GetUserChargingMode(void);
void McuHeidelberg_SetUserChargingMode(McuHeidelberg_UserChargingMode_e mode);

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

uint32_t McuHeidelberg_GetSolarPowerWatt(void);
void McuHeidelberg_SetSolarPowerWatt(uint32_t powerW);

uint32_t McuHeidelberg_GetSitePowerWatt(void);
void McuHeidelberg_SetSitePowerWatt(uint32_t powerW);

int32_t McuHeidelberg_GetGridPowerWatt(void);
void McuHeidelberg_SetGridPowerWatt(int32_t powerW);

int32_t McuHeidelberg_GetBatteryPowerWatt(void);
void McuHeidelberg_SetBatteryPowerWatt(int32_t powerW);

uint32_t McuHeidelberg_GetMaxCarPower(void);

uint32_t McuHeidelberg_GetCurrChargerPower(void);

uint8_t McuHeidelberg_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void McuHeidelberg_Deinit(void);
void McuHeidelberg_Init(void);

#endif /* MODBUS_MCUHEIDELBERG_H_ */
