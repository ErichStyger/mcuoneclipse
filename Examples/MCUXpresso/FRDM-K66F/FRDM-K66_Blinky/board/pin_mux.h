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

/*! @name PORTA2 (coord K6), J9[6]/JTAG_TDO/TRACE_SWO/EZP_DO
  @{ */
#define BOARD_TRACE_SWO_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_TRACE_SWO_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

/*! @name PORTD11 (coord B2), SW2
  @{ */
#define BOARD_SW2_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_SW2_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SW2_PIN 11U    /*!<@brief PORTD pin index: 11 */
                             /* @} */

/*! @name PORTA10 (coord M9), SW3
  @{ */
#define BOARD_SW3_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_SW3_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_SW3_PIN 10U    /*!<@brief PORTA pin index: 10 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONsPins(void);

/*! @name PORTA11 (coord L9), LEDRGB_BLUE
  @{ */
#define BOARD_LED_BLUE_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_LED_BLUE_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_LED_BLUE_PIN 11U    /*!<@brief PORTA pin index: 11 */
                                  /* @} */

/*! @name PORTE6 (coord E1), LEDRGB_GREEN
  @{ */
#define BOARD_LED_GREEN_GPIO GPIOE /*!<@brief GPIO device name: GPIOE */
#define BOARD_LED_GREEN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_LED_GREEN_PIN 6U     /*!<@brief PORTE pin index: 6 */
                                   /* @} */

/*! @name PORTC9 (coord D7), LEDRGB_RED
  @{ */
#define BOARD_LED_RED_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_LED_RED_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_LED_RED_PIN 9U     /*!<@brief PORTC pin index: 9 */
                                 /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void);

#define PORT_DFER_DFE_8_MASK 0x0100u /*!<@brief Digital Filter Enable Mask for item 8. */
#define PORT_DFER_DFE_9_MASK 0x0200u /*!<@brief Digital Filter Enable Mask for item 9. */

/*! @name PORTD8 (coord C9), U8[4]/U19[11]/I2C0_SCL
  @{ */
#define BOARD_ACCEL_SCL_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_ACCEL_SCL_PIN 8U     /*!<@brief PORTD pin index: 8 */
                                   /* @} */

/*! @name PORTD9 (coord B9), U8[6]/U19[12]/I2C0_SDA
  @{ */
#define BOARD_ACCEL_SDA_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_ACCEL_SDA_PIN 9U     /*!<@brief PORTD pin index: 9 */
                                   /* @} */

/*! @name PORTC17 (coord D5), U8[11]/FXOS8700CQ_INT1
  @{ */
#define BOARD_ACCEL_INT1_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT1_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT1_PIN 17U    /*!<@brief PORTC pin index: 17 */
                                    /* @} */

/*! @name PORTC13 (coord D6), U8[9]/FXOS8700CQ_INT2
  @{ */
#define BOARD_ACCEL_INT2_GPIO GPIOC /*!<@brief GPIO device name: GPIOC */
#define BOARD_ACCEL_INT2_PORT PORTC /*!<@brief PORT device name: PORTC */
#define BOARD_ACCEL_INT2_PIN 13U    /*!<@brief PORTC pin index: 13 */
                                    /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCEL_I2CPins(void);

#define PORT_DFER_DFE_8_MASK 0x0100u /*!<@brief Digital Filter Enable Mask for item 8. */
#define PORT_DFER_DFE_9_MASK 0x0200u /*!<@brief Digital Filter Enable Mask for item 9. */

/*! @name PORTD9 (coord B9), U8[6]/U19[12]/I2C0_SDA
  @{ */
#define BOARD_GYRO_SDA_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_GYRO_SDA_PIN 9U     /*!<@brief PORTD pin index: 9 */
                                  /* @} */

/*! @name PORTD8 (coord C9), U8[4]/U19[11]/I2C0_SCL
  @{ */
#define BOARD_GYRO_SCL_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_GYRO_SCL_PIN 8U     /*!<@brief PORTD pin index: 8 */
                                  /* @} */

/*! @name PORTA29 (coord H11), U19[3]/FXAS21002_INT1
  @{ */
#define BOARD_GYRO_INT1_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_GYRO_INT1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_GYRO_INT1_PIN 29U    /*!<@brief PORTA pin index: 29 */
                                   /* @} */

/*! @name PORTA28 (coord H12), U19[2]/FXAS21002_INT2
  @{ */
#define BOARD_GYRO_INT2_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_GYRO_INT2_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_GYRO_INT2_PIN 28U    /*!<@brief PORTA pin index: 28 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitGYRO_I2CPins(void);

#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART 0 transmit data source select: UART0_TX pin */

/*! @name PORTB16 (coord E10), U7[4]/UART0_RX
  @{ */
#define BOARD_DEBUG_UART_RX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_RX_PIN 16U    /*!<@brief PORTB pin index: 16 */
                                       /* @} */

/*! @name PORTB17 (coord E9), U10[1]/UART0_TX
  @{ */
#define BOARD_DEBUG_UART_TX_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_DEBUG_UART_TX_PIN 17U    /*!<@brief PORTB pin index: 17 */
                                       /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void);

#define PORT_DFER_DFE_10_MASK 0x0400u /*!<@brief Digital Filter Enable Mask for item 10. */

/*! @name PORTE3 (coord E4), SDHC0_CMD
  @{ */
#define BOARD_SDHC0_CMD_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_CMD_PIN 3U     /*!<@brief PORTE pin index: 3 */
                                   /* @} */

/*! @name PORTE1 (coord D2), SDHC0_D0
  @{ */
#define BOARD_SDHC0_D0_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D0_PIN 1U     /*!<@brief PORTE pin index: 1 */
                                  /* @} */

/*! @name PORTE0 (coord D3), SDHC0_D1
  @{ */
#define BOARD_SDHC0_D1_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D1_PIN 0U     /*!<@brief PORTE pin index: 0 */
                                  /* @} */

/*! @name PORTE5 (coord E2), SDHC0_D2
  @{ */
#define BOARD_SDHC0_D2_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D2_PIN 5U     /*!<@brief PORTE pin index: 5 */
                                  /* @} */

/*! @name PORTE4 (coord E3), SDHC0_D3
  @{ */
#define BOARD_SDHC0_D3_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_D3_PIN 4U     /*!<@brief PORTE pin index: 4 */
                                  /* @} */

/*! @name PORTE2 (coord D1), SDHC0_DCLK
  @{ */
#define BOARD_SDHC0_DCLK_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_SDHC0_DCLK_PIN 2U     /*!<@brief PORTE pin index: 2 */
                                    /* @} */

/*! @name PORTD10 (coord B3), SD_CARD_DETECT
  @{ */
#define BOARD_SDCARD_CARD_DETECTION_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_SDCARD_CARD_DETECTION_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_SDCARD_CARD_DETECTION_PIN 10U    /*!<@brief PORTD pin index: 10 */
                                               /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDHC0Pins(void);

#define SOPT2_RMIISRC_ENET 0x01u /*!<@brief RMII clock source select: External bypass clock (ENET_1588_CLKIN). */

/*! @name PORTE26 (coord K4), U13[16]/ETHERNET_CLOCK
  @{ */
#define BOARD_ETHERNET_CLOCK_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_ETHERNET_CLOCK_PIN 26U    /*!<@brief PORTE pin index: 26 */
                                        /* @} */

/*! @name PORTA14 (coord L10), U13[15]/RMII0_CRS_DV
  @{ */
#define BOARD_RMII0_CRS_DV_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_CRS_DV_PIN 14U    /*!<@brief PORTA pin index: 14 */
                                      /* @} */

/*! @name PORTB1 (coord H9), U13[11]/RMII0_MDC
  @{ */
#define BOARD_RMII0_MDC_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_RMII0_MDC_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                   /* @} */

/*! @name PORTB0 (coord H10), U13[10]/RMII0_MDIO
  @{ */
#define BOARD_RMII0_MDIO_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_RMII0_MDIO_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                    /* @} */

/*! @name PORTA13 (coord J9), U13[13]/RMII0_RXD0
  @{ */
#define BOARD_RMII0_RXD0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_RXD0_PIN 13U    /*!<@brief PORTA pin index: 13 */
                                    /* @} */

/*! @name PORTA12 (coord K9), U13[12]/RMII0_RXD1
  @{ */
#define BOARD_RMII0_RXD1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_RXD1_PIN 12U    /*!<@brief PORTA pin index: 12 */
                                    /* @} */

/*! @name PORTA5 (coord M8), U13[17]/RMII0_RXER
  @{ */
#define BOARD_RMII0_RXER_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_RXER_PIN 5U     /*!<@brief PORTA pin index: 5 */
                                    /* @} */

/*! @name PORTA16 (coord K10), U13[20]/RMII0_TXD_0
  @{ */
#define BOARD_RMII0_TXD_0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_TXD_0_PIN 16U    /*!<@brief PORTA pin index: 16 */
                                     /* @} */

/*! @name PORTA17 (coord K11), U13[21]/RMII0_TXD_1
  @{ */
#define BOARD_RMII0_TXD_1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_TXD_1_PIN 17U    /*!<@brief PORTA pin index: 17 */
                                     /* @} */

/*! @name PORTA15 (coord L11), U13[19]/RMII0_TXEN
  @{ */
#define BOARD_RMII0_TXEN_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_RMII0_TXEN_PIN 15U    /*!<@brief PORTA pin index: 15 */
                                    /* @} */

/*! @name PORTE26 (coord K4), U13[16]/ETHERNET_CLOCK
  @{ */
#define BOARD_ENET_1588_CLKIN_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_ENET_1588_CLKIN_PIN 26U    /*!<@brief PORTE pin index: 26 */
                                         /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitENETPins(void);

/*! @name USB1_DM (coord K1), K66_MICRO_USB_DN
  @{ */
/* @} */

/*! @name USB1_DP (coord J1), K66_MICRO_USB_DP
  @{ */
/* @} */

/*! @name PORTE10 (coord F1), USB_ID
  @{ */
#define BOARD_USB_ID_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_USB_ID_PIN 10U    /*!<@brief PORTE pin index: 10 */
                                /* @} */

/*! @name USB1_VBUS (coord L1), P5V_K66_USB
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSBPins(void);

/*! @name PORTA18 (coord M12), EXTAL0
  @{ */
#define BOARD_EXTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_EXTAL0_PIN 18U    /*!<@brief PORTA pin index: 18 */
                                /* @} */

/*! @name PORTA19 (coord M11), X501[3]
  @{ */
#define BOARD_XTAL0_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_XTAL0_PIN 19U    /*!<@brief PORTA pin index: 19 */
                               /* @} */

/*! @name EXTAL32 (coord M6), Y3[2]
  @{ */
/* @} */

/*! @name XTAL32 (coord M7), Y3[1]
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSCsPins(void);

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
