/*
 * Copyright (c) 2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "bootloader_common.h"
#include "bootloader/bl_peripheral_interface.h"

//! @addtogroup bl_hw
//! @{

///////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/*!
 * @brief Configure IRQ gate for I2C peripherals
 *
 * This function enables or disables IRQ gate for specified I2C peripheral
 *
 * @param instance I2C instance
 * @param set Option for disabling or enabling IRQ gates.
 */
void I2C_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set);

/*!
 * @brief Configure IRQ gate for DSPI peripherals
 *
 * This function enables or disables IRQ gate for specified DSPI peripheral
 *
 * @param instance DSPI instance
 * @param set Option for disabling or enabling IRQ gates.
 */
void DSPI_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set);

/*!
 * @brief Configure IRQ gate for LPUART peripherals
 *
 * This function enables or disables IRQ gate for specified LPUART peripheral
 *
 * @param instance LPUART instance
 * @param set Option for disabling or enabling IRQ gates.
 */
void LPUART_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set);

/*!
 * @brief Configure IRQ gate for UART peripherals
 *
 * This function enables or disables IRQ gate for specified UART peripheral
 *
 * @param instance UART instance
 * @param set Option for disabling or enabling IRQ gates.
 */
void UART_SetSystemIRQ(uint32_t instance, PeripheralSystemIRQSetting set);

/*!
 * @brief Configure IRQ gate for LPI2C peripherals
 *
 * This function enables or disables IRQ gate for specified LPI2C peripheral
 *
 * @param instance LPI2C instance
 * @param set Option for disabling or enabling IRQ gates.
 */
void lpi2c_set_system_IRQ_gate(uint32_t instance, PeripheralSystemIRQSetting set);

/*!
 * @brief Configure IRQ gate for LPSPI peripherals
 *
 * This function enables or disables IRQ gate for specified LPSPI peripheral
 *
 * @param instance LPSPI instance
 * @param set Option for disabling or enabling IRQ gates.
 */
void lpspi_set_system_IRQ_gate(uint32_t instance, PeripheralSystemIRQSetting set);

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
