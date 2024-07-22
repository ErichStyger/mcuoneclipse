/*!
 * Copyright (c) 2024, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * \file
 * \brief Configuration header file for the McuCoverage module.
 */

#ifndef MCUCOVERAGECONFIG_H_
#define MCUCOVERAGECONFIG_H_

#ifndef McuCoverage_CONFIG_IS_ENABLED
  #define McuCoverage_CONFIG_IS_ENABLED            (1)
    /*!< 1: Module is enabled; 0: Module is disabled, not adding anything to the application code */
#endif

#ifndef McuCoverage_CONFIG_IS_STANDALONE
  #define McuCoverage_CONFIG_IS_STANDALONE            (1)
    /*!< 1: Implementation of standalone version; 0: No standalone support */
#endif

#endif /* MCUCOVERAGECONFIG_H_ */
