/**
 * \file
 * \brief Configuration header file for SDK_BitIO
 *
 * This header file is used to configure settings of the SDK Bit I/O module.
 */
#ifndef __DQ1_CONFIG_H
#define __DQ1_CONFIG_H

#ifndef DQ1_CONFIG_PORT_NAME
  #define DQ1_CONFIG_PORT_NAME       GPIO1
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef DQ1_CONFIG_GPIO_NAME
  #define DQ1_CONFIG_GPIO_NAME       GPIO1
    /*!< name of GPIO, is pointer to GPIO_Type, not used for S32K SDK */
#endif

#ifndef DQ1_CONFIG_PIN_NUMBER
  #define DQ1_CONFIG_PIN_NUMBER      0u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef DQ1_CONFIG_PIN_SYMBOL
  #define DQ1_CONFIG_PIN_SYMBOL      OneWireData
    /*!< symbolic name for pin, used for NXP SDK V1.3 */
#endif

#ifndef DQ1_CONFIG_INIT_PIN_VALUE
  #define DQ1_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define DQ1_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define DQ1_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define DQ1_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef DQ1_CONFIG_INIT_PIN_DIRECTION
  #define DQ1_CONFIG_INIT_PIN_DIRECTION  DQ1_CONFIG_INIT_PIN_DIRECTION_INPUT
#endif

#ifndef DQ1_CONFIG_DO_PIN_MUXING
  #define DQ1_CONFIG_DO_PIN_MUXING  0
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#ifndef DQ1_CONFIG_PULL_RESISTOR
  #define DQ1_CONFIG_PULL_RESISTOR  0
  /*!< pull resistor setting. 0: no pull resistor, 1: pull-up, 2: pull-down, 3: pull-up or no pull, 4: pull-down or no pull: 4: autoselect-pull */
#endif

#endif /* __DQ1_CONFIG_H */
