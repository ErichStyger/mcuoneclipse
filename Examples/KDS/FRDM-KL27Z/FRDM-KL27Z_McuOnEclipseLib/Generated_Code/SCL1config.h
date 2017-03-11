#ifndef __SCL1_CONFIG_H
#define __SCL1_CONFIG_H

#ifndef SCL1_CONFIG_PORT_NAME
  #define SCL1_CONFIG_PORT_NAME       PORTD
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef SCL1_CONFIG_GPIO_NAME
  #define SCL1_CONFIG_GPIO_NAME       GPIOD
    /*!< name of GPIO, is pointer to GPIO_Type */
#endif

#ifndef SCL1_CONFIG_PIN_NUMBER
  #define SCL1_CONFIG_PIN_NUMBER      7u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef SCL1_CONFIG_INIT_PIN_VALUE
  #define SCL1_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define SCL1_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define SCL1_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define SCL1_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef SCL1_CONFIG_INIT_PIN_DIRECTION
  #define SCL1_CONFIG_INIT_PIN_DIRECTION  SCL1_CONFIG_INIT_PIN_DIRECTION_INPUT
#endif

#ifndef SCL1_CONFIG_DO_PIN_MUXING
  #define SCL1_CONFIG_DO_PIN_MUXING  1
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#endif /* __SCL1_CONFIG_H */
