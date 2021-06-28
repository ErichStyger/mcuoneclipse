/*
** ###################################################################
**     Version:             rev. 1.0, 2018-01-09
**     Build:               b190816
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2019 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-01-09)
**         Initial version.
**
** ###################################################################
*/

#ifndef _LPC804_FEATURES_H_
#define _LPC804_FEATURES_H_

/* SOC module features */

#if defined(CPU_LPC804M101JDH20) || defined(CPU_LPC804UK)
    /* @brief ADC availability on the SoC. */
    #define FSL_FEATURE_SOC_ADC_COUNT (1)
    /* @brief CAPT availability on the SoC. */
    #define FSL_FEATURE_SOC_CAPT_COUNT (1)
    /* @brief CRC availability on the SoC. */
    #define FSL_FEATURE_SOC_CRC_COUNT (1)
    /* @brief CTIMER availability on the SoC. */
    #define FSL_FEATURE_SOC_CTIMER_COUNT (1)
    /* @brief GPIO availability on the SoC. */
    #define FSL_FEATURE_SOC_GPIO_COUNT (1)
    /* @brief I2C availability on the SoC. */
    #define FSL_FEATURE_SOC_I2C_COUNT (2)
    /* @brief IOCON availability on the SoC. */
    #define FSL_FEATURE_SOC_IOCON_COUNT (1)
    /* @brief MRT availability on the SoC. */
    #define FSL_FEATURE_SOC_MRT_COUNT (1)
    /* @brief PINT availability on the SoC. */
    #define FSL_FEATURE_SOC_PINT_COUNT (1)
    /* @brief PMU availability on the SoC. */
    #define FSL_FEATURE_SOC_PMU_COUNT (1)
    /* @brief SPI availability on the SoC. */
    #define FSL_FEATURE_SOC_SPI_COUNT (1)
    /* @brief SWM availability on the SoC. */
    #define FSL_FEATURE_SOC_SWM_COUNT (1)
    /* @brief SYSCON availability on the SoC. */
    #define FSL_FEATURE_SOC_SYSCON_COUNT (1)
    /* @brief USART availability on the SoC. */
    #define FSL_FEATURE_SOC_USART_COUNT (2)
    /* @brief WWDT availability on the SoC. */
    #define FSL_FEATURE_SOC_WWDT_COUNT (1)
#elif defined(CPU_LPC804M101JDH24) || defined(CPU_LPC804M101JHI33) || defined(CPU_LPC804M111JDH24)
    /* @brief ADC availability on the SoC. */
    #define FSL_FEATURE_SOC_ADC_COUNT (1)
    /* @brief CAPT availability on the SoC. */
    #define FSL_FEATURE_SOC_CAPT_COUNT (1)
    /* @brief CRC availability on the SoC. */
    #define FSL_FEATURE_SOC_CRC_COUNT (1)
    /* @brief CTIMER availability on the SoC. */
    #define FSL_FEATURE_SOC_CTIMER_COUNT (1)
    /* @brief DAC availability on the SoC. */
    #define FSL_FEATURE_SOC_DAC_COUNT (1)
    /* @brief GPIO availability on the SoC. */
    #define FSL_FEATURE_SOC_GPIO_COUNT (1)
    /* @brief I2C availability on the SoC. */
    #define FSL_FEATURE_SOC_I2C_COUNT (2)
    /* @brief IOCON availability on the SoC. */
    #define FSL_FEATURE_SOC_IOCON_COUNT (1)
    /* @brief MRT availability on the SoC. */
    #define FSL_FEATURE_SOC_MRT_COUNT (1)
    /* @brief PINT availability on the SoC. */
    #define FSL_FEATURE_SOC_PINT_COUNT (1)
    /* @brief PMU availability on the SoC. */
    #define FSL_FEATURE_SOC_PMU_COUNT (1)
    /* @brief SPI availability on the SoC. */
    #define FSL_FEATURE_SOC_SPI_COUNT (1)
    /* @brief SWM availability on the SoC. */
    #define FSL_FEATURE_SOC_SWM_COUNT (1)
    /* @brief SYSCON availability on the SoC. */
    #define FSL_FEATURE_SOC_SYSCON_COUNT (1)
    /* @brief USART availability on the SoC. */
    #define FSL_FEATURE_SOC_USART_COUNT (2)
    /* @brief WWDT availability on the SoC. */
    #define FSL_FEATURE_SOC_WWDT_COUNT (1)
#endif

/* ACOMP module features */

/* @brief Has INTENA bitfile in CTRL reigster. */
#define FSL_FEATURE_ACOMP_HAS_CTRL_INTENA (1)

/* ADC module features */

/* @brief Do not has input select (register INSEL). */
#define FSL_FEATURE_ADC_HAS_NO_INSEL  (1)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_ASYNMODE (0)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_RESOL (0)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_BYPASSCAL (0)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_TSAMP (0)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_LPWRMODE (1)
/* @brief Has ASYNMODE bitfile in CTRL reigster. */
#define FSL_FEATURE_ADC_HAS_CTRL_CALMODE (0)
/* @brief Has startup register. */
#define FSL_FEATURE_ADC_HAS_STARTUP_REG (0)
/* @brief Has ADTrim register */
#define FSL_FEATURE_ADC_HAS_TRIM_REG (0)
/* @brief Has Calibration register. */
#define FSL_FEATURE_ADC_HAS_CALIB_REG (0)
/* @brief Has no Calibration function. */
#define FSL_FEATURE_ADC_HAS_NO_CALIB_FUNC (1)

/* CAPT module features */

/* @brief Has DMA bitfile in CTRL reigster. */
#define FSL_FEATURE_CAPT_HAS_CTRL_DMA (0)

/* CLOCK module features */

/* @brief GPIOINT clock source. */
#define FSL_FEATURE_CLOCK_HAS_GPIOINT_CLOCK_SOURCE (1)

/* CTIMER module features */

/* @brief Writing a zero asserts the CTIMER reset. */
#define FSL_FEATURE_CTIMER_WRITE_ZERO_ASSERT_RESET (1)

/* IOCON module features */

/* No feature definitions */

/* MRT module features */

/* @brief Writing a zero asserts the MRT reset. */
#define FSL_FEATURE_MRT_WRITE_ZERO_ASSERT_RESET (1)
/* @brief Has no MULTITASK bitfile in MODCFG reigster. */
#define FSL_FEATURE_MRT_HAS_NO_MODCFG_MULTITASK (1)
/* @brief Has no INUSE bitfile in STAT reigster. */
#define FSL_FEATURE_MRT_HAS_NO_CHANNEL_STAT_INUSE (1)
/* @brief number of channels. */
#define FSL_FEATURE_MRT_NUMBER_OF_CHANNELS  (4)

/* NVIC module features */

/* @brief Number of connected outputs. */
#define FSL_FEATURE_NVIC_HAS_SHARED_INTERTTUPT_NUMBER (1)

/* PINT module features */

/* @brief Number of connected outputs */
#define FSL_FEATURE_PINT_NUMBER_OF_CONNECTED_OUTPUTS (8)

/* SPI module features */

/* @brief Has SPOL0 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL0 (1)
/* @brief Has SPOL1 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL1 (1)
/* @brief Has SPOL2 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL2 (0)
/* @brief Has SPOL3 bitfile in CFG reigster. */
#define FSL_FEATURE_SPI_HAS_SSEL3 (0)

/* SWM module features */

/* @brief Has SWM PINENABLE0 ACMP I3. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I3 (1)
/* @brief Has SWM PINENABLE0 ACMP I4. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I4 (1)
/* @brief Has SWM PINENABLE0 ACMP I5. */
#define FSL_FEATURE_SWM_HAS_PINENABLE0_ACMP_I5 (1)
/* @brief Has PINASSIGNFIXED0 register. */
#define FSL_FEATURE_SWM_HAS_PINASSIGNFIXED0_REGISTER  (1)

/* SYSCON module features */

/* @brief Pointer to ROM IAP entry functions */
#define FSL_FEATURE_SYSCON_IAP_ENTRY_LOCATION (0x0F001FF1)
/* @brief Flash page size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_PAGE_SIZE_BYTES (64)
/* @brief Flash sector size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SECTOR_SIZE_BYTES (1024)
/* @brief Flash size in bytes */
#define FSL_FEATURE_SYSCON_FLASH_SIZE_BYTES (32640)
/* @brief IAP has Flash read & write function */
#define FSL_FEATURE_IAP_HAS_FLASH_FUNCTION (1)
/* @brief Starter register discontinuous. */
#define FSL_FEATURE_SYSCON_STARTER_DISCONTINUOUS (1)
/* @brief Has PINTSEL register. */
#define FSL_FEATURE_SYSCON_HAS_PINT_SEL_REGISTER (1)
/* @brief Has fixed reference clock for flash controller */
#define FSL_FEATURE_SYSCON_HAS_FLASH_REFERENCE_CLOCK (1)

/* USART module features */

/* @brief Has OSR (register OSR). */
#define FSL_FEATURE_USART_HAS_OSR_REGISTER (1)
/* @brief Has TXIDLEEN bitfile in INTENSET reigster. */
#define FSL_FEATURE_USART_HAS_INTENSET_TXIDLEEN (1)
/* @brief Has ABERREN bitfile in INTENSET reigster. */
#define FSL_FEATURE_USART_HAS_ABERR_CHECK (1)

/* WKT module features */

/* @brief Has SEL_EXTCLK bitfile in CTRL reigster. */
#define FSL_FEATURE_WKT_HAS_CTRL_SEL_EXTCLK (1)

/* WWDT module features */

/* @brief Has no RESET register. */
#define FSL_FEATURE_WWDT_HAS_NO_RESET (1)
/* @brief Has LPOSC as clock source. */
#define FSL_FEATURE_WWDT_HAS_LPOSC_CLOCK_SOURCE (1)

#endif /* _LPC804_FEATURES_H_ */

