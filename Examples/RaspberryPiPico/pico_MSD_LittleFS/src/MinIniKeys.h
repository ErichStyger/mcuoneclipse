/*
 * Copyright (c) 2022-2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MININIKEYS_H_
#define MININIKEYS_H_

/* strings and names used in minINI configuration file */

#define NVMC_MININI_FILE_NAME       "SETTINGS.INI" /* 'file' name used */

/* settings for application LED */
#define NVMC_MININI_SECTION_LED               "LED"
#define NVMC_MININI_KEY_LED_DELAY_MS             "delayMs"     /* LED blinky delay in ms  */
#define NVMC_MININI_KEY_LED_DELAY_MS_DEFAULT     1000          /* LED blinky default delay in ms  */

#endif /* MININIKEYS_H_ */
