/*
 * Copyright (c) 2022-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuLib.h"
#if McuLib_CONFIG_SDK_USE_FREERTOS

#include "McuHeidelberg.h"
#include "McuHeidelberg_config.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuModbus.h"
#include "McuRTOS.h"
#include "McuLog.h"
#if McuHeidelberg_CONFIG_USE_WATCHDOG
  #include "McuWatchdog.h"
#endif

typedef enum McuHeidelberg_AddrMap_e{
  McuHeidelberg_Addr_ModbusRegisterLayoutVersion    = 4,
  McuHeidelberg_Addr_ChargingState                  = 5,
  McuHeidelberg_Addr_Current_L1                     = 6,
  McuHeidelberg_Addr_Current_L2                     = 7,
  McuHeidelberg_Addr_Current_L3                     = 8,
  McuHeidelberg_Addr_Temperature                    = 9,
  McuHeidelberg_Addr_Voltage_L1                     = 10,
  McuHeidelberg_Addr_Voltage_L2                     = 11,
  McuHeidelberg_Addr_Voltage_L3                     = 12,
  McuHeidelberg_Addr_LockState                      = 13,
  McuHeidelberg_Addr_Power                          = 14,
  McuHeidelberg_Addr_EnergyPowerOn                  = 15,
    McuHeidelberg_Addr_EnergyPowerOn_High           = McuHeidelberg_Addr_EnergyPowerOn,
    McuHeidelberg_Addr_EnergyPowerOn_Low            = McuHeidelberg_Addr_EnergyPowerOn+1,
  McuHeidelberg_Addr_Energy_Installation            = 17,
    McuHeidelberg_Addr_Energy_Installation_High     = McuHeidelberg_Addr_Energy_Installation,
    McuHeidelberg_Addr_Energy_Installation_Low      = McuHeidelberg_Addr_Energy_Installation+1,
  McuHeidelberg_Addr_MaxCurrent                     = 100,
  McuHeidelberg_Addr_MinCurrent                     = 101,
  McuHeidelberg_Addr_LogisticString                 = 102,
    McuHeidelberg_Addr_LogisticString_Start         = McuHeidelberg_Addr_LogisticString,
    McuHeidelberg_Addr_LogisticString_End           = 133,
  McuHeidelberg_Addr_HardwareVariant                = 200,
  McuHeidelberg_Addr_AppSoftwareRevision            = 203,
  McuHeidelberg_Addr_WatchDogTimeout                = 257,
  McuHeidelberg_Addr_StandbyFunctionControl         = 258,
  McuHeidelberg_Addr_RemoteLock                     = 259,
  McuHeidelberg_Addr_MaxCurrentCommand              = 261,
  McuHeidelberg_Addr_FailSafeCurrent                = 262,
  McuHeidelberg_Addr_SupportDiagnosticData          = 300,
    McuHeidelberg_Addr_SupportDiagnosticData_Start  = McuHeidelberg_Addr_SupportDiagnosticData,
    McuHeidelberg_Addr_SupportDiagnosticData_End    = 318,
  McuHeidelberg_Addr_ErrorMemory                    = 500,
    McuHeidelberg_Addr_ErrorMemory_Start            = McuHeidelberg_Addr_ErrorMemory,
    McuHeidelberg_Addr_ErrorMemory_End              = 819,
} McuHeidelberg_AddrMap_e;

static const uint8_t McuHeidelberg_deviceID = 0x01; /* assigned Modbus ID/address */

/* state of the wallbox task */
typedef enum WallboxTaskState_e {
  Wallbox_TaskState_None,
  Wallbox_TaskState_Connected,
  Wallbox_TaskState_Vehicle_Plugged,
  Wallbox_TaskState_Vehicle_Start_Charging,
  Wallbox_TaskState_Vehicle_Charging,
  Wallbox_TaskState_Vehicle_Stop_Charging,
  Wallbox_TaskState_Error,
} WallboxTaskState_e;

static struct McuHeidelbergInfo_s {
  bool isActive;                                      /* if unit is in standby or not */
  WallboxTaskState_e state;                           /* state of the wallbox task */
  McuHeidelberg_UserChargingMode_e userChargingMode;  /* selected user charging mode */
  uint32_t solarPowerW;                               /* produced solar power in Watt */
  uint32_t sitePowerW;                                /* used power by the building or site, including charger */
  int32_t gridPowerW;                                 /* (positive) power from or to the grid (negative) */
  uint32_t maxCarPowerW;                              /* maximum charge power in Watt: used for charger 'I max' command */
  uint8_t nofPhases;                                  /* number of active phases detected on the charger */
  McuHeidelberg_EventCallback eventCallback;          /* registered callback for events */
  struct hw { /* wallbox hardware register values */
    uint16_t version;                 /* register layout version */
    uint16_t chargerState;            /* wallbox charging state */
    uint16_t minCurrent;              /* minimal current, as configured by the hardware switch, 6 A up to 16 A */
    uint16_t maxCurrent;              /* maximal current, as configured by the hardware switch, 6 A up to 16 A */
    uint16_t current[3];              /* RMS current of the three phases, in 0.1 A units */
    int16_t  temperature;             /* PCB temperature, in 0.1 degree C */
    uint16_t voltage[3];              /* RMS voltage of the three phases, in 0.1 A units */
    uint16_t lockState;               /* external lock */
    uint16_t power;                   /* sum of power of all three phases */
    uint32_t energySincePowerOn;      /* energy since last standby or power-off */
    uint32_t energySinceInstallation; /* energy since installation */
  } hw;
} McuHeidelbergInfo;

static SemaphoreHandle_t semNewSolarValue; /* binary semaphore to notify task about new solar PV value */

#if McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
static struct mock {
  uint16_t hwChargerState; /* mock value of wallbox charging state */
} mock;
#endif

static const unsigned char *McuHeidelberg_GetHWChargerStateString(McuHeidelbergChargerState_e state) {
  const unsigned char *str;
  switch(state) {
    case McuHeidelberg_ChargerState_A1:       str = (unsigned char*)"A1: no vehicle plugged, wallbox doesn't allow charging"; break;
    case McuHeidelberg_ChargerState_A2:       str = (unsigned char*)"A2: no vehicle plugged, wallbox allows charging"; break;
    case McuHeidelberg_ChargerState_B1:       str = (unsigned char*)"B1: vehicle plugged, no charging request, wallbox doesn't allow charging"; break;
    case McuHeidelberg_ChargerState_B2:       str = (unsigned char*)"B2: vehicle plugged, no charging request, wallbox allows charging"; break;
    case McuHeidelberg_ChargerState_C1:       str = (unsigned char*)"C1: vehicle plugged with charging request, wallbox doesn't allow charging"; break;
    case McuHeidelberg_ChargerState_C2:       str = (unsigned char*)"C2: vehicle plugged with charging request, wallbox allows charging"; break;
    case McuHeidelberg_ChargerState_Derating: str = (unsigned char*)"--: derating"; break;
    case McuHeidelberg_ChargerState_E:        str = (unsigned char*)"E: error"; break;
    case McuHeidelberg_ChargerState_F:        str = (unsigned char*)"F: wallbox locked or not ready"; break;
    case McuHeidelberg_ChargerState_Error:    str = (unsigned char*)"--: Error"; break;
    default:                                  str = (unsigned char*)"ERROR, unknown state!"; break;
  }
  return str;
}

const unsigned char *McuHeidelberg_GetShortHWChargerStateString(McuHeidelbergChargerState_e state) {
  const unsigned char *str;
  switch(state) {
    case McuHeidelberg_ChargerState_A1:       str = (unsigned char*)"A1"; break;
    case McuHeidelberg_ChargerState_A2:       str = (unsigned char*)"A2"; break;
    case McuHeidelberg_ChargerState_B1:       str = (unsigned char*)"B1"; break;
    case McuHeidelberg_ChargerState_B2:       str = (unsigned char*)"B2"; break;
    case McuHeidelberg_ChargerState_C1:       str = (unsigned char*)"C1"; break;
    case McuHeidelberg_ChargerState_C2:       str = (unsigned char*)"C2"; break;
    case McuHeidelberg_ChargerState_Derating: str = (unsigned char*)"der"; break;
    case McuHeidelberg_ChargerState_E:        str = (unsigned char*)"E"; break;
    case McuHeidelberg_ChargerState_F:        str = (unsigned char*)"F"; break;
    case McuHeidelberg_ChargerState_Error:    str = (unsigned char*)"Err"; break;
    default:                                  str = (unsigned char*)"ERR"; break;
  }
  return str;
}

static const unsigned char *McuHeidelberg_GetStateString(WallboxTaskState_e state) {
  const unsigned char *str;
  switch(state) {
    case Wallbox_TaskState_None:                  str = (unsigned char*)"none"; break;
    case Wallbox_TaskState_Connected:             str = (unsigned char*)"connected"; break;
    case Wallbox_TaskState_Vehicle_Plugged:       str = (unsigned char*)"vehicle plugged"; break;
    case Wallbox_TaskState_Vehicle_Start_Charging:str = (unsigned char*)"start charging"; break;
    case Wallbox_TaskState_Vehicle_Charging:      str = (unsigned char*)"vehicle charging"; break;
    case Wallbox_TaskState_Vehicle_Stop_Charging: str = (unsigned char*)"stop charging"; break;
    case Wallbox_TaskState_Error:                 str = (unsigned char*)"error"; break;
    default:                                  str = (unsigned char*)"ERROR, unknown state!"; break;
  }
  return str;
}

static const unsigned char *McuHeidelberg_GetUserChargingModeString(McuHeidelberg_UserChargingMode_e mode) {
  const unsigned char *str;
  switch(mode) {
    case McuHeidelberg_User_ChargingMode_Stop:         str = (unsigned char*)"stop"; break;
    case McuHeidelberg_User_ChargingMode_Fast:         str = (unsigned char*)"fast"; break;
    case McuHeidelberg_User_ChargingMode_Slow:         str = (unsigned char*)"slow"; break;
    case McuHeidelberg_User_ChargingMode_SlowPlusPV:   str = (unsigned char*)"slow plus PV"; break;
    case McuHeidelberg_User_ChargingMode_OnlyPV:       str = (unsigned char*)"only PV"; break;
    default:                        str = (unsigned char*)"ERROR, unknown mode!"; break;
  }
  return str;
}

/* -------------------------------------------- */
/* Read and write the hardware Modbus registers */

uint8_t McuHeidelberg_ReadRegisterLayoutVersion(uint8_t id, uint16_t *version) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_ModbusRegisterLayoutVersion, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *version = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadChargingState(uint8_t id, uint16_t *state) {
#if McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
  *state = mock.hwChargerState;
#else
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_ChargingState, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *state = value;
#endif
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadCurrent(uint8_t id, uint16_t current[3]) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(McuHeidelberg_deviceID, McuHeidelberg_Addr_Current_L1, 1, &value)==ERR_OK) {
    current[0] = value;
  } else {
    return ERR_FAILED;
  }
  if (McuModbus_ReadInputRegisters(McuHeidelberg_deviceID, McuHeidelberg_Addr_Current_L2, 1, &value)==ERR_OK) {
    current[1] = value;
  } else {
    return ERR_FAILED;
  }
  if (McuModbus_ReadInputRegisters(McuHeidelberg_deviceID, McuHeidelberg_Addr_Current_L3, 1, &value)==ERR_OK) {
    current[2] = value;
  } else {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadTemperature(uint8_t id, int16_t *temperature) {
  int16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_Temperature, 1, (uint16_t*)&value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *temperature = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadVoltage(uint8_t id, uint16_t voltage[3]) {
  uint16_t value[3];

  if (McuModbus_ReadInputRegisters(McuHeidelberg_deviceID, McuHeidelberg_Addr_Voltage_L1, 3, value)==ERR_OK) {
    voltage[0] = value[0];
    voltage[1] = value[1];
    voltage[2] = value[2];
  } else {
    return ERR_FAILED;
  }
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadLockstate(uint8_t id, uint16_t *state) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_LockState, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *state = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadPower(uint8_t id, uint16_t *power) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_Power, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *power = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadEnergySincePowerOn(uint8_t id, uint32_t *energy) {
  uint16_t value[2];

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_EnergyPowerOn, 2, value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *energy = (value[0]<<16) + value[1];
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadEnergySinceInstallation(uint8_t id, uint32_t *energy) {
  uint16_t value[2];

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_Energy_Installation, 2, value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *energy = (value[0]<<16) + value[1];
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadHardwareMaxCurrent(uint8_t id, uint16_t *current) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_MaxCurrent, 1, &value)!=ERR_OK) {
    *current = 6; /* minimal current */
    return ERR_FAILED;
  }
  *current = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadHardwareMinCurrent(uint8_t id, uint16_t *current) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_MinCurrent, 1, &value)!=ERR_OK) {
    *current = 6; /* minimal current */
    return ERR_FAILED;
  }
  *current = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadLogisticString(uint8_t id, unsigned char *string, size_t stringSize) {
  uint16_t value[McuHeidelberg_Addr_LogisticString_End-McuHeidelberg_Addr_LogisticString_Start+1];

  memset(value, 0, sizeof(value));
  for(int i=0; i<sizeof(value)/sizeof(value[0]); i++) {
    if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_LogisticString+i, 1, &value[i])!=ERR_OK) {
      return ERR_FAILED;
    }
  }
  string[0] = '\0';
  for(int i=0; i<sizeof(value)/sizeof(value[0]); i++) {
    McuUtility_chcat(string, stringSize, (unsigned char)(value[i]>>8));
    McuUtility_chcat(string, stringSize, (unsigned char)(value[i]&0xff));
  }
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadHardwareVariant(uint8_t id, uint16_t *variant) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_HardwareVariant, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *variant = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadApplicationSoftwareRevision(uint8_t id, uint16_t *revision) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_AppSoftwareRevision, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *revision = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadWatchDogTimeOut(uint8_t id, uint16_t *timeout) {
  uint16_t value;

  if (McuModbus_ReadHoldingRegisters(id, McuHeidelberg_Addr_WatchDogTimeout, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *timeout = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_WriteWatchDogTimeOut(uint8_t id, uint16_t timeoutMs) {
  return McuModbus_WriteHoldingRegister(id, McuHeidelberg_Addr_WatchDogTimeout, timeoutMs);
}

uint8_t McuHeidelberg_ReadStandbyFunctionControl(uint8_t id, uint16_t *control) {
  uint16_t value;

  if (McuModbus_ReadHoldingRegisters(id, McuHeidelberg_Addr_StandbyFunctionControl, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *control = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_WriteStandbyFunctionControl(uint8_t id, bool standbyEnabled) {
  return McuModbus_WriteHoldingRegister(id, McuHeidelberg_Addr_StandbyFunctionControl, standbyEnabled?0:4);
}

uint8_t McuHeidelberg_ReadRemoteLock(uint8_t id, uint16_t *lock) {
  uint16_t value;

  if (McuModbus_ReadHoldingRegisters(id, McuHeidelberg_Addr_RemoteLock, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *lock = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadMaxCurrentCmd(uint8_t id, uint16_t *current) {
  uint16_t value;

  if (McuModbus_ReadHoldingRegisters(id, McuHeidelberg_Addr_MaxCurrentCommand, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *current = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_WriteMaxCurrentCmd(uint8_t id, uint16_t current) {
  if (current>1 && current<60) {
    current = 0; /* not allowed, set to zero */
  }
  if (current>160) {
    current = 160; /* max 16.0 A */
  }
  return McuModbus_WriteHoldingRegister(id, McuHeidelberg_Addr_MaxCurrentCommand, current);
}

uint8_t McuHeidelberg_ReadFailSafeCurrent(uint8_t id, uint16_t *current) {
  uint16_t value;

  if (McuModbus_ReadHoldingRegisters(id, McuHeidelberg_Addr_FailSafeCurrent, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *current = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_WriteFailSafeCurrent(uint8_t id, uint16_t current) {
  if (current>1 && current<60) {
    current = 0; /* not allowed, set to zero */
  }
  if (current>160) {
    current = 160; /* max 16.0 A */
  }
  return McuModbus_WriteHoldingRegister(id, McuHeidelberg_Addr_FailSafeCurrent, current);
}

uint8_t McuHeidelberg_ReadSupportDiagnosticDataItem(uint8_t id, McuHeidelberg_AddrMap_e itemAddr, uint16_t *data) {
  uint16_t value;

  if (itemAddr<McuHeidelberg_Addr_SupportDiagnosticData_Start || itemAddr>McuHeidelberg_Addr_SupportDiagnosticData_End) {
    return ERR_RANGE;
  }
  if (McuModbus_ReadInputRegisters(id, itemAddr, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *data = value;
  return ERR_OK;
}

static uint16_t calculatePowerToChargerDeciAmpere(uint32_t power) {
  return power*10/230/McuHeidelbergInfo.nofPhases;
}

static uint32_t calculateMinWallboxPower(void) {
  return McuHeidelbergInfo.hw.minCurrent*230*McuHeidelbergInfo.nofPhases; /* minimum power setting possible */
}

static uint32_t calculateMaxWallboxPower(void) {
  return McuHeidelbergInfo.hw.maxCurrent*230*McuHeidelbergInfo.nofPhases; /* maximum power setting possible */
}

static uint32_t calculateAvailableSolarPower(void) {
  uint32_t solar, siteOnly, available;

  solar = McuHeidelberg_GetSolarPowerWatt(); /* power produced by the solar panels */
#if McuHeidelberg_CONFIG_SITE_BASE_POWER!=0
  siteOnly = McuHeidelberg_CONFIG_SITE_BASE_POWER;
#else
  siteOnly = McuHeidelberg_GetSiteWithoutChargerPowerWatt(); /* power used by site *without* the charger */
#endif
  /* calculate how much we have available for charging */
  if (solar>siteOnly) { /* more solar power available than currently used? */
    available = solar-siteOnly; /* return difference as surplus */
  } else {
    available = 0;
  }
  McuLog_info("solar: %d, site: %d, site only: %d, charger: %d, available: %d", solar, McuHeidelberg_GetSitePowerWatt(), siteOnly, McuHeidelberg_GetCurrChargerPower(), available);
  return available;
}

static uint32_t calculateChargingWatt(void) {
  uint32_t watt = 0;
  McuHeidelberg_UserChargingMode_e mode = McuHeidelberg_GetUserChargingMode();

  if (mode==McuHeidelberg_User_ChargingMode_Stop) { /* stop charging */
    watt = 0;
  } else if (mode==McuHeidelberg_User_ChargingMode_Slow) { /* only charge with lowest power, slow */
    watt = calculateMinWallboxPower();
  } else if (mode==McuHeidelberg_User_ChargingMode_Fast) { /* only charge with maximum power, fast */
    watt = calculateMaxWallboxPower();
  } else if (mode==McuHeidelberg_User_ChargingMode_SlowPlusPV) { /* charge slow, but increase if solar is available */
    int minPower = calculateMinWallboxPower();
    int availableSolarP = calculateAvailableSolarPower();
    if (availableSolarP>minPower) { /* more solar power available than the minimal amount: use that extra power to charge the vehicle faster */
      watt = availableSolarP;
    } else {
      watt = minPower; /* keep it at the base and minimal level */
    }
  } else if (mode==McuHeidelberg_User_ChargingMode_OnlyPV) { /* only using available solar power */
    int power = calculateMinWallboxPower();
    int availableSolarP = calculateAvailableSolarPower();
    if (availableSolarP>=power) {
      watt = availableSolarP; /* charge with what we have available */
    } else {
      watt = 0; /* stop charging */ /*!\todo: need to use a hysteresis: check for at least a minute */
    }
  }
  /* check current boundaries */
  if (watt < calculateMinWallboxPower()) { /* below minimal possible setting */
    watt = 0;
  } else if (watt > calculateMaxWallboxPower()) { /* above maximum setting */
    watt = calculateMaxWallboxPower();
  }
  return watt;
}

static uint8_t calculateNofActivePhases(void) {
  uint8_t nof;
  uint8_t res;

  res = McuHeidelberg_ReadVoltage(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.voltage[0]);
  if (res!=ERR_OK) {
    McuLog_fatal("failed reading voltage");
    return 1;
  }
  nof = 0;
  for(int i=0; i<sizeof(McuHeidelbergInfo.hw.voltage)/sizeof(McuHeidelbergInfo.hw.voltage[0]); i++) {
    if (McuHeidelbergInfo.hw.voltage[i]>210) { /* voltage above 220V? */
      nof++;
    }
  }
  if (nof<1 || nof>3) { /* should never be the case? */
    McuLog_fatal("failed determine active phases");
    return 1; /* error fallback */
  }
  return nof; /* return number of phases detected */
}

void McuHeidelberg_RegisterEventCallback(McuHeidelberg_EventCallback callback) {
  McuHeidelbergInfo.eventCallback = callback;
}

static void CallEventCallback(McuHeidelberg_Event_e event) {
  if (McuHeidelbergInfo.eventCallback!=NULL) {
    McuHeidelbergInfo.eventCallback(event);
  }
}

McuHeidelbergChargerState_e McuHeidelberg_GetHWChargerState(void) {
  return McuHeidelbergInfo.hw.chargerState;
}

static void McuHeidelberg_SetHWChargerState(uint16_t state) {
  if (McuHeidelbergInfo.hw.chargerState!=state) {
    McuHeidelbergInfo.hw.chargerState = state;
    CallEventCallback(McuHeidelberg_Event_HW_State_Changed);
  }
}

/* -------------------------------------------- */
/* Setter and Getter for available solar power  */
uint32_t McuHeidelberg_GetSolarPowerWatt(void) {
  return McuHeidelbergInfo.solarPowerW;
}

void McuHeidelberg_SetSolarPowerWatt(uint32_t powerW) {
  if (McuHeidelbergInfo.solarPowerW!=powerW) {
    McuHeidelbergInfo.solarPowerW = powerW;
    CallEventCallback(McuHeidelberg_Event_SolarPower_Changed);
    (void)xSemaphoreGive(semNewSolarValue); /* notify task */
  }
}

/* -------------------------------------------- */
/* Setter and Getter for grid power  */
int32_t McuHeidelberg_GetGridPowerWatt(void) {
  return McuHeidelbergInfo.gridPowerW;
}

void McuHeidelberg_SetGridPowerWatt(int32_t powerW) {
  if (McuHeidelbergInfo.gridPowerW!=powerW) {
    McuHeidelbergInfo.gridPowerW = powerW;
    CallEventCallback(McuHeidelberg_Event_GridPower_Changed);
  }
}
/* -------------------------------------------- */
/* Setter and Getter for power used by site  */
uint32_t McuHeidelberg_GetSitePowerWatt(void) {
  return McuHeidelbergInfo.sitePowerW;
}

void McuHeidelberg_SetSitePowerWatt(uint32_t powerW) {
  if (McuHeidelbergInfo.sitePowerW!=powerW) {
    McuHeidelbergInfo.sitePowerW = powerW;
    CallEventCallback(McuHeidelberg_Event_SitePower_Changed);
  }
}

uint32_t McuHeidelberg_GetSiteWithoutChargerPowerWatt(void) {
  uint32_t chargerW = McuHeidelberg_GetCurrChargerPower();
  uint32_t siteW = McuHeidelberg_GetSitePowerWatt();
  uint32_t power;

  if (chargerW==0) { /* charger not active */
    power = siteW;
  } else if (siteW>chargerW) { /* normal charging */
    power = siteW-chargerW;
  } else { /* the value from MQTT does not sum up? Maybe charger watts have not been included in site yet */
    power = siteW; /* assuming what we have as site watt */
  }
  return power;
}

/* -------------------------------------------- */
/* Setter and Getter for maximum charging current     */
uint32_t McuHeidelberg_GetMaxCarPower(void) {
  return McuHeidelbergInfo.maxCarPowerW;
}

static void McuHeidelberg_SetMaxCarPower(uint32_t power) {
  /* sets the maximum current to be provided by the charger */
  if (McuHeidelbergInfo.maxCarPowerW!=power) {
    uint16_t dA = calculatePowerToChargerDeciAmpere(power);
    if (McuHeidelberg_WriteMaxCurrentCmd(McuHeidelberg_deviceID, dA)!=ERR_OK) {
      McuLog_error("failed writing max current");
      power = 0;
    }
    McuHeidelbergInfo.maxCarPowerW = power;
  }
}

uint32_t McuHeidelberg_GetCurrChargerPower(void) {
  return McuHeidelbergInfo.hw.power;
}

static void McuHeidelberg_UpdateCurrChargerPower(void) {
  uint16_t power;

  if (McuHeidelberg_ReadPower(McuHeidelberg_deviceID, &power)!=ERR_OK) {
    McuLog_error("failed reading charger power");
    McuHeidelbergInfo.hw.power = 0;
  } else if (power != McuHeidelbergInfo.hw.power) {
    McuHeidelbergInfo.hw.power = power;
  }
  CallEventCallback(McuHeidelberg_Event_ChargerPower_Changed);
}

static void readStatusRegisters(void) {
  if (McuHeidelberg_ReadCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.current[0])!=ERR_OK) {
    McuLog_error("failed reading current");
  }
  if (McuHeidelberg_ReadTemperature(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.temperature)!=ERR_OK) {
    McuLog_error("failed reading temperature");
  }
  if (McuHeidelberg_ReadVoltage(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.voltage[0])!=ERR_OK) {
    McuLog_error("failed reading voltage");
  }
  if (McuHeidelberg_ReadLockstate(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.lockState)!=ERR_OK) {
    McuLog_error("failed reading lockstate");
  }
  if (McuHeidelberg_ReadPower(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.power)!=ERR_OK) {
    McuLog_error("failed reading power");
  }
  if (McuHeidelberg_ReadEnergySincePowerOn(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.energySincePowerOn)!=ERR_OK) {
    McuLog_error("failed reading energy since power-on");
  }
  if (McuHeidelberg_ReadEnergySinceInstallation(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.energySinceInstallation)!=ERR_OK) {
    McuLog_error("failed reading energy since installation");
  }
  calculateNofActivePhases();
}

static void resetHardwareDataValues(void) {
  McuHeidelbergInfo.hw.current[0] = 0;
  McuHeidelbergInfo.hw.current[1] = 0;
  McuHeidelbergInfo.hw.current[2] = 0;
  McuHeidelbergInfo.hw.temperature = 0;
  McuHeidelbergInfo.hw.voltage[0] = 0;
  McuHeidelbergInfo.hw.voltage[1] = 0;
  McuHeidelbergInfo.hw.voltage[2] = 0;

  McuHeidelbergInfo.hw.power = 0;
  McuHeidelberg_UpdateCurrChargerPower();
}

/* -------------------------------------------- */
/* Setter and Getter for user charging mode     */
McuHeidelberg_UserChargingMode_e McuHeidelberg_GetUserChargingMode(void) {
  return McuHeidelbergInfo.userChargingMode;
}

void McuHeidelberg_SetUserChargingMode(McuHeidelberg_UserChargingMode_e mode) {
  if (McuHeidelbergInfo.userChargingMode!=mode) {
    McuHeidelberg_SetMaxCarPower(0); /* set initial charger current to zero */
    readStatusRegisters(); /* read in again the status register to have a good and clean state */
    McuHeidelbergInfo.userChargingMode = mode;
    CallEventCallback(McuHeidelberg_Event_UserChargingMode_Changed);
  }
}

static void wallboxTask(void *pv) {
  uint8_t res;
  uint16_t prevHWchargerState = 0;
  uint16_t prevChargingWatt = 0; /* previous charging power in Watt */
  uint16_t currChargingWatt = 0; /* current charging power in Watt */

  McuHeidelbergInfo.isActive = false;
  McuHeidelbergInfo.state = Wallbox_TaskState_None;
  McuHeidelbergInfo.userChargingMode = McuHeidelberg_CONFIG_DEFAULT_CHARGING_MODE;
#if McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
  mock.hwChargerState = McuHeidelberg_ChargerState_A1;
#endif
/*
 * With the car plugged in, the charging state jumps to 4 (McuHeidelberg_ChargerState_B1).
 * Then write every second the load current into register 261 (McuHeidelberg_Addr_MaxCurrentCommand).
 * The charging state jumps to 7 (McuHeidelberg_ChargerState_C2) (charging).
 * To stop the charging, write 0 to register 261 (McuHeidelberg_Addr_MaxCurrentCommand).
 */
  for(;;) {
    if (xSemaphoreTake(semNewSolarValue, pdMS_TO_TICKS(1000))==pdTRUE) { /* standard delay time, or notification received */
      McuLog_trace("new solar value received");
    }

    if (McuHeidelbergInfo.state!=Wallbox_TaskState_None) { /* as soon as we have a connection, check the wallbox state for changes */
      uint16_t HWchargerState;
      if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &HWchargerState)==ERR_OK) {
        McuHeidelberg_SetHWChargerState(HWchargerState); /* store state we got */
        if (prevHWchargerState != HWchargerState) { /* state changed? */
          McuLog_trace("wallbox state changed from %s (%d) to %s (%d)", McuHeidelberg_GetShortHWChargerStateString(prevHWchargerState), prevHWchargerState, McuHeidelberg_GetShortHWChargerStateString(HWchargerState), HWchargerState);
          McuHeidelberg_UpdateCurrChargerPower(); /* update values, as state has changed */
          prevHWchargerState = HWchargerState;
        }
      } else {
        McuLog_error("failed to get charger state");
        McuHeidelbergInfo.state = Wallbox_TaskState_Error;
      }
    }

    switch(McuHeidelbergInfo.state) {
      case Wallbox_TaskState_None:
        McuHeidelbergInfo.isActive = false;
        /* no state yet: probe layout register to check if we can reach the charger */
        res = McuHeidelberg_ReadRegisterLayoutVersion(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.version);
        if (res==ERR_OK) {
          McuLog_info("connected with charger");
          McuHeidelbergInfo.isActive = true;
          McuHeidelbergInfo.state = Wallbox_TaskState_Connected;
          /* read static values from wallbox */
          if (McuHeidelberg_ReadHardwareMinCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.minCurrent)!=ERR_OK) {
            McuLog_error("failed reading min current");
          }
          if (McuHeidelberg_ReadHardwareMaxCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.maxCurrent)!=ERR_OK) {
            McuLog_error("failed reading max current");
          }
          /* read other dynamic values the first time */
          uint16_t val;

          if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &val)==ERR_OK) {
            McuHeidelberg_SetHWChargerState(val); /* store state we got */
            prevHWchargerState = val;
          } else {
            McuLog_error("failed reading device ID");
          }
          if (McuHeidelberg_ReadCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.current[0])!=ERR_OK) {
            McuLog_error("failed reading current");
          }
          if (McuHeidelberg_ReadTemperature(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.temperature)!=ERR_OK) {
            McuLog_error("failed reading temperature");
          }
          if (McuHeidelberg_ReadVoltage(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.voltage[0])!=ERR_OK) {
            McuLog_error("failed reading voltage");
          }
          if (McuHeidelberg_ReadLockstate(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.lockState)!=ERR_OK) {
            McuLog_error("failed reading lockstate");
          }
          if (McuHeidelberg_ReadPower(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.power)!=ERR_OK) {
            McuLog_error("failed reading power");
          }
          if (McuHeidelberg_ReadEnergySincePowerOn(McuHeidelberg_deviceID, &McuHeidelbergInfo.hw.energySincePowerOn)!=ERR_OK) {
            McuLog_error("failed reading energy");
          }
          /* determine the number of active phases */
          McuHeidelbergInfo.nofPhases = calculateNofActivePhases();
          McuHeidelberg_SetMaxCarPower(calculateMinWallboxPower()); /* set initial charging value */
        } else {
          resetHardwareDataValues();
          McuLog_error("communication failed, charger in standby? Retry in 30 seconds...");
          vTaskDelay(pdMS_TO_TICKS(30000)); /* need to poll the device on a regular base, otherwise it goes into communication error state */
        }
        break;

      case Wallbox_TaskState_Connected:
         switch(McuHeidelbergInfo.hw.chargerState) {
          case McuHeidelberg_ChargerState_A1:
          case McuHeidelberg_ChargerState_A2:
            /* no vehicle plugged, stay in current state */
            break;

          case McuHeidelberg_ChargerState_B1:
          case McuHeidelberg_ChargerState_B2:
          case McuHeidelberg_ChargerState_C1:
          case McuHeidelberg_ChargerState_C2:
            McuLog_info("vehicle plugged");
            McuHeidelbergInfo.state = Wallbox_TaskState_Vehicle_Plugged;
            break;

          case McuHeidelberg_ChargerState_Derating:
          case McuHeidelberg_ChargerState_E:
          case McuHeidelberg_ChargerState_F:
          case McuHeidelberg_ChargerState_Error:
          default:
            McuHeidelbergInfo.state = Wallbox_TaskState_Error; /* error case */
            break;
        } /* switch */
        break;

      case Wallbox_TaskState_Vehicle_Plugged:
        switch(McuHeidelbergInfo.hw.chargerState) {
          case McuHeidelberg_ChargerState_A1:
          case McuHeidelberg_ChargerState_A2:
            McuLog_trace("vehicle not plugged any more");
            McuHeidelbergInfo.state = Wallbox_TaskState_Connected;
            break;

          case McuHeidelberg_ChargerState_B1: /* plugged, no charging request, but charging not possible */
            currChargingWatt = calculateChargingWatt();
            if (currChargingWatt!=prevChargingWatt) {
              McuLog_info("B1, setting charging power to %d W", currChargingWatt);
              McuHeidelberg_SetMaxCarPower(currChargingWatt);
              prevChargingWatt = currChargingWatt;
            }
            vTaskDelay(pdMS_TO_TICKS(5000));
            break;

          case McuHeidelberg_ChargerState_B2: /* plugged, no charging request, charging possible */
            /* vehicle plugged, but no charging request: stay in this state */
            break;

          case McuHeidelberg_ChargerState_C1:
            /* charging request from vehicle, but wallbox does not allow charging: stay here */
            break;

          case McuHeidelberg_ChargerState_C2:
            McuLog_trace("vehicle plugged, with charging request");
            McuHeidelbergInfo.state = Wallbox_TaskState_Vehicle_Start_Charging;
            break;

          case McuHeidelberg_ChargerState_Derating:
          case McuHeidelberg_ChargerState_E:
          case McuHeidelberg_ChargerState_F:
          case McuHeidelberg_ChargerState_Error:
          default:
            McuHeidelbergInfo.state = Wallbox_TaskState_Error; /* error case */
            break;
        } /* switch */
        break;

      case Wallbox_TaskState_Vehicle_Start_Charging:
        McuLog_info("start charging");
        currChargingWatt = calculateChargingWatt();
        McuLog_info("setting charging power to %d W", currChargingWatt);
        McuHeidelberg_SetMaxCarPower(currChargingWatt);
        prevChargingWatt = currChargingWatt;
        McuHeidelbergInfo.state = Wallbox_TaskState_Vehicle_Charging;
        break;

      case Wallbox_TaskState_Vehicle_Charging:
        switch(McuHeidelbergInfo.hw.chargerState) {
          case McuHeidelberg_ChargerState_A1:
          case McuHeidelberg_ChargerState_A2:
            McuLog_trace("vehicle not plugged any more");
            McuHeidelbergInfo.state = Wallbox_TaskState_Connected;
            McuHeidelberg_UpdateCurrChargerPower(); /* update current charging power from hardware */
            vTaskDelay(pdMS_TO_TICKS(1000)); /* control loop delay */
            break;

          case McuHeidelberg_ChargerState_B1:
          case McuHeidelberg_ChargerState_B2:
            McuLog_trace("vehicle plugged, but dropped charging request");
            McuHeidelbergInfo.state = Wallbox_TaskState_Connected;
            McuHeidelberg_UpdateCurrChargerPower(); /* update current charging power from hardware */
            vTaskDelay(pdMS_TO_TICKS(1000)); /* control loop delay */
            break;

          case McuHeidelberg_ChargerState_C1:
          case McuHeidelberg_ChargerState_C2:
            /* vehicle plugged, with charging request: stay in this state */
            McuHeidelberg_UpdateCurrChargerPower(); /* update current charging power from hardware */
            vTaskDelay(pdMS_TO_TICKS(1000)); /* control loop delay */
            break;

          case McuHeidelberg_ChargerState_Derating:
            McuLog_trace("de-rating while charging, waiting 5 seconds");
            vTaskDelay(pdMS_TO_TICKS(5000));
            break;
          case McuHeidelberg_ChargerState_E:
          case McuHeidelberg_ChargerState_F:
          case McuHeidelberg_ChargerState_Error:
          default:
            McuHeidelbergInfo.state = Wallbox_TaskState_Error; /* error case */
            break;
        } /* switch */
        if (McuHeidelbergInfo.hw.chargerState==McuHeidelberg_ChargerState_C2) { /* in active charging state? */
          static TickType_t lastTicksCount = 0;
          TickType_t currTicksCount = xTaskGetTickCount();
          if (currTicksCount >= lastTicksCount+(McuHeidelberg_CONFIG_CHARGING_CALC_PERIOD_SEC*pdMS_TO_TICKS(1000))) { /* only do new calculation with given period */
            lastTicksCount = currTicksCount;
            /* calculate possible charging level */
            McuHeidelberg_UpdateCurrChargerPower(); /* update current charging power from hardware */
            currChargingWatt = calculateChargingWatt();
            if (currChargingWatt!=prevChargingWatt) {
              int diff;

              if (currChargingWatt>prevChargingWatt) {
                diff = currChargingWatt-prevChargingWatt;
              } else {
                diff = prevChargingWatt-currChargingWatt;
              }
              #define MIN_DIFF_POWER_W  (500)

              if (diff>=MIN_DIFF_POWER_W || currChargingWatt==0) {
                McuLog_info("diff > %d W, changing charging power from %d W to %d W", MIN_DIFF_POWER_W, prevChargingWatt, currChargingWatt);
                McuHeidelberg_SetMaxCarPower(currChargingWatt); /* tell hardware to change charging */
                prevChargingWatt = currChargingWatt;
              }
            }
          }
        }
        break;

      case Wallbox_TaskState_Vehicle_Stop_Charging:
        McuLog_info("stop charging");
        McuHeidelberg_SetMaxCarPower(0); /* stop charging */
        McuHeidelbergInfo.state = Wallbox_TaskState_Connected;
        break;

      case Wallbox_TaskState_Error:
        McuLog_error("error, stop charging, reinitializing");
        McuHeidelberg_SetMaxCarPower(0); /* stop charging */
        McuHeidelbergInfo.state = Wallbox_TaskState_None;
        break;

      default:
        break;
    } /* switch */
  }
}

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[96];
  uint16_t value16u;

  readStatusRegisters(); /* read hardware registers into McuHeidelbergInfo.hw so we can use them below */
  McuShell_SendStatusStr((unsigned char*)"McuHeidelberg", (unsigned char*)"Heidelberg wallbox status\r\n", io->stdOut);

  McuShell_SendStatusStr((unsigned char*)"  wallbox", McuHeidelbergInfo.isActive?(unsigned char*)"active\r\n":(unsigned char*)"standby or powered off\r\n", io->stdOut);

  McuUtility_Num8uToStr(buf, sizeof(buf), McuHeidelberg_deviceID);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  Modbus addr", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), McuHeidelberg_GetStateString(McuHeidelbergInfo.state));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  state", buf, io->stdOut);

  McuHeidelberg_UserChargingMode_e mode = McuHeidelberg_GetUserChargingMode();
  McuUtility_Num16uToStr(buf, sizeof(buf), mode);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": ");
  McuUtility_strcat(buf, sizeof(buf), McuHeidelberg_GetUserChargingModeString(mode));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  user mode", buf, io->stdOut);

  McuUtility_Num8uToStr(buf, sizeof(buf), McuHeidelbergInfo.nofPhases);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (detected)\r\n");
  McuShell_SendStatusStr((unsigned char*)"  nof phases", buf, io->stdOut);

  McuUtility_Num32sToStrFormatted(buf, sizeof(buf), McuHeidelberg_GetGridPowerWatt(), ' ', 6);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W\r\n");
  McuShell_SendStatusStr((unsigned char*)"  grid", buf, io->stdOut);

  McuUtility_Num32uToStrFormatted(buf, sizeof(buf), McuHeidelberg_GetSolarPowerWatt(), ' ', 6);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W\r\n");
  McuShell_SendStatusStr((unsigned char*)"  solar", buf, io->stdOut);

  McuUtility_Num32uToStrFormatted(buf, sizeof(buf), McuHeidelberg_GetSitePowerWatt(), ' ', 6);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W, without charger: ");

  McuUtility_strcatNum32u(buf, sizeof(buf), McuHeidelberg_GetSiteWithoutChargerPowerWatt());
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W\r\n");
  McuShell_SendStatusStr((unsigned char*)"  site", buf, io->stdOut);

  McuUtility_Num32uToStrFormatted(buf, sizeof(buf), McuHeidelberg_CONFIG_SITE_BASE_POWER, ' ', 6);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W\r\n");
  McuShell_SendStatusStr((unsigned char*)"  SITE_BASE", buf, io->stdOut);

  uint32_t powerW = McuHeidelberg_GetMaxCarPower();
  uint16_t dA = calculatePowerToChargerDeciAmpere(powerW);
  McuUtility_Num32uToStrFormatted(buf, sizeof(buf), powerW, ' ', 6);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W, Imax ");
  McuUtility_strcatNum16uFormatted(buf, sizeof(buf), dA/10, ' ', 2);
  McuUtility_chcat(buf, sizeof(buf), '.');
  McuUtility_strcatNum16uFormatted(buf, sizeof(buf), dA%10, '0', 1);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
  McuShell_SendStatusStr((unsigned char*)"  charge max", buf, io->stdOut);

  McuUtility_Num32sToStrFormatted(buf, sizeof(buf), McuHeidelberg_GetCurrChargerPower(), ' ', 6);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W reported by charger\r\n");
  McuShell_SendStatusStr((unsigned char*)"  charge curr", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[  4] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), McuHeidelbergInfo.hw.version);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  HW version", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[  5] ");
  if (McuHeidelbergInfo.isActive) {
    McuHeidelbergChargerState_e chargerState = McuHeidelberg_GetHWChargerState();
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), chargerState);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ");
    McuUtility_strcat(buf, sizeof(buf), McuHeidelberg_GetHWChargerStateString(chargerState));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  HW state", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[  6] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.hw.current[0]/10, ' ', 2);
    McuUtility_chcat(buf, sizeof(buf), '.');
    McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.hw.current[0]%10, '0', 1);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A, [ 10] ");
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.voltage[0]);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" V rms\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  L1", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[  7] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.hw.current[1]/10, ' ', 2);
    McuUtility_chcat(buf, sizeof(buf), '.');
    McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.hw.current[1]%10, '0', 1);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A, [ 11] ");
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.voltage[1]);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" V rms\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  L2", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[  8] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.hw.current[2]/10, ' ', 2);
    McuUtility_chcat(buf, sizeof(buf), '.');
    McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.hw.current[2]%10, '0', 1);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A, [ 12] ");
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.voltage[2]);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" V rms\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  L3", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[  9] ");
  if (McuHeidelbergInfo.isActive) {
    int16_t val = McuHeidelbergInfo.hw.temperature;
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.temperature/10);
    McuUtility_chcat(buf, sizeof(buf), '.');
    if (val<0) {
      val = -val;
    }
    McuUtility_chcat(buf, sizeof(buf), '0'+(val%10));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" C (PCB)\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  temperature", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[ 13] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.lockState);
    if (McuHeidelbergInfo.hw.lockState==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": system locked\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": system unlocked\r\n");
    }
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  lock", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[ 14] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.power);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W (sum of all phases)\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  power", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[ 15] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum32u(buf, sizeof(buf), McuHeidelbergInfo.hw.energySincePowerOn);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" Wh (since power-on)\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  energy", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[ 17] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum32u(buf, sizeof(buf), McuHeidelbergInfo.hw.energySinceInstallation);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" Wh (since installation)\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  energy", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[100] ");
  if (McuHeidelbergInfo.isActive) {
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.minCurrent);
    McuUtility_chcat(buf, sizeof(buf), '-');
    McuUtility_strcatNum16u(buf, sizeof(buf), McuHeidelbergInfo.hw.maxCurrent);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  I min-max", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[200] ");
  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadHardwareVariant(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value16u);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  HW variant", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[203] ");
  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadApplicationSoftwareRevision(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value16u);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  SW revision", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[257] ");
  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadWatchDogTimeOut(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    if (value16u==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0 (disabled Modbus timeout)\r\n");
    } else {
      McuUtility_strcatNum16u(buf, sizeof(buf), value16u/1000);
      McuUtility_chcat(buf, sizeof(buf), '.');
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u%1000, '0', 3);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" s Modbus timeout\r\n");
    }
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  WDT timeout", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[258] ");
  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadStandbyFunctionControl(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_strcatNum16u(buf, sizeof(buf), value16u);
    if (value16u==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (enabled, power saving if no car is connected)\r\n");
    } else if (value16u==4) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (disabled)\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (illegal value)\r\n");
    }
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  standby", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[259] ");
  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadRemoteLock(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_strcatNum16u(buf, sizeof(buf), value16u);
    if (value16u==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (locked)\r\n");
    } else if (value16u==1) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (unlocked)\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (illegal value)\r\n");
    }
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  remote lock", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[261] ");
  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadMaxCurrentCmd(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    if (value16u==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0 A (no charging possible)\r\n");
    } else if (value16u<60) {
      McuUtility_strcatNum16u(buf, sizeof(buf), value16u);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" not allowed (no charging possible)\r\n");
    } else {
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u/10, ' ', 2);
      McuUtility_chcat(buf, sizeof(buf), '.');
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u%10, '0', 1);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
    }
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  I max cmd", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"[262] ");
  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadFailSafeCurrent(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    if (value16u==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"0 A (no charging possible)\r\n");
    } else if (value16u<60) {
      McuUtility_strcatNum16u(buf, sizeof(buf), value16u);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" not allowed (no charging possible)\r\n");
    } else {
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u/10, ' ', 2);
      McuUtility_chcat(buf, sizeof(buf), '.');
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u%10, '0', 1);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
    }
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  I failsafe", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuHeidelberg", (unsigned char*)"Group of McuHeidelberg wallbox commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  standby on|off", (unsigned char*)"Enable or disable standby function\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  show logistic", (unsigned char*)"Show logistic string\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  show diagnostic", (unsigned char*)"Show support diagnostic data\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set timeout <ms>", (unsigned char*)"Set WDT standby timeout\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set Imax <dA>", (unsigned char*)"Set max charging current in deci-amps (0 or 60-160), e.g. 60 for 6.0 A\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set Ifail <dA>", (unsigned char*)"Set failsafe current in case of comm lost, in deci-amps (0 or 60-160), e.g. 60 for 6.0 A\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set charge mode <m>", (unsigned char*)"Set user charge mode: 0 (stop), 1 (PV only), 2 (slow), 3 (slow+PV), 4 (fast) \r\n", io->stdOut);
#if McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
  McuShell_SendHelpStr((unsigned char*)"  setmock state <value>", (unsigned char*)"Set mock hardware state register value (2-11)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  setmock phases <nof>", (unsigned char*)"Set mock number of phases (1-3)\r\n", io->stdOut);
#endif
#if McuHeidelberg_CONFIG_USE_MOCK_SOLAR
  McuShell_SendHelpStr((unsigned char*)"  setmock solar <w>", (unsigned char*)"Set mock solar panel power value (W)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  setmock site <w>", (unsigned char*)"Set mock site or residual power value (W)\r\n", io->stdOut);
#endif
  return ERR_OK;
}

uint8_t McuHeidelberg_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  uint16_t val16u;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP)==0 || McuUtility_strcmp((char*)cmd, "McuHeidelberg help")==0) {
    *handled = true;
    return PrintHelp(io);
  } else if ((McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0) || (McuUtility_strcmp((char*)cmd, "McuHeidelberg status")==0)) {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuHeidelberg show logistic")==0) {
    *handled = true;
    uint8_t res;
    unsigned char buf[32];

    res = McuHeidelberg_ReadLogisticString(McuHeidelberg_deviceID, buf, sizeof(buf));
    if (res!=ERR_OK) {
      return res;
    }
    McuShell_SendStr(buf, io->stdOut);
    return ERR_OK;
  } else if (McuUtility_strcmp((char*)cmd, "McuHeidelberg show diagnostic")==0) {
    uint16_t value;
    uint8_t res;
    uint8_t buf[8];

    *handled = true;
    for(int addr=McuHeidelberg_Addr_SupportDiagnosticData_Start; addr<=McuHeidelberg_Addr_SupportDiagnosticData_End; addr++) {
      res = McuHeidelberg_ReadSupportDiagnosticDataItem(McuHeidelberg_deviceID, addr, &value);
      if (res!=ERR_OK) {
        McuShell_SendStr((unsigned char*)"failed!\r\n", io->stdOut);
        break;
      }
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
      McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
      McuUtility_chcat(buf, sizeof(buf), ' ');
      McuShell_SendStr(buf, io->stdOut);
    } /* for */
    McuShell_SendStr((unsigned char*)"\r\n", io->stdOut);
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg set timeout ", sizeof("McuHeidelberg set timeout ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg set timeout ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuHeidelberg_WriteWatchDogTimeOut(McuHeidelberg_deviceID, val16u);
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg set Imax ", sizeof("McuHeidelberg set Imax ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg set Imax ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)!=ERR_OK && !(val16u==0 || (val16u>=60 && val16u<=160))) {
      return ERR_FAILED;
    }
    return McuHeidelberg_WriteMaxCurrentCmd(McuHeidelberg_deviceID, val16u);
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg set Ifail ", sizeof("McuHeidelberg set Ifail ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg set Ifail ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)!=ERR_OK && !(val16u==0 || (val16u>=60 && val16u<=160))) {
      return ERR_FAILED;
    }
    return McuHeidelberg_WriteFailSafeCurrent(McuHeidelberg_deviceID, val16u);
  } else if (McuUtility_strcmp((char*)cmd, "McuHeidelberg standby on")==0) {
    *handled = true;
    return McuHeidelberg_WriteStandbyFunctionControl(McuHeidelberg_deviceID, true);
  } else if (McuUtility_strcmp((char*)cmd, "McuHeidelberg standby off")==0) {
    *handled = true;
    return McuHeidelberg_WriteStandbyFunctionControl(McuHeidelberg_deviceID, false);
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg set charge mode ", sizeof("McuHeidelberg set charge mode ")-1)==0) {
     *handled = true;
     p = cmd+sizeof("McuHeidelberg set charge mode ")-1;
     if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK && val16u>=0 && val16u<McuHeidelberg_User_ChargingMode_NofChargingMode) {
       McuHeidelberg_SetUserChargingMode(val16u);
       return ERR_OK;
     }
     return ERR_FAILED;
#if McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg setmock state ", sizeof("McuHeidelberg setmock state ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg setmock state ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK && (val16u>=2 && val16u<=11)) {
      mock.hwChargerState = val16u;
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg setmock phases ", sizeof("McuHeidelberg setmock phases ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg setmock phases ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK && val16u>=1 && val16u<=3) {
      McuHeidelbergInfo.nofPhases = val16u;
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if McuHeidelberg_CONFIG_USE_MOCK_SOLAR
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg setmock solar ", sizeof("McuHeidelberg setmock solar ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg setmock solar ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      McuHeidelberg_SetSolarPowerWatt(val16u);
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if McuHeidelberg_CONFIG_USE_MOCK_SOLAR
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg setmock site ", sizeof("McuHeidelberg setmock site ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg setmock site ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      McuHeidelberg_SetSitePowerWatt(val16u);
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
  }
  return ERR_OK;
}

void McuHeidelberg_Deinit(void) {
  /* nothing needed */
}

void McuHeidelberg_Init(void) {
  if (xTaskCreate(
       wallboxTask,  /* pointer to the task */
       "wallbox", /* task name for kernel awareness debugging */
       1500/sizeof(StackType_t), /* task stack size */
       (void*)NULL, /* optional task startup argument */
       tskIDLE_PRIORITY+4,  /* initial priority */
       (TaskHandle_t*)NULL /* optional task handle to create */
     ) != pdPASS)
   {
     McuLog_fatal("Failed creating task");
     for(;;){} /* error! probably out of memory */
   }
  semNewSolarValue = xSemaphoreCreateBinary();
  if (semNewSolarValue==NULL) {
    McuLog_fatal("Failed creating semaphore");
    for(;;){} /* error! probably out of memory */
  }
  vQueueAddToRegistry(semNewSolarValue, "semNewSolarValue");
}

#endif /* McuLib_CONFIG_SDK_USE_FREERTOS */
