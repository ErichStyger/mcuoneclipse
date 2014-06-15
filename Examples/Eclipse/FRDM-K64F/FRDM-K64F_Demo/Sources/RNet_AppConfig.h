/**
 * \file
 * \brief This is a configuration file for the RNet stack
 * \author (c) 2014 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * Here the stack can be configured using macros.
 */

#ifndef __RNET_APP_CONFIG__
#define __RNET_APP_CONFIG__

#include "Platform.h"
#if PL_HAS_RADIO

/*! type ID's for application messages */
typedef enum {
  RAPP_MSG_TYPE_STDIN = 0x00,
  RAPP_MSG_TYPE_STDOUT = 0x01,
  RAPP_MSG_TYPE_STDERR = 0x02,
} RAPP_MSG_Type;

#define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  32
  /*!< Size of the physical transceiver payload (bytes), max 32 bytes for nRF24L01+, max 128 bytes for MC1320x */

#define RNET_CONFIG_SHORT_ADDR_SIZE   1
  /*!< size of short address type. Either 1 or 2 */

#define RNET_CONFIG_USE_ACK           1
  /*!< If set to 1, the NWK layer will send an acknowledge message for every data packet received */

#endif /* PL_HAS_RADIO */

#endif /* __RNET_APP_CONFIG__ */
