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

static struct McuHeidelbergInfo_s {
  bool isActive;                /* if unit is in standby or not */
  uint16_t version;             /* register layout version */
  uint16_t chargingState;       /* charging state */
  uint16_t current[3];          /* RMS current of the three phases, in 0.1 A units */
  int16_t temperature;          /* PCB temperature, in 0.1 degree C */
  uint16_t voltage[3];          /* RMS voltage of the three phases, in 0.1 A units */
  uint16_t lockState;           /* external lock */
  uint16_t power;               /* sum of power of all three phases */
  uint32_t energySincePowerOn;  /* energy since last standby or power-off */
} McuHeidelbergInfo;

typedef enum ChargingState_e {
  McuHeidelberg_ChargerState_A1       = 2,
  McuHeidelberg_ChargerState_A2       = 3,
  McuHeidelberg_ChargerState_B1       = 4,
  McuHeidelberg_ChargerState_B2       = 5,
  McuHeidelberg_ChargerState_C1       = 6,
  McuHeidelberg_ChargerState_C2       = 7,
  McuHeidelberg_ChargerState_Derating = 8,
  McuHeidelberg_ChargerState_E        = 9,
  McuHeidelberg_ChargerState_F        = 10,
  McuHeidelberg_ChargerState_Error    = 11,
} ChargingState_e;

const unsigned char *McuHeidelberg_GetChargingStateString(uint16_t state) {
  const unsigned char *str;
  switch(state) {
    case McuHeidelberg_ChargerState_A1:       str = (unsigned char*)"A1: no vehicle plugged, wallbox does not allow charging"; break;
    case McuHeidelberg_ChargerState_A2:       str = (unsigned char*)"A2: no vehicle plugged, wallbox allows charging"; break;
    case McuHeidelberg_ChargerState_B1:       str = (unsigned char*)"B1: vehicle plugged without charging request, wallbox does not allow charging"; break;
    case McuHeidelberg_ChargerState_B2:       str = (unsigned char*)"B2: vehicle plugged without charging request, wallbox allows charging"; break;
    case McuHeidelberg_ChargerState_C1:       str = (unsigned char*)"C1: vehicle plugged with charging request, wallbox does not allow charging"; break;
    case McuHeidelberg_ChargerState_C2:       str = (unsigned char*)"C2: vehicle plugged with charging request, wallbox allows charging"; break;
    case McuHeidelberg_ChargerState_Derating: str = (unsigned char*)"--: derating"; break;
    case McuHeidelberg_ChargerState_E:        str = (unsigned char*)"E: error"; break;
    case McuHeidelberg_ChargerState_F:        str = (unsigned char*)"F: wallbox locked or not ready"; break;
    case McuHeidelberg_ChargerState_Error:    str = (unsigned char*)"--: Error"; break;
    default:                                  str = (unsigned char*)"ERROR, unknown state!"; break;
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
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_ChargingState, 1, &value)!=ERR_OK) {
    return ERR_FAILED;
  }
  *state = value;
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
    return ERR_FAILED;
  }
  *current = value;
  return ERR_OK;
}

uint8_t McuHeidelberg_ReadHardwareMinCurrent(uint8_t id, uint16_t *current) {
  uint16_t value;

  if (McuModbus_ReadInputRegisters(id, McuHeidelberg_Addr_MinCurrent, 1, &value)!=ERR_OK) {
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
  unsigned char buf[64];
  uint32_t value32u;
  uint16_t value16u;

  McuShell_SendStatusStr((unsigned char*)"McuHeidelberg", (unsigned char*)"Heidelberg wallbox settings\r\n", io->stdOut);

  McuShell_SendStatusStr((unsigned char*)"  state", McuHeidelbergInfo.isActive?(unsigned char*)"active\r\n":(unsigned char*)"standby or powered off\r\n", io->stdOut);


  McuUtility_Num8uToStr(buf, sizeof(buf), McuHeidelberg_deviceID);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  ID", buf, io->stdOut);

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
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VA (sum of all phases)\r\n");
  McuShell_SendStatusStr((unsigned char*)"  power", buf, io->stdOut);

  if (McuHeidelbergInfo.isActive && McuHeidelberg_ReadEnergySinceInstallation(McuHeidelberg_deviceID, &value32u)==ERR_OK) {
    McuUtility_Num32uToStr(buf, sizeof(buf), value32u);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" VAh (since installation)\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  energy", buf, io->stdOut);

  buf[0] = '\0';
  if (McuHeidelbergInfo.isActive) {
    if (McuHeidelberg_ReadHardwareMinCurrent(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
      McuUtility_strcatNum32u(buf, sizeof(buf), value16u);
      McuUtility_chcat(buf, sizeof(buf), '-');
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"ERR ");
    }
    if (McuHeidelberg_ReadHardwareMaxCurrent(McuHeidelberg_deviceID, &value16u)==ERR_OK) {
      McuUtility_strcatNum32u(buf, sizeof(buf), value16u);
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" A\r\n");
    } else {
      McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"ERR\r\n");
    }
  } else {
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"(standby)\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  I range", buf, io->stdOut);

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
  McuShell_SendHelpStr((unsigned char*)"  set Imax <dA>", (unsigned char*)"Set charging current deci-amps (0 or 60-160), e.g. 60 for 6.0 A\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  set Ifail <dA>", (unsigned char*)"Set failsafe current deci-amps (0 or 60-160), e.g. 60 for 6.0 A\r\n", io->stdOut);
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
  }
  return ERR_OK;
}

typedef enum {
  Wallbox_State_None,
  Wallbox_State_Connected,
  Wallbox_State_Vehicle_Plugged,
  Wallbox_State_Vehicle_Charging,
  Wallbox_State_Error,
} WallboxState_e;

static void wallboxTask(void *pv) {
  uint8_t res;
  WallboxState_e state = Wallbox_State_None;
  uint16_t prevWallboxCharingState;

  McuHeidelbergInfo.isActive = false;
  for(;;) {
    vTaskDelay(pdMS_TO_TICKS(100)); /* standard delay time */
    switch(state) {
      case Wallbox_State_None:
        McuHeidelbergInfo.isActive = false;
        /* no state yet: probe layout register to check if we can reach the charger */
        res = McuHeidelberg_ReadRegisterLayoutVersion(McuHeidelberg_deviceID, &McuHeidelbergInfo.version);
        if (res==ERR_OK) {
          McuLog_trace("connected with charger");
          McuHeidelbergInfo.isActive = true;
          prevWallboxCharingState = 0; /* reset */
          state = Wallbox_State_Connected;
        } else {
          McuLog_error("communication failed, charger in standby? Retry in 10 seconds...");
          vTaskDelay(pdMS_TO_TICKS(10000)); /* need to poll the device on a regular base, otherwise it goes into communication error state */
        }
        break;
      case Wallbox_State_Connected:
        if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState)==ERR_OK) {
          if (prevWallboxCharingState != McuHeidelbergInfo.chargingState) { /* state change? */
            McuLog_trace("wallbox state changed from '%d' to '%d'", prevWallboxCharingState, McuHeidelbergInfo.chargingState);
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
                state = Wallbox_State_Vehicle_Plugged;
                break;

              case McuHeidelberg_ChargerState_Derating:
              case McuHeidelberg_ChargerState_E:
              case McuHeidelberg_ChargerState_F:
              case McuHeidelberg_ChargerState_Error:
              default:
                state = Wallbox_State_Error; /* error case */
                break;
            }
            prevWallboxCharingState = McuHeidelbergInfo.chargingState;
          } /* if state changed */
        } else {
          McuLog_error("unable to get charging state");
          state = Wallbox_State_Error;
        }
        break;

      case Wallbox_State_Vehicle_Plugged:
        if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState)==ERR_OK) {
          if (prevWallboxCharingState != McuHeidelbergInfo.chargingState) { /* state change? */
            McuLog_trace("wallbox state changed from '%d' to '%d'", prevWallboxCharingState, McuHeidelbergInfo.chargingState);
            switch(McuHeidelbergInfo.chargingState) {
              case McuHeidelberg_ChargerState_A1:
              case McuHeidelberg_ChargerState_A2:
                McuLog_trace("vehicle not plugged any more");
                state = Wallbox_State_Connected;
                break;

              case McuHeidelberg_ChargerState_B1:
              case McuHeidelberg_ChargerState_B2:
                /* vehicle plugged, but no charging request: stay in this state */
                break;

              case McuHeidelberg_ChargerState_C1:
              case McuHeidelberg_ChargerState_C2:
                McuLog_trace("vehicle plugged, with charging request");
                state = Wallbox_State_Vehicle_Charging;
                break;

              case McuHeidelberg_ChargerState_Derating:
              case McuHeidelberg_ChargerState_E:
              case McuHeidelberg_ChargerState_F:
              case McuHeidelberg_ChargerState_Error:
              default:
                state = Wallbox_State_Error; /* error case */
                break;
            }
            prevWallboxCharingState = McuHeidelbergInfo.chargingState;
          } /* if state changed */
        } else {
          McuLog_error("unable to get charging state");
          state = Wallbox_State_Error;
        }
        break;

      case Wallbox_State_Vehicle_Charging:
        if (McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState)==ERR_OK) {
          if (prevWallboxCharingState != McuHeidelbergInfo.chargingState) { /* state change? */
            McuLog_trace("wallbox state changed from '%d' to '%d'", prevWallboxCharingState, McuHeidelbergInfo.chargingState);
            switch(McuHeidelbergInfo.chargingState) {
              case McuHeidelberg_ChargerState_A1:
              case McuHeidelberg_ChargerState_A2:
                McuLog_trace("vehicle not plugged any more");
                state = Wallbox_State_Connected;
                break;

              case McuHeidelberg_ChargerState_B1:
              case McuHeidelberg_ChargerState_B2:
                McuLog_trace("vehicle plugged, but dropped charging request");
                state = Wallbox_State_Connected;
                break;

              case McuHeidelberg_ChargerState_C1:
              case McuHeidelberg_ChargerState_C2:
                /* vehicle plugged, with charging request: stay in this state */
                break;

              case McuHeidelberg_ChargerState_Derating:
              case McuHeidelberg_ChargerState_E:
              case McuHeidelberg_ChargerState_F:
              case McuHeidelberg_ChargerState_Error:
              default:
                state = Wallbox_State_Error; /* error case */
                break;
            }
            prevWallboxCharingState = McuHeidelbergInfo.chargingState;
          } /* if state changed */
        } else {
          McuLog_error("unable to get charging state");
          state = Wallbox_State_Error;
        }
       break;

      case Wallbox_State_Error:
        McuLog_error("error in state, reinitializing");
        state = Wallbox_State_None;
        break;

      default:
        (void)McuHeidelberg_ReadChargingState(McuHeidelberg_deviceID, &McuHeidelbergInfo.chargingState);
        (void)McuHeidelberg_ReadCurrent(McuHeidelberg_deviceID, &McuHeidelbergInfo.current[0]);
        (void)McuHeidelberg_ReadTemperature(McuHeidelberg_deviceID, &McuHeidelbergInfo.temperature);
        (void)McuHeidelberg_ReadVoltage(McuHeidelberg_deviceID, &McuHeidelbergInfo.voltage[0]);
        (void)McuHeidelberg_ReadLockstate(McuHeidelberg_deviceID, &McuHeidelbergInfo.lockState);
        (void)McuHeidelberg_ReadPower(McuHeidelberg_deviceID, &McuHeidelbergInfo.power);
        (void)McuHeidelberg_ReadEnergySincePowerOn(McuHeidelberg_deviceID, &McuHeidelbergInfo.energySincePowerOn);
        vTaskDelay(pdMS_TO_TICKS(5000)); /* need to poll the device on a regular base, otherwise it goes into communication error state */
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

