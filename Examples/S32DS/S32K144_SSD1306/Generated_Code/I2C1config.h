/**
 * \file
 * \brief Configuration header file for GenericSWI2C
 *
 * This header file is used to configure settings of the software (bit-banging) I2C module.
 */

#ifndef __I2C1_CONFIG_H
#define __I2C1_CONFIG_H

#ifndef I2C1_CONFIG_TIMEOUT_COUNTER_VALUE
  #define I2C1_CONFIG_TIMEOUT_COUNTER_VALUE    (65535)
    /*!< Timeout counter value waiting for a SDA or CLK line change. The higher the value, the longer the timeout */
#endif

#ifndef I2C1_CONFIG_DELAY_NS
  #define I2C1_CONFIG_DELAY_NS    (1250)
    /*!< delay time in ns */
#endif

#ifndef I2C1_CONFIG_NOF_TRIALS
  #define I2C1_CONFIG_NOF_TRIALS    (256)
    /*!< number of trials */
#endif

#ifndef I2C1_CONFIG_DO_YIELD
  #define I2C1_CONFIG_DO_YIELD    (1)
    /*!< 1: if RTOS present, do a yield. 0: do not yield during waiting */
#endif

#endif /* __I2C1_CONFIG_H */
