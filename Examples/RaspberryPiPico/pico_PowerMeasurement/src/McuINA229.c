/**
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * \brief Driver for the TI INA229 SPI current/voltage sensor.
 */

#include "McuINA229.h"
#include "McuUtility.h"
#include "McuLog.h"
#include "McuSPI.h"
#include "McuGPIO.h"

typedef enum {
  McuINA229_REG_CONFIG        = 0x00,
  McuINA229_REG_ADC_CONFIG    = 0x01,
  McuINA229_REG_DEVICE_ID     = 0x3F,
} McuINA229_REG_e;

static struct {
  McuGPIO_Handle_t cs; /* chip select (output) pin, LOW active */
  McuGPIO_Handle_t alert; /* alert (innput) pin, default state is active LOW */
} device;

static void SPI_Select(void) {
  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_SetLow(device.cs);
  #endif
}

static void SPI_Unselect(void) {
  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_SetHigh(device.cs);
  #endif
}

static uint8_t SPI_CmdReadBytes2(uint8_t reg, uint16_t *data) {
  uint8_t tx[3], rx[3], res;

  tx[0] = (reg<<2) | 1; /* command: 6bit register address, a zero bit plus 1 bit with one for reading */
  res = McuSPI_SendReceiveBlock(tx, rx, sizeof(tx)); /* send command and receive data */
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  *data = rx[1]<<8 | rx[2]; /* return 16bit value we have read */
  return ERR_OK;
}

static uint8_t SPI_CmdWriteBytes2(uint8_t reg, uint16_t data) {
  uint8_t tx[3], rx[3], res;

  tx[0] = (reg<<2); /* command: 6bit register address, a zero byte plus 1 bit with zero for writing */
  tx[1] = data<<8;  /* data high byte */
  tx[2] = data;     /* data low byte */
  res = McuSPI_SendReceiveBlock(tx, rx, sizeof(tx)); /* send command and receive data */
  if (res!=ERR_OK) {
    return res; /* failed */
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadDeviceID(uint16_t *id) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_DEVICE_ID, id);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

static uint8_t McuINA229_ReadConfig(uint16_t *config) {
  uint8_t res;

  SPI_Select();
  res = SPI_CmdReadBytes2(McuINA229_REG_CONFIG, config);
  SPI_Unselect();
  if (res!=ERR_OK) {
    return res;
  }
  return ERR_OK;
}

#if McuINA229_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  uint16_t val16;
  unsigned char buf[64];

  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_GetPinStatusString(device.cs, buf, sizeof(buf));
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
    McuShell_SendStatusStr((unsigned char*)"  CS", buf, io->stdOut);
  #endif

  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_GetPinStatusString(device.alert, buf, sizeof(buf));
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
    McuShell_SendStatusStr((unsigned char*)"  ALERT", buf, io->stdOut);
  #endif

  if (McuINA229_ReadConfig(&val16)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), val16);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  config", buf, io->stdOut);
  
  if (McuINA229_ReadDeviceID(&val16)==ERR_OK) {
    McuUtility_strcpy(buf, sizeof(buf), "0x");
    McuUtility_strcatNum16Hex(buf, sizeof(buf), val16);
    McuUtility_strcat(buf, sizeof(buf), "\r\n");
  } else {
    McuUtility_strcpy(buf, sizeof(buf), "***failed****\r\n");
  }
  McuShell_SendStatusStr((unsigned char*)"  device ID", buf, io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuINA229", (unsigned char*)"Group of INA229 sensor commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
  return ERR_OK;
}

uint8_t McuINA229_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io) {
  uint8_t res = ERR_OK;

  if (McuUtility_strcmp((char*)cmd, McuShell_CMD_HELP) == 0
    || McuUtility_strcmp((char*)cmd, "McuINA229 help") == 0)
  {
    *handled = true;
    return PrintHelp(io);
  } else if (   (McuUtility_strcmp((char*)cmd, McuShell_CMD_STATUS)==0)
             || (McuUtility_strcmp((char*)cmd, "McuINA229 status")==0)
            )
  {
    *handled = true;
    res = PrintStatus(io);
  }
  return res;
}
#endif /* McuINA229_CONFIG_PARSE_COMMAND_ENABLED */

void McuINA229_Deinit(void) {
  /* nothing needed */
}

void McuINA229_Init(void) {
  #if McuINA229_CONFIG_CS_PIN_NUMBER!=-1
    McuGPIO_Config_t config_cs;

    McuGPIO_GetDefaultConfig(&config_cs);
    config_cs.isInput = false;
    config_cs.isHighOnInit = true; /* CS is active LOW */
    config_cs.hw.pin = McuINA229_CONFIG_CS_PIN_NUMBER;
    device.cs = McuGPIO_InitGPIO(&config_cs);
    if (device.cs==NULL) {
      McuLog_fatal("failed initializing CS pin");
      for(;;){}
    }
  #endif
  #if McuINA229_CONFIG_ALERT_PIN_NUMBER!=-1
    McuGPIO_Config_t config_alert;

    McuGPIO_GetDefaultConfig(&config_alert);
    config_alert.isInput = true;
    config_alert.hw.pin = McuINA229_CONFIG_ALERT_PIN_NUMBER;
    config_alert.hw.pull = McuGPIO_PULL_DISABLE;
    device.alert = McuGPIO_InitGPIO(&config_alert);
    if (device.alert==NULL) {
      McuLog_fatal("failed initializing ALERT pin");
      for(;;){}
    }
  #endif
}
