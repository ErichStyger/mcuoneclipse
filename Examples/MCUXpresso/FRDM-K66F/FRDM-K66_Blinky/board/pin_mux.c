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
processor: MK66FN2M0xxx18
package_id: MK66FN2M0VMD18
mcu_data: ksdk2_0
processor_version: 0.0.19
board: FRDM-K66F
pin_labels:
- {pin_num: A1, pin_signal: PTD7/CMT_IRO/UART0_TX/FTM0_CH7/SDRAM_CKE/FTM0_FLT1/SPI1_SIN, label: 'J6[7]/SPI1_SIN/MISO'}
- {pin_num: B1, pin_signal: PTD12/SPI2_SCK/FTM3_FLT0/SDHC0_D4/FB_A20, label: 'J2[19]/FB_A20', identifier: FB_A20}
- {pin_num: C1, pin_signal: PTD15/SPI2_PCS1/SDHC0_D7/FB_A23, label: NC}
- {pin_num: D1, pin_signal: ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/TRACE_D2, label: SDHC0_DCLK, identifier: SDHC0_DCLK}
- {pin_num: E1, pin_signal: PTE6/LLWU_P16/SPI1_PCS3/UART3_CTS_b/I2S0_MCLK/FTM3_CH1/USB0_SOF_OUT, label: LEDRGB_GREEN, identifier: LED_GREEN}
- {pin_num: F1, pin_signal: PTE10/LLWU_P18/I2C3_SDA/I2S0_TXD0/LPUART0_CTS_b/FTM3_CH5/USB1_ID, label: USB_ID, identifier: USB_ID}
- {pin_num: G1, pin_signal: VREG_OUT, label: C81, identifier: C81}
- {pin_num: J1, pin_signal: USB1_DP/LLWU_P30, label: K66_MICRO_USB_DP, identifier: K66_MICRO_USB_DP_DCD;K66_MICRO_USB_DP_PHY}
- {pin_num: H1, pin_signal: USB0_DP, label: NC}
- {pin_num: K1, pin_signal: USB1_DM/LLWU_P31, label: K66_MICRO_USB_DN, identifier: K66_MICRO_USB_DN_DCD;K66_MICRO_USB_DN_PHY}
- {pin_num: L1, pin_signal: USB1_VBUS/LLWU_P29, label: P5V_K66_USB, identifier: P5V_K66_USB}
- {pin_num: M1, pin_signal: ADC1_DP0/ADC0_DP3, label: 'J4[1]/DIFF_ADC1_DP0', identifier: DIFF_ADC1_DP0}
- {pin_num: A2, pin_signal: ADC0_SE7b/PTD6/LLWU_P15/SPI0_PCS3/UART0_RX/FTM0_CH6/FB_AD0/FTM0_FLT0/SPI1_SOUT, label: 'J6[6]/SPI1_SOUT/MOSI'}
- {pin_num: B2, pin_signal: PTD11/LLWU_P25/SPI2_PCS0/SDHC0_CLKIN/LPUART0_CTS_b/FB_A19, label: SW2, identifier: SW2}
- {pin_num: C2, pin_signal: PTD14/SPI2_SIN/SDHC0_D6/FB_A22, label: NC}
- {pin_num: D2, pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/TRACE_D3/I2C1_SCL/SPI1_SIN, label: SDHC0_D0, identifier: SDHC0_D0}
- {pin_num: E2, pin_signal: PTE5/SPI1_PCS2/UART3_RX/SDHC0_D2/FTM3_CH0, label: SDHC0_D2, identifier: SDHC0_D2}
- {pin_num: F2, pin_signal: PTE9/LLWU_P17/I2S0_TXD1/I2S0_RX_BCLK/LPUART0_RX/FTM3_CH4, label: 'J30[3]/U22[3]/I2S_RX_BCLK', identifier: I2S_RX_BCLK}
- {pin_num: G2, pin_signal: VREG_IN0, label: VREGIN_K66}
- {pin_num: J2, pin_signal: VREG_IN1, label: VREGIN_K66}
- {pin_num: H2, pin_signal: USB0_DM, label: NC}
- {pin_num: K2, pin_signal: USB1_VSS, label: GND}
- {pin_num: L2, pin_signal: ADC0_DM0/ADC1_DM3, label: 'J2[3]/ADC0_DM0_RC', identifier: ADC0_DM0_RC}
- {pin_num: M2, pin_signal: ADC1_DM0/ADC0_DM3, label: 'J4[3]/DIFF_ADC1_DM0', identifier: DIFF_ADC1_DM0}
- {pin_num: A3, pin_signal: ADC0_SE6b/PTD5/SPI0_PCS2/UART0_CTS_b/UART0_COL_b/FTM0_CH5/FB_AD1/SDRAM_A9/EWM_OUT_b/SPI1_SCK, label: 'J6[7]/SPI1_SCK/SCK'}
- {pin_num: B3, pin_signal: PTD10/LPUART0_RTS_b/FB_A18, label: SD_CARD_DETECT, identifier: SDCARD_CARD_DETECTION}
- {pin_num: C3, pin_signal: PTD13/SPI2_SOUT/SDHC0_D5/FB_A21, label: 'J2[17]/FB_A21', identifier: FB_A21}
- {pin_num: D3, pin_signal: ADC1_SE4a/PTE0/SPI1_PCS1/UART1_TX/SDHC0_D1/TRACE_CLKOUT/I2C1_SDA/RTC_CLKOUT, label: SDHC0_D1, identifier: SDHC0_D1}
- {pin_num: E3, pin_signal: PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/SDHC0_D3/TRACE_D0, label: SDHC0_D3, identifier: SDHC0_D3}
- {pin_num: F3, pin_signal: PTE8/I2S0_RXD1/I2S0_RX_FS/LPUART0_TX/FTM3_CH3, label: 'J1[13]/J34[3]/J38[1]/I2S_RX_WCLK/I2S_RXD1', identifier: I2S_RX_WCLK_RXD1}
- {pin_num: G3, pin_signal: PTE12/I2S0_TX_BCLK/FTM3_CH7, label: 'J1[1]/J37[3]/I2S_TX_BCLK', identifier: I2S_TX_BCLK}
- {pin_num: H3, pin_signal: VSS6, label: GND}
- {pin_num: J3, pin_signal: ADC0_SE16/CMP1_IN2/ADC0_SE21, label: 'J4[5]/ADC0', identifier: ADC0_SE16}
- {pin_num: K3, pin_signal: ADC1_SE16/CMP2_IN2/ADC0_SE22, label: 'J4[7]/ADC1', identifier: ADC1_SE16}
- {pin_num: L3, pin_signal: DAC0_OUT/CMP1_IN3/ADC0_SE23, label: 'J4[11]/DAC_OUT', identifier: DAC0_OUT}
- {pin_num: M3, pin_signal: VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18, label: 'J2[1]/ADC1_SE18_RC', identifier: ADC1_SE18_RC}
- {pin_num: A4, pin_signal: PTD4/LLWU_P14/SPI0_PCS1/UART0_RTS_b/FTM0_CH4/FB_AD2/SDRAM_A10/EWM_IN/SPI1_PCS0, label: 'J6[4]/SPI1_PCS0/CS'}
- {pin_num: B4, pin_signal: PTD3/SPI0_SIN/UART2_TX/FTM3_CH3/FB_AD3/SDRAM_A11/I2C0_SDA, label: 'J2[10]/SPI0_SIN/FB_AD3', identifier: SPI0_SIN}
- {pin_num: C4, pin_signal: PTD2/LLWU_P13/SPI0_SOUT/UART2_RX/FTM3_CH2/FB_AD4/SDRAM_A12/I2C0_SCL, label: 'J2[8]/SPI0_SOUT/FB_AD4', identifier: SPI0_SOUT}
- {pin_num: D4, pin_signal: ADC0_SE5b/PTD1/SPI0_SCK/UART2_CTS_b/FTM3_CH1/FB_CS0_b, label: 'J2[12]/SPI0_SCK/FB_CS0_B', identifier: SPI0_SCK}
- {pin_num: E4, pin_signal: ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/TRACE_D1/SPI1_SOUT, label: SDHC0_CMD, identifier: SDHC0_CMD}
- {pin_num: F4, pin_signal: PTE7/UART3_RTS_b/I2S0_RXD0/FTM3_CH2, label: 'J1[15]/J34[1]/U20[C7]/I2S_RXD0', identifier: I2S_RXD0}
- {pin_num: G4, pin_signal: PTE11/I2C3_SCL/I2S0_TX_FS/LPUART0_RTS_b/FTM3_CH6, label: 'J1[3]/J38[3]/I2S_TX_WCLK', identifier: I2S_TX_WCLK}
- {pin_num: H4, pin_signal: PTE28, label: 'J14[1]/ETHERNET_RST/PET_1_RST_B'}
- {pin_num: J4, pin_signal: PTE27/UART4_RTS_b, label: NC}
- {pin_num: K4, pin_signal: PTE26/ENET_1588_CLKIN/UART4_CTS_b/RTC_CLKOUT/USB0_CLKIN, label: 'U13[16]/ETHERNET_CLOCK', identifier: ETHERNET_CLOCK;ENET_1588_CLKIN}
- {pin_num: L4, pin_signal: DAC1_OUT/CMP0_IN4/CMP2_IN3/ADC1_SE23, label: 'J2[5]/ADC1_SE23_RC', identifier: ADC1_SE23_RC}
- {pin_num: M4, pin_signal: ADC0_SE17/PTE24/CAN1_TX/UART4_TX/I2C0_SCL/EWM_OUT_b, label: 'J2[13]/ADC0_SE17', identifier: ADC0_SE17}
- {pin_num: A5, pin_signal: PTD0/LLWU_P12/SPI0_PCS0/UART2_RTS_b/FTM3_CH0/FB_ALE/FB_CS1_b/FB_TS_b, label: 'J2[6]/SPI0_PCS0/FTM3_CH0', identifier: SPI0_PCS0}
- {pin_num: C5, pin_signal: PTC18/UART3_RTS_b/ENET0_1588_TMR2/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b/SDRAM_DQM1, label: 'J6[8]/RF_WIFI_IRQ'}
- {pin_num: B5, pin_signal: PTC19/UART3_CTS_b/ENET0_1588_TMR3/FB_CS3_b/FB_BE7_0_BLS31_24_b/SDRAM_DQM0/FB_TA_b, label: NC}
- {pin_num: D5, pin_signal: PTC17/CAN1_TX/UART3_TX/ENET0_1588_TMR1/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b/SDRAM_DQM3, label: 'U8[11]/FXOS8700CQ_INT1', identifier: ACCEL_INT1}
- {pin_num: E5, pin_signal: VDD5, label: P3V3_K66F}
- {pin_num: F5, pin_signal: VDD126, label: P3V3_K66F}
- {pin_num: G5, pin_signal: VREFH, label: VREFH}
- {pin_num: H5, pin_signal: VDDA, label: P3V3_K66F}
- {pin_num: J5, pin_signal: TSI0_CH1/PTA0/UART0_CTS_b/UART0_COL_b/FTM0_CH5/LPUART0_CTS_b/JTAG_TCLK/SWD_CLK/EZP_CLK, label: 'J8[2]/J9[4]/JTAG_TCLK/SWD_CLK/EZP_CLK',
  identifier: SWD_CLK}
- {pin_num: K5, pin_signal: ADC0_SE18/PTE25/LLWU_P21/CAN1_RX/UART4_RX/I2C0_SDA/EWM_IN, label: 'J2[15]/ADC0_SE18', identifier: ADC0_SE18}
- {pin_num: L5, pin_signal: RTC_WAKEUP_B, label: RTC_WAKEUP/TP18}
- {pin_num: M5, pin_signal: NC184, label: NC}
- {pin_num: A6, pin_signal: PTC16/CAN1_RX/UART3_RX/ENET0_1588_TMR0/FB_CS5_b/FB_TSIZ1/FB_BE23_16_BLS15_8_b/SDRAM_DQM2, label: 'J1[6]/ENET0_1588_TMR0', identifier: ENET0_1588_TMR0}
- {pin_num: B6, pin_signal: PTC15/UART4_TX/FB_AD24/SDRAM_D24, label: 'J199[4]/K66F_UART4_TX', identifier: K66F_UART4_TX}
- {pin_num: C6, pin_signal: PTC14/UART4_RX/FB_AD25/SDRAM_D25, label: 'J199[3]/K66F_UART4_RX', identifier: K66F_UART4_RX}
- {pin_num: D6, pin_signal: PTC13/UART4_CTS_b/FTM_CLKIN1/FB_AD26/SDRAM_D26/TPM_CLKIN1, label: 'U8[9]/FXOS8700CQ_INT2', identifier: ACCEL_INT2}
- {pin_num: E6, pin_signal: VDD16, label: P3V3_K66F}
- {pin_num: F6, pin_signal: VSS22, label: GND}
- {pin_num: G6, pin_signal: VREFL, label: GND}
- {pin_num: H6, pin_signal: VSSA, label: GND}
- {pin_num: J6, pin_signal: TSI0_CH2/PTA1/UART0_RX/FTM0_CH6/I2C3_SDA/LPUART0_RX/JTAG_TDI/EZP_DI, label: 'J3[15]/FTM0_CH6', identifier: FTM0_CH6}
- {pin_num: K6, pin_signal: TSI0_CH3/PTA2/UART0_TX/FTM0_CH7/I2C3_SCL/LPUART0_TX/JTAG_TDO/TRACE_SWO/EZP_DO, label: 'J9[6]/JTAG_TDO/TRACE_SWO/EZP_DO', identifier: TRACE_SWO}
- {pin_num: L6, pin_signal: VBAT, label: VBAT}
- {pin_num: M6, pin_signal: EXTAL32, label: 'Y3[2]', identifier: EXTAL32K}
- {pin_num: A7, pin_signal: PTC12/UART4_RTS_b/FTM_CLKIN0/FB_AD27/SDRAM_D27/FTM3_FLT0/TPM_CLKIN0, label: 'J1[10]/FB_AD27', identifier: FB_AD27}
- {pin_num: B7, pin_signal: ADC1_SE7b/PTC11/LLWU_P11/I2C1_SDA/FTM3_CH7/I2S0_RXD1/FB_RW_b, label: 'J2[18]/U20[C9]/I2C1_SDA/DA7212_SDA', identifier: I2C1_SDA}
- {pin_num: C7, pin_signal: ADC1_SE6b/PTC10/I2C1_SCL/FTM3_CH6/I2S0_RX_FS/FB_AD5/SDRAM_A13, label: 'J2[20]/U20[D8]/I2C1_SCL/DA7212_CLK', identifier: I2C1_SCL}
- {pin_num: D7, pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/SDRAM_A14/FTM2_FLT0, label: LEDRGB_RED, identifier: LED_RED}
- {pin_num: E7, pin_signal: VDD80, label: P3V3_K66F}
- {pin_num: F7, pin_signal: VSS17, label: GND}
- {pin_num: G7, pin_signal: VSS81, label: GND}
- {pin_num: H7, pin_signal: VSS125, label: GND}
- {pin_num: J7, pin_signal: PTA6/FTM0_CH3/CLKOUT/TRACE_CLKOUT, label: 'J3[7]/CLKOUT', identifier: CLKOUT}
- {pin_num: K7, pin_signal: TSI0_CH4/PTA3/UART0_RTS_b/FTM0_CH0/LPUART0_RTS_b/JTAG_TMS/SWD_DIO, label: 'J9[2]/J12[2]/JTAG_TMS/SWD_DIO', identifier: SWD_DIO}
- {pin_num: L7, pin_signal: TSI0_CH5/PTA4/LLWU_P3/FTM0_CH1/NMI_b/EZP_CS_b, label: 'J3[5]/LLWU_P3/FTM0_CH1/NMI', identifier: NMI}
- {pin_num: M7, pin_signal: XTAL32, label: 'Y3[1]', identifier: XTAL32K}
- {pin_num: A8, pin_signal: ADC1_SE4b/CMP0_IN2/PTC8/FTM3_CH4/I2S0_MCLK/FB_AD7/SDRAM_A15, label: 'J1[8]/FTM3_CH4/ADC1_SE4b', identifier: FTM3_CH4}
- {pin_num: B8, pin_signal: CMP0_IN1/PTC7/SPI0_SIN/USB0_SOF_OUT/I2S0_RX_FS/FB_AD8/SDRAM_A16, label: 'J1[11]/USB0_SOF_OUT/I2S0_RX_FS/FB_AD8', identifier: USB_SOF_OUT}
- {pin_num: C8, pin_signal: CMP0_IN0/PTC6/LLWU_P10/SPI0_SOUT/PDB0_EXTRG/I2S0_RX_BCLK/FB_AD9/SDRAM_A17/I2S0_MCLK, label: 'J1[9]/LLWU_P10/FB_AD9/I2S0_MCLK', identifier: I2S_MCLK}
- {pin_num: D8, pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/I2S0_RXD0/FB_AD10/SDRAM_A18/CMP0_OUT/FTM0_CH2, label: 'J1[12]/I2S0_RXD0/FB_AD10/FTM0_CH2', identifier: FB_AD10}
- {pin_num: E8, pin_signal: VDD94, label: P3V3_K66F}
- {pin_num: F8, pin_signal: VDD173, label: P3V3_K66F}
- {pin_num: G8, pin_signal: VSS95, label: GND}
- {pin_num: H8, pin_signal: VSS139, label: GND}
- {pin_num: J8, pin_signal: ADC0_SE10/PTA7/FTM0_CH4/RMII0_MDIO/MII0_MDIO/TRACE_D3, label: 'J3[9]/FTM0_CH4/TRACE_D3', identifier: FTM0_CH4}
- {pin_num: K8, pin_signal: ADC0_SE11/PTA8/FTM1_CH0/RMII0_MDC/MII0_MDC/FTM1_QD_PHA/TPM1_CH0/TRACE_D2, label: 'J3[11]/FTM1_CH0/TRACE_D2', identifier: FTM1_CH0}
- {pin_num: L8, pin_signal: PTA9/FTM1_CH1/MII0_RXD3/FTM1_QD_PHB/TPM1_CH1/TRACE_D1, label: 'J3[13]/FTM1_CH1/TRACE_D1', identifier: FTM1_CH1}
- {pin_num: M8, pin_signal: PTA5/USB0_CLKIN/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/I2S0_TX_BCLK/JTAG_TRST_b, label: 'U13[17]/RMII0_RXER', identifier: RMII0_RXER}
- {pin_num: A9, pin_signal: PTC4/LLWU_P8/SPI0_PCS0/UART1_TX/FTM0_CH3/FB_AD11/SDRAM_A19/CMP1_OUT, label: 'J1[4]/UART1_TX/FTM0_CH3/FB_AD11', identifier: UART1_TX}
- {pin_num: B9, pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17, label: 'U8[6]/U19[12]/I2C0_SDA', identifier: ACCEL_SDA;GYRO_SDA}
- {pin_num: C9, pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, label: 'U8[4]/U19[11]/I2C0_SCL', identifier: ACCEL_SCL;GYRO_SCL}
- {pin_num: D9, pin_signal: PTB21/SPI2_SCK/FB_AD30/SDRAM_D30/CMP1_OUT, label: NC}
- {pin_num: E9, pin_signal: TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1, label: 'U10[1]/UART0_TX', identifier: DEBUG_UART_TX}
- {pin_num: F9, pin_signal: PTB9/SPI1_PCS1/UART3_CTS_b/FB_AD20/SDRAM_D20, label: NC}
- {pin_num: G9, pin_signal: ADC1_SE11/PTB5/ENET0_1588_TMR3/FTM2_FLT0, label: 'J4[6]/ADC1_SE11', identifier: ADC1_SE11}
- {pin_num: H9, pin_signal: ADC0_SE9/ADC1_SE9/TSI0_CH6/PTB1/I2C0_SDA/FTM1_CH1/RMII0_MDC/MII0_MDC/SDRAM_RAS_b/FTM1_QD_PHB/TPM1_CH1, label: 'U13[11]/RMII0_MDC', identifier: RMII0_MDC}
- {pin_num: J9, pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB/TPM1_CH1, label: 'U13[13]/RMII0_RXD0', identifier: RMII0_RXD0}
- {pin_num: K9, pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA/TPM1_CH0, label: 'U13[12]/RMII0_RXD1', identifier: RMII0_RXD1}
- {pin_num: L9, pin_signal: PTA11/LLWU_P23/FTM2_CH1/MII0_RXCLK/I2C2_SDA/FTM2_QD_PHB/TPM2_CH1, label: LEDRGB_BLUE, identifier: LED_BLUE}
- {pin_num: M9, pin_signal: PTA10/LLWU_P22/FTM2_CH0/MII0_RXD2/FTM2_QD_PHA/TPM2_CH0/TRACE_D0, label: SW3, identifier: SW3}
- {pin_num: A10, pin_signal: NC185, label: NC}
- {pin_num: B10, pin_signal: NC186, label: NC}
- {pin_num: C10, pin_signal: NC187, label: NC}
- {pin_num: D10, pin_signal: PTB20/SPI2_PCS0/FB_AD31/SDRAM_D31/CMP0_OUT, label: 'J6[3]/RF_WIFI_CE'}
- {pin_num: E10, pin_signal: TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0, label: 'U7[4]/UART0_RX', identifier: DEBUG_UART_RX}
- {pin_num: F10, pin_signal: PTB8/UART3_RTS_b/FB_AD21/SDRAM_D21, label: NC}
- {pin_num: G10, pin_signal: ADC1_SE10/PTB4/ENET0_1588_TMR2/SDRAM_CS1_b/FTM1_FLT0, label: 'J4[8]/ADC1_SE10', identifier: ADC1_SE10}
- {pin_num: H10, pin_signal: ADC0_SE8/ADC1_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/RMII0_MDIO/MII0_MDIO/SDRAM_CAS_b/FTM1_QD_PHA/TPM1_CH0, label: 'U13[10]/RMII0_MDIO',
  identifier: RMII0_MDIO}
- {pin_num: J10, pin_signal: PTA27/MII0_CRS/FB_A26, label: 'J3[1]/FB_A26', identifier: FB_A26}
- {pin_num: K10, pin_signal: CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1, label: 'U13[20]/RMII0_TXD_0', identifier: RMII0_TXD_0}
- {pin_num: L10, pin_signal: PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1, label: 'U13[15]/RMII0_CRS_DV', identifier: RMII0_CRS_DV}
- {pin_num: M10, pin_signal: VSS172, label: GND}
- {pin_num: A11, pin_signal: CMP1_IN1/PTC3/LLWU_P7/SPI0_PCS1/UART1_RX/FTM0_CH2/CLKOUT/I2S0_TX_BCLK, label: 'J1[2]/UART1_RX/FTM0_CH2/CLKOUT', identifier: UART1_RX}
- {pin_num: B11, pin_signal: ADC0_SE15/TSI0_CH14/PTC1/LLWU_P6/SPI0_PCS3/UART1_RTS_b/FTM0_CH0/FB_AD13/SDRAM_A21/I2S0_TXD0, label: 'J1[5]/U20[C5]/I2S_TXD', identifier: I2S_TXD}
- {pin_num: C11, pin_signal: PTB23/SPI2_SIN/SPI0_PCS5/FB_AD28/SDRAM_D28/CMP3_OUT, label: 'J3[9]/CMP3_OUT', identifier: CMP_OUT}
- {pin_num: D11, pin_signal: TSI0_CH12/PTB19/CAN0_RX/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB/TPM2_CH1, label: 'J2[4]/FTM2_CH1', identifier: FTM2_CH1}
- {pin_num: E11, pin_signal: ADC1_SE15/PTB11/SPI1_SCK/UART3_TX/FB_AD18/SDRAM_D18/FTM0_FLT2, label: 'J2[9]/PTB11_RC/ADC1_SE15', identifier: PTB11_RC}
- {pin_num: E12, pin_signal: ADC1_SE14/PTB10/SPI1_PCS0/UART3_RX/FB_AD19/SDRAM_D19/FTM0_FLT1, label: 'J2[7]/PTB10_RC/ADC1_SE14', identifier: PTB10_RC}
- {pin_num: F11, pin_signal: ADC1_SE13/PTB7/FB_AD22/SDRAM_D22, label: 'J4[2]/ADC1_SE13', identifier: ADC1_SE13}
- {pin_num: G11, pin_signal: ADC0_SE13/TSI0_CH8/PTB3/I2C0_SDA/UART0_CTS_b/UART0_COL_b/ENET0_1588_TMR1/SDRAM_CS0_b/FTM0_FLT0, label: 'J4[10]/ADC0_SE13/I2C0_SDA', identifier: ADC0_SE13}
- {pin_num: G12, pin_signal: ADC0_SE12/TSI0_CH7/PTB2/I2C0_SCL/UART0_RTS_b/ENET0_1588_TMR0/SDRAM_WE/FTM0_FLT3, label: 'J4[12]/ADC0_SE12/I2C0_SCL', identifier: ADC0_SE12}
- {pin_num: H11, pin_signal: PTA29/MII0_COL/FB_A24, label: 'U19[3]/FXAS21002_INT1', identifier: GYRO_INT1}
- {pin_num: J11, pin_signal: PTA26/MII0_TXD3/FB_A27, label: 'J3[3]/FB_A27', identifier: FB_A27}
- {pin_num: K11, pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK, label: 'U13[21]/RMII0_TXD_1', identifier: RMII0_TXD_1}
- {pin_num: L11, pin_signal: CMP3_IN1/PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0, label: 'U13[19]/RMII0_TXEN', identifier: RMII0_TXEN}
- {pin_num: M11, pin_signal: XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1/TPM_CLKIN1, label: 'X501[3]', identifier: XTAL0}
- {pin_num: A12, pin_signal: ADC0_SE4b/CMP1_IN0/TSI0_CH15/PTC2/SPI0_PCS2/UART1_CTS_b/FTM0_CH1/FB_AD12/SDRAM_A20/I2S0_TX_FS, label: 'J1[14]/FTM0_CH1/CMP1_IN0/FB_AD12',
  identifier: FTM0_CH1}
- {pin_num: B12, pin_signal: ADC0_SE14/TSI0_CH13/PTC0/SPI0_PCS4/PDB0_EXTRG/USB0_SOF_OUT/FB_AD14/SDRAM_A22/I2S0_TXD1, label: 'J2[11]/ADC0_SE14', identifier: ADC0_SE14}
- {pin_num: C12, pin_signal: PTB22/SPI2_SOUT/FB_AD29/SDRAM_D29/CMP2_OUT, label: NC}
- {pin_num: D12, pin_signal: TSI0_CH11/PTB18/CAN0_TX/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/SDRAM_A23/FTM2_QD_PHA/TPM2_CH0, label: 'J2[2]/FTM2_CH0', identifier: FTM2_CH0}
- {pin_num: F12, pin_signal: ADC1_SE12/PTB6/FB_AD23/SDRAM_D23, label: 'J4[4]/ADC1_SE12', identifier: ADC1_SE12}
- {pin_num: H12, pin_signal: PTA28/MII0_TXER/FB_A25, label: 'U19[2]/FXAS21002_INT2', identifier: GYRO_INT2}
- {pin_num: J12, pin_signal: CMP3_IN5/PTA25/MII0_TXCLK/FB_A28, label: 'J1[16]/CMP3_IN5', identifier: CMP3_IN5}
- {pin_num: K12, pin_signal: CMP3_IN4/PTA24/MII0_TXD2/FB_A29, label: NC}
- {pin_num: L12, pin_signal: RESET_b, label: RESET}
- {pin_num: M12, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0/TPM_CLKIN0, label: EXTAL0, identifier: EXTAL0}
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
  - {pin_num: K6, peripheral: TPIU, signal: SWO, pin_signal: TSI0_CH3/PTA2/UART0_TX/FTM0_CH7/I2C3_SCL/LPUART0_TX/JTAG_TDO/TRACE_SWO/EZP_DO, pull_select: down, pull_enable: disable}
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

    /* PORTA2 (pin K6) is configured as TRACE_SWO */
    PORT_SetPinMux(BOARD_TRACE_SWO_PORT, BOARD_TRACE_SWO_PIN, kPORT_MuxAlt7);

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
BOARD_InitBUTTONsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B2, peripheral: GPIOD, signal: 'GPIO, 11', pin_signal: PTD11/LLWU_P25/SPI2_PCS0/SDHC0_CLKIN/LPUART0_CTS_b/FB_A19, direction: INPUT, gpio_interrupt: kPORT_InterruptFallingEdge,
    pull_select: up, pull_enable: enable}
  - {pin_num: M9, peripheral: GPIOA, signal: 'GPIO, 10', pin_signal: PTA10/LLWU_P22/FTM2_CH0/MII0_RXD2/FTM2_QD_PHA/TPM2_CH0/TRACE_D0, direction: INPUT, gpio_interrupt: kPORT_InterruptFallingEdge,
    pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBUTTONsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBUTTONsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA10 (pin M9)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PIN, &SW3_config);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD11 (pin B2)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PIN, &SW2_config);

    /* PORTA10 (pin M9) is configured as PTA10 */
    PORT_SetPinMux(BOARD_SW3_PORT, BOARD_SW3_PIN, kPORT_MuxAsGpio);

    /* Interrupt configuration on PORTA10 (pin M9): Interrupt on falling edge */
    PORT_SetPinInterruptConfig(BOARD_SW3_PORT, BOARD_SW3_PIN, kPORT_InterruptFallingEdge);

    PORTA->PCR[10] = ((PORTA->PCR[10] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                       * corresponding PE field is set. */
                      | (uint32_t)(kPORT_PullUp));

    /* PORTD11 (pin B2) is configured as PTD11 */
    PORT_SetPinMux(BOARD_SW2_PORT, BOARD_SW2_PIN, kPORT_MuxAsGpio);

    /* Interrupt configuration on PORTD11 (pin B2): Interrupt on falling edge */
    PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_PIN, kPORT_InterruptFallingEdge);

    PORTD->PCR[11] = ((PORTD->PCR[11] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the
                       * corresponding PE field is set. */
                      | (uint32_t)(kPORT_PullUp));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: L9, peripheral: GPIOA, signal: 'GPIO, 11', pin_signal: PTA11/LLWU_P23/FTM2_CH1/MII0_RXCLK/I2C2_SDA/FTM2_QD_PHB/TPM2_CH1, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: E1, peripheral: GPIOE, signal: 'GPIO, 6', pin_signal: PTE6/LLWU_P16/SPI1_PCS3/UART3_CTS_b/I2S0_MCLK/FTM3_CH1/USB0_SOF_OUT, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: D7, peripheral: GPIOC, signal: 'GPIO, 9', pin_signal: ADC1_SE5b/CMP0_IN3/PTC9/FTM3_CH5/I2S0_RX_BCLK/FB_AD6/SDRAM_A14/FTM2_FLT0, direction: OUTPUT, gpio_init_state: 'true',
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
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
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t LED_BLUE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTA11 (pin L9)  */
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_PIN, &LED_BLUE_config);

    gpio_pin_config_t LED_RED_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTC9 (pin D7)  */
    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_PIN, &LED_RED_config);

    gpio_pin_config_t LED_GREEN_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 1U
    };
    /* Initialize GPIO functionality on pin PTE6 (pin E1)  */
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_PIN, &LED_GREEN_config);

    const port_pin_config_t LED_BLUE = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as PTA11 */
                                        kPORT_MuxAsGpio,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTA11 (pin L9) is configured as PTA11 */
    PORT_SetPinConfig(BOARD_LED_BLUE_PORT, BOARD_LED_BLUE_PIN, &LED_BLUE);

    const port_pin_config_t LED_RED = {/* Internal pull-up/down resistor is disabled */
                                       kPORT_PullDisable,
                                       /* Fast slew rate is configured */
                                       kPORT_FastSlewRate,
                                       /* Passive filter is disabled */
                                       kPORT_PassiveFilterDisable,
                                       /* Open drain is disabled */
                                       kPORT_OpenDrainDisable,
                                       /* Low drive strength is configured */
                                       kPORT_LowDriveStrength,
                                       /* Pin is configured as PTC9 */
                                       kPORT_MuxAsGpio,
                                       /* Pin Control Register fields [15:0] are not locked */
                                       kPORT_UnlockRegister};
    /* PORTC9 (pin D7) is configured as PTC9 */
    PORT_SetPinConfig(BOARD_LED_RED_PORT, BOARD_LED_RED_PIN, &LED_RED);

    const port_pin_config_t LED_GREEN = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as PTE6 */
                                         kPORT_MuxAsGpio,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTE6 (pin E1) is configured as PTE6 */
    PORT_SetPinConfig(BOARD_LED_GREEN_PORT, BOARD_LED_GREEN_PIN, &LED_GREEN);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCEL_I2CPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: C9, peripheral: I2C0, signal: SCL, pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, identifier: ACCEL_SCL, slew_rate: fast, open_drain: enable,
    pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: B9, peripheral: I2C0, signal: SDA, pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17, identifier: ACCEL_SDA, slew_rate: fast, open_drain: enable, pull_select: down,
    pull_enable: disable, digital_filter: disable}
  - {pin_num: D5, peripheral: GPIOC, signal: 'GPIO, 17', pin_signal: PTC17/CAN1_TX/UART3_TX/ENET0_1588_TMR1/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b/SDRAM_DQM3, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: D6, peripheral: GPIOC, signal: 'GPIO, 13', pin_signal: PTC13/UART4_CTS_b/FTM_CLKIN1/FB_AD26/SDRAM_D26/TPM_CLKIN1, direction: INPUT, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitACCEL_I2CPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitACCEL_I2CPins(void)
{
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t ACCEL_INT2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC13 (pin D6)  */
    GPIO_PinInit(BOARD_ACCEL_INT2_GPIO, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2_config);

    gpio_pin_config_t ACCEL_INT1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC17 (pin D5)  */
    GPIO_PinInit(BOARD_ACCEL_INT1_GPIO, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1_config);

    const port_pin_config_t ACCEL_INT2 = {/* Internal pull-up resistor is enabled */
                                          kPORT_PullUp,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTC13 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC13 (pin D6) is configured as PTC13 */
    PORT_SetPinConfig(BOARD_ACCEL_INT2_PORT, BOARD_ACCEL_INT2_PIN, &ACCEL_INT2);

    const port_pin_config_t ACCEL_INT1 = {/* Internal pull-up resistor is enabled */
                                          kPORT_PullUp,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as PTC17 */
                                          kPORT_MuxAsGpio,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTC17 (pin D5) is configured as PTC17 */
    PORT_SetPinConfig(BOARD_ACCEL_INT1_PORT, BOARD_ACCEL_INT1_PIN, &ACCEL_INT1);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
          PORT_DFER_DFE_8_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_9_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t ACCEL_SCL = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
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
    /* PORTD8 (pin C9) is configured as I2C0_SCL */
    PORT_SetPinConfig(BOARD_ACCEL_SCL_PORT, BOARD_ACCEL_SCL_PIN, &ACCEL_SCL);

    const port_pin_config_t ACCEL_SDA = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
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
    /* PORTD9 (pin B9) is configured as I2C0_SDA */
    PORT_SetPinConfig(BOARD_ACCEL_SDA_PORT, BOARD_ACCEL_SDA_PIN, &ACCEL_SDA);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitGYRO_I2CPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B9, peripheral: I2C0, signal: SDA, pin_signal: PTD9/I2C0_SDA/LPUART0_TX/FB_A17, identifier: GYRO_SDA, slew_rate: fast, open_drain: enable, pull_select: down,
    pull_enable: disable, digital_filter: disable}
  - {pin_num: C9, peripheral: I2C0, signal: SCL, pin_signal: PTD8/LLWU_P24/I2C0_SCL/LPUART0_RX/FB_A16, identifier: GYRO_SCL, slew_rate: fast, open_drain: enable,
    pull_select: down, pull_enable: disable, digital_filter: disable}
  - {pin_num: H11, peripheral: GPIOA, signal: 'GPIO, 29', pin_signal: PTA29/MII0_COL/FB_A24, direction: INPUT, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable}
  - {pin_num: H12, peripheral: GPIOA, signal: 'GPIO, 28', pin_signal: PTA28/MII0_TXER/FB_A25, direction: INPUT, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitGYRO_I2CPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitGYRO_I2CPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t GYRO_INT2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA28 (pin H12)  */
    GPIO_PinInit(BOARD_GYRO_INT2_GPIO, BOARD_GYRO_INT2_PIN, &GYRO_INT2_config);

    gpio_pin_config_t GYRO_INT1_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA29 (pin H11)  */
    GPIO_PinInit(BOARD_GYRO_INT1_GPIO, BOARD_GYRO_INT1_PIN, &GYRO_INT1_config);

    const port_pin_config_t GYRO_INT2 = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as PTA28 */
                                         kPORT_MuxAsGpio,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTA28 (pin H12) is configured as PTA28 */
    PORT_SetPinConfig(BOARD_GYRO_INT2_PORT, BOARD_GYRO_INT2_PIN, &GYRO_INT2);

    const port_pin_config_t GYRO_INT1 = {/* Internal pull-up resistor is enabled */
                                         kPORT_PullUp,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is enabled */
                                         kPORT_OpenDrainEnable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as PTA29 */
                                         kPORT_MuxAsGpio,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTA29 (pin H11) is configured as PTA29 */
    PORT_SetPinConfig(BOARD_GYRO_INT1_PORT, BOARD_GYRO_INT1_PIN, &GYRO_INT1);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
          PORT_DFER_DFE_8_MASK
            /* Digital filter is configured for PORTD1 */
            | PORT_DFER_DFE_9_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t GYRO_SCL = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
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
    /* PORTD8 (pin C9) is configured as I2C0_SCL */
    PORT_SetPinConfig(BOARD_GYRO_SCL_PORT, BOARD_GYRO_SCL_PIN, &GYRO_SCL);

    const port_pin_config_t GYRO_SDA = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
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
    /* PORTD9 (pin B9) is configured as I2C0_SDA */
    PORT_SetPinConfig(BOARD_GYRO_SDA_PORT, BOARD_GYRO_SDA_PIN, &GYRO_SDA);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: E10, peripheral: UART0, signal: RX, pin_signal: TSI0_CH9/PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/SDRAM_D17/EWM_IN/TPM_CLKIN0, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: E9, peripheral: UART0, signal: TX, pin_signal: TSI0_CH10/PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/SDRAM_D16/EWM_OUT_b/TPM_CLKIN1, direction: OUTPUT,
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
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

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
                                             /* Pin is configured as UART0_RX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB16 (pin E10) is configured as UART0_RX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, &DEBUG_UART_RX);

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
                                             /* Pin is configured as UART0_TX */
                                             kPORT_MuxAlt3,
                                             /* Pin Control Register fields [15:0] are not locked */
                                             kPORT_UnlockRegister};
    /* PORTB17 (pin E9) is configured as UART0_TX */
    PORT_SetPinConfig(BOARD_DEBUG_UART_TX_PORT, BOARD_DEBUG_UART_TX_PIN, &DEBUG_UART_TX);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDHC0Pins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: E4, peripheral: SDHC, signal: CMD, pin_signal: ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/TRACE_D1/SPI1_SOUT, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: D2, peripheral: SDHC, signal: 'DATA, 0', pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/TRACE_D3/I2C1_SCL/SPI1_SIN, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: D3, peripheral: SDHC, signal: 'DATA, 1', pin_signal: ADC1_SE4a/PTE0/SPI1_PCS1/UART1_TX/SDHC0_D1/TRACE_CLKOUT/I2C1_SDA/RTC_CLKOUT, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: E2, peripheral: SDHC, signal: 'DATA, 2', pin_signal: PTE5/SPI1_PCS2/UART3_RX/SDHC0_D2/FTM3_CH0, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: E3, peripheral: SDHC, signal: 'DATA, 3', pin_signal: PTE4/LLWU_P2/SPI1_PCS0/UART3_TX/SDHC0_D3/TRACE_D0, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
  - {pin_num: D1, peripheral: SDHC, signal: DCLK, pin_signal: ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/TRACE_D2, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: B3, peripheral: GPIOD, signal: 'GPIO, 10', pin_signal: PTD10/LPUART0_RTS_b/FB_A18, direction: INPUT, slew_rate: fast, open_drain: disable, pull_select: up,
    pull_enable: enable, digital_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSDHC0Pins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitSDHC0Pins(void)
{
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t SDCARD_CARD_DETECTION_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTD10 (pin B3)  */
    GPIO_PinInit(BOARD_SDCARD_CARD_DETECTION_GPIO, BOARD_SDCARD_CARD_DETECTION_PIN, &SDCARD_CARD_DETECTION_config);
    /* Configure digital filter */
    PORT_EnablePinsDigitalFilter(
        /* Digital filter is configured on port D */
        PORTD,
        /* Digital filter is configured for PORTD0 */
        PORT_DFER_DFE_10_MASK,
        /* Disable digital filter */
        false);

    const port_pin_config_t SDCARD_CARD_DETECTION = {/* Internal pull-up resistor is enabled */
                                                     kPORT_PullUp,
                                                     /* Fast slew rate is configured */
                                                     kPORT_FastSlewRate,
                                                     /* Passive filter is disabled */
                                                     kPORT_PassiveFilterDisable,
                                                     /* Open drain is disabled */
                                                     kPORT_OpenDrainDisable,
                                                     /* Low drive strength is configured */
                                                     kPORT_LowDriveStrength,
                                                     /* Pin is configured as PTD10 */
                                                     kPORT_MuxAsGpio,
                                                     /* Pin Control Register fields [15:0] are not locked */
                                                     kPORT_UnlockRegister};
    /* PORTD10 (pin B3) is configured as PTD10 */
    PORT_SetPinConfig(BOARD_SDCARD_CARD_DETECTION_PORT, BOARD_SDCARD_CARD_DETECTION_PIN, &SDCARD_CARD_DETECTION);

    const port_pin_config_t SDHC0_D1 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D1 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTE0 (pin D3) is configured as SDHC0_D1 */
    PORT_SetPinConfig(BOARD_SDHC0_D1_PORT, BOARD_SDHC0_D1_PIN, &SDHC0_D1);

    const port_pin_config_t SDHC0_D0 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D0 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTE1 (pin D2) is configured as SDHC0_D0 */
    PORT_SetPinConfig(BOARD_SDHC0_D0_PORT, BOARD_SDHC0_D0_PIN, &SDHC0_D0);

    const port_pin_config_t SDHC0_DCLK = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as SDHC0_DCLK */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTE2 (pin D1) is configured as SDHC0_DCLK */
    PORT_SetPinConfig(BOARD_SDHC0_DCLK_PORT, BOARD_SDHC0_DCLK_PIN, &SDHC0_DCLK);

    const port_pin_config_t SDHC0_CMD = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as SDHC0_CMD */
                                         kPORT_MuxAlt4,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTE3 (pin E4) is configured as SDHC0_CMD */
    PORT_SetPinConfig(BOARD_SDHC0_CMD_PORT, BOARD_SDHC0_CMD_PIN, &SDHC0_CMD);

    const port_pin_config_t SDHC0_D3 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D3 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTE4 (pin E3) is configured as SDHC0_D3 */
    PORT_SetPinConfig(BOARD_SDHC0_D3_PORT, BOARD_SDHC0_D3_PIN, &SDHC0_D3);

    const port_pin_config_t SDHC0_D2 = {/* Internal pull-up/down resistor is disabled */
                                        kPORT_PullDisable,
                                        /* Fast slew rate is configured */
                                        kPORT_FastSlewRate,
                                        /* Passive filter is disabled */
                                        kPORT_PassiveFilterDisable,
                                        /* Open drain is disabled */
                                        kPORT_OpenDrainDisable,
                                        /* Low drive strength is configured */
                                        kPORT_LowDriveStrength,
                                        /* Pin is configured as SDHC0_D2 */
                                        kPORT_MuxAlt4,
                                        /* Pin Control Register fields [15:0] are not locked */
                                        kPORT_UnlockRegister};
    /* PORTE5 (pin E2) is configured as SDHC0_D2 */
    PORT_SetPinConfig(BOARD_SDHC0_D2_PORT, BOARD_SDHC0_D2_PIN, &SDHC0_D2);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitENETPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: K4, peripheral: ENET, signal: RMII_CLKIN, pin_signal: PTE26/ENET_1588_CLKIN/UART4_CTS_b/RTC_CLKOUT/USB0_CLKIN, identifier: ETHERNET_CLOCK, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: L10, peripheral: ENET, signal: RMII_CRS_DV, pin_signal: PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: H9, peripheral: ENET, signal: RMII_MDC, pin_signal: ADC0_SE9/ADC1_SE9/TSI0_CH6/PTB1/I2C0_SDA/FTM1_CH1/RMII0_MDC/MII0_MDC/SDRAM_RAS_b/FTM1_QD_PHB/TPM1_CH1,
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: H10, peripheral: ENET, signal: RMII_MDIO, pin_signal: ADC0_SE8/ADC1_SE8/TSI0_CH0/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/RMII0_MDIO/MII0_MDIO/SDRAM_CAS_b/FTM1_QD_PHA/TPM1_CH0,
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: down, pull_enable: disable}
  - {pin_num: J9, peripheral: ENET, signal: RMII_RXD0, pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB/TPM1_CH1,
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: K9, peripheral: ENET, signal: RMII_RXD1, pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA/TPM1_CH0, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: M8, peripheral: ENET, signal: RMII_RXER, pin_signal: PTA5/USB0_CLKIN/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/I2S0_TX_BCLK/JTAG_TRST_b, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: K10, peripheral: ENET, signal: RMII_TXD0, pin_signal: CMP3_IN2/PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: K11, peripheral: ENET, signal: RMII_TXD1, pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: L11, peripheral: ENET, signal: RMII_TXEN, pin_signal: CMP3_IN1/PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: K4, peripheral: ENET, signal: CLKIN_1588, pin_signal: PTE26/ENET_1588_CLKIN/UART4_CTS_b/RTC_CLKOUT/USB0_CLKIN, identifier: ENET_1588_CLKIN, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitENETPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitENETPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    const port_pin_config_t RMII0_RXD1 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as RMII0_RXD1 */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTA12 (pin K9) is configured as RMII0_RXD1 */
    PORT_SetPinConfig(BOARD_RMII0_RXD1_PORT, BOARD_RMII0_RXD1_PIN, &RMII0_RXD1);

    const port_pin_config_t RMII0_RXD0 = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as RMII0_RXD0 */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTA13 (pin J9) is configured as RMII0_RXD0 */
    PORT_SetPinConfig(BOARD_RMII0_RXD0_PORT, BOARD_RMII0_RXD0_PIN, &RMII0_RXD0);

    const port_pin_config_t RMII0_CRS_DV = {/* Internal pull-up/down resistor is disabled */
                                            kPORT_PullDisable,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as RMII0_CRS_DV */
                                            kPORT_MuxAlt4,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTA14 (pin L10) is configured as RMII0_CRS_DV */
    PORT_SetPinConfig(BOARD_RMII0_CRS_DV_PORT, BOARD_RMII0_CRS_DV_PIN, &RMII0_CRS_DV);

    const port_pin_config_t RMII0_TXEN = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as RMII0_TXEN */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTA15 (pin L11) is configured as RMII0_TXEN */
    PORT_SetPinConfig(BOARD_RMII0_TXEN_PORT, BOARD_RMII0_TXEN_PIN, &RMII0_TXEN);

    const port_pin_config_t RMII0_TXD_0 = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as RMII0_TXD0 */
                                           kPORT_MuxAlt4,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTA16 (pin K10) is configured as RMII0_TXD0 */
    PORT_SetPinConfig(BOARD_RMII0_TXD_0_PORT, BOARD_RMII0_TXD_0_PIN, &RMII0_TXD_0);

    const port_pin_config_t RMII0_TXD_1 = {/* Internal pull-up/down resistor is disabled */
                                           kPORT_PullDisable,
                                           /* Fast slew rate is configured */
                                           kPORT_FastSlewRate,
                                           /* Passive filter is disabled */
                                           kPORT_PassiveFilterDisable,
                                           /* Open drain is disabled */
                                           kPORT_OpenDrainDisable,
                                           /* Low drive strength is configured */
                                           kPORT_LowDriveStrength,
                                           /* Pin is configured as RMII0_TXD1 */
                                           kPORT_MuxAlt4,
                                           /* Pin Control Register fields [15:0] are not locked */
                                           kPORT_UnlockRegister};
    /* PORTA17 (pin K11) is configured as RMII0_TXD1 */
    PORT_SetPinConfig(BOARD_RMII0_TXD_1_PORT, BOARD_RMII0_TXD_1_PIN, &RMII0_TXD_1);

    const port_pin_config_t RMII0_RXER = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as RMII0_RXER */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTA5 (pin M8) is configured as RMII0_RXER */
    PORT_SetPinConfig(BOARD_RMII0_RXER_PORT, BOARD_RMII0_RXER_PIN, &RMII0_RXER);

    const port_pin_config_t RMII0_MDIO = {/* Internal pull-up/down resistor is disabled */
                                          kPORT_PullDisable,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is disabled */
                                          kPORT_OpenDrainDisable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as RMII0_MDIO */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTB0 (pin H10) is configured as RMII0_MDIO */
    PORT_SetPinConfig(BOARD_RMII0_MDIO_PORT, BOARD_RMII0_MDIO_PIN, &RMII0_MDIO);

    const port_pin_config_t RMII0_MDC = {/* Internal pull-up/down resistor is disabled */
                                         kPORT_PullDisable,
                                         /* Fast slew rate is configured */
                                         kPORT_FastSlewRate,
                                         /* Passive filter is disabled */
                                         kPORT_PassiveFilterDisable,
                                         /* Open drain is disabled */
                                         kPORT_OpenDrainDisable,
                                         /* Low drive strength is configured */
                                         kPORT_LowDriveStrength,
                                         /* Pin is configured as RMII0_MDC */
                                         kPORT_MuxAlt4,
                                         /* Pin Control Register fields [15:0] are not locked */
                                         kPORT_UnlockRegister};
    /* PORTB1 (pin H9) is configured as RMII0_MDC */
    PORT_SetPinConfig(BOARD_RMII0_MDC_PORT, BOARD_RMII0_MDC_PIN, &RMII0_MDC);

    const port_pin_config_t ETHERNET_CLOCK = {/* Internal pull-up/down resistor is disabled */
                                              kPORT_PullDisable,
                                              /* Fast slew rate is configured */
                                              kPORT_FastSlewRate,
                                              /* Passive filter is disabled */
                                              kPORT_PassiveFilterDisable,
                                              /* Open drain is disabled */
                                              kPORT_OpenDrainDisable,
                                              /* Low drive strength is configured */
                                              kPORT_LowDriveStrength,
                                              /* Pin is configured as ENET_1588_CLKIN */
                                              kPORT_MuxAlt2,
                                              /* Pin Control Register fields [15:0] are not locked */
                                              kPORT_UnlockRegister};
    /* PORTE26 (pin K4) is configured as ENET_1588_CLKIN */
    PORT_SetPinConfig(BOARD_ETHERNET_CLOCK_PORT, BOARD_ETHERNET_CLOCK_PIN, &ETHERNET_CLOCK);

    SIM->SOPT2 = ((SIM->SOPT2 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT2_RMIISRC_MASK)))

                  /* RMII clock source select: External bypass clock (ENET_1588_CLKIN). */
                  | SIM_SOPT2_RMIISRC(SOPT2_RMIISRC_ENET));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitUSBPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: K1, peripheral: USBPHY, signal: DM, pin_signal: USB1_DM/LLWU_P31, identifier: K66_MICRO_USB_DN_PHY}
  - {pin_num: J1, peripheral: USBPHY, signal: DP, pin_signal: USB1_DP/LLWU_P30, identifier: K66_MICRO_USB_DP_PHY}
  - {pin_num: F1, peripheral: USBPHY, signal: ID, pin_signal: PTE10/LLWU_P18/I2C3_SDA/I2S0_TXD0/LPUART0_CTS_b/FTM3_CH5/USB1_ID, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: L1, peripheral: USBPHY, signal: VBUS, pin_signal: USB1_VBUS/LLWU_P29}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitUSBPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitUSBPins(void)
{
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    const port_pin_config_t USB_ID = {/* Internal pull-up/down resistor is disabled */
                                      kPORT_PullDisable,
                                      /* Fast slew rate is configured */
                                      kPORT_FastSlewRate,
                                      /* Passive filter is disabled */
                                      kPORT_PassiveFilterDisable,
                                      /* Open drain is disabled */
                                      kPORT_OpenDrainDisable,
                                      /* Low drive strength is configured */
                                      kPORT_LowDriveStrength,
                                      /* Pin is configured as USB1_ID */
                                      kPORT_MuxAlt7,
                                      /* Pin Control Register fields [15:0] are not locked */
                                      kPORT_UnlockRegister};
    /* PORTE10 (pin F1) is configured as USB1_ID */
    PORT_SetPinConfig(BOARD_USB_ID_PORT, BOARD_USB_ID_PIN, &USB_ID);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSCsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: M12, peripheral: OSC, signal: EXTAL0, pin_signal: EXTAL0/PTA18/FTM0_FLT2/FTM_CLKIN0/TPM_CLKIN0, slew_rate: no_init, open_drain: no_init, pull_select: no_init,
    pull_enable: no_init}
  - {pin_num: M11, peripheral: OSC, signal: XTAL0, pin_signal: XTAL0/PTA19/FTM1_FLT0/FTM_CLKIN1/LPTMR0_ALT1/TPM_CLKIN1, slew_rate: no_init, open_drain: no_init, pull_select: no_init,
    pull_enable: no_init}
  - {pin_num: M6, peripheral: RTC, signal: EXTAL32, pin_signal: EXTAL32}
  - {pin_num: M7, peripheral: RTC, signal: XTAL32, pin_signal: XTAL32}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitOSCsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitOSCsPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* PORTA18 (pin M12) is configured as EXTAL0 */
    PORT_SetPinMux(BOARD_EXTAL0_PORT, BOARD_EXTAL0_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTA19 (pin M11) is configured as XTAL0 */
    PORT_SetPinMux(BOARD_XTAL0_PORT, BOARD_XTAL0_PIN, kPORT_PinDisabledOrAnalog);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
