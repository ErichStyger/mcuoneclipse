/**
 * \file
 * \brief Driver for the the W5100
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html).
 * Credits to:
 * - http://www.ermicro.com/blog/?p=1773
 * - http://www.seanet.com/~karllunt/w5100_library.html
 *
 * This module is implements a low level driver for the W5100 chip.
 */

/* https://github.com/braiden/embedded-ac-controller/blob/master/w5100.c */
/* http://www.seanet.com/~karllunt/w5100_library.html */

#include "w5100.h"
#include "ETH_CS.h"
#include "ETH_INT.h"
#include "WAIT1.h"
#include "SM1.h"
#include "FRTOS1.h"
#include "CLS1.h"
#include "UTIL1.h"
#include "SPI.h"

#define W5100_CS_ENABLE()   ETH_CS_ClrVal() /* chip select is low active */
#define W5100_CS_DISABLE()  ETH_CS_SetVal() /* chip select is low active */

uint8_t W5100_MemWriteByte(uint16_t addr, uint8_t val) {
  SPI_RequestSPIBus();
  W5100_CS_ENABLE();
  SPI_WriteByte(W5100_CMD_WRITE);
  SPI_WriteByte(addr>>8); /* high address */
  SPI_WriteByte(addr&0xff); /* low address */
  SPI_WriteByte(val); /* data */
  W5100_CS_DISABLE();
  SPI_ReleaseSPIBus();
  return ERR_OK;
}

uint8_t W5100_MemReadByte(uint16_t addr, uint8_t *val) {
  SPI_RequestSPIBus();
  W5100_CS_ENABLE();
  SPI_WriteByte(W5100_CMD_READ);
  SPI_WriteByte(addr>>8); /* high address */
  SPI_WriteByte(addr&0xff); /* low address */
  *val = SPI_ReadByte(); /* data */
  W5100_CS_DISABLE();
  SPI_ReleaseSPIBus();
  return ERR_OK;
}

uint8_t W5100_MemWriteWord(uint16_t addr, uint16_t val) {
  SPI_RequestSPIBus();

  W5100_CS_ENABLE();
  SPI_WriteByte(W5100_CMD_WRITE);
  SPI_WriteByte(addr>>8); /* high address */
  SPI_WriteByte(addr&0xff); /* low address */
  SPI_WriteByte(val>>8); /* data */
  W5100_CS_DISABLE();

  addr++;
  W5100_CS_ENABLE();
  SPI_WriteByte(W5100_CMD_WRITE);
  SPI_WriteByte(addr>>8); /* high address */
  SPI_WriteByte(addr&0xff); /* low address */
  SPI_WriteByte(val&0xff); /* data */
  W5100_CS_DISABLE();

  SPI_ReleaseSPIBus();
  return ERR_OK;
}

uint8_t W5100_MemReadWord(uint16_t addr, uint16_t *val) {
  uint8_t low, high;
  
  SPI_RequestSPIBus();

  W5100_CS_ENABLE();
  SPI_WriteByte(W5100_CMD_READ);
  SPI_WriteByte(addr>>8); /* high address */
  SPI_WriteByte(addr&0xff); /* low address */
  high = SPI_ReadByte(); /* data */
  W5100_CS_DISABLE();
  
  addr++;
  W5100_CS_ENABLE();
  SPI_WriteByte(W5100_CMD_READ);
  SPI_WriteByte(addr>>8); /* high address */
  SPI_WriteByte(addr&0xff); /* low address */
  low = SPI_ReadByte(); /* data */
  W5100_CS_DISABLE();
  
  SPI_ReleaseSPIBus();
  
  *val = (high<<8)|low;
  return ERR_OK;
}

uint8_t W5100_MemReadBlock(uint16_t addr, void *data, size_t dataSize) {
  while(dataSize>0) {
    if (W5100_MemReadByte(addr, (uint8_t*)data)!=ERR_OK) {
      return ERR_FAILED;
    }
    data++; addr++; dataSize--;
  }
  return ERR_OK;
}

uint8_t W5100_MemWriteBlock(uint16_t addr, void *data, size_t dataSize) {
  while(dataSize>0) {
    if (W5100_MemWriteByte(addr, *((uint8_t*)data))!=ERR_OK) {
      return ERR_FAILED;
    }
    data++; addr++; dataSize--;
  }
  return ERR_OK;
}

uint8_t W5100_WriteConfig(w5100_config_t *config) {
  return W5100_MemWriteBlock(W5100_GAR0, (void*)config, sizeof(w5100_config_t));
}

uint8_t W5100_ReadConfig(w5100_config_t *config) {
  return W5100_MemReadBlock(W5100_GAR0, (void*)config, sizeof(w5100_config_t));
}

void W5100_Init(void) {
  /* bring reset pin low */
 // ETH_RESET_ClrVal();
 // WAIT1_Waitms(10);
 // ETH_RESET_SetVal();
  /* gateway IP register */
}

static uint8_t PrintStatus(CLS1_ConstStdIOType *io) {
  w5100_config_t config;
  uint8_t buf[24];
  int i;
  
  CLS1_SendStatusStr((unsigned char*)"w5100", (unsigned char*)"\r\n", io->stdOut);
  if (W5100_ReadConfig(&config)!=ERR_OK) {
    CLS1_SendStr((unsigned char*)"ReadConfig() failed!\r\n", io->stdErr);
    return ERR_FAILED;
  }
  /* gateway address */
  buf[0] = '\0';
  for(i=0;i<sizeof(config.gateway);i++) {
    UTIL1_strcatNum8u(buf, sizeof(buf), config.gateway[i]);
    if (i<sizeof(config.gateway)-1) {
      UTIL1_chcat(buf, sizeof(buf), '.');
    } else {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    }
  }
  CLS1_SendStatusStr((unsigned char*)"  Gateway", buf, io->stdOut);
  /* netmask */
  buf[0] = '\0';
  for(i=0;i<sizeof(config.netmask);i++) {
    UTIL1_strcatNum8u(buf, sizeof(buf), config.netmask[i]);
    if (i<sizeof(config.netmask)-1) {
      UTIL1_chcat(buf, sizeof(buf), '.');
    } else {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    }
  }
  CLS1_SendStatusStr((unsigned char*)"  NetMask", buf, io->stdOut);
  /* HW/MAC address */
  buf[0] = '\0';
  for(i=0;i<sizeof(config.hwaddr);i++) {
    UTIL1_strcatNum8Hex(buf, sizeof(buf), config.hwaddr[i]);
    if (i<sizeof(config.hwaddr)-1) {
      UTIL1_chcat(buf, sizeof(buf), '-');
    } else {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    }
  }
  CLS1_SendStatusStr((unsigned char*)"  MAC", buf, io->stdOut);
  /* IP address */
  buf[0] = '\0';
  for(i=0;i<sizeof(config.ipaddr);i++) {
    UTIL1_strcatNum8u(buf, sizeof(buf), config.ipaddr[i]);
    if (i<sizeof(config.ipaddr)-1) {
      UTIL1_chcat(buf, sizeof(buf), '.');
    } else {
      UTIL1_strcat(buf, sizeof(buf), (unsigned char*)"\r\n");
    }
  }
  CLS1_SendStatusStr((unsigned char*)"  IP", buf, io->stdOut);
  return ERR_OK;
}

uint8_t W5100_ParseCommand(const unsigned char *cmd, bool *handled, CLS1_ConstStdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, "w5100 help")==0) {
    CLS1_SendHelpStr((unsigned char*)"w5100", (const unsigned char*)"Group of w5100 commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*)"  help|status", (const unsigned char*)"Print help or status information\r\n", io->stdOut);
    *handled = TRUE;
    return ERR_OK;
  } else if (UTIL1_strcmp((char*)cmd, CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, "w5100 status")==0) {
    *handled = TRUE;
    return PrintStatus(io);
  }
  return ERR_OK; /* no error */
}
