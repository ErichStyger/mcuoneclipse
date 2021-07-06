/**
 * \file
 * \brief MCP4728 DAC device.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for Microchip MCP4728 DAC.
 */

#include "Platform.h"
#if PL_HAS_MCP4728
#include "MCP4728.h"
#include "GI2C1.h"
#include "UTIL1.h"
#include "WAIT1.h"
#if PL_HAS_MCP4728_RDY
  #include "MCP4728_RDY.h"
#endif
#if PL_HAS_MCP4728_LDAC
  #include "MCP4728_LDAC.h"
#endif

#define MCP4728_CPU_IS_LITTLE_ENDIAN 1 /* Cpu is little endian */

/* commands */
#define MCP4728_GC_RESET            0x06 /* general call reset command */
#define MCP4728_GC_SOFTWARE_UPDATE  0x08 /* general call software command */
#define MCP4728_GC_WAKEUP           0x09 /* general call wake-up command */
#define MCP4728_GC_READ             0x0C /* general call read address bits command */

#if PL_IS_INTRO_ZUMO_K22_V2
  #define MCP4728_I2C_ADDRESS 0x61 /* default address of device (4728A1) for new/production Zumo */
#else
  #define MCP4728_I2C_ADDRESS 0x60 /* default address of device (4728UN) for prototype Zumo V2 */
#endif

bool MCP4728_IsBusy(void) {
#if PL_HAS_MCP4728_RDY
  return MCP4728_RDY_GetVal()==0; /* HIGH pin value means ready, LOW means busy */
#else
  return FALSE;
#endif
}

/*!
 * \brief General Call to reset, wake-up, sofware update or read address bits.
 */
static uint8_t MCP4728_GeneralCall(uint8_t cmd) {
  uint8_t res;
  
  res = GI2C1_SelectSlave(MCP4728_I2C_ADDRESS);
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

uint8_t MCP4728_Reset(void) {
  return MCP4728_GeneralCall(MCP4728_GC_RESET);
}

uint8_t MCP4728_Wakeup(void) {
  return MCP4728_GeneralCall(MCP4728_GC_WAKEUP);
}

uint8_t MCP4728_Update(void) {
  return MCP4728_GeneralCall(MCP4728_GC_SOFTWARE_UPDATE);
}

/* Single Write DAC Input Register (EEPROM not updated) */
uint8_t MCP4728_FastWriteDAC(uint8_t channel, uint16_t val) {
  uint8_t res;
  uint8_t data[3];

  /* 01000|DAC1|DAC0|UDAC VREF|PD1|PD0|Gx|D11-D0 */
  if (channel>3) {
    return ERR_FAILED; /* only channel 0-3 allowed */
  }
  data[0] = 0x40|((channel&0x3)<<1); /* UDAC zero */
  data[1] = (uint8_t)((val>>8)&0x0F); /* VREF, PD1, PD2 and Gx zero */
  data[2] = (uint8_t)(val&0xff); /* low byte */
  res = GI2C1_SelectSlave(MCP4728_I2C_ADDRESS);
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

/* Fast Mode Write: updates all 4 channels, but does not update EEPROM */
uint8_t MCP4728_FastWriteAllDAC(uint16_t dac[4], size_t dacSize, uint8_t pd[4], size_t pdSize) {
  uint8_t res;
  uint8_t data[4*2], *p;
  int i;
  
  /* DAC contains PD1|PD0|D11..D0 */
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
  res = GI2C1_SelectSlave(MCP4728_I2C_ADDRESS);
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


/* Single Write DAC Input Register and EEPROM */
uint8_t MCP4728_WriteDACandEE(uint8_t channel, uint16_t val) {
  uint8_t res;
  uint8_t data[3];
  
  /* 01011|DAC1|DAC0|UDAC VREF|PD1|PD0|Gx|D11-D0 */
  if (channel>3) {
    return ERR_FAILED; /* only channel 0-3 allowed */
  }
  data[0] = 0x58|((channel&0x3)<<1); /* UDAC zero */
  data[1] = (uint8_t)((val>>8)&0x0F); /* VREF, PD1, PD2 and Gx zero */
  data[2] = (uint8_t)(val&0xff); /* low byte */
  res = GI2C1_SelectSlave(MCP4728_I2C_ADDRESS);
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
#if PL_HAS_MCP4728_RDY
  while(MCP4728_IsBusy()) {
    WAIT1_WaitOSms(10); /* wait until data is written */
  }
#else
  WAIT1_WaitOSms(500); /* give EEPROM time to write data */
#endif
  return ERR_OK;
}

uint8_t MCP4728_Read(uint8_t buf[3*8], size_t bufSize) {
  uint8_t res;
  
  if (bufSize!=2*3*4) {
    return ERR_FAILED;
  }
  res = GI2C1_SelectSlave(MCP4728_I2C_ADDRESS);
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

void MCP4728_Deinit(void) {
  /* nothing */
}

void MCP4728_Init(void) {
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
  uint8_t buf[16];

  CLS1_SendStatusStr((unsigned char*)"MCP4728", (unsigned char*)"\r\n", io->stdOut);
  UTIL1_strcpy(buf, sizeof(buf), (unsigned char*)"0x");
  UTIL1_strcatNum8Hex(buf, sizeof(buf), MCP4728_I2C_ADDRESS);
  UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
  CLS1_SendStatusStr((unsigned char*)"  I2C addr", buf, io->stdOut);
  
  if (MCP4728_Read(data, sizeof(data))==ERR_OK) {
    DecodeChannelDACInputRegister((unsigned char*)"  A DAC Reg", &data[0], io);
    DecodeChannelDACInputRegister((unsigned char*)"  A EEPROM",  &data[3], io);
    DecodeChannelDACInputRegister((unsigned char*)"  B DAC Reg", &data[6], io);
    DecodeChannelDACInputRegister((unsigned char*)"  B EEPROM",  &data[9], io);
    DecodeChannelDACInputRegister((unsigned char*)"  C DAC Reg", &data[12], io);
    DecodeChannelDACInputRegister((unsigned char*)"  C EEPROM",  &data[15], io);
    DecodeChannelDACInputRegister((unsigned char*)"  D DAC Reg", &data[18], io);
    DecodeChannelDACInputRegister((unsigned char*)"  D EEPROM",  &data[21], io);
  } else {
    CLS1_SendStatusStr((unsigned char*)"MCP4728", (unsigned char*)"ERROR!\r\n", io->stdOut);
  }
#if PL_HAS_MCP4728_RDY
  CLS1_SendStatusStr((unsigned char*)"  RDY Pin", MCP4728_RDY_GetVal()!=0?(unsigned char*)"input: HIGH, ready\r\n":(unsigned char*)"input: LOW, busy\r\n", io->stdOut);
#endif
#if PL_HAS_MCP4728_LDAC
  CLS1_SendStatusStr((unsigned char*)"  LDAC Pin", MCP4728_LDAC_GetVal()!=0?(unsigned char*)"output: HIGH, output with UDAC bit\r\n":(unsigned char*)"output: LOW, immediate\r\n", io->stdOut);
#endif
  return ERR_OK;
}

static uint8_t PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"MCP4728", (unsigned char*)"Group of MCP4728 commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  reset", (unsigned char*)"General Call Reset\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  wakeup", (unsigned char*)"General Call Wake-Up\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  update", (unsigned char*)"General Call software update\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  fastwrite all 0x...", (unsigned char*)"Fast write all channel DAC values with four 12bit hex values (EEPROM not affected)\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  fastwrite <ch> 0x...", (unsigned char*)"Fast write single channel (0..3) DAC value with a 12bit hex value (EEPROM not affected)\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  write <ch> <val>", (unsigned char*)"Single write EEPROM and DAC value channel (hex 12bit) for channel 0-3\r\n", io->stdOut);
  return ERR_OK;
}

byte MCP4728_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  const unsigned char *p;

  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "MCP4728 help")==0) {
    *handled = TRUE;
    return PrintHelp(io);
  } else if ((UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0) || (UTIL1_strcmp((char*)cmd, "MCP4728 status")==0)) {
    *handled = TRUE;
    return PrintStatus(io);
  } else if (UTIL1_strcmp((char*)cmd, "MCP4728 reset")==0) {
    *handled = TRUE;
    if (MCP4728_Reset()!=ERR_OK) {
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strcmp((char*)cmd, "MCP4728 wakeup")==0) {
    *handled = TRUE;
    if (MCP4728_Wakeup()!=ERR_OK) {
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strcmp((char*)cmd, "MCP4728 update")==0) {
    *handled = TRUE;
    if (MCP4728_Update()!=ERR_OK) {
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strncmp((char*)cmd, "MCP4728 fastwrite all ", sizeof("MCP4728 fastwrite all ")-1)==0) {
    uint16_t dac[4];
    uint8_t pd[4];
    int i;
    
    *handled = TRUE;
    p = cmd+sizeof("MCP4728 fastwrite all ")-1;
    for(i=0;i<4;i++) { /* init */
      dac[i] = 0;
      pd[i] = 0;
    }
    for(i=0;i<4;i++) {
      if (UTIL1_ScanHex16uNumber(&p, &dac[i])!=ERR_OK) {
        break;
      }
      dac[i] &= MCP4728_MAX_DAC_VAL; /* ensure it is 12 bits */
    }
    if (i!=4) {
      CLS1_SendStr((unsigned char*)"**** Not enough values, 4 expected!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (MCP4728_FastWriteAllDAC(dac, sizeof(dac), pd, sizeof(pd))!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"**** FastWrite failed.\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strncmp((char*)cmd, "MCP4728 fastwrite ", sizeof("MCP4728 fastwrite ")-1)==0) {
    /* e.g. MCP4728 fastwrite 2 0x512 */
    uint16_t dac=0;
    uint8_t channel=0;

    *handled = TRUE;
    p = cmd+sizeof("MCP4728 fastwrite ")-1;
    if (UTIL1_ScanDecimal8uNumber(&p, &channel)!=ERR_OK || channel>3) {
      CLS1_SendStr((unsigned char*)"**** error parsing channel, must be 0, 1, 2 or 3!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    if (UTIL1_ScanHex16uNumber(&p, &dac)!=ERR_OK || dac>MCP4728_MAX_DAC_VAL) {
      CLS1_SendStr((unsigned char*)"**** error parsing 12bit hex value, must start with 0x!\r\n", io->stdErr);
      return ERR_FAILED;
    }
    dac &= MCP4728_MAX_DAC_VAL; /* ensure it is 12 bits */
    if (MCP4728_FastWriteDAC(channel, dac)!=ERR_OK) {
      CLS1_SendStr((unsigned char*)"**** Write channel DAC failed!\r\n", io->stdErr);
      return ERR_FAILED;
    } else {
      return ERR_OK;
    }
  } else if (UTIL1_strncmp((char*)cmd, "MCP4728 write ", sizeof("MCP4728 write ")-1)==0) {
    uint16_t dac;
    uint8_t ch, res;
    
    *handled = TRUE;
    res = ERR_OK;
    p = cmd+sizeof("MCP4728 write ")-1;
    if (UTIL1_ScanDecimal8uNumber(&p, &ch)!=ERR_OK || ch>3) {
      CLS1_SendStr((unsigned char*)"**** Failed reading channel. Must be 0, 1, 2 or 3\r\n", io->stdErr);
      res = ERR_FAILED;
    } else {
      if (UTIL1_ScanHex16uNumber(&p, &dac)!=ERR_OK) {
        CLS1_SendStr((unsigned char*)"**** Failed DAC value, must start with 0x\r\n", io->stdErr);
        res = ERR_FAILED;
      } else {
        if (MCP4728_WriteDACandEE(ch, dac)!=ERR_OK) {
          CLS1_SendStr((unsigned char*)"**** Write failed.\r\n", io->stdErr);
          res = ERR_FAILED;
        }
      }
    }
    return res;
  }
  return ERR_OK;
}
#endif /* PL_HAS_MCP4728 */
