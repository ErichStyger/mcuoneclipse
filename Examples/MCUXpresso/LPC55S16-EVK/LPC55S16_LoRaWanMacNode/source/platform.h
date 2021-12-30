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

#define PL_CONFIG_USE_LED1          (1) /* Tx */
#define PL_CONFIG_USE_LED2          (0) /* Rx, LED not supported on LPC55S16-EVK */
#define PL_CONFIG_USE_UART2         (0)

/* FLASH storage parameters, used for EEPROM Emulation */
#define PL_CONFIG_FLASH_NVM_ADDR_START      (((0+244*1024)-((PL_CONFIG_FLASH_NVM_NOF_BLOCKS+McuMinINI_CONFIG_FLASH_NVM_NOF_BLOCKS)*PL_CONFIG_FLASH_NVM_BLOCK_SIZE))) /* last block in FLASH, start address of configuration data in flash */
#define PL_CONFIG_FLASH_NVM_BLOCK_SIZE      (McuMinINI_CONFIG_FLASH_NVM_BLOCK_SIZE)   /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#define PL_CONFIG_FLASH_NVM_NOF_BLOCKS      (3)       /* number of flash blocks, need >1024 bytes! */

/* module and platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
