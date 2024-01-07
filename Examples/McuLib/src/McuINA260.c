/**
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * \brief Driver for the TI INA260 current/voltage sensor.
 */

#include "McuINA260.h"
#include "McuUtility.h"
#include "McuGenericI2C.h"

#define SwapBytes(u16)  ((u16<<8)|(u16>>8))

/*! 
 * \brief Convert the 16bit current register value to micro amps
 * \param value McuINA260_ADDR_CURRENT_REGISTER register value
 * \return Current in micro amp
 */
static int32_t McuINA260_ConvertCurrentRegisterToMicroAmps(int16_t value) {
  /* LSB == 1.25 mA == 1250 uA */
  return value*1250;
}

/*!
 * \brief Convert the voltage register value into miro volts
 * \param value McuINA260_ADDR_BUS_VOLTAGE_REGISTER register value
 * \return Voltage in micro volt
 */
static uint32_t McuINA260_ConvertBusVoltageRegisterToMicroVoltage(uint16_t value) {
  /* LSB == 1.25 mV == 1250 uV */
  return (uint32_t)value*1250;
}

/*!
 * \brief Convert the power register value into miro volts
 * \param value McuINA260_ADDR_POWER_REGISTER register value
 * \return Voltage in milli watt
 */
static uint32_t McuINA260_ConvertPowerRegisterToMilliWatt(uint16_t value) {
  /* LSB == 10 mW */
  return (uint32_t)value*10;
}

uint8_t McuINA260_ReadRegister(INA260_REG_e reg, uint16_t *value) {
  uint8_t res;
  uint16_t data;

  res = McuGenericI2C_ReadWordAddress8(McuINA260_CONFIG_I2C_ADDRESS, reg, &data);
  if (res!=ERR_OK) {
    return res;
  }
  *value = SwapBytes(data);
  return ERR_OK;
}

uint8_t McuINA260_WriteRegister(INA260_REG_e reg, uint16_t value) {
  uint8_t res;
  uint16_t data;

  data = SwapBytes(value);
  res = McuGenericI2C_WriteWordAddress8(McuINA260_CONFIG_I2C_ADDRESS, reg, data);
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t McuINA260_ReadConfigRegister(uint16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_CONFIGURATION_REGISTER, value);
}

uint8_t McuINA260_WriteConfigRegister(uint16_t value) {
  return McuINA260_WriteRegister(McuINA260_ADDR_CONFIGURATION_REGISTER, value);
}

uint8_t McuINA260_WriteResetBit(void) {
  return McuINA260_WriteConfigRegister(1<<15);
}

uint8_t McuINA260_ReadCurrentRegister(int16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_CURRENT_REGISTER, value);
}

uint8_t McuINA260_ReadBusVoltageRegister(uint16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_BUS_VOLTAGE_REGISTER, value);
}

uint8_t McuINA260_ReadPowerRegister(uint16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_POWER_REGISTER, value);
}

uint8_t McuINA260_ReadMaskEnableRegister(uint16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_MASK_ENABLE_REGISTER, value);
}

uint8_t McuINA260_ReadAlertLimitRegister(uint16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_ALERT_LIMIT_REGISTER, value);
}

uint8_t McuINA260_ReadManufacturereIDRegister(uint16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_MANUFACTURER_ID_REGISTER, value);
}

uint8_t McuINA260_ReadDieIDRegister(uint16_t *value) {
  return McuINA260_ReadRegister(McuINA260_ADDR_DIE_ID_REGISTER, value);
}

/*!
 * \brief Read the bus voltage measurement value from the device.
 * \return Power value, as mV (micro-Volt).
 */
uint32_t McuINA260_ReadVoltage(void) {
  uint8_t res;
  uint16_t val;

  res = McuINA260_ReadBusVoltageRegister(&val);
  if (res==ERR_OK) {
    return McuINA260_ConvertBusVoltageRegisterToMicroVoltage(val);
  } else {
    return 0; /* error case */
  } 
}

/*!
 * \brief Read the power measurement value from the device.
 * \return Power value, as mW (milli-Watt).
 */
uint32_t McuINA260_ReadPower(void) {
  uint8_t res;
  uint16_t val;

  res = McuINA260_ReadPowerRegister(&val);
  if (res==ERR_OK) {
    return McuINA260_ConvertPowerRegisterToMilliWatt(val);
  } else {
    return 0; /* error case */
  } 
}

/*!
 * \brief Read the current measurement value from the device.
 * \return Current value, as uA (micro-Amps).
 */
int32_t McuINA260_ReadCurrent(void) {
  uint8_t res;
  int16_t val;

  res = McuINA260_ReadCurrentRegister(&val);
  if (res==ERR_OK) {
    return McuINA260_ConvertCurrentRegisterToMicroAmps(val);
  } else {
    return 0; /* error case */
  }
}

#if McuINA260_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32];
  uint16_t value;

  McuShell_SendStatusStr((unsigned char*)"McuINA260", (unsigned char*)"INA260 sensor status\r\n", io->stdOut);

  McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_CONFIG_I2C_ADDRESS);
  McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  McuShell_SendStatusStr((unsigned char*)"  I2C addr", buf, io->stdOut);

  if (McuINA260_ReadConfigRegister(&value)==ERR_OK) {
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_ADDR_CONFIGURATION_REGISTER);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"h: 0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FAILED\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Config", buf, io->stdOut);

  if (McuINA260_ReadCurrentRegister(&value)==ERR_OK) {
    int32_t uA = McuINA260_ConvertCurrentRegisterToMicroAmps(value);

    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_ADDR_CURRENT_REGISTER);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"h: 0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", ");
    McuUtility_strcatNum32s(buf, sizeof(buf), uA/1000);
    McuUtility_chcat(buf, sizeof(buf), '.');
    if (uA<0) { /* value can be negative */
      uA = -uA; /* make it positive for the modulo operation below */
    }
    McuUtility_strcatNum32sFormatted(buf, sizeof(buf), uA%1000, '0', 3);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" mA\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FAILED\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Current", buf, io->stdOut);

  if (McuINA260_ReadBusVoltageRegister(&value)==ERR_OK) {
    uint32_t uV = McuINA260_ConvertBusVoltageRegisterToMicroVoltage(value);

    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_ADDR_BUS_VOLTAGE_REGISTER);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"h: 0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", ");
    McuUtility_strcatNum32u(buf, sizeof(buf), uV/1000);
    McuUtility_chcat(buf, sizeof(buf), '.');
    McuUtility_strcatNum32sFormatted(buf, sizeof(buf), uV%1000, '0', 3);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" mV\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FAILED\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Bus voltage", buf, io->stdOut);

  if (McuINA260_ReadPowerRegister(&value)==ERR_OK) {
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_ADDR_POWER_REGISTER);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"h: 0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)", ");
    McuUtility_strcatNum32u(buf, sizeof(buf), McuINA260_ConvertPowerRegisterToMilliWatt(value));
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)" mW\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FAILED\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Power", buf, io->stdOut);

  if (McuINA260_ReadAlertLimitRegister(&value)==ERR_OK) {
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_ADDR_ALERT_LIMIT_REGISTER);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"h: 0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FAILED\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Alert limit", buf, io->stdOut);

  if (McuINA260_ReadManufacturereIDRegister(&value)==ERR_OK) {
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_ADDR_MANUFACTURER_ID_REGISTER);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"h: 0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FAILED\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Manufac. ID", buf, io->stdOut);

  if (McuINA260_ReadDieIDRegister(&value)==ERR_OK) {
    buf[0] = '\0';
    McuUtility_strcatNum8Hex(buf, sizeof(buf), McuINA260_ADDR_DIE_ID_REGISTER);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"h: 0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), value);
    McuUtility_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), (unsigned char*)"FAILED\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  Die ID", buf, io->stdOut);

  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"INA260", (unsigned char*)"Group of INA260 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"Reset the device with the reset bit\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  config <val>", (unsigned char*)"Write a value to the configuration register\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuINA260_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "INA260 help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "INA260 status")==0)
            )
  {
    *handled = true;
    res = PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "INA260 reset")==0) {
    *handled = true;
    return McuINA260_WriteResetBit();
  } else if (McuUtility_strncmp((char*)cmd, "INA260 config ", sizeof("INA260 config "-1))==0) {
    const unsigned char *p;
    int32_t val;

    *handled = true;
    p = cmd + sizeof("INA260 config "-1);
    if (McuUtility_xatoi(&p, &val)==ERR_OK && val>=0) {
      return McuINA260_WriteConfigRegister(val);
    }
  }
  return res;
}
#endif /* McuINA260_CONFIG_PARSE_COMMAND_ENABLED */

void McuINA260_Deinit(void) {
  /* nothing needed */
}

void McuINA260_Init(void) {
  /* nothing needed */
}