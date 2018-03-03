/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
