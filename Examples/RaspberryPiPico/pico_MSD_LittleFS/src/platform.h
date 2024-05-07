/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_BOARD_H_
#define PLATFORM_BOARD_H_

#define PL_CONFIG_USE_RTT             (1) /* if using RTT */
#define PL_CONFIG_USE_USB_CDC         (0) /* if using USB CDC for command line shell */
#define PL_CONFIG_USE_SHELL           (1) /* if using command line shell */

#define PL_CONFIG_USE_INTERNAL_FLASH  (1) /* if using internal flash, e.g. for MinINI or LittleFS */

#define PL_CONFIG_USE_LITTLE_FS       (1 && PL_CONFIG_USE_INTERNAL_FLASH && LITTLEFS_CONFIG_ENABLED)

#define PL_CONFIG_USE_MININI          (1 && PL_CONFIG_USE_INTERNAL_FLASH && McuMinINI_CONFIG_FS==McuMinINI_CONFIG_FS_TYPE_LITTLE_FS)
    /*!< type of MinINI is configured in McuMinINI_CONFIG_FS of IncludeMcuLibConfig. */

#define PL_CONFIG_USE_TINY_USB        (1 && PL_CONFIG_USE_LITTLE_FS) /* using tinyUSB as MSD device for LittleFS volume */

void PL_Init(void);

#endif /* PLATFORM_BOARD_H_ */
