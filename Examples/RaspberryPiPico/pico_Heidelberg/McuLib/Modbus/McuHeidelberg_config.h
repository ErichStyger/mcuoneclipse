/*
 * Copyright (c) 2022, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MODBUS_MCUHEIDELBERG_CONFIG_H_
#define MODBUS_MCUHEIDELBERG_CONFIG_H_

#ifndef McuHeidelberg_CONFIG_USE_MOCK_WALLBOX
  #define McuHeidelberg_CONFIG_USE_MOCK_WALLBOX  (1) /*!< if using testing mocks for wallbox state and phase values instead of real state */
#endif

#ifndef McuHeidelberg_CONFIG_USE_MOCK_SOLAR
  #define McuHeidelberg_CONFIG_USE_MOCK_SOLAR     (1) /*!< if using testing mocks for solar and site power instead of real power */
#endif

#endif /* MODBUS_MCUHEIDELBERG_CONFIG_H_ */
