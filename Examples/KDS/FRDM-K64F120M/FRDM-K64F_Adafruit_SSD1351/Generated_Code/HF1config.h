/**
 * \file
 * \brief Configuration header file for HardFault
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the HardFault module.
 */

#ifndef __HF1_CONFIG_H
#define __HF1_CONFIG_H

#include "MCUC1.h" /* SDK and API used */

#define HF1_CONFIG_SETTING_HAS_ACTLR   (1 || (MCUC1_CPU_IS_ARM_CORTEX_M && MCUC1_CONFIG_CORTEX_M>=3))
  /*!< 1: Cortex-M3, M4 have Auxiliary Control Register, ACTLR register */

#ifndef HF1_CONFIG_SETTING_DISABLE_WRITE_BUFFER
  #define HF1_CONFIG_SETTING_DISABLE_WRITE_BUFFER   (0 && HF1_CONFIG_SETTING_HAS_ACTLR)
  /*!< 1: disable write buffer in ACTLR register */
#endif

#ifndef HF1_CONFIG_SETTING_SEMIHOSTING
  #define HF1_CONFIG_SETTING_SEMIHOSTING   (1)
  /*!< 1: do not stop in handler with semihosting and no debugger attached. 0: semihosting hardfault will stop target */
#endif


#endif /* __HF1_CONFIG_H */
