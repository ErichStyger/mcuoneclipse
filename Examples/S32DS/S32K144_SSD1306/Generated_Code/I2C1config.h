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

#endif /* __I2C1_CONFIG_H */
