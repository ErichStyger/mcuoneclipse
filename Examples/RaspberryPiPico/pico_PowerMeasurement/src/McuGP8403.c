/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * 2-Channel I2C DAC module with a voltage of 0-10V
 */

#include "McuGP8403.h"
#include "McuGP8403_config.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"
#include "McuUtility.h"
#include "McuGenericI2C.h"
#include "McuLog.h"

/* GP8403 device register map: */
typedef enum McuGP8403_Reg_e { /* values are the hardware register addresses */
  McuADS1115_ADDR_CONFIG_REGISTER     = 0x01,  /**< writing 0x00: 0-5V, writing 0x11: 0-10V */
  McuADS1115_ADDR_VOUT0_REGISTER      = 0x02,  /**< VOUT0 12bit data register (5 and 10V output) */
  McuADS1115_ADDR_VOUT1_REGISTER      = 0x04,  /**< VOUT1 12bit data register (5 and 10V output) */
} McuGP8403_Reg_e;

#define SWAP_BYTES(u16)  (((u16)<<8)|((u16)>>8))

uint8_t McuGP8403_ReadRegisterByte(McuGP8403_Reg_e reg, uint8_t *value) {
  uint8_t res;
  uint8_t data;

  res = McuGenericI2C_ReadByteAddress8(McuGP8403_CONFIG_I2C_ADDRESS, reg, &data);
  if (res!=ERR_OK) {
    return res;
  }
  *value = data;
  return ERR_OK;
}

uint8_t McuGP8403_ReadRegisterWord(McuGP8403_Reg_e reg, uint16_t *value) {
  uint8_t res;
  uint16_t data;

  res = McuGenericI2C_ReadWordAddress8(McuGP8403_CONFIG_I2C_ADDRESS, reg, &data);
  if (res!=ERR_OK) {
    return res;
  }
  *value = data;
  return ERR_OK;
}

uint8_t McuGP8403_WriteRegisterByte(McuGP8403_Reg_e reg, uint8_t value) {
  return McuGenericI2C_WriteByteAddress8(McuGP8403_CONFIG_I2C_ADDRESS, reg, value);
}

uint8_t McuGP8403_WriteRegisterWord(McuGP8403_Reg_e reg, uint16_t value) {
  return McuGenericI2C_WriteWordAddress8(McuGP8403_CONFIG_I2C_ADDRESS, reg, value);
}

uint8_t McuGP8403_SetMaxOutputVoltage(uint8_t v) {
  if (!(v==5 || v==10)) {
    return ERR_RANGE; /* only 5 or 10 allowed */
  }
  return McuGP8403_WriteRegisterByte(McuADS1115_ADDR_CONFIG_REGISTER, v==5?0x0:0x11); /* write 0x00 for 5V and 0x11 for 10V */
}

uint8_t McuGP8403_GetMaxOutputVoltage(uint8_t *v) {
  uint8_t res, val8;

  *v = 0;
  res = McuGP8403_ReadRegisterByte(McuADS1115_ADDR_CONFIG_REGISTER, &val8);
  if (res!=ERR_OK) {
    return res;
  }
  if (val8==0x00) {
    *v = 5;
    return ERR_OK;
  } else if (val8==0x11) {
    *v = 10;
    return ERR_OK;
  } else {
    *v = 0;
    return ERR_FAILED;
  }
}


uint8_t McuGP8403_SetVoutxVoltage(uint8_t reg, uint16_t val) {
  uint8_t res;

  val = (val<<12) | (val>>4); /* write bits as 3 2 1 0 xxxx 11  - 10 9 8 7 6 5 4 */
  val = SWAP_BYTES(val);
  res = McuGP8403_WriteRegisterWord(reg, val);
  if (res!=ERR_OK) {
    return res; /* error case */
  }
  return ERR_OK;
}

uint8_t McuGP8403_SetVout0Voltage(uint16_t val) {
  return McuGP8403_SetVoutxVoltage(McuADS1115_ADDR_VOUT0_REGISTER, val);
}

uint8_t McuGP8403_SetVout1Voltage(uint16_t val) {
  return McuGP8403_SetVoutxVoltage(McuADS1115_ADDR_VOUT1_REGISTER, val);
}

uint8_t McuGP8403_GetVoutxVoltage(uint8_t reg, uint16_t *val) {
  uint8_t res, v;
  uint16_t val16;

  res = McuGP8403_ReadRegisterWord(reg, &val16); /* always reads 0x1111 ??? */
  if (res!=ERR_OK) {
    return res; /* error case */
  }
  val16 = (val16>>12) | (val16<<4); /* swap bytes and ignore lower 4 bits of Data0low */
  #if 0 /* \todo */
  res = McuGP8403_GetMaxOutputVoltage(&v);
  if (res!=ERR_OK) {
    return res; /* error case */
  }
  #endif
  *val = val16;
  return ERR_OK;
}

uint8_t McuGP8403_GetVout0Voltage(uint16_t *val) {
  return McuGP8403_ReadRegisterWord(McuADS1115_ADDR_VOUT0_REGISTER, val);
}

uint8_t McuGP8403_GetVout1Voltage(uint16_t *val) {
  return McuGP8403_ReadRegisterWord(McuADS1115_ADDR_VOUT1_REGISTER, val);
}

#if McuGP8403_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32], res, val8;
  uint16_t val16;

  McuShell_SendStatusStr((unsigned char*)"McuGP8403", (unsigned char*)"GP8403 DAC status\r\n", io->stdOut);
  res = McuGP8403_GetMaxOutputVoltage(&val8);
  if (res==ERR_OK) {
     McuUtility_strcpy(buf, sizeof(buf), "0-");
     McuUtility_strcatNum8u(buf, sizeof(buf), val8);
     McuUtility_strcat(buf, sizeof(buf), "V\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "read failed\r\n");
  }
  McuShell_SendStatusStr("  voltage", buf, io->stdOut);

  res = McuGP8403_GetVout0Voltage(&val16);
   if (res==ERR_OK) {
     McuUtility_strcpy(buf, sizeof(buf), "0x");
     McuUtility_strcatNum16Hex(buf, sizeof(buf), val16);
     McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "read failed\r\n");
  }
  McuShell_SendStatusStr("  Vout0", buf, io->stdOut);

  res = McuGP8403_GetVout1Voltage(&val16);
  if (res==ERR_OK) {
     McuUtility_strcpy(buf, sizeof(buf), "0x");
     McuUtility_strcatNum16Hex(buf, sizeof(buf), val16);
     McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "read failed\r\n");
  }
  McuShell_SendStatusStr("  Vout1", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {

  McuShell_SendHelpStr((unsigned char*)"McuGP8403", (unsigned char*)"Group of GP8403 DAC commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  voltage 5|10", (unsigned char*)"Set maximum output voltage to 5V or 10V\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  vout0|vout1 <val>", (unsigned char*)"Set vout0 or 1 output voltage\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuGP8403_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  int32_t val;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "McuGP8403 help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "McuGP8403 status")==0)
            )
  {
    *handled = true;
    return PrintStatus(io);
  } else if (McuUtility_strcmp((char*)cmd, "McuGP8403 voltage 5")==0) {
    *handled=true;
    return McuGP8403_SetMaxOutputVoltage(5);
  } else if (McuUtility_strcmp((char*)cmd, "McuGP8403 voltage 10")==0) {
    *handled=true;
    return McuGP8403_SetMaxOutputVoltage(10);
  } else if (McuUtility_strncmp((char*)cmd, "McuGP8403 vout0 ", sizeof("McuGP8403 vout0 ")-1)==0) {
    *handled=true;
    p = cmd + sizeof("McuGP8403 vout0 ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuGP8403_SetVout0Voltage(val);
  } else if (McuUtility_strncmp((char*)cmd, "McuGP8403 vout1 ", sizeof("McuGP8403 vout1 ")-1)==0) {
    *handled=true;
    p = cmd + sizeof("McuGP8403 vout1 ")-1;
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuGP8403_SetVout1Voltage(val);
  }
  return ERR_OK;
}
#endif /* McuGP8403_CONFIG_PARSE_COMMAND_ENABLED */

void McuGP8403_Init(void) {}

void McuGP8403_Deinit(void) {}
