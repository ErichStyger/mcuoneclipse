/*
 * Copyright (c) 2021, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSWOCONFIG_H_
#define MCUSWOCONFIG_H_

#ifndef McuSWO_CONFIG_SPEED_BAUD
  #define McuSWO_CONFIG_SPEED_BAUD         (64000)
  /*!< baud of SWO data */
#endif

#ifndef McuSWO_CONFIG_TERMINAL_CHANNEL
  #define McuSWO_CONFIG_TERMINAL_CHANNEL   (0)
  /*!< default SWO channel for terminal */
#endif

#ifndef McuSWO_CONFIG_PC_SAMPLING
  #define McuSWO_CONFIG_PC_SAMPLING   (0)
  /*!< if SWO PC sampling is turned on */
#endif

#endif /* MCUSWOCONFIG_H_ */
