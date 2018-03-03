/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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

#include "fsl_device_registers.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! peripheral enable configurations
#define BL_ENABLE_PINMUX_UART1 (BL_CONFIG_SCUART)
#define BL_ENABLE_PINMUX_SPI1 (BL_CONFIG_DSPI)
#define BL_ENABLE_PINMUX_I2C1 (BL_CONFIG_I2C)

//! UART pinmux configurations
#define UART1_RX_PORT_BASE PORTE
#define UART1_RX_GPIO_BASE PTE
#define UART1_RX_GPIO_PIN_NUM 1  // PTE1
#define UART1_RX_FUNC_ALT_MODE 3 // ALT mode for UART1 RX functionality
#define UART1_RX_GPIO_ALT_MODE 1 // ALT mdoe for GPIO functionality
#define UART1_RX_GPIO_IRQn PORTE_IRQn
#define UART1_RX_GPIO_IRQHandler PORTE_IRQHandler
#define UART1_TX_PORT_BASE PORTE
#define UART1_TX_GPIO_PIN_NUM 0  // PTE0
#define UART1_TX_FUNC_ALT_MODE 3 // ALT mode for UART1 TX functionality

//! I2C pinmux configurations
#define I2C1_SCL_PORT_BASE PORTC
#define I2C1_SCL_GPIO_PIN_NUM 10 // PTC10
#define I2C1_SCL_FUNC_ALT_MODE 2 // ALT mode for I2C1 SCL functionality
#define I2C1_SDA_PORT_BASE PORTC
#define I2C1_SDA_GPIO_PIN_NUM 11 // PTC11
#define I2C1_SDA_FUNC_ALT_MODE 2 // ALT mode for I2C1 SDA functionality

//! SPI pinmux configurations
#define SPI1_PCS_PORT_BASE PORTD
#define SPI1_PCS_GPIO_PIN_NUM 4  // PTD4
#define SPI1_PCS_FUNC_ALT_MODE 7 // ALT mode for SPI1 PCS functionality
#define SPI1_SCK_PORT_BASE PORTD
#define SPI1_SCK_GPIO_PIN_NUM 5  // PPTD5
#define SPI1_SCK_FUNC_ALT_MODE 7 // ALT mode for SPI1 SCK functionality
#define SPI1_SOUT_PORT_BASE PORTD
#define SPI1_SOUT_GPIO_PIN_NUM 6  // PPTD6
#define SPI1_SOUT_FUNC_ALT_MODE 7 // ALT mode for SPI1 SOUT functionality
#define SPI1_SIN_PORT_BASE PORTD
#define SPI1_SIN_GPIO_PIN_NUM 7  // PTD7
#define SPI1_SIN_FUNC_ALT_MODE 7 // ALT mode for SPI1 SIN functionality

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
