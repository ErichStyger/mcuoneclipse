/*
 * Copyright 2018-2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*! @name PORTC6 (number 78), U8[11]/SW2
  @{ */
#define BOARD_SW2_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_SW2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_SW2_PIN 6U     /*!<@brief PORTC pin index: 6 */
                             /* @} */

/*! @name PORTA4 (number 38), SW3
  @{ */
#define BOARD_SW3_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_SW3_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SW3_PIN 4U     /*!<@brief PORTA pin index: 4 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitButtonsPins(void);

/*! @name PORTB21 (number 67), D12[3]/LEDRGB_BLUE
  @{ */
#define BOARD_LED_BLUE_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_LED_BLUE_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_LED_BLUE_PIN 21U    /*!<@brief PORTB pin index: 21 */
                                  /* @} */

/*! @name PORTB22 (number 68), D12[1]/LEDRGB_RED
  @{ */
#define BOARD_LED_RED_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_LED_RED_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_LED_RED_PIN 22U    /*!<@brief PORTB pin index: 22 */
                                 /* @} */

/*! @name PORTE26 (number 33), J2[1]/D12[4]/LEDRGB_GREEN
  @{ */
#define BOARD_LED_GREEN_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_GREEN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_GREEN_PIN 26U    /*!<@brief PORTE pin index: 26 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB17 (number 63), U10[1]/UART0_TX
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_TX_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                       /* @} */

/*! @name PORTB16 (number 62), U7[4]/UART0_RX
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_RX_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

/*! @name PORTA18 (number 50), U13[16]/RMII_RXCLK
  @{ */
#define BOARD_EXTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_EXTAL0_PIN 18U    /*!<@brief PORTA pin index: 18 */
                                /* @} */

/*! @name EXTAL32 (number 29), Y3[2]/EXTAL32_RTC
  @{ */
/* @} */

/*! @name XTAL32 (number 28), Y3[1]/XTAL32_RTC
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSCPins(void);

/*! @name PORTE25 (number 32), J2[18]/U8[6]/I2C0_SDA
  @{ */
#define BOARD_ACCEL_SDA_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_ACCEL_SDA_PIN 25U    /*!<@brief PORTE pin index: 25 */
                                   /* @} */

/*! @name PORTE24 (number 31), J2[20]/U8[4]/I2C0_SCL
  @{ */
#define BOARD_ACCEL_SCL_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_ACCEL_SCL_PIN 24U    /*!<@brief PORTE pin index: 24 */
                                   /* @} */

/*! @name PORTC6 (number 78), U8[11]/SW2
  @{ */
#define BOARD_ACCEL_INT1_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT1_PIN 6U     /*!<@brief PORTC pin index: 6 */
                                    /* @} */

/*! @name PORTC13 (number 85), U8[9]
  @{ */
#define BOARD_ACCEL_INT2_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT2_PIN 13U    /*!<@brief PORTC pin index: 13 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCELPins(void);

#define SOPT2_RMIISRC_EXTAL 0x00u /*!<@brief RMII clock source select: EXTAL clock */

/*! @name PORTB1 (number 54), U13[11]/RMII0_MDC
  @{ */
#define BOARD_RMII0_MDC_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_RMII0_MDC_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                   /* @} */

/*! @name PORTB0 (number 53), U13[10]/RMII0_MDIO
  @{ */
#define BOARD_RMII0_MDIO_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_RMII0_MDIO_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                    /* @} */

/*! @name PORTA13 (number 43), U13[13]/RMII0_RXD_0
  @{ */
#define BOARD_RMII0_RXD0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_RXD0_PIN 13U    /*!<@brief PORTA pin index: 13 */
                                    /* @} */

/*! @name PORTA12 (number 42), U13[12]/RMII0_RXD_1
  @{ */
#define BOARD_RMII0_RXD1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_RXD1_PIN 12U    /*!<@brief PORTA pin index: 12 */
                                    /* @} */

/*! @name PORTA5 (number 39), U13[17]/RMII0_RXER
  @{ */
#define BOARD_RMII0_RXER_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_RXER_PIN 5U     /*!<@brief PORTA pin index: 5 */
                                    /* @} */

/*! @name PORTA16 (number 46), U13[20]/RMII0_TXD0
  @{ */
#define BOARD_RMII0_TXD0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_TXD0_PIN 16U    /*!<@brief PORTA pin index: 16 */
                                    /* @} */

/*! @name PORTA17 (number 47), U13[21]/RMII0_TXD1
  @{ */
#define BOARD_RMII0_TXD1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_TXD1_PIN 17U    /*!<@brief PORTA pin index: 17 */
                                    /* @} */

/*! @name PORTA15 (number 45), U13[19]/RMII0_TXEN
  @{ */
#define BOARD_RMII0_TXEN_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_TXEN_PIN 15U    /*!<@brief PORTA pin index: 15 */
                                    /* @} */

/*! @name PORTA14 (number 44), U13[15]/RMII0_CRS_DV
  @{ */
#define BOARD_RMII0_CRS_DV_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_CRS_DV_PIN 14U    /*!<@brief PORTA pin index: 14 */
                                      /* @} */

/*! @name PORTA18 (number 50), U13[16]/RMII_RXCLK
  @{ */
#define BOARD_RMII_RXCLK_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII_RXCLK_PIN 18U    /*!<@brief PORTA pin index: 18 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitENETPins(void);

/*! @name PORTE0 (number 1), J15[P8]/SDHC0_D1
  @{ */
#define BOARD_SDHC0_D1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D1_PIN 0U     /*!<@brief PORTE pin index: 0 */
                                  /* @} */

/*! @name PORTE1 (number 2), J15[P7]/SDHC0_D0
  @{ */
#define BOARD_SDHC0_D0_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D0_PIN 1U     /*!<@brief PORTE pin index: 1 */
                                  /* @} */

/*! @name PORTE2 (number 3), J15[P5]/SDHC0_DCLK
  @{ */
#define BOARD_SDHC0_DCLK_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_DCLK_PIN 2U     /*!<@brief PORTE pin index: 2 */
                                    /* @} */

/*! @name PORTE3 (number 4), J15[P3]/SDHC0_CMD
  @{ */
#define BOARD_SDHC0_CMD_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_CMD_PIN 3U     /*!<@brief PORTE pin index: 3 */
                                   /* @} */

/*! @name PORTE4 (number 5), J15[P2]/SDHC0_D3
  @{ */
#define BOARD_SDHC0_D3_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D3_PIN 4U     /*!<@brief PORTE pin index: 4 */
                                  /* @} */

/*! @name PORTE5 (number 6), J15[P1]/SDHC0_D2
  @{ */
#define BOARD_SDHC0_D2_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D2_PIN 5U     /*!<@brief PORTE pin index: 5 */
                                  /* @} */

/*! @name PORTE6 (number 7), J15[G1]/SD_CARD_DETECT
  @{ */
#define BOARD_SDHC_CD_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_SDHC_CD_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC_CD_PIN 6U     /*!<@brief PORTE pin index: 6 */
                                 /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDHCPins(void);

/*! @name USB0_DP (number 10), J22[3]/K64_MICRO_USB_DP
  @{ */
/* @} */

/*! @name USB0_DM (number 11), J22[2]/K64_MICRO_USB_DN
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSBPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
