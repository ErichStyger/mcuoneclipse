/**
 * \file
 * \brief Configuration header file for Nordic Semiconductor nRF24L01+ transceiver
 *
 * This header file is used to configure settings of the nRF24L01 module.
 */

#ifndef __RF1_CONFIG_H
#define __RF1_CONFIG_H

#ifndef RF1_CONFIG_IRQ_PIN_ENABLED
  void RF1_OnInterrupt(void); /* prototype for interrupt handler */
  #define RF1_CONFIG_IRQ_PIN_ENABLED  0
    /*!< 1: IRQ pin is enabled, 0: No IRQ pin available */
#endif

#ifndef RF1_CONFIG_ON_ACTIVATE_CALLBACK
  void RF1_OnActivate(void); /* prototype */
  #define RF1_CONFIG_ON_ACTIVATE_CALLBACK()  /* RF1_OnActivate() */
    /*!< User callback called before using device */
#endif

#ifndef RF1_CONFIG_ON_DEACTIVATE_CALLBACK
  void RF1_OnActivate(void); /* prototype */
  #define RF1_CONFIG_ON_DEACTIVATE_CALLBACK()  /* RF1_OnDeactivate() */
    /*!< User callback called after using device */
#endif

#ifndef RF1_CONFIG_USE_MUTEX
  #define RF1_CONFIG_USE_MUTEX  1
    /*!< 1: Use FreeRTOS Mutex, 0: Do not use FreeRTOS mutex */
#endif

#endif /* __RF1_CONFIG_H */
