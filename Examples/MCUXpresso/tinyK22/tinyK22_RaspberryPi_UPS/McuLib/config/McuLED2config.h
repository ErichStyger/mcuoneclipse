#ifndef __McuLED2_CONFIG_H
#define __McuLED2_CONFIG_H

#ifndef McuLED2_CONFIG_USE_GPIO_PIN
  #define McuLED2_CONFIG_USE_GPIO_PIN   (1)
    /*!< 1: use GPIO pin; 0: use PWM pin */
#endif

#ifndef McuLED2_CONFIG_IS_LOW_ACTIVE
  #define McuLED2_CONFIG_IS_LOW_ACTIVE   (1)
    /*!< 1: LED is low active (cathode on port side), 0: LED is HIGH active (anode on port side) */
#endif

#endif /* __McuLED2_CONFIG_H */
