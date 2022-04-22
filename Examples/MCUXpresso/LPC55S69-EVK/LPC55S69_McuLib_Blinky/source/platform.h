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

#define PL_CONFIG_USE_SHELL       (1)
#define PL_CONFIG_USE_USB_CDC     (0)

#define PL_CONFIG_USE_I2C         (1) /* if I2C peripheral is used */
#define PL_CONFIG_USE_HW_I2C      (USE_HW_I2C && PL_CONFIG_USE_I2C) /* USE_HW_I2C defined in IncludeMcuLibConfig.h */
#define PL_CONFIG_USE_OLED        (1 && PL_CONFIG_USE_I2C)

void PL_Init(void);

#endif /* PLATFORM_H_ */
