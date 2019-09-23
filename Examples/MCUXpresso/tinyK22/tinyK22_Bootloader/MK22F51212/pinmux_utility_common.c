/*
 * Copyright (c) 2014-2015 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
#include "bootloader_common.h"
#include "bootloader/bl_context.h"
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_IOMUXC_COUNT
#include "fsl_iomuxc.h"
#endif // #if FSL_FEATURE_SOC_IOMUXC_COUNT
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "peripherals_pinmux.h"

#if (BL_CONFIG_LPUART || BL_CONFIG_SCUART || BL_CONFIG_UART)

#if BL_ENABLE_PINMUX_UART4
#define BL_ENABLED_MAX_UART_INSTANCE (4)
#elif BL_ENABLE_PINMUX_UART3
#define BL_ENABLED_MAX_UART_INSTANCE (3)
#elif BL_ENABLE_PINMUX_UART2
#define BL_ENABLED_MAX_UART_INSTANCE (2)
#elif BL_ENABLE_PINMUX_UART1
#define BL_ENABLED_MAX_UART_INSTANCE (1)
#elif BL_ENABLE_PINMUX_UART0
#define BL_ENABLED_MAX_UART_INSTANCE (0)
#endif

//! UART autobaud port irq configurations
#define PORT_IRQC_INTERRUPT_ENABLED_PRIORITY 1
#define PORT_IRQC_INTERRUPT_RESTORED_PRIORITY 0

#define PORT_IRQC_INTERRUPT_FALLING_EDGE 0xA
#define PORT_IRQC_INTERRUPT_DISABLE 0

//! this is to store the function pointer for calling back to the function that wants
//! the UART RX instance pin that triggered the interrupt. This only supports 1 pin
//! for UART0 because UART1 is on PORTC which does not support interrupts :(

static pin_irq_callback_t s_pin_irq_func[BL_ENABLED_MAX_UART_INSTANCE + 1] = { 0 };

#endif // BL_CONFIG_LPUART

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
#if FSL_FEATURE_SOC_IOMUXC_COUNT
static inline void IOMUXC_RestoreDefault(uint32_t muxRegister,
                                         uint32_t muxMode,
                                         uint32_t inputRegister,
                                         uint32_t inputDaisy,
                                         uint32_t configRegister,
                                         uint32_t configDefaultValue)
{
    *((volatile uint32_t *)muxRegister) = 0 /*Mux default value*/;
    if (inputRegister)
    {
        *((volatile uint32_t *)inputRegister) = 0 /*Daisy defualt value*/;
    }
    if (configRegister)
    {
        *((volatile uint32_t *)configRegister) = configDefaultValue;
    }
}

static inline void IOMUXC_SetUartAutoBaudPinMode(uint32_t muxRegister,
                                                 uint32_t muxMode,
                                                 uint32_t inputRegister,
                                                 uint32_t inputDaisy,
                                                 uint32_t configRegister,
                                                 GPIO_Type *gpioBase,
                                                 uint32_t pin)
{
    // Configure the UART RX pin to GPIO mode
    IOMUXC_SetPinMux(muxRegister, 1 /*kIOMUXC_MuxAsGpio*/, inputRegister, inputDaisy, configRegister,
                     0 /*kIOMUXC_InputPathDeteminedByMux*/);
#if BL_FEATURE_UART_RX_PULLUP
    // Pull-up resistor enabled.
    *((volatile uint32_t *)configRegister) |= IOMUXC0_SW_PAD_CTL_PAD_PKE(1);
#else
    // Pull-up resistor disabled.
    *((volatile uint32_t *)configRegister) &= ~IOMUXC0_SW_PAD_CTL_PAD_PKE(1);
#endif // BL_FEATURE_UART_RX_PULLUP
    // Configure UART RX pin to digital input mode.
    gpioBase->PDDR &= (uint32_t) ~(1 << pin);
}

static inline void IOMUXC_SetUartPinMode(uint32_t muxRegister,
                                         uint32_t muxMode,
                                         uint32_t inputRegister,
                                         uint32_t inputDaisy,
                                         uint32_t configRegister)
{
    IOMUXC_SetPinMux(muxRegister, muxMode, inputRegister, inputDaisy, configRegister,
                     0 /*kIOMUXC_InputPathDeteminedByMux*/);
};
#endif // #if FSL_FEATURE_SOC_IOMUXC_COUNT

uint32_t PORT_GetPinIsf(PORT_Type *base, uint32_t pin)
{
    return (base->PCR[pin] & PORT_PCR_ISF_MASK) >> PORT_PCR_ISF_SHIFT;
}

#if FSL_FEATURE_PORT_PCR_MUX_WIDTH
static inline void PORT_RestoreDefault(PORT_Type *base, uint32_t pin)
{
    base->PCR[pin] = 0;
}
#endif // #if FSL_FEATURE_PORT_PCR_MUX_WIDTH

#if (BL_CONFIG_LPUART || BL_CONFIG_SCUART || BL_CONFIG_UART) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
//! @brief Configure the GPIO mode for auto baud detection.
static inline void PORT_SetUartAutoBaudPinMode(PORT_Type *portBase, GPIO_Type *gpioBase, uint32_t pin)
{
#if BL_FEATURE_UART_RX_PULLUP
    // Configure the UART RX pin to GPIO mode, with pull-up resistor enabled.
    portBase->PCR[pin] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
#else
    // Configure the UART RX pin to GPIO mode
    portBase->PCR[pin] = PORT_PCR_MUX(1);
#endif // BL_FEATURE_UART_RX_PULLUP

    // Configure UART RX pin to digital input mode.
    gpioBase->PDDR &= (uint32_t) ~(1 << pin);
}

static inline void PORT_SetUartPinMode(PORT_Type *base, uint32_t pin, uint32_t mux)
{
    base->PCR[pin] = PORT_PCR_MUX(mux);
}
#endif

#if (BL_CONFIG_I2C || BL_CONFIG_LPI2C) && (FSL_FEATURE_PORT_PCR_MUX_WIDTH)
static inline void PORT_SetI2cPinMode(PORT_Type *base, uint32_t pin, uint32_t mux)
{
#if defined(FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && (FSL_FEATURE_PORT_HAS_OPEN_DRAIN > 0)
    base->PCR[pin] = PORT_PCR_MUX(mux) | PORT_PCR_ODE(1);
#else
    base->PCR[pin] = PORT_PCR_MUX(mux);
#endif // //#if defined(FSL_FEATURE_PORT_HAS_OPEN_DRAIN) && (FSL_FEATURE_PORT_HAS_OPEN_DRAIN > 0)
}
#endif

#if (BL_CONFIG_DSPI || BL_CONFIG_SPI || BL_CONFIG_LPSPI) && FSL_FEATURE_PORT_PCR_MUX_WIDTH
static inline void PORT_SetSpiPinMode(PORT_Type *base, uint32_t pin, uint32_t mux)
{
    base->PCR[pin] = PORT_PCR_MUX(mux);
}
#endif

#if BL_CONFIG_CAN && FSL_FEATURE_PORT_PCR_MUX_WIDTH
static inline void PORT_SetCanPinMode(PORT_Type *base, uint32_t pin, uint32_t mux)
{
    base->PCR[pin] = PORT_PCR_MUX(mux);
}
#endif

/*!
 * @brief Configure pinmux for uart module.
 *
 * This function only support switching default or gpio or fixed-ALTx mode on fixed pins
 * (Although there are many ALTx-pinmux configuration choices on various pins for the same
 * peripheral module)
 */
void uart_pinmux_config(uint32_t instance, pinmux_type_t pinmux)
{
    switch (instance)
    {
#if BL_ENABLE_PINMUX_UART0
        case 0:
            switch (pinmux)
            {
                case kPinmuxType_Default:
#if FSL_FEATURE_PORT_PCR_MUX_WIDTH
                    PORT_RestoreDefault(UART0_TX_PORT_BASE, UART0_TX_GPIO_PIN_NUM);
#elif FSL_FEATURE_SOC_IOMUXC_COUNT
                    IOMUXC_RestoreDefault(UART0_TX_IOMUXC_MUX_FUNC, UART0_TX_IOMUXC_PAD_DEFAULT);
#else
#error "Unknown mux setting."
#endif // #if FSL_FEATURE_PORT_PCR_MUX_WIDTH
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_RestoreForActivity:
#endif // BL_FEATURE_6PINS_PERIPHERAL
#if FSL_FEATURE_PORT_PCR_MUX_WIDTH
                    PORT_RestoreDefault(UART0_RX_PORT_BASE, UART0_RX_GPIO_PIN_NUM);
#elif FSL_FEATURE_SOC_IOMUXC_COUNT
                    IOMUXC_RestoreDefault(UART0_RX_IOMUXC_MUX_FUNC, UART0_RX_IOMUXC_PAD_DEFAULT);
#else
#error "Unknown mux setting."
#endif // #if FSL_FEATURE_PORT_PCR_MUX_WIDTH
                    break;
                case kPinmuxType_PollForActivity:
#if FSL_FEATURE_PORT_PCR_MUX_WIDTH
                    PORT_SetUartAutoBaudPinMode(UART0_RX_PORT_BASE, UART0_RX_GPIO_BASE, UART0_RX_GPIO_PIN_NUM);

#elif FSL_FEATURE_SOC_IOMUXC_COUNT
                    IOMUXC_SetUartAutoBaudPinMode(UART0_RX_IOMUXC_MUX_GPIO, UART0_RX_GPIO_BASE, UART0_RX_GPIO_PIN_NUM);
#else
#error "Unknown mux setting."
#endif // #if FSL_FEATURE_PORT_PCR_MUX_WIDTH
                    break;
                case kPinmuxType_Peripheral:
// Enable pins for UART0.
#if FSL_FEATURE_PORT_PCR_MUX_WIDTH
                    PORT_SetUartPinMode(UART0_RX_PORT_BASE, UART0_RX_GPIO_PIN_NUM,
                                        UART0_RX_FUNC_ALT_MODE); // Set UART0_RX pin to UART0_RX functionality
                    PORT_SetUartPinMode(UART0_TX_PORT_BASE, UART0_TX_GPIO_PIN_NUM,
                                        UART0_TX_FUNC_ALT_MODE); // Set UART0_TX pin to UART0_TX functionality
#elif FSL_FEATURE_SOC_IOMUXC_COUNT
                    IOMUXC_SetUartPinMode(UART0_RX_IOMUXC_MUX_FUNC);
                    IOMUXC_SetUartPinMode(UART0_TX_IOMUXC_MUX_FUNC);
#else
#error "Unknown mux setting."
#endif // #if FSL_FEATURE_PORT_PCR_MUX_WIDTH
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_UART0

#if BL_ENABLE_PINMUX_UART1
        case 1:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(UART1_RX_PORT_BASE, UART1_RX_GPIO_PIN_NUM);
                    PORT_RestoreDefault(UART1_TX_PORT_BASE, UART1_TX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_PollForActivity:
                    PORT_SetUartAutoBaudPinMode(UART1_RX_PORT_BASE, UART1_RX_GPIO_BASE, UART1_RX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_Peripheral:
                    // Enable pins for UART1.
                    PORT_SetUartPinMode(UART1_RX_PORT_BASE, UART1_RX_GPIO_PIN_NUM,
                                        UART1_RX_FUNC_ALT_MODE); // Set UART1_RX pin to UART1_RX functionality
                    PORT_SetUartPinMode(UART1_TX_PORT_BASE, UART1_TX_GPIO_PIN_NUM,
                                        UART1_TX_FUNC_ALT_MODE); // Set UART1_TX pin to UART1_TX functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_UART1

#if BL_ENABLE_PINMUX_UART2
        case 2:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(UART2_RX_PORT_BASE, UART2_RX_GPIO_PIN_NUM);
                    PORT_RestoreDefault(UART2_TX_PORT_BASE, UART2_TX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_PollForActivity:
                    PORT_SetUartAutoBaudPinMode(UART2_RX_PORT_BASE, UART2_RX_GPIO_BASE, UART2_RX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_Peripheral:
                    // Enable pins for UART2.
                    PORT_SetUartPinMode(UART2_RX_PORT_BASE, UART2_RX_GPIO_PIN_NUM,
                                        UART2_RX_FUNC_ALT_MODE); // Set UART2_RX pin to UART2_RX functionality
                    PORT_SetUartPinMode(UART2_TX_PORT_BASE, UART2_TX_GPIO_PIN_NUM,
                                        UART2_TX_FUNC_ALT_MODE); // Set UART2_TX pin to UART2_TX functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_UART2

#if BL_ENABLE_PINMUX_UART3
        case 3:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(UART3_RX_PORT_BASE, UART3_RX_GPIO_PIN_NUM);
                    PORT_RestoreDefault(UART3_TX_PORT_BASE, UART3_TX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_PollForActivity:
                    PORT_SetUartAutoBaudPinMode(UART3_RX_PORT_BASE, UART3_RX_GPIO_BASE, UART3_RX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_Peripheral:
                    // Enable pins for UART3.
                    PORT_SetUartPinMode(UART3_RX_PORT_BASE, UART3_RX_GPIO_PIN_NUM,
                                        UART3_RX_FUNC_ALT_MODE); // Set UART3_RX pin to UART3_RX functionality
                    PORT_SetUartPinMode(UART3_TX_PORT_BASE, UART3_TX_GPIO_PIN_NUM,
                                        UART3_TX_FUNC_ALT_MODE); // Set UART3_TX pin to UART3_TX functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_UART3

#if BL_ENABLE_PINMUX_UART4
        case 4:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(UART4_RX_PORT_BASE, UART4_RX_GPIO_PIN_NUM);
                    PORT_RestoreDefault(UART4_TX_PORT_BASE, UART4_TX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_PollForActivity:
                    PORT_SetUartAutoBaudPinMode(UART4_RX_PORT_BASE, UART4_RX_GPIO_BASE, UART4_RX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_Peripheral:
                    // Enable pins for UART4.
                    PORT_SetUartPinMode(UART4_RX_PORT_BASE, UART4_RX_GPIO_PIN_NUM,
                                        UART4_RX_FUNC_ALT_MODE); // Set UART4_RX pin to UART4_RX functionality
                    PORT_SetUartPinMode(UART4_TX_PORT_BASE, UART4_TX_GPIO_PIN_NUM,
                                        UART4_TX_FUNC_ALT_MODE); // Set UART4_TX pin to UART4_TX functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_UART4

        default:
            break;
    }
}

/*!
 * @brief Configure pinmux for i2c module.
 *
 * This function only support switching default or gpio or fixed-ALTx mode on fixed pins
 * (Although there are many ALTx-pinmux configuration choices on various pins for the same
 * peripheral module)
 */
void i2c_pinmux_config(uint32_t instance, pinmux_type_t pinmux)
{
    switch (instance)
    {
#if BL_ENABLE_PINMUX_I2C0
        case 0:
            switch (pinmux)
            {
                case kPinmuxType_Default:
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_RestoreForActivity:
#endif // BL_FEATURE_6PINS_PERIPHERAL
                    PORT_RestoreDefault(I2C0_SCL_PORT_BASE, I2C0_SCL_GPIO_PIN_NUM);
                    PORT_RestoreDefault(I2C0_SDA_PORT_BASE, I2C0_SDA_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_Peripheral:
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_PollForActivity:
#endif // BL_FEATURE_6PINS_PERIPHERAL
                    // Enable pins for I2C0.
                    PORT_SetI2cPinMode(I2C0_SDA_PORT_BASE, I2C0_SDA_GPIO_PIN_NUM,
                                       I2C0_SDA_FUNC_ALT_MODE); // Set I2C0_SDA pin to I2C0_SDA functionality
                    PORT_SetI2cPinMode(I2C0_SCL_PORT_BASE, I2C0_SCL_GPIO_PIN_NUM,
                                       I2C0_SCL_FUNC_ALT_MODE); // Set I2C0_SCL pin to I2C0_SCL functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_I2C0

#if BL_ENABLE_PINMUX_I2C1
        case 1:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(I2C1_SCL_PORT_BASE, I2C1_SCL_GPIO_PIN_NUM);
                    PORT_RestoreDefault(I2C1_SDA_PORT_BASE, I2C1_SDA_GPIO_PIN_NUM);
                    break;
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_PollForActivity:
#endif // BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_Peripheral:
                    // Enable pins for I2C1.
                    PORT_SetI2cPinMode(I2C1_SDA_PORT_BASE, I2C1_SDA_GPIO_PIN_NUM,
                                       I2C1_SDA_FUNC_ALT_MODE); // Set I2C1_SDA pin to I2C1_SDA functionality
                    PORT_SetI2cPinMode(I2C1_SCL_PORT_BASE, I2C1_SCL_GPIO_PIN_NUM,
                                       I2C1_SCL_FUNC_ALT_MODE); // Set I2C1_SCL pin to I2C1_SCL functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_I2C1

#if BL_ENABLE_PINMUX_I2C2
        case 2:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(I2C2_SCL_PORT_BASE, I2C2_SCL_GPIO_PIN_NUM);
                    PORT_RestoreDefault(I2C2_SDA_PORT_BASE, I2C2_SDA_GPIO_PIN_NUM);
                    break;
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_PollForActivity:
#endif // BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_Peripheral:
                    // Enable pins for I2C2.
                    PORT_SetI2cPinMode(I2C2_SDA_PORT_BASE, I2C2_SDA_GPIO_PIN_NUM,
                                       I2C2_SDA_FUNC_ALT_MODE); // Set I2C2_SDA pin to I2C2_SDA functionality
                    PORT_SetI2cPinMode(I2C2_SCL_PORT_BASE, I2C2_SCL_GPIO_PIN_NUM,
                                       I2C2_SCL_FUNC_ALT_MODE); // Set I2C2_SCL pin to I2C2_SCL functionality
                    break;
                default:
                    break;
            }
#endif // #if BL_ENABLE_PINMUX_I2C2

        default:
            break;
    }
}

/*!
 * @brief Configure pinmux for SPI module.
 *
 * This function only support switching default or gpio or fixed-ALTx mode on fixed pins
 * (Although there are many ALTx-pinmux configuration choices on various pins for the same
 * peripheral module)
 */
void spi_pinmux_config(uint32_t instance, pinmux_type_t pinmux)
{
    switch (instance)
    {
#if BL_ENABLE_PINMUX_SPI0
        case 0:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(SPI0_SOUT_PORT_BASE, SPI0_SOUT_GPIO_PIN_NUM);
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_RestoreForActivity:
#endif // BL_FEATURE_6PINS_PERIPHERAL
                    PORT_RestoreDefault(SPI0_PCS_PORT_BASE, SPI0_PCS_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI0_SCK_PORT_BASE, SPI0_SCK_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI0_SIN_PORT_BASE, SPI0_SIN_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_Peripheral:
                    // Enable pins for SPI0
                    PORT_SetSpiPinMode(SPI0_SOUT_PORT_BASE, SPI0_SOUT_GPIO_PIN_NUM,
                                       SPI0_SOUT_FUNC_ALT_MODE); // Set SPI0_SOUT pin to SPI0_SOUT functionality
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_PollForActivity:
#endif // BL_FEATURE_6PINS_PERIPHERAL
                    PORT_SetSpiPinMode(SPI0_PCS_PORT_BASE, SPI0_PCS_GPIO_PIN_NUM,
                                       SPI0_PCS_FUNC_ALT_MODE); // Set SPI0_PCS pin to SPI0_PCS functionality
                    PORT_SetSpiPinMode(SPI0_SCK_PORT_BASE, SPI0_SCK_GPIO_PIN_NUM,
                                       SPI0_SCK_FUNC_ALT_MODE); // Set SPI0_SCK pin to SPI0_SCK functionality
                    PORT_SetSpiPinMode(SPI0_SIN_PORT_BASE, SPI0_SIN_GPIO_PIN_NUM,
                                       SPI0_SIN_FUNC_ALT_MODE); // Set SPI0_SIN pin to SPI0_SIN functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_SPI0

#if BL_ENABLE_PINMUX_SPI1
        case 1:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(SPI1_PCS_PORT_BASE, SPI1_PCS_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI1_SCK_PORT_BASE, SPI1_SCK_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI1_SOUT_PORT_BASE, SPI1_SOUT_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI1_SIN_PORT_BASE, SPI1_SIN_GPIO_PIN_NUM);
                    break;
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_PollForActivity:
                    PORT_SetSpiPinMode(SPI1_PCS_PORT_BASE, SPI1_PCS_GPIO_PIN_NUM,
                                       SPI1_PCS_FUNC_ALT_MODE); // Set SPI1_PCS pin to SPI1_PCS functionality
                    PORT_SetSpiPinMode(SPI1_SCK_PORT_BASE, SPI1_SCK_GPIO_PIN_NUM,
                                       SPI1_SCK_FUNC_ALT_MODE); // Set SPI1_SCK pin to SPI1_SCK functionality
                    PORT_SetSpiPinMode(SPI1_SIN_PORT_BASE, SPI1_SIN_GPIO_PIN_NUM,
                                       SPI1_SIN_FUNC_ALT_MODE); // Set SPI1_SIN pin to SPI1_SIN functionality
                    break;
#endif // BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_Peripheral:
                    // Enable pins for SPI1
                    PORT_SetSpiPinMode(SPI1_PCS_PORT_BASE, SPI1_PCS_GPIO_PIN_NUM,
                                       SPI1_PCS_FUNC_ALT_MODE); // Set SPI1_PCS pin to SPI1_PCS functionality
                    PORT_SetSpiPinMode(SPI1_SCK_PORT_BASE, SPI1_SCK_GPIO_PIN_NUM,
                                       SPI1_SCK_FUNC_ALT_MODE); // Set SPI1_SCK pin to SPI1_SCK functionality
                    PORT_SetSpiPinMode(SPI1_SOUT_PORT_BASE, SPI1_SOUT_GPIO_PIN_NUM,
                                       SPI1_SOUT_FUNC_ALT_MODE); // Set SPI1_SOUT pin to SPI1_SOUT functionality
                    PORT_SetSpiPinMode(SPI1_SIN_PORT_BASE, SPI1_SIN_GPIO_PIN_NUM,
                                       SPI1_SIN_FUNC_ALT_MODE); // Set SPI1_SIN pin to SPI1_SIN functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_SPI1

#if BL_ENABLE_PINMUX_SPI2
        case 2:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(SPI2_PCS_PORT_BASE, SPI2_PCS_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI2_SCK_PORT_BASE, SPI2_SCK_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI2_SOUT_PORT_BASE, SPI2_SOUT_GPIO_PIN_NUM);
                    PORT_RestoreDefault(SPI2_SIN_PORT_BASE, SPI2_SIN_GPIO_PIN_NUM);
                    break;
#if defined(BL_FEATURE_6PINS_PERIPHERAL) && BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_PollForActivity:
                    PORT_SetSpiPinMode(SPI2_PCS_PORT_BASE, SPI2_PCS_GPIO_PIN_NUM,
                                       SPI2_PCS_FUNC_ALT_MODE); // Set SPI1_PCS pin to SPI1_PCS functionality
                    PORT_SetSpiPinMode(SPI2_SCK_PORT_BASE, SPI2_SCK_GPIO_PIN_NUM,
                                       SPI2_SCK_FUNC_ALT_MODE); // Set SPI1_SCK pin to SPI1_SCK functionality
                    PORT_SetSpiPinMode(SPI2_SIN_PORT_BASE, SPI2_SIN_GPIO_PIN_NUM,
                                       SPI2_SIN_FUNC_ALT_MODE); // Set SPI1_SIN pin to SPI1_SIN functionality
                    break;
#endif // BL_FEATURE_6PINS_PERIPHERAL
                case kPinmuxType_Peripheral:
                    // Enable pins for SPI1
                    PORT_SetSpiPinMode(SPI2_PCS_PORT_BASE, SPI2_PCS_GPIO_PIN_NUM,
                                       SPI2_PCS_FUNC_ALT_MODE); // Set SPI1_PCS pin to SPI1_PCS functionality
                    PORT_SetSpiPinMode(SPI2_SCK_PORT_BASE, SPI2_SCK_GPIO_PIN_NUM,
                                       SPI2_SCK_FUNC_ALT_MODE); // Set SPI1_SCK pin to SPI1_SCK functionality
                    PORT_SetSpiPinMode(SPI2_SOUT_PORT_BASE, SPI2_SOUT_GPIO_PIN_NUM,
                                       SPI2_SOUT_FUNC_ALT_MODE); // Set SPI1_SOUT pin to SPI1_SOUT functionality
                    PORT_SetSpiPinMode(SPI2_SIN_PORT_BASE, SPI2_SIN_GPIO_PIN_NUM,
                                       SPI2_SIN_FUNC_ALT_MODE); // Set SPI1_SIN pin to SPI1_SIN functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_SPI2

        default:
            break;
    }
}

/*!
 * @brief Configure pinmux for CAN module.
 *
 * This function only support switching default or gpio or fixed-ALTx mode on fixed pins
 * (Although there are many ALTx-pinmux configuration choices on various pins for the same
 * peripheral module)
 */
void can_pinmux_config(uint32_t instance, pinmux_type_t pinmux)
{
    switch (instance)
    {
#if BL_ENABLE_PINMUX_CAN0
        case 0:
            switch (pinmux)
            {
                case kPinmuxType_Default:
                    PORT_RestoreDefault(CAN0_RX_PORT_BASE, CAN0_RX_GPIO_PIN_NUM);
                    PORT_RestoreDefault(CAN0_TX_PORT_BASE, CAN0_TX_GPIO_PIN_NUM);
                    break;
                case kPinmuxType_Peripheral:
                    // Enable pins for CAN0
                    PORT_SetCanPinMode(CAN0_RX_PORT_BASE, CAN0_RX_GPIO_PIN_NUM,
                                       CAN0_RX_FUNC_ALT_MODE); // Set CAN0_RX pin to CAN0_RX functionality
                    PORT_SetCanPinMode(CAN0_TX_PORT_BASE, CAN0_TX_GPIO_PIN_NUM,
                                       CAN0_TX_FUNC_ALT_MODE); // Set CAN0_TX pin to CAN0_TX functionality
                    break;
                default:
                    break;
            }
            break;
#endif // #if BL_ENABLE_PINMUX_CAN0

        default:
            break;
    }
}

//! @brief this is going to be used for autobaud IRQ handling for UART0
#if BL_ENABLE_PINMUX_UART0
void UART0_RX_GPIO_IRQHandler(void)
{
    // Check if the pin for UART0 is what triggered the RX PORT interrupt
    if (PORT_GetPinIsf(UART0_RX_PORT_BASE, UART0_RX_GPIO_PIN_NUM) && s_pin_irq_func[0])
    {
        s_pin_irq_func[0](0);
        PORT_ClearPinsInterruptFlags(UART0_RX_PORT_BASE, ~0U);
    }
}
#endif // #if BL_ENABLE_PINMUX_UART0

//! @brief this is going to be used for autobaud IRQ handling for UART1
#if BL_ENABLE_PINMUX_UART1
void UART1_RX_GPIO_IRQHandler(void)
{
    // Check if the pin for UART1 is what triggered the RX PORT interrupt
    if (PORT_GetPinIsf(UART1_RX_PORT_BASE, UART1_RX_GPIO_PIN_NUM) && s_pin_irq_func[1])
    {
        s_pin_irq_func[1](1);
        PORT_ClearPinsInterruptFlags(UART1_RX_PORT_BASE, ~0U);
    }
}
#endif // #if BL_ENABLE_PINMUX_UART1

//! @brief this is going to be used for autobaud IRQ handling for UART2
#if BL_ENABLE_PINMUX_UART2
void UART2_RX_GPIO_IRQHandler(void)
{
    // Check if the pin for UART2 is what triggered the RX PORT interrupt
    if (PORT_GetPinIsf(UART2_RX_PORT_BASE, UART2_RX_GPIO_PIN_NUM) && s_pin_irq_func[2])
    {
        s_pin_irq_func[2](2);
        PORT_ClearPinsInterruptFlags(UART2_RX_PORT_BASE, ~0U);
    }
}
#endif // #if BL_ENABLE_PINMUX_UART2

//! @brief this is going to be used for autobaud IRQ handling for UART3
#if BL_ENABLE_PINMUX_UART3
void UART3_RX_GPIO_IRQHandler(void)
{
    // Check if the pin for UART3 is what triggered the RX PORT interrupt
    if (PORT_GetPinIsf(UART3_RX_PORT_BASE, UART3_RX_GPIO_PIN_NUM) && s_pin_irq_func[3])
    {
        s_pin_irq_func[3](3);
        PORT_ClearPinsInterruptFlags(UART3_RX_PORT_BASE, ~0U);
    }
}
#endif // #if BL_ENABLE_PINMUX_UART3

//! @brief this is going to be used for autobaud IRQ handling for UART4
#if BL_ENABLE_PINMUX_UART4
void UART4_RX_GPIO_IRQHandler(void)
{
    // Check if the pin for UART4 is what triggered the RX PORT interrupt
    if (PORT_GetPinIsf(UART4_RX_PORT_BASE, UART4_RX_GPIO_PIN_NUM) && s_pin_irq_func[4])
    {
        s_pin_irq_func[4](4);
        PORT_ClearPinsInterruptFlags(UART4_RX_PORT_BASE, ~0U);
    }
}
#endif // #if BL_ENABLE_PINMUX_UART4

void enable_autobaud_pin_irq(uint32_t instance, pin_irq_callback_t func)
{
    switch (instance)
    {
#if BL_ENABLE_PINMUX_UART0
        case 0:
            NVIC_SetPriority(UART0_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_ENABLED_PRIORITY);
            NVIC_EnableIRQ(UART0_RX_GPIO_IRQn);
            // Only look for a falling edge for our interrupts
            PORT_SetPinInterruptConfig(UART0_RX_PORT_BASE, UART0_RX_GPIO_PIN_NUM, kPORT_InterruptFallingEdge);
            s_pin_irq_func[0] = func;
            break;
#endif // #if BL_ENABLE_PINMUX_UART0

#if BL_ENABLE_PINMUX_UART1
        case 1:
            NVIC_SetPriority(UART1_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_ENABLED_PRIORITY);
            NVIC_EnableIRQ(UART1_RX_GPIO_IRQn);
            // Only look for a falling edge for our interrupts
            PORT_SetPinInterruptConfig(UART1_RX_PORT_BASE, UART1_RX_GPIO_PIN_NUM, kPORT_InterruptFallingEdge);
            s_pin_irq_func[1] = func;
            break;
#endif // #if BL_ENABLE_PINMUX_UART1

#if BL_ENABLE_PINMUX_UART2
        case 2:
            NVIC_SetPriority(UART2_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_ENABLED_PRIORITY);
            NVIC_EnableIRQ(UART2_RX_GPIO_IRQn);
            // Only look for a falling edge for our interrupts
            PORT_SetPinInterruptConfig(UART2_RX_PORT_BASE, UART2_RX_GPIO_PIN_NUM, kPORT_InterruptFallingEdge);
            s_pin_irq_func[2] = func;
            break;
#endif // #if BL_ENABLE_PINMUX_UART2

#if BL_ENABLE_PINMUX_UART3
        case 3:
            NVIC_SetPriority(UART3_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_ENABLED_PRIORITY);
            NVIC_EnableIRQ(UART3_RX_GPIO_IRQn);
            // Only look for a falling edge for our interrupts
            PORT_SetPinInterruptConfig(UART3_RX_PORT_BASE, UART3_RX_GPIO_PIN_NUM, kPORT_InterruptFallingEdge);
            s_pin_irq_func[3] = func;
            break;
#endif // #if BL_ENABLE_PINMUX_UART3

#if BL_ENABLE_PINMUX_UART4
        case 4:
            NVIC_SetPriority(UART4_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_ENABLED_PRIORITY);
            NVIC_EnableIRQ(UART4_RX_GPIO_IRQn);
            // Only look for a falling edge for our interrupts
            PORT_SetPinInterruptConfig(UART4_RX_PORT_BASE, UART4_RX_GPIO_PIN_NUM, kPORT_InterruptFallingEdge);
            s_pin_irq_func[4] = func;
            break;
#endif // #if BL_ENABLE_PINMUX_UART4

        default:
            break;
    }
}

void disable_autobaud_pin_irq(uint32_t instance)
{
    switch (instance)
    {
#if BL_ENABLE_PINMUX_UART0
        case 0:
            NVIC_DisableIRQ(UART0_RX_GPIO_IRQn);
            NVIC_SetPriority(UART0_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_RESTORED_PRIORITY);
            PORT_SetPinInterruptConfig(UART0_RX_PORT_BASE, UART0_RX_GPIO_PIN_NUM, kPORT_InterruptOrDMADisabled);
            s_pin_irq_func[0] = 0;
            break;
#endif // #if BL_ENABLE_PINMUX_UART0

#if BL_ENABLE_PINMUX_UART1
        case 1:
            NVIC_DisableIRQ(UART1_RX_GPIO_IRQn);
            NVIC_SetPriority(UART1_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_RESTORED_PRIORITY);
            PORT_SetPinInterruptConfig(UART1_RX_PORT_BASE, UART1_RX_GPIO_PIN_NUM, kPORT_InterruptOrDMADisabled);
            s_pin_irq_func[1] = 0;
            break;
#endif // #if BL_ENABLE_PINMUX_UART1

#if BL_ENABLE_PINMUX_UART2
        case 2:
            NVIC_DisableIRQ(UART2_RX_GPIO_IRQn);
            NVIC_SetPriority(UART2_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_RESTORED_PRIORITY);
            PORT_SetPinInterruptConfig(UART2_RX_PORT_BASE, UART2_RX_GPIO_PIN_NUM, kPORT_InterruptOrDMADisabled);
            s_pin_irq_func[2] = 0;
            break;
#endif // #if BL_ENABLE_PINMUX_UART2

#if BL_ENABLE_PINMUX_UART3
        case 3:
            NVIC_DisableIRQ(UART3_RX_GPIO_IRQn);
            NVIC_SetPriority(UART3_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_RESTORED_PRIORITY);
            PORT_SetPinInterruptConfig(UART3_RX_PORT_BASE, UART3_RX_GPIO_PIN_NUM, kPORT_InterruptOrDMADisabled);
            s_pin_irq_func[3] = 0;
            break;
#endif // #if BL_ENABLE_PINMUX_UART3

#if BL_ENABLE_PINMUX_UART4
        case 4:
            NVIC_DisableIRQ(UART4_RX_GPIO_IRQn);
            NVIC_SetPriority(UART4_RX_GPIO_IRQn, PORT_IRQC_INTERRUPT_RESTORED_PRIORITY);
            PORT_SetPinInterruptConfig(UART4_RX_PORT_BASE, UART4_RX_GPIO_PIN_NUM, kPORT_InterruptOrDMADisabled);
            s_pin_irq_func[4] = 0;
            break;
#endif // #if BL_ENABLE_PINMUX_UART4

        default:
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
