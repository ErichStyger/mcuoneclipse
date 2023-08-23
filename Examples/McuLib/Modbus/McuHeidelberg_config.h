/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MODBUS_MCUHEIDELBERG_CONFIG_H_
#define MODBUS_MCUHEIDELBERG_CONFIG_H_

#ifndef McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
  #define McuHeidelberg_CONFIG_USE_MOCK_WALLBOX   (0)
    /*!< if using testing mocks for wallbox state and phase values instead of real state. Note this cannot be used with a real vehicle! */
#endif

#ifndef McuHeidelberg_CONFIG_USE_MOCK_SOLAR
  #define McuHeidelberg_CONFIG_USE_MOCK_SOLAR     (0)
    /*!< if using testing mocks for solar and site power instead of real power */
#endif

#ifndef McuHeidelberg_CONFIG_USE_WATCHDOG
  #define McuHeidelberg_CONFIG_USE_WATCHDOG       (0)
    /*!< if using MCU watchdog functionality. Currently not implemented */
#endif

#ifndef McuHeidelberg_CONFIG_SITE_BASE_POWER
  #define McuHeidelberg_CONFIG_SITE_BASE_POWER    (500)
    /*! If non-zero, use this value as the site base power */
#endif

#endif /* MODBUS_MCUHEIDELBERG_CONFIG_H_ */
