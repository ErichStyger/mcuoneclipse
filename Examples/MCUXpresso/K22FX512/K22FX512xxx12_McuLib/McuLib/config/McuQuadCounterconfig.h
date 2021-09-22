/**
 * \file
 * \brief Configuration header file for QuadCounter component
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the quadrature counter module.
 */

#ifndef __McuQuadCounter_CONFIG_H
#define __McuQuadCounter_CONFIG_H

#ifndef McuQuadCounter_CONFIG_USE_ERROR_CORRECTION
  #define McuQuadCounter_CONFIG_USE_ERROR_CORRECTION  (0)
    /*!< 1: Use error correction, 0: not using error correction */
#endif

#ifndef McuQuadCounter_CONFIG_COUNT_ERRORS
  #define McuQuadCounter_CONFIG_COUNT_ERRORS  (1)
    /*!< 1: count errors, 0: do not count errors */
#endif

#endif /* __McuQuadCounter_CONFIG_H */
