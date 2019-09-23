/*
 * Copyright (c) 2013 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#if !defined(__BL_PERIPHERAL_INTERFACE_H__)
#define __BL_PERIPHERAL_INTERFACE_H__

#include "bootloader/bl_context.h"

//! @addtogroup peripherals
//! @{

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

//! @brief Clock options.
typedef enum
{
    kPeripheralClearClock = 0,
    kPeripheralSetClock
} PeripheralClockSetting;

//! @brief IRQ options.
typedef enum
{
    kPeripheralDisableIRQ = 0,
    kPeripheralEnableIRQ
} PeripheralSystemIRQSetting;

////////////////////////////////////////////////////////////////////////////////
// Externs
////////////////////////////////////////////////////////////////////////////////

//! @name I2C Peripheral Interfaces
//@{
//! @brief Control interface for the I2C peripheral driver.
extern const peripheral_control_interface_t g_i2cControlInterface;

//! @brief Byte I/O interface for the I2C peripheral driver.
extern const peripheral_byte_inteface_t g_i2cByteInterface;
//@}

//! @name LPI2C Peripheral Interfaces
//@{
//! @brief Control interface for the LPI2C peripheral driver.
extern const peripheral_control_interface_t g_lpi2cControlInterface;

//! @brief Byte I/O interface for the LPI2C peripheral driver.
extern const peripheral_byte_inteface_t g_lpi2cByteInterface;
//@}

//! @name FLEXCOMM I2C Peripheral Interfaces
//@{
//! @brief Control interface for the FLEXCOMM I2C peripheral driver.
extern const peripheral_control_interface_t g_flexcommI2cControlInterface;

//! @brief Byte I/O interface for the FLEXCOMM I2C peripheral driver.
extern const peripheral_byte_inteface_t g_flexcommI2cByteInterface;
//@}

//! @name SPI Peripheral Interfaces
//@{
//! @brief Control interface for the SPI peripheral driver.
extern const peripheral_control_interface_t g_spiControlInterface;

//! @brief Byte I/O interface for the SPI peripheral driver.
extern const peripheral_byte_inteface_t g_spiByteInterface;
//@}

//! @name FLEXCAN Peripheral Interfaces
//@{
//! @brief Control interface for the FLEXCAN peripheral driver.
extern const peripheral_control_interface_t g_flexcanControlInterface;

//! @brief Byte I/O interface for the FLEXCAN peripheral driver.
extern const peripheral_byte_inteface_t g_flexcanByteInterface;
//@}

//! @name LPSPI Peripheral Interfaces
//@{
//! @brief Control interface for the LPSPI peripheral driver.
extern const peripheral_control_interface_t g_lpspiControlInterface;

//! @brief Byte I/O interface for the LPSPI peripheral driver.
extern const peripheral_byte_inteface_t g_lpspiByteInterface;
//@}

//! @name DSPI Peripheral Interfaces
//@{
//! @brief Control interface for the DSPI peripheral driver.
extern const peripheral_control_interface_t g_dspiControlInterface;

//! @brief Byte I/O interface for the DSPI peripheral driver.
extern const peripheral_byte_inteface_t g_dspiByteInterface;
//@}

//! @name FLEXCOMM SPI Peripheral Interfaces
//@{
//! @brief Control interface for the FLEXCOMM SPI peripheral driver.
extern const peripheral_control_interface_t g_flexcommSpiControlInterface;

//! @brief Byte I/O interface for the FLEXCOMM SPI peripheral driver.
extern const peripheral_byte_inteface_t g_flexcommSpiByteInterface;
//@}

//! @name SCIUART Peripheral Interfaces
//@{
//! @brief Control interface for the SCIUART peripheral driver.
extern const peripheral_control_interface_t g_scuartControlInterface;

//! @brief Byte I/O interface for the SCIUART peripheral driver.
extern const peripheral_byte_inteface_t g_scuartByteInterface;
//@}

//! @name LPUART Peripheral Interfaces
//@{
//! @brief Control interface for the LPUART peripheral driver.
extern const peripheral_control_interface_t g_lpuartControlInterface;

//! @brief Byte I/O interface for the LPUART peripheral driver.
extern const peripheral_byte_inteface_t g_lpuartByteInterface;
//@}

//! @name UART Peripheral Interfaces
//@{
//! @brief Control interface for the UART peripheral driver.
extern const peripheral_control_interface_t g_uartControlInterface;

//! @brief Byte I/O interface for the UART peripheral driver.
extern const peripheral_byte_inteface_t g_uartByteInterface;
//@}

//! @name UART0 Peripheral Interfaces
//@{
//! @brief Control interface for the UART0 peripheral driver.
extern const peripheral_control_interface_t g_uart0ControlInterface;

//! @brief Byte I/O interface for the UART0 peripheral driver.
extern const peripheral_byte_inteface_t g_uart0ByteInterface;
//@}

//! @name FLEXCOMM USART Peripheral Interfaces
//@{
//! @brief Control interface for the FLEXCOMM USART peripheral driver.
extern const peripheral_control_interface_t g_flexcommUsartControlInterface;

//! @brief Byte I/O interface for the FLEXCOMM USART peripheral driver.
extern const peripheral_byte_inteface_t g_flexcommUsartByteInterface;
//@}

//! @name USB HID Peripheral Interfaces
//@{
//! @brief Control interface for the USB HID peripheral driver.
extern const peripheral_control_interface_t g_usbHidControlInterface;

//! @brief Packet interface for the USB HID peripheral driver.
extern const peripheral_packet_interface_t g_usbHidPacketInterface;
//@}

//! @name USB MSD Peripheral Interfaces
//@{
//! @brief Control interface for the USB MSD peripheral driver.
extern const peripheral_control_interface_t g_usbMsdControlInterface;
//@}

//! @}

#endif // __BL_PERIPHERAL_INTERFACE_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
