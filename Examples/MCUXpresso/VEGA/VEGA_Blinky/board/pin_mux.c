/*
 * Copyright 2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: RV32M1
package_id: RV32M1
mcu_data: ksdk2_0
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
    BOARD_InitPins();
}

#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN23_IDX                       23u   /*!< Pin number for pin 23 in a port */
#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: N2, peripheral: LPUART0, signal: RX, pin_signal: LPCMP0_IN0/PTC7/LLWU_P15/LPSPI0_PCS3/LPUART0_RX/LPI2C1_HREQ/TPM0_CH0/LPTMR1_ALT1}
  - {pin_num: P3, peripheral: LPUART0, signal: TX, pin_signal: LPCMP0_IN1/PTC8/LPSPI0_SCK/LPUART0_TX/LPI2C0_HREQ/TPM0_CH1}
  - {pin_num: D6, peripheral: TPM2, signal: 'CH, 0', pin_signal: PTA24/LPSPI2_PCS0/LPSPI1_SCK/LPI2C2_SCL/FB_OE_b/TPM2_CH0}
  - {pin_num: E6, peripheral: TPM2, signal: 'CH, 1', pin_signal: PTA23/LPSPI2_SIN/LPSPI1_PCS3/LPI2C2_SDA/FB_AD15/TPM2_CH1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTA, PIN23_IDX, kPORT_MuxAlt6);           /* PORTA23 (pin E6) is configured as TPM2_CH1 */
  PORT_SetPinMux(PORTA, PIN24_IDX, kPORT_MuxAlt6);           /* PORTA24 (pin D6) is configured as TPM2_CH0 */
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt3);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt3);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
}


#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_I2C_ConfigurePins:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: G15, peripheral: LPI2C3, signal: SDA, pin_signal: PTE29/LPUART3_RX/LPI2C3_SDA/FXIO0_D30, slew_rate: fast, open_drain: enable, pull_select: up, pull_enable: enable}
  - {pin_num: G17, peripheral: LPI2C3, signal: SCL, pin_signal: PTE30/LPUART3_TX/LPI2C3_SCL/TPM2_CLKIN/FXIO0_D31, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_I2C_ConfigurePins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_I2C_ConfigurePins(void) {
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Clock Gate Control: 0x01u */

  const port_pin_config_t porte29_pinG15_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainEnable,                                   /* Open drain is enabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C3_SDA */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN29_IDX, &porte29_pinG15_config); /* PORTE29 (pin G15) is configured as LPI2C3_SDA */
  const port_pin_config_t porte30_pinG17_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainEnable,                                   /* Open drain is enabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C3_SCL */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN30_IDX, &porte30_pinG17_config); /* PORTE30 (pin G17) is configured as LPI2C3_SCL */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
