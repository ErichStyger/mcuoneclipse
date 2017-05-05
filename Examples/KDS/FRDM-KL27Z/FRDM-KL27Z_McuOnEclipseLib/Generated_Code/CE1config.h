/**
 * \file
 * \brief Configuration header file for SDK_BitIO
 *
 * This header file is used to configure settings of the SDK Bit I/O module.
 */
#ifndef __CE1_CONFIG_H
#define __CE1_CONFIG_H

#ifndef CE1_CONFIG_PORT_NAME
  #define CE1_CONFIG_PORT_NAME       PORTA
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef CE1_CONFIG_GPIO_NAME
  #define CE1_CONFIG_GPIO_NAME       GPIOA
    /*!< name of GPIO, is pointer to GPIO_Type */
#endif

#ifndef CE1_CONFIG_PIN_NUMBER
  #define CE1_CONFIG_PIN_NUMBER      4u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef CE1_CONFIG_INIT_PIN_VALUE
  #define CE1_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define CE1_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define CE1_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define CE1_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef CE1_CONFIG_INIT_PIN_DIRECTION
  #define CE1_CONFIG_INIT_PIN_DIRECTION  CE1_CONFIG_INIT_PIN_DIRECTION_OUTPUT
#endif

#ifndef CE1_CONFIG_DO_PIN_MUXING
  #define CE1_CONFIG_DO_PIN_MUXING  1
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#endif /* __CE1_CONFIG_H */
