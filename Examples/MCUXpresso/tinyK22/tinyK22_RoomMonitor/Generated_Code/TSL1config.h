#ifndef __TSL1_CONFIG_H
#define __TSL1_CONFIG_H

#define TSL2561_CONFIG_PACKAGE_CS       (0)
  /*!< 1: device is in CS package. 0: device is in normal package */

#define TSL2561_CONFIG_I2C_DEVICE_ADDRESS  0b0111001
  /*!< Device I2C address */
//#define TSL2561_CONFIG_I2C_DEVICE_ADDRESS  0b0101001  /* device address with ADDR pin set to GND */
//#define TSL2561_CONFIG_I2C_DEVICE_ADDRESS  0b0111001  /* device address with ADDR pin floating */
//#define TSL2561_CONFIG_I2C_DEVICE_ADDRESS  0b1001001  /* device address with ADDR pin set to VDD */

#if !defined(TSL1_CONFIG_PARSE_COMMAND_ENABLED)
  #define TSL1_CONFIG_PARSE_COMMAND_ENABLED                (1)
    /*!< 1: shell support enabled, 0: otherwise */
#endif

#endif /* __TSL1_CONFIG_H */
