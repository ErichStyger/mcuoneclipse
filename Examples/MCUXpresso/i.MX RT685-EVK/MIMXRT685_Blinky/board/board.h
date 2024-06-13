/*
 * Copyright 2018-2019, 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_reset.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME      "MIMXRT685-EVK"
#define BOARD_I3C_CODEC (1)

/*! @brief The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE     kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) USART0
#define BOARD_DEBUG_UART_INSTANCE 0U
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetFlexCommClkFreq(0U)
#define BOARD_DEBUG_UART_FRG_CLK \
    (&(const clock_frg_clk_config_t){0, kCLOCK_FrgPllDiv, 255, 0}) /*!< Select FRG0 mux as frg_pll */
#define BOARD_DEBUG_UART_CLK_ATTACH kFRG_to_FLEXCOMM0
#define BOARD_DEBUG_UART_RST        kFC0_RST_SHIFT_RSTn
#define BOARD_DEBUG_UART_CLKSRC     kCLOCK_Flexcomm0
#define BOARD_UART_IRQ_HANDLER      FLEXCOMM0_IRQHandler
#define BOARD_UART_IRQ              FLEXCOMM0_IRQn

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

#define BOARD_FLEXSPI_PSRAM FLEXSPI
#ifndef BOARD_ENABLE_PSRAM_CACHE
#define BOARD_ENABLE_PSRAM_CACHE 1
#endif

#if BOARD_I3C_CODEC && (defined(SDK_I3C_BASED_COMPONENT_USED) && SDK_I3C_BASED_COMPONENT_USED)
#define BOARD_CODEC_I2C_BASEADDR   I3C
#define BOARD_CODEC_I2C_CLOCK_FREQ CLOCK_GetI3cClkFreq()
#define BOARD_CODEC_I2C_INSTANCE   0
#else
#define BOARD_CODEC_I2C_BASEADDR   I2C4
#define BOARD_CODEC_I2C_CLOCK_FREQ CLOCK_GetFlexCommClkFreq(4U)
#define BOARD_CODEC_I2C_INSTANCE   4
#endif

#define BOARD_PMIC_I2C_BASEADDR   I2C15
#define BOARD_PMIC_I2C_CLOCK_FREQ CLOCK_GetFlexCommClkFreq(15U)

#define BOARD_ACCEL_I2C_BASEADDR   I2C2
#define BOARD_ACCEL_I2C_ADDR       0x1E
#define BOARD_ACCEL_I2C_CLOCK_FREQ CLOCK_GetFlexCommClkFreq(2U)

/* Board led color mapping */
#define LOGIC_LED_ON  1U
#define LOGIC_LED_OFF 0U

#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIO
#endif
#define BOARD_LED_RED_GPIO_PORT 0U
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 31U
#endif

#ifndef BOARD_LED_GREEN_GPIO
#define BOARD_LED_GREEN_GPIO GPIO
#endif
#define BOARD_LED_GREEN_GPIO_PORT 0U
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 14U
#endif
#ifndef BOARD_LED_BLUE_GPIO
#define BOARD_LED_BLUE_GPIO GPIO
#endif
#define BOARD_LED_BLUE_GPIO_PORT 0U
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 26U
#endif

#ifndef BOARD_FLASH_RESET_GPIO
#define BOARD_FLASH_RESET_GPIO GPIO
#endif
#ifndef BOARD_FLASH_RESET_GPIO_PORT
#define BOARD_FLASH_RESET_GPIO_PORT 2U
#endif
#ifndef BOARD_FLASH_RESET_GPIO_PIN
#define BOARD_FLASH_RESET_GPIO_PIN 12U
#endif

/* Board microphone defines */
#ifndef BOARD_DMIC_NUM
#define BOARD_DMIC_NUM 2
#endif

#define LED_RED_INIT(output)                                                          \
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED_RED */
#define LED_RED_ON()                                          \
    GPIO_PortSet(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, \
                 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn on target LED_RED */
#define LED_RED_OFF()                                           \
    GPIO_PortClear(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, \
                   1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED_RED */
#define LED_RED_TOGGLE()                                         \
    GPIO_PortToggle(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, \
                    1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED_RED */

#define LED_GREEN_INIT(output)                                                              \
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED_GREEN */
#define LED_GREEN_ON()                                            \
    GPIO_PortSet(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, \
                 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED_GREEN */
#define LED_GREEN_OFF()                                             \
    GPIO_PortClear(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, \
                   1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED_GREEN */
#define LED_GREEN_TOGGLE()                                           \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, \
                    1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED_GREEN */

#define LED_BLUE_INIT(output)                                                            \
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED_BLUE */
#define LED_BLUE_ON()                                           \
    GPIO_PortSet(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED_BLUE */
#define LED_BLUE_OFF()                                            \
    GPIO_PortClear(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                   1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED_BLUE */
#define LED_BLUE_TOGGLE()                                          \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                    1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED_BLUE */

/* Board SW PIN */
#ifndef BOARD_SW1_GPIO
#define BOARD_SW1_GPIO GPIO
#endif
#define BOARD_SW1_GPIO_PORT 1U
#ifndef BOARD_SW1_GPIO_PIN
#define BOARD_SW1_GPIO_PIN 1U
#endif

#ifndef BOARD_SW2_GPIO
#define BOARD_SW2_GPIO GPIO
#endif
#define BOARD_SW2_GPIO_PORT 0U
#ifndef BOARD_SW2_GPIO_PIN
#define BOARD_SW2_GPIO_PIN 10U
#endif

/* USDHC configuration */
#define BOARD_SD_SUPPORT_180V          (1)
#define BOARD_USDHC_CD_GPIO_BASE       GPIO
#define BOARD_USDHC_CD_GPIO_PORT       (2)
#define BOARD_USDHC_CD_GPIO_PIN        (9)
#define BOARD_SD_POWER_RESET_GPIO      (GPIO)
#define BOARD_SD_POWER_RESET_GPIO_PORT (2)
#define BOARD_SD_POWER_RESET_GPIO_PIN  (10)

/* Card detect handled by uSDHC, no GPIO interrupt */
#define BOARD_SD_DETECT_TYPE              kSDMMCHOST_DetectCardByHostCD
#define BOARD_USDHC_CD_PORT_IRQ           USDHC0_IRQn
#define BOARD_USDHC_CD_STATUS()           0
#define BOARD_USDHC_CD_INTERRUPT_STATUS() 0
#define BOARD_USDHC_CD_CLEAR_INTERRUPT(flag)
#define BOARD_USDHC_CD_GPIO_INIT()

#define BOARD_HAS_SDCARD                 (1U)
#define BOARD_USDHC_CARD_INSERT_CD_LEVEL (0U)

#define BOARD_USDHC_MMCCARD_POWER_CONTROL_INIT()
#define BOARD_USDHC_MMCCARD_POWER_CONTROL(state)
#define BOARD_USDHC_SDCARD_POWER_CONTROL_INIT()                                                                \
    {                                                                                                          \
        GPIO_PortInit(BOARD_SD_POWER_RESET_GPIO, BOARD_SD_POWER_RESET_GPIO_PORT);                              \
        GPIO_PinInit(BOARD_SD_POWER_RESET_GPIO, BOARD_SD_POWER_RESET_GPIO_PORT, BOARD_SD_POWER_RESET_GPIO_PIN, \
                     &(gpio_pin_config_t){kGPIO_DigitalOutput, 0});                                            \
    }

#define BOARD_MMC_SUPPORT_8BIT_BUS 0

#define BOARD_USDHC_SDCARD_POWER_CONTROL(state)                                                                        \
    (state ?                                                                                                           \
         GPIO_PortSet(BOARD_SD_POWER_RESET_GPIO, BOARD_SD_POWER_RESET_GPIO_PORT, 1 << BOARD_SD_POWER_RESET_GPIO_PIN) : \
         GPIO_PortClear(BOARD_SD_POWER_RESET_GPIO, BOARD_SD_POWER_RESET_GPIO_PORT,                                     \
                        1 << BOARD_SD_POWER_RESET_GPIO_PIN))

#define BOARD_USDHC0_BASEADDR USDHC0

#define BOARD_USDHC0_CLK_FREQ CLOCK_GetSdioClkFreq(0)

#define BOARD_USDHC_SWITCH_VOLTAGE_FUNCTION 1U

#define BOARD_SD_HOST_BASEADDR BOARD_USDHC0_BASEADDR
#define BOARD_SD_HOST_CLK_FREQ BOARD_USDHC0_CLK_FREQ
#define BOARD_SD_HOST_IRQ      USDHC0_IRQn

#define BOARD_SD_Pin_Config(speed, strength)

/* USB PHY condfiguration */
#define BOARD_USB_PHY_D_CAL     (0x0CU)
#define BOARD_USB_PHY_TXCAL45DP (0x06U)
#define BOARD_USB_PHY_TXCAL45DM (0x06U)

#define BOARD_FLASH_SIZE (0x4000000U)

/* Display. */
#define BOARD_LCD_DC_GPIO      GPIO
#define BOARD_LCD_DC_GPIO_PORT 1U
#define BOARD_LCD_DC_GPIO_PIN  7U

#define BOARD_BT_UART_INSTANCE 4
#define BOARD_BT_UART_BAUDRATE 3000000
#define BOARD_BT_UART_CLK_FREQ CLOCK_GetFlexCommClkFreq(4U)
#define BOARD_BT_UART_FRG_CLK \
    (&(const clock_frg_clk_config_t){4, kCLOCK_FrgPllDiv, 255, 4}) /*!< Select FRG0 mux as frg_pll */
#define BOARD_BT_UART_CLK_ATTACH  kFRG_to_FLEXCOMM4
#define BOARD_BT_UART_RST         kFC4_RST_SHIFT_RSTn
#define BOARD_BT_UART_IRQ         FLEXCOMM4_IRQn
#define BOARD_BT_UART_IRQ_HANDLER FLEXCOMM4_IRQHandler
#define BOARD_BT_UART_CLKSRC      kCLOCK_Flexcomm4

/* ERPC SPI configuration */
#define ERPC_BOARD_SPI_SLAVE_READY_USE_GPIO (1)
#define ERPC_BOARD_SPI_BASEADDR             SPI14_BASE
#define ERPC_BOARD_SPI_BAUDRATE             500000U
#define ERPC_BOARD_SPI_CLKSRC               kCLOCK_Flexcomm14
#define ERPC_BOARD_SPI_CLK_FREQ             CLOCK_GetFlexCommClkFreq(14)
#define ERPC_BOARD_SPI_INT_GPIO             GPIO
#define ERPC_BOARD_SPI_INT_PORT             1U
#define ERPC_BOARD_SPI_INT_PIN              16U
#define ERPC_BOARD_SPI_INT_PIN_IRQ          PIN_INT1_IRQn
#define ERPC_BOARD_SPI_INT_PIN_IRQ_HANDLER  PIN_INT1_IRQHandler
#define ERPC_BOARD_SPI_INT_GPIO_LPC         (1)

/* ERPC I2C configuration */
#define ERPC_BOARD_I2C_BASEADDR            I2C2_BASE
#define ERPC_BOARD_I2C_BAUDRATE            100000U
#define ERPC_BOARD_I2C_CLKSRC              kCLOCK_Flexcomm2
#define ERPC_BOARD_I2C_CLK_FREQ            CLOCK_GetFlexCommClkFreq(2)
#define ERPC_BOARD_I2C_INT_GPIO            GPIO
#define ERPC_BOARD_I2C_INT_PORT            1U
#define ERPC_BOARD_I2C_INT_PIN             16U
#define ERPC_BOARD_I2C_INT_PIN_IRQ         PIN_INT1_IRQn
#define ERPC_BOARD_I2C_INT_PIN_IRQ_HANDLER PIN_INT1_IRQHandler

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
status_t BOARD_InitPsRam(void);
void BOARD_FlexspiClockSafeConfig(void);
AT_QUICKACCESS_SECTION_CODE(void BOARD_SetFlexspiClock(uint32_t src, uint32_t divider));
AT_QUICKACCESS_SECTION_CODE(void BOARD_DeinitXip(FLEXSPI_Type *base));
AT_QUICKACCESS_SECTION_CODE(void BOARD_InitXip(FLEXSPI_Type *base));
AT_QUICKACCESS_SECTION_CODE(void BOARD_SetDeepSleepPinConfig(void));
AT_QUICKACCESS_SECTION_CODE(void BOARD_RestoreDeepSleepPinConfig(void));
AT_QUICKACCESS_SECTION_CODE(void BOARD_EnterDeepSleep(const uint32_t exclude_from_pd[4]));
AT_QUICKACCESS_SECTION_CODE(void BOARD_EnterDeepPowerDown(const uint32_t exclude_from_pd[4]));
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_I2C_Init(I2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_I2C_Send(I2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize);
status_t BOARD_I2C_Receive(I2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize);
#endif
#if defined(SDK_I3C_BASED_COMPONENT_USED) && SDK_I3C_BASED_COMPONENT_USED
void BOARD_I3C_Init(I3C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_I3C_Send(I3C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize);
status_t BOARD_I3C_Receive(I3C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize);
#endif
#if defined BOARD_USE_CODEC
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_PMIC_I2C_Init(void);
status_t BOARD_PMIC_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_PMIC_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);

#endif /* SDK_I2C_BASED_COMPONENT_USED */
#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
