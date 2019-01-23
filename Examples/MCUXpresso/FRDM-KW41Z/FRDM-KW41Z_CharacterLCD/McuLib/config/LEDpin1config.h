/**
 * \file
 * \brief Configuration header file for SDK_BitIO
 *
 * This header file is used to configure settings of the SDK Bit I/O module.
 */
#ifndef __LEDpin1_CONFIG_H
#define __LEDpin1_CONFIG_H

#ifndef LEDpin1_CONFIG_PORT_NAME
  #if McuLib_CONFIG_CPU_IS_IMXRT
    #define LEDpin1_CONFIG_PORT_NAME       GPIO1
  #else /* name from properties */
    #define LEDpin1_CONFIG_PORT_NAME       PORTA
  #endif
    /*!< name of PORT, is pointer to PORT_Type */
#endif

#ifndef LEDpin1_CONFIG_GPIO_NAME
  #if McuLib_CONFIG_CPU_IS_IMXRT
    #define LEDpin1_CONFIG_GPIO_NAME       GPIO1
  #else /* name from properties */
    #define LEDpin1_CONFIG_GPIO_NAME       GPIOA
  #endif
    /*!< name of GPIO, is pointer to GPIO_Type, not used for S32K SDK */
#endif

#ifndef LEDpin1_CONFIG_PIN_NUMBER
  #define LEDpin1_CONFIG_PIN_NUMBER      19u
    /*!< number of pin, type unsigned integer */
#endif

#ifndef LEDpin1_CONFIG_PIN_SYMBOL
  #define LEDpin1_CONFIG_PIN_SYMBOL      LED_GREEN
    /*!< symbolic name for pin, used for NXP SDK V1.3 */
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
  #define LEDpin1_CONFIG_DO_PIN_MUXING  0
  /*!< 1: perform pin muxing in Init(), 0: do not do pin muxing */
#endif

#ifndef LEDpin1_CONFIG_PULL_RESISTOR
  #define LEDpin1_CONFIG_PULL_RESISTOR  0
  /*!< pull resistor setting. 0: no pull resistor, 1: pull-up, 2: pull-down, 3: pull-up or no pull, 4: pull-down or no pull: 4: autoselect-pull */
#endif

#endif /* __LEDpin1_CONFIG_H */
