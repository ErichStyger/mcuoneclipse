/**
 * \file
 * \brief Configuration header file for Nordic Semiconductor nRF24L01+ transceiver
 *
 * This header file is used to configure settings of the nRF24L01 module.
 */

#ifndef __McuNRF24L01_CONFIG_H
#define __McuNRF24L01_CONFIG_H

#include "McuLib.h"

#ifndef McuNRF24L01_CONFIG_IS_ENABLED
  #define McuNRF24L01_CONFIG_IS_ENABLED  (0)
    /*!< 1: enable driver/module; 0: module is not enabled */
#endif

#ifndef McuNRF24L01_CONFIG_IRQ_PIN_ENABLED
  void McuNRF24L01_OnInterrupt(void); /* prototype for interrupt handler */
  #define McuNRF24L01_CONFIG_IRQ_PIN_ENABLED  (0)
    /*!< 1: IRQ pin is enabled, 0: No IRQ pin available */
#endif

#ifndef McuNRF24L01_CONFIG_USE_ON_ACTIVATE_CALLBACK
  #define McuNRF24L01_CONFIG_USE_ON_ACTIVATE_CALLBACK  (0)
    /*!< If McuNRF24L01_CONFIG_ON_ACTIVATE_CALLBACK is called or not */
#endif

#ifndef McuNRF24L01_CONFIG_ON_ACTIVATE_CALLBACK
  void McuNRF24L01_OnActivate(void); /* prototype */
  #define McuNRF24L01_CONFIG_ON_ACTIVATE_CALLBACK()  McuNRF24L01_OnActivate()
    /*!< User callback called before using device */
#endif

#ifndef McuNRF24L01_CONFIG_USE_ON_DEACTIVATE_CALLBACK
  #define McuNRF24L01_CONFIG_USE_ON_DEACTIVATE_CALLBACK  (0)
    /*!< If McuNRF24L01_CONFIG_ON_DEACTIVATE_CALLBACK is called or not */
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

#ifndef McuNRF24L01_CONFIG_CE_CSN_PIN_PRE_INIT
  #if McuLib_CONFIG_CPU_IS_RPxxxx
    #define McuNRF24L01_CONFIG_CE_CSN_PIN_PRE_INIT() /* nothing needed */
  #elif McuLib_CONFIG_CPU_IS_ESP32
    #define McuNRF24L01_CONFIG_CE_CSN_PIN_PRE_INIT() /* nothing needed */
  #elif McuLib_CONFIG_CPU_IS_KINETIS
    #define McuNRF24L01_CONFIG_CE_CSN_PIN_PRE_INIT()  CLOCK_EnableClock(kCLOCK_PortB)
      /*!< Optional hardware initialization for CS Pin */
  #endif
#endif

#ifndef McuNRF24L01_CONFIG_CE_PIN_GPIO
  #define McuNRF24L01_CONFIG_CE_PIN_GPIO   GPIOB
    /*!< GPIO for CE Pin */
#endif

  #ifndef McuNRF24L01_CONFIG_CE_PIN_PORT
  #define McuNRF24L01_CONFIG_CE_PIN_PORT   PORTB
    /*!< PORT for CE Pin */
#endif

#ifndef McuNRF24L01_CONFIG_CE_PIN_NUMBER
  #define McuNRF24L01_CONFIG_CE_PIN_NUMBER   10
    /*!< Pin number of the CE Pin */
#endif

#ifndef McuNRF24L01_CONFIG_CSN_PIN_GPIO
  #define McuNRF24L01_CONFIG_CSN_PIN_GPIO   GPIOB
    /*!< GPIO for CSN Pin */
#endif

#ifndef McuNRF24L01_CONFIG_CSN_PIN_PORT
  #define McuNRF24L01_CONFIG_CSN_PIN_PORT   PORTB
    /*!< PORT for CSN Pin */
#endif

#ifndef McuNRF24L01_CONFIG_CSN_PIN_NUMBER
  #define McuNRF24L01_CONFIG_CSN_PIN_NUMBER   0
    /*!< Pin number of the CSN Pin */
#endif

#ifndef McuNRF24L01_CONFIG_IRQ_PIN_GPIO
  #define McuNRF24L01_CONFIG_IRQ_PIN_GPIO   GPIOB
    /*!< GPIO for IRQ Pin */
#endif

#ifndef McuNRF24L01_CONFIG_IRQ_PIN_PORT
  #define McuNRF24L01_CONFIG_IRQ_PIN_PORT   PORTB
    /*!< PORT for IRQ Pin */
#endif

#ifndef McuNRF24L01_CONFIG_IRQ_PIN_NUMBER
  #define McuNRF24L01_CONFIG_IRQ_PIN_NUMBER   0
    /*!< Pin number of the IRQ Pin */
#endif

#ifndef McuNRF24L01_CONFIG_IRQ_LINE_NUMBER
  #define McuNRF24L01_CONFIG_IRQ_LINE_NUMBER   PORTB_IRQn
    /*!< Kinetis IRQ line number for interrupt settings */
#endif

#endif /* __McuNRF24L01_CONFIG_H */
