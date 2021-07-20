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
processor: LPC54608J512
package_id: LPC54608J512ET180
mcu_data: ksdk2_0
processor_version: 0.0.28
board: LPCXpresso54608
pin_labels:
- {pin_num: K12, pin_signal: PIO1_1/FC3_RXD_SDA_MOSI/CTIMER0_CAP3/SCT0_GPI5/USB1_OVERCURRENTN, label: 'J12[12]/U29[4]/SW5/P1_1-USER_PB-USB1_OVRCURn', identifier: SW5}
- {pin_num: E7, pin_signal: PIO0_5/CAN0_TD/FC4_RXD_SDA_MOSI/CTIMER3_MAT0/SCT0_GPI5/EMC_D(3)/ENET_MDIO, label: 'U28[C9]/RP3[1]/JS32[1]/SW3/P0_5-ISP1/P0_5-EMC_D3',
  identifier: SW3;EMC_D3}
- {pin_num: C8, pin_signal: PIO0_4/CAN0_RD/FC4_SCK/CTIMER3_CAP0/SCT0_GPI4/EMC_D(2)/ENET_MDC, label: 'U28[B8]/RP3[2]/JS32[3]/SW4/P0_4-ISP0/P0_4-EMC_D2', identifier: SW4;EMC_D2}
- {pin_num: A13, pin_signal: PIO3_3/LCD_VD(17)/FC9_TXD_SCL_MISO, label: 'J9[8]/LED2/P3_3-USR_LED2', identifier: LED2}
- {pin_num: C3, pin_signal: PIO2_2/ENET_CRS/FC3_SSEL3/SCT0_OUT6/CTIMER1_MAT1, label: 'J9[6]/LED3/P2_2-CT1MAT1-USR_LED3', identifier: LED3}
- {pin_num: E3, pin_signal: PIO3_14/SCT0_OUT4/FC9_RTS_SCL_SSEL1/CTIMER3_MAT1/TRACEDATA(2), label: 'J13[5]/LED1/P3_14-CT3MAT1-USR_LED1', identifier: LED1}
- {pin_num: A1, pin_signal: PIO0_1/CAN1_TD/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_GPI1/PDM0_DATA, label: 'U26[14]/J14[1]/P0_1-ISP_FC3_SSEL0', identifier: ISP_FC3_SSEL0}
- {pin_num: A10, pin_signal: PIO0_3/FC3_RXD_SDA_MOSI/CTIMER0_MAT1/SCT0_OUT1/SCT0_GPI3/EMC_D(1), label: 'U28[B9]/RP3[3]/JS34[1]/U26[11]/J14[2]/P0_3-ISP_FC3_MOSI/P0_3-EMC_D1',
  identifier: ISP_FC3_MOSI;EMC_D1}
- {pin_num: E9, pin_signal: PIO0_2/FC3_TXD_SCL_MISO/CTIMER0_CAP1/SCT0_OUT0/SCT0_GPI2/EMC_D(0), label: 'U28[A8]/RP3[4]/JS35[1]/U24[11]/J14[3]/P0_2-ISP_FC3_MISO/P0_2-EMC_D0',
  identifier: ISP_FC3_MISO;EMC_D0}
- {pin_num: D6, pin_signal: PIO0_0/CAN1_RD/FC3_SCK/CTIMER0_MAT0/SCT0_GPI0/PDM0_CLK, label: 'U26[13]/J14[4]/P0_0-ISP_FC3_SCK', identifier: ISP_FC3_SCK}
- {pin_num: H4, pin_signal: PIO3_13/SCT0_OUT9/FC9_CTS_SDA_SSEL0/CTIMER3_CAP1/EMC_FBCK/TRACEDATA(1), label: 'J14[8]/P3_13-BRIDGE_GPIO', identifier: BRIDGE_GPIO}
- {pin_num: F11, pin_signal: PIO0_13/FC1_CTS_SDA_SSEL0/UTICK_CAP0/CTIMER0_CAP0/SCT0_GPI0/ENET_RXD0, label: 'JS16[2]/J14[9]/P0_13-ISP_FC1_SDAX', identifier: ISP_FC1_SDAX}
- {pin_num: E13, pin_signal: PIO0_14/FC1_RTS_SCL_SSEL1/UTICK_CAP1/CTIMER0_CAP1/SCT0_GPI1/ENET_RXD1, label: 'JS15[2]/J14[10]/P0_14-ISP_FC1_SCLX', identifier: ISP_FC1_SCLX}
- {pin_num: E2, pin_signal: PIO3_24/FC2_RTS_SCL_SSEL1/CTIMER4_CAP0/USB0_VBUS, label: 'J11[9]/J9[1]/U10[2]/J17[4]/U19[2]/P3_24-FC2_SCLX', identifier: FC2_SCLX}
- {pin_num: C2, pin_signal: PIO3_23/FC2_CTS_SDA_SSEL0/UTICK_CAP3, label: 'J11[10]/J9[3]/U10[3]/J17[5]/U19[10]/P3_23-FC2_SDAX', identifier: FC2_SDAX}
- {pin_num: B11, pin_signal: PIO3_4/LCD_VD(18)/FC8_CTS_SDA_SSEL0/CTIMER4_CAP1, label: 'J12[10]/U19[3]/P3_4-ACCL_INTR', identifier: ACCL_INTR}
- {pin_num: N7, pin_signal: PIO0_23/MCLK/CTIMER1_MAT2/CTIMER3_MAT3/SCT0_OUT4/SPIFI_CSN/ADC0_11, label: 'J13[8]/U27[1]/P0_23-SPIFI_CSn-MCLK', identifier: SPIFI_CSn}
- {pin_num: M13, pin_signal: PIO0_26/FC2_RXD_SDA_MOSI/CLKOUT/CTIMER3_CAP2/SCT0_OUT5/PDM0_CLK/SPIFI_CLK/USB0_IDVALUE, label: 'J13[2]/U27[6]/P0_26-SPIFI_CLK', identifier: SPIFI_CLK}
- {pin_num: M7, pin_signal: PIO0_24/FC0_RXD_SDA_MOSI/SD_D(0)/CTIMER2_CAP0/SCT0_GPI0/SPIFI_IO(0), label: 'J13[6]/U27[5]/P0_24-SPIFI_IO0', identifier: SPIFI_IO0}
- {pin_num: L9, pin_signal: PIO0_27/FC2_TXD_SCL_MISO/CTIMER3_MAT2/SCT0_OUT6/PDM0_DATA/SPIFI_IO(3), label: 'J13[12]/U27[7]/P0_27-SPIFI_IO3', identifier: SPIFI_IO3}
- {pin_num: M9, pin_signal: PIO0_28/FC0_SCK/CTIMER2_CAP3/SCT0_OUT7/TRACEDATA(3)/SPIFI_IO(2)/USB0_OVERCURRENTN, label: 'J13[10]/U27[3]/P0_28-SPIFI_IO2-USB0_OCURRn',
  identifier: SPIFI_IO2}
- {pin_num: K8, pin_signal: PIO0_25/FC0_TXD_SCL_MISO/SD_D(1)/CTIMER2_CAP1/SCT0_GPI1/SPIFI_IO(1), label: 'J13[4]/U27[2]/P0_25-SPIFI_IO1', identifier: SPIFI_IO1}
- {pin_num: M2, pin_signal: PIO2_12/LCD_LE/SD_VOLT(1)/USB0_IDVALUE/FC5_RXD_SDA_MOSI, label: 'U26A1[3]/P2_12-SPIFI_RSTn', identifier: SPIFI_RSTn}
- {pin_num: D2, pin_signal: PIO3_15/FC8_SCK/SD_WR_PRT, label: 'RP1[1]/U9[8]/P3_15-SD_WPn', identifier: SD_WPn}
- {pin_num: P1, pin_signal: PIO2_10/ENET_RX_ER/SD_CARD_DET_N, label: 'RP1[2]/U9[7]/P2_10-SD_CDn', identifier: SD_CDn}
- {pin_num: F4, pin_signal: PIO2_8/ENET_RXD2/SD_D(2)/CTIMER0_MAT0, label: 'RP1[3]/U9[6]/P2_8-SD_D2', identifier: SD_D2}
- {pin_num: J2, pin_signal: PIO2_7/ENET_COL/SD_D(1)/FREQME_GPIO_CLK_B/CTIMER0_CAP1, label: 'RP1[4]/U9[5]/P2_7-SD_D1', identifier: SD_D1}
- {pin_num: F3, pin_signal: PIO2_6/ENET_TX_CLK/SD_D(0)/FC1_RTS_SCL_SSEL1/CTIMER0_CAP0, label: 'RP1[5]/U9[4]/P2_6-SD_D0', identifier: SD_D0}
- {pin_num: B1, pin_signal: PIO2_3/ENET_TXD2/SD_CLK/FC1_RXD_SDA_MOSI/CTIMER2_MAT0, label: 'U9[3]/P2_3-SD_CLK', identifier: SD_CLK}
- {pin_num: D3, pin_signal: PIO2_4/ENET_TXD3/SD_CMD/FC1_TXD_SCL_MISO/CTIMER2_MAT1, label: 'RP1[6]/U9[2]/P2_4-SD_CMD', identifier: SD_CMD}
- {pin_num: K2, pin_signal: PIO2_9/ENET_RXD3/SD_D(3)/CTIMER0_MAT1, label: 'RP1[7]/U9[1]/P2_9-SD_D3', identifier: SD_D3}
- {pin_num: C1, pin_signal: PIO2_5/ENET_TX_ER/SD_POW_EN/FC1_CTS_SDA_SSEL0/CTIMER1_MAT2, label: 'Q3[1]/P2_5-SD_POW_EN', identifier: SD_POW_EN}
- {pin_num: P9, pin_signal: PIO3_25/CTIMER4_CAP2/FC4_SCK/EMC_A(14), label: 'U28[G8]/P3_25-EMC_A14', identifier: EMC_A14}
- {pin_num: M12, pin_signal: PIO1_25/FC2_TXD_SCL_MISO/SCT0_OUT2/UTICK_CAP0/EMC_A(13), label: 'U28[G7]/P1_25-EMC_A13', identifier: EMC_A13}
- {pin_num: N14, pin_signal: PIO1_24/FC2_RXD_SDA_MOSI/SCT0_OUT1/FC3_SSEL3/EMC_A(12), label: 'U28[G1]/P1_24-EMC_A12', identifier: EMC_A12}
- {pin_num: M10, pin_signal: PIO1_23/FC2_SCK/SCT0_OUT0/ENET_MDIO/FC3_SSEL2/EMC_A(11), label: 'U28[G2]/P1_23-EMC_A11', identifier: EMC_A11}
- {pin_num: B7, pin_signal: PIO1_16/ENET_MDC/FC6_TXD_SCL_MISO_WS/CTIMER1_MAT3/SD_CMD/EMC_A(10), label: 'U28[H9]/P1_16-EMC_A10', identifier: EMC_A10}
- {pin_num: F10, pin_signal: PIO1_27/FC2_RTS_SCL_SSEL1/SD_D(4)/CTIMER0_MAT3/CLKOUT/EMC_A(9), label: 'U28[G3]/P1_27-EMC_A9', identifier: EMC_A9}
- {pin_num: J10, pin_signal: PIO1_26/FC2_CTS_SDA_SSEL0/SCT0_OUT3/CTIMER0_CAP3/UTICK_CAP1/EMC_A(8), label: 'U28[H1]/P1_26-EMC_A8', identifier: EMC_A8}
- {pin_num: P8, pin_signal: PIO1_8/FC0_CTS_SDA_SSEL0/SD_CLK/SCT0_OUT1/FC4_SSEL2/EMC_A(7), label: 'U28[H2]/P1_8-EMC_A7', identifier: EMC_A7}
- {pin_num: N1, pin_signal: PIO1_7/FC0_RTS_SCL_SSEL1/SD_D(1)/CTIMER2_MAT2/SCT0_GPI4/EMC_A(6), label: 'U28[H3]/P1_7-EMC_A6', identifier: EMC_A6}
- {pin_num: G4, pin_signal: PIO1_6/FC0_TXD_SCL_MISO/SD_D(3)/CTIMER2_MAT1/SCT0_GPI3/EMC_A(5), label: 'U28[J2]/P1_6-EMC_A5', identifier: EMC_A5}
- {pin_num: E4, pin_signal: PIO1_5/FC0_RXD_SDA_MOSI/SD_D(2)/CTIMER2_MAT0/SCT0_GPI0/EMC_A(4), label: 'U28[J3]/P1_5-EMC_A4', identifier: EMC_A4}
- {pin_num: C13, pin_signal: PIO0_21/FC3_RTS_SCL_SSEL1/UTICK_CAP3/CTIMER3_MAT3/SCT0_GPI3/SCI0_SCLK/EMC_A(3)/FC7_SCK, label: 'U28[J7]/P0_21-EMC_A3', identifier: EMC_A3}
- {pin_num: D13, pin_signal: PIO0_20/FC3_CTS_SDA_SSEL0/CTIMER1_MAT1/CTIMER3_CAP3/SCT0_GPI2/SCI0_IO/EMC_A(2)/FC7_RXD_SDA_MOSI_DATA, label: 'U28[J8]/P0_20-EMC_A2',
  identifier: EMC_A2}
- {pin_num: C6, pin_signal: PIO0_19/FC4_RTS_SCL_SSEL1/UTICK_CAP0/CTIMER0_MAT2/SCT0_OUT2/EMC_A(1)/FC7_TXD_SCL_MISO_WS, label: 'U28[H8]/P0_19-EMC_A1', identifier: EMC_A1}
- {pin_num: C14, pin_signal: PIO0_18/FC4_CTS_SDA_SSEL0/SD_WR_PRT/CTIMER1_MAT0/SCT0_OUT1/SCI1_SCLK/EMC_A(0), label: 'U28[H7]/P0_18-EMC_A0', identifier: EMC_A0}
- {pin_num: L4, pin_signal: PIO0_15/FC6_CTS_SDA_SSEL0/UTICK_CAP2/CTIMER4_CAP0/SCT0_OUT2/EMC_WEN/ENET_TX_EN/ADC0_3, label: 'U28[F9]/P0_15-EMC_WEn', identifier: EMC_WEn}
- {pin_num: K6, pin_signal: PIO1_9/ENET_TXD0/FC1_SCK/CTIMER1_CAP0/SCT0_OUT2/FC4_CTS_SDA_SSEL0/EMC_CASN, label: 'U28[F7]/P1_9-EMC_CASn', identifier: EMC_CASn}
- {pin_num: N9, pin_signal: PIO1_10/ENET_TXD1/FC1_RXD_SDA_MOSI/CTIMER1_MAT0/SCT0_OUT3/EMC_RASN, label: 'U28[F8]/P1_10-EMC_RASn', identifier: EMC_RASn}
- {pin_num: K9, pin_signal: PIO1_12/ENET_RXD0/FC6_SCK/CTIMER1_MAT1/USB0_PORTPWRN/EMC_DYCSN(0), label: 'U28[G9]/P1_12-EMC_DYCSn0', identifier: EMC_DYCSn0}
- {pin_num: C5, pin_signal: PIO1_31/MCLK/CTIMER0_MAT2/SCT0_OUT6/FC8_CTS_SDA_SSEL0/EMC_D(15), label: 'U28[A2]/RP2[1]/P1_31-EMC_D15', identifier: EMC_D15}
- {pin_num: A8, pin_signal: PIO1_30/FC7_TXD_SCL_MISO_WS/SD_D(7)/SCT0_GPI7/USB1_OVERCURRENTN/USB1_UP_LED/EMC_D(14), label: 'U28[B1]/RP2[2]/P1_30-EMC_D14', identifier: EMC_D14}
- {pin_num: C11, pin_signal: PIO1_29/FC7_RXD_SDA_MOSI_DATA/SD_D(6)/SCT0_GPI6/USB1_PORTPWRN/USB1_FRAME/EMC_D(13), label: 'U28[B2]/RP2[3]/P1_29-EMC_D13', identifier: EMC_D13}
- {pin_num: E12, pin_signal: PIO1_28/FC7_SCK/SD_D(5)/CTIMER0_CAP2/EMC_D(12), label: 'U28[C1]/RP2[4]/P1_28-EMC_D12', identifier: EMC_D12}
- {pin_num: D4, pin_signal: PIO1_4/FC0_SCK/SD_D(0)/CTIMER2_MAT1/SCT0_OUT0/FREQME_GPIO_CLK_A/EMC_D(11), label: 'U28[C2]/RP4[1]/P1_4-EMC_D11', identifier: EMC_D11}
- {pin_num: N8, pin_signal: PIO1_21/FC7_CTS_SDA_SSEL0/CTIMER3_MAT2/FC4_RXD_SDA_MOSI/EMC_D(10), label: 'U28[D1]/RP4[2]/P1_21-EMC_D10', identifier: EMC_D10}
- {pin_num: M1, pin_signal: PIO1_20/FC7_RTS_SCL_SSEL1/CTIMER3_CAP2/FC4_TXD_SCL_MISO/EMC_D(9), label: 'U28[D2]/RP4[3]/P1_20-EMC_D9', identifier: EMC_D9}
- {pin_num: L1, pin_signal: PIO1_19/FC8_SCK/SCT0_OUT7/CTIMER3_MAT1/SCT0_GPI7/FC4_SCK/EMC_D(8), label: 'U28[E1]/RP4[4]/P1_19-EMC_D8', identifier: EMC_D8}
- {pin_num: G12, pin_signal: PIO0_9/FC3_SSEL2/SD_POW_EN/FC5_TXD_SCL_MISO/SCI1_IO/EMC_D(7), label: 'U28[E9]/RP5[1]/P0_9-EMC_D7', identifier: EMC_D7}
- {pin_num: H10, pin_signal: PIO0_8/FC3_SSEL3/SD_CMD/FC5_RXD_SDA_MOSI/SWO/PDM1_DATA/EMC_D(6), label: 'U28[D8]/RP5[2]/P0_8-EMC_D6', identifier: EMC_D6}
- {pin_num: H12, pin_signal: PIO0_7/FC3_RTS_SCL_SSEL1/SD_CLK/FC5_SCK/FC1_SCK/PDM1_CLK/EMC_D(5)/ENET_RX_CLK, label: 'U28[D9]/RP5[3]/P0_7-EMC_D5', identifier: EMC_D5}
- {pin_num: A5, pin_signal: PIO0_6/FC3_SCK/CTIMER3_CAP1/CTIMER4_MAT0/SCT0_GPI6/EMC_D(4)/ENET_RX_DV, label: 'U28[C8]/RP5[4]/SW2/P0_6-ISP2/P0_6-EMC_D4', identifier: SW2;EMC_D4}
- {pin_num: C12, pin_signal: PIO1_14/ENET_RX_DV/UTICK_CAP2/CTIMER1_MAT2/FC5_CTS_SDA_SSEL0/USB0_UP_LED/EMC_DQM(1), label: 'U28[F1]/P1_14-EMC_DQM1', identifier: EMC_DQM1}
- {pin_num: G10, pin_signal: PIO1_13/ENET_RXD1/FC6_RXD_SDA_MOSI_DATA/CTIMER1_CAP2/USB0_OVERCURRENTN/USB0_FRAME/EMC_DQM(0), label: 'U28[E8]/P1_13-EMC_DQM0', identifier: EMC_DQM0}
- {pin_num: B4, pin_signal: PIO1_11/ENET_TX_EN/FC1_TXD_SCL_MISO/CTIMER1_CAP1/USB0_VBUS/EMC_CLK(0), label: 'U28[F2]/P1_11-EMC_CLK0', identifier: EMC_CLK0}
- {pin_num: A11, pin_signal: PIO1_15/ENET_RX_CLK/UTICK_CAP3/CTIMER1_CAP3/FC5_RTS_SCL_SSEL1/FC4_RTS_SCL_SSEL1/EMC_CKE(0), label: 'U28[F3]/P1_15-EMC_CKE0', identifier: EMC_CKE0}
- {pin_num: H3, pin_signal: USB1_DP, label: 'J2[3]/U2[2]/U25[H3]/USB1_DP_TRGT', identifier: USB1_DP}
- {pin_num: H2, pin_signal: USB1_DM, label: 'J2[2]/U2[3]/U25[H2]/USB1_DM_TRGT', identifier: USB1_DM}
- {pin_num: D5, pin_signal: USB0_DM, label: 'J3[2]/U3[3]/USB0_DM_TRGT', identifier: USB0_DM}
- {pin_num: E5, pin_signal: USB0_DP, label: 'J3[3]/U3[2]/USB0_DP_TRGT', identifier: USB0_DP}
- {pin_num: B12, pin_signal: PIO0_22/FC6_TXD_SCL_MISO_WS/UTICK_CAP1/CTIMER3_CAP3/SCT0_OUT3/USB0_VBUS, label: 'U3[4]/J3[1]/P0_22-USB0_VBUS', identifier: USB0_VBUS}
- {pin_num: G2, pin_signal: USB1_VBUS, label: 'J2[1]/U2[4]/VBUS1_TARGET', identifier: USB1_VBUS}
- {pin_num: G1, pin_signal: USB1_ID, label: 'J2[4]/USB1_ID_TARGET', identifier: USB1_ID}
- {pin_num: A9, pin_signal: PIO4_11/ENET_RXD0/FC2_CTS_SDA_SSEL0/USB0_IDVALUE/SCT0_GPI4, label: 'U12[8]/JP12[1]/J3[4]/JP12[3]/P4_11-USB0_ID/P4_11-ENET_RXD0', identifier: USB0_ID;ENET_RXD0}
- {pin_num: B13, pin_signal: PIO0_29/FC0_RXD_SDA_MOSI/CTIMER2_MAT3/SCT0_OUT8/TRACEDATA(2), label: 'U24[13]/P0_29-ISP_FC0_RXD', identifier: ISP_FC0_RXD}
- {pin_num: A2, pin_signal: PIO0_30/FC0_TXD_SCL_MISO/CTIMER0_MAT0/SCT0_OUT9/TRACEDATA(1), label: 'U24[12]/P0_30-ISP_FC0_TXD', identifier: ISP_FC0_TXD}
- {pin_num: M3, pin_signal: PIO0_12/FC3_TXD_SCL_MISO/FREQME_GPIO_CLK_B/SCT0_GPI7/SWDIO/ADC0_2, label: 'P1[2]/U22[4]/D5[5]/IF_SWDIO', identifier: IF_SWDIO}
- {pin_num: L3, pin_signal: PIO0_11/FC6_RXD_SDA_MOSI_DATA/CTIMER2_MAT2/FREQME_GPIO_CLK_A/SWCLK/ADC0_1, label: 'U16[4]/SWDCLK_TRGT', identifier: SWDCLK_TRGT}
- {pin_num: P2, pin_signal: PIO0_10/FC6_SCK/CTIMER2_CAP2/CTIMER2_MAT0/FC1_TXD_SCL_MISO/SWO/ADC0_0, label: 'U16[12]/SWO_TRGT', identifier: SWO_TRGT}
- {pin_num: L10, pin_signal: PIO2_21/LCD_VD(3)/FC3_CTS_SDA_SSEL0/MCLK/CTIMER3_MAT3, label: 'J16[8]/P2_21-LCD_VD3', identifier: LCD_VD3}
- {pin_num: K10, pin_signal: PIO2_22/LCD_VD(4)/SCT0_OUT7/CTIMER2_CAP0, label: 'J16[9]/P2_22-LCD_VD4', identifier: LCD_VD4}
- {pin_num: M14, pin_signal: PIO2_23/LCD_VD(5)/SCT0_OUT8, label: 'J16[10]/P2_23-LCD_VD5', identifier: LCD_VD5}
- {pin_num: K14, pin_signal: PIO2_24/LCD_VD(6)/SCT0_OUT9, label: 'J16[11]/P2_24-LCD_VD6', identifier: LCD_VD6}
- {pin_num: J11, pin_signal: PIO2_25/LCD_VD(7)/USB0_VBUS, label: 'J16[12]/P2_25-LCD_VD7', identifier: LCD_VD7}
- {pin_num: G13, pin_signal: PIO2_28/LCD_VD(10)/FC7_CTS_SDA_SSEL0/CTIMER2_CAP2, label: 'J16[15]/P2_28-LCD_VD10', identifier: LCD_VD10}
- {pin_num: G11, pin_signal: PIO2_29/LCD_VD(11)/FC7_RTS_SCL_SSEL1/FC8_TXD_SCL_MISO/CTIMER2_CAP3/CLKOUT, label: 'J16[16]/P2_29-LCD_VD11', identifier: LCD_VD11}
- {pin_num: F12, pin_signal: PIO2_30/LCD_VD(12)/CTIMER2_MAT2, label: 'J16[17]/P2_30-LCD_VD12', identifier: LCD_VD12}
- {pin_num: D14, pin_signal: PIO2_31/LCD_VD(13), label: 'J16[18]/P2_31-LCD_VD13', identifier: LCD_VD13}
- {pin_num: D12, pin_signal: PIO3_0/LCD_VD(14)/PDM0_CLK/CTIMER1_MAT0, label: 'J16[19]/JS36[1]/P3_0-LCD_VD14', identifier: LCD_VD14}
- {pin_num: D11, pin_signal: PIO3_1/LCD_VD(15)/PDM0_DATA/CTIMER1_MAT1, label: 'J16[20]/JS33[1]/P3_1-LCD_VD15', identifier: LCD_VD15}
- {pin_num: B10, pin_signal: PIO3_5/LCD_VD(19)/FC8_RTS_SCL_SSEL1/CTIMER4_MAT1, label: 'J16[24]/P3_5-LCD_VD19', identifier: LCD_VD19}
- {pin_num: C9, pin_signal: PIO3_6/LCD_VD(20)/LCD_VD(0)/CTIMER4_MAT2, label: 'J16[25]/P3_6-LCD_VD20', identifier: LCD_VD20}
- {pin_num: B8, pin_signal: PIO3_7/LCD_VD(21)/LCD_VD(1)/CTIMER4_CAP2, label: 'J16[26]/P3_7-LCD_VD21', identifier: LCD_VD21}
- {pin_num: A7, pin_signal: PIO3_8/LCD_VD(22)/LCD_VD(2)/CTIMER4_CAP3, label: 'J16[27]/P3_8-LCD_VD22', identifier: LCD_VD22}
- {pin_num: C7, pin_signal: PIO3_9/LCD_VD(23)/LCD_VD(3)/CTIMER0_CAP2, label: 'J16[28]/P3_9-LCD_VD23', identifier: LCD_VD23}
- {pin_num: P7, pin_signal: PIO2_13/LCD_DCLK/SD_VOLT(2)/FC5_TXD_SCL_MISO, label: 'J16[30]/P2_13-LCD_DCLK', identifier: LCD_DCLK}
- {pin_num: K3, pin_signal: PIO2_11/LCD_PWR/SD_VOLT(0)/FC5_SCK, label: 'J16[31]/P2_11-LCD_PWR', identifier: LCD_PWR}
- {pin_num: L8, pin_signal: PIO2_16/LCD_LP/USB1_FRAME/USB1_PORTPWRN/CTIMER1_MAT3/FC8_SCK, label: 'J16[32]/P2_16-LCD_LP', identifier: LCD_LP}
- {pin_num: L7, pin_signal: PIO2_14/LCD_FP/USB0_FRAME/USB0_PORTPWRN/CTIMER0_MAT2/FC5_CTS_SDA_SSEL0, label: 'J16[33]/P2_14-LCD_FP', identifier: LCD_FP}
- {pin_num: M8, pin_signal: PIO2_15/LCD_AC/USB0_UP_LED/USB0_OVERCURRENTN/CTIMER0_MAT3/FC5_RTS_SCL_SSEL1, label: 'J16[34]/P2_15-LCD_AC_ENAB_M', identifier: LCD_AC_ENAB_M}
- {pin_num: B14, pin_signal: PIO4_8/ENET_TXD0/FC2_SCK/USB0_OVERCURRENTN/USB0_UP_LED/SCT0_GPI1, label: 'U12[17]/JP11[1]/P4_8-ENET_TXD0', identifier: ENET_TXD0}
- {pin_num: E14, pin_signal: PIO0_17/FC4_SSEL2/SD_CARD_DET_N/SCT0_GPI7/SCT0_OUT0/EMC_OEN/ENET_TXD1, label: 'U12[18]/P0_17-ENET_TXD1', identifier: ENET_TXD1}
- {pin_num: B6, pin_signal: PIO4_13/ENET_TX_EN/CTIMER4_MAT0/SCT0_GPI6, label: 'U12[16]/P4_13-ENET_TX_EN', identifier: ENET_TX_EN}
- {pin_num: A6, pin_signal: PIO4_12/ENET_RXD1/FC2_RTS_SCL_SSEL1/SCT0_GPI5, label: 'U12[7]/P4_12-ENET_RXD1', identifier: ENET_RXD1}
- {pin_num: B9, pin_signal: PIO4_10/ENET_RX_DV/FC2_TXD_SCL_MISO/USB1_OVERCURRENTN/USB1_UP_LED/SCT0_GPI3, label: 'U12[11]/P4_10-ENET_CRS_DV', identifier: ENET_CRS_DV}
- {pin_num: C4, pin_signal: PIO4_16/ENET_MDIO/CTIMER4_MAT3/FC9_TXD_SCL_MISO, label: 'U12[12]/P4_16-ENET_MDIO', identifier: ENET_MDIO}
- {pin_num: A4, pin_signal: PIO4_15/ENET_MDC/CTIMER4_MAT2/FC9_RXD_SDA_MOSI, label: 'U12[13]/P4_15-ENET_MDC', identifier: ENET_MDC}
- {pin_num: H11, pin_signal: PIO2_26/LCD_VD(8)/FC3_SCK/CTIMER2_CAP1, label: 'U12[15]/P2_26-ENET_PHY_RSTn', identifier: ENET_PHY_RSTn}
- {pin_num: B5, pin_signal: PIO4_14/ENET_RX_CLK/CTIMER4_MAT1/FC9_SCK/SCT0_GPI7, label: 'JS18[2]/P4_14-ENET_RX_CLK', identifier: ENET_RX_CLK}
- {pin_num: L14, pin_signal: PIO1_2/CAN0_TD/CTIMER0_MAT3/SCT0_GPI6/PDM1_CLK/USB1_PORTPWRN, label: 'J13[18]/JS25[3]/DMIC1[4]/P1_2-PDM1_CLK', identifier: PDM1_CLK}
- {pin_num: J13, pin_signal: PIO1_3/CAN0_RD/SCT0_OUT4/PDM1_DATA/USB0_PORTPWRN, label: 'JS26[3]/DMIC1[1]/P1_3-PDM1_DATA', identifier: PDM1_DATA}
- {pin_num: G14, pin_signal: PIO4_1/FC6_SCK/SCT0_GPI2/EMC_CSN(2), label: 'U10[29]/J9[14]/P4_1-FC6_I2S_TX_SCK', identifier: FC6_I2S_TX_SCK}
- {pin_num: F13, pin_signal: PIO4_3/FC6_TXD_SCL_MISO_WS/CTIMER0_CAP3/SCT0_GPI4/EMC_DYCSN(2), label: 'U10[30]/J9[12]/P4_3-FC6_I2S_TX_WS', identifier: FC6_I2S_TX_WS}
- {pin_num: F14, pin_signal: PIO4_2/FC6_RXD_SDA_MOSI_DATA/SCT0_GPI3/EMC_CSN(3), label: 'U10[32]/J9[10]/P4_2-FC6_I2S_TX_DATA', identifier: FC6_I2S_TX_DATA}
- {pin_num: P12, pin_signal: PIO2_19/LCD_VD(1)/FC3_TXD_SCL_MISO/FC7_RXD_SDA_MOSI_DATA/CTIMER3_MAT1, label: 'U10[31]/J9[20]/P2_19-FC7_I2S_RX_DAT', identifier: FC7_I2S_RX_DAT}
- {pin_num: N10, pin_signal: PIO2_18/LCD_VD(0)/FC3_RXD_SDA_MOSI/FC7_SCK/CTIMER3_MAT0, label: 'U10[29]/J9[16]/P2_18-FC7_I2S_RX_SCK', identifier: FC7_I2S_RX_SCK}
- {pin_num: P13, pin_signal: PIO2_20/LCD_VD(2)/FC3_RTS_SCL_SSEL1/FC7_TXD_SCL_MISO_WS/CTIMER3_MAT2/CTIMER4_CAP0, label: 'U10[30]/J9[18]/P2_20-FC7_I2S_RX_WS', identifier: FC7_I2S_RX_WS}
- {pin_num: B2, pin_signal: PIO3_11/MCLK/FC0_SCK/FC1_SCK/TRACEDATA(3), label: 'J11[8]/J12[7]/P3_11-MCLK-PMOD2_GPIO', identifier: MCLK}
- {pin_num: D1, pin_signal: PIO1_18/FC8_TXD_SCL_MISO/SCT0_OUT5/CAN1_RD/EMC_BLSN(1), label: 'J9[2]/P1_18-CAN1_RD'}
- {pin_num: M4, pin_signal: PIO0_16/FC4_TXD_SCL_MISO/CLKOUT/CTIMER1_CAP0/EMC_CSN(0)/ENET_TXD0/ADC0_4, label: 'J12[2]/P0_16-ADC0IN4'}
- {pin_num: M5, pin_signal: PIO0_31/FC0_CTS_SDA_SSEL0/SD_D(2)/CTIMER0_MAT1/SCT0_OUT3/TRACEDATA(0)/ADC0_5, label: 'J12[4]/P0_31-ADC0IN5'}
- {pin_num: N3, pin_signal: PIO1_0/FC0_RTS_SCL_SSEL1/SD_D(3)/CTIMER0_CAP2/SCT0_GPI4/TRACECLK/ADC0_6, label: 'J12[6]/P0_31-ADC0IN5'}
- {pin_num: N12, pin_signal: PIO1_17/ENET_MDIO/FC8_RXD_SDA_MOSI/SCT0_OUT4/CAN1_TD/EMC_BLSN(0), label: 'J9[4]/P1_17-CAN1_TD'}
- {pin_num: P11, pin_signal: PIO1_22/FC8_RTS_SCL_SSEL1/SD_CMD/CTIMER2_MAT3/SCT0_GPI5/FC4_SSEL3/EMC_CKE(1), label: 'J13[1]/P1_22-CT2MAT3'}
- {pin_num: P3, pin_signal: PIO2_0/FC0_RXD_SDA_MOSI/CTIMER1_CAP0/ADC0_7, label: 'J12[8]/P2_0-ADC0IN7-PMOD2_INTR'}
- {pin_num: P4, pin_signal: PIO2_1/FC0_TXD_SCL_MISO/CTIMER1_MAT0/ADC0_8, label: 'J9[17]/P2_1-CT1MAT0'}
- {pin_num: P10, pin_signal: PIO2_17/LCD_CLKIN/USB1_UP_LED/USB1_OVERCURRENTN/CTIMER1_CAP1/FC8_RXD_SDA_MOSI, label: 'J13[20]/P2_17-CT1CAP1-FC8_RXD'}
- {pin_num: H14, pin_signal: PIO2_27/LCD_VD(9)/FC9_SCK/FC3_SSEL2, label: 'J17[2]/P2_27-CT_RSTn'}
- {pin_num: C10, pin_signal: PIO3_2/LCD_VD(16)/FC9_RXD_SDA_MOSI/CTIMER1_MAT2, label: 'J13[11]/P3_2-FC9_MOSI-CT1MAT2'}
- {pin_num: A3, pin_signal: PIO3_10/SCT0_OUT3/CTIMER3_MAT0/EMC_DYCSN(1)/TRACEDATA(0), label: 'J13[7]/P3_10-CT3MAT0'}
- {pin_num: L2, pin_signal: PIO3_12/SCT0_OUT8/CTIMER3_CAP0/CLKOUT/EMC_CLK(1)/TRACECLK, label: 'J12[9]/P3_12-CLKOUT'}
- {pin_num: E1, pin_signal: PIO3_16/FC8_RXD_SDA_MOSI/SD_D(4), label: 'J12[3]/P3_16-GPIO_SPI_CS2'}
- {pin_num: K1, pin_signal: PIO3_17/FC8_TXD_SCL_MISO/SD_D(5), label: 'JS25[1]/P3_17-FC8_TXD'}
- {pin_num: M6, pin_signal: PIO3_18/FC8_CTS_SDA_SSEL0/SD_D(6)/CTIMER4_MAT0/CAN0_TD/SCT0_OUT5, label: 'J10[4]/P3_17-FC8_TXD'}
- {pin_num: J3, pin_signal: PIO3_19/FC8_RTS_SCL_SSEL1/SD_D(7)/CTIMER4_MAT1/CAN0_RD/SCT0_OUT6, label: 'J10[2]/P3_19-CAN0_RD'}
- {pin_num: N2, pin_signal: PIO3_20/FC9_SCK/SD_CARD_INT_N/CLKOUT/SCT0_OUT7, label: 'J9[9]/P3_20-FC9_SCK'}
- {pin_num: P5, pin_signal: PIO3_21/FC9_RXD_SDA_MOSI/SD_BACKEND_PWR/CTIMER4_MAT3/UTICK_CAP2/ADC0_9, label: 'J9[13]/P3_21-FC9_MOSI'}
- {pin_num: N5, pin_signal: PIO3_22/FC9_TXD_SCL_MISO/ADC0_10, label: 'J9[11]/P3_21-FC9_MISO'}
- {pin_num: K5, pin_signal: PIO3_26/SCT0_OUT0/FC4_RXD_SDA_MOSI/EMC_A(15), label: 'J13[15]/P3_26-FC4_RXD'}
- {pin_num: P14, pin_signal: PIO3_27/SCT0_OUT1/FC4_TXD_SCL_MISO/EMC_A(16), label: 'J13[13]/P3_26-FC4_TXD'}
- {pin_num: M11, pin_signal: PIO3_28/SCT0_OUT2/FC4_CTS_SDA_SSEL0/EMC_A(17), label: 'JS26[1]/P3_28-FC4_CTS_SDAX'}
- {pin_num: L13, pin_signal: PIO3_29/SCT0_OUT3/FC4_RTS_SCL_SSEL1/EMC_A(18), label: 'J13[14]/P3_29-FC4_RTS_SCLX'}
- {pin_num: K13, pin_signal: PIO3_30/FC9_CTS_SDA_SSEL0/SCT0_OUT4/FC4_SSEL2/EMC_A(19), label: 'J9[15]/P3_30-FC9_SSELn0'}
- {pin_num: J14, pin_signal: PIO3_31/FC9_RTS_SCL_SSEL1/SCT0_OUT5/CTIMER4_MAT2/SCT0_GPI0/EMC_A(20), label: 'U14[4]/P3_31-SCT0_OUT5_CT4MAT2'}
- {pin_num: H13, pin_signal: PIO4_0/FC6_CTS_SDA_SSEL0/CTIMER4_CAP1/SCT0_GPI1/EMC_CSN(1), label: 'J17[3]/P4_0-CT_INTR'}
- {pin_num: D9, pin_signal: PIO4_4/FC4_SSEL3/FC0_RTS_SCL_SSEL1/SCT0_GPI5/EMC_DYCSN(3), label: 'J13[19]/P4_4'}
- {pin_num: E10, pin_signal: PIO4_5/FC9_CTS_SDA_SSEL0/FC0_CTS_SDA_SSEL0/CTIMER4_MAT3/SCT0_GPI6/EMC_CKE(2), label: 'J13[9]/P4_5-CT4MAT3'}
- {pin_num: D10, pin_signal: PIO4_6/FC9_RTS_SCL_SSEL1/SCT0_GPI7/EMC_CKE(3), label: 'J12[1]/P4_6-FC9_SSELn1'}
- {pin_num: A14, pin_signal: PIO4_7/CTIMER4_CAP3/USB0_PORTPWRN/USB0_FRAME/SCT0_GPI0, label: P4_7}
- {pin_num: A12, pin_signal: PIO4_9/ENET_TXD1/FC2_RXD_SDA_MOSI/USB1_PORTPWRN/USB1_FRAME/SCT0_GPI2, label: 'U29[2]/P4_9-USB1_PORTPWRn'}
- {pin_num: N13, pin_signal: RESET, label: 'J15[1]/nRESET_TRGT'}
- {pin_num: L12, pin_signal: RTCXIN, label: Y4}
- {pin_num: K11, pin_signal: RTCXOUT, label: Y4}
- {pin_num: G3, pin_signal: USB1_AVDD0, label: +3.3V_USB_ENET}
- {pin_num: H1, pin_signal: USB1_AVDD1, label: +3.3V_USB_ENET}
- {pin_num: F2, pin_signal: USB1_AVSSC, label: GND}
- {pin_num: J1, pin_signal: USB1_AVSSTX3V3, label: GND}
- {pin_num: F1, pin_signal: USB1_REXT, label: GND}
- {pin_num: N11, pin_signal: VBAT0, label: VDD_TARGE}
- {pin_num: H5, pin_signal: VD1_00, label: JS22}
- {pin_num: E6, pin_signal: VDD0, label: VDD_TARGET_IC}
- {pin_num: E8, pin_signal: VDD1, label: VDD_TARGET_IC}
- {pin_num: F5, pin_signal: VDD2, label: VDD_TARGET_IC}
- {pin_num: G5, pin_signal: VDD3, label: VDD_TARGET_IC}
- {pin_num: J12, pin_signal: VDD4, label: VDD_TARGET_IC}
- {pin_num: L11, pin_signal: VDD5, label: VDD_TARGET_IC}
- {pin_num: N6, pin_signal: VDDA, label: VDD_TARGET}
- {pin_num: L6, pin_signal: VPP0, label: VDD_TARGET_IC}
- {pin_num: P6, pin_signal: VREFP, label: 'JS23[1]'}
- {pin_num: N4, pin_signal: VREFN, label: 'JS22[2]'}
- {pin_num: B3, pin_signal: VSS0, label: GND}
- {pin_num: D7, pin_signal: VSS1, label: GND}
- {pin_num: D8, pin_signal: VSS2, label: GND}
- {pin_num: E11, pin_signal: VSS3, label: GND}
- {pin_num: J5, pin_signal: VSS4, label: GND}
- {pin_num: L5, pin_signal: VSSA, label: GND}
- {pin_num: K4, pin_signal: XTAL1, label: Y2}
- {pin_num: J4, pin_signal: XTAL2, label: Y2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
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
  - {pin_num: P2, peripheral: SWD, signal: SWO, pin_signal: PIO0_10/FC6_SCK/CTIMER2_CAP2/CTIMER2_MAT0/FC1_TXD_SCL_MISO/SWO/ADC0_0, identifier: '', mode: inactive}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][10] = ((IOCON->PIO[0][10] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT010 (pin P2) is configured as SWO. */
                         | IOCON_PIO_FUNC(PIO010_FUNC_ALT6)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Inactive.
                          * Inactive (no pull-down/pull-up resistor enabled). */
                         | IOCON_PIO_MODE(PIO010_MODE_INACTIVE)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO010_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitBUTTONsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: A5, peripheral: GPIO, signal: 'PIO0, 6', pin_signal: PIO0_6/FC3_SCK/CTIMER3_CAP1/CTIMER4_MAT0/SCT0_GPI6/EMC_D(4)/ENET_RX_DV, identifier: SW2, direction: INPUT}
  - {pin_num: E7, peripheral: GPIO, signal: 'PIO0, 5', pin_signal: PIO0_5/CAN0_TD/FC4_RXD_SDA_MOSI/CTIMER3_MAT0/SCT0_GPI5/EMC_D(3)/ENET_MDIO, identifier: SW3, direction: INPUT}
  - {pin_num: C8, peripheral: GPIO, signal: 'PIO0, 4', pin_signal: PIO0_4/CAN0_RD/FC4_SCK/CTIMER3_CAP0/SCT0_GPI4/EMC_D(2)/ENET_MDC, identifier: SW4, direction: INPUT}
  - {pin_num: K12, peripheral: GPIO, signal: 'PIO1, 1', pin_signal: PIO1_1/FC3_RXD_SDA_MOSI/CTIMER0_CAP3/SCT0_GPI5/USB1_OVERCURRENTN, direction: INPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBUTTONsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitBUTTONsPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);
    /* Enables the clock for the GPIO1 module */
    CLOCK_EnableClock(kCLOCK_Gpio1);

    gpio_pin_config_t SW4_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_4 (pin C8)  */
    GPIO_PinInit(BOARD_SW4_GPIO, BOARD_SW4_PORT, BOARD_SW4_PIN, &SW4_config);

    gpio_pin_config_t SW3_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_5 (pin E7)  */
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_PORT, BOARD_SW3_PIN, &SW3_config);

    gpio_pin_config_t SW2_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_6 (pin A5)  */
    GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_PORT, BOARD_SW2_PIN, &SW2_config);

    gpio_pin_config_t SW5_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO1_1 (pin K12)  */
    GPIO_PinInit(BOARD_SW5_GPIO, BOARD_SW5_PORT, BOARD_SW5_PIN, &SW5_config);

    IOCON->PIO[0][4] = ((IOCON->PIO[0][4] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT04 (pin C8) is configured as PIO0_4. */
                        | IOCON_PIO_FUNC(PIO04_FUNC_ALT0)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO04_DIGIMODE_DIGITAL));

    IOCON->PIO[0][5] = ((IOCON->PIO[0][5] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT05 (pin E7) is configured as PIO0_5. */
                        | IOCON_PIO_FUNC(PIO05_FUNC_ALT0)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO05_DIGIMODE_DIGITAL));

    IOCON->PIO[0][6] = ((IOCON->PIO[0][6] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT06 (pin A5) is configured as PIO0_6. */
                        | IOCON_PIO_FUNC(PIO06_FUNC_ALT0)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO06_DIGIMODE_DIGITAL));

    IOCON->PIO[1][1] = ((IOCON->PIO[1][1] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT11 (pin K12) is configured as PIO1_1. */
                        | IOCON_PIO_FUNC(PIO11_FUNC_ALT0)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO11_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDsPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: A13, peripheral: GPIO, signal: 'PIO3, 3', pin_signal: PIO3_3/LCD_VD(17)/FC9_TXD_SCL_MISO, direction: OUTPUT}
  - {pin_num: C3, peripheral: GPIO, signal: 'PIO2, 2', pin_signal: PIO2_2/ENET_CRS/FC3_SSEL3/SCT0_OUT6/CTIMER1_MAT1, direction: OUTPUT}
  - {pin_num: E3, peripheral: GPIO, signal: 'PIO3, 14', pin_signal: PIO3_14/SCT0_OUT4/FC9_RTS_SCL_SSEL1/CTIMER3_MAT1/TRACEDATA(2), direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLEDsPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitLEDsPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO2 module */
    CLOCK_EnableClock(kCLOCK_Gpio2);
    /* Enables the clock for the GPIO3 module */
    CLOCK_EnableClock(kCLOCK_Gpio3);

    gpio_pin_config_t LED3_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO2_2 (pin C3)  */
    GPIO_PinInit(BOARD_LED3_GPIO, BOARD_LED3_PORT, BOARD_LED3_PIN, &LED3_config);

    gpio_pin_config_t LED2_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO3_3 (pin A13)  */
    GPIO_PinInit(BOARD_LED2_GPIO, BOARD_LED2_PORT, BOARD_LED2_PIN, &LED2_config);

    gpio_pin_config_t LED1_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO3_14 (pin E3)  */
    GPIO_PinInit(BOARD_LED1_GPIO, BOARD_LED1_PORT, BOARD_LED1_PIN, &LED1_config);

    IOCON->PIO[2][2] = ((IOCON->PIO[2][2] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT22 (pin C3) is configured as PIO2_2. */
                        | IOCON_PIO_FUNC(PIO22_FUNC_ALT0)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO22_DIGIMODE_DIGITAL));

    IOCON->PIO[3][14] = ((IOCON->PIO[3][14] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT314 (pin E3) is configured as PIO3_14. */
                         | IOCON_PIO_FUNC(PIO314_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO314_DIGIMODE_DIGITAL));

    IOCON->PIO[3][3] = ((IOCON->PIO[3][3] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT33 (pin A13) is configured as PIO3_3. */
                        | IOCON_PIO_FUNC(PIO33_FUNC_ALT0)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO33_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPMod_SPI_I2C_BRIDGEPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: A1, peripheral: FLEXCOMM3, signal: CTS_SDA_SSEL0, pin_signal: PIO0_1/CAN1_TD/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_GPI1/PDM0_DATA, direction: OUTPUT}
  - {pin_num: A10, peripheral: FLEXCOMM3, signal: RXD_SDA_MOSI, pin_signal: PIO0_3/FC3_RXD_SDA_MOSI/CTIMER0_MAT1/SCT0_OUT1/SCT0_GPI3/EMC_D(1), identifier: ISP_FC3_MOSI,
    direction: OUTPUT}
  - {pin_num: E9, peripheral: FLEXCOMM3, signal: TXD_SCL_MISO, pin_signal: PIO0_2/FC3_TXD_SCL_MISO/CTIMER0_CAP1/SCT0_OUT0/SCT0_GPI2/EMC_D(0), identifier: ISP_FC3_MISO,
    direction: INPUT}
  - {pin_num: D6, peripheral: FLEXCOMM3, signal: SCK, pin_signal: PIO0_0/CAN1_RD/FC3_SCK/CTIMER0_MAT0/SCT0_GPI0/PDM0_CLK, direction: OUTPUT}
  - {pin_num: H4, peripheral: GPIO, signal: 'PIO3, 13', pin_signal: PIO3_13/SCT0_OUT9/FC9_CTS_SDA_SSEL0/CTIMER3_CAP1/EMC_FBCK/TRACEDATA(1)}
  - {pin_num: F11, peripheral: FLEXCOMM1, signal: CTS_SDA_SSEL0, pin_signal: PIO0_13/FC1_CTS_SDA_SSEL0/UTICK_CAP0/CTIMER0_CAP0/SCT0_GPI0/ENET_RXD0}
  - {pin_num: E13, peripheral: FLEXCOMM1, signal: RTS_SCL_SSEL1, pin_signal: PIO0_14/FC1_RTS_SCL_SSEL1/UTICK_CAP1/CTIMER0_CAP1/SCT0_GPI1/ENET_RXD1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPMod_SPI_I2C_BRIDGEPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitPMod_SPI_I2C_BRIDGEPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][0] = ((IOCON->PIO[0][0] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT00 (pin D6) is configured as FC3_SCK. */
                        | IOCON_PIO_FUNC(PIO00_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO00_DIGIMODE_DIGITAL));

    IOCON->PIO[0][1] = ((IOCON->PIO[0][1] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT01 (pin A1) is configured as FC3_CTS_SDA_SSEL0. */
                        | IOCON_PIO_FUNC(PIO01_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO01_DIGIMODE_DIGITAL));

    IOCON->PIO[0][13] = ((IOCON->PIO[0][13] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT013 (pin F11) is configured as FC1_CTS_SDA_SSEL0. */
                         | IOCON_PIO_FUNC(PIO013_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO013_DIGIMODE_DIGITAL));

    IOCON->PIO[0][14] = ((IOCON->PIO[0][14] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT014 (pin E13) is configured as FC1_RTS_SCL_SSEL1. */
                         | IOCON_PIO_FUNC(PIO014_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO014_DIGIMODE_DIGITAL));

    IOCON->PIO[0][2] = ((IOCON->PIO[0][2] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT02 (pin E9) is configured as FC3_TXD_SCL_MISO. */
                        | IOCON_PIO_FUNC(PIO02_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO02_DIGIMODE_DIGITAL));

    IOCON->PIO[0][3] = ((IOCON->PIO[0][3] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT03 (pin A10) is configured as FC3_RXD_SDA_MOSI. */
                        | IOCON_PIO_FUNC(PIO03_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO03_DIGIMODE_DIGITAL));

    IOCON->PIO[3][13] = ((IOCON->PIO[3][13] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT313 (pin H4) is configured as PIO3_13. */
                         | IOCON_PIO_FUNC(PIO313_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO313_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCELPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: C2, peripheral: FLEXCOMM2, signal: CTS_SDA_SSEL0, pin_signal: PIO3_23/FC2_CTS_SDA_SSEL0/UTICK_CAP3}
  - {pin_num: E2, peripheral: FLEXCOMM2, signal: RTS_SCL_SSEL1, pin_signal: PIO3_24/FC2_RTS_SCL_SSEL1/CTIMER4_CAP0/USB0_VBUS}
  - {pin_num: B11, peripheral: GPIO, signal: 'PIO3, 4', pin_signal: PIO3_4/LCD_VD(18)/FC8_CTS_SDA_SSEL0/CTIMER4_CAP1, direction: INPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitACCELPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitACCELPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO3 module */
    CLOCK_EnableClock(kCLOCK_Gpio3);

    gpio_pin_config_t ACCL_INTR_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO3_4 (pin B11)  */
    GPIO_PinInit(BOARD_ACCL_INTR_GPIO, BOARD_ACCL_INTR_PORT, BOARD_ACCL_INTR_PIN, &ACCL_INTR_config);

    IOCON->PIO[3][23] = ((IOCON->PIO[3][23] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT323 (pin C2) is configured as FC2_CTS_SDA_SSEL0. */
                         | IOCON_PIO_FUNC(PIO323_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO323_DIGIMODE_DIGITAL));

    IOCON->PIO[3][24] = ((IOCON->PIO[3][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT324 (pin E2) is configured as FC2_RTS_SCL_SSEL1. */
                         | IOCON_PIO_FUNC(PIO324_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO324_DIGIMODE_DIGITAL));

    IOCON->PIO[3][4] = ((IOCON->PIO[3][4] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT34 (pin B11) is configured as PIO3_4. */
                        | IOCON_PIO_FUNC(PIO34_FUNC_ALT0)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO34_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitQSPI_FLASHPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: M13, peripheral: SPIFI0, signal: SPIFI_SCK, pin_signal: PIO0_26/FC2_RXD_SDA_MOSI/CLKOUT/CTIMER3_CAP2/SCT0_OUT5/PDM0_CLK/SPIFI_CLK/USB0_IDVALUE}
  - {pin_num: M7, peripheral: SPIFI0, signal: SPIFI_IO0/SPIFI_MOSI, pin_signal: PIO0_24/FC0_RXD_SDA_MOSI/SD_D(0)/CTIMER2_CAP0/SCT0_GPI0/SPIFI_IO(0)}
  - {pin_num: K8, peripheral: SPIFI0, signal: SPIFI_IO1/SPIFI_MISO, pin_signal: PIO0_25/FC0_TXD_SCL_MISO/SD_D(1)/CTIMER2_CAP1/SCT0_GPI1/SPIFI_IO(1)}
  - {pin_num: L9, peripheral: SPIFI0, signal: 'SPIFI_IO, 3', pin_signal: PIO0_27/FC2_TXD_SCL_MISO/CTIMER3_MAT2/SCT0_OUT6/PDM0_DATA/SPIFI_IO(3)}
  - {pin_num: M9, peripheral: SPIFI0, signal: 'SPIFI_IO, 2', pin_signal: PIO0_28/FC0_SCK/CTIMER2_CAP3/SCT0_OUT7/TRACEDATA(3)/SPIFI_IO(2)/USB0_OVERCURRENTN}
  - {pin_num: N7, peripheral: SPIFI0, signal: SPIFI_CSN, pin_signal: PIO0_23/MCLK/CTIMER1_MAT2/CTIMER3_MAT3/SCT0_OUT4/SPIFI_CSN/ADC0_11}
  - {pin_num: M2, peripheral: GPIO, signal: 'PIO2, 12', pin_signal: PIO2_12/LCD_LE/SD_VOLT(1)/USB0_IDVALUE/FC5_RXD_SDA_MOSI}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitQSPI_FLASHPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitQSPI_FLASHPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][23] = ((IOCON->PIO[0][23] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT023 (pin N7) is configured as SPIFI_CSN. */
                         | IOCON_PIO_FUNC(PIO023_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO023_DIGIMODE_DIGITAL));

    IOCON->PIO[0][24] = ((IOCON->PIO[0][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT024 (pin M7) is configured as SPIFI_IO(0). */
                         | IOCON_PIO_FUNC(PIO024_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO024_DIGIMODE_DIGITAL));

    IOCON->PIO[0][25] = ((IOCON->PIO[0][25] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT025 (pin K8) is configured as SPIFI_IO(1). */
                         | IOCON_PIO_FUNC(PIO025_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO025_DIGIMODE_DIGITAL));

    IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT026 (pin M13) is configured as SPIFI_CLK. */
                         | IOCON_PIO_FUNC(PIO026_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO026_DIGIMODE_DIGITAL));

    IOCON->PIO[0][27] = ((IOCON->PIO[0][27] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT027 (pin L9) is configured as SPIFI_IO(3). */
                         | IOCON_PIO_FUNC(PIO027_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO027_DIGIMODE_DIGITAL));

    IOCON->PIO[0][28] = ((IOCON->PIO[0][28] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT028 (pin M9) is configured as SPIFI_IO(2). */
                         | IOCON_PIO_FUNC(PIO028_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO028_DIGIMODE_DIGITAL));

    IOCON->PIO[2][12] = ((IOCON->PIO[2][12] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT212 (pin M2) is configured as PIO2_12. */
                         | IOCON_PIO_FUNC(PIO212_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO212_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDHCPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: D2, peripheral: SDIF, signal: SD_WR_PRT, pin_signal: PIO3_15/FC8_SCK/SD_WR_PRT}
  - {pin_num: P1, peripheral: SDIF, signal: SD_CARD_DET, pin_signal: PIO2_10/ENET_RX_ER/SD_CARD_DET_N}
  - {pin_num: F4, peripheral: SDIF, signal: 'SD_D, 2', pin_signal: PIO2_8/ENET_RXD2/SD_D(2)/CTIMER0_MAT0}
  - {pin_num: J2, peripheral: SDIF, signal: 'SD_D, 1', pin_signal: PIO2_7/ENET_COL/SD_D(1)/FREQME_GPIO_CLK_B/CTIMER0_CAP1}
  - {pin_num: F3, peripheral: SDIF, signal: 'SD_D, 0', pin_signal: PIO2_6/ENET_TX_CLK/SD_D(0)/FC1_RTS_SCL_SSEL1/CTIMER0_CAP0}
  - {pin_num: B1, peripheral: SDIF, signal: SD_CLK, pin_signal: PIO2_3/ENET_TXD2/SD_CLK/FC1_RXD_SDA_MOSI/CTIMER2_MAT0}
  - {pin_num: D3, peripheral: SDIF, signal: SD_CMD, pin_signal: PIO2_4/ENET_TXD3/SD_CMD/FC1_TXD_SCL_MISO/CTIMER2_MAT1}
  - {pin_num: K2, peripheral: SDIF, signal: 'SD_D, 3', pin_signal: PIO2_9/ENET_RXD3/SD_D(3)/CTIMER0_MAT1}
  - {pin_num: C1, peripheral: SDIF, signal: SD_POW_EN, pin_signal: PIO2_5/ENET_TX_ER/SD_POW_EN/FC1_CTS_SDA_SSEL0/CTIMER1_MAT2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSDHCPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitSDHCPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[2][10] = ((IOCON->PIO[2][10] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT210 (pin P1) is configured as SD_CARD_DET_N. */
                         | IOCON_PIO_FUNC(PIO210_FUNC_ALT2)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO210_DIGIMODE_DIGITAL));

    IOCON->PIO[2][3] = ((IOCON->PIO[2][3] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT23 (pin B1) is configured as SD_CLK. */
                        | IOCON_PIO_FUNC(PIO23_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO23_DIGIMODE_DIGITAL));

    IOCON->PIO[2][4] = ((IOCON->PIO[2][4] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT24 (pin D3) is configured as SD_CMD. */
                        | IOCON_PIO_FUNC(PIO24_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO24_DIGIMODE_DIGITAL));

    IOCON->PIO[2][5] = ((IOCON->PIO[2][5] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT25 (pin C1) is configured as SD_POW_EN. */
                        | IOCON_PIO_FUNC(PIO25_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO25_DIGIMODE_DIGITAL));

    IOCON->PIO[2][6] = ((IOCON->PIO[2][6] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT26 (pin F3) is configured as SD_D(0). */
                        | IOCON_PIO_FUNC(PIO26_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO26_DIGIMODE_DIGITAL));

    IOCON->PIO[2][7] = ((IOCON->PIO[2][7] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT27 (pin J2) is configured as SD_D(1). */
                        | IOCON_PIO_FUNC(PIO27_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO27_DIGIMODE_DIGITAL));

    IOCON->PIO[2][8] = ((IOCON->PIO[2][8] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT28 (pin F4) is configured as SD_D(2). */
                        | IOCON_PIO_FUNC(PIO28_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO28_DIGIMODE_DIGITAL));

    IOCON->PIO[2][9] = ((IOCON->PIO[2][9] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT29 (pin K2) is configured as SD_D(3). */
                        | IOCON_PIO_FUNC(PIO29_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO29_DIGIMODE_DIGITAL));

    IOCON->PIO[3][15] = ((IOCON->PIO[3][15] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT315 (pin D2) is configured as SD_WR_PRT. */
                         | IOCON_PIO_FUNC(PIO315_FUNC_ALT2)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO315_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDRAMPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: P9, peripheral: EMC, signal: 'EMC_A, 14', pin_signal: PIO3_25/CTIMER4_CAP2/FC4_SCK/EMC_A(14)}
  - {pin_num: M12, peripheral: EMC, signal: 'EMC_A, 13', pin_signal: PIO1_25/FC2_TXD_SCL_MISO/SCT0_OUT2/UTICK_CAP0/EMC_A(13)}
  - {pin_num: N14, peripheral: EMC, signal: 'EMC_A, 12', pin_signal: PIO1_24/FC2_RXD_SDA_MOSI/SCT0_OUT1/FC3_SSEL3/EMC_A(12)}
  - {pin_num: M10, peripheral: EMC, signal: 'EMC_A, 11', pin_signal: PIO1_23/FC2_SCK/SCT0_OUT0/ENET_MDIO/FC3_SSEL2/EMC_A(11)}
  - {pin_num: B7, peripheral: EMC, signal: 'EMC_A, 10', pin_signal: PIO1_16/ENET_MDC/FC6_TXD_SCL_MISO_WS/CTIMER1_MAT3/SD_CMD/EMC_A(10)}
  - {pin_num: F10, peripheral: EMC, signal: 'EMC_A, 9', pin_signal: PIO1_27/FC2_RTS_SCL_SSEL1/SD_D(4)/CTIMER0_MAT3/CLKOUT/EMC_A(9)}
  - {pin_num: J10, peripheral: EMC, signal: 'EMC_A, 8', pin_signal: PIO1_26/FC2_CTS_SDA_SSEL0/SCT0_OUT3/CTIMER0_CAP3/UTICK_CAP1/EMC_A(8)}
  - {pin_num: P8, peripheral: EMC, signal: 'EMC_A, 7', pin_signal: PIO1_8/FC0_CTS_SDA_SSEL0/SD_CLK/SCT0_OUT1/FC4_SSEL2/EMC_A(7)}
  - {pin_num: N1, peripheral: EMC, signal: 'EMC_A, 6', pin_signal: PIO1_7/FC0_RTS_SCL_SSEL1/SD_D(1)/CTIMER2_MAT2/SCT0_GPI4/EMC_A(6)}
  - {pin_num: G4, peripheral: EMC, signal: 'EMC_A, 5', pin_signal: PIO1_6/FC0_TXD_SCL_MISO/SD_D(3)/CTIMER2_MAT1/SCT0_GPI3/EMC_A(5)}
  - {pin_num: E4, peripheral: EMC, signal: 'EMC_A, 4', pin_signal: PIO1_5/FC0_RXD_SDA_MOSI/SD_D(2)/CTIMER2_MAT0/SCT0_GPI0/EMC_A(4)}
  - {pin_num: C13, peripheral: EMC, signal: 'EMC_A, 3', pin_signal: PIO0_21/FC3_RTS_SCL_SSEL1/UTICK_CAP3/CTIMER3_MAT3/SCT0_GPI3/SCI0_SCLK/EMC_A(3)/FC7_SCK}
  - {pin_num: D13, peripheral: EMC, signal: 'EMC_A, 2', pin_signal: PIO0_20/FC3_CTS_SDA_SSEL0/CTIMER1_MAT1/CTIMER3_CAP3/SCT0_GPI2/SCI0_IO/EMC_A(2)/FC7_RXD_SDA_MOSI_DATA}
  - {pin_num: C6, peripheral: EMC, signal: 'EMC_A, 1', pin_signal: PIO0_19/FC4_RTS_SCL_SSEL1/UTICK_CAP0/CTIMER0_MAT2/SCT0_OUT2/EMC_A(1)/FC7_TXD_SCL_MISO_WS}
  - {pin_num: C14, peripheral: EMC, signal: 'EMC_A, 0', pin_signal: PIO0_18/FC4_CTS_SDA_SSEL0/SD_WR_PRT/CTIMER1_MAT0/SCT0_OUT1/SCI1_SCLK/EMC_A(0)}
  - {pin_num: L4, peripheral: EMC, signal: EMC_WE, pin_signal: PIO0_15/FC6_CTS_SDA_SSEL0/UTICK_CAP2/CTIMER4_CAP0/SCT0_OUT2/EMC_WEN/ENET_TX_EN/ADC0_3}
  - {pin_num: K6, peripheral: EMC, signal: EMC_CAS, pin_signal: PIO1_9/ENET_TXD0/FC1_SCK/CTIMER1_CAP0/SCT0_OUT2/FC4_CTS_SDA_SSEL0/EMC_CASN}
  - {pin_num: N9, peripheral: EMC, signal: EMC_RAS, pin_signal: PIO1_10/ENET_TXD1/FC1_RXD_SDA_MOSI/CTIMER1_MAT0/SCT0_OUT3/EMC_RASN}
  - {pin_num: K9, peripheral: EMC, signal: 'EMC_DYCS, 0', pin_signal: PIO1_12/ENET_RXD0/FC6_SCK/CTIMER1_MAT1/USB0_PORTPWRN/EMC_DYCSN(0)}
  - {pin_num: C5, peripheral: EMC, signal: 'EMC_D, 15', pin_signal: PIO1_31/MCLK/CTIMER0_MAT2/SCT0_OUT6/FC8_CTS_SDA_SSEL0/EMC_D(15)}
  - {pin_num: A8, peripheral: EMC, signal: 'EMC_D, 14', pin_signal: PIO1_30/FC7_TXD_SCL_MISO_WS/SD_D(7)/SCT0_GPI7/USB1_OVERCURRENTN/USB1_UP_LED/EMC_D(14)}
  - {pin_num: C11, peripheral: EMC, signal: 'EMC_D, 13', pin_signal: PIO1_29/FC7_RXD_SDA_MOSI_DATA/SD_D(6)/SCT0_GPI6/USB1_PORTPWRN/USB1_FRAME/EMC_D(13)}
  - {pin_num: E12, peripheral: EMC, signal: 'EMC_D, 12', pin_signal: PIO1_28/FC7_SCK/SD_D(5)/CTIMER0_CAP2/EMC_D(12)}
  - {pin_num: D4, peripheral: EMC, signal: 'EMC_D, 11', pin_signal: PIO1_4/FC0_SCK/SD_D(0)/CTIMER2_MAT1/SCT0_OUT0/FREQME_GPIO_CLK_A/EMC_D(11)}
  - {pin_num: N8, peripheral: EMC, signal: 'EMC_D, 10', pin_signal: PIO1_21/FC7_CTS_SDA_SSEL0/CTIMER3_MAT2/FC4_RXD_SDA_MOSI/EMC_D(10)}
  - {pin_num: M1, peripheral: EMC, signal: 'EMC_D, 9', pin_signal: PIO1_20/FC7_RTS_SCL_SSEL1/CTIMER3_CAP2/FC4_TXD_SCL_MISO/EMC_D(9)}
  - {pin_num: L1, peripheral: EMC, signal: 'EMC_D, 8', pin_signal: PIO1_19/FC8_SCK/SCT0_OUT7/CTIMER3_MAT1/SCT0_GPI7/FC4_SCK/EMC_D(8)}
  - {pin_num: G12, peripheral: EMC, signal: 'EMC_D, 7', pin_signal: PIO0_9/FC3_SSEL2/SD_POW_EN/FC5_TXD_SCL_MISO/SCI1_IO/EMC_D(7)}
  - {pin_num: H10, peripheral: EMC, signal: 'EMC_D, 6', pin_signal: PIO0_8/FC3_SSEL3/SD_CMD/FC5_RXD_SDA_MOSI/SWO/PDM1_DATA/EMC_D(6)}
  - {pin_num: H12, peripheral: EMC, signal: 'EMC_D, 5', pin_signal: PIO0_7/FC3_RTS_SCL_SSEL1/SD_CLK/FC5_SCK/FC1_SCK/PDM1_CLK/EMC_D(5)/ENET_RX_CLK}
  - {pin_num: A5, peripheral: EMC, signal: 'EMC_D, 4', pin_signal: PIO0_6/FC3_SCK/CTIMER3_CAP1/CTIMER4_MAT0/SCT0_GPI6/EMC_D(4)/ENET_RX_DV, identifier: EMC_D4}
  - {pin_num: E7, peripheral: EMC, signal: 'EMC_D, 3', pin_signal: PIO0_5/CAN0_TD/FC4_RXD_SDA_MOSI/CTIMER3_MAT0/SCT0_GPI5/EMC_D(3)/ENET_MDIO, identifier: EMC_D3}
  - {pin_num: C8, peripheral: EMC, signal: 'EMC_D, 2', pin_signal: PIO0_4/CAN0_RD/FC4_SCK/CTIMER3_CAP0/SCT0_GPI4/EMC_D(2)/ENET_MDC, identifier: EMC_D2}
  - {pin_num: A10, peripheral: EMC, signal: 'EMC_D, 1', pin_signal: PIO0_3/FC3_RXD_SDA_MOSI/CTIMER0_MAT1/SCT0_OUT1/SCT0_GPI3/EMC_D(1), identifier: EMC_D1}
  - {pin_num: E9, peripheral: EMC, signal: 'EMC_D, 0', pin_signal: PIO0_2/FC3_TXD_SCL_MISO/CTIMER0_CAP1/SCT0_OUT0/SCT0_GPI2/EMC_D(0), identifier: EMC_D0}
  - {pin_num: C12, peripheral: EMC, signal: 'EMC_DQM, 1', pin_signal: PIO1_14/ENET_RX_DV/UTICK_CAP2/CTIMER1_MAT2/FC5_CTS_SDA_SSEL0/USB0_UP_LED/EMC_DQM(1)}
  - {pin_num: G10, peripheral: EMC, signal: 'EMC_DQM, 0', pin_signal: PIO1_13/ENET_RXD1/FC6_RXD_SDA_MOSI_DATA/CTIMER1_CAP2/USB0_OVERCURRENTN/USB0_FRAME/EMC_DQM(0)}
  - {pin_num: B4, peripheral: EMC, signal: 'EMC_CLK, 0', pin_signal: PIO1_11/ENET_TX_EN/FC1_TXD_SCL_MISO/CTIMER1_CAP1/USB0_VBUS/EMC_CLK(0)}
  - {pin_num: A11, peripheral: EMC, signal: 'EMC_CKE, 0', pin_signal: PIO1_15/ENET_RX_CLK/UTICK_CAP3/CTIMER1_CAP3/FC5_RTS_SCL_SSEL1/FC4_RTS_SCL_SSEL1/EMC_CKE(0)}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSDRAMPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitSDRAMPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][15] = ((IOCON->PIO[0][15] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT015 (pin L4) is configured as EMC_WEN. */
                         | IOCON_PIO_FUNC(PIO015_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO015_DIGIMODE_DIGITAL));

    IOCON->PIO[0][18] = ((IOCON->PIO[0][18] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT018 (pin C14) is configured as EMC_A(0). */
                         | IOCON_PIO_FUNC(PIO018_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO018_DIGIMODE_DIGITAL));

    IOCON->PIO[0][19] = ((IOCON->PIO[0][19] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT019 (pin C6) is configured as EMC_A(1). */
                         | IOCON_PIO_FUNC(PIO019_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO019_DIGIMODE_DIGITAL));

    IOCON->PIO[0][2] = ((IOCON->PIO[0][2] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT02 (pin E9) is configured as EMC_D(0). */
                        | IOCON_PIO_FUNC(PIO02_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO02_DIGIMODE_DIGITAL));

    IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT020 (pin D13) is configured as EMC_A(2). */
                         | IOCON_PIO_FUNC(PIO020_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO020_DIGIMODE_DIGITAL));

    IOCON->PIO[0][21] = ((IOCON->PIO[0][21] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT021 (pin C13) is configured as EMC_A(3). */
                         | IOCON_PIO_FUNC(PIO021_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO021_DIGIMODE_DIGITAL));

    IOCON->PIO[0][3] = ((IOCON->PIO[0][3] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT03 (pin A10) is configured as EMC_D(1). */
                        | IOCON_PIO_FUNC(PIO03_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO03_DIGIMODE_DIGITAL));

    IOCON->PIO[0][4] = ((IOCON->PIO[0][4] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT04 (pin C8) is configured as EMC_D(2). */
                        | IOCON_PIO_FUNC(PIO04_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO04_DIGIMODE_DIGITAL));

    IOCON->PIO[0][5] = ((IOCON->PIO[0][5] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT05 (pin E7) is configured as EMC_D(3). */
                        | IOCON_PIO_FUNC(PIO05_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO05_DIGIMODE_DIGITAL));

    IOCON->PIO[0][6] = ((IOCON->PIO[0][6] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT06 (pin A5) is configured as EMC_D(4). */
                        | IOCON_PIO_FUNC(PIO06_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO06_DIGIMODE_DIGITAL));

    IOCON->PIO[0][7] = ((IOCON->PIO[0][7] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT07 (pin H12) is configured as EMC_D(5). */
                        | IOCON_PIO_FUNC(PIO07_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO07_DIGIMODE_DIGITAL));

    IOCON->PIO[0][8] = ((IOCON->PIO[0][8] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT08 (pin H10) is configured as EMC_D(6). */
                        | IOCON_PIO_FUNC(PIO08_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO08_DIGIMODE_DIGITAL));

    IOCON->PIO[0][9] = ((IOCON->PIO[0][9] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT09 (pin G12) is configured as EMC_D(7). */
                        | IOCON_PIO_FUNC(PIO09_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO09_DIGIMODE_DIGITAL));

    IOCON->PIO[1][10] = ((IOCON->PIO[1][10] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT110 (pin N9) is configured as EMC_RASN. */
                         | IOCON_PIO_FUNC(PIO110_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO110_DIGIMODE_DIGITAL));

    IOCON->PIO[1][11] = ((IOCON->PIO[1][11] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT111 (pin B4) is configured as EMC_CLK(0). */
                         | IOCON_PIO_FUNC(PIO111_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO111_DIGIMODE_DIGITAL));

    IOCON->PIO[1][12] = ((IOCON->PIO[1][12] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT112 (pin K9) is configured as EMC_DYCSN(0). */
                         | IOCON_PIO_FUNC(PIO112_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO112_DIGIMODE_DIGITAL));

    IOCON->PIO[1][13] = ((IOCON->PIO[1][13] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT113 (pin G10) is configured as EMC_DQM(0). */
                         | IOCON_PIO_FUNC(PIO113_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO113_DIGIMODE_DIGITAL));

    IOCON->PIO[1][14] = ((IOCON->PIO[1][14] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT114 (pin C12) is configured as EMC_DQM(1). */
                         | IOCON_PIO_FUNC(PIO114_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO114_DIGIMODE_DIGITAL));

    IOCON->PIO[1][15] = ((IOCON->PIO[1][15] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT115 (pin A11) is configured as EMC_CKE(0). */
                         | IOCON_PIO_FUNC(PIO115_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO115_DIGIMODE_DIGITAL));

    IOCON->PIO[1][16] = ((IOCON->PIO[1][16] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT116 (pin B7) is configured as EMC_A(10). */
                         | IOCON_PIO_FUNC(PIO116_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO116_DIGIMODE_DIGITAL));

    IOCON->PIO[1][19] = ((IOCON->PIO[1][19] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT119 (pin L1) is configured as EMC_D(8). */
                         | IOCON_PIO_FUNC(PIO119_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO119_DIGIMODE_DIGITAL));

    IOCON->PIO[1][20] = ((IOCON->PIO[1][20] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT120 (pin M1) is configured as EMC_D(9). */
                         | IOCON_PIO_FUNC(PIO120_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO120_DIGIMODE_DIGITAL));

    IOCON->PIO[1][21] = ((IOCON->PIO[1][21] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT121 (pin N8) is configured as EMC_D(10). */
                         | IOCON_PIO_FUNC(PIO121_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO121_DIGIMODE_DIGITAL));

    IOCON->PIO[1][23] = ((IOCON->PIO[1][23] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT123 (pin M10) is configured as EMC_A(11). */
                         | IOCON_PIO_FUNC(PIO123_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO123_DIGIMODE_DIGITAL));

    IOCON->PIO[1][24] = ((IOCON->PIO[1][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT124 (pin N14) is configured as EMC_A(12). */
                         | IOCON_PIO_FUNC(PIO124_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO124_DIGIMODE_DIGITAL));

    IOCON->PIO[1][25] = ((IOCON->PIO[1][25] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT125 (pin M12) is configured as EMC_A(13). */
                         | IOCON_PIO_FUNC(PIO125_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO125_DIGIMODE_DIGITAL));

    IOCON->PIO[1][26] = ((IOCON->PIO[1][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT126 (pin J10) is configured as EMC_A(8). */
                         | IOCON_PIO_FUNC(PIO126_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO126_DIGIMODE_DIGITAL));

    IOCON->PIO[1][27] = ((IOCON->PIO[1][27] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT127 (pin F10) is configured as EMC_A(9). */
                         | IOCON_PIO_FUNC(PIO127_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO127_DIGIMODE_DIGITAL));

    IOCON->PIO[1][28] = ((IOCON->PIO[1][28] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT128 (pin E12) is configured as EMC_D(12). */
                         | IOCON_PIO_FUNC(PIO128_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO128_DIGIMODE_DIGITAL));

    IOCON->PIO[1][29] = ((IOCON->PIO[1][29] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT129 (pin C11) is configured as EMC_D(13). */
                         | IOCON_PIO_FUNC(PIO129_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO129_DIGIMODE_DIGITAL));

    IOCON->PIO[1][30] = ((IOCON->PIO[1][30] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT130 (pin A8) is configured as EMC_D(14). */
                         | IOCON_PIO_FUNC(PIO130_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO130_DIGIMODE_DIGITAL));

    IOCON->PIO[1][31] = ((IOCON->PIO[1][31] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT131 (pin C5) is configured as EMC_D(15). */
                         | IOCON_PIO_FUNC(PIO131_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO131_DIGIMODE_DIGITAL));

    IOCON->PIO[1][4] = ((IOCON->PIO[1][4] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT14 (pin D4) is configured as EMC_D(11). */
                        | IOCON_PIO_FUNC(PIO14_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO14_DIGIMODE_DIGITAL));

    IOCON->PIO[1][5] = ((IOCON->PIO[1][5] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT15 (pin E4) is configured as EMC_A(4). */
                        | IOCON_PIO_FUNC(PIO15_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO15_DIGIMODE_DIGITAL));

    IOCON->PIO[1][6] = ((IOCON->PIO[1][6] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT16 (pin G4) is configured as EMC_A(5). */
                        | IOCON_PIO_FUNC(PIO16_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO16_DIGIMODE_DIGITAL));

    IOCON->PIO[1][7] = ((IOCON->PIO[1][7] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT17 (pin N1) is configured as EMC_A(6). */
                        | IOCON_PIO_FUNC(PIO17_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO17_DIGIMODE_DIGITAL));

    IOCON->PIO[1][8] = ((IOCON->PIO[1][8] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT18 (pin P8) is configured as EMC_A(7). */
                        | IOCON_PIO_FUNC(PIO18_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO18_DIGIMODE_DIGITAL));

    IOCON->PIO[1][9] = ((IOCON->PIO[1][9] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT19 (pin K6) is configured as EMC_CASN. */
                        | IOCON_PIO_FUNC(PIO19_FUNC_ALT6)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO19_DIGIMODE_DIGITAL));

    IOCON->PIO[3][25] = ((IOCON->PIO[3][25] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT325 (pin P9) is configured as EMC_A(14). */
                         | IOCON_PIO_FUNC(PIO325_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO325_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitUSBPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: H3, peripheral: USBHSH, signal: USB_DP, pin_signal: USB1_DP}
  - {pin_num: H2, peripheral: USBHSH, signal: USB_DM, pin_signal: USB1_DM}
  - {pin_num: D5, peripheral: USBFSH, signal: USB_DM, pin_signal: USB0_DM}
  - {pin_num: E5, peripheral: USBFSH, signal: USB_DP, pin_signal: USB0_DP}
  - {pin_num: G2, peripheral: USBHSH, signal: USB_VBUS, pin_signal: USB1_VBUS}
  - {pin_num: B12, peripheral: USBFSH, signal: USB_VBUS, pin_signal: PIO0_22/FC6_TXD_SCL_MISO_WS/UTICK_CAP1/CTIMER3_CAP3/SCT0_OUT3/USB0_VBUS}
  - {pin_num: G1, peripheral: USBHSH, signal: USB_IDVALUE, pin_signal: USB1_ID}
  - {pin_num: A9, peripheral: USBFSH, signal: USB_IDVALUE, pin_signal: PIO4_11/ENET_RXD0/FC2_CTS_SDA_SSEL0/USB0_IDVALUE/SCT0_GPI4, identifier: ENET_RXD0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitUSBPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitUSBPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][22] = ((IOCON->PIO[0][22] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT022 (pin B12) is configured as USB0_VBUS. */
                         | IOCON_PIO_FUNC(PIO022_FUNC_ALT7)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO022_DIGIMODE_DIGITAL));

    IOCON->PIO[4][11] = ((IOCON->PIO[4][11] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT411 (pin A9) is configured as USB0_IDVALUE. */
                         | IOCON_PIO_FUNC(PIO411_FUNC_ALT3)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO411_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDEBUG_UARTPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B13, peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI, pin_signal: PIO0_29/FC0_RXD_SDA_MOSI/CTIMER2_MAT3/SCT0_OUT8/TRACEDATA(2), direction: INPUT}
  - {pin_num: A2, peripheral: FLEXCOMM0, signal: TXD_SCL_MISO, pin_signal: PIO0_30/FC0_TXD_SCL_MISO/CTIMER0_MAT0/SCT0_OUT9/TRACEDATA(1), direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDEBUG_UARTPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitDEBUG_UARTPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][29] = ((IOCON->PIO[0][29] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT029 (pin B13) is configured as FC0_RXD_SDA_MOSI. */
                         | IOCON_PIO_FUNC(PIO029_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO029_DIGIMODE_DIGITAL));

    IOCON->PIO[0][30] = ((IOCON->PIO[0][30] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT030 (pin A2) is configured as FC0_TXD_SCL_MISO. */
                         | IOCON_PIO_FUNC(PIO030_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO030_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSWD_DEBUGPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: M3, peripheral: SWD, signal: SWDIO, pin_signal: PIO0_12/FC3_TXD_SCL_MISO/FREQME_GPIO_CLK_B/SCT0_GPI7/SWDIO/ADC0_2}
  - {pin_num: L3, peripheral: SWD, signal: SWCLK, pin_signal: PIO0_11/FC6_RXD_SDA_MOSI_DATA/CTIMER2_MAT2/FREQME_GPIO_CLK_A/SWCLK/ADC0_1}
  - {pin_num: P2, peripheral: SWD, signal: SWO, pin_signal: PIO0_10/FC6_SCK/CTIMER2_CAP2/CTIMER2_MAT0/FC1_TXD_SCL_MISO/SWO/ADC0_0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitSWD_DEBUGPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitSWD_DEBUGPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[0][10] = ((IOCON->PIO[0][10] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT010 (pin P2) is configured as SWO. */
                         | IOCON_PIO_FUNC(PIO010_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO010_DIGIMODE_DIGITAL));

    IOCON->PIO[0][11] = ((IOCON->PIO[0][11] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT011 (pin L3) is configured as SWCLK. */
                         | IOCON_PIO_FUNC(PIO011_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO011_DIGIMODE_DIGITAL));

    IOCON->PIO[0][12] = ((IOCON->PIO[0][12] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT012 (pin M3) is configured as SWDIO. */
                         | IOCON_PIO_FUNC(PIO012_FUNC_ALT6)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO012_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLCDPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: K3, peripheral: LCD, signal: LCD_PWR, pin_signal: PIO2_11/LCD_PWR/SD_VOLT(0)/FC5_SCK}
  - {pin_num: L7, peripheral: LCD, signal: LCD_FP, pin_signal: PIO2_14/LCD_FP/USB0_FRAME/USB0_PORTPWRN/CTIMER0_MAT2/FC5_CTS_SDA_SSEL0}
  - {pin_num: P7, peripheral: LCD, signal: LCD_DCLK, pin_signal: PIO2_13/LCD_DCLK/SD_VOLT(2)/FC5_TXD_SCL_MISO}
  - {pin_num: L8, peripheral: LCD, signal: LCD_LP, pin_signal: PIO2_16/LCD_LP/USB1_FRAME/USB1_PORTPWRN/CTIMER1_MAT3/FC8_SCK}
  - {pin_num: M8, peripheral: LCD, signal: LCD_AC, pin_signal: PIO2_15/LCD_AC/USB0_UP_LED/USB0_OVERCURRENTN/CTIMER0_MAT3/FC5_RTS_SCL_SSEL1}
  - {pin_num: K10, peripheral: LCD, signal: 'LCD_VD, 4', pin_signal: PIO2_22/LCD_VD(4)/SCT0_OUT7/CTIMER2_CAP0}
  - {pin_num: L10, peripheral: LCD, signal: 'LCD_VD, 3', pin_signal: PIO2_21/LCD_VD(3)/FC3_CTS_SDA_SSEL0/MCLK/CTIMER3_MAT3}
  - {pin_num: G11, peripheral: LCD, signal: 'LCD_VD, 11', pin_signal: PIO2_29/LCD_VD(11)/FC7_RTS_SCL_SSEL1/FC8_TXD_SCL_MISO/CTIMER2_CAP3/CLKOUT}
  - {pin_num: J11, peripheral: LCD, signal: 'LCD_VD, 7', pin_signal: PIO2_25/LCD_VD(7)/USB0_VBUS}
  - {pin_num: F12, peripheral: LCD, signal: 'LCD_VD, 12', pin_signal: PIO2_30/LCD_VD(12)/CTIMER2_MAT2}
  - {pin_num: G13, peripheral: LCD, signal: 'LCD_VD, 10', pin_signal: PIO2_28/LCD_VD(10)/FC7_CTS_SDA_SSEL0/CTIMER2_CAP2}
  - {pin_num: D14, peripheral: LCD, signal: 'LCD_VD, 13', pin_signal: PIO2_31/LCD_VD(13)}
  - {pin_num: K14, peripheral: LCD, signal: 'LCD_VD, 6', pin_signal: PIO2_24/LCD_VD(6)/SCT0_OUT9}
  - {pin_num: M14, peripheral: LCD, signal: 'LCD_VD, 5', pin_signal: PIO2_23/LCD_VD(5)/SCT0_OUT8}
  - {pin_num: D12, peripheral: LCD, signal: 'LCD_VD, 14', pin_signal: PIO3_0/LCD_VD(14)/PDM0_CLK/CTIMER1_MAT0}
  - {pin_num: D11, peripheral: LCD, signal: 'LCD_VD, 15', pin_signal: PIO3_1/LCD_VD(15)/PDM0_DATA/CTIMER1_MAT1}
  - {pin_num: B10, peripheral: LCD, signal: 'LCD_VD, 19', pin_signal: PIO3_5/LCD_VD(19)/FC8_RTS_SCL_SSEL1/CTIMER4_MAT1}
  - {pin_num: C9, peripheral: LCD, signal: 'LCD_VD, 20', pin_signal: PIO3_6/LCD_VD(20)/LCD_VD(0)/CTIMER4_MAT2}
  - {pin_num: B8, peripheral: LCD, signal: 'LCD_VD, 21', pin_signal: PIO3_7/LCD_VD(21)/LCD_VD(1)/CTIMER4_CAP2}
  - {pin_num: A7, peripheral: LCD, signal: 'LCD_VD, 22', pin_signal: PIO3_8/LCD_VD(22)/LCD_VD(2)/CTIMER4_CAP3}
  - {pin_num: C7, peripheral: LCD, signal: 'LCD_VD, 23', pin_signal: PIO3_9/LCD_VD(23)/LCD_VD(3)/CTIMER0_CAP2}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitLCDPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitLCDPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[2][11] = ((IOCON->PIO[2][11] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT211 (pin K3) is configured as LCD_PWR. */
                         | IOCON_PIO_FUNC(PIO211_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO211_DIGIMODE_DIGITAL));

    IOCON->PIO[2][13] = ((IOCON->PIO[2][13] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT213 (pin P7) is configured as LCD_DCLK. */
                         | IOCON_PIO_FUNC(PIO213_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO213_DIGIMODE_DIGITAL));

    IOCON->PIO[2][14] = ((IOCON->PIO[2][14] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT214 (pin L7) is configured as LCD_FP. */
                         | IOCON_PIO_FUNC(PIO214_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO214_DIGIMODE_DIGITAL));

    IOCON->PIO[2][15] = ((IOCON->PIO[2][15] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT215 (pin M8) is configured as LCD_AC. */
                         | IOCON_PIO_FUNC(PIO215_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO215_DIGIMODE_DIGITAL));

    IOCON->PIO[2][16] = ((IOCON->PIO[2][16] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT216 (pin L8) is configured as LCD_LP. */
                         | IOCON_PIO_FUNC(PIO216_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO216_DIGIMODE_DIGITAL));

    IOCON->PIO[2][21] = ((IOCON->PIO[2][21] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT221 (pin L10) is configured as LCD_VD(3). */
                         | IOCON_PIO_FUNC(PIO221_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO221_DIGIMODE_DIGITAL));

    IOCON->PIO[2][22] = ((IOCON->PIO[2][22] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT222 (pin K10) is configured as LCD_VD(4). */
                         | IOCON_PIO_FUNC(PIO222_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO222_DIGIMODE_DIGITAL));

    IOCON->PIO[2][23] = ((IOCON->PIO[2][23] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT223 (pin M14) is configured as LCD_VD(5). */
                         | IOCON_PIO_FUNC(PIO223_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO223_DIGIMODE_DIGITAL));

    IOCON->PIO[2][24] = ((IOCON->PIO[2][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT224 (pin K14) is configured as LCD_VD(6). */
                         | IOCON_PIO_FUNC(PIO224_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO224_DIGIMODE_DIGITAL));

    IOCON->PIO[2][25] = ((IOCON->PIO[2][25] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT225 (pin J11) is configured as LCD_VD(7). */
                         | IOCON_PIO_FUNC(PIO225_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO225_DIGIMODE_DIGITAL));

    IOCON->PIO[2][28] = ((IOCON->PIO[2][28] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT228 (pin G13) is configured as LCD_VD(10). */
                         | IOCON_PIO_FUNC(PIO228_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO228_DIGIMODE_DIGITAL));

    IOCON->PIO[2][29] = ((IOCON->PIO[2][29] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT229 (pin G11) is configured as LCD_VD(11). */
                         | IOCON_PIO_FUNC(PIO229_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO229_DIGIMODE_DIGITAL));

    IOCON->PIO[2][30] = ((IOCON->PIO[2][30] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT230 (pin F12) is configured as LCD_VD(12). */
                         | IOCON_PIO_FUNC(PIO230_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO230_DIGIMODE_DIGITAL));

    IOCON->PIO[2][31] = ((IOCON->PIO[2][31] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT231 (pin D14) is configured as LCD_VD(13). */
                         | IOCON_PIO_FUNC(PIO231_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO231_DIGIMODE_DIGITAL));

    IOCON->PIO[3][0] = ((IOCON->PIO[3][0] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT30 (pin D12) is configured as LCD_VD(14). */
                        | IOCON_PIO_FUNC(PIO30_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO30_DIGIMODE_DIGITAL));

    IOCON->PIO[3][1] = ((IOCON->PIO[3][1] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT31 (pin D11) is configured as LCD_VD(15). */
                        | IOCON_PIO_FUNC(PIO31_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO31_DIGIMODE_DIGITAL));

    IOCON->PIO[3][5] = ((IOCON->PIO[3][5] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT35 (pin B10) is configured as LCD_VD(19). */
                        | IOCON_PIO_FUNC(PIO35_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO35_DIGIMODE_DIGITAL));

    IOCON->PIO[3][6] = ((IOCON->PIO[3][6] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT36 (pin C9) is configured as LCD_VD(20). */
                        | IOCON_PIO_FUNC(PIO36_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO36_DIGIMODE_DIGITAL));

    IOCON->PIO[3][7] = ((IOCON->PIO[3][7] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT37 (pin B8) is configured as LCD_VD(21). */
                        | IOCON_PIO_FUNC(PIO37_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO37_DIGIMODE_DIGITAL));

    IOCON->PIO[3][8] = ((IOCON->PIO[3][8] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT38 (pin A7) is configured as LCD_VD(22). */
                        | IOCON_PIO_FUNC(PIO38_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO38_DIGIMODE_DIGITAL));

    IOCON->PIO[3][9] = ((IOCON->PIO[3][9] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT39 (pin C7) is configured as LCD_VD(23). */
                        | IOCON_PIO_FUNC(PIO39_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO39_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitENETPins:
- options: {coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: B14, peripheral: ENET, signal: 'ENET_TXD, 0', pin_signal: PIO4_8/ENET_TXD0/FC2_SCK/USB0_OVERCURRENTN/USB0_UP_LED/SCT0_GPI1}
  - {pin_num: E14, peripheral: ENET, signal: 'ENET_TXD, 1', pin_signal: PIO0_17/FC4_SSEL2/SD_CARD_DET_N/SCT0_GPI7/SCT0_OUT0/EMC_OEN/ENET_TXD1}
  - {pin_num: B6, peripheral: ENET, signal: ENET_TX_EN, pin_signal: PIO4_13/ENET_TX_EN/CTIMER4_MAT0/SCT0_GPI6}
  - {pin_num: A9, peripheral: ENET, signal: 'ENET_RXD, 0', pin_signal: PIO4_11/ENET_RXD0/FC2_CTS_SDA_SSEL0/USB0_IDVALUE/SCT0_GPI4, identifier: ENET_RXD0}
  - {pin_num: A6, peripheral: ENET, signal: 'ENET_RXD, 1', pin_signal: PIO4_12/ENET_RXD1/FC2_RTS_SCL_SSEL1/SCT0_GPI5}
  - {pin_num: B9, peripheral: ENET, signal: ENET_RX_DV, pin_signal: PIO4_10/ENET_RX_DV/FC2_TXD_SCL_MISO/USB1_OVERCURRENTN/USB1_UP_LED/SCT0_GPI3}
  - {pin_num: C4, peripheral: ENET, signal: ENET_MDIO, pin_signal: PIO4_16/ENET_MDIO/CTIMER4_MAT3/FC9_TXD_SCL_MISO}
  - {pin_num: A4, peripheral: ENET, signal: ENET_MDC, pin_signal: PIO4_15/ENET_MDC/CTIMER4_MAT2/FC9_RXD_SDA_MOSI}
  - {pin_num: H11, peripheral: GPIO, signal: 'PIO2, 26', pin_signal: PIO2_26/LCD_VD(8)/FC3_SCK/CTIMER2_CAP1, direction: OUTPUT}
  - {pin_num: B5, peripheral: ENET, signal: ENET_RX_CLK, pin_signal: PIO4_14/ENET_RX_CLK/CTIMER4_MAT1/FC9_SCK/SCT0_GPI7}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitENETPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitENETPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO2 module */
    CLOCK_EnableClock(kCLOCK_Gpio2);

    gpio_pin_config_t ENET_PHY_RSTn_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO2_26 (pin H11)  */
    GPIO_PinInit(BOARD_INITENETPINS_ENET_PHY_RSTn_GPIO, BOARD_INITENETPINS_ENET_PHY_RSTn_PORT, BOARD_INITENETPINS_ENET_PHY_RSTn_PIN, &ENET_PHY_RSTn_config);

    IOCON->PIO[0][17] = ((IOCON->PIO[0][17] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT017 (pin E14) is configured as ENET_TXD1. */
                         | IOCON_PIO_FUNC(PIO017_FUNC_ALT7)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO017_DIGIMODE_DIGITAL));

    IOCON->PIO[2][26] = ((IOCON->PIO[2][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT226 (pin H11) is configured as PIO2_26. */
                         | IOCON_PIO_FUNC(PIO226_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO226_DIGIMODE_DIGITAL));

    IOCON->PIO[4][10] = ((IOCON->PIO[4][10] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT410 (pin B9) is configured as ENET_RX_DV. */
                         | IOCON_PIO_FUNC(PIO410_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO410_DIGIMODE_DIGITAL));

    IOCON->PIO[4][11] = ((IOCON->PIO[4][11] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT411 (pin A9) is configured as ENET_RXD0. */
                         | IOCON_PIO_FUNC(PIO411_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO411_DIGIMODE_DIGITAL));

    IOCON->PIO[4][12] = ((IOCON->PIO[4][12] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT412 (pin A6) is configured as ENET_RXD1. */
                         | IOCON_PIO_FUNC(PIO412_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO412_DIGIMODE_DIGITAL));

    IOCON->PIO[4][13] = ((IOCON->PIO[4][13] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT413 (pin B6) is configured as ENET_TX_EN. */
                         | IOCON_PIO_FUNC(PIO413_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO413_DIGIMODE_DIGITAL));

    IOCON->PIO[4][14] = ((IOCON->PIO[4][14] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT414 (pin B5) is configured as ENET_RX_CLK. */
                         | IOCON_PIO_FUNC(PIO414_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO414_DIGIMODE_DIGITAL));

    IOCON->PIO[4][15] = ((IOCON->PIO[4][15] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT415 (pin A4) is configured as ENET_MDC. */
                         | IOCON_PIO_FUNC(PIO415_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO415_DIGIMODE_DIGITAL));

    IOCON->PIO[4][16] = ((IOCON->PIO[4][16] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT416 (pin C4) is configured as ENET_MDIO. */
                         | IOCON_PIO_FUNC(PIO416_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO416_DIGIMODE_DIGITAL));

    IOCON->PIO[4][8] = ((IOCON->PIO[4][8] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT48 (pin B14) is configured as ENET_TXD0. */
                        | IOCON_PIO_FUNC(PIO48_FUNC_ALT1)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO48_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitDMICPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: L14, peripheral: DMIC0, signal: 'CLK, 1', pin_signal: PIO1_2/CAN0_TD/CTIMER0_MAT3/SCT0_GPI6/PDM1_CLK/USB1_PORTPWRN}
  - {pin_num: J13, peripheral: DMIC0, signal: 'DATA, 1', pin_signal: PIO1_3/CAN0_RD/SCT0_OUT4/PDM1_DATA/USB0_PORTPWRN}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitDMICPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitDMICPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[1][2] = ((IOCON->PIO[1][2] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT12 (pin L14) is configured as PDM1_CLK. */
                        | IOCON_PIO_FUNC(PIO12_FUNC_ALT5)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO12_DIGIMODE_DIGITAL));

    IOCON->PIO[1][3] = ((IOCON->PIO[1][3] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT13 (pin J13) is configured as PDM1_DATA. */
                        | IOCON_PIO_FUNC(PIO13_FUNC_ALT5)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO13_DIGIMODE_DIGITAL));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitI2SPins:
- options: {prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: C2, peripheral: FLEXCOMM2, signal: CTS_SDA_SSEL0, pin_signal: PIO3_23/FC2_CTS_SDA_SSEL0/UTICK_CAP3, identifier: ''}
  - {pin_num: E2, peripheral: FLEXCOMM2, signal: RTS_SCL_SSEL1, pin_signal: PIO3_24/FC2_RTS_SCL_SSEL1/CTIMER4_CAP0/USB0_VBUS, identifier: ''}
  - {pin_num: G14, peripheral: FLEXCOMM6, signal: SCK, pin_signal: PIO4_1/FC6_SCK/SCT0_GPI2/EMC_CSN(2)}
  - {pin_num: F13, peripheral: FLEXCOMM6, signal: TXD_SCL_MISO_WS, pin_signal: PIO4_3/FC6_TXD_SCL_MISO_WS/CTIMER0_CAP3/SCT0_GPI4/EMC_DYCSN(2)}
  - {pin_num: F14, peripheral: FLEXCOMM6, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO4_2/FC6_RXD_SDA_MOSI_DATA/SCT0_GPI3/EMC_CSN(3)}
  - {pin_num: P12, peripheral: FLEXCOMM7, signal: RXD_SDA_MOSI_DATA, pin_signal: PIO2_19/LCD_VD(1)/FC3_TXD_SCL_MISO/FC7_RXD_SDA_MOSI_DATA/CTIMER3_MAT1}
  - {pin_num: N10, peripheral: FLEXCOMM7, signal: SCK, pin_signal: PIO2_18/LCD_VD(0)/FC3_RXD_SDA_MOSI/FC7_SCK/CTIMER3_MAT0}
  - {pin_num: P13, peripheral: FLEXCOMM3, signal: RTS_SCL_SSEL1, pin_signal: PIO2_20/LCD_VD(2)/FC3_RTS_SCL_SSEL1/FC7_TXD_SCL_MISO_WS/CTIMER3_MAT2/CTIMER4_CAP0}
  - {pin_num: B2, peripheral: SYSCON, signal: MCLK, pin_signal: PIO3_11/MCLK/FC0_SCK/FC1_SCK/TRACEDATA(3)}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitI2SPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitI2SPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON->PIO[2][18] = ((IOCON->PIO[2][18] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT218 (pin N10) is configured as FC7_SCK. */
                         | IOCON_PIO_FUNC(PIO218_FUNC_ALT3)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO218_DIGIMODE_DIGITAL));

    IOCON->PIO[2][19] = ((IOCON->PIO[2][19] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT219 (pin P12) is configured as FC7_RXD_SDA_MOSI_DATA. */
                         | IOCON_PIO_FUNC(PIO219_FUNC_ALT3)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO219_DIGIMODE_DIGITAL));

    IOCON->PIO[2][20] = ((IOCON->PIO[2][20] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT220 (pin P13) is configured as FC3_RTS_SCL_SSEL1. */
                         | IOCON_PIO_FUNC(PIO220_FUNC_ALT2)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO220_DIGIMODE_DIGITAL));

    IOCON->PIO[3][11] = ((IOCON->PIO[3][11] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT311 (pin B2) is configured as MCLK. */
                         | IOCON_PIO_FUNC(PIO311_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO311_DIGIMODE_DIGITAL));

    IOCON->PIO[3][23] = ((IOCON->PIO[3][23] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT323 (pin C2) is configured as FC2_CTS_SDA_SSEL0. */
                         | IOCON_PIO_FUNC(PIO323_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO323_DIGIMODE_DIGITAL));

    IOCON->PIO[3][24] = ((IOCON->PIO[3][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT324 (pin E2) is configured as FC2_RTS_SCL_SSEL1. */
                         | IOCON_PIO_FUNC(PIO324_FUNC_ALT1)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO324_DIGIMODE_DIGITAL));

    IOCON->PIO[4][1] = ((IOCON->PIO[4][1] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT41 (pin G14) is configured as FC6_SCK. */
                        | IOCON_PIO_FUNC(PIO41_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO41_DIGIMODE_DIGITAL));

    IOCON->PIO[4][2] = ((IOCON->PIO[4][2] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT42 (pin F14) is configured as FC6_RXD_SDA_MOSI_DATA. */
                        | IOCON_PIO_FUNC(PIO42_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO42_DIGIMODE_DIGITAL));

    IOCON->PIO[4][3] = ((IOCON->PIO[4][3] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Selects pin function.
                         * : PORT43 (pin F13) is configured as FC6_TXD_SCL_MISO_WS. */
                        | IOCON_PIO_FUNC(PIO43_FUNC_ALT2)

                        /* Select Analog/Digital mode.
                         * : Digital mode. */
                        | IOCON_PIO_DIGIMODE(PIO43_DIGIMODE_DIGITAL));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
