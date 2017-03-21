#ifndef __LEDpin1_CONFIG_H
#define __LEDpin1_CONFIG_H

#ifndef LEDpin1_CONFIG_PORT_NAME
  #define LEDpin1_CONFIG_PORT_NAME       PORTE
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef LEDpin1_CONFIG_GPIO_NAME
  #define LEDpin1_CONFIG_GPIO_NAME       GPIOE
    /*!< name of GPIO, is pointer to GPIO_Type */
#endif

#ifndef LEDpin1_CONFIG_PIN_NUMBER
  #define LEDpin1_CONFIG_PIN_NUMBER      31u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef LEDpin1_CONFIG_INIT_PIN_VALUE
  #define LEDpin1_CONFIG_INIT_PIN_VALUE  0
  /*!< 0: Pin data is initialized with 0 (low); 1: pin value is initialized with 1 (high) */
#endif

/* different types of pin direction settings */
#define LEDpin1_CONFIG_INIT_PIN_DIRECTION_NONE    (0)
#define LEDpin1_CONFIG_INIT_PIN_DIRECTION_INPUT   (1)
#define LEDpin1_CONFIG_INIT_PIN_DIRECTION_OUTPUT  (2)

#ifndef LEDpin1_CONFIG_INIT_PIN_DIRECTION
  #define LEDpin1_CONFIG_INIT_PIN_DIRECTION  LEDpin1_CONFIG_INIT_PIN_DIRECTION_OUTPUT
#endif

#ifndef LEDpin1_CONFIG_DO_PIN_MUXING
  #define LEDpin1_CONFIG_DO_PIN_MUXING  1
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#endif /* __LEDpin1_CONFIG_H */
