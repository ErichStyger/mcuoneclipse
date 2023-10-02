/**
 * \file
 * \brief This is a main configuration file for the RNet stack
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * With this header file, the stack is configured. It sets the configuration defaults.
 * The application can overwrite the configuration with a RNet_AppConfig.h header file.
 */

#ifndef __McuRNet_CONFIG_H
#define __McuRNet_CONFIG_H

#include "McuRNetConfig.h"
#if McuRNET_CONFIG_IS_ENABLED

#ifndef McuRNet_CONFIG_APPLICATION_HEADER_FILE
  #define McuRNet_CONFIG_APPLICATION_HEADER_FILE    "RNet_AppConfig.h"
    /*!< Header file to be used for the RNet application configuration */
#endif

#include "McuLib.h"
//#include McuRNet_CONFIG_APPLICATION_HEADER_FILE /* User application configuration file */
#include "McuRNet.h"  /* component main header file */

#ifndef McuRNET_CONFIG_IS_ENABLED
  #define McuRNET_CONFIG_IS_ENABLED       (1 && McuLib_CONFIG_SDK_USE_FREERTOS)
#endif

/* remote standard I/O destination address */
#ifndef RSTDIO_CONFIG_SETTING_RSTDIO_DEFAULT_DESTINATION_ADDRESS
  #define RSTDIO_CONFIG_SETTING_RSTDIO_DEFAULT_DESTINATION_ADDRESS   255
#endif

/* Default configuration items, can be overwritten by the application configuration header file: */
#define RNET_CONFIG_TRANSCEIVER_NRF24   1
  /*!< Nordic Semiconductor nRF24L01+ */
#define RNET_CONFIG_TRANSCEIVER_MC13201 2
  /*!< Freescale MC13201/MC13213 */

#define RNET_CONFIG_TRANSCEIVER_TYPE  RNET_CONFIG_TRANSCEIVER_NRF24
  /*!< Transceiver type used */

#if RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_NRF24
  /* nRF24L01+ specific settings */
  #ifndef RNET_CONFIG_NRF24_DATA_RATE
    #define RNET_CONFIG_NRF24_DATA_RATE  (McuNRF24L01_RF_SETUP_RF_DR_2000)
      /*!< default transceiver data rate */
  #endif
#endif /* RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_NRF24 */

#if RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_MC13201
  /* MC1320x specific settings */
  #ifndef RNET_CONFIG_SMAC_OUPTUT_POWER
  #define RNET_CONFIG_SMAC_OUPTUT_POWER  (McuNRF24L01_RF_SETUP_RF_DR_2000)
    /*!< default transceiver data rate */
#endif

#endif /* RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_MC13201 */

#ifndef RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE
  #define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  (32)
    /*!< Size of the physical transceiver payload (bytes), max 32 bytes for nRF24L01+, max 128 bytes for MC1320x */
#endif

#ifndef RNET_CONFIG_TRANSCEIVER_CHANNEL
  #define RNET_CONFIG_TRANSCEIVER_CHANNEL  (81)
    /*!< default radio channel of transceiver */
#endif

#ifndef RNET_CONFIG_SHORT_ADDR_SIZE
  #define RNET_CONFIG_SHORT_ADDR_SIZE   (1)
    /*!< size of short address type. Either 1 or 2 */
#endif

#ifndef RNET_CONFIG_SEND_RETRY_CNT
  #define RNET_CONFIG_SEND_RETRY_CNT    (3)
    /*!< Number of retries if message sending failed. Set to zero to disable retry. */
#endif

/* Configuration for Rx and Tx queues */
#ifndef RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS
  #define RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS        (15)
    /*!< Number items in the Rx message queue. The higher, the more items can be buffered. */
#endif

#ifndef RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS
  #define RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS        (15)
    /*!< Number items in the Tx message queue. The higher, the more items can be buffered. */
#endif

#ifndef RNET_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS
  #define RNET_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS   (200/portTICK_PERIOD_MS)
    /*!< Blocking time for putting items into the message queue before timeout. Use portMAX_DELAY for blocking. */
#endif

#ifndef RNET_CONFIG_REMOTE_STDIO
  #define RNET_CONFIG_REMOTE_STDIO        (1)
    /*!< 1 for remote stdio over radio enabled, 0 for disabled. */
#endif

#ifndef RNET_RADIO_WAITNG_TIMEOUT_MS
  #define RNET_RADIO_WAITNG_TIMEOUT_MS   250 /* timeout value in milliseconds, used for RADIO_WAITING_DATA_SENT */
#endif

#endif /* McuRNET_CONFIG_IS_ENABLED */

#endif /* __McuRNet_CONFIG_H */
