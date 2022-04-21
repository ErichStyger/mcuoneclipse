/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#define PL_CONFIG_USE_SHELL       (0) /* if using command line shell */
#define PL_CONFIG_USE_SHELL_UART  (1 && PL_CONFIG_USE_SHELL) /* if using shell with UART */
#define PL_CONFIG_USE_RTT         (0) /* if using RTT for shell */
#define PL_CONFIG_USE_USB_CDC     (0) /* if implementing a USB CDC device and use it for the shell */
#define PL_CONFIG_USE_SD_CARD     (0) /* if implementing using a SD card */
#define PL_CONFIG_USE_MININI      (1 && PL_CONFIG_USE_SD_CARD)
#define PL_CONFIG_USE_USB_MSD     (0) /* if using USB MSD device */
#define PL_CONFIG_USE_SWO         (0) /* for J-Link: need to call SWO_SetSpeed()! */
#define PL_CONFIG_INIT_SWO        (1 && PL_CONFIG_USE_SWO) /* if SWO shall be initialized by the application and not by the debugger */

#define PL_CONFIG_USE_I2C         (1) /* if I2C peripherals are used */
#define PL_CONFIG_USE_HW_I2C      (USE_HW_I2C && PL_CONFIG_USE_I2C) /* USE_HW_I2C defined in IncludeMcuLibConfig.h */
#define PL_CONFIG_USE_OLED        (1 && PL_CONFIG_USE_I2C)
#define PL_CONFIG_USE_EXT_I2C_RTC (1)
#define PL_CONFIG_USE_NVMC        (1) /* if flash non-volatile memory is used to store data */

#define PL_CONFIG_USE_LED1          (1) /* Tx indication */
#define PL_CONFIG_USE_LED2          (0) /* Rx indication, LED not supported on LPC55S16-EVK */
#define PL_CONFIG_USE_UART2         (0)

#define PL_CONFIG_USE_SHT31			(1)


#define PL_CONFIG_USE_W25Q        (1) /* if flash non-volatile memory is used to store data */

#define PL_CONFIG_USE_littleFS        (0) /* if flash non-volatile memory is used to store data */

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
#define PL_CONFIG_FLASH_NVM_ADDR_START      (((0+240*1024)-((PL_CONFIG_FLASH_NVM_NOF_BLOCKS+McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS)*PL_CONFIG_FLASH_NVM_BLOCK_SIZE))) /* last block in FLASH, start address of configuration data in flash */
#define PL_CONFIG_FLASH_NVM_BLOCK_SIZE      (McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE)   /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#define PL_CONFIG_FLASH_NVM_NOF_BLOCKS      (8) /* number of flash blocks, need >1804 bytes with US915 for EEPROM! */



/* module and platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
