/*
 * MPC4728.c
 *
 *  Created on: Jan 30, 2014
 *      Author: tastyger
 */

#include "MPC4728.h"
#include "GI2C1.h"
#include "UTIL1.h"

#define MPC4728_CPU_IS_LITTLE_ENDIAN 1 /* Cpu is little endian */

/* commands */
#define MPC4728_GC_RESET            0x06 /* general call reset command */
#define MPC4728_GC_SOFTWARE_UPDATE  0x08 /* general call software command */
#define MPC4728_GC_WAKEUP           0x09 /* general call wake-up command */
#define MPC4728_GC_READ             0x0C /* general call read address bits command */

#define MPC4728_I2C_ADDRESS 0x60 /* default address of device */

static uint8_t MPC4728_GeneralCall(uint8_t cmd) {
  uint8_t res;
  
  res = GI2C1_SelectSlave(MPC4728_I2C_ADDRESS);
  if (res!=ERR_OK) {
    return res;
  }
  res = GI2C1_WriteBlock(&cmd, sizeof(cmd), GI2C1_SEND_STOP);
  if (res!=ERR_OK) {
    (void)GI2C1_UnselectSlave();
    return res;
  }
  res = GI2C1_UnselectSlave();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t MPC4728_Reset(void) {
  return MPC4728_GeneralCall(MPC4728_GC_RESET);
}

uint8_t MPC4728_Wakeup(void) {
  return MPC4728_GeneralCall(MPC4728_GC_WAKEUP);
}

uint8_t MPC4728_Update(void) {
  return MPC4728_GeneralCall(MPC4728_GC_SOFTWARE_UPDATE);
}

uint8_t MPC4728_FastWrite(uint16_t dac[4], size_t dacSize, uint8_t pd[4], size_t pdSize) {
  uint8_t res;
  uint8_t data[4*2], *p;
  int i;
  
  /* dac contains PD1|PD0|D11..D0 */
  if (dacSize!=4*sizeof(uint16_t) || pdSize!=4) {
    return ERR_FAILED;
  }
  p = &data[0];
  for(i=0;i<4;i++) {
    *p = (pd[i]&0x3)<<4;
    *p |= (dac[i]>>8)&0x0F;
    p++;
    *p = (uint8_t)(dac[i]&0xFF);
    p++;
  }
  res = GI2C1_SelectSlave(MPC4728_I2C_ADDRESS);
  if (res!=ERR_OK) {
    return res;
  }
  res = GI2C1_WriteBlock(data, sizeof(data), GI2C1_SEND_STOP);
  if (res!=ERR_OK) {
    (void)GI2C1_UnselectSlave();
    return res;
  }
  res = GI2C1_UnselectSlave();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t MPC4728_SingleWrite(uint8_t channel, uint16_t val) {
  uint8_t res;
  uint8_t data[3];
  
  /* 01011|DAC1|DAC0|UDAC VREF|PD1|PD0|Gx|D11-D0 */
  data[0] = 0xB0|((channel&0x3)<<1);
  data[1] = (uint8_t)(val>>8);
  data[2] = (uint8_t)(val&0xff);
  res = GI2C1_SelectSlave(MPC4728_I2C_ADDRESS);
  if (res!=ERR_OK) {
    return res;
  }
  res = GI2C1_WriteBlock(&data[0], sizeof(data), GI2C1_SEND_STOP);
  if (res!=ERR_OK) {
    (void)GI2C1_UnselectSlave();
    return res;
  }
  res = GI2C1_UnselectSlave();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

uint8_t MPC4728_Read(uint8_t buf[3*8], size_t bufSize) {
  uint8_t res;
  
  if (bufSize!=2*3*4) {
    return ERR_FAILED;
  }
  res = GI2C1_SelectSlave(MPC4728_I2C_ADDRESS);
  if (res!=ERR_OK) {
    return res;
  }
  res = GI2C1_ReadBlock(buf, bufSize, GI2C1_SEND_STOP);
  if (res!=ERR_OK) {
    (void)GI2C1_UnselectSlave();
    return res;
  }
  res = GI2C1_UnselectSlave();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

void MPC4728_Deinit(void) {
  /* nothing */
}

void MPC4728_Init(void) {
  /* nothing */
}

static void DecodeChannelDACInputRegister(uint8_t *info, uint8_t data[3], const CLS1_StdIOType *io) {
  uint8_t buf[16];
  
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), data[0]);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), data[1]);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)" 0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), data[2]);
  CLS1_SendStatusStr(info, buf, io->stdOut);
  CLS1_SendStr((unsigned char*)"\r\n", io->stdOut);
}

static uint8_t PrintStatus(const CLS1_StdIOType *io) {
  uint8_t data[2*3*4];
  
  if (MPC4728_Read(data, sizeof(data))==ERR_OK) {
    CLS1_SendStatusStr((unsigned char*)"MPC4728", (unsigned char*)"\r\n", io->stdOut);
    DecodeChannelDACInputRegister((unsigned char*)"  A DAC Reg", &data[0], io);
    DecodeChannelDACInputRegister((unsigned char*)"  A EEPROM",  &data[3], io);
    DecodeChannelDACInputRegister((unsigned char*)"  B DAC Reg", &data[6], io);
    DecodeChannelDACInputRegister((unsigned char*)"  B EEPROM",  &data[9], io);
    DecodeChannelDACInputRegister((unsigned char*)"  C DAC Reg", &data[12], io);
    DecodeChannelDACInputRegister((unsigned char*)"  C EEPROM",  &data[15], io);
    DecodeChannelDACInputRegister((unsigned char*)"  D DAC Reg", &data[18], io);
    DecodeChannelDACInputRegister((unsigned char*)"  D EEPROM",  &data[21], io);
  } else {
    CLS1_SendStatusStr((unsigned char*)"MPC4728", (unsigned char*)"ERROR!\r\n", io->stdOut);
  }
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"MPC4728", (unsigned char*)"Group of MPC4728 commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"General Call Reset\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  wakeup", (unsigned char*)"General Call Wake-Up\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  update", (unsigned char*)"General Call software update\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  fastwrite 0x...", (unsigned char*)"Fast write DAC values. Command followed by 4 hex values\r\n", io->stdOut);
  return ERR_OK;
}

byte MPC4728_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "MPC4728 help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "MPC4728 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "MPC4728 reset")==0) {
    *handled = TRUE;
    if (MPC4728_Reset()!=ERR_OK) {
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strcmp((char*)cmd, "MPC4728 wakeup")==0) {
    *handled = TRUE;
    if (MPC4728_Wakeup()!=ERR_OK) {
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strcmp((char*)cmd, "MPC4728 update")==0) {
    *handled = TRUE;
    if (MPC4728_Update()!=ERR_OK) {
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strncmp((char*)cmd, "MPC4728 fastwrite ", sizeof("MPC4728 fastwrite ")-1)==0) {
    uint16_t dac[4];
    uint8_t pd[4];
    int i;
    
    *handled = TRUE;
    p = cmd+sizeof("I2CSPY1 fastwrite ")-1;
    for(i=0;i<4;i++) { /* init */
      dac[i] = 0;
      pd[i] = 0;
    }
    for(i=0;i<4;i++) {
      if (UTIL1_ScanHex16uNumber(&p, &dac[i])!=ERR_OK) {
        break;
      }
      dac[i] &= 0xFFF; /* ensure it is 12 bits */
    }
    if (i!=4) {
      CLS1_SendStr((unsigned char*)"**** Not enough values, 4 expected.\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (MPC4728_FastWrite(dac, sizeof(dac), pd, sizeof(pd))!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"**** FastWrite failed.\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  }
  return ERR_OK;
}
