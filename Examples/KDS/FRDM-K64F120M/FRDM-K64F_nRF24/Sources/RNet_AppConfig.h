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

/*! type ID's for application messages */
typedef enum {
  RAPP_MSG_TYPE_PING = 0x55,
} RAPP_MSG_Type;

#endif /* __RNET_APP_CONFIG__ */
