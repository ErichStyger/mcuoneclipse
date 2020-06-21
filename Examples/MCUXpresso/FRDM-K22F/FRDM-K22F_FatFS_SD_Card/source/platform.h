/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

/* Features */
#define PL_CONFIG_USE_SD_CARD       (1) /* if using FatFS with SD card */
#define PL_CONFIG_USE_USB_MSD       (1) /* if using FatFS with USB MSD */
#define PL_CONFIG_USE_USB_MSD_TEST  (0) /* if after connecting a device it shall run a test suite */
#define PL_CONFIG_USE_LOGGING       (1) /* if using logging */
#define PL_CONFIG_USE_MININI        (1 && PL_CONFIG_USE_SD_CARD) /* if using minIni */

#define PL_CONFIG_USE_I2C           (1) /* use I2C bus: SCL PTB0, SDA PTB1 */
#define PL_CONFIG_USE_HW_I2C        (CONFIG_USE_HW_I2C) /* using hardware I2C and not software I2C: set in IncludeMcuLibConfig.h  */
#define PL_CONFIG_USE_EXT_I2C_RTC   (1 && PL_CONFIG_USE_I2C) /* configure the RTC handling in the IncludeMcuLibConfig.h, set McuExtRTC_CONFIG_DEVICE */

/* Shell */
#define PL_CONFIG_USE_SHELL         (1) /* if using shell */
#define PL_CONFIG_USE_SHELL_UART    (1) /* if using (OpenSDA) UART */
#define PL_CONFIG_USE_SHELL_UART0   (0) /* if using UART0 (PTB16 (Rx), PTB17 (Tx)). Set McuShellUart_CONFIG_UART in IncludeMcuLibConfig.h  */
#define PL_CONFIG_USE_RTT           (1) /* if using RTT */
#define PL_CONFIG_USE_USB_CDC       (0) /* if using USB CDC */

void PL_InitFromTask(void);

/* platform initialization */
void PL_Init(void);

#endif /* PLATFORM_H_ */
