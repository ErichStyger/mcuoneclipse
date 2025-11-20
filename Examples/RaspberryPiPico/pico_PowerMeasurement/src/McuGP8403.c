/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
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
  McuADS1115_ADDR_dummy_REGISTER      = 0x00,  /**< todo */
} McuGP8403_Reg_e;

uint8_t McuGP8403_ReadRegister(McuGP8403_Reg_e reg, uint8_t *value) {
  uint8_t res;
  uint8_t data;

  res = McuGenericI2C_ReadByteAddress8(McuGP8403_CONFIG_I2C_ADDRESS, reg, &data);
  if (res!=ERR_OK) {
    return res;
  }
  *value = data;
  return ERR_OK;
}

uint8_t McuGP8403_WriteRegister(McuGP8403_Reg_e reg, uint8_t value) {
  return McuGenericI2C_WriteWordAddress8(McuGP8403_CONFIG_I2C_ADDRESS, reg, value);
}

#if McuGP8403_CONFIG_PARSE_COMMAND_ENABLED
static uint8_t PrintStatus(const McuShell_StdIOType *io) {
  McuShell_SendStatusStr((unsigned char*)"McuGP8403", (unsigned char*)"GP8403 sensor status\r\n", io->stdOut);
  return ERR_OK;
}

static uint8_t PrintHelp(const McuShell_StdIOType *io) {
  McuShell_SendHelpStr((unsigned char*)"McuGP8403", (unsigned char*)"Group of GP8403 commands\r\n", io->stdOut);
  McuShell_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Print help or status information\r\n", io->stdOut);
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
  }
  return ERR_OK;
}
#endif /* McuGP8403_CONFIG_PARSE_COMMAND_ENABLED */

void McuGP8403_Init(void) {}

void McuGP8403_Deinit(void) {}
