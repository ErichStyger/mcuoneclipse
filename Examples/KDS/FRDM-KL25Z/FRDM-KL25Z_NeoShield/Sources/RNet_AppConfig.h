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
  RAPP_MSG_TYPE_STDIN = 0x00,
  RAPP_MSG_TYPE_STDOUT = 0x01,
  RAPP_MSG_TYPE_STDERR = 0x02,
  RAPP_MSG_TYPE_ACCEL = 0x03,
  RAPP_MSG_TYPE_DATA = 0x04,
  RAPP_MSG_TYPE_JOYSTICK_XY = 0x05,     /* Joystick xy message: data is x,y (two signed bytes) from -128...127 */
  RAPP_MSG_TYPE_JOYSTICK_BTN = 0x54,    /* Joystick button message (data is one byte: 'A', 'B', ... 'F' and 'K') */
  RAPP_MSG_TYPE_REQUEST_SET_VALUE = 0x55,      /* request to set a value for id: 16bit ID followed by 32bit value */
  RAPP_MSG_TYPE_NOTIFY_VALUE = 0x56,           /* notification about a value: 16bit ID followed by 32bit value */
  RAPP_MSG_TYPE_QUERY_VALUE = 0x57,            /* request to query for a value: data is 16bit ID */
  RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE = 0x58,   /* response for RAPP_MSG_TYPE_QUERY_VALUE request: 16bit ID followed by 32bit value */
} RAPP_MSG_Type;

/* IDs for RAPP_MSG_TYPE_QUERY_VALUE and RAPP_MSG_TYPE_QUERY_VALUE_RESPONSE */
typedef enum {
  RAPP_MSG_TYPE_DATA_ID_NONE = 0,           /* dummy ID */
  RAPP_MSG_TYPE_DATA_ID_MINT_BALL = 1,      /* ball presence status: 0: not present, 1: present */
  RAPP_MSG_TYPE_DATA_ID_MINT_MODE = 2,      /* mint mode: 0: manual, 1: automatic */
  RAPP_MSG_TYPE_DATA_ID_MINT_GOTO = 3,      /* goto command: 0 (line), 1 (start), 2 (finish) */
  RAPP_MSG_TYPE_DATA_ID_TOF_VALUES = 4,     /* ToF values: four 8bit values */
  RAPP_MSG_TYPE_DATA_ID_POSITION = 5,       /* Position information: 0: no position, 1: start position, 3: finish position */
  RAPP_MSG_TYPE_DATA_ID_REED_CONTACT = 6,   /* Reed contact position: 0: no position, 1: start position, 3: finish position */
  RAPP_MSG_TYPE_DATA_ID_BATTERY_V = 7,      /* Battery voltage */
  RAPP_MSG_TYPE_DATA_ID_PID_FW_SPEED = 8,   /* PID forward speed */
  RAPP_MSG_TYPE_DATA_ID_NEO_BRIGHTNESS = 9, /* NeoPixel brightness */
  RAPP_MSG_TYPE_DATA_ID_NEO_RED = 10,       /* NeoPixel red color level */
  RAPP_MSG_TYPE_DATA_ID_NEO_GREEN = 11,     /* NeoPixel green color level */
  RAPP_MSG_TYPE_DATA_ID_NEO_BLUE = 12,      /* NeoPixel blue color level */
} RAPP_MSG_DateIDType;

#endif /* __RNET_APP_CONFIG__ */
