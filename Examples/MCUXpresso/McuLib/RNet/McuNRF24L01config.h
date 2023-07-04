/**
 * \file
 * \brief Configuration header file for Nordic Semiconductor nRF24L01+ transceiver
 *
 * This header file is used to configure settings of the nRF24L01 module.
 */

#ifndef __McuNRF24L01_CONFIG_H
#define __McuNRF24L01_CONFIG_H

#ifndef McuNRF24L01_CONFIG_IS_ENABLED
  #define McuNRF24L01_CONFIG_IS_ENABLED  (0)
    /*!< 1: enable driver/module; 0: module is not enabled */
#endif

#ifndef McuNRF24L01_CONFIG_IRQ_PIN_ENABLED
  void McuNRF24L01_OnInterrupt(void); /* prototype for interrupt handler */
  #define McuNRF24L01_CONFIG_IRQ_PIN_ENABLED  (0)
    /*!< 1: IRQ pin is enabled, 0: No IRQ pin available */
#endif

#ifndef McuNRF24L01_CONFIG_ON_ACTIVATE_CALLBACK
  void McuNRF24L01_OnActivate(void); /* prototype */
  #define McuNRF24L01_CONFIG_ON_ACTIVATE_CALLBACK()  McuNRF24L01_OnActivate()
    /*!< User callback called before using device */
#endif

#ifndef McuNRF24L01_CONFIG_ON_DEACTIVATE_CALLBACK
  void McuNRF24L01_OnDeactivate(void); /* prototype */
  #define McuNRF24L01_CONFIG_ON_DEACTIVATE_CALLBACK()  McuNRF24L01_OnDeactivate()
    /*!< User callback called after using device */
#endif

#ifndef McuNRF24L01_CONFIG_USE_MUTEX
  #define McuNRF24L01_CONFIG_USE_MUTEX  (1)
    /*!< 1: Use FreeRTOS Mutex, 0: Do not use FreeRTOS mutex */
#endif

#ifndef McuNRF24L01_CONFIG_INITIALIZE_DURING_STARTUP
  #define McuNRF24L01_CONFIG_INITIALIZE_DURING_STARTUP  (0)
    /*!< 1: Call Init() during startup, 0: Do not call Init() */
#endif


#ifndef McuNRF24L01_CONFIG_CS_PIN_PORT

#endif

#endif /* __McuNRF24L01_CONFIG_H */
