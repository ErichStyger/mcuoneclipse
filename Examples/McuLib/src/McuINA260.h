/**
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * \brief Driver for the TI INA260 current/voltage sensor.
 */

#ifndef McuINA260_H_
#define McuINA260_H_

#include "McuINA260config.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TI INA260 device registers: */
typedef enum INA260_REG_e {
  McuINA260_ADDR_CONFIGURATION_REGISTER           = 0x00,
  McuINA260_ADDR_CURRENT_REGISTER                 = 0x01,
  McuINA260_ADDR_BUS_VOLTAGE_REGISTER             = 0x02,
  McuINA260_ADDR_POWER_REGISTER                   = 0x03,
  McuINA260_ADDR_MASK_ENABLE_REGISTER             = 0x06,
  McuINA260_ADDR_ALERT_LIMIT_REGISTER             = 0x07,
  McuINA260_ADDR_MANUFACTURER_ID_REGISTER         = 0xFE,
  McuINA260_ADDR_DIE_ID_REGISTER                  = 0xFF,
} INA260_REG_e;

/*!
 * \brief Read a device register
 * \param reg Device register
 * \param value Pointer where to store the register value
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t McuINA260_ReadRegister(INA260_REG_e reg, uint16_t *value);

/*!
 * \brief Write a device register
 * \param reg Device register
 * \param value Register value to write
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t McuINA260_WriteRegister(INA260_REG_e reg, uint16_t value);

/*!
 * \brief Read the bus voltage measurement value from the device.
 * \return Power value, as mV (micro-Volt).
 */
uint32_t McuINA260_ReadVoltage(void);

/*!
 * \brief Read the power measurement value from the device.
 * \return Power value, as mW (milli-Watt).
 */
uint32_t McuINA260_ReadPower(void);

/*!
 * \brief Read the current measurement value from the device.
 * \return Current value, as uA (micro-Amps).
 */
int32_t McuINA260_ReadCurrent(void);


#if McuINA260_CONFIG_PARSE_COMMAND_ENABLED
  #include "McuShell.h"

/*!
 * \brief Shell command line handler
 * \param cmd Pointer to the command string
 * \param handled Return value to indicate if command has been recognized
 * \param io I/O handler for input/output
 * \return Error code, ERR_OK for no error
 */
  uint8_t McuINA260_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);
#endif

/*! \brief Module de-initialization */
void McuINA260_Deinit(void);

/*! \brief Module initialization */
void McuINA260_Init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* McuINA260_H_ */