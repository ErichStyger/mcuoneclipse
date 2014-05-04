/**
 * \file
 * \brief This is a main configuration file for the RNet stack
 * \author (c) 2013-2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * With this header file, the stack is configured. It sets the configuration defaults.
 * The application can overwrite the configuration with a RNet_AppConfig.h header file.
 */

#ifndef RNETCONF_H_
#define RNETCONF_H_

#include "%'ModuleName'.h"  /* component main header file */
#include "RNet_AppConfig.h" /* User application configuration file */

/* Default configuration items, can be overwritten by the application configuration header file: */
#define RNET_CONFIG_TRANSCEIVER_NRF24   1 
  /*!< Nordic Semiconductor nRF24L01+ */
#define RNET_CONFIG_TRANSCEIVER_MC13201 2
  /*!< Freescale MC13201/MC13213 */

%if defined(TransceiverType)
#define RNET_CONFIG_TRANSCEIVER_TYPE  %TransceiverType
%else
#define RNET_CONFIG_TRANSCEIVER_TYPE  RNET_CONFIG_TRANSCEIVER_NRF24
%endif
  /*!< Transceiver type used */

#if RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_NRF24
/* nRF24L01+ specific settings */
#ifndef RNET_CONFIG_NRF24_DATA_RATE
%if defined(nRF24DataRate) & defined(nRF24L01p)
#define RNET_CONFIG_NRF24_DATA_RATE  (%@nRF24L01p@'ModuleName'%.%nRF24DataRate)
%else
#define RNET_CONFIG_NRF24_DATA_RATE  (RF1_RF_SETUP_RF_DR_250)
%endif
  /*!< default transceiver data rate */
#endif

#endif /* RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_NRF24 */

#if RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_MC13201
/* MC1320x specific settings */
#ifndef RNET_CONFIG_SMAC_OUPTUT_POWER
%if defined(nRF24DataRate) & defined(nRF24L01p)
#define RNET_CONFIG_SMAC_OUPTUT_POWER  (%@nRF24L01p@'ModuleName'%.%nRF24DataRate)
%else
#define RNET_CONFIG_SMAC_OUPTUT_POWER  (15)
%endif
  /*!< default transceiver data rate */
#endif

#endif /* RNET_CONFIG_TRANSCEIVER_TYPE==RNET_CONFIG_TRANSCEIVER_MC13201 */

#ifndef RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE
%if defined(PayloadSize)
#define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  (%PayloadSize)
%else
#define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  (32)
%endif
  /*!< Size of the physical transceiver payload (bytes), max 32 bytes for nRF24L01+, max 128 bytes for MC1320x */
#endif

#ifndef RNET_CONFIG_TRANSCEIVER_CHANNEL
%if defined(RadioChannel_nRF)
#define RNET_CONFIG_TRANSCEIVER_CHANNEL  (%RadioChannel_nRF)
%elif defined(RadioChannel_SMAC)
#define RNET_CONFIG_TRANSCEIVER_CHANNEL  (%RadioChannel_SMAC)
%else
#define RNET_CONFIG_TRANSCEIVER_CHANNEL  (0)
%endif
  /*!< default radio channel of transceiver */
#endif

#ifndef RNET_CONFIG_SHORT_ADDR_SIZE
%if defined(ShortAddrSize)
#define RNET_CONFIG_SHORT_ADDR_SIZE   (%ShortAddrSize) 
%else
#define RNET_CONFIG_SHORT_ADDR_SIZE   (1) 
%endif
  /*!< size of short address type. Either 1 or 2 */
#endif

#ifndef RNET_CONFIG_USE_ACK
%if defined(UseACK) & %UseACK='yes'
#define RNET_CONFIG_USE_ACK           (1)
%else
#define RNET_CONFIG_USE_ACK           (0)
%endif
  /*!< If set to 1, the NWK layer will send an acknowledge message for every data packet received */
#endif

#ifndef RNET_CONFIG_SEND_RETRY_CNT
%if defined(MsgSendRetryCount)
#define RNET_CONFIG_SEND_RETRY_CNT    (%MsgSendRetryCount)
%else
#define RNET_CONFIG_SEND_RETRY_CNT    (0)
%endif
  /*!< Number of retries if message sending failed. Set to zero to disable retry. */
#endif

/* Configuration for Rx and Tx queues */
#ifndef RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS
%if defined(NofRxQueueItems)
#define RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS        (%NofRxQueueItems)
%else
#define RNET_CONFIG_MSG_QUEUE_NOF_RX_ITEMS        (6)
%endif
  /*!< Number items in the Rx message queue. The higher, the more items can be buffered. */
#endif

#ifndef RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS
%if defined(NofTxQueueItems)
#define RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS        (%NofTxQueueItems)
%else
#define RNET_CONFIG_MSG_QUEUE_NOF_TX_ITEMS        (6)
%endif
  /*!< Number items in the Tx message queue. The higher, the more items can be buffered. */
#endif

#ifndef RNET_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS
%if defined(MsgQueuePutBlockTimeMs)
#define RNET_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS   (%MsgQueuePutBlockTimeMs/portTICK_RATE_MS)
%else
#define RNET_CONFIG_MSG_QUEUE_PUT_BLOCK_TIME_MS   (200/portTICK_RATE_MS)
%endif
  /*!< Blocking time for putting items into the message queue before timeout. Use portMAX_DELAY for blocking. */
#endif

#ifndef RNET_CONFIG_REMOTE_STDIO
%if defined(RStdioEnabled) & %RStdioEnabled='yes'
#define RNET_CONFIG_REMOTE_STDIO        (1)
%else
#define RNET_CONFIG_REMOTE_STDIO        (0)
%endif
  /*!< 1 for remote stdio over radio enabled, 0 for disabled. */
#endif


#endif /* RNETCONF_H_ */
