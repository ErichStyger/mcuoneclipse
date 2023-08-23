/**
 * \file
 * \brief Configuration header file for GenericSWI2C
 * Copyright (c) 2020, Erich Styger
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * This header file is used to configure settings of the software (bit-banging) I2C module.
 */

#ifndef __McuGenericSWI2C_CONFIG_H
#define __McuGenericSWI2C_CONFIG_H

#ifndef McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE
  #define McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE    (65535)
    /*!< Timeout counter value waiting for a SDA or CLK line change. The higher the value, the longer the timeout */
#endif

#ifndef McuGenericSWI2C_CONFIG_DELAY_NS
  #define McuGenericSWI2C_CONFIG_DELAY_NS    (1250)
    /*!< delay time in ns */
#endif

#ifndef McuGenericSWI2C_CONFIG_NOF_TRIALS
  #define McuGenericSWI2C_CONFIG_NOF_TRIALS    (256)
    /*!< number of trials */
#endif

#ifndef McuGenericSWI2C_CONFIG_DO_YIELD
  #define McuGenericSWI2C_CONFIG_DO_YIELD    (0)
    /*!< 1: if RTOS present, do a yield. 0: do not yield during waiting */
#endif

#endif /* __McuGenericSWI2C_CONFIG_H */
