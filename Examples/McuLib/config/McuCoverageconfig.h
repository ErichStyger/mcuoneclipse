/*!
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * \brief Configuration header file for the McuCoverage module.
 */

#ifndef MCUCOVERAGECONFIG_H_
#define MCUCOVERAGECONFIG_H_

#ifndef McuCoverage_CONFIG_IS_ENABLED
  #define McuCoverage_CONFIG_IS_ENABLED               (0)
    /*!< 1: Module is enabled; 0: Module is disabled, not adding anything to the application code */
#endif

#ifndef McuCoverage_CONFIG_USE_FREESTANDING
  #define McuCoverage_CONFIG_USE_FREESTANDING         (0 && McuCoverage_CONFIG_IS_ENABLED)
    /*!< 1: Implementation using a freestanding environment; 0: No freestanding environment */
#endif

#endif /* MCUCOVERAGECONFIG_H_ */
