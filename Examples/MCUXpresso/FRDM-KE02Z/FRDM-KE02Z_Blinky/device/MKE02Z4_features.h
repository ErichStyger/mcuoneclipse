/*
** ###################################################################
**     Version:             rev. 1.0, 2017-05-19
**     Build:               b201014
**
**     Abstract:
**         Chip specific module features.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2020 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2017-05-19)
**         Initial version.
**
** ###################################################################
*/

#ifndef _MKE02Z4_FEATURES_H_
#define _MKE02Z4_FEATURES_H_

/* SOC module features */

/* @brief ACMP availability on the SoC. */
#define FSL_FEATURE_SOC_ACMP_COUNT (2)
/* @brief ADC availability on the SoC. */
#define FSL_FEATURE_SOC_ADC_COUNT (1)
/* @brief CRC availability on the SoC. */
#define FSL_FEATURE_SOC_CRC_COUNT (1)
/* @brief FGPIO availability on the SoC. */
#define FSL_FEATURE_SOC_FGPIO_COUNT (2)
/* @brief FTM availability on the SoC. */
#define FSL_FEATURE_SOC_FTM_COUNT (3)
/* @brief FTMRH availability on the SoC. */
#define FSL_FEATURE_SOC_FTMRH_COUNT (1)
/* @brief GPIO availability on the SoC. */
#define FSL_FEATURE_SOC_GPIO_COUNT (2)
/* @brief I2C availability on the SoC. */
#define FSL_FEATURE_SOC_I2C_COUNT (1)
/* @brief ICS availability on the SoC. */
#define FSL_FEATURE_SOC_ICS_COUNT (1)
/* @brief IRQ availability on the SoC. */
#define FSL_FEATURE_SOC_IRQ_COUNT (1)
/* @brief KBI availability on the SoC. */
#define FSL_FEATURE_SOC_KBI_COUNT (2)
/* @brief MCM availability on the SoC. */
#define FSL_FEATURE_SOC_MCM_COUNT (1)
/* @brief OSC availability on the SoC. */
#define FSL_FEATURE_SOC_OSC_COUNT (1)
/* @brief PIT availability on the SoC. */
#define FSL_FEATURE_SOC_PIT_COUNT (1)
/* @brief PMC availability on the SoC. */
#define FSL_FEATURE_SOC_PMC_COUNT (1)
/* @brief PORT availability on the SoC. */
#define FSL_FEATURE_SOC_PORT_COUNT (1)
/* @brief ROM availability on the SoC. */
#define FSL_FEATURE_SOC_ROM_COUNT (1)
/* @brief RTC availability on the SoC. */
#define FSL_FEATURE_SOC_RTC_COUNT (1)
/* @brief SIM availability on the SoC. */
#define FSL_FEATURE_SOC_SIM_COUNT (1)
/* @brief SPI availability on the SoC. */
#define FSL_FEATURE_SOC_SPI_COUNT (2)
/* @brief UART availability on the SoC. */
#define FSL_FEATURE_SOC_UART_COUNT (3)
/* @brief WDOG availability on the SoC. */
#define FSL_FEATURE_SOC_WDOG_COUNT (1)

/* ADC module features */

/* @brief Has status and control register 5. */
#define FSL_FEATURE_ADC_HAS_SC5_REG (0)
/* @brief Has hardware trigger multiple conversion enable. */
#define FSL_FEATURE_ADC_HAS_SC4_HTRGME (0)

/* CRC module features */

/* @brief Has data register with name CRC */
#define FSL_FEATURE_CRC_HAS_CRC_REG (0)

/* FGPIO module features */

/* No feature definitions */

/* FTM module features */

/* @brief Number of channels. */
#define FSL_FEATURE_FTM_CHANNEL_COUNTn(x) (8)
/* @brief Has counter reset by the selected input capture event (register bits C0SC[ICRST], C1SC[ICRST], ...). */
#define FSL_FEATURE_FTM_HAS_COUNTER_RESET_BY_CAPTURE_EVENT (0)
/* @brief Has extended deadtime value. */
#define FSL_FEATURE_FTM_HAS_EXTENDED_DEADTIME_VALUE (0)
/* @brief Enable pwm output for the module. */
#define FSL_FEATURE_FTM_HAS_ENABLE_PWM_OUTPUT (0)
/* @brief Has half-cycle reload for the module. */
#define FSL_FEATURE_FTM_HAS_HALFCYCLE_RELOAD (0)
/* @brief Has reload interrupt. */
#define FSL_FEATURE_FTM_HAS_RELOAD_INTERRUPT (0)
/* @brief Has reload initialization trigger. */
#define FSL_FEATURE_FTM_HAS_RELOAD_INITIALIZATION_TRIGGER (0)
/* @brief Has DMA support, bitfield CnSC[DMA]. */
#define FSL_FEATURE_FTM_HAS_DMA_SUPPORT (0)
/* @brief If channel 6 is used to generate channel trigger, bitfield EXTTRIG[CH6TRIG]. */
#define FSL_FEATURE_FTM_HAS_CHANNEL6_TRIGGER (0)
/* @brief If channel 7 is used to generate channel trigger, bitfield EXTTRIG[CH7TRIG]. */
#define FSL_FEATURE_FTM_HAS_CHANNEL7_TRIGGER (0)
/* @brief Has no QDCTRL. */
#define FSL_FEATURE_FTM_HAS_NO_QDCTRL (1)
/* @brief If instance has only TPM function. */
#define FSL_FEATURE_FTM_IS_TPM_ONLY_INSTANCEn(x) \
    (((x) == FTM0) ? (1) : \
    (((x) == FTM1) ? (1) : \
    (((x) == FTM2) ? (0) : (-1))))
/* @brief TPM Has no CONF. */
#define FSL_FEATURE_TPM_HAS_NO_CONF (1)
/* @brief There is CLKS bit in SC register. */
#define FSL_FEATURE_TPM_HAS_SC_CLKS (1)
/* @brief Wait CnV register is updated after CnV register is written. */
#define FSL_FEATURE_TPM_WAIT_CnV_REGISTER_UPDATE (1)
/* @brief CHF is cleared by write a 0 to the CHF bit in CnSC register. */
#define FSL_FEATURE_TPM_CnSC_CHF_WRITE_0_CLEAR (1)
/* @brief Has no STATUS. */
#define FSL_FEATURE_TPM_HAS_NO_STATUS (1)
/* @brief Number of channels. */
#define FSL_FEATURE_TPM_CHANNEL_COUNTn(x) ((x) == TPM0 ? (2) : ((x) == TPM1 ? (2) : (-1)))

/* FTMRH module features */

/* @brief Is of type FTMRE. */
#define FSL_FEATURE_FLASH_IS_FTMRE (0U)
/* @brief Is of type FTMRH. */
#define FSL_FEATURE_FLASH_IS_FTMRH (1U)
/* @brief Has EEPROM region protection (register FEPROT). */
#define FSL_FEATURE_FLASH_HAS_EEROM_REGION_PROTECTION (0U)
/* @brief Has flash cache control in FMC module. */
#define FSL_FEATURE_FLASH_HAS_FMC_FLASH_CACHE_CONTROLS (0U)
/* @brief Has flash cache control in MCM module. */
#define FSL_FEATURE_FLASH_HAS_MCM_FLASH_CACHE_CONTROLS (1U)
/* @brief P-Flash higher region start address. */
#define FSL_FEATURE_FLASH_PFLASH_HIGH_START_ADDRESS (0x00007FFFUL)
/* @brief P-Flash start address. */
#define FSL_FEATURE_FLASH_PFLASH_START_ADDRESS (0x00000000UL)
/* @brief P-Flash block count. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT (1U)
/* @brief P-Flash block size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE (65536UL)
/* @brief P-Flash sector size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE (512UL)
/* @brief P-Flash write unit size. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE (8U)
/* @brief P-Flash data path width. */
#define FSL_FEATURE_FLASH_PFLASH_BLOCK_DATA_PATH_WIDTH (16U)
/* @brief Has EEPROM memory. */
#define FSL_FEATURE_FLASH_HAS_EEPROM (1U)
/* @brief EEPROM start address. */
#define FSL_FEATURE_FLASH_EEPROM_START_ADDRESS (0x10000000UL)
/* @brief EEPROM block count. */
#define FSL_FEATURE_FLASH_EEPROM_BLOCK_COUNT (1U)
/* @brief EEPROM block size . */
#define FSL_FEATURE_FLASH_EEPROM_BLOCK_SIZE (256UL)
/* @brief EEPROM sector size. */
#define FSL_FEATURE_FLASH_EEPROM_BLOCK_SECTOR_SIZE (2U)
/* @brief EEPROM write unit size. */
#define FSL_FEATURE_FLASH_EEPROM_BLOCK_WRITE_UNIT_SIZE (8U)
/* @brief EEPROM data path width. */
#define FSL_FEATURE_FLASH_EEPROM_BLOCK_DATA_PATH_WIDTH (8U)
/* @brief Has 0x01 Erase Verify All Blocks command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_VERIFY_ALL_BLOCKS_CMD (1U)
/* @brief Has 0x02 Erase Verify Block command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_VERIFY_BLOCK_CMD (1U)
/* @brief Has 0x03 Erase Verify Flash Section command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_VERIFY_FLASH_SECTION_CMD (1U)
/* @brief Has 0x04 Read Once command. */
#define FSL_FEATURE_FLASH_HAS_READ_ONCE_CMD (1U)
/* @brief Has 0x06 Program Flash command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_FLASH_CMD (1U)
/* @brief Has 0x07 Program Once command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_ONCE_CMD (1U)
/* @brief Has 0x08 Erase All Blocks command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_ALL_BLOCKS_CMD (1U)
/* @brief Has 0x09 Erase Flash Block command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_FLASH_BLOCK_CMD (1U)
/* @brief Has 0x0A Erase Flash Sector command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_FLASH_SECTOR_CMD (1U)
/* @brief Has 0x0B Unsecure Flash command. */
#define FSL_FEATURE_FLASH_HAS_UNSECURE_FLASH_CMD (1U)
/* @brief Has 0x0C Verify Backdoor Access Key command. */
#define FSL_FEATURE_FLASH_HAS_VERIFY_BACKDOOR_ACCESS_KEY_CMD (1U)
/* @brief Has 0x0D Set User Margin Level command. */
#define FSL_FEATURE_FLASH_HAS_SET_USER_MARGIN_LEVEL_CMD (1U)
/* @brief Has 0x0E Set Factory Margin Level command. */
#define FSL_FEATURE_FLASH_HAS_SET_FACTORY_MARGIN_LEVEL_CMD (1U)
/* @brief Has 0x0F Configure NVM command. */
#define FSL_FEATURE_FLASH_HAS_CONFIGURE_NVM_CMD (1U)
/* @brief Has 0x10 Erase Verify EEPROM Section command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_VERIFY_EEPROM_SECTION_CMD (1U)
/* @brief Has 0x11 Program EEPROM command. */
#define FSL_FEATURE_FLASH_HAS_PROGRAM_EEPROM_CMD (1U)
/* @brief Has 0x12 Erase EEPROM Sector command. */
#define FSL_FEATURE_FLASH_HAS_ERASE_EEPROM_SECTOR_CMD (1U)
/* @brief P-Flash Erase sector command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT (4U)
/* @brief P-Flash Rrogram/Verify section command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT (4U)
/* @brief P-Flash Program flash command address alignment. */
#define FSL_FEATURE_FLASH_PFLASH_PROGRAM_CMD_ADDRESS_ALIGMENT (4U)

/* GPIO module features */

/* @brief Has GPIO attribute checker register (GACR). */
#define FSL_FEATURE_GPIO_HAS_ATTRIBUTE_CHECKER (0)

/* I2C module features */

/* @brief Has System Management Bus support (registers SMB, A2, SLTL and SLTH). */
#define FSL_FEATURE_I2C_HAS_SMBUS (1)
/* @brief Maximum supported baud rate in kilobit per second. */
#define FSL_FEATURE_I2C_MAX_BAUD_KBPS (400)
/* @brief Is affected by errata with ID 6070 (repeat start cannot be generated if the F[MULT] bit field is set to a
 * non-zero value). */
#define FSL_FEATURE_I2C_HAS_ERRATA_6070 (0)
/* @brief Has DMA support (register bit C1[DMAEN]). */
#define FSL_FEATURE_I2C_HAS_DMA_SUPPORT (0)
/* @brief Has I2C bus start and stop detection (register bits FLT[SSIE], FLT[STARTF] and FLT[STOPF]). */
#define FSL_FEATURE_I2C_HAS_START_STOP_DETECT (1)
/* @brief Has I2C bus stop detection (register bits FLT[STOPIE] and FLT[STOPF]). */
#define FSL_FEATURE_I2C_HAS_STOP_DETECT (0)
/* @brief Has I2C bus stop hold off (register bit FLT[SHEN]). */
#define FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF (1)
/* @brief Maximum width of the glitch filter in number of bus clocks. */
#define FSL_FEATURE_I2C_MAX_GLITCH_FILTER_WIDTH (15)
/* @brief Has control of the drive capability of the I2C pins. */
#define FSL_FEATURE_I2C_HAS_HIGH_DRIVE_SELECTION (0)
/* @brief Has double buffering support (register S2). */
#define FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING (0)
/* @brief Has double buffer enable. */
#define FSL_FEATURE_I2C_HAS_DOUBLE_BUFFER_ENABLE (0)

/* KBI module features */

/* @brief KBI module has source pin. */
#define FSL_FEATURE_KBI_HAS_SOURCE_PIN (0)
/* @brief KBI register width. */
#define FSL_FEATURE_KBI_REG_WIDTH (8)

/* PIT module features */

/* @brief Number of channels (related to number of registers LDVALn, CVALn, TCTRLn, TFLGn). */
#define FSL_FEATURE_PIT_TIMER_COUNT (2)
/* @brief Has lifetime timer (related to existence of registers LTMR64L and LTMR64H). */
#define FSL_FEATURE_PIT_HAS_LIFETIME_TIMER (0)
/* @brief Has chain mode (related to existence of register bit field TCTRLn[CHN]). */
#define FSL_FEATURE_PIT_HAS_CHAIN_MODE (1)
/* @brief Has shared interrupt handler (has not individual interrupt handler for each channel). */
#define FSL_FEATURE_PIT_HAS_SHARED_IRQ_HANDLER (0)
/* @brief Has timer enable control. */
#define FSL_FEATURE_PIT_HAS_MDIS (1)

/* SPI module features */

/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_SPI_HAS_FIFO (0)
/* @brief Has DMA support (register bit fields C2[RXDMAE] and C2[TXDMAE]). */
#define FSL_FEATURE_SPI_HAS_DMA_SUPPORT (0)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_SPI_HAS_SEPARATE_DMA_RX_TX_REQn(x) (0)
/* @brief Receive/transmit FIFO size in number of 16-bit communication items. */
#define FSL_FEATURE_SPI_FIFO_SIZEn(x) (0)
/* @brief Maximum transfer data width in bits. */
#define FSL_FEATURE_SPI_MAX_DATA_WIDTH (8)
/* @brief The data register name has postfix (L as low and H as high). */
#define FSL_FEATURE_SPI_DATA_REGISTER_HAS_POSTFIX (0)
/* @brief Has separated TXDATA and CMD FIFOs (register SREX). */
#define FSL_FEATURE_SPI_HAS_SEPARATE_TXDATA_CMD_FIFO (0)
/* @brief Has 16-bit data transfer support. */
#define FSL_FEATURE_SPI_16BIT_TRANSFERS (0)

/* UART module features */

/* @brief Has receive FIFO overflow detection (bit field CFIFO[RXOFE]). */
#define FSL_FEATURE_UART_HAS_IRQ_EXTENDED_FUNCTIONS (1)
/* @brief Has low power features (can be enabled in wait mode via register bit C1[DOZEEN] or CTRL[DOZEEN] if the
 * registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_LOW_POWER_UART_SUPPORT (0)
/* @brief Has extended data register ED (or extra flags in the DATA register if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS (0)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_UART_HAS_FIFO (0)
/* @brief Hardware flow control (RTS, CTS) is supported. */
#define FSL_FEATURE_UART_HAS_MODEM_SUPPORT (0)
/* @brief Infrared (modulation) is supported. */
#define FSL_FEATURE_UART_HAS_IR_SUPPORT (0)
/* @brief 2 bits long stop bit is available. */
#define FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT (1)
/* @brief If 10-bit mode is supported. */
#define FSL_FEATURE_UART_HAS_10BIT_DATA_SUPPORT (0)
/* @brief Baud rate fine adjustment is available. */
#define FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT (0)
/* @brief Baud rate oversampling is available (has bit fields C4[OSR], C5[BOTHEDGE], C5[RESYNCDIS] or BAUD[OSR],
 * BAUD[BOTHEDGE], BAUD[RESYNCDIS] if the registers are 32-bit wide). */
#define FSL_FEATURE_UART_HAS_BAUD_RATE_OVER_SAMPLING_SUPPORT (0)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_UART_HAS_RX_RESYNC_SUPPORT (1)
/* @brief Baud rate oversampling is available. */
#define FSL_FEATURE_UART_HAS_BOTH_EDGE_SAMPLING_SUPPORT (1)
/* @brief Peripheral type. */
#define FSL_FEATURE_UART_IS_SCI (0)
/* @brief Capacity (number of entries) of the transmit/receive FIFO (or zero if no FIFO is available). */
#define FSL_FEATURE_UART_FIFO_SIZE (0)
/* @brief Supports two match addresses to filter incoming frames. */
#define FSL_FEATURE_UART_HAS_ADDRESS_MATCHING (0)
/* @brief Has transmitter/receiver DMA enable bits C5[TDMAE]/C5[RDMAE] (or BAUD[TDMAE]/BAUD[RDMAE] if the registers are
 * 32-bit wide). */
#define FSL_FEATURE_UART_HAS_DMA_ENABLE (0)
/* @brief Has transmitter/receiver DMA select bits C4[TDMAS]/C4[RDMAS], resp. C5[TDMAS]/C5[RDMAS] if IS_SCI = 0. */
#define FSL_FEATURE_UART_HAS_DMA_SELECT (0)
/* @brief Data character bit order selection is supported (bit field S2[MSBF] or STAT[MSBF] if the registers are 32-bit
 * wide). */
#define FSL_FEATURE_UART_HAS_BIT_ORDER_SELECT (0)
/* @brief Has smart card (ISO7816 protocol) support and no improved smart card support. */
#define FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT (0)
/* @brief Has improved smart card (ISO7816 protocol) support. */
#define FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT (0)
/* @brief Has local operation network (CEA709.1-B protocol) support. */
#define FSL_FEATURE_UART_HAS_LOCAL_OPERATION_NETWORK_SUPPORT (0)
/* @brief Has 32-bit registers (BAUD, STAT, CTRL, DATA, MATCH, MODIR) instead of 8-bit (BDH, BDL, C1, S1, D, etc.). */
#define FSL_FEATURE_UART_HAS_32BIT_REGISTERS (0)
/* @brief Lin break detect available (has bit BDH[LBKDIE]). */
#define FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT (1)
/* @brief UART stops in Wait mode available (has bit C1[UARTSWAI]). */
#define FSL_FEATURE_UART_HAS_WAIT_MODE_OPERATION (1)
/* @brief Has separate DMA RX and TX requests. */
#define FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(x) (0)

#endif /* _MKE02Z4_FEATURES_H_ */

