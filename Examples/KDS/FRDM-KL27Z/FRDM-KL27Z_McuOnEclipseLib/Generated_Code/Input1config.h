#ifndef __Input1_CONFIG_H
#define __Input1_CONFIG_H

#ifndef Input1_CONFIG_PORT_NAME
  #define Input1_CONFIG_PORT_NAME       PORTA
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef Input1_CONFIG_GPIO_NAME
  #define Input1_CONFIG_GPIO_NAME       GPIOA
    /*!< name of GPIO, is pointer to GPIO_Type */
#endif

#ifndef Input1_CONFIG_PIN_NUMBER
  #define Input1_CONFIG_PIN_NUMBER      1u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef Input1_CONFIG_INIT_PIN_VALUE
  #define Input1_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define Input1_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define Input1_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define Input1_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef Input1_CONFIG_INIT_PIN_DIRECTION
  #define Input1_CONFIG_INIT_PIN_DIRECTION  Input1_CONFIG_INIT_PIN_DIRECTION_OUTPUT
#endif

#ifndef Input1_CONFIG_DO_PIN_MUXING
  #define Input1_CONFIG_DO_PIN_MUXING  0
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#endif /* __Input1_CONFIG_H */
