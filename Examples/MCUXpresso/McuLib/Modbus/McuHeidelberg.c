/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "McuHeidelberg.h"
#include "McuShell.h"
#include "McuUtility.h"
#include "McuModbus.h"
#include "McuRTOS.h"
#include "McuLog.h"

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

/* state of the hardware wallbox */
typedef enum ChargingState_e {
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
} ChargingState_e;

/* state of the wallbox task */
typedef enum WallboxState_e {
  Wallbox_State_None,
  Wallbox_State_Connected,
  Wallbox_State_Vehicle_Plugged,
  Wallbox_State_Vehicle_Start_Charging,
  Wallbox_State_Vehicle_Charging,
  Wallbox_State_Vehicle_Stop_Charging,
  Wallbox_State_Error,
} WallboxState_e;

/* types of charging strategies and modes */
typedef enum ChargingMode_e {
  ChargingMode_Stop,        /* stop immediately the charging */
  ChargingMode_Fast,        /* charge immediately with maximum power */
  ChargingMode_Slow,        /* charge immediately with the minimal power */
  ChargingMode_SlowPlusPV,  /* charge immediately with the minimal power. If PV supports more power, the power level gets increased */
  ChargingMode_OnlyPV,      /* charge only with the PV power available */
  ChargingMode_NofChargingMode, /* sentinel, must be last in list! */
} ChargingMode_e;

static struct McuHeidelbergInfo_s {
  WallboxState_e state;         /* state of the wallbox task */
  ChargingMode_e chargingMode;  /* selected charging mode */
  uint32_t solarPowerW;         /* available solar power in Watt (note: solar minus site!) */
  uint8_t nofPhases;            /* number of active phases */
  bool isActive;                /* if unit is in standby or not */
  uint16_t version;             /* register layout version */
  uint16_t chargingState;       /* wallbox charging state */
  uint16_t minCurrent;          /* minimal current, as configured by the hardware switch, 6 A up to 16 A */
  uint16_t maxCurrent;          /* maximal current, as configured by the hardware switch, 6 A up to 16 A */
  uint16_t current[3];          /* RMS current of the three phases, in 0.1 A units */
  int16_t temperature;          /* PCB temperature, in 0.1 degree C */
  uint16_t voltage[3];          /* RMS voltage of the three phases, in 0.1 A units */
  uint16_t lockState;           /* external lock */
  uint16_t power;               /* sum of power of all three phases */
  uint32_t energySincePowerOn;  /* energy since last standby or power-off */
} McuHeidelbergInfo;

#define McuHeidelberg_CONFIG_USE_MOCK  (1) /*!< if using testing mocks */

#if McuHeidelberg_CONFIG_USE_MOCK
static struct mock {
  uint16_t chargingState; /* wallbox charging state */
} mock;
#endif

const unsigned char *McuHeidelberg_GetChargingStateString(uint16_t state) {
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

static const unsigned char *McuHeidelberg_GetStateString(WallboxState_e state) {
  const unsigned char *str;
  switch(state) {
    case Wallbox_State_None:                  str = (unsigned char*)"none"; break;
    case Wallbox_State_Connected:             str = (unsigned char*)"connected"; break;
    case Wallbox_State_Vehicle_Plugged:       str = (unsigned char*)"vehicle plugged"; break;
    case Wallbox_State_Vehicle_Start_Charging:str = (unsigned char*)"start charging"; break;
    case Wallbox_State_Vehicle_Charging:      str = (unsigned char*)"vehicle charging"; break;
    case Wallbox_State_Vehicle_Stop_Charging: str = (unsigned char*)"stop charging"; break;
    case Wallbox_State_Error:                 str = (unsigned char*)"error"; break;
    default:                                  str = (unsigned char*)"ERROR, unknown state!"; break;
  }
  return str;
}

static const unsigned char *McuHeidelberg_GetChargingMode(ChargingMode_e mode) {
  const unsigned char *str;
  switch(mode) {
    case ChargingMode_Stop:         str = (unsigned char*)"stop"; break;
    case ChargingMode_Fast:         str = (unsigned char*)"fast"; break;
    case ChargingMode_Slow:         str = (unsigned char*)"slow"; break;
    case ChargingMode_SlowPlusPV:   str = (unsigned char*)"slow plus PV"; break;
    case ChargingMode_OnlyPV:       str = (unsigned char*)"only PV"; break;
    default:                        str = (unsigned char*)"ERROR, unknown mode!"; break;
  }
  return str;
}

uint8_t McuHeidelberg_ReadRegisterLayoutVersion(uint8_t id, uint16_t *version) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_ModbusRegisterLayoutVersion, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *version = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadChargingState(uint8_t id, uint16_t *state) {
#if McuHeidelberg_CONFIG_USE_MOCK
  *state = mock.chargingState;
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
    current[0] = value;
  } else {
    return ERR_FAILED;
  }
  if (McuModbus_ReadInputRegisters(McuHeidelberg_deviceID, McuHeidelberg_Addr_Current_L3, 1, &value)==ERR_OK) {
    current[0] = value;
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

static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  unsigned char buf[96];
  uint32_t value32u;
  uint16_t value16u;

  McuShell_SendStatusStr((unsigned char*)"McuHeidelberg", (unsigned char*)"Heidelberg wallbox settings\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), McuHeidelberg_GetStateString(McuHeidelbergInfo.state));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  task state", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.chargingMode);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": ");
  McuUtility_strcat(buf, sizeof(buf), McuHeidelberg_GetChargingMode(McuHeidelbergInfo.chargingMode));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  charge mode", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), McuHeidelbergInfo.nofPhases);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  phases", buf, io->stdOut);

  McuUtility_Num32uToStr(buf, sizeof(buf), McuHeidelbergInfo.solarPowerW);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W\r\n");
  McuShell_SendStatusStr((unsigned char*)"  solar power", buf, io->stdOut);

  McuShell_SendStatusStr((unsigned char*)"  wallbox", McuHeidelbergInfo.isActive?(unsigned char*)"active\r\n":(unsigned char*)"standby or powered off\r\n", io->stdOut);

  McuUtility_Num8uToStr(buf, sizeof(buf), McuHeidelberg_deviceID);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  Modbus ID", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum16Hex(buf, sizeof(buf), McuHeidelbergInfo.version);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  version", buf, io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum16Hex(buf, sizeof(buf), McuHeidelbergInfo.chargingState);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" ");
  McuUtility_strcat(buf, sizeof(buf), McuHeidelberg_GetChargingStateString(McuHeidelbergInfo.chargingState));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  state", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.current[0]/10);
  McuUtility_chcat(buf, sizeof(buf), '.');
  McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.current[0]%10, '0', 1);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A rms\r\n");
  McuShell_SendStatusStr((unsigned char*)"  L1", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.current[1]/10);
  McuUtility_chcat(buf, sizeof(buf), '.');
  McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.current[1]%10, '0', 1);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A rms\r\n");
  McuShell_SendStatusStr((unsigned char*)"  L2", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.current[2]/10);
  McuUtility_chcat(buf, sizeof(buf), '.');
  McuUtility_strcatNum16uFormatted(buf, sizeof(buf), McuHeidelbergInfo.current[2]%10, '0', 1);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A rms\r\n");
  McuShell_SendStatusStr((unsigned char*)"  L3", buf, io->stdOut);

  int16_t val = McuHeidelbergInfo.temperature;
  McuUtility_Num16sToStr(buf, sizeof(buf), McuHeidelbergInfo.temperature/10);
  McuUtility_chcat(buf, sizeof(buf), '.');
  if (val<0) {
    val = -val;
  }
  McuUtility_chcat(buf, sizeof(buf), '0'+(val%10));
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" C\r\n");
  McuShell_SendStatusStr((unsigned char*)"  temperature", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.voltage[0]);
   McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" V rms\r\n");
  McuShell_SendStatusStr((unsigned char*)"  L1", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.voltage[1]);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" V rms\r\n");
  McuShell_SendStatusStr((unsigned char*)"  L2", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.voltage[2]);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" V rms\r\n");
  McuShell_SendStatusStr((unsigned char*)"  L3", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.lockState);
  if (McuHeidelbergInfo.lockState==0) {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": system locked\r\n");
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)": system unlocked\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  lock", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.power);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" W (sum of all phases)\r\n");
  McuShell_SendStatusStr((unsigned char*)"  power", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadEnergySinceInstallation(McuHeidelberg_deviceID, &value32u)==ERR_OK) {
    McuUtility_Num32uToStr(buf, sizeof(buf), value32u);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" Wh (since installation)\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  energy", buf, io->stdOut);

  McuUtility_Num16uToStr(buf, sizeof(buf), McuHeidelbergInfo.minCurrent);
  McuUtility_chcat(buf, sizeof(buf), '-');
  McuUtility_strcatNum32u(buf, sizeof(buf), McuHeidelbergInfo.maxCurrent);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
  McuShell_SendStatusStr((unsigned char*)"  I min-max", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadHardwareVariant(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value16u);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  HW variant", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadApplicationSoftwareRevision(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value16u);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  SW revision", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadWatchDogTimeOut(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    if (value16u==0) {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0 (disabled Modbus timeout)\r\n");
    } else {
      McuUtility_Num16uToStr(buf, sizeof(buf), value16u/1000);
      McuUtility_chcat(buf, sizeof(buf), '.');
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u%1000, '0', 3);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" s Modbus timeout\r\n");
    }
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  WDT timeout", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadStandbyFunctionControl(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_Num16uToStr(buf, sizeof(buf), value16u);
    if (value16u==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (enabled, power saving if no car is connected)\r\n");
    } else if (value16u==4) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (disabled)\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (illegal value)\r\n");
    }
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  standby", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadRemoteLock(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    McuUtility_Num16uToStr(buf, sizeof(buf), value16u);
    if (value16u==0) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (locked)\r\n");
    } else if (value16u==1) {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (unlocked)\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" (illegal value)\r\n");
    }
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  remote lock", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadMaxCurrentCmd(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    if (value16u==0) {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0 A (no charging possible)\r\n");
    } else if (value16u<60) {
      McuUtility_Num16uToStr(buf, sizeof(buf), value16u);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" not allowed (no charging possible)\r\n");
    } else {
      McuUtility_Num16uToStr(buf, sizeof(buf), value16u/10);
      McuUtility_chcat(buf, sizeof(buf), '.');
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u%10, '0', 1);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
    }
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  I max cmd", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadFailSafeCurrent(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
    if (value16u==0) {
      McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0 A (no charging possible)\r\n");
    } else if (value16u<60) {
      McuUtility_Num16uToStr(buf, sizeof(buf), value16u);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" not allowed (no charging possible)\r\n");
    } else {
      McuUtility_Num16uToStr(buf, sizeof(buf), value16u/10);
      McuUtility_chcat(buf, sizeof(buf), '.');
      McuUtility_strcatNum16uFormatted(buf, sizeof(buf), value16u%10, '0', 1);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
    }
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
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
  McuShell_SendHelpStr((unsigned char*)"  set Ifail <dA>", (unsigned char*)"Set failsafe current in deci-amps (0 or 60-160), e.g. 60 for 6.0 A\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set chargemode <m>", (unsigned char*)"Set charge mode: 0 (stop), 1 (fast), 2 (slow), 3 (slow+PV), 4 (PV) \r\n", io->stdOut);
#if McuHeidelberg_CONFIG_USE_MOCK
  McuShell_SendHelpStr((unsigned char*)"  setmock state <value>", (unsigned char*)"Set mock wb state register value (2-11)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  setmock solar <value>", (unsigned char*)"Set mock solar power value (W)\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  setmock phases <value>", (unsigned char*)"Set mock number of phases (1-3)\r\n", io->stdOut);
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
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg set chargemode ", sizeof("McuHeidelberg set chargemode ")-1)==0) {
     *handled = true;
     p = cmd+sizeof("McuHeidelberg set chargemode ")-1;
     if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK && val16u>=0 && val16u<ChargingMode_NofChargingMode) {
       McuHeidelbergInfo.chargingMode = val16u;
       return ERR_OK;
     }
     return ERR_FAILED;
#if McuHeidelberg_CONFIG_USE_MOCK
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg setmock state ", sizeof("McuHeidelberg setmock state ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg setmock state ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK && (val16u>=2 && val16u<=11)) {
      mock.chargingState = val16u;
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if McuHeidelberg_CONFIG_USE_MOCK
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg setmock solar ", sizeof("McuHeidelberg setmock solar ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg setmock solar ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK) {
      McuHeidelbergInfo.solarPowerW = val16u;
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
#if McuHeidelberg_CONFIG_USE_MOCK
  } else if (McuUtility_strncmp((char*)cmd, "McuHeidelberg setmock phases ", sizeof("McuHeidelberg setmock phases ")-1)==0) {
    *handled = true;
    p = cmd+sizeof("McuHeidelberg setmock phases ")-1;
    if (McuUtility_ScanDecimal16uNumber(&p, &val16u)==ERR_OK && val16u>=1 && val16u<=3) {
      McuHeidelbergInfo.nofPhases = val16u;
      return ERR_OK;
    }
    return ERR_FAILED;
#endif
  }
  return ERR_OK;
}

static uint16_t CalculateChargingCurrentdA(void) {
  uint16_t current = 0; /* in dA units, e.g. 60 is 6.0 A */
  int power;

  if (McuHeidelbergInfo.chargingMode==ChargingMode_Stop) {
    current = 0;
  } else if (McuHeidelbergInfo.chargingMode==ChargingMode_Slow) {
    current = McuHeidelbergInfo.minCurrent*10;
  } else if (McuHeidelbergInfo.chargingMode==ChargingMode_Fast) {
    current = McuHeidelbergInfo.maxCurrent*10;
  } else if (McuHeidelbergInfo.chargingMode==ChargingMode_SlowPlusPV) {
    power = McuHeidelbergInfo.minCurrent*230*McuHeidelbergInfo.nofPhases;
    if (McuHeidelbergInfo.solarPowerW>power) { /* more solar power than the minimal amount: use that power */
      current = (McuHeidelbergInfo.solarPowerW*10)/230;
    } else {
      current = McuHeidelbergInfo.minCurrent*10;
    }
  } else if (McuHeidelbergInfo.chargingMode==ChargingMode_OnlyPV) {
    int power = McuHeidelbergInfo.minCurrent*230*McuHeidelbergInfo.nofPhases; /* minimal power setting possible */
    if (McuHeidelbergInfo.solarPowerW>=power) {
      current = (McuHeidelbergInfo.solarPowerW*10)/230;
    } else {
      current = 0; /* stop charging */ /*!\todo: need to use a hysteresis: check for at least a minute */
    }
  }
  /* check current boundaries */
  if (current<McuHeidelbergInfo.minCurrent*10) {
    current = 0;
  } else if (current>McuHeidelbergInfo.maxCurrent*10) {
    current = McuHeidelbergInfo.maxCurrent*10;
  }
  return current;
}

static uint8_t CalculateNofActivePhases(void) {
  uint8_t nof;
  uint8_t res;

  res = McuHeidelberg_ReadVoltage(McuHeidelberg_deviceID, &McuHeidelbergInfo.voltage[0]);
  if (res!=ERR_OK) {
    McuLog_fatal("failed reading voltage");
    return 1;
  }
  nof = 0;
  for(int i=0; i<sizeof(McuHeidelbergInfo.voltage)/sizeof(McuHeidelbergInfo.voltage[0]); i++) {
    if (McuHeidelbergInfo.voltage[i]>210) { /* voltage above 220V? */
      nof++;
    }
  }
  if (nof<1 || nof>3) { /* should never be the case? */
    McuLog_fatal("failed determine active phases");
    return 1; /* error fallback */
  }
  return nof; /* return number of phases detected */
}

static void wallboxTask(void *pv) {
  uint8_t res;
  uint16_t prevWallboxChargingState = 0;
  uint16_t prevChargingCurrentdA = 0; /* previous charging current in dA */
  uint16_t currChargingCurrentdA = 0; /* current charging current in dA */

  McuHeidelbergInfo.isActive = false;
  McuHeidelbergInfo.state = Wallbox_State_None;
  McuHeidelbergInfo.chargingMode = ChargingMode_Stop;
#if McuHeidelberg_CONFIG_USE_MOCK
  mock.chargingState = McuHeidelberg_ChargerState_A1;
#endif
/*
 * With the car plugged in, the charging state jumps to 4 (McuHeidelberg_ChargerState_B1).
 * Then write every second the load current into register 261 (McuHeidelberg_Addr_MaxCurrentCommand).
 * The charging state jumps to 7 (McuHeidelberg_ChargerState_C2) (charging).
 * To stop the charging, write 0 to register 261 (McuHeidelberg_Addr_MaxCurrentCommand).
 */
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(100)); /* standard delay time */
    switch(McuHeidelbergInfo.state) {
      case Wallbox_State_None:
        McuHeidelbergInfo.isActive = false;
        /* no state yet: probe layout register to check if we can reach the charger */
        res = McuHeidelberg_ReadRegisterLayoutVersion(McuHeidelberg_deviceID, &McuHeidelbergInfo.version);
        if (res==ERR_OK) {
          McuLog_trace("connected with charger");
          McuHeidelbergInfo.isActive = true;
          prevWallboxChargingState = 0; /* reset */
          McuHeidelbergInfo.state = Wallbox_State_Connected;
          /* set initial charger current to zero */
          if (McuHeidelberg_WriteMaxCurrentCmd(McuHeidelberg_deviceID, 0)!=ERR_OK) {
            McuLog_error("failed writing max current");
          }
          //vTaskDelay(10);
          /* read static values from wallbox */
          if (McuHeidelberg_ReadHardwareMinCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.minCurrent)!=ERR_OK) {
            McuLog_error("failed reding min current");
          }
          if (McuHeidelberg_ReadHardwareMaxCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.maxCurrent)!=ERR_OK) {
            McuLog_error("failed read max current");
          }
          /* read other dynamic values the first time */
          if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState)!=ERR_OK) {
            McuLog_error("failed read device ID current");
          }
          if (McuHeidelberg_ReadCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.current[0])!=ERR_OK) {
            McuLog_error("failed read current current");
          }
          if (McuHeidelberg_ReadTemperature(McuHeidelberg_deviceID, &McuHeidelbergInfo.temperature)!=ERR_OK) {
            McuLog_error("failed read temperature current");
          }
          if (McuHeidelberg_ReadVoltage(McuHeidelberg_deviceID, &McuHeidelbergInfo.voltage[0])!=ERR_OK) {
            McuLog_error("failed read voltage current");
          }
          if (McuHeidelberg_ReadLockstate(McuHeidelberg_deviceID, &McuHeidelbergInfo.lockState)!=ERR_OK) {
            McuLog_error("failed read lockstate current");
          }
          if (McuHeidelberg_ReadPower(McuHeidelberg_deviceID, &McuHeidelbergInfo.power)!=ERR_OK) {
            McuLog_error("failed read power current");
          }
          if (McuHeidelberg_ReadEnergySincePowerOn(McuHeidelberg_deviceID, &McuHeidelbergInfo.energySincePowerOn)!=ERR_OK) {
            McuLog_error("failed read energy current");
          }
          /* determine the number of active phases */
          McuHeidelbergInfo.nofPhases = CalculateNofActivePhases();
        } else {
          McuLog_error("communication failed, charger in standby? Retry in 10 seconds...");
          vTaskDelay(pdMS_TO_TICKS(10000)); /* need to poll the device on a regular base, otherwise it goes into communication error state */
        }
        break;

      case Wallbox_State_Connected:
        if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState)==ERR_OK) {
          if (prevWallboxChargingState != McuHeidelbergInfo.chargingState) { /* state change? */
            McuLog_trace("wallbox state changed from '%d' to '%d'", prevWallboxChargingState, McuHeidelbergInfo.chargingState);
            switch(McuHeidelbergInfo.chargingState) {
              case McuHeidelberg_ChargerState_A1:
              case McuHeidelberg_ChargerState_A2:
                /* no vehicle plugged, stay in current state */
                break;

              case McuHeidelberg_ChargerState_B1:
              case McuHeidelberg_ChargerState_B2:
              case McuHeidelberg_ChargerState_C1:
              case McuHeidelberg_ChargerState_C2:
                 McuLog_trace("vehicle plugged");
                 McuHeidelbergInfo.state = Wallbox_State_Vehicle_Plugged;
                break;

              case McuHeidelberg_ChargerState_Derating:
              case McuHeidelberg_ChargerState_E:
              case McuHeidelberg_ChargerState_F:
              case McuHeidelberg_ChargerState_Error:
              default:
                McuHeidelbergInfo.state = Wallbox_State_Error; /* error case */
                break;
            }
            prevWallboxChargingState = McuHeidelbergInfo.chargingState;
          } /* if state changed */
        } else {
          McuLog_error("unable to get charging state");
          McuHeidelbergInfo.state = Wallbox_State_Error;
        }
        break;

      case Wallbox_State_Vehicle_Plugged:
        if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState)==ERR_OK) {
          if (prevWallboxChargingState != McuHeidelbergInfo.chargingState) { /* state change? */
            McuLog_trace("wallbox state changed from '%d' to '%d'", prevWallboxChargingState, McuHeidelbergInfo.chargingState);
            switch(McuHeidelbergInfo.chargingState) {
              case McuHeidelberg_ChargerState_A1:
              case McuHeidelberg_ChargerState_A2:
                McuLog_trace("vehicle not plugged any more");
                McuHeidelbergInfo.state = Wallbox_State_Connected;
                break;

              case McuHeidelberg_ChargerState_B1:
              case McuHeidelberg_ChargerState_B2:
                /* vehicle plugged, but no charging request: stay in this state */
                break;

              case McuHeidelberg_ChargerState_C1:
              case McuHeidelberg_ChargerState_C2:
                McuLog_trace("vehicle plugged, with charging request");
                McuHeidelbergInfo.state = Wallbox_State_Vehicle_Start_Charging;
                break;

              case McuHeidelberg_ChargerState_Derating:
              case McuHeidelberg_ChargerState_E:
              case McuHeidelberg_ChargerState_F:
              case McuHeidelberg_ChargerState_Error:
              default:
                McuHeidelbergInfo.state = Wallbox_State_Error; /* error case */
                break;
            }
            prevWallboxChargingState = McuHeidelbergInfo.chargingState;
          } /* if state changed */
        } else {
          McuLog_error("unable to get charging state");
          McuHeidelbergInfo.state = Wallbox_State_Error;
        }
        break;

      case Wallbox_State_Vehicle_Start_Charging:
        McuLog_trace("start charging");
        currChargingCurrentdA = CalculateChargingCurrentdA();
        McuLog_info("setting charging current to %d.%d A (%d W)", currChargingCurrentdA/10, currChargingCurrentdA%10, McuHeidelbergInfo.nofPhases*currChargingCurrentdA*230/10);
        McuHeidelberg_WriteMaxCurrentCmd(McuHeidelberg_deviceID, currChargingCurrentdA); /* set value in dA */
        prevChargingCurrentdA = currChargingCurrentdA;
        McuHeidelbergInfo.state = Wallbox_State_Vehicle_Charging;
        break;

      case Wallbox_State_Vehicle_Charging:
        if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState)==ERR_OK) {
          if (prevWallboxChargingState != McuHeidelbergInfo.chargingState) { /* state change? */
            McuLog_trace("wallbox state changed from '%d' to '%d'", prevWallboxChargingState, McuHeidelbergInfo.chargingState);
            switch(McuHeidelbergInfo.chargingState) {
              case McuHeidelberg_ChargerState_A1:
              case McuHeidelberg_ChargerState_A2:
                McuLog_trace("vehicle not plugged any more");
                McuHeidelbergInfo.state = Wallbox_State_Connected;
                break;

              case McuHeidelberg_ChargerState_B1:
              case McuHeidelberg_ChargerState_B2:
                McuLog_trace("vehicle plugged, but dropped charging request");
                McuHeidelbergInfo.state = Wallbox_State_Connected;
                break;

              case McuHeidelberg_ChargerState_C1:
              case McuHeidelberg_ChargerState_C2:
                /* vehicle plugged, with charging request: stay in this state */
                vTaskDelay(pdMS_TO_TICKS(2000));
                break;

              case McuHeidelberg_ChargerState_Derating:
                McuLog_trace("derating while charging, waiting 5 seconds");
                vTaskDelay(pdMS_TO_TICKS(5000));
                break;
              case McuHeidelberg_ChargerState_E:
              case McuHeidelberg_ChargerState_F:
              case McuHeidelberg_ChargerState_Error:
              default:
                McuHeidelbergInfo.state = Wallbox_State_Error; /* error case */
                break;
            } /* switch */
            prevWallboxChargingState = McuHeidelbergInfo.chargingState;
          } /* if state changed */
          if (McuHeidelbergInfo.chargingState==McuHeidelberg_ChargerState_C2) {
            /* calculate charging current */
            currChargingCurrentdA = CalculateChargingCurrentdA();
            if (currChargingCurrentdA!=prevChargingCurrentdA) {
              McuLog_info("changing charging current from %d.%d A to %d.%d A (%d W)", prevChargingCurrentdA/10, prevChargingCurrentdA%10, currChargingCurrentdA/10, currChargingCurrentdA%10, McuHeidelbergInfo.nofPhases*currChargingCurrentdA*230/10);
              McuHeidelberg_WriteMaxCurrentCmd(McuHeidelberg_deviceID, currChargingCurrentdA); /* set value in dA */
              prevChargingCurrentdA = currChargingCurrentdA;
            }
          }
        } else {
          McuLog_error("unable to get charging state");
          McuHeidelbergInfo.state = Wallbox_State_Error;
        }
        break;

      case Wallbox_State_Vehicle_Stop_Charging:
        McuLog_trace("stop charging");
        McuHeidelberg_WriteMaxCurrentCmd(McuHeidelberg_deviceID, 0); /* stop charging */
        McuHeidelbergInfo.state = Wallbox_State_Connected;
        break;

      case Wallbox_State_Error:
        McuLog_error("error, stop charging, reinitializing");
        McuHeidelberg_WriteMaxCurrentCmd(McuHeidelberg_deviceID, 0); /* stop charging */
        McuHeidelbergInfo.state = Wallbox_State_None;
        break;

      default:
        break;
    } /* switch */
  }
}

void McuHeidelberg_Deinit(void) {
  /* nothing needed */
}

void McuHeidelberg_Init(void) {
  if (xTaskCreate(
       wallboxTask,  /* pointer to the task */
       "wallbox", /* task name for kernel awareness debugging */
       600/sizeof(StackType_t), /* task stack size */
       (void*)NULL, /* optional task startup argument */
       tskIDLE_PRIORITY+4,  /* initial priority */
       (TaskHandle_t*)NULL /* optional task handle to create */
     ) != pdPASS)
   {
     McuLog_fatal("Failed creating task");
     for(;;){} /* error! probably out of memory */
   }
}

