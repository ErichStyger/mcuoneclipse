/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL         (1)  /* if shell support is enabled */
#define PL_CONFIG_USE_SHELL_UART    (1 && McuLib_CONFIG_SDK_USE_FREERTOS)  /* using UART for shell */
#define PL_CONFIG_USE_RTT           (1)  /* using RTT as shell interface */
#define PL_CONFIG_USE_USB_CDC       (0)  /* using USB CDC for shell */
#define PL_CONFIG_USE_MININI        (1)  /* using MinINI with flash */

#define PL_CONFIG_USE_LED1          (1) /* Tx indication */
#define PL_CONFIG_USE_LED2          (0) /* Rx indication, LED not supported on LPC55S16-EVK */
#define PL_CONFIG_USE_UART2         (0)

/* FLASH storage parameters, used for EEPROM Emulation */
/* 4 pages (2.0 KByte) is reserved for EEPROM emulation buffer
 * 4 pages (2.0 KByte) is reserved for MinINI storage
 * 0x3C000  EEPROM
 * 0x3C200  EEPROM
 * 0x3C400  EEPROM
 * 0x3C600  EEPROM
 * 0x3C800  MinINI
 * 0x3CA00  MinINI
 * 0x3CC00  MinINI
 * 0x3CE00  MinINI
 */
#define PL_CONFIG_RADIO_TRANSEIVER_RFM96        (1)  /* if shell support is enabled */
#define PL_CONFIG_RADIO_TRANSEIVER_SX126x        (0)  /* if shell support is enabled */

#define PL_CONFIG_FLASH_NVM_ADDR_START      (((0+244*1024)-((PL_CONFIG_FLASH_NVM_NOF_BLOCKS+McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS)*PL_CONFIG_FLASH_NVM_BLOCK_SIZE))) /* last block in FLASH, start address of configuration data in flash */
#define PL_CONFIG_FLASH_NVM_BLOCK_SIZE      (McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE)   /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#define PL_CONFIG_FLASH_NVM_NOF_BLOCKS      (8) /* number of flash blocks, need >1804 bytes with US915 for EEPROM! */

/* module and platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
