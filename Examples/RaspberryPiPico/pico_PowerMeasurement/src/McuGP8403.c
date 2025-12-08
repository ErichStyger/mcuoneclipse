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
  McuGP8403_ADDR_CONFIG_REGISTER     = 0x01,  /**< writing 0x00: 0-5V, writing 0x11: 0-10V */
  McuGP8403_ADDR_VOUT0_REGISTER      = 0x02,  /**< VOUT0 12bit data register (5 and 10V output) */
  McuGP8403_ADDR_VOUT1_REGISTER      = 0x04,  /**< VOUT1 12bit data register (5 and 10V output) */
} McuGP8403_Reg_e;

/* because we cannot read back from the device somehow, we store the settings here in a struct */
typedef struct McuGP8403_State_t {
  uint8_t maxOutputVoltage; /* 5 or 10, in Volt */
  uint16_t vout0, vout1;    /* 12bit value of DAC */
} McuGP8403_State_t;

static McuGP8403_State_t devices[McuGP8403_CONFIG_NOF_DEVICES];

#define SWAP_BYTES(u16)  (((u16)<<8)|((u16)>>8))

uint8_t McuGP8403_ReadRegisterByte(uint8_t idx, McuGP8403_Reg_e reg, uint8_t *value) {
  uint8_t res;
  uint8_t data;

  res = McuGenericI2C_ReadByteAddress8(McuGP8403_CONFIG_I2C_ADDRESS+idx, reg, &data);
  if (res!=ERR_OK) {
    return res;
  }
  *value = data;
  return ERR_OK;
}

uint8_t McuGP8403_ReadRegisterWord(uint8_t idx, McuGP8403_Reg_e reg, uint16_t *value) {
  uint8_t res;
  uint16_t data;

  res = McuGenericI2C_ReadWordAddress8(McuGP8403_CONFIG_I2C_ADDRESS+idx, reg, &data);
  if (res!=ERR_OK) {
    return res;
  }
  *value = data;
  return ERR_OK;
}

uint8_t McuGP8403_WriteRegisterByte(uint8_t idx, McuGP8403_Reg_e reg, uint8_t value) {
  return McuGenericI2C_WriteByteAddress8(McuGP8403_CONFIG_I2C_ADDRESS+idx, reg, value);
}

uint8_t McuGP8403_WriteRegisterWord(uint8_t idx, McuGP8403_Reg_e reg, uint16_t value) {
  return McuGenericI2C_WriteWordAddress8(McuGP8403_CONFIG_I2C_ADDRESS+idx, reg, value);
}

uint8_t McuGP8403_SetMaxOutputVoltage(uint8_t idx, uint8_t v) {
  uint8_t res;

  if (idx>=McuGP8403_CONFIG_NOF_DEVICES) {
    return ERR_RANGE;
  }
  if (!(v==5 || v==10)) {
    return ERR_RANGE; /* only 5 or 10 allowed */
  }
  res = McuGP8403_WriteRegisterByte(idx, McuGP8403_ADDR_CONFIG_REGISTER, v==5?0x0:0x11); /* write 0x00 for 5V and 0x11 for 10V */
  if (res!=ERR_OK) {
    return ERR_FAILED;
  }
  devices[idx].maxOutputVoltage = v;
  return ERR_OK;
}

uint8_t McuGP8403_GetMaxOutputVoltage(uint8_t idx, uint8_t *v) {
  if (idx>=McuGP8403_CONFIG_NOF_DEVICES) {
    return ERR_RANGE;
  }
#if 0 /* reading from the device does not work? */
  uint8_t res, val8;

  *v = 0;
  res = McuGP8403_ReadRegisterByte(McuGP8403_ADDR_CONFIG_REGISTER+idx, &val8);
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
#else
  /* \TODO calculate voltage */
  *v = devices[idx].maxOutputVoltage;
  return ERR_OK;
#endif
}

uint8_t McuGP8403_SetVoutxVoltage(uint8_t idx, uint8_t reg, uint16_t val) {
  uint8_t res;
  uint16_t n;

  if (idx>=McuGP8403_CONFIG_NOF_DEVICES) {
    return ERR_RANGE;
  }
  uint8_t hibyte = ((val << 4) & 0xff00) >> 8; 
  uint8_t lobyte = ((val << 4) & 0xff);
  n = lobyte << 8 | hibyte;
  n = SWAP_BYTES(n);
  res = McuGP8403_WriteRegisterWord(idx, reg, n);
  if (res!=ERR_OK) {
    return res; /* error case */
  }
  if (reg==McuGP8403_ADDR_VOUT0_REGISTER) {
    devices[idx].vout0 = val;
  } else {
    devices[idx].vout1 = val;
  }
  return ERR_OK;
}

uint8_t McuGP8403_SetVout0Voltage(uint8_t idx, uint16_t val) {
  return McuGP8403_SetVoutxVoltage(idx, McuGP8403_ADDR_VOUT0_REGISTER, val);
}

uint8_t McuGP8403_SetVout1Voltage(uint8_t idx, uint16_t val) {
  return McuGP8403_SetVoutxVoltage(idx, McuGP8403_ADDR_VOUT1_REGISTER, val);
}

uint8_t McuGP8403_GetVoutxVoltage(uint8_t idx, uint8_t reg, uint16_t *val) {
  uint8_t res, v;
  uint16_t val16;

  if (idx>=McuGP8403_CONFIG_NOF_DEVICES) {
    return ERR_RANGE;
  }
  #if 0 /* reading device register does not work? */
    res = McuGP8403_ReadRegisterWord(idx, reg, &val16); /* always reads 0x1111 ??? */
    if (res!=ERR_OK) {
      return res; /* error case */
    }
    val16 = (val16>>12) | (val16<<4); /* swap bytes and ignore lower 4 bits of Data0low */
  #else
    if (reg==McuGP8403_ADDR_VOUT0_REGISTER) {
      val16 = devices[idx].vout0;
    } else {
      val16 = devices[idx].vout1;
    }
  #endif
  #if 0 /* \todo */
  res = McuGP8403_GetMaxOutputVoltage(&v);
  if (res!=ERR_OK) {
    return res; /* error case */
  }
  #endif
  *val = val16;
  return ERR_OK;
}

uint8_t McuGP8403_GetVout0Voltage(uint8_t idx, uint16_t *val) {
#if 0 /* reading back registers does not work */
  return McuGP8403_ReadRegisterWord(idx, McuGP8403_ADDR_VOUT0_REGISTER, val);
#else
  return McuGP8403_GetVoutxVoltage(idx, McuGP8403_ADDR_VOUT0_REGISTER, val);
#endif
}

uint8_t McuGP8403_GetVout1Voltage(uint8_t idx, uint16_t *val) {
#if 0 /* reading back registers does not work */
  return McuGP8403_ReadRegisterWord(idx, McuGP8403_ADDR_VOUT1_REGISTER, val);
#else
  return McuGP8403_GetVoutxVoltage(idx, McuGP8403_ADDR_VOUT1_REGISTER, val);
#endif
}

#if McuGP8403_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint8_t buf[32], res, val8;
  uint16_t val16;

  McuShell_SendStatusStr((unsigned char*)"McuGP8403", (unsigned char*)"GP8403 DAC status\r\n", io->stdOut);

  
  McuUtility_Num8uToStr(buf, sizeof(buf), McuGP8403_CONFIG_NOF_DEVICES);
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr("  nof devices", buf, io->stdOut);

  buf[0] = '\0';
  for(int idx=0; idx<McuGP8403_CONFIG_NOF_DEVICES; idx++) {
    res = McuGP8403_GetMaxOutputVoltage(idx, &val8);
    if (res==ERR_OK) {
      McuUtility_strcat(buf, sizeof(buf), "0-");
      McuUtility_strcatNum8u(buf, sizeof(buf), val8);
      McuUtility_strcat(buf, sizeof(buf), "V ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), "read failed ");
    }
  }
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr("  voltage", buf, io->stdOut);

  buf[0] = '\0';
  for(int idx=0; idx<McuGP8403_CONFIG_NOF_DEVICES; idx++) {
    res = McuGP8403_GetVout0Voltage(idx, &val16);
    if (res==ERR_OK) {
      McuUtility_strcat(buf, sizeof(buf), "0x");
      McuUtility_strcatNum16Hex(buf, sizeof(buf), val16);
      McuUtility_strcat(buf, sizeof(buf), " ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), "read failed ");
    }
  }
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr("  vout0", buf, io->stdOut);

  buf[0] = '\0';
  for(int idx=0; idx<McuGP8403_CONFIG_NOF_DEVICES; idx++) {
    res = McuGP8403_GetVout1Voltage(idx, &val16);
    if (res==ERR_OK) {
      McuUtility_strcat(buf, sizeof(buf), "0x");
      McuUtility_strcatNum16Hex(buf, sizeof(buf), val16);
      McuUtility_strcat(buf, sizeof(buf), " ");
    } else {
      McuUtility_strcat(buf, sizeof(buf), "read failed ");
    }
  }
  McuUtility_strcat(buf, sizeof(buf), "\r\n");
  McuShell_SendStatusStr("  vout1", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuGP8403", (unsigned char*)"Group of GP8403 DAC commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  voltage <idx> 5|10", (unsigned char*)"Set maximum output voltage to 5V or 10V for device index\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  vout0|vout1 <idx> <val>", (unsigned char*)"Set vout0 or vout1 output voltage for device index\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuGP8403_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  const unsigned char *p;
  int32_t val, idx;

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
  } else if (McuUtility_strncmp((char*)cmd, "McuGP8403 voltage ", sizeof("McuGP8403 voltage ")-1)==0) {
    *handled=true;
    p = cmd + sizeof("McuGP8403 voltage ")-1;
    if (McuUtility_xatoi(&p, &idx)!=ERR_OK && idx<0) {
      return ERR_FAILED;
    }
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuGP8403_SetMaxOutputVoltage(idx, val);
  } else if (McuUtility_strncmp((char*)cmd, "McuGP8403 vout0 ", sizeof("McuGP8403 vout0 ")-1)==0) {
    *handled=true;
    p = cmd + sizeof("McuGP8403 vout0 ")-1;
    if (McuUtility_xatoi(&p, &idx)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuGP8403_SetVout0Voltage(idx, val);
  } else if (McuUtility_strncmp((char*)cmd, "McuGP8403 vout1 ", sizeof("McuGP8403 vout1 ")-1)==0) {
    *handled=true;
    p = cmd + sizeof("McuGP8403 vout1 ")-1;
    if (McuUtility_xatoi(&p, &idx)!=ERR_OK) {
      return ERR_FAILED;
    }
    if (McuUtility_xatoi(&p, &val)!=ERR_OK) {
      return ERR_FAILED;
    }
    return McuGP8403_SetVout1Voltage(idx, val);
  }
  return ERR_OK;
}
#endif /* McuGP8403_CONFIG_PARSE_COMMAND_ENABLED */

void McuGP8403_Init(void) {
  for(int i=0; i<McuGP8403_CONFIG_NOF_DEVICES; i++) {
    devices[i].maxOutputVoltage = 10;
    devices[i].vout0 = 0;
    devices[i].vout1 = 0;
  }
}

void McuGP8403_Deinit(void) {}
