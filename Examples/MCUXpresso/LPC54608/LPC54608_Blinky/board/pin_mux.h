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
 * @brief Select Analog/Digital mode.: Digital mode. */
#define PIO010_DIGIMODE_DIGITAL 0x01u
/*!
 * @brief Selects pin function.: Alternative connection 6. */
#define PIO010_FUNC_ALT6 0x06u
/*!
 * @brief
 * Selects function mode (on-chip pull-up/pull-down resistor control).
 * : Inactive.
 * Inactive (no pull-down/pull-up resistor enabled).
 */
#define PIO010_MODE_INACTIVE 0x00u

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void); /* Function assigned for the Cortex-M4F */

#define PIO04_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO04_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */
#define PIO05_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO05_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */
#define PIO06_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO06_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */
#define PIO11_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO11_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */

/*! @name PIO0_6 (coord A5), U28[C8]/RP5[4]/SW2/P0_6-ISP2/P0_6-EMC_D4
  @{ */
#define BOARD_SW2_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_SW2_PORT 0U   /*!<@brief PORT device name: 0U */
#define BOARD_SW2_PIN 6U    /*!<@brief 0U pin index: 6 */
                            /* @} */

/*! @name PIO0_5 (coord E7), U28[C9]/RP3[1]/JS32[1]/SW3/P0_5-ISP1/P0_5-EMC_D3
  @{ */
#define BOARD_SW3_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_SW3_PORT 0U   /*!<@brief PORT device name: 0U */
#define BOARD_SW3_PIN 5U    /*!<@brief 0U pin index: 5 */
                            /* @} */

/*! @name PIO0_4 (coord C8), U28[B8]/RP3[2]/JS32[3]/SW4/P0_4-ISP0/P0_4-EMC_D2
  @{ */
#define BOARD_SW4_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_SW4_PORT 0U   /*!<@brief PORT device name: 0U */
#define BOARD_SW4_PIN 4U    /*!<@brief 0U pin index: 4 */
                            /* @} */

/*! @name PIO1_1 (coord K12), J12[12]/U29[4]/SW5/P1_1-USER_PB-USB1_OVRCURn
  @{ */
#define BOARD_SW5_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_SW5_PORT 1U   /*!<@brief PORT device name: 1U */
#define BOARD_SW5_PIN 1U    /*!<@brief 1U pin index: 1 */
                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitBUTTONsPins(void); /* Function assigned for the Cortex-M4F */

#define PIO22_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO22_FUNC_ALT0 0x00u         /*!<@brief Selects pin function.: Alternative connection 0. */
#define PIO314_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO314_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */
#define PIO33_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO33_FUNC_ALT0 0x00u         /*!<@brief Selects pin function.: Alternative connection 0. */

/*! @name PIO3_3 (coord A13), J9[8]/LED2/P3_3-USR_LED2
  @{ */
#define BOARD_LED2_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_LED2_PORT 3U   /*!<@brief PORT device name: 3U */
#define BOARD_LED2_PIN 3U    /*!<@brief 3U pin index: 3 */
                             /* @} */

/*! @name PIO2_2 (coord C3), J9[6]/LED3/P2_2-CT1MAT1-USR_LED3
  @{ */
#define BOARD_LED3_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_LED3_PORT 2U   /*!<@brief PORT device name: 2U */
#define BOARD_LED3_PIN 2U    /*!<@brief 2U pin index: 2 */
                             /* @} */

/*! @name PIO3_14 (coord E3), J13[5]/LED1/P3_14-CT3MAT1-USR_LED1
  @{ */
#define BOARD_LED1_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_LED1_PORT 3U   /*!<@brief PORT device name: 3U */
#define BOARD_LED1_PIN 14U   /*!<@brief 3U pin index: 14 */
                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDsPins(void); /* Function assigned for the Cortex-M4F */

#define PIO00_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO00_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO013_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO013_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO014_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO014_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO01_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO01_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO02_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO02_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO03_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO03_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO313_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO313_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */

/*! @name FC3_CTS_SDA_SSEL0 (coord A1), U26[14]/J14[1]/P0_1-ISP_FC3_SSEL0
  @{ */
/* @} */

/*! @name FC3_RXD_SDA_MOSI (coord A10), U28[B9]/RP3[3]/JS34[1]/U26[11]/J14[2]/P0_3-ISP_FC3_MOSI/P0_3-EMC_D1
  @{ */
/* @} */

/*! @name FC3_TXD_SCL_MISO (coord E9), U28[A8]/RP3[4]/JS35[1]/U24[11]/J14[3]/P0_2-ISP_FC3_MISO/P0_2-EMC_D0
  @{ */
/* @} */

/*! @name FC3_SCK (coord D6), U26[13]/J14[4]/P0_0-ISP_FC3_SCK
  @{ */
/* @} */

/*! @name PIO3_13 (coord H4), J14[8]/P3_13-BRIDGE_GPIO
  @{ */
#define BOARD_BRIDGE_GPIO_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_BRIDGE_GPIO_PORT 3U   /*!<@brief PORT device name: 3U */
#define BOARD_BRIDGE_GPIO_PIN 13U   /*!<@brief 3U pin index: 13 */
                                    /* @} */

/*! @name FC1_CTS_SDA_SSEL0 (coord F11), JS16[2]/J14[9]/P0_13-ISP_FC1_SDAX
  @{ */
/* @} */

/*! @name FC1_RTS_SCL_SSEL1 (coord E13), JS15[2]/J14[10]/P0_14-ISP_FC1_SCLX
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPMod_SPI_I2C_BRIDGEPins(void); /* Function assigned for the Cortex-M4F */

#define PIO323_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO323_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO324_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO324_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO34_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO34_FUNC_ALT0 0x00u         /*!<@brief Selects pin function.: Alternative connection 0. */

/*! @name FC2_CTS_SDA_SSEL0 (coord C2), J11[10]/J9[3]/U10[3]/J17[5]/U19[10]/P3_23-FC2_SDAX
  @{ */
/* @} */

/*! @name FC2_RTS_SCL_SSEL1 (coord E2), J11[9]/J9[1]/U10[2]/J17[4]/U19[2]/P3_24-FC2_SCLX
  @{ */
/* @} */

/*! @name PIO3_4 (coord B11), J12[10]/U19[3]/P3_4-ACCL_INTR
  @{ */
#define BOARD_ACCL_INTR_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_ACCL_INTR_PORT 3U   /*!<@brief PORT device name: 3U */
#define BOARD_ACCL_INTR_PIN 4U    /*!<@brief 3U pin index: 4 */
                                  /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCELPins(void); /* Function assigned for the Cortex-M4F */

#define PIO023_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO023_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO024_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO024_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO025_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO025_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO026_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO026_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO027_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO027_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO028_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO028_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO212_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO212_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */

/*! @name SPIFI_CLK (coord M13), J13[2]/U27[6]/P0_26-SPIFI_CLK
  @{ */
/* @} */

/*! @name SPIFI_IO(0) (coord M7), J13[6]/U27[5]/P0_24-SPIFI_IO0
  @{ */
/* @} */

/*! @name SPIFI_IO(1) (coord K8), J13[4]/U27[2]/P0_25-SPIFI_IO1
  @{ */
/* @} */

/*! @name SPIFI_IO(3) (coord L9), J13[12]/U27[7]/P0_27-SPIFI_IO3
  @{ */
/* @} */

/*! @name SPIFI_IO(2) (coord M9), J13[10]/U27[3]/P0_28-SPIFI_IO2-USB0_OCURRn
  @{ */
/* @} */

/*! @name SPIFI_CSN (coord N7), J13[8]/U27[1]/P0_23-SPIFI_CSn-MCLK
  @{ */
/* @} */

/*! @name PIO2_12 (coord M2), U26A1[3]/P2_12-SPIFI_RSTn
  @{ */
#define BOARD_SPIFI_RSTn_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_SPIFI_RSTn_PORT 2U   /*!<@brief PORT device name: 2U */
#define BOARD_SPIFI_RSTn_PIN 12U   /*!<@brief 2U pin index: 12 */
                                   /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitQSPI_FLASHPins(void); /* Function assigned for the Cortex-M4F */

#define PIO210_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO210_FUNC_ALT2 0x02u        /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO23_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO23_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO24_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO24_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO25_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO25_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO26_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO26_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO27_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO27_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO28_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO28_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO29_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO29_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO315_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO315_FUNC_ALT2 0x02u        /*!<@brief Selects pin function.: Alternative connection 2. */

/*! @name SD_WR_PRT (coord D2), RP1[1]/U9[8]/P3_15-SD_WPn
  @{ */
/* @} */

/*! @name SD_CARD_DET_N (coord P1), RP1[2]/U9[7]/P2_10-SD_CDn
  @{ */
/* @} */

/*! @name SD_D(2) (coord F4), RP1[3]/U9[6]/P2_8-SD_D2
  @{ */
/* @} */

/*! @name SD_D(1) (coord J2), RP1[4]/U9[5]/P2_7-SD_D1
  @{ */
/* @} */

/*! @name SD_D(0) (coord F3), RP1[5]/U9[4]/P2_6-SD_D0
  @{ */
/* @} */

/*! @name SD_CLK (coord B1), U9[3]/P2_3-SD_CLK
  @{ */
/* @} */

/*! @name SD_CMD (coord D3), RP1[6]/U9[2]/P2_4-SD_CMD
  @{ */
/* @} */

/*! @name SD_D(3) (coord K2), RP1[7]/U9[1]/P2_9-SD_D3
  @{ */
/* @} */

/*! @name SD_POW_EN (coord C1), Q3[1]/P2_5-SD_POW_EN
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDHCPins(void); /* Function assigned for the Cortex-M4F */

#define PIO015_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO015_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO018_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO018_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO019_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO019_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO020_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO020_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO021_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO021_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO02_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO02_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO03_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO03_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO04_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO04_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO05_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO05_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO06_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO06_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO07_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO07_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO08_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO08_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO09_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO09_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO110_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO110_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO111_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO111_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO112_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO112_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO113_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO113_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO114_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO114_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO115_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO115_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO116_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO116_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO119_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO119_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO120_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO120_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO121_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO121_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO123_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO123_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO124_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO124_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO125_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO125_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO126_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO126_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO127_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO127_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO128_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO128_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO129_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO129_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO130_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO130_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO131_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO131_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO14_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO14_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO15_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO15_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO16_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO16_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO17_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO17_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO18_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO18_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO19_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO19_FUNC_ALT6 0x06u         /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO325_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO325_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */

/*! @name EMC_A(14) (coord P9), U28[G8]/P3_25-EMC_A14
  @{ */
/* @} */

/*! @name EMC_A(13) (coord M12), U28[G7]/P1_25-EMC_A13
  @{ */
/* @} */

/*! @name EMC_A(12) (coord N14), U28[G1]/P1_24-EMC_A12
  @{ */
/* @} */

/*! @name EMC_A(11) (coord M10), U28[G2]/P1_23-EMC_A11
  @{ */
/* @} */

/*! @name EMC_A(10) (coord B7), U28[H9]/P1_16-EMC_A10
  @{ */
/* @} */

/*! @name EMC_A(9) (coord F10), U28[G3]/P1_27-EMC_A9
  @{ */
/* @} */

/*! @name EMC_A(8) (coord J10), U28[H1]/P1_26-EMC_A8
  @{ */
/* @} */

/*! @name EMC_A(7) (coord P8), U28[H2]/P1_8-EMC_A7
  @{ */
/* @} */

/*! @name EMC_A(6) (coord N1), U28[H3]/P1_7-EMC_A6
  @{ */
/* @} */

/*! @name EMC_A(5) (coord G4), U28[J2]/P1_6-EMC_A5
  @{ */
/* @} */

/*! @name EMC_A(4) (coord E4), U28[J3]/P1_5-EMC_A4
  @{ */
/* @} */

/*! @name EMC_A(3) (coord C13), U28[J7]/P0_21-EMC_A3
  @{ */
/* @} */

/*! @name EMC_A(2) (coord D13), U28[J8]/P0_20-EMC_A2
  @{ */
/* @} */

/*! @name EMC_A(1) (coord C6), U28[H8]/P0_19-EMC_A1
  @{ */
/* @} */

/*! @name EMC_A(0) (coord C14), U28[H7]/P0_18-EMC_A0
  @{ */
/* @} */

/*! @name EMC_WEN (coord L4), U28[F9]/P0_15-EMC_WEn
  @{ */
/* @} */

/*! @name EMC_CASN (coord K6), U28[F7]/P1_9-EMC_CASn
  @{ */
/* @} */

/*! @name EMC_RASN (coord N9), U28[F8]/P1_10-EMC_RASn
  @{ */
/* @} */

/*! @name EMC_DYCSN(0) (coord K9), U28[G9]/P1_12-EMC_DYCSn0
  @{ */
/* @} */

/*! @name EMC_D(15) (coord C5), U28[A2]/RP2[1]/P1_31-EMC_D15
  @{ */
/* @} */

/*! @name EMC_D(14) (coord A8), U28[B1]/RP2[2]/P1_30-EMC_D14
  @{ */
/* @} */

/*! @name EMC_D(13) (coord C11), U28[B2]/RP2[3]/P1_29-EMC_D13
  @{ */
/* @} */

/*! @name EMC_D(12) (coord E12), U28[C1]/RP2[4]/P1_28-EMC_D12
  @{ */
/* @} */

/*! @name EMC_D(11) (coord D4), U28[C2]/RP4[1]/P1_4-EMC_D11
  @{ */
/* @} */

/*! @name EMC_D(10) (coord N8), U28[D1]/RP4[2]/P1_21-EMC_D10
  @{ */
/* @} */

/*! @name EMC_D(9) (coord M1), U28[D2]/RP4[3]/P1_20-EMC_D9
  @{ */
/* @} */

/*! @name EMC_D(8) (coord L1), U28[E1]/RP4[4]/P1_19-EMC_D8
  @{ */
/* @} */

/*! @name EMC_D(7) (coord G12), U28[E9]/RP5[1]/P0_9-EMC_D7
  @{ */
/* @} */

/*! @name EMC_D(6) (coord H10), U28[D8]/RP5[2]/P0_8-EMC_D6
  @{ */
/* @} */

/*! @name EMC_D(5) (coord H12), U28[D9]/RP5[3]/P0_7-EMC_D5
  @{ */
/* @} */

/*! @name EMC_D(4) (coord A5), U28[C8]/RP5[4]/SW2/P0_6-ISP2/P0_6-EMC_D4
  @{ */
/* @} */

/*! @name EMC_D(3) (coord E7), U28[C9]/RP3[1]/JS32[1]/SW3/P0_5-ISP1/P0_5-EMC_D3
  @{ */
/* @} */

/*! @name EMC_D(2) (coord C8), U28[B8]/RP3[2]/JS32[3]/SW4/P0_4-ISP0/P0_4-EMC_D2
  @{ */
/* @} */

/*! @name EMC_D(1) (coord A10), U28[B9]/RP3[3]/JS34[1]/U26[11]/J14[2]/P0_3-ISP_FC3_MOSI/P0_3-EMC_D1
  @{ */
/* @} */

/*! @name EMC_D(0) (coord E9), U28[A8]/RP3[4]/JS35[1]/U24[11]/J14[3]/P0_2-ISP_FC3_MISO/P0_2-EMC_D0
  @{ */
/* @} */

/*! @name EMC_DQM(1) (coord C12), U28[F1]/P1_14-EMC_DQM1
  @{ */
/* @} */

/*! @name EMC_DQM(0) (coord G10), U28[E8]/P1_13-EMC_DQM0
  @{ */
/* @} */

/*! @name EMC_CLK(0) (coord B4), U28[F2]/P1_11-EMC_CLK0
  @{ */
/* @} */

/*! @name EMC_CKE(0) (coord A11), U28[F3]/P1_15-EMC_CKE0
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDRAMPins(void); /* Function assigned for the Cortex-M4F */

#define PIO022_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO022_FUNC_ALT7 0x07u        /*!<@brief Selects pin function.: Alternative connection 7. */
#define PIO411_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO411_FUNC_ALT3 0x03u        /*!<@brief Selects pin function.: Alternative connection 3. */

/*! @name USB1_DP (coord H3), J2[3]/U2[2]/U25[H3]/USB1_DP_TRGT
  @{ */
/* @} */

/*! @name USB1_DM (coord H2), J2[2]/U2[3]/U25[H2]/USB1_DM_TRGT
  @{ */
/* @} */

/*! @name USB0_DM (coord D5), J3[2]/U3[3]/USB0_DM_TRGT
  @{ */
/* @} */

/*! @name USB0_DP (coord E5), J3[3]/U3[2]/USB0_DP_TRGT
  @{ */
/* @} */

/*! @name USB1_VBUS (coord G2), J2[1]/U2[4]/VBUS1_TARGET
  @{ */
/* @} */

/*! @name USB0_VBUS (coord B12), U3[4]/J3[1]/P0_22-USB0_VBUS
  @{ */
/* @} */

/*! @name USB1_ID (coord G1), J2[4]/USB1_ID_TARGET
  @{ */
/* @} */

/*! @name USB0_IDVALUE (coord A9), U12[8]/JP12[1]/J3[4]/JP12[3]/P4_11-USB0_ID/P4_11-ENET_RXD0
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSBPins(void); /* Function assigned for the Cortex-M4F */

#define PIO029_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO029_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO030_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO030_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */

/*! @name FC0_RXD_SDA_MOSI (coord B13), U24[13]/P0_29-ISP_FC0_RXD
  @{ */
/* @} */

/*! @name FC0_TXD_SCL_MISO (coord A2), U24[12]/P0_30-ISP_FC0_TXD
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDEBUG_UARTPins(void); /* Function assigned for the Cortex-M4F */

#define PIO010_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO010_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO011_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO011_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */
#define PIO012_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO012_FUNC_ALT6 0x06u        /*!<@brief Selects pin function.: Alternative connection 6. */

/*! @name SWDIO (coord M3), P1[2]/U22[4]/D5[5]/IF_SWDIO
  @{ */
/* @} */

/*! @name SWCLK (coord L3), U16[4]/SWDCLK_TRGT
  @{ */
/* @} */

/*! @name SWO (coord P2), U16[12]/SWO_TRGT
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSWD_DEBUGPins(void); /* Function assigned for the Cortex-M4F */

#define PIO211_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO211_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO213_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO213_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO214_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO214_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO215_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO215_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO216_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO216_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO221_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO221_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO222_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO222_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO223_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO223_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO224_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO224_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO225_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO225_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO228_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO228_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO229_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO229_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO230_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO230_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO231_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO231_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO30_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO30_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO31_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO31_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO35_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO35_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO36_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO36_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO37_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO37_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO38_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO38_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO39_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO39_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */

/*! @name LCD_PWR (coord K3), J16[31]/P2_11-LCD_PWR
  @{ */
/* @} */

/*! @name LCD_FP (coord L7), J16[33]/P2_14-LCD_FP
  @{ */
/* @} */

/*! @name LCD_DCLK (coord P7), J16[30]/P2_13-LCD_DCLK
  @{ */
/* @} */

/*! @name LCD_LP (coord L8), J16[32]/P2_16-LCD_LP
  @{ */
/* @} */

/*! @name LCD_AC (coord M8), J16[34]/P2_15-LCD_AC_ENAB_M
  @{ */
/* @} */

/*! @name LCD_VD(4) (coord K10), J16[9]/P2_22-LCD_VD4
  @{ */
/* @} */

/*! @name LCD_VD(3) (coord L10), J16[8]/P2_21-LCD_VD3
  @{ */
/* @} */

/*! @name LCD_VD(11) (coord G11), J16[16]/P2_29-LCD_VD11
  @{ */
/* @} */

/*! @name LCD_VD(7) (coord J11), J16[12]/P2_25-LCD_VD7
  @{ */
/* @} */

/*! @name LCD_VD(12) (coord F12), J16[17]/P2_30-LCD_VD12
  @{ */
/* @} */

/*! @name LCD_VD(10) (coord G13), J16[15]/P2_28-LCD_VD10
  @{ */
/* @} */

/*! @name LCD_VD(13) (coord D14), J16[18]/P2_31-LCD_VD13
  @{ */
/* @} */

/*! @name LCD_VD(6) (coord K14), J16[11]/P2_24-LCD_VD6
  @{ */
/* @} */

/*! @name LCD_VD(5) (coord M14), J16[10]/P2_23-LCD_VD5
  @{ */
/* @} */

/*! @name LCD_VD(14) (coord D12), J16[19]/JS36[1]/P3_0-LCD_VD14
  @{ */
/* @} */

/*! @name LCD_VD(15) (coord D11), J16[20]/JS33[1]/P3_1-LCD_VD15
  @{ */
/* @} */

/*! @name LCD_VD(19) (coord B10), J16[24]/P3_5-LCD_VD19
  @{ */
/* @} */

/*! @name LCD_VD(20) (coord C9), J16[25]/P3_6-LCD_VD20
  @{ */
/* @} */

/*! @name LCD_VD(21) (coord B8), J16[26]/P3_7-LCD_VD21
  @{ */
/* @} */

/*! @name LCD_VD(22) (coord A7), J16[27]/P3_8-LCD_VD22
  @{ */
/* @} */

/*! @name LCD_VD(23) (coord C7), J16[28]/P3_9-LCD_VD23
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLCDPins(void); /* Function assigned for the Cortex-M4F */

#define PIO017_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO017_FUNC_ALT7 0x07u        /*!<@brief Selects pin function.: Alternative connection 7. */
#define PIO226_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO226_FUNC_ALT0 0x00u        /*!<@brief Selects pin function.: Alternative connection 0. */
#define PIO410_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO410_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO411_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO411_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO412_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO412_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO413_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO413_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO414_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO414_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO415_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO415_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO416_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO416_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO48_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO48_FUNC_ALT1 0x01u         /*!<@brief Selects pin function.: Alternative connection 1. */

/*! @name ENET_TXD0 (coord B14), U12[17]/JP11[1]/P4_8-ENET_TXD0
  @{ */
/* @} */

/*! @name ENET_TXD1 (coord E14), U12[18]/P0_17-ENET_TXD1
  @{ */
/* @} */

/*! @name ENET_TX_EN (coord B6), U12[16]/P4_13-ENET_TX_EN
  @{ */
/* @} */

/*! @name ENET_RXD0 (coord A9), U12[8]/JP12[1]/J3[4]/JP12[3]/P4_11-USB0_ID/P4_11-ENET_RXD0
  @{ */
/* @} */

/*! @name ENET_RXD1 (coord A6), U12[7]/P4_12-ENET_RXD1
  @{ */
/* @} */

/*! @name ENET_RX_DV (coord B9), U12[11]/P4_10-ENET_CRS_DV
  @{ */
/* @} */

/*! @name ENET_MDIO (coord C4), U12[12]/P4_16-ENET_MDIO
  @{ */
/* @} */

/*! @name ENET_MDC (coord A4), U12[13]/P4_15-ENET_MDC
  @{ */
/* @} */

/*! @name PIO2_26 (coord H11), U12[15]/P2_26-ENET_PHY_RSTn
  @{ */
#define BOARD_INITENETPINS_ENET_PHY_RSTn_GPIO GPIO /*!<@brief GPIO device name: GPIO */
#define BOARD_INITENETPINS_ENET_PHY_RSTn_PORT 2U   /*!<@brief PORT device name: 2U */
#define BOARD_INITENETPINS_ENET_PHY_RSTn_PIN 26U   /*!<@brief 2U pin index: 26 */
                                                   /* @} */

/*! @name ENET_RX_CLK (coord B5), JS18[2]/P4_14-ENET_RX_CLK
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitENETPins(void); /* Function assigned for the Cortex-M4F */

#define PIO12_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO12_FUNC_ALT5 0x05u        /*!<@brief Selects pin function.: Alternative connection 5. */
#define PIO13_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO13_FUNC_ALT5 0x05u        /*!<@brief Selects pin function.: Alternative connection 5. */

/*! @name PDM1_CLK (coord L14), J13[18]/JS25[3]/DMIC1[4]/P1_2-PDM1_CLK
  @{ */
/* @} */

/*! @name PDM1_DATA (coord J13), JS26[3]/DMIC1[1]/P1_3-PDM1_DATA
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitDMICPins(void); /* Function assigned for the Cortex-M4F */

#define PIO218_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO218_FUNC_ALT3 0x03u        /*!<@brief Selects pin function.: Alternative connection 3. */
#define PIO219_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO219_FUNC_ALT3 0x03u        /*!<@brief Selects pin function.: Alternative connection 3. */
#define PIO220_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO220_FUNC_ALT2 0x02u        /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO311_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO311_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO323_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO323_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO324_DIGIMODE_DIGITAL 0x01u /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO324_FUNC_ALT1 0x01u        /*!<@brief Selects pin function.: Alternative connection 1. */
#define PIO41_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO41_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO42_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO42_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */
#define PIO43_DIGIMODE_DIGITAL 0x01u  /*!<@brief Select Analog/Digital mode.: Digital mode. */
#define PIO43_FUNC_ALT2 0x02u         /*!<@brief Selects pin function.: Alternative connection 2. */

/*! @name FC6_SCK (coord G14), U10[29]/J9[14]/P4_1-FC6_I2S_TX_SCK
  @{ */
/* @} */

/*! @name FC6_TXD_SCL_MISO_WS (coord F13), U10[30]/J9[12]/P4_3-FC6_I2S_TX_WS
  @{ */
/* @} */

/*! @name FC6_RXD_SDA_MOSI_DATA (coord F14), U10[32]/J9[10]/P4_2-FC6_I2S_TX_DATA
  @{ */
/* @} */

/*! @name FC7_RXD_SDA_MOSI_DATA (coord P12), U10[31]/J9[20]/P2_19-FC7_I2S_RX_DAT
  @{ */
/* @} */

/*! @name FC7_SCK (coord N10), U10[29]/J9[16]/P2_18-FC7_I2S_RX_SCK
  @{ */
/* @} */

/*! @name FC3_RTS_SCL_SSEL1 (coord P13), U10[30]/J9[18]/P2_20-FC7_I2S_RX_WS
  @{ */
/* @} */

/*! @name MCLK (coord B2), J11[8]/J12[7]/P3_11-MCLK-PMOD2_GPIO
  @{ */
/* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitI2SPins(void); /* Function assigned for the Cortex-M4F */

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
