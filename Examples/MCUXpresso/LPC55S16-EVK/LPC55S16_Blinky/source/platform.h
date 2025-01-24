/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifndef PL_CONFIG_USE_LORA_SHIELD
  #error "PL_CONFIG_USE_LORA_SHIELD needs be set in IncludeMcuLibConfig.h!"
#endif

#define PL_CONFIG_USE_SHELL       (1) /* if using command line shell */
#define PL_CONFIG_USE_SHELL_UART  (1 && PL_CONFIG_USE_SHELL) /* if using shell with UART */
#define PL_CONFIG_USE_RTT         (1) /* if using RTT for shell */
#define PL_CONFIG_USE_USB_CDC     (0) /* if implementing a USB CDC device and use it for the shell */
#define PL_CONFIG_USE_SD_CARD     (0) /* if implementing using a SD card */
#define PL_CONFIG_USE_MININI      (1 && (PL_CONFIG_USE_SD_CARD || PL_CONFIG_HAS_LITTLE_FS)) /* configure it as well with McuMinINI_CONFIG_FS in IncludeMcuLibConfig.h */
#define PL_CONFIG_USE_USB_MSD     (0) /* if using USB MSD device */
#define PL_CONFIG_USE_SWO         (1) /* for J-Link: need to call SWO_SetSpeed()! */
#define PL_CONFIG_INIT_SWO        (0 && PL_CONFIG_USE_SWO) /* if SWO shall be initialized by the application and not by the debugger. Disable for profiling in the IDE! */

#define PL_CONFIG_USE_I2C         (1 || PL_CONFIG_USE_LORA_SHIELD) /* if I2C peripherals are used */
#define PL_CONFIG_USE_HW_I2C      (USE_HW_I2C && PL_CONFIG_USE_I2C) /* USE_HW_I2C defined in IncludeMcuLibConfig.h */
#define PL_CONFIG_USE_OLED        (0 && PL_CONFIG_USE_I2C) /* GUI and OLED */

#define PL_CONFIG_USE_NVMC        (0) /* if flash non-volatile memory is used to store data */

#if PL_CONFIG_USE_LORA_SHIELD
  /* NOTE: this requires the JP9 on the LPC55S16-EVN to be *installed*, otherwise the SPI signals are driven by the debug interface.
   * But JP9 installed means it is not possible to use the UART over the LinkServer USB connection: RTT has to be used instead */
  #define PL_CONFIG_HAS_USER_BUTTON    (0) /* pin connected on DIO5 of the transceiver */
  #define PL_CONFIG_HAS_HW_RTC         (1 && PL_CONFIG_USE_I2C) /* D3232MZ+ */
  #define PL_CONFIG_HAS_LITTLE_FS      (1) /* littleFS with Winbond */
  #define PL_CONFIG_HAS_SHT31          (1 && PL_CONFIG_USE_I2C) /* Sensirion SHT31 */
#else
  #define PL_CONFIG_HAS_USER_BUTTON    (1)
  #define PL_CONFIG_HAS_HW_RTC         (0 && PL_CONFIG_USE_I2C)
  #define PL_CONFIG_HAS_LITTLE_FS      (1) /* littleFS with internal FLASH */
  #define PL_CONFIG_HAS_SHT31          (0 && PL_CONFIG_USE_I2C) /* Sensirion SHT31 */
#endif

/* flash memory for McuFlash */
#define PL_CONFIG_FLASH_NVM_ADDR_START      (McuFlash_CONFIG_MEM_START) /* last block in FLASH, start address of configuration data in flash */
#define PL_CONFIG_FLASH_NVM_BLOCK_SIZE      (McuFlash_CONFIG_FLASH_BLOCK_SIZE)   /* must match FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize) */
#define PL_CONFIG_FLASH_NVM_NOF_BLOCKS      (McuFlash_CONFIG_NOF_BLOCKS) /* number of flash blocks! */


/*!
 * \brief Module initialization
 */
void PL_Init(void);


#endif /* PLATFORM_H_ */
