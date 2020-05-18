/*
 * Copyright 2018-2019 NXP.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v5.0
processor: MK22FN512xxx12
package_id: MK22FN512VLH12
mcu_data: ksdk2_0
processor_version: 0.0.18
board: FRDM-K22F
pin_labels:
- {pin_num: '22', pin_signal: PTA0/UART0_CTS_b/FTM0_CH5/JTAG_TCLK/SWD_CLK/EZP_CLK, label: 'J11[4]/SWD_CLK_TGTMCU'}
- {pin_num: '23', pin_signal: PTA1/UART0_RX/FTM0_CH6/JTAG_TDI/EZP_DI, label: 'J2[4]/RED_LED', identifier: LEDRGB_RED}
- {pin_num: '24', pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, label: 'J1[8]/GREEN_LED', identifier: LEDRGB_GREEN}
- {pin_num: '25', pin_signal: PTA3/UART0_RTS_b/FTM0_CH0/JTAG_TMS/SWD_DIO, label: 'J11[2]/SWD_DIO_TGTMCU'}
- {pin_num: '26', pin_signal: PTA4/LLWU_P3/FTM0_CH1/NMI_b/EZP_CS_b, label: 'J1[10]/LLWU_P3'}
- {pin_num: '27', pin_signal: PTA5/USB_CLKIN/FTM0_CH2/I2S0_TX_BCLK/JTAG_TRST_b, label: 'J1[1]/I2S0_TX_BCLK', identifier: AC_I2S_SCLK;USB_CLKIN}
- {pin_num: '28', pin_signal: PTA12/FTM1_CH0/I2S0_TXD0/FTM1_QD_PHA, label: 'J1[5]/I2S0_TXD0', identifier: AC_I2S_DIN}
- {pin_num: '29', pin_signal: PTA13/LLWU_P4/FTM1_CH1/I2S0_TX_FS/FTM1_QD_PHB, label: 'J1[3]', identifier: AC_I2S_LRCLK}
- {pin_num: '32', pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, label: 'Y1[3]/EXTAL', identifier: EXTAL0}
- {pin_num: '33', pin_signal: XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1, label: 'Y1[1]/XTAL', identifier: XTAL0}
- {pin_num: '35', pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA, label: 'J24[2]/LLWU_P5'}
- {pin_num: '36', pin_signal: ADC0_SE9/ADC1_SE9/PTB1/I2C0_SDA/FTM1_CH1/FTM1_QD_PHB, label: 'J24[4]'}
- {pin_num: '37', pin_signal: ADC0_SE12/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT3, label: 'J24[12]/U8[4]/ADC0_SE12/I2C0_SCL/AUD/ACCEL_I2C/POT_5K', identifier: ACCEL_SCL;AUDIO_SCL;POT_5K}
- {pin_num: '38', pin_signal: ADC0_SE13/PTB3/I2C0_SDA/UART0_CTS_b/FTM0_FLT0, label: 'J24[10]/U8[6]/ADC0_SE13/I2C0_SDA/AUD/ACCEL_I2C', identifier: ACCEL_SDA;AUDIO_SDA}
- {pin_num: '39', pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN, label: 'J1[6]/J8[G1]/SD_CARD_DETECT', identifier: SD_CARD_DETECT}
- {pin_num: '40', pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, label: PUSH_BUTTON1, identifier: SW3}
- {pin_num: '41', pin_signal: PTB18/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/FTM2_QD_PHA, label: 'J1[12]'}
- {pin_num: '42', pin_signal: PTB19/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB, label: 'J2[2]'}
- {pin_num: '43', pin_signal: ADC0_SE14/PTC0/SPI0_PCS4/PDB0_EXTRG/USB_SOF_OUT/FB_AD14, label: 'J2[5]/U13[3]'}
- {pin_num: '44', pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/I2S0_TXD0/LPUART0_RTS_b, label: 'J24[6]/LLWU_P6/ADC0_SE15/PUSH_BUTTON2',
  identifier: SW2}
- {pin_num: '45', pin_signal: ADC0_SE4b/CMP1_IN0/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/I2S0_TX_FS/LPUART0_CTS_b, label: 'J24[8]'}
- {pin_num: '51', pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/I2S0_MCLK, label: 'J1[16]/LLWU_P10'}
- {pin_num: '49', pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/FB_AD11/CMP1_OUT/LPUART0_TX, label: 'J8[P2]/J24[9]/uSD_card_CS', identifier: SD_CARD_DAT3}
- {pin_num: '50', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/FB_AD10/CMP0_OUT/FTM0_CH2, label: 'J1[15]/I2S0_RXD0', identifier: AC_I2S_DOUT}
- {pin_num: '52', pin_signal: CMP0_IN1/PTC7/SPI0_SIN/USB_SOF_OUT/I2S0_RX_FS/FB_AD8, label: 'J1[11]/I2S0_RX_FS'}
- {pin_num: '53', pin_signal: ADC1_SE4b/CMP0_IN2/PTC8/FTM3_CH4/I2S0_MCLK/FB_AD7, label: 'J1[7]/I2S0_MCLK', identifier: AC_SYS_MCLK}
- {pin_num: '54', pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/FTM2_FLT0, label: 'J1[9]/I2S0_RX_BCLK'}
- {pin_num: '55', pin_signal: ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5, label: 'J1[13]/I2C1_SCL/I2S0_RX_FS'}
- {pin_num: '56', pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/FB_RW_b, label: 'J2[7]/I2C1_SDA', identifier: RF_CE}
- {pin_num: '57', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b/LPUART0_RTS_b, label: 'U8[11]/LLWU_P12/ACCEL_INT1', identifier: ACCEL_INT1;RF_IRQ}
- {pin_num: '58', pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b/LPUART0_CTS_b, label: 'U8[9]/J8[P5]/SPI0_SCK/uSD_SPI_CL/ACCEL_INT2', identifier: SD_CARD_CLK;ACCEL_INT2}
- {pin_num: '59', pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/LPUART0_RX/I2C0_SCL, label: 'J1[2]/J8[P3]/uSD_SPI_MOSI', identifier: SD_CARD_CMD}
- {pin_num: '60', pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/LPUART0_TX/I2C0_SDA, label: 'J1[4]/J8[P7]/SPI0_SIN/uSD_SPI_MISO', identifier: SD_CARD_DAT0}
- {pin_num: '61', pin_signal: PTD4/LLWU_P14/SPI0_PCS1/UART0_RTS_b/FTM0_CH4/FB_AD2/EWM_IN/SPI1_PCS0, label: 'J2[6]/SPI0_PCS1/LLWU_P14', identifier: RF_CS}
- {pin_num: '62', pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/FTM0_CH5/FB_AD1/EWM_OUT_b/SPI1_SCK, label: 'J2[12]/BLUE_LED', identifier: LEDRGB_BLUE}
- {pin_num: '63', pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT, label: 'J2[8]'}
- {pin_num: '64', pin_signal: PTD7/UART0_TX/FTM0_CH7/FTM0_FLT1/SPI1_SIN, label: 'J2[10]'}
- {pin_num: '1', pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA/RTC_CLKOUT, label: 'J2[18]/UART1_TX_TGTMCU', identifier: DEBUG_UART_TX;RTC_CLKOUT;CLKOUT32K}
- {pin_num: '2', pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN, label: 'J2[20]/UART1_RX_TGTMCU', identifier: DEBUG_UART_RX}
- {pin_num: '4', pin_signal: VSS4, label: GND}
- {pin_num: '31', pin_signal: VSS31, label: GND}
- {pin_num: '47', pin_signal: VSS47, label: GND}
- {pin_num: '16', pin_signal: VSSA, label: VSSA}
- {pin_num: '15', pin_signal: VREFL, label: VREFL}
- {pin_num: '14', pin_signal: VREFH, label: 'J2[16]/VREFH'}
- {pin_num: '19', pin_signal: XTAL32, label: XTAL32_RTC, identifier: XTAL32}
- {pin_num: '20', pin_signal: EXTAL32, label: EXTAL32_RTC, identifier: EXTAL32}
- {pin_num: '11', pin_signal: ADC1_DP0/ADC0_DP3, label: 'J24[5]/ADC0_DP3/ADC0_SE3/LIGHT_SNSR', identifier: LSENSE_EMITTER}
- {pin_num: '18', pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23, label: 'J24[11]/DAC0_OUT/ADC0_SE23'}
- {pin_num: '12', pin_signal: ADC1_DM0/ADC0_DM3, label: 'J24[7]/ADC0_DM3/ADC0_SE7a'}
- {pin_num: '10', pin_signal: ADC0_DM0/ADC1_DM3, label: 'J24[3]/ADC0_DM0/ADC0_SE4a'}
- {pin_num: '9', pin_signal: ADC0_DP0/ADC1_DP3, label: 'J24[1]/ADC0_DP0/ADC0_SE0'}
- {pin_num: '17', pin_signal: VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18, label: 'J2[1]'}
- {pin_num: '21', pin_signal: VBAT, label: VBAT}
- {pin_num: '13', pin_signal: VDDA, label: P3V3_K22F}
- {pin_num: '30', pin_signal: VDD30, label: P3V3_K22F}
- {pin_num: '3', pin_signal: VDD3, label: P3V3_K22F}
- {pin_num: '48', pin_signal: VDD48, label: P3V3_K22F}
- {pin_num: '7', pin_signal: VOUT33, label: USB_VOUT33, identifier: USB_VOUT33}
- {pin_num: '5', pin_signal: USB0_DP, label: USB_DP, identifier: USB_DP}
- {pin_num: '6', pin_signal: USB0_DM, label: USB_DN, identifier: USB_DN}
- {pin_num: '34', pin_signal: RESET_b, label: 'J11[10]/RST_TGTMCU_b'}
- {pin_num: '8', pin_signal: VREGIN, label: P5V_K22F, identifier: USB_VREGIN}
- {pin_num: '46', pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/I2S0_TX_BCLK/LPUART0_RX, label: 'J1[14]', identifier: CLKOUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    BOARD_InitDEBUG_UARTPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '24', peripheral: TPIU, signal: SWO, pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, identifier: '', pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA2 (pin 24) is configured as TRACE_SWO */
    PORT_SetPinMux(PORTA, 2U, kPORT_MuxAlt7);

    PORTA->PCR[2] = ((PORTA->PCR[2] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                      * corresponding PE field is set. */
                     | PORT_PCR_PS(kPORT_PullDown)

                     /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
                     | PORT_PCR_PE(kPORT_PullDisable));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '23', peripheral: GPIOA, signal: 'GPIO, 1', pin_signal: PTA1/UART0_RX/FTM0_CH6/JTAG_TDI/EZP_DI, direction: OUTPUT, gpio_init_state: 'true', slew_rate: slow,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: '24', peripheral: GPIOA, signal: 'GPIO, 2', pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: slow, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: '62', peripheral: GPIOD, signal: 'GPIO, 5', pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/FTM0_CH5/FB_AD1/EWM_OUT_b/SPI1_SCK, direction: OUTPUT,
    gpio_init_state: 'true', slew_rate: slow, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLEDsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t LEDRGB_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTA1 (pin 23)  */
    GPIO_PinInit(BOARD_LEDRGB_RED_GPIO, BOARD_LEDRGB_RED_PIN, &LEDRGB_RED_config);

    gpio_pin_config_t LEDRGB_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTA2 (pin 24)  */
    GPIO_PinInit(BOARD_LEDRGB_GREEN_GPIO, BOARD_LEDRGB_GREEN_PIN, &LEDRGB_GREEN_config);

    gpio_pin_config_t LEDRGB_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTD5 (pin 62)  */
    GPIO_PinInit(BOARD_LEDRGB_BLUE_GPIO, BOARD_LEDRGB_BLUE_PIN, &LEDRGB_BLUE_config);

    const port_pin_config_t LEDRGB_RED = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Slow slew rate is configured */
                                          kPORT_SlowSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTA1 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTA1 (pin 23) is configured as PTA1 */
    PORT_SetPinConfig(BOARD_LEDRGB_RED_PORT, BOARD_LEDRGB_RED_PIN, &LEDRGB_RED);

    const port_pin_config_t LEDRGB_GREEN = {/* Internal pull-up/down resistor is disabled */
                                            kPORT_PullDisable,
                                            /* Slow slew rate is configured */
                                            kPORT_SlowSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as PTA2 */
                                            kPORT_MuxAsGpio,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTA2 (pin 24) is configured as PTA2 */
    PORT_SetPinConfig(BOARD_LEDRGB_GREEN_PORT, BOARD_LEDRGB_GREEN_PIN, &LEDRGB_GREEN);

    const port_pin_config_t LEDRGB_BLUE = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Slow slew rate is configured */
                                           kPORT_SlowSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as PTD5 */
                                           kPORT_MuxAsGpio,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTD5 (pin 62) is configured as PTD5 */
    PORT_SetPinConfig(BOARD_LEDRGB_BLUE_PORT, BOARD_LEDRGB_BLUE_PIN, &LEDRGB_BLUE);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitButtonsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '40', peripheral: GPIOB, signal: 'GPIO, 17', pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable}
  - {pin_num: '44', peripheral: GPIOC, signal: 'GPIO, 1', pin_signal: ADC0_SE15/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/I2S0_TXD0/LPUART0_RTS_b, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitButtonsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitButtonsPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB17 (pin 40)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC1 (pin 44)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

    const port_pin_config_t SW3 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTB17 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTB17 (pin 40) is configured as PTB17 */
    PORT_SetPinConfig(BOARD_SW3_PORT, BOARD_SW3_PIN, &SW3);

    const port_pin_config_t SW2 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTC1 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTC1 (pin 44) is configured as PTC1 */
    PORT_SetPinConfig(BOARD_SW2_PORT, BOARD_SW2_PIN, &SW2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '2', peripheral: UART1, signal: RX, pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: '1', peripheral: UART1, signal: TX, pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA/RTC_CLKOUT, identifier: DEBUG_UART_TX, direction: OUTPUT,
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitDEBUG_UARTPins(void)
{
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    const port_pin_config_t DEBUG_UART_TX = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Fast slew rate is configured */
                                             kPORT_FastSlewRate,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Open drain is disabled */
                                             kPORT_OpenDrainDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as UART1_TX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTE0 (pin 1) is configured as UART1_TX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, &DEBUG_UART_TX);

    const port_pin_config_t DEBUG_UART_RX = {/* Internal pull-up/down resistor is disabled */
                                             kPORT_PullDisable,
                                             /* Fast slew rate is configured */
                                             kPORT_FastSlewRate,
                                             /* Passive filter is disabled */
                                             kPORT_PassiveFilterDisable,
                                             /* Open drain is disabled */
                                             kPORT_OpenDrainDisable,
                                             /* Low drive strength is configured */
                                             kPORT_LowDriveStrength,
                                             /* Pin is configured as UART1_RX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTE1 (pin 2) is configured as UART1_RX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, &DEBUG_UART_RX);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART1TXSRC_MASK)))

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitAccelPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '37', peripheral: I2C0, signal: SCL, pin_signal: ADC0_SE12/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT3, identifier: ACCEL_SCL, slew_rate: fast, open_drain: enable,
    pull_select: up, pull_enable: enable}
  - {pin_num: '38', peripheral: I2C0, signal: SDA, pin_signal: ADC0_SE13/PTB3/I2C0_SDA/UART0_CTS_b/FTM0_FLT0, identifier: ACCEL_SDA, slew_rate: fast, open_drain: enable,
    pull_select: up, pull_enable: enable}
  - {pin_num: '57', peripheral: GPIOD, signal: 'GPIO, 0', pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b/LPUART0_RTS_b, identifier: ACCEL_INT1,
    direction: INPUT, slew_rate: fast, open_drain: enable, pull_select: down, pull_enable: disable}
  - {pin_num: '58', peripheral: GPIOD, signal: 'GPIO, 1', pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b/LPUART0_CTS_b, identifier: ACCEL_INT2,
    direction: INPUT, slew_rate: fast, open_drain: enable, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitAccelPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitAccelPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t ACCEL_INT1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD0 (pin 57)  */
    GPIO_PinInit(BOARD_ACCEL_INT1_GPIO, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1_config);

    gpio_pin_config_t ACCEL_INT2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD1 (pin 58)  */
    GPIO_PinInit(BOARD_ACCEL_INT2_GPIO, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2_config);

    const port_pin_config_t ACCEL_SCL = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as I2C0_SCL */
                                         kPORT_MuxAlt2,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB2 (pin 37) is configured as I2C0_SCL */
    PORT_SetPinConfig(BOARD_ACCEL_SCL_PORT, BOARD_ACCEL_SCL_PIN, &ACCEL_SCL);

    const port_pin_config_t ACCEL_SDA = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as I2C0_SDA */
                                         kPORT_MuxAlt2,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB3 (pin 38) is configured as I2C0_SDA */
    PORT_SetPinConfig(BOARD_ACCEL_SDA_PORT, BOARD_ACCEL_SDA_PIN, &ACCEL_SDA);

    const port_pin_config_t ACCEL_INT1 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is enabled */
                                          kPORT_OpenDrainEnable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTD0 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTD0 (pin 57) is configured as PTD0 */
    PORT_SetPinConfig(BOARD_ACCEL_INT1_PORT, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1);

    const port_pin_config_t ACCEL_INT2 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is enabled */
                                          kPORT_OpenDrainEnable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTD1 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTD1 (pin 58) is configured as PTD1 */
    PORT_SetPinConfig(BOARD_ACCEL_INT2_PORT, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDHCPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '49', peripheral: SPI0, signal: PCS0_SS, pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/FB_AD11/CMP1_OUT/LPUART0_TX, direction: INPUT, slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: '58', peripheral: SPI0, signal: SCK, pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b/LPUART0_CTS_b, identifier: SD_CARD_CLK, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: '59', peripheral: SPI0, signal: SOUT, pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/LPUART0_RX/I2C0_SCL, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: '60', peripheral: SPI0, signal: SIN, pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/LPUART0_TX/I2C0_SDA, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: '39', peripheral: GPIOB, signal: 'GPIO, 16', pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN, direction: INPUT, slew_rate: slow, open_drain: disable,
    pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSDHCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitSDHCPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t SD_CARD_DETECT_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB16 (pin 39)  */
    GPIO_PinInit(BOARD_SD_CARD_DETECT_GPIO, BOARD_SD_CARD_DETECT_PIN, &SD_CARD_DETECT_config);

    const port_pin_config_t SD_CARD_DETECT = {/* Internal pull-up resistor is enabled */
                                              kPORT_PullUp,
                                              /* Slow slew rate is configured */
                                              kPORT_SlowSlewRate,
                                              /* Passive filter is disabled */
                                              kPORT_PassiveFilterDisable,
                                              /* Open drain is disabled */
                                              kPORT_OpenDrainDisable,
                                              /* Low drive strength is configured */
                                              kPORT_LowDriveStrength,
                                              /* Pin is configured as PTB16 */
                                              kPORT_MuxAsGpio,
                                              /* Pin Control Register fields [15:0] are not locked */
                                              kPORT_UnlockRegister};
    /* PORTB16 (pin 39) is configured as PTB16 */
    PORT_SetPinConfig(BOARD_SD_CARD_DETECT_PORT, BOARD_SD_CARD_DETECT_PIN, &SD_CARD_DETECT);

    const port_pin_config_t SD_CARD_DAT3 = {/* Internal pull-up/down resistor is disabled */
                                            kPORT_PullDisable,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as SPI0_PCS0 */
                                            kPORT_MuxAlt2,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTC4 (pin 49) is configured as SPI0_PCS0 */
    PORT_SetPinConfig(BOARD_SD_CARD_DAT3_PORT, BOARD_SD_CARD_DAT3_PIN, &SD_CARD_DAT3);

    const port_pin_config_t SD_CARD_CLK = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as SPI0_SCK */
                                           kPORT_MuxAlt2,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTD1 (pin 58) is configured as SPI0_SCK */
    PORT_SetPinConfig(BOARD_SD_CARD_CLK_PORT, BOARD_SD_CARD_CLK_PIN, &SD_CARD_CLK);

    const port_pin_config_t SD_CARD_CMD = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as SPI0_SOUT */
                                           kPORT_MuxAlt2,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTD2 (pin 59) is configured as SPI0_SOUT */
    PORT_SetPinConfig(BOARD_SD_CARD_CMD_PORT, BOARD_SD_CARD_CMD_PIN, &SD_CARD_CMD);

    const port_pin_config_t SD_CARD_DAT0 = {/* Internal pull-up/down resistor is disabled */
                                            kPORT_PullDisable,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as SPI0_SIN */
                                            kPORT_MuxAlt2,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTD3 (pin 60) is configured as SPI0_SIN */
    PORT_SetPinConfig(BOARD_SD_CARD_DAT0_PORT, BOARD_SD_CARD_DAT0_PIN, &SD_CARD_DAT0);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSCPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '32', peripheral: OSC, signal: EXTAL0, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0, slew_rate: no_init, open_drain: no_init, pull_select: no_init,
    pull_enable: no_init}
  - {pin_num: '33', peripheral: OSC, signal: XTAL0, pin_signal: XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1, slew_rate: no_init, open_drain: no_init, pull_select: no_init,
    pull_enable: no_init}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitOSCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitOSCPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA18 (pin 32) is configured as EXTAL0 */
    PORT_SetPinMux(BOARD_EXTAL0_PORT, BOARD_EXTAL0_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTA19 (pin 33) is configured as XTAL0 */
    PORT_SetPinMux(BOARD_XTAL0_PORT, BOARD_XTAL0_PIN, kPORT_PinDisabledOrAnalog);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPOTPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '37', peripheral: ADC0, signal: 'SE, 12', pin_signal: ADC0_SE12/PTB2/I2C0_SCL/UART0_RTS_b/FTM0_FLT3, identifier: POT_5K, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPOTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPOTPins(void)
{
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    const port_pin_config_t POT_5K = {/* Internal pull-up/down resistor is disabled */
                                      kPORT_PullDisable,
                                      /* Fast slew rate is configured */
                                      kPORT_FastSlewRate,
                                      /* Passive filter is disabled */
                                      kPORT_PassiveFilterDisable,
                                      /* Open drain is disabled */
                                      kPORT_OpenDrainDisable,
                                      /* Low drive strength is configured */
                                      kPORT_LowDriveStrength,
                                      /* Pin is configured as ADC0_SE12 */
                                      kPORT_PinDisabledOrAnalog,
                                      /* Pin Control Register fields [15:0] are not locked */
                                      kPORT_UnlockRegister};
    /* PORTB2 (pin 37) is configured as ADC0_SE12 */
    PORT_SetPinConfig(BOARD_POT_5K_PORT, BOARD_POT_5K_PIN, &POT_5K);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLSENSEPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '11', peripheral: ADC0, signal: 'SE, 3', pin_signal: ADC1_DP0/ADC0_DP3}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLSENSEPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitLSENSEPins(void)
{
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
