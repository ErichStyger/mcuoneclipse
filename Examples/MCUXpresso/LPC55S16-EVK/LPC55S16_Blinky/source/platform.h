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

#define PL_CONFIG_USE_NVMC        (0) /* if flash non-volatile memory is used to store data */


#if PL_CONFIG_USE_LORA_SHIELD
  #define PL_CONFIG_HAS_USER_BUTTON    (0) /* pin connected on DIO5 of the transceiver */
  #define PL_CONFIG_HAS_HW_RTC         (1 && PL_CONFIG_USE_I2C) /* D53232MZ+ */
#else
  #define PL_CONFIG_HAS_USER_BUTTON    (1)
  #define PL_CONFIG_HAS_HW_RTC         (0)
#endif

/*!
 * \brief Module initialization
 */
void PL_Init(void);


#endif /* PLATFORM_H_ */
