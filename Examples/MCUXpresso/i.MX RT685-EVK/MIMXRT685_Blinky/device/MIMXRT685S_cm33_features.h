/*
** ###################################################################
**     Version:             rev. 1.0, 2018-06-19
**     Build:               b231016
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2023 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-06-19)
**         Initial version.
**
** ###################################################################
*/

#ifndef _MIMXRT685S_cm33_FEATURES_H_
#define _MIMXRT685S_cm33_FEATURES_H_

/* SOC module features */

/* @brief ACMP availability on the SoC. */
#define FSL_FEATURE_SOC_ACMP_COUNT (1)
/* @brief CACHE64_CTRL availability on the SoC. */
#define FSL_FEATURE_SOC_CACHE64_CTRL_COUNT (1)
/* @brief CACHE64_POLSEL availability on the SoC. */
#define FSL_FEATURE_SOC_CACHE64_POLSEL_COUNT (1)
/* @brief CASPER availability on the SoC. */
#define FSL_FEATURE_SOC_CASPER_COUNT (1)
/* @brief CLKCTL0 availability on the SoC. */
#define FSL_FEATURE_SOC_CLKCTL0_COUNT (1)
/* @brief CLKCTL1 availability on the SoC. */
#define FSL_FEATURE_SOC_CLKCTL1_COUNT (1)
/* @brief CRC availability on the SoC. */
#define FSL_FEATURE_SOC_CRC_COUNT (1)
/* @brief CTIMER availability on the SoC. */
#define FSL_FEATURE_SOC_CTIMER_COUNT (5)
/* @brief DMA availability on the SoC. */
#define FSL_FEATURE_SOC_DMA_COUNT (2)
/* @brief DMIC availability on the SoC. */
#define FSL_FEATURE_SOC_DMIC_COUNT (1)
/* @brief FLEXCOMM availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXCOMM_COUNT (10)
/* @brief FLEXSPI availability on the SoC. */
#define FSL_FEATURE_SOC_FLEXSPI_COUNT (1)
/* @brief FREQME availability on the SoC. */
#define FSL_FEATURE_SOC_FREQME_COUNT (1)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (1)
/* @brief SECGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_SECGPIO_COUNT (1)
/* @brief HASHCRYPT availability on the SoC. */
#define FSL_FEATURE_SOC_HASHCRYPT_COUNT (1)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (9)
/* @brief I3C availability on the SoC. */
#define FSL_FEATURE_SOC_I3C_COUNT (1)
/* @brief I2S availability on the SoC. */
#define FSL_FEATURE_SOC_I2S_COUNT (8)
/* @brief INPUTMUX availability on the SoC. */
#define FSL_FEATURE_SOC_INPUTMUX_COUNT (1)
/* @brief IOPCTL availability on the SoC. */
#define FSL_FEATURE_SOC_IOPCTL_COUNT (1)
/* @brief LPADC availability on the SoC. */
#define FSL_FEATURE_SOC_LPADC_COUNT (1)
/* @brief MPU availability on the SoC. */
#define FSL_FEATURE_SOC_MPU_COUNT (1)
/* @brief MRT availability on the SoC. */
#define FSL_FEATURE_SOC_MRT_COUNT (1)
/* @brief MU availability on the SoC. */
#define FSL_FEATURE_SOC_MU_COUNT (1)
/* @brief OCOTP availability on the SoC. */
#define FSL_FEATURE_SOC_OCOTP_COUNT (1)
/* @brief OSTIMER availability on the SoC. */
#define FSL_FEATURE_SOC_OSTIMER_COUNT (1)
/* @brief OTFAD availability on the SoC. */
#define FSL_FEATURE_SOC_OTFAD_COUNT (1)
/* @brief PINT availability on the SoC. */
#define FSL_FEATURE_SOC_PINT_COUNT (1)
/* @brief PMC availability on the SoC. */
#define FSL_FEATURE_SOC_PMC_COUNT (1)
/* @brief POWERQUAD availability on the SoC. */
#define FSL_FEATURE_SOC_POWERQUAD_COUNT (1)
/* @brief PUF availability on the SoC. */
#define FSL_FEATURE_SOC_PUF_COUNT (1)
/* @brief RSTCTL0 availability on the SoC. */
#define FSL_FEATURE_SOC_RSTCTL0_COUNT (1)
/* @brief RSTCTL1 availability on the SoC. */
#define FSL_FEATURE_SOC_RSTCTL1_COUNT (1)
/* @brief RTC availability on the SoC. */
#define FSL_FEATURE_SOC_RTC_COUNT (1)
/* @brief SCT availability on the SoC. */
#define FSL_FEATURE_SOC_SCT_COUNT (1)
/* @brief SEMA42 availability on the SoC. */
#define FSL_FEATURE_SOC_SEMA42_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (9)
/* @brief SYSCTL0 availability on the SoC. */
#define FSL_FEATURE_SOC_SYSCTL0_COUNT (1)
/* @brief SYSCTL1 availability on the SoC. */
#define FSL_FEATURE_SOC_SYSCTL1_COUNT (1)
/* @brief TRNG availability on the SoC. */
#define FSL_FEATURE_SOC_TRNG_COUNT (1)
/* @brief USART availability on the SoC. */
#define FSL_FEATURE_SOC_USART_COUNT (8)
/* @brief USBHSD availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSD_COUNT (1)
/* @brief USBHSDCD availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSDCD_COUNT (1)
/* @brief USBHSH availability on the SoC. */
#define FSL_FEATURE_SOC_USBHSH_COUNT (1)
/* @brief USBPHY availability on the SoC. */
#define FSL_FEATURE_SOC_USBPHY_COUNT (1)
/* @brief USDHC availability on the SoC. */
#define FSL_FEATURE_SOC_USDHC_COUNT (2)
/* @brief UTICK availability on the SoC. */
#define FSL_FEATURE_SOC_UTICK_COUNT (1)
/* @brief WWDT availability on the SoC. */
#define FSL_FEATURE_SOC_WWDT_COUNT (2)

/* LPADC module features */

/* @brief FIFO availability on the SoC. */
#define FSL_FEATURE_LPADC_FIFO_COUNT (1)
/* @brief Has subsequent trigger priority (bitfield CFG[TPRICTRL]). */
#define FSL_FEATURE_LPADC_HAS_CFG_SUBSEQUENT_PRIORITY (1)
/* @brief Has differential mode (bitfield CMDLn[DIFF]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_DIFF (1)
/* @brief Has channel scale (bitfield CMDLn[CSCALE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_CSCALE (1)
/* @brief Has conversion type select (bitfield CMDLn[CTYPE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_CTYPE (0)
/* @brief Has conversion resolution select  (bitfield CMDLn[MODE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_MODE (0)
/* @brief Has compare function enable (bitfield CMDHn[CMPEN]). */
#define FSL_FEATURE_LPADC_HAS_CMDH_CMPEN (1)
/* @brief Has Wait for trigger assertion before execution (bitfield CMDHn[WAIT_TRIG]). */
#define FSL_FEATURE_LPADC_HAS_CMDH_WAIT_TRIG (0)
/* @brief Has offset calibration (bitfield CTRL[CALOFS]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CALOFS (0)
/* @brief Has gain calibration (bitfield CTRL[CAL_REQ]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CAL_REQ (0)
/* @brief Has calibration average (bitfield CTRL[CAL_AVGS]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CAL_AVGS (0)
/* @brief Has internal clock (bitfield CFG[ADCKEN]). */
#define FSL_FEATURE_LPADC_HAS_CFG_ADCKEN (0)
/* @brief Enable support for low voltage reference on option 1 reference (bitfield CFG[VREF1RNG]). */
#define FSL_FEATURE_LPADC_HAS_CFG_VREF1RNG (0)
/* @brief Has calibration (bitfield CFG[CALOFS]). */
#define FSL_FEATURE_LPADC_HAS_CFG_CALOFS (0)
/* @brief Has offset trim (register OFSTRIM). */
#define FSL_FEATURE_LPADC_HAS_OFSTRIM (0)
/* @brief Has Trigger status register. */
#define FSL_FEATURE_LPADC_HAS_TSTAT (0)
/* @brief Has power select (bitfield CFG[PWRSEL]). */
#define FSL_FEATURE_LPADC_HAS_CFG_PWRSEL (1)
/* @brief Has alternate channel B scale (bitfield CMDLn[ALTB_CSCALE]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_ALTB_CSCALE (0)
/* @brief Has alternate channel B select enable (bitfield CMDLn[ALTBEN]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_ALTBEN (0)
/* @brief Has alternate channel input (bitfield CMDLn[ALTB_ADCH]). */
#define FSL_FEATURE_LPADC_HAS_CMDL_ALTB_ADCH (0)
/* @brief Has offset calibration mode (bitfield CTRL[CALOFSMODE]). */
#define FSL_FEATURE_LPADC_HAS_CTRL_CALOFSMODE (0)
/* @brief Conversion averaged bitfiled width. */
#define FSL_FEATURE_LPADC_CONVERSIONS_AVERAGED_BITFIELD_WIDTH (3)
/* @brief Has B side channels. */
#define FSL_FEATURE_LPADC_HAS_B_SIDE_CHANNELS (1)
/* @brief Indicate whether the LPADC STAT register has trigger exception interrupt function (bitfield STAT[TEXC_INT]). */
#define FSL_FEATURE_LPADC_HAS_STAT_TEXC_INT (0)
/* @brief Indicate whether the LPADC STAT register has trigger completion interrupt function (bitfield STAT[TCOMP_INT]). */
#define FSL_FEATURE_LPADC_HAS_STAT_TCOMP_INT (0)
/* @brief Indicate whether the LPADC STAT register has calibration ready function (bitfield STAT[CAL_RDY]). */
#define FSL_FEATURE_LPADC_HAS_STAT_CAL_RDY (0)
/* @brief Indicate whether the LPADC STAT register has ADC active function (bitfield STAT[ADC_ACTIVE]). */
#define FSL_FEATURE_LPADC_HAS_STAT_ADC_ACTIVE (0)
/* @brief Indicate whether the LPADC IE register has trigger exception interrupt enable function (bitfield IE[TEXC_IE]). */
#define FSL_FEATURE_LPADC_HAS_IE_TEXC_IE (0)
/* @brief Indicate whether the LPADC IE register has trigger completion interrupt enable function (bitfield IE[TCOMP_IE]). */
#define FSL_FEATURE_LPADC_HAS_IE_TCOMP_IE (0)
/* @brief Indicate whether the LPADC CFG register has trigger resume/restart enable function (bitfield CFG[TRES]). */
#define FSL_FEATURE_LPADC_HAS_CFG_TRES (0)
/* @brief Indicate whether the LPADC CFG register has trigger command resume/restart enable function (bitfield CFG[TCMDRES]). */
#define FSL_FEATURE_LPADC_HAS_CFG_TCMDRES (0)
/* @brief Indicate whether the LPADC CFG register has high priority trigger exception disable function (bitfield CFG[HPT_EXDI]). */
#define FSL_FEATURE_LPADC_HAS_CFG_HPT_EXDI (0)
/* @brief Indicate LPADC CFG register TPRICTRL bitfield width. */
#define FSL_FEATURE_LPADC_CFG_TPRICTRL_BITFIELD_WIDTH (1)

/* CACHE64_CTRL module features */

/* @brief Cache Line size in byte. */
#define FSL_FEATURE_CACHE64_CTRL_LINESIZE_BYTE (32)

/* CACHE64_POLSEL module features */

/* No feature definitions */

/* CASPER module features */

/* @brief Base address of the CASPER dedicated RAM. */
#define FSL_FEATURE_CASPER_RAM_BASE_ADDRESS (0x40152000u)

/* ACMP module features */

/* @brief Has CMP_C3. */
#define FSL_FEATURE_ACMP_HAS_C3_REG (1)
/* @brief Has C0 LINKEN Bit */
#define FSL_FEATURE_ACMP_HAS_C0_LINKEN_BIT (1)
/* @brief Has C0 OFFSET Bit */
#define FSL_FEATURE_ACMP_HAS_C0_OFFSET_BIT (0)
/* @brief Has C0 HYSTCTR Bit */
#define FSL_FEATURE_ACMP_HAS_C0_HYSTCTR_BIT (1)
/* @brief Has C1 INPSEL Bit */
#define FSL_FEATURE_ACMP_HAS_C1_INPSEL_BIT (0)
/* @brief Has C1 INNSEL Bit */
#define FSL_FEATURE_ACMP_HAS_C1_INNSEL_BIT (0)
/* @brief Has C1 DACOE Bit */
#define FSL_FEATURE_ACMP_HAS_C1_DACOE_BIT (0)
/* @brief Has C1 DMODE Bit */
#define FSL_FEATURE_ACMP_HAS_C1_DMODE_BIT (1)
/* @brief Has C2 RRE Bit */
#define FSL_FEATURE_ACMP_HAS_C2_RRE_BIT (0)

/* CRC module features */

/* @brief Has data register with name CRC */
#define FSL_FEATURE_CRC_HAS_CRC_REG (0)

/* CTIMER module features */

/* @brief CTIMER has no capture channel. */
#define FSL_FEATURE_CTIMER_HAS_NO_INPUT_CAPTURE (0)
/* @brief CTIMER has no capture 2 interrupt. */
#define FSL_FEATURE_CTIMER_HAS_NO_IR_CR2INT (0)
/* @brief CTIMER capture 3 interrupt. */
#define FSL_FEATURE_CTIMER_HAS_IR_CR3INT (1)
/* @brief Has CTIMER CCR_CAP2 (register bits CCR[CAP2RE][CAP2FE][CAP2I]. */
#define FSL_FEATURE_CTIMER_HAS_NO_CCR_CAP2 (0)
/* @brief Has CTIMER CCR_CAP3 (register bits CCR[CAP3RE][CAP3FE][CAP3I]). */
#define FSL_FEATURE_CTIMER_HAS_CCR_CAP3 (1)
/* @brief CTIMER Has register MSR */
#define FSL_FEATURE_CTIMER_HAS_MSR (1)

/* DMA module features */

/* @brief Number of channels */
#define FSL_FEATURE_DMA_NUMBER_OF_CHANNELSn(x) (33)
/* @brief Number of all DMA channels */
#define FSL_FEATURE_DMA_ALL_CHANNELS (66)
/* @brief Max Number of DMA channels */
#define FSL_FEATURE_DMA_MAX_CHANNELS (33)
/* @brief Align size of DMA descriptor */
#define FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZE (1024)
/* @brief DMA head link descriptor table align size */
#define FSL_FEATURE_DMA_LINK_DESCRIPTOR_ALIGN_SIZE (16U)

/* DMIC module features */

/* @brief Number of channels */
#define FSL_FEATURE_DMIC_CHANNEL_NUM (8)
/* @brief DMIC channel support stereo data */
#define FSL_FEATURE_DMIC_IO_HAS_STEREO_2_4_6 (1)
/* @brief DMIC does not support bypass channel clock */
#define FSL_FEATURE_DMIC_IO_HAS_NO_BYPASS (1)
/* @brief DMIC channel FIFO register support sign extended */
#define FSL_FEATURE_DMIC_CHANNEL_HAS_SIGNEXTEND (1)
/* @brief DMIC has no IOCFG register */
#define FSL_FEATURE_DMIC_HAS_NO_IOCFG (1)
/* @brief DMIC has decimator reset function */
#define FSL_FEATURE_DMIC_HAS_DECIMATOR_RESET_FUNC (1)
/* @brief DMIC has global channel synchronization function */
#define FSL_FEATURE_DMIC_HAS_GLOBAL_SYNC_FUNC (1)

/* FLEXCOMM module features */

/* @brief FLEXCOMM0 USART INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_USART_INDEX (0)
/* @brief FLEXCOMM0 SPI INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_SPI_INDEX (0)
/* @brief FLEXCOMM0 I2C INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_I2C_INDEX (0)
/* @brief FLEXCOMM0 I2S INDEX 0 */
#define FSL_FEATURE_FLEXCOMM0_I2S_INDEX (0)
/* @brief FLEXCOMM1 USART INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_USART_INDEX (1)
/* @brief FLEXCOMM1 SPI INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_SPI_INDEX (1)
/* @brief FLEXCOMM1 I2C INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_I2C_INDEX (1)
/* @brief FLEXCOMM1 I2S INDEX 1 */
#define FSL_FEATURE_FLEXCOMM1_I2S_INDEX (1)
/* @brief FLEXCOMM2 USART INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_USART_INDEX (2)
/* @brief FLEXCOMM2 SPI INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_SPI_INDEX (2)
/* @brief FLEXCOMM2 I2C INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_I2C_INDEX (2)
/* @brief FLEXCOMM2 I2S INDEX 2 */
#define FSL_FEATURE_FLEXCOMM2_I2S_INDEX (2)
/* @brief FLEXCOMM3 USART INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_USART_INDEX (3)
/* @brief FLEXCOMM3 SPI INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_SPI_INDEX (3)
/* @brief FLEXCOMM3 I2C INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_I2C_INDEX (3)
/* @brief FLEXCOMM3 I2S INDEX 3 */
#define FSL_FEATURE_FLEXCOMM3_I2S_INDEX (3)
/* @brief FLEXCOMM4 USART INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_USART_INDEX (4)
/* @brief FLEXCOMM4 SPI INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_SPI_INDEX (4)
/* @brief FLEXCOMM4 I2C INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_I2C_INDEX (4)
/* @brief FLEXCOMM4 I2S INDEX 4 */
#define FSL_FEATURE_FLEXCOMM4_I2S_INDEX (4)
/* @brief FLEXCOMM5 USART INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_USART_INDEX (5)
/* @brief FLEXCOMM5 SPI INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_SPI_INDEX (5)
/* @brief FLEXCOMM5 I2C INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_I2C_INDEX (5)
/* @brief FLEXCOMM5 I2S INDEX 5 */
#define FSL_FEATURE_FLEXCOMM5_I2S_INDEX (5)
/* @brief FLEXCOMM6 USART INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_USART_INDEX (6)
/* @brief FLEXCOMM6 SPI INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_SPI_INDEX (6)
/* @brief FLEXCOMM6 I2C INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_I2C_INDEX (6)
/* @brief FLEXCOMM6 I2S INDEX 6 */
#define FSL_FEATURE_FLEXCOMM6_I2S_INDEX (6)
/* @brief FLEXCOMM7 USART INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_USART_INDEX (7)
/* @brief FLEXCOMM7 SPI INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_SPI_INDEX (7)
/* @brief FLEXCOMM7 I2C INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_I2C_INDEX (7)
/* @brief FLEXCOMM7 I2S INDEX 7 */
#define FSL_FEATURE_FLEXCOMM7_I2S_INDEX (7)
/* @brief FLEXCOMM14 SPI(HS_SPI) INDEX 14 */
#define FSL_FEATURE_FLEXCOMM14_SPI_INDEX (14)
/* @brief FLEXCOMM15 I2C INDEX 15 */
#define FSL_FEATURE_FLEXCOMM15_I2C_INDEX (15)
/* @brief I2S has DMIC interconnection */
#define FSL_FEATURE_FLEXCOMM_INSTANCE_I2S_HAS_DMIC_INTERCONNECTIONn(x) \
    (((x) == FLEXCOMM0) ? (1) : \
    (((x) == FLEXCOMM1) ? (0) : \
    (((x) == FLEXCOMM2) ? (0) : \
    (((x) == FLEXCOMM3) ? (0) : \
    (((x) == FLEXCOMM4) ? (0) : \
    (((x) == FLEXCOMM5) ? (0) : \
    (((x) == FLEXCOMM6) ? (0) : \
    (((x) == FLEXCOMM7) ? (0) : \
    (((x) == FLEXCOMM14) ? (0) : \
    (((x) == FLEXCOMM15) ? (0) : (-1)))))))))))

/* FLEXSPI module features */

/* @brief FlexSPI AHB buffer count */
#define FSL_FEATURE_FLEXSPI_AHB_BUFFER_COUNTn(x) (8)
/* @brief FlexSPI has no MCR0 ARDFEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_ARDFEN (1)
/* @brief FlexSPI has no MCR0 ATDFEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_ATDFEN (1)
/* @brief FlexSPI has no MCR0 COMBINATIONEN bit */
#define FSL_FEATURE_FLEXSPI_HAS_NO_MCR0_COMBINATIONEN (1)
/* @brief FLEXSPI has no IP parallel mode. */
#define FSL_FEATURE_FLEXSPI_HAS_NO_IP_PARALLEL_MODE (0)
/* @brief FLEXSPI has no AHB parallel mode. */
#define FSL_FEATURE_FLEXSPI_HAS_NO_AHB_PARALLEL_MODE (0)
/* @brief FLEXSPI support address shift. */
#define FSL_FEATURE_FLEXSPI_SUPPORT_ADDRESS_SHIFT (0)

/* GPIO module features */

/* @brief GPIO has interrupts */
#define FSL_FEATURE_GPIO_HAS_INTERRUPT (1)
/* @brief GPIO DIRSET and DIRCLR register. */
#define FSL_FEATURE_GPIO_DIRSET_AND_DIRCLR (1)

/* HASHCRYPT module features */

/* @brief hashcrypt has reload feature */
#define FSL_FEATURE_HASHCRYPT_HAS_RELOAD_FEATURE (1)

/* I2S module features */

/* @brief I2S support dual channel transfer. */
#define FSL_FEATURE_I2S_SUPPORT_SECONDARY_CHANNEL (1)
/* @brief I2S has DMIC interconnection. */
#define FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION (1)

/* I3C module features */

/* @brief Has TERM bitfile in MERRWARN register. */
#define FSL_FEATURE_I3C_HAS_NO_MERRWARN_TERM (0)
/* @brief SOC has no reset driver. */
#define FSL_FEATURE_I3C_HAS_NO_RESET (0)
/* @brief Use fixed BAMATCH count, do not provide editable BAMATCH. */
#define FSL_FEATURE_I3C_HAS_NO_SCONFIG_BAMATCH (0)
/* @brief Register SCONFIG do not have IDRAND bitfield. */
#define FSL_FEATURE_I3C_HAS_NO_SCONFIG_IDRAND (0)
/* @brief Register SCONFIG has HDROK bitfield. */
#define FSL_FEATURE_I3C_HAS_HDROK (0)
/* @brief SOC doesn't support slave IBI/MR/HJ. */
#define FSL_FEATURE_I3C_HAS_NO_SLAVE_IBI_MR_HJ (0)

/* INPUTMUX module features */

/* @brief Inputmux has DMA Request Enable */
#define FSL_FEATURE_INPUTMUX_HAS_SIGNAL_ENA (1)
/* @brief Inputmux has channel mux control */
#define FSL_FEATURE_INPUTMUX_HAS_CHANNEL_MUX (0)

/* MRT module features */

/* @brief number of channels. */
#define FSL_FEATURE_MRT_NUMBER_OF_CHANNELS (4)

/* MU module features */

/* @brief MU Has register CCR */
#define FSL_FEATURE_MU_HAS_CCR (0)
/* @brief MU Has register SR[RS], BSR[ARS] */
#define FSL_FEATURE_MU_HAS_SR_RS (1)
/* @brief MU Has register CR[RDIE], CR[RAIE], SR[RDIP], SR[RAIP] */
#define FSL_FEATURE_MU_HAS_RESET_INT (0)
/* @brief MU Has register SR[MURIP] */
#define FSL_FEATURE_MU_HAS_SR_MURIP (0)
/* @brief brief MU Has register SR[HRIP] */
#define FSL_FEATURE_MU_HAS_SR_HRIP (0)
/* @brief brief MU does not support enable clock of the other core, CR[CLKE] or CCR[CLKE]. */
#define FSL_FEATURE_MU_NO_CLKE (1)
/* @brief brief MU does not support NMI, CR[NMI]. */
#define FSL_FEATURE_MU_NO_NMI (1)
/* @brief brief MU does not support hold the other core reset. CR[RSTH] or CCR[RSTH]. */
#define FSL_FEATURE_MU_NO_RSTH (1)
/* @brief brief MU does not supports MU reset, CR[MUR]. */
#define FSL_FEATURE_MU_NO_MUR (0)
/* @brief brief MU does not supports hardware reset, CR[HR] or CCR[HR]. */
#define FSL_FEATURE_MU_NO_HR (1)
/* @brief brief MU supports mask the hardware reset. CR[HRM] or CCR[HRM]. */
#define FSL_FEATURE_MU_HAS_HRM (0)

/* OTFAD module features */

/* @brief OTFAD has Security Violation Mode (SVM) */
#define FSL_FEATURE_OTFAD_HAS_SVM_MODE (0)
/* @brief OTFAD has Key Blob Processing */
#define FSL_FEATURE_OTFAD_HAS_KEYBLOB_PROCESSING (0)
/* @brief OTFAD has interrupt request enable */
#define FSL_FEATURE_OTFAD_HAS_HAS_IRQ_ENABLE (0)
/* @brief OTFAD has Force Error */
#define FSL_FEATURE_OTFAD_HAS_FORCE_ERR (0)

/* PINT module features */

/* @brief Number of connected outputs */
#define FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS (8)

/* PMC module features */

/* @brief Has no OS Timer control register in PMC. */
#define FSL_FEATURE_PMC_HAS_NO_OSTIMER_REG (1)

/* PUF module features */

/* @brief PUF need to setup SRAM manually */
#define FSL_FEATURE_PUF_PWR_HAS_MANUAL_SLEEP_CONTROL (1)
/* @brief PUF has SHIFT_STATUS register. */
#define FSL_FEATURE_PUF_HAS_SHIFT_STATUS (0)
/* @brief PUF has IDXBLK_SHIFT register. */
#define FSL_FEATURE_PUF_HAS_IDXBLK_SHIFT (0)

/* RTC module features */

/* @brief RTC has no reset control */
#define FSL_FEATURE_RTC_HAS_NO_RESET (1)
/* @brief Has SUBSEC Register (register SUBSEC) */
#define FSL_FEATURE_RTC_HAS_SUBSEC (1)

/* SCT module features */

/* @brief Number of events */
#define FSL_FEATURE_SCT_NUMBER_OF_EVENTS (16)
/* @brief Number of states */
#define FSL_FEATURE_SCT_NUMBER_OF_STATES (32)
/* @brief Number of match capture */
#define FSL_FEATURE_SCT_NUMBER_OF_MATCH_CAPTURE (16)
/* @brief Number of outputs */
#define FSL_FEATURE_SCT_NUMBER_OF_OUTPUTS (10)

/* SEMA42 module features */

/* @brief Gate counts */
#define FSL_FEATURE_SEMA42_GATE_COUNT (16)

/* SPI module features */

/* @brief SSEL pin count. */
#define FSL_FEATURE_SPI_SSEL_COUNT (4)

/* TRNG module features */

/* No feature definitions */

/* USBHSD module features */

/* @brief Size of the USB dedicated RAM */
#define FSL_FEATURE_USBHSD_USB_RAM (0x00004000)
/* @brief Base address of the USB dedicated RAM */
#define FSL_FEATURE_USBHSD_USB_RAM_BASE_ADDRESS (0x40140000)
/* @brief USBHSD version */
#define FSL_FEATURE_USBHSD_VERSION (300)
/* @brief Number of the endpoint in USB HS */
#define FSL_FEATURE_USBHSD_EP_NUM (6)
/* @brief The controller doesn't exit HS mode automatically after vbus becomes invalid */
#define FSL_FEATURE_USBHSD_HAS_EXIT_HS_ISSUE (1)

/* USBHSH module features */

/* @brief Size of the USB dedicated RAM */
#define FSL_FEATURE_USBHSH_USB_RAM (0x00004000)
/* @brief Base address of the USB dedicated RAM */
#define FSL_FEATURE_USBHSH_USB_RAM_BASE_ADDRESS (0x40140000)
/* @brief USBHSH version */
#define FSL_FEATURE_USBHSH_VERSION (300)
/* @brief USBHSH has packet turnaround time-out register */
#define FSL_FEATURE_USBHSH_HAS_TURNAROUND_TIMEOUT (0)

/* USBPHY module features */

/* @brief USBPHY contain DCD analog module */
#define FSL_FEATURE_USBPHY_HAS_DCD_ANALOG (1)
/* @brief USBPHY has register TRIM_OVERRIDE_EN */
#define FSL_FEATURE_USBPHY_HAS_TRIM_OVERRIDE_EN (1)
/* @brief USBPHY is 28FDSOI */
#define FSL_FEATURE_USBPHY_28FDSOI (0)

/* USDHC module features */

/* @brief Has external DMA support (VEND_SPEC[EXT_DMA_EN]) */
#define FSL_FEATURE_USDHC_HAS_EXT_DMA (0)
/* @brief Has HS400 mode (MIX_CTRL[HS400_MODE]) */
#define FSL_FEATURE_USDHC_HAS_HS400_MODE (1)
/* @brief Has SDR50 support (HOST_CTRL_CAP[SDR50_SUPPORT]) */
#define FSL_FEATURE_USDHC_HAS_SDR50_MODE (1)
/* @brief Has SDR104 support (HOST_CTRL_CAP[SDR104_SUPPORT]) */
#define FSL_FEATURE_USDHC_HAS_SDR104_MODE (1)
/* @brief USDHC has reset control */
#define FSL_FEATURE_USDHC_HAS_RESET (1)
/* @brief USDHC has no bitfield WTMK_LVL[WR_BRST_LEN] and WTMK_LVL[RD_BRST_LEN] */
#define FSL_FEATURE_USDHC_HAS_NO_RW_BURST_LEN (0)
/* @brief If USDHC instance support 8 bit width */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_8_BIT_WIDTHn(x) (1)
/* @brief If USDHC instance support HS400 mode */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_HS400_MODEn(x) \
    (((x) == USDHC0) ? (1) : \
    (((x) == USDHC1) ? (0) : (-1)))
/* @brief If USDHC instance support 1v8 signal */
#define FSL_FEATURE_USDHC_INSTANCE_SUPPORT_1V8_SIGNALn(x) (1)
/* @brief Has no retuning time counter (HOST_CTRL_CAP[TIME_COUNT_RETURNING]) */
#define FSL_FEATURE_USDHC_REGISTER_HOST_CTRL_CAP_HAS_NO_RETUNING_TIME_COUNTER (0)
/* @brief Has no VSELECT bit in VEND_SPEC register */
#define FSL_FEATURE_USDHC_HAS_NO_VOLTAGE_SELECT (0)

/* UTICK module features */

/* @brief UTICK does not support power down configure. */
#define FSL_FEATURE_UTICK_HAS_NO_PDCFG (1)

/* WWDT module features */

/* @brief WWDT does not support oscillator lock. */
#define FSL_FEATURE_WWDT_HAS_NO_OSCILLATOR_LOCK (0)
/* @brief WWDT does not support power down configure. */
#define FSL_FEATURE_WWDT_HAS_NO_PDCFG (1)

#endif /* _MIMXRT685S_cm33_FEATURES_H_ */

