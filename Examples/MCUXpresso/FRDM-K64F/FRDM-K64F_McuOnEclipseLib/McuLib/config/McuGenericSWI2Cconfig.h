/**
 * \file
 * \brief Configuration header file for GenericSWI2C
 *
 * This header file is used to configure settings of the software (bit-banging) I2C module.
 */

#ifndef __McuGenericSWI2C_CONFIG_H
#define __McuGenericSWI2C_CONFIG_H

#ifndef McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE
  #define McuGenericSWI2C_CONFIG_TIMEOUT_COUNTER_VALUE    (65535)
    /*!< Timeout counter value waiting for a SDA or CLK line change. The higher the value, the longer the timeout */
#endif

#endif /* __McuGenericSWI2C_CONFIG_H */
