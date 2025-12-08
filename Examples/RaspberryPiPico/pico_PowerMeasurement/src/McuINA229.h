/**
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * \brief Driver for the TI INA229 SPI current/voltage sensor.
 */

#ifndef McuINA229_H_
#define McuINA229_H_

#include "McuINA229config.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TI INA229 device registers: */
typedef enum INA229_REG_e {
  McuINA229_ADDR_CONFIGURATION_REGISTER           = 0x00,
  McuINA229_ADDR_CURRENT_REGISTER                 = 0x01,
  McuINA229_ADDR_BUS_VOLTAGE_REGISTER             = 0x02,
  McuINA229_ADDR_POWER_REGISTER                   = 0x03,
  McuINA229_ADDR_MASK_ENABLE_REGISTER             = 0x06,
  McuINA229_ADDR_ALERT_LIMIT_REGISTER             = 0x07,
  McuINA229_ADDR_MANUFACTURER_ID_REGISTER         = 0xFE,
  McuINA229_ADDR_DIE_ID_REGISTER                  = 0xFF,
} INA229_REG_e;

/*!
 * \brief Read a device register
 * \param reg Device register
 * \param value Pointer where to store the register value
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t McuINA229_ReadRegister(INA229_REG_e reg, uint16_t *value);

/*!
 * \brief Write a device register
 * \param reg Device register
 * \param value Register value to write
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t McuINA229_WriteRegister(INA229_REG_e reg, uint16_t value);

#if McuINA229_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
  uint8_t McuINA229_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*! \brief Module de-initialization */
void McuINA229_Deinit(void);

/*! \brief Module initialization */
void McuINA229_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* McuINA229_H_ */