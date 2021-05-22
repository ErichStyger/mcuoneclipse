/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSWOCONFIG_H_
#define MCUSWOCONFIG_H_

#ifndef McuSWO_CONFIG_SPEED
  #define McuSWO_CONFIG_SPEED         (64000)
  /*!< baud of SWO data */
#endif

#ifndef McuSWO_CONFIG_PC_SAMPLING
  #define McuSWO_CONFIG_PC_SAMPLING   (1)
  /*!< if SWO PC sampling is turned on */
#endif

#endif /* MCUSWOCONFIG_H_ */
