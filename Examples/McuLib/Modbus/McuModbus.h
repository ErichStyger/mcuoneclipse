/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUMODBUS_H_
#define MCUMODBUS_H_

#include "McuModbus_config.h"
#include <stdint.h>
#include <stdbool.h>
#include "McuShell.h"

typedef enum McuModbus_Func_Code_e {
  McuModbus_Func_ReadCoils              = 0x01,
  McuModbus_Func_ReadDiscreteInputs     = 0x02,
  McuModbus_Func_ReadHoldingRegisters   = 0x03,
  McuModbus_Func_ReadInputRegisters     = 0x04,
  McuModbus_Func_WriteSingleCoil        = 0x05,
  McuModbus_Func_WriteSingleRegister    = 0x06,
  McuModbus_Func_WriteMultipleCoils     = 0x0f,
  McuModbus_Func_WriteMultipleRegisters = 0x10,
} McuModbus_Func_Code_e;

uint8_t McuModbus_ParseCommand(const unsigned char *cmd, bool *handled, const McuShell_StdIOType *io);

void McuModbus_Send(uint8_t slaveID, McuModbus_Func_Code_e function, uint16_t addr, uint16_t nofCoils, uint8_t *result, const McuShell_StdIOType *io);

uint8_t McuModbus_ReadInputRegisters(uint8_t deviceID, uint16_t addr, uint16_t nofRegs, uint16_t *result);
uint8_t McuModbus_WriteInputRegister(uint8_t deviceID, uint16_t addr, uint16_t value);

uint8_t McuModbus_ReadHoldingRegisters(uint8_t deviceID, uint16_t addr, uint16_t nofRegs, uint16_t *result);
uint8_t McuModbus_WriteHoldingRegister(uint8_t deviceID, uint16_t addr, uint16_t value);

void McuModbus_Deinit(void);
void McuModbus_Init(void);

#endif /* MCUMODBUS_H_ */
