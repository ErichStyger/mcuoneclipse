/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
