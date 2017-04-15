#ifndef __LEDpin2_CONFIG_H
#define __LEDpin2_CONFIG_H

#ifndef LEDpin2_CONFIG_PORT_NAME
  #define LEDpin2_CONFIG_PORT_NAME       PORTE
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef LEDpin2_CONFIG_GPIO_NAME
  #define LEDpin2_CONFIG_GPIO_NAME       GPIOE
    /*!< name of GPIO, is pointer to GPIO_Type */
#endif

#ifndef LEDpin2_CONFIG_PIN_NUMBER
  #define LEDpin2_CONFIG_PIN_NUMBER      26u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef LEDpin2_CONFIG_INIT_PIN_VALUE
  #define LEDpin2_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define LEDpin2_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define LEDpin2_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define LEDpin2_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef LEDpin2_CONFIG_INIT_PIN_DIRECTION
  #define LEDpin2_CONFIG_INIT_PIN_DIRECTION  LEDpin2_CONFIG_INIT_PIN_DIRECTION_OUTPUT
#endif

#ifndef LEDpin2_CONFIG_DO_PIN_MUXING
  #define LEDpin2_CONFIG_DO_PIN_MUXING  1
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#endif /* __LEDpin2_CONFIG_H */
