/*
 * AD5252.c
 *
 *  Created on: 12.02.2018
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#include "AD5252.h"
#include "GI2C1.h"
#include "CLS1.h"
#include "UTIL1.h"

#define AD5252_I2C_ADDR   0b0101100 /* S01011xx */

#define AD5252_I2C_CMD    (1<<7)
#define AD5252_I2C_REG    (0<<7)

#define AD5252_I2C_EE     (1<<5)
#define AD5252_I2C_RDAC   (0<<5)

uint8_t AD5252_ReadEEMEMReg(AD5252_EEMEM_REG reg, uint8_t *val) {
  uint8_t addr;

  addr = reg | AD5252_I2C_REG | AD5252_I2C_EE;
  *val = 0; /* init */
  return GI2C1_ReadAddress(AD5252_I2C_ADDR, &addr, sizeof(addr), val, sizeof(uint8_t));
}

uint8_t AD5252_ReadRDACReg(AD5252_RDAC_REG reg, uint8_t *val) {
  uint8_t addr;

  addr = reg | AD5252_I2C_REG | AD5252_I2C_RDAC;
  *val = 0; /* init */
  return GI2C1_ReadAddress(AD5252_I2C_ADDR, &addr, sizeof(addr), val, sizeof(uint8_t));
}

uint8_t AD5252_WriteRDACReg(AD5252_RDAC_REG reg, uint8_t val) {
  uint8_t addr;

  addr = reg | AD5252_I2C_REG | AD5252_I2C_RDAC;
  return GI2C1_WriteAddress(AD5252_I2C_ADDR, &addr, sizeof(addr), &val, sizeof(val));
}

uint8_t AD5252_WriteEEMEMReg(AD5252_EEMEM_REG reg, uint8_t val) {
  uint8_t addr;

  addr = reg | AD5252_I2C_REG | AD5252_I2C_EE;
  return GI2C1_WriteAddress(AD5252_I2C_ADDR, &addr, sizeof(addr), &val, sizeof(val));
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"ad5252", (unsigned char*)"Group of ad5252 commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  write rdac1|rdac3 <val>", (unsigned char*)"Write value to RDAC1 or RDAC3 register\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  uint8_t res, val;

  CLS1_SendStatusStr((unsigned char*)"ad5252", (unsigned char*)"\r\n", io->stdOut);

  res = AD5252_ReadRDACReg(AD5252_RDAC1, &val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  RDAC1", buf, io->stdOut);

  res = AD5252_ReadRDACReg(AD5252_RDAC3, &val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  RDAC3", buf, io->stdOut);

  res = AD5252_ReadEEMEMReg(AD5252_EEMEM1, &val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  EMEM1", buf, io->stdOut);

  res = AD5252_ReadEEMEMReg(AD5252_EEMEM3, &val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  EMEM3", buf, io->stdOut);

  res = AD5252_ReadEEMEMReg(AD5252_EEMEM4, &val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  EMEM4", buf, io->stdOut);

  res = AD5252_ReadEEMEMReg(AD5252_EEMEM5, &val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  EMEM5", buf, io->stdOut);

  res = AD5252_ReadEEMEMReg(AD5252_EEMEM6, &val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  EMEM6", buf, io->stdOut);

  /* \todo list EEMEM7 to EEMEM15 */
  return ERR_OK;
}

uint8_t AD5252_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  uint8_t val;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
    || UTIL1_strcmp((char*)cmd, "ad5252 help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0)
             || (UTIL1_strcmp((char*)cmd, "ad5252 status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (UTIL1_strncmp((char*)cmd, "ad5252 write rdac", sizeof("ad5252 write rdac")-1) == 0) {
    AD5252_RDAC_REG reg;

    cmd += sizeof("ad5252 write rdac")-1;
    if (*cmd=='1') {
      reg = AD5252_RDAC1;
    } else if (*cmd=='3') {
      reg = AD5252_RDAC3;
    } else {
      CLS1_SendStr("Unknown RDAC register number!\n", io->stdErr);
      return ERR_FAILED;
    }
    cmd++;
    res = UTIL1_ScanDecimal8uNumber(&cmd, &val);
    if (res==ERR_OK) {
      res = AD5252_WriteRDACReg(reg, val);
      if (res!=ERR_OK) {
        CLS1_SendStr("failed writing RDAC!\n", io->stdErr);
      }
    } else {
      CLS1_SendStr("failed scanning number!\n", io->stdErr);
    }
    *handled = TRUE;
  }
  return res;
}


void AD5252_Init(void) {

}
