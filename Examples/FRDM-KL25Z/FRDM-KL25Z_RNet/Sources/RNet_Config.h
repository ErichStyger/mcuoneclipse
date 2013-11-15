/**
 * \file
 * \brief This is a configuration file for the RNet stack
 * \author Erich Styger
 *
 */

#ifndef __RNET_CONFIG__
#define __RNET_CONFIG__

#include "Platform.h"
#if PL_HAS_RADIO
//  #include "SMAC1.h"
//  #define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  SMAC1_RADIO_BUF_SIZE  /* max 128 bytes */
  #define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  32  /* max 32 bytes */

#define RNET_CONFIG_SHORT_ADDR_SIZE   2 
  /*!< size of short address type. Either 1 or 2 */

#endif /* PL_HAS_RADIO */

#endif /* __RNET_CONFIG__ */
