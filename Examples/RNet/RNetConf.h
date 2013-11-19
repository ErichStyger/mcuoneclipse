/**
 * \file
 * \brief This is a main configuration file for the RNet stack
 * \author (c) 2013 Erich Styger, http://mcuoneclipse.com/
 * \note MIT License (http://opensource.org/licenses/mit-license.html)
 *
 * With this header file, the stack is configured. It sets the configuration defaults.
 * The application can overwrite the configuration with a RNet_AppConfig.h header file.
 */

#ifndef RNETCONF_H_
#define RNETCONF_H_

#include "RNet_AppConfig.h" /* user application configuration file */

/* default configuration items, can be overwritten by the application configuration header file: */

#ifndef RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE
#define RNET_CONFIG_TRANSCEIVER_PAYLOAD_SIZE  32
  /*!< Size of the physical transceiver payload (bytes), max 32 bytes for nRF24L01+, max 128 bytes for MC1320x */
#endif

#ifndef RNET_CONFIG_SHORT_ADDR_SIZE
#define RNET_CONFIG_SHORT_ADDR_SIZE   1 
  /*!< size of short address type. Either 1 or 2 */
#endif

#ifndef RNET_CONFIG_USE_ACK
#define RNET_CONFIG_USE_ACK           0
  /*!< If set to 1, the NWK layer will send an acknowledge message for every data packet received */
#endif

#endif /* RNETCONF_H_ */
