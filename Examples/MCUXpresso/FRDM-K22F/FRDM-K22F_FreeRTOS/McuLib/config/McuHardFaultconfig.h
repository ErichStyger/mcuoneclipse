/**
 * \file
 * \brief Configuration header file for HardFault
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the HardFault module.
 */

#ifndef __McuHardFault_CONFIG_H
#define __McuHardFault_CONFIG_H

#include "McuLib.h" /* SDK and API used */

#define McuHardFault_CONFIG_SETTING_HAS_ACTLR   (1 || (McuLib_CPU_IS_ARM_CORTEX_M && McuLib_CONFIG_CORTEX_M>=3))
  /*!< 1: Cortex-M3, M4 have Auxiliary Control Register, ACTLR register */

#ifndef McuHardFault_CONFIG_SETTING_DISABLE_WRITE_BUFFER
  #define McuHardFault_CONFIG_SETTING_DISABLE_WRITE_BUFFER   (0 && McuHardFault_CONFIG_SETTING_HAS_ACTLR)
  /*!< 1: disable write buffer in ACTLR register */
#endif

#ifndef McuHardFault_CONFIG_SETTING_SEMIHOSTING
  #define McuHardFault_CONFIG_SETTING_SEMIHOSTING   (1)
  /*!< 1: do not stop in handler with semihosting and no debugger attached. 0: semihosting hardfault will stop target */
#endif


#endif /* __McuHardFault_CONFIG_H */
