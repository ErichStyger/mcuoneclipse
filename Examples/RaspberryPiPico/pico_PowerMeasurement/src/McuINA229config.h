/*
 * Copyright (c) 2025, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef McuINA229_CONFIG_H_
#define McuINA229_CONFIG_H_

#ifndef McuINA229_CONFIG_PARSE_COMMAND_ENABLED
  #define McuINA229_CONFIG_PARSE_COMMAND_ENABLED    (1)
    /*!< If shell parser is enabled (1) or not (0). */
#endif

#ifndef McuINA229_CONFIG_CS_PIN_NUMBER
  #define McuINA229_CONFIG_CS_PIN_NUMBER    (-1)
    /*!< GPIO pin number for chip select, -1 means it is not used. */
#endif

#ifndef McuINA229_CONFIG_ALERT_PIN_NUMBER
  #define McuINA229_CONFIG_ALERT_PIN_NUMBER    (-1)
    /*!< GPIO pin number for chip select, -1 means it is not used. */
#endif

#endif /* McuINA229_CONFIG_H_ */