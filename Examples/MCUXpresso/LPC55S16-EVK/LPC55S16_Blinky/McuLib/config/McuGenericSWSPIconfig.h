/**
 * \file
 * \brief Configuration header file for GenericSWSPI
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the software (bit-banging) SPI module.
 */

#ifndef __McuGenericSWSPI_CONFIG_H
#define __McuGenericSWSPI_CONFIG_H

#ifndef McuGenericSWSPI_CONFIG_CLOCK_POLARITY
  #define McuGenericSWSPI_CONFIG_CLOCK_POLARITY  0
    /*!< 0: clock is low if idle; 1: clock is high if idle */
#endif

#ifndef McuGenericSWSPI_CONFIG_CLOCK_EDGE
  #define McuGenericSWSPI_CONFIG_CLOCK_EDGE  0
    /*!< 0: data is shifted on falling clock edge; 1: data is shifted on rising clock edge */
#endif


#endif /* __McuGenericSWSPI_CONFIG_H */

