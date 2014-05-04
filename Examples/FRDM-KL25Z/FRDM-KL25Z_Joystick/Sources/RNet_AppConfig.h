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

/*! type ID's for application messages */
typedef enum {
  RAPP_MSG_TYPE_STDIN = 0x00,
  RAPP_MSG_TYPE_STDOUT = 0x01,
  RAPP_MSG_TYPE_STDERR = 0x02,
  RAPP_MSG_TYPE_JOYSTICK_XY = 0x53, /* Joystick xy message: data is x,y (two signed bytes) from -128...127 */
  RAPP_MSG_TYPE_JOYSTICK_BTN = 0x54, /* Joystick button message (data is one byte: 'A', 'B', ... 'F' and 'K') */
  RAPP_MSG_TYPE_DATA = 0x55, /* ID for data message */
} RAPP_MSG_Type;

#endif /* __RNET_APP_CONFIG__ */
