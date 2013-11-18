/**
 * \file
 * \brief This is a configuration file for the RNet stack
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * Here the stack can be configured using macros.
 */

#ifndef __RNET_CONFIG__
#define __RNET_CONFIG__

#include "Platform.h"
#if PL_HAS_RADIO

#define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  32  
  /*!< Size of the physical transceiver payload (bytes), max 32 bytes for nRF24L01+, max 128 bytes for MC1320x */

#define RNET_CONFIG_SHORT_ADDR_SIZE   1 
  /*!< size of short address type. Either 1 or 2 */

#endif /* PL_HAS_RADIO */

#endif /* __RNET_CONFIG__ */
