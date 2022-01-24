/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief The board name */
#define BOARD_NAME "FRDM-KE02Z40M"

/*! @brief The UART to use for debug messages. */
#define BOARD_USE_UART
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) UART1
#define BOARD_DEBUG_UART_INSTANCE 1U
#define BOARD_DEBUG_UART_CLKSRC   kCLOCK_BusClk
#define BOARD_UART_IRQ            UART1_IRQn
#define BOARD_UART_IRQ_HANDLER    UART1_IRQHandler

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*! @brief The i2c instance used for i2c connection by default */
#define BOARD_I2C_BASEADDR I2C0

#define BOARD_ACCEL_I2C_BASEADDR I2C0

/*! @brief The rtc instance used for board. */
#define BOARD_RTC_FUNC_BASEADDR RTC

/*! @brief Indexes of the TSI channels for on-board electrodes */
#ifndef BOARD_TSI_ELECTRODE_1
#define BOARD_TSI_ELECTRODE_1 22U
#endif
#ifndef BOARD_TSI_ELECTRODE_2
#define BOARD_TSI_ELECTRODE_2 23U
#endif

/*! @brief Indexes of the TSI mutual channels for FRDM-TOUCH board */
#define BOARD_TSI_MUTUAL_TX_ELECTRODE_1 2U
#define BOARD_TSI_MUTUAL_RX_ELECTRODE_1 6U

/* Board RGB LED color mapping */
#define LOGIC_LED_ON  0U
#define LOGIC_LED_OFF 1U

#define BOARD_LED_RED_GPIO_PORT kGPIO_PORTH
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 1U
#endif

#define BOARD_LED_GREEN_GPIO_PORT kGPIO_PORTH
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 2U
#endif

#define BOARD_LED_BLUE_GPIO_PORT kGPIO_PORTE
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 7U
#endif

#define LED_RED1_INIT(output)                                                                                         \
    GPIO_PinWrite(BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, output);                                           \
    GPIOB->PDDR |= (1U << (BOARD_LED_RED_GPIO_PIN + ((BOARD_LED_RED_GPIO_PORT % 4) * 8))) /*!< Enable target LED_RED1 \
                                                                                           */
#define LED_RED1_ON() \
    GPIO_PortClear(BOARD_LED_RED_GPIO_PORT, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn on target LED_RED1 */
#define LED_RED1_OFF() \
    GPIO_PortSet(BOARD_LED_RED_GPIO_PORT, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED_RED1 */
#define LED_RED1_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_RED_GPIO_PORT, 1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED_RED1 */

#define LED_GREEN1_INIT(output)                                                 \
    GPIO_PinWrite(BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_GPIO_PIN, output); \
    GPIOB->PDDR |=                                                              \
        (1U << (BOARD_LED_GREEN_GPIO_PIN + ((BOARD_LED_GREEN_GPIO_PORT % 4) * 8))) /*!< Enable target LED_GREEN1 */
#define LED_GREEN1_ON() \
    GPIO_PortClear(BOARD_LED_GREEN_GPIO_PORT, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED_GREEN1 */
#define LED_GREEN1_OFF() \
    GPIO_PortSet(BOARD_LED_GREEN_GPIO_PORT, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED_GREEN1 */
#define LED_GREEN1_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO_PORT, 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN1 */

#define LED_BLUE_INIT(output)                                                 \
    GPIO_PinWrite(BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN, output); \
    GPIOB->PDDR |=                                                            \
        (1U << (BOARD_LED_BLUE_GPIO_PIN + ((BOARD_LED_BLUE_GPIO_PORT % 4) * 8))) /*!< Enable target LED_BLUE */
#define LED_BLUE_ON() \
    GPIO_PortClear(BOARD_LED_BLUE_GPIO_PORT, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED_BLUE */
#define LED_BLUE_OFF() \
    GPIO_PortSet(BOARD_LED_BLUE_GPIO_PORT, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED_BLUE */
#define LED_BLUE_TOGGLE() \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO_PORT, 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
