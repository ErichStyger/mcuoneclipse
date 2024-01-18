/*
 * Copyright (c) 2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef McuINA260_CONFIG_H_
#define McuINA260_CONFIG_H_

#ifndef McuINA260_CONFIG_PARSE_COMMAND_ENABLED
  #define McuINA260_CONFIG_PARSE_COMMAND_ENABLED    (1)
    /*!< If shell parser is enabled (1) or not (0). */
#endif

#ifndef McuINA260_CONFIG_I2C_ADDRESS
  #define McuINA260_CONFIG_I2C_ADDRESS              (0x40)
    /*! I2C address of the sensor, default 0x40 */
#endif

#endif /* McuINA260_CONFIG_H_ */