/*
 * AD5252.c
 *
 *  Created on: 12.02.2018
 *      Author: Erich Styger Local
 */

#include "Platform.h"
#include "AD5141.h"
#include "GI2C1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "RESET.h"
#include "WAIT1.h"

#define AD5141_I2C_ADDR   0b0101111 /* S01011xx with xx set to 1 if ADDRx pins to GND */

uint8_t AD5141_HardwareReset(void) {
  RESET_ClrVal(); /* reset is LOW active */
  WAIT1_Waitus(2*30); /* double the minimal time */
  RESET_SetVal();
  return ERR_OK;
}

uint8_t AD5141_ReadEEMEMReg(uint8_t *val) {
  uint8_t addr[2];

  addr[0] = 0b00110000;
  addr[1] = 0b00000001;
  *val = 0; /* init */
  return GI2C1_ReadAddress(AD5141_I2C_ADDR, &addr[0], sizeof(addr), val, sizeof(uint8_t));
}

uint8_t AD5141_ReadRDACReg(uint8_t *val) {
  uint8_t addr[2];

  addr[0] = 0b00110000;
  addr[1] = 0b00000011;
  *val = 0; /* init */
  return GI2C1_ReadAddress(AD5141_I2C_ADDR, &addr[0], sizeof(addr), val, sizeof(uint8_t));
}

uint8_t AD5141_WriteRDACReg(uint8_t val) {
  uint8_t addr;

  addr = 0b00010000;
  return GI2C1_WriteAddress(AD5141_I2C_ADDR, &addr, sizeof(addr), &val, sizeof(val));
}

uint8_t AD5141_WriteEEMEMReg(uint8_t val) {
  uint8_t addr;

  addr = 0b10000000;
  return GI2C1_WriteAddress(AD5141_I2C_ADDR, &addr, sizeof(addr), &val, sizeof(val));
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"ad5141", (unsigned char*)"Group of ad5141 commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  hwreset", (unsigned char*)"Reset the device pulling the RESET pin low\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  write rdac <val>", (unsigned char*)"Write value to RDAC register\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  write eeprom <val>", (unsigned char*)"Write value to EEPROM register\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t buf[32];
  uint8_t res, val;

  CLS1_SendStatusStr((unsigned char*)"ad5141", (unsigned char*)"\r\n", io->stdOut);

  res = AD5141_ReadRDACReg(&val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  RDAC", buf, io->stdOut);

  res = AD5141_ReadEEMEMReg(&val);
  if (res==ERR_OK) {
    UTIL1_Num8uToStr(buf, sizeof(buf), val);
    UTIL1_strcat(buf, sizeof(buf), "\n");
  } else {
    UTIL1_strcpy(buf, sizeof(buf), "ERROR\n");
  }
  CLS1_SendStatusStr((unsigned char*)"  EMEM", buf, io->stdOut);

  return ERR_OK;
}

uint8_t AD5141_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io) {
  uint8_t res = ERR_OK;
  uint8_t val;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP) == 0
    || UTIL1_strcmp((char*)cmd, "ad5141 help") == 0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if (   (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0)
             || (UTIL1_strcmp((char*)cmd, "ad5141 status") == 0)
            )
  {
    *handled = TRUE;
    res = PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "ad5141 hwreset") == 0) {
    *handled = TRUE;
    return AD5141_HardwareReset();
  } else if (UTIL1_strncmp((char*)cmd, "ad5141 write rdac", sizeof("ad5141 write rdac")-1) == 0) {
    cmd += sizeof("ad5141 write rdac")-1;
    res = UTIL1_ScanDecimal8uNumber(&cmd, &val);
    if (res==ERR_OK) {
      res = AD5141_WriteRDACReg(val);
      if (res!=ERR_OK) {
        CLS1_SendStr("failed writing RDAC!\n", io->stdErr);
      }
    } else {
      CLS1_SendStr("failed scanning number!\n", io->stdErr);
    }
    *handled = TRUE;
  } else if (UTIL1_strncmp((char*)cmd, "ad5141 write eeprom", sizeof("ad5141 write eeprom")-1) == 0) {
    cmd += sizeof("ad5141 write eeprom")-1;
    res = UTIL1_ScanDecimal8uNumber(&cmd, &val);
    if (res==ERR_OK) {
      res = AD5141_WriteEEMEMReg(val);
      if (res!=ERR_OK) {
        CLS1_SendStr("failed writing EEPROM!\n", io->stdErr);
      }
    } else {
      CLS1_SendStr("failed scanning number!\n", io->stdErr);
    }
    *handled = TRUE;
  }
  return res;
}

void AD5141_Init(void) {
  AD5141_HardwareReset();
}
