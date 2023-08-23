/*
 * Copyright (c) 2021-2023, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCUSWOCONFIG_H_
#define MCUSWOCONFIG_H_

#ifndef McuSWO_CONFIG_HAS_SWO
  #define McuSWO_CONFIG_HAS_SWO          (0)
  /*!< 1: MCU has SWO; 0: MCUS does not have SWO */
#endif

#ifndef McuSWO_CONFIG_SPEED_BAUD
  #define McuSWO_CONFIG_SPEED_BAUD       (96000000)
  /*!< baud of SWO data. Note that the J-Link can consume up to 400 kHz. */
#endif

#ifndef McuSWO_CONFIG_TERMINAL_CHANNEL
  #define McuSWO_CONFIG_TERMINAL_CHANNEL   (0)
  /*!< default SWO channel/stimulus for terminal */
#endif

#ifndef McuSWO_CONFIG_DO_MUXING
  #define McuSWO_CONFIG_DO_MUXING        (1)
    /*! if SWO pin muxing shall be done inside McuSWO_Init(). Otherwise pin muxing is responsible of the application */
#endif

#ifndef McuSWO_CONFIG_DO_CLOCKING
  #define McuSWO_CONFIG_DO_CLOCKING    (1)
    /*! if SWO clocking shall be configured inside McuSWO_Init(). Otherwise pin muxing is responsible of the application */
#endif

#ifndef McuSWO_CONFIG_DO_SWO_INIT
  #define McuSWO_CONFIG_DO_SWO_INIT    (1)
    /*! if SWO/ITM device shall be initialized inside McuSWO_Init(). Otherwise it needs to be done in the application or in the debugger. */
#endif

#ifndef McuSWO_CONFIG_RETARGET_STDIO
  #define McuSWO_CONFIG_RETARGET_STDIO    (0)
    /*! 1: implement hooks to re-target stdin (e.g. scanf()) input and stdout (printf()) output. */
#endif

#ifndef McuSWO_CONFIG_PC_SAMPLING
  #define McuSWO_CONFIG_PC_SAMPLING   (0)
  /*!< if SWO PC sampling is turned on */
#endif

#ifndef McuSWO_CONFIG_SHELL_ENABLED
  #define McuSWO_CONFIG_SHELL_ENABLED    (1)
    /*!< 1: Shell support enabled; 0: no command line shell */
#endif

#endif /* MCUSWOCONFIG_H_ */
